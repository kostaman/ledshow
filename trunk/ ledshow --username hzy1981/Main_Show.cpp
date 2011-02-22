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
INT32U Get_Area_In_Step_Delay(INT8U Area_No)
{
  return CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.In_Time);///(100/MOVE_STEP);
}

//��ȡĳ����������ĳ��������ͣ��ʱ��
INT32U Get_Area_Out_Step_Delay(INT8U Area_No)
{
  return CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.Out_Time);///(100/MOVE_STEP);
}

//��ȡ�ļ�����ʱ��
INT32U Get_File_In_Time(INT8U Area_No)
{
 return CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.In_Time);
  
}

//��ȡ�ļ���ͣ��ʱ��,��λΪms
//ԭ�������Ϊ��ʾ��λ��0Ϊs��1Ϊms
INT32U Get_File_Stay_Time(INT8U Area_No)
{
  return CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time);
}

//��ȡ�ļ�����ʱ��
INT32U Get_File_Out_Time(INT8U Area_No)
{
  return CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.Out_Time);  
}

//�����ļ���ͣ��ʱ��
void Set_File_Stay_Time(INT8U Area_No, INT16U ms)
{
  Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time = ms;
  Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time = Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time | 0x8000;
  SET_SUM(Prog_Status.File_Para[Area_No].Pic_Para);
}

//ÿ��MOVE_STEP_TIMER ms���øú���,ʵ���ƶ���ʾ��Ч��
void Update_Show_Data()
{
  INT8U i;

  if(Screen_Status.Open_Flag EQ 0) //��ǰ�ڹػ�״̬
    return;
  
  for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
//#if PIC_SHOW_EN    
    //if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_PIC)
      Update_Pic_Data(i);
//#endif
/*
#if CLOCK_SHOW_EN
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_CLOCK)
      Update_Clock_Data(i);
#endif
      */
    /*
#if TIMER_SHOW_EN
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_TIMER)
      Update_Timer_Data(i);
#endif
      */
    /*
#if TIME_SHOW_EN
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_TIME)
      Update_Time_Data(i);
#endif
      */
    /*
#if TEMP_SHOW_EN
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_TEMP)
      Update_Temp_Data(i);
#endif
      */
    /*
#if LUN_SHOW_EN
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_LUN)
      Update_Lun_Data(i);
#endif
      */
  }
#if BORDER_SHOW_EN
  Update_Border_Data(MAX_AREA_NUM); //���±߿�����
#endif  
}

//������ʾ���������ݡ���ʾ�ǹ̶��ı�����Ϣ
INT8U Update_XXX_Data(S_Show_Data *pDst, INT8U Area_No)
{
  INT8U Flag; 
  
  Flag = Prog_Status.File_Para[Area_No].Pic_Para.Flag;
  
  //ĳЩ��ͼ��������Ҫ��ʱˢ��!Ӧ�ñ�֤ÿ���ӽ���һ��
  if(Flag EQ SHOW_PIC)
    ;
#if CLOCK_SHOW_EN  
  else if(Flag EQ SHOW_CLOCK)
    Update_Clock_Data(pDst, Area_No);
#endif
#if TIME_SHOW_EN  
  else if(Flag EQ SHOW_TIME)
    Update_Time_Data(pDst, Area_No);
#endif
#if TIMER_SHOW_EN  
  else if(Flag EQ SHOW_TIMER)
    Update_Timer_Data(pDst, Area_No);
#endif
#if TEMP_SHOW_EN  
  else if(Flag EQ SHOW_TEMP)
    Update_Temp_Data(pDst, Area_No);
#endif
#if LUN_SHOW_EN  
  else if(Flag EQ SHOW_LUN)
    Update_Lun_Data(pDst, Area_No);
#endif
#if HUMIDITY_SHOW_EN
  else if(Flag EQ SHOW_HUMIDITY)
    Update_Humidity_Data(pDst, Area_No);
#endif
#if NOISE_SHOW_EN
  else if(Flag EQ SHOW_NOISE)
    Update_Noise_Data(pDst, Area_No);
#endif
  else
    ASSERT_FAILED(); 
  
  return 1;
}

//���ĳ��������״̬
void Clr_Area_Status(INT8U Area_No)
{
  if(Area_No >= MAX_AREA_NUM)
  {
    ASSERT_FAILED();
    return;
  }
  
  memset(&Prog_Status.Area_Status[Area_No], 0, sizeof(Prog_Status.Area_Status[Area_No])); 
  SET_HT(Prog_Status.Area_Status[Area_No]);
}

void Clr_All_Area_Status()
{
    INT8U i;

    for(i = 0; i < MAX_AREA_NUM; i++)
    {
        Clr_Area_Status(i);
    }
}

void Clr_Show_Data()
{
  memset(Show_Data.Color_Data, 0, sizeof(Show_Data.Color_Data));
  memset(Show_Data_Bak.Color_Data, 0, sizeof(Show_Data_Bak.Color_Data));
}

//��ȡһ����ʾ����
//prog��Ŀ��
//area������
INT8U Update_Show_Data_Bak(INT8U Prog_No, INT8U Area_No)
{
  INT16U Len,SNum;
  INT16S Len0;
  INT16U X,Y,Width,Height;
  //INT8U File_No;
  //INT8U Counts;
  //���з�������ʾ�����л����¸���ʾ�ļ�
  if(Prog_Status.New_Prog_Flag) //�ڽ�Ŀ����״̬�У��������ļ�����
      return 0;

  if(Prog_Para.Area_File_Num[Area_No] EQ 0)
      return 0;

  if(Prog_Status.Area_Status[Area_No].New_File_Flag EQ 0 &&\
     Prog_Status.Area_Status[Area_No].New_SCN_Flag EQ 0)
  {
      if(Prog_Status.Area_Status[Area_No].SNum >= Prog_Status.File_Para[Area_No].Pic_Para.SNum)
      {
          Prog_Status.Area_Status[Area_No].New_File_Flag = NEW_FLAG;
          Prog_Status.Area_Status[Area_No].File_No ++;
      }
  }

  //����Ƿ���Ҫ���µ���һ�ļ�
  if(Prog_Status.Area_Status[Area_No].New_File_Flag)//SNum > Prog_Status.File_Para[Area_No].Pic_Para.SNum)
  {

    //debug("prog %d area %d file %d play end!", Prog_Status.Prog_No, Area_No, Prog_Status.Area_Status[Area_No].File_No);

    Prog_Status.Area_Status[Area_No].SNum = 0;
    //�ļ�������ȡʧ�����л����¸��ļ�

    if(Prog_Status.Area_Status[Area_No].File_No >= Prog_Para.Area_File_Num[Area_No] ||\
       Prog_Status.Area_Status[Area_No].File_No >= MAX_FILE_NUM) //�����ļ�ȫ����������һ��
    {
      Prog_Status.Area_Status[Area_No].File_No = 0;
      Prog_Status.Area_Status[Area_No].Counts++; //�����ļ���������һ�Σ��򽫲��Ŵ���+1

      Check_Prog_Play_Counts();
      if(Check_Prog_End() > 0) //��Ŀ�����ˣ�
      {
         Prog_Status.New_Prog_Flag = NEW_FLAG;
         Prog_Status.Prog_No ++;
         return 0;
      }
   }

    debug("\r\nprog %d area %d play new file: %d", Prog_No, Area_No, Prog_Status.Area_Status[Area_No].File_No);
    //�Ƚ��ļ��������� 
    Prog_Status.Area_Status[Area_No].Play_Flag = 0; //�رձ�������ʾ

    Len = 0;
#if DATA_PREP_EN
    if(Prep_Data.Para_Prog_No[Area_No] EQ Prog_Status.Prog_No &&\
       Prep_Data.Para_File_No[Area_No] EQ Prog_Status.Area_Status[Area_No].File_No &&\
       Prep_Data.File_Para_Ok_Flag[Area_No] EQ DATA_OK)
    {
        memcpy(&Prog_Status.File_Para[Area_No], &Prep_Data.File_Para[Area_No], sizeof(U_File_Para));
        Len = 1;
    }
    else
        Len = Read_File_Para(Prog_No, Area_No, Prog_Status.Area_Status[Area_No].File_No, \
                       &Prog_Status.File_Para[Area_No].Pic_Para.Flag, \
                       &Prog_Status.File_Para[Area_No], sizeof(U_File_Para));

    Prep_Data.File_Para_Read_Flag[Area_No] = DATA_READ;
#else
    Len = Read_File_Para(Prog_No, Area_No, Prog_Status.Area_Status[Area_No].File_No, \
                   &Prog_Status.File_Para[Area_No].Pic_Para.Flag, \
                   &Prog_Status.File_Para[Area_No], sizeof(U_File_Para)); 
#endif

    if(Len EQ 0)
    {
      ASSERT_FAILED();
      Prog_Status.Area_Status[Area_No].New_File_Flag = NEW_FLAG;
      Prog_Status.Area_Status[Area_No].File_No ++;

     // return 0;
    }
    else
    {
      Prog_Status.Area_Status[Area_No].New_File_Flag = 0;
      Prog_Status.Area_Status[Area_No].New_SCN_Flag = NEW_FLAG;
      Prog_Status.Area_Status[Area_No].SNum = 0;
    }
  }

  //�����ļ����������в����·�������
  if(Prog_Status.Area_Status[Area_No].New_File_Flag)// EQ 0 &&
    return 0;

  //�������ݵ��µ�һ��
  if(Prog_Status.Area_Status[Area_No].New_SCN_Flag)
  {
      //�Ѿ���������һĻ���л����¸��ļ�
      if(Prog_Status.Area_Status[Area_No].SNum >= Prog_Status.File_Para[Area_No].Pic_Para.SNum)
      {
          Prog_Status.Area_Status[Area_No].New_File_Flag = NEW_FLAG;
          Prog_Status.Area_Status[Area_No].File_No ++;
          return 0;
      }

      //������ʾ����
      Prog_Status.Area_Status[Area_No].Play_Flag = 0; //--��ȡ��ʾ���ݹ����н����ű�־��0���Ӷ��жϳ����в�����

      debug("\r\nread prog %d area %d, file %d %dth screen show data", \
            Prog_No, Area_No, Prog_Status.Area_Status[Area_No].File_No,Prog_Status.Area_Status[Area_No].SNum);

      Clear_Area_Data(&Show_Data_Bak, Area_No);

      Len0 = -1;
#if DATA_PREP_EN > 0      
      if(Prep_Data.Data_Prog_No[Area_No] EQ Prog_Status.Prog_No &&\
         Prep_Data.Data_File_No[Area_No] EQ Prog_Status.Area_Status[Area_No].File_No &&\
         Prep_Data.Data_Ok_Flag[Area_No] EQ DATA_OK &&\
         Prep_Data.Data_SNum[Area_No] EQ Prog_Status.Area_Status[Area_No].SNum)
      {

        S_Point P0;
        debug("use prepaid data: area_no:%d, snum:%d", Area_No, Prep_Data.Data_SNum[Area_No]);
        P0.X = Prep_Data.Data_X[Area_No];
        P0.Y = Prep_Data.Data_Y[Area_No];
        Copy_Filled_Rect(&Prep_Data.Show_Data, \
                         Area_No,\
                         &P0,\
                         Prep_Data.Data_Width[Area_No],\
                         Prep_Data.Data_Height[Area_No],\
                         &Show_Data_Bak,\
                         &P0);
        
        Len0 = 1;//GET_TEXT_LEN(Prep_Data.Data_Width[Area_No]
      }
      else
          Len0 = Read_Show_Data(Area_No, \
                         Prog_Status.Area_Status[Area_No].File_No, \
                         &Prog_Status.File_Para[Area_No],\
                         Prog_Status.Area_Status[Area_No].SNum,\
                         &Show_Data_Bak,&X,&Y,&Width,&Height);

      Prep_Data.Data_Read_Flag[Area_No] = DATA_READ;
#else      
      Len0 = Read_Show_Data(Area_No, \
                     Prog_Status.Area_Status[Area_No].File_No, \
                     &Prog_Status.File_Para[Area_No],\ 
                     Prog_Status.Area_Status[Area_No].SNum,\
                     &Show_Data_Bak,&X,&Y,&Width,&Height);
#endif
      if(Len0 >= 0)
      {
        Prog_Status.Area_Status[Area_No].Play_Flag = 1; //�򿪱�������ʾ
        Prog_Status.Area_Status[Area_No].New_SCN_Flag = 0;
      }
      else
      {
        //������ʾ����û�ж��������������

        ASSERT_FAILED();
        Prog_Status.Area_Status[Area_No].New_SCN_Flag = NEW_FLAG;
        Prog_Status.Area_Status[Area_No].SNum ++; //��ʾ��������
      }
  }


//-----------------
  return AREA_OK;
}


//��������ʾ����������
INT8U Check_Update_Show_Data_Bak()
{
  INT8U i;
  INT32U Stay_Time;
  S_Int8U Sec = {CHK_BYTE, 0xFF, CHK_BYTE};
  
  //if(Prog_Status.Play_Flag EQ 0)
      //return 0;

  for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
      /*
    Stay_Time = Get_File_Stay_Time(i);
    //Ŀǰ��ʾ�Ĳ����Ѿ���100%����Ŀǰͣ��ʱ���Ѿ��ﵽ�ļ���ͣ��ʱ�䣬����Ϊ�����Ѿ���ʾ��ϣ��л�������
    if(Stay_Time < MIN_STAY_TIME)
      Set_File_Stay_Time(i, MIN_STAY_TIME);
*/
    //Step>=100��ʾ�����ƶ�������ɣ�Stay_Time>=��ʾͣ��ʱ�䵽���������Ϊ��һ������
    /*
      if(Prog_Status.Area_Status[i].Play_Flag EQ 0 &&\
       Prog_Status.Area_Status[i].Step EQ 0 &&\
       Prog_Status.Area_Status[i].Stay_Time EQ 0)
    */
     if(Prog_Status.Area_Status[i].New_File_Flag ||\
        Prog_Status.Area_Status[i].New_SCN_Flag)
     {
      Update_Show_Data_Bak(Prog_Para.Prog_No, i);// == FILE_END)
    }
  }
 /*
  //ÿ�����һ��ʱ�ӡ��¶ȡ���ʱ������
  if(Sec.Var != Cur_Time.Time[T_SEC])
  {
    Sec.Var = Cur_Time.Time[T_SEC];    
    for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
    {    
      Update_XXX_Data_Bak(i);
    }
  }
  */
  return 1;
}

void Check_Update_Show_Data()
{
  
}

void Clr_Prog_Status()
{
  memset(&Prog_Status, 0, sizeof(Prog_Status));
  SET_HT(Prog_Status);
  
}

//����Ŀ�Ƿ񲥷Ž���
//����1��ʾ�����ˣ�0��ʾ��û�н���
INT8U Check_Prog_End()
{
  if(Check_Prog_Play_Time() EQ 0)
  {
     debug("prog %d now not play time, end", Prog_Status.Prog_No);
     return 1;
  }
  //����ģʽ
  if(Prog_Para.Mode EQ PROG_COUNTS_MODE)
  {
    if(Prog_Status.Counts >= Prog_Para.Counts)
    {
      debug("prog %d play counts %d, end", Prog_Status.Prog_No, Prog_Status.Counts);      
      return 1;
    }
    else
      return 0;
  }
  else if(Prog_Para.Mode EQ PROG_TIME_MODE)//ʱ��ģʽ
  {
    if(Prog_Status.Time >= Prog_Para.Time)
    {
      debug("prog %d play times %d, end", Prog_Status.Prog_No, Prog_Status.Time);      
      return 1;
    }
    else
      return 0;
  }
  else
  {
    ASSERT_FAILED();
    return 1;
  } 
}

//��ʱ��Ϣ�У����ڵĵ�0λ��ʾ����1����6λ��ʾ������
//��鵱ǰʱ���Ƿ��ڽ�Ŀ��������ʱ���ڣ����򷵻�1�����򷵻�0
INT8U Check_Prog_Play_Time()
{
  //INT8U i;//Re = 1;
  INT8U Temp[20];
  memset(Temp, 0xFF, sizeof(Temp));

  //�����ڶ�ʱ
  if(Prog_Para.Timing[0].Week_Check > 0)
  {
    if(GET_BIT(Prog_Para.Timing[0].Week_Flag, Cur_Time.Time[T_WEEK]) EQ 0)
      return 0;
  }


  //�����ڶ�ʱ
  if(Prog_Para.Timing[0].Date_Check > 0)
  {
    if(!(Cur_Time.Time[T_YEAR] >= Prog_Para.Timing[0].Start_Date[0] &&\
        Cur_Time.Time[T_YEAR] <= Prog_Para.Timing[0].End_Date[0] &&\
        Cur_Time.Time[T_MONTH] >= Prog_Para.Timing[0].Start_Date[1] &&\
        Cur_Time.Time[T_MONTH] <= Prog_Para.Timing[0].End_Date[1] &&\
        Cur_Time.Time[T_DATE] >= Prog_Para.Timing[0].Start_Date[2] &&\
        Cur_Time.Time[T_DATE] <= Prog_Para.Timing[0].End_Date[2]))
      return 0;

  }

  //��ʱ�䶨ʱ
  if(Prog_Para.Timing[0].Time_Check > 0)
  {
    if(!(Cur_Time.Time[T_HOUR] >= Prog_Para.Timing[0].Start_Time[0] &&\
        Cur_Time.Time[T_HOUR] <= Prog_Para.Timing[0].End_Time[0] &&\
        Cur_Time.Time[T_MIN] >= Prog_Para.Timing[0].Start_Time[1] &&\
        Cur_Time.Time[T_MIN] <= Prog_Para.Timing[0].End_Time[1]))
      return 0;

  }

  return 1;
}
/*
INT8U Check_Prog_Play_Time()
{
 return 1;
}
*/
//ÿ��MOVE_STEP_TIMER ms ���øú�����ʵ���ƶ�Ч��
void Show_Timer_Proc()
{
  Update_Show_Data(); //������ʾ����

}

INT8U Inc_Prog_No(INT8U Prog_No)
{
  return 1;
}

void Check_Prog_Play_Counts()
{
    INT16U Min_Counts = 0xFFFF;
    INT8U i;

    //��С���Ŵ����ǽ�Ŀ�Ĳ��Ŵ���---����Ҳ�ɲ����������Ĳ��Ŵ���
    Min_Counts = 0xFFFF;
    for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
    {
      if(Prog_Status.Area_Status[i].Counts < Min_Counts)
        Min_Counts = Prog_Status.Area_Status[i].Counts;
    }

    Prog_Status.Counts = Min_Counts; //�����з����ڵ���С���Ŵ������ǽ�Ŀ���ܲ��Ŵ���

}
//����Ƿ���Ҫ���½�Ŀ����
void Check_Update_Program_Para()
{
  INT8U Re;
  INT8U i,Prog_No,Count = 0;
  INT16U Len;
  static S_Int8U Sec = {CHK_BYTE, 0xFF, CHK_BYTE};
  static S_Int8U Min = {CHK_BYTE, 0xFF, CHK_BYTE};
  
  //if(Sec.Var EQ Cur_Time.Time[T_SEC])
    //return;
  
  //Sec.Var = Cur_Time.Time[T_SEC];
  
  Re = CHK_HT(Prog_Status);
  if(Re EQ 0)
    ASSERT_FAILED();
  
  if(Prog_Status.New_Prog_Flag EQ 0)//--��ǰ�ڽ�Ŀ����״̬
  {
    if(Min.Var != Cur_Time.Time[T_MIN]) //ÿ����+1����ǰ��Ŀ�Ĳ���ʱ��
    {
      Min.Var = Cur_Time.Time[T_MIN];
      Prog_Status.Time ++;
    }
   
    
    //debug("check prog end! counts = %d", Min_Counts);
    if(Check_Prog_End() > 0)//==0��ʾ��Ŀ����
    {
      //��ȡ�ý�Ŀ�Ĵ洢����
      Prog_Status.Play_Flag = 0;
      Prog_No = Prog_Status.Prog_No;

      Prog_Status.New_Prog_Flag = NEW_FLAG;
      Clr_Prog_Status(); //�����Ŀ״̬--�����¸���Ŀ

      Prog_Status.Prog_No = Prog_No ++;

    }
  }

  //if(Prog_Status.Play_Flag EQ 0) //��δ�����Ŀ����״̬
  //{
    if(Prog_Status.New_Prog_Flag)//while(1) //Ѱ����һ���ɲ��ŵĽ�Ŀ
    {

      //Prog_Status.Play_Flag = 0;

      //
      if(Prog_Status.Prog_No >= Screen_Para.Prog_Num ||\
         Prog_Status.Prog_No >= MAX_PROG_NUM)
        Prog_Status.Prog_No = 0;
#if QT_EN
      Prog_Status.Prog_No = Preview_Prog_No;
#endif

      debug("\r\n-----update new prog %d para-----\r\n", Prog_Status.Prog_No);

      Len = Read_Prog_Para(Prog_Status.Prog_No, &Prog_Para); //���¸��½�Ŀ����
      
      if(Len > 0 && Check_Prog_Play_Time() > 0)
      {
        Prog_No = Prog_Status.Prog_No;
        Clr_Prog_Status();
        Prog_Status.Prog_No = Prog_No;
        
        Len = Read_Prog_Block_Index(Prog_Status.Prog_No);//���¶�ȡ��Ŀ�Ĵ洢����
        
        if(Len > 0)
        {
          Clr_Show_Data();

          Prog_Status.New_Prog_Flag = 0;

          for(i = 0; i < MAX_AREA_NUM; i ++)
          {
            Prog_Status.Area_Status[i].New_File_Flag = NEW_FLAG;
            Prog_Status.Area_Status[i].File_No = 0;

          }
        }
      }
      else
      {
        Prog_Status.New_Prog_Flag = NEW_FLAG;
        Prog_Status.Prog_No ++;

        ASSERT_FAILED();
        if(Len EQ 0)
          debug("read prog para failed");
        else
          debug("prog %d now not play time", Prog_Status.Prog_No);
      }

      //Prog_Status.Prog_No ++; //��û�ж�����Ŀ����������£���ȡ��һ����Ŀ�Ĳ���
      //����ѯ����������Screen_Para.Prog_Num��MAX_PROG_NUM��
      //if(Count > Screen_Para.Prog_Num || Count > MAX_PROG_NUM)
        //break;
    }
  //}
}

//����Ƿ����Ԥ׼������
void Check_Update_Data_Prep()
{
  INT8U Prog_No,File_Flag;
  INT8U File_No, Prog_End_Flag;
  INT16U SNum,Len;
  INT16U Counts,i,j,X,Y,Width,Height;
  

  if(Prog_Status.New_Prog_Flag)
    return;
  
  //׼��ÿ�������Ĳ���������
  for(i =0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
    if(Prog_Status.Area_Status[i].New_File_Flag ||\
       Prog_Status.Area_Status[i].New_SCN_Flag)
      return;
    
    //��ȡ��һ������
    if(Prep_Data.Data_Read_Flag[i] EQ DATA_READ) //��Ҫ��ȡ��һ���Ĳ���
    {
      Prep_Data.Data_Read_Flag[i] = 0;
      SNum = Prog_Status.Area_Status[i].SNum + 1; //��һ������

      Prog_No = Prog_Status.Prog_No;
      File_No = Prog_Status.Area_Status[i].File_No;
            
      if(SNum >= Prog_Status.File_Para[i].Pic_Para.SNum) //��ȡ�¸��ļ�
      {
        SNum = 0;
        File_No ++; 
        if(File_No >= Prog_Para.Area_File_Num[i])
          File_No = 0;

        //���¶�ȡ�ļ�����
        if(Prep_Data.File_Para_Read_Flag[i] EQ DATA_READ)
        {
          debug("\r\nprepaid prog %d, area %d,file %d para", Prog_No, i, File_No);
          
          Prep_Data.File_Para_Read_Flag[i] = 0;

          if(Prep_Data.File_Para_Ok_Flag[i] != DATA_OK ||\
             Prep_Data.Para_Prog_No[i] != Prog_No ||\
             Prep_Data.Para_File_No[i] != File_No)
          {
              Len = Read_File_Para(Prog_No, i, File_No, \
                 &Prep_Data.File_Para[i].Pic_Para.Flag, &Prep_Data.File_Para[i], sizeof(Prep_Data.File_Para[i]));

              Prep_Data.Para_Prog_No[i] = Prog_No;
              Prep_Data.Para_File_No[i] = File_No;
              Prep_Data.File_Para_Ok_Flag[i] = (Len >0)?DATA_OK:DATA_ERR;

              if(Len EQ 0)
                return;

              debug("\r\nprepaid prog %d, area %d, file %d, scn %d data",Prog_No, i, File_No, SNum);

              if(Prep_Data.Data_Ok_Flag[i] != DATA_OK ||\
                 Prep_Data.Data_Prog_No[i] != Prog_No ||\
                 Prep_Data.Data_SNum[i] != SNum)
              {
                  Len = Read_Show_Data(i, \
                               File_No, \
                               &Prep_Data.File_Para[i],\
                               SNum,\
                               &Prep_Data.Show_Data,&X,&Y,&Width,&Height);

                  Prep_Data.Data_Prog_No[i] = Prog_No;
                  Prep_Data.Data_File_No[i] = File_No;
                  Prep_Data.Data_SNum[i] = SNum;
                  Prep_Data.Data_X[i] = X;
                  Prep_Data.Data_Y[i] = Y;
                  Prep_Data.Data_Width[i] = Width;
                  Prep_Data.Data_Height[i] = Height;
                  Prep_Data.Data_Ok_Flag[i] = (Len > 0)?DATA_OK:DATA_ERR;
             }
              return;
          }
        }
      }

      debug("\r\nprepaid prog %d, file %d, area %d, scn %d data",Prog_No, i, File_No, SNum);

      if(Prep_Data.Data_Ok_Flag[i] != DATA_OK ||\
         Prep_Data.Data_Prog_No[i] != Prog_No ||\
         Prep_Data.Data_SNum[i] != SNum)
      {
          Len = Read_Show_Data(i, \
                       File_No, \
                       &Prog_Status.File_Para[i],\
                       SNum,\
                       &Prep_Data.Show_Data, &X, &Y, &Width, &Height);

         Prep_Data.Data_Prog_No[i] = Prog_No;
         Prep_Data.Data_File_No[i] = File_No;
         Prep_Data.Data_SNum[i] = SNum;
         Prep_Data.Data_X[i] = X;
         Prep_Data.Data_Y[i] = Y;
         Prep_Data.Data_Width[i] = Width;
         Prep_Data.Data_Height[i] = Height;
         Prep_Data.Data_Ok_Flag[i] = (Len > 0)?DATA_OK:DATA_ERR;
     }
      
    }
  }  
  
}

//����ڴ��е����ݻ��߲����Ƿ���ȷ
void Check_Show_Data_Para()
{
  INT8U i, Re = 1;
  INT8U Flag;

  Re &= CHK_HT(Screen_Para);
  Re &= CHK_HT(Card_Para);  
  Re &= CHK_HT(Prog_Para);
  Re &= CHK_HT(Prog_Status);
  Re &= CHK_HT(Cur_Block_Index);
  Re &= CHK_HT(Show_Data);
  Re &= CHK_HT(Show_Data_Bak);
  Re &= CHK_HT(Cur_Time);
  if(Re EQ 0)
    ASSERT_FAILED();
  
  Re = 1;
  for(i = 0; i < S_NUM(Prog_Status.Area_Status); i ++)
  {
    Re &= CHK_HT(Prog_Status.Area_Status[i]);
    if(Re EQ 0)
      ASSERT_FAILED();
    
    Flag = Prog_Status.File_Para[i].Pic_Para.Flag;
    if(Flag EQ SHOW_NULL)
      ;
    else if(Flag EQ SHOW_PIC)
      Re &= CHK_HT(Prog_Status.File_Para[i].Pic_Para);
#if CLOCK_SHOW_EN    
    else if(Flag EQ SHOW_CLOCK)
      Re &= CHK_HT(Prog_Status.File_Para[i].Clock_Para);
#endif
#if TIME_SHOW_EN    
    else if(Flag EQ SHOW_TIME)
      Re &= CHK_HT(Prog_Status.File_Para[i].Time_Para);
#endif
#if TIMER_SHOW_EN    
    else if(Flag EQ SHOW_TIMER)
      Re &= CHK_HT(Prog_Status.File_Para[i].Timer_Para);
#endif
#if TEMP_SHOW_EN    
    else if(Flag EQ SHOW_TEMP)
      Re &= CHK_HT(Prog_Status.File_Para[i].Temp_Para);
#endif
#if LUN_SHOW_EN    
    else if(Flag EQ SHOW_LUN)
      Re &= CHK_HT(Prog_Status.File_Para[i].Lun_Para);
#endif
#if HUMIDITY_SHOW_EN
    else if(Flag EQ SHOW_HUMIDITY)
      Re &= CHK_HT(Prog_Status.File_Para[i].Humidity_Para);
#endif
#if NOISE_SHOW_EN
    else if(Flag EQ SHOW_NOISE)
      Re &= CHK_HT(Prog_Status.File_Para[i].Noise_Para);
#endif
    else
      Re = 0;
    
    if(Re EQ 0)
      ASSERT_FAILED();
    
  }
  
}

//���ڴ��еı�����ʼ��ͷβ
void Ram_Init()
{
  memset(&Screen_Para, 0, sizeof(Screen_Para));
  //memset(&Card_Para, 0, sizeof(Card_Para));
  memset(&Prog_Para, 0, sizeof(Prog_Para));
  memset(&Screen_Status, 0, sizeof(Screen_Status));
  memset(&Prog_Status, 0, sizeof(Prog_Status));
  memset(&Prep_Data, 0, sizeof(Prep_Data));
  memset(&Show_Data, 0, sizeof(Show_Data));
  memset(&Show_Data_Bak, 0, sizeof(Show_Data_Bak));
  memset(&Cur_Block_Index, 0, sizeof(Cur_Block_Index));
  memset(&Cur_Time, 0, sizeof(Cur_Time));

  SET_HT(Screen_Para);  
  //SET_HT(Card_Para);
  SET_HT(Prog_Para);
  SET_HT(Screen_Status);
  SET_HT(Prog_Status);
  SET_HT(Prep_Data);
  SET_HT(Cur_Block_Index);
  SET_HT(Show_Data);
  SET_HT(Show_Data_Bak);
  SET_HT(Cur_Block_Index);
  SET_HT(Cur_Time);

  Prog_Status.New_Prog_Flag = NEW_FLAG;
}

//��ʾ��ش���
void Show_Main_Proc()
{
  Screen_Proc();
  if(Get_Screen_Open_Status() > 0) //��ǰ�ڿ���״̬�Ž���
  {
    Check_Update_Program_Para(); //����Ƿ���Ҫ���½�Ŀ
    Check_Update_Show_Data_Bak(); //����Ƿ���Ҫ������ʾ����������
    Check_Update_Data_Prep();
  }
}

//��ʾ��ʼ��
void Show_Init()
{
  Ram_Init();
  Read_Screen_Para();
}
