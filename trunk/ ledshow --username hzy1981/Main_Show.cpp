#define MAIN_SHOW_C
#include "includes.h"


//ÿ���ٶȵ���ʱ,��λΪ����
const INT16U Step_Delay[]=
{
  10,
  20,
  30,
  40,
  50,
  60,
  70,
  80,
  90,
  100
};


//��ȡĳ����������ĳ��������ͣ��ʱ��
INT8U Get_Area_Step_Delay(INT8U Area_No)
{
  INT8U Step;

  if(Area_No >= MAX_AREA_NUM)
  {
    ASSERT_FAILED();
    return Step_Delay[0];
  }

  Step = File_Para[Area_No].Pic_Para.In_Speed; //�����ٶ�
  if(Step >= sizeof(Step_Delay)/sizeof(Step_Delay))
    Step = sizeof(Step_Delay)/sizeof(Step_Delay);

  return Step_Delay[Step];
}

//��ȡ�ļ���ͣ��ʱ��,��λΪms
//ԭ�������Ϊ��ʾ��λ��0Ϊs��1Ϊms
INT32U Get_File_Stay_Time(INT8U Area_No)
{
  if((File_Para[Area_No].Pic_Para.Stay_Time & 0x8000) > 0)
    return (INT32U)(File_Para[Area_No].Pic_Para.Stay_Time & 0x7FFF);
  else
    return (INT32U)File_Para[Area_No].Pic_Para.Stay_Time * 1000;
}

//�����ļ���ͣ��ʱ��
void Set_File_Stay_Time(INT8U Area_No, INT16U ms)
{
  File_Para[Area_No].Pic_Para.Stay_Time = ms;
  File_Para[Area_No].Pic_Para.Stay_Time = File_Para[Area_No].Pic_Para.Stay_Time | 0x80;
}

//ÿ��MOVE_STEP_TIMER ms���øú���,ʵ���ƶ���ʾ��Ч��
void Update_Show_Data()
{
  INT8U i;
  //static S_Int8U Ms10_Timer
  for(i = 0; i < Program_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
    if(File_Para[i].Pic_Para.Flag EQ SHOW_PIC)
      Update_Pic_Data(i);
    else if(File_Para[i].Pic_Para.Flag EQ SHOW_CLOCK)
      Update_Clock_Data(i);
    else if(File_Para[i].Pic_Para.Flag EQ SHOW_TIMER)
      Update_Timer_Data(i);
    else if(File_Para[i].Pic_Para.Flag EQ SHOW_TIME)
      Update_Time_Data(i);
    else if(File_Para[i].Pic_Para.Flag EQ SHOW_TEMP)
      Update_Temp_Data(i);
  }
}

//��ȡһ����ʾ����
//prog��Ŀ��
//area������
INT8S Update_Show_Data_Bak(INT8U Prog_No, INT8U Area_No)
{
  INT8S Re;
  INT8U Seq;
  char File_Name[MAX_FILE_NAME_SIZE];
  FILE_T File;
  INT16U Ctrl_Code;
  INT32S Len, Len0;
  INT32U Dst_Index, Size;
  INT16U X,Y,X_Len,Y_Len;

  Re = AREA_OK;
  //Read_Para();
  Get_Program_Data_File_Name(Prog_No, Area_No, File_Name); //��ȡ�÷�������ʾ�ļ�

  File = File_Open(File_Name, FILE_R); //Read_

  Len = File_Read_One_Frame(File, Area_Status[Area_No].File_Offset, &Seq, &Ctrl_Code, Pub_Buf, Pub_Buf, sizeof(Pub_Buf));
  if(Len EQ FILE_END) //�ļ�����--��ͷ��ʼ����
  {
    Area_Status[Area_No].File_Offset = 0;
    Area_Status[Area_No].File_Type = 0;
    Len = File_Read_One_Frame(File, Area_Status[Area_No].File_Offset, &Seq, &Ctrl_Code, Pub_Buf, Pub_Buf, sizeof(Pub_Buf));
  }

  if(Seq EQ 0)//---�����ǵ�һ֡,�Ƚ���ʾ��ز������Ƶ�File_Para�ṹ����
  {
    Area_Status[Area_No].File_Offset += Len;

    if(Len > (sizeof(S_Pic_Para) - 2)) //��һ֡
    {
      Len0 = 0;

      Dst_Index = Get_Area_Point_Index(Area_No, 0, 0);
      Size = 0;
      Area_Status[Area_No].File_Type = Pub_Buf[0];

      if(Pub_Buf[0] EQ SHOW_PIC) //ͼ��
      {
        Len0 =  sizeof(File_Para[Area_No].Pic_Para) - 2;
        mem_cpy(&File_Para[Area_No].Pic_Para.Flag, Pub_Buf, Len0, &File_Para[Area_No].Pic_Para, sizeof(File_Para[Area_No].Pic_Para));
        X = 0;
        Y = 0;
        X_Len = Program_Para.Area[Area_No].X_Len;
        Y_Len = Program_Para.Area[Area_No].Y_Len;
      }
      else if(Pub_Buf[0] EQ SHOW_CLOCK)//����
      {
        Len0 =  sizeof(File_Para[Area_No].Clock_Para) - 2;
        mem_cpy(&File_Para[Area_No].Clock_Para.Flag, Pub_Buf, Len0, &File_Para[Area_No].Clock_Para, sizeof(File_Para[Area_No].Clock_Para));

        X = File_Para[Area_No].Clock_Para.Text_X;
        Y = File_Para[Area_No].Clock_Para.Text_Y;
        X_Len = File_Para[Area_No].Clock_Para.Text_Width;
        Y_Len = File_Para[Area_No].Clock_Para.Text_Height;
      }
      else if(Pub_Buf[0] EQ SHOW_TIME)//ʱ��
      {
        Len0 =  sizeof(File_Para[Area_No].Time_Para) - 2;
        mem_cpy(&File_Para[Area_No].Time_Para.Flag, Pub_Buf, Len0, &File_Para[Area_No].Time_Para, sizeof(File_Para[Area_No].Time_Para));

        X = File_Para[Area_No].Clock_Para.Text_X;
        Y = File_Para[Area_No].Clock_Para.Text_Y;
        X_Len = File_Para[Area_No].Clock_Para.Text_Width;
        Y_Len = File_Para[Area_No].Clock_Para.Text_Height;
      }
      else if(Pub_Buf[0] EQ SHOW_TIMER)//��ʱ��
      {
        Len0 =  sizeof(File_Para[Area_No].Timer_Para) - 2;
        mem_cpy(&File_Para[Area_No].Timer_Para.Flag, Pub_Buf, Len0, &File_Para[Area_No].Timer_Para, sizeof(File_Para[Area_No].Timer_Para));

        X = File_Para[Area_No].Clock_Para.Text_X;
        Y = File_Para[Area_No].Clock_Para.Text_Y;
        X_Len = File_Para[Area_No].Clock_Para.Text_Width;
        Y_Len = File_Para[Area_No].Clock_Para.Text_Height;
      }
      else if(Pub_Buf[0] EQ SHOW_TEMP)//�¶�
      {
        Len0 =  sizeof(File_Para[Area_No].Temp_Para) - 2;
        mem_cpy(&File_Para[Area_No].Temp_Para.Flag, Pub_Buf, Len0, &File_Para[Area_No].Temp_Para, sizeof(File_Para[Area_No].Temp_Para));

        X = File_Para[Area_No].Clock_Para.Text_X;
        Y = File_Para[Area_No].Clock_Para.Text_Y;
        X_Len = File_Para[Area_No].Clock_Para.Text_Width;
        Y_Len = File_Para[Area_No].Clock_Para.Text_Height;
      }

      //Bits_Copy(Pub_Buf, sizeof(Pub_Buf), 0, (Len - Len0)* 8, Show_Data.Color_Data + Dst_Index, sizeof(Show_Data.Color_Data), Dst_Index);
      Copy_Buf_2_Area_Rect_0(Pub_Buf, Len - Len0, 0, &Show_Data_Bak, Area_No, X, Y, X_Len, Y_Len);
      Dst_Index += (Len - Len0)*8;
      Size += (Len - Len0);
    }
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }

  if((Ctrl_Code & 0x10) == 0x10) //�к���֡
  {
    STOP_SHOW_TIMER_INT; //�ر���ʾ�ж�

    do
    { //��������һ֡
      Len = File_Read_One_Frame(File, Area_Status[Area_No].File_Offset, &Seq, &Ctrl_Code, Pub_Buf, Pub_Buf, sizeof(Pub_Buf)); //��ȡһ֡

      if(Len > 0) //��������һ֡
      {
        if((Size + Len) * 8 > Get_Area_Size(Area_No)) //�����˷����ķ�Χ��
        {
          ASSERT_FAILED();
          break;
        }

        //λ����
        Copy_Buf_2_Area_Rect_0(Pub_Buf, Len - Len0, Size, &Show_Data_Bak, Area_No, X, Y, X_Len, Y_Len);
        //Bits_Copy(Pub_Buf, sizeof(Pub_Buf), 0, Len * 8, Show_Data.Color_Data + Dst_Index, sizeof(Show_Data.Color_Data), Dst_Index);
        Dst_Index += Len*8;
        Size += Len;
        //�޸Ķ��ļ�ƫ��
        Area_Status[Area_No].File_Offset += Len;

        if((Ctrl_Code & 0x10) != 0x10) //û�к���֡���˳�
          break;
      }
      else //������һ��������֡�����ˣ���Ϊ�÷����������ݽ�����
      {
        Area_Status[Area_No].File_Offset = 0;
        Re = AREA_END;
        break;
      }
    }while(1); //��ͬһ������,�к���֡��ʾ---һ����������������һ֡���䣬����̫�����֡

    START_SHOW_TIMER_INT; //����ʾ�ж�
  }

  File_Close(File); //�ر�

  return 1;
}


//��������ʾ����������
INT8S Check_Update_Show_Data_Bak()
{
  INT8U i, Re;
  INT32U Area_End_Flag = 0;
  INT8U All_End_Flag = 1; //��һ������û�н���������0

  for(i = 0; i < Program_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
    //Ŀǰ��ʾ�Ĳ����Ѿ���100%����Ŀǰͣ��ʱ���Ѿ��ﵽ�ļ���ͣ��ʱ�䣬����Ϊ�����Ѿ���ʾ��ϣ��л�������
    if(Get_File_Stay_Time(i) < MIN_STAY_TIME)
      Set_File_Stay_Time(i, MIN_STAY_TIME);

    //Step>=100��ʾ�����ƶ�������ɣ�Stay_Time>=��ʾͣ��ʱ�䵽���������Ϊ��һ������
    if(Area_Status[i].Step >= 100 && Area_Status[i].Stay_Time >= Get_File_Stay_Time(i))
    {
      Re = Update_Show_Data_Bak(Program_Para.Program_No, i);// == FILE_END)
      if(Re EQ AREA_END) //�������
      {
        SET_BIT(Area_End_Flag, i); //��i������Ŀ�������
        if(i + 1 EQ Program_Para.Main_Area_No)
          return PROG_END;
      }
      else
        All_End_Flag = 0; //��һ������û�н���������ñ�־
    }
  }

  if(All_End_Flag EQ 1) //���з�����������
    return PROG_END;
  else
    return PROG_OK;
}



//ÿ��MOVE_STEP_TIMER ms ���øú�����ʵ���ƶ�Ч��
void Show_Timer_Proc()
{
  Update_Show_Data(); //������ʾ����

}




//��ʾ��ش���
void Show_Main_Proc()
{
  //Check_Update_Program_Para(); //����Ƿ���Ҫ���½�Ŀ
  Check_Update_Show_Data_Bak(); //����Ƿ���Ҫ������ʾ����������
  //Check_Update_Show_Data(); //����Ƿ������ʾ������

}


