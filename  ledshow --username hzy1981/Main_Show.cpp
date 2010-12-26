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

  Step = Prog_Status.File_Para[Area_No].Pic_Para.In_Speed; //�����ٶ�
  
  if(Step >= S_NUM(Step_Delay))
    Step = S_NUM(Step_Delay) - 1;

  return Step_Delay[Step];
}

//��ȡ�ļ���ͣ��ʱ��,��λΪms
//ԭ�������Ϊ��ʾ��λ��0Ϊs��1Ϊms
INT32U Get_File_Stay_Time(INT8U Area_No)
{
  if((Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time & 0x8000) > 0)
    return (INT32U)(Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time & 0x7FFF);
  else
    return (INT32U)Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time * 1000;
}

//�����ļ���ͣ��ʱ��
void Set_File_Stay_Time(INT8U Area_No, INT16U ms)
{
  Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time = ms;
  Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time = Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time | 0x80;
  SET_SUM(Prog_Status.File_Para[Area_No].Pic_Para);
}

//ÿ��MOVE_STEP_TIMER ms���øú���,ʵ���ƶ���ʾ��Ч��
void Update_Show_Data()
{
  INT8U i;

  for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
    if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_PIC)
      Update_Pic_Data(i);
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_CLOCK)
      Update_Clock_Data(i);
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_TIMER)
      Update_Timer_Data(i);
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_TIME)
      Update_Time_Data(i);
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_TEMP)
      Update_Temp_Data(i);
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_LUN)
      Update_Lun_Data(i);
  }
  Update_Border_Data(MAX_AREA_NUM); //���±߿�����
}

//��ȡһ����ʾ����
//prog��Ŀ��
//area������
INT8U Update_Show_Data_Bak(INT8U Prog_No, INT8U Area_No)
{
  INT16U Len,SNum;
  
  if(Prog_Status.Area_Status[Area_No].SNum EQ 0) //��һ����ʾ--��ʾ���µ�һ���µ��ļ��ˣ������ض��ļ�����
  {
    //�Ƚ��ļ���������
    Prog_Status.Area_Status[Area_No].File_No ++;
   
    //�ļ���
    if(Prog_Status.Area_Status[Area_No].File_No >= Prog_Para.Area_File_Num[Area_No]) //�����ļ�ȫ����������һ��
    {
      Prog_Status.Area_Status[Area_No].File_No = 0;
      Prog_Status.Area_Status[Area_No].Counts++; //�����ļ���������һ�Σ��򽫲��Ŵ���+1
    }
    
    Len = Read_File_Para(Prog_No, Area_No, Prog_Status.Area_Status[Area_No].File_No, \
                   &Prog_Status.File_Para[Area_No].Pic_Para.Flag, \
                   &Prog_Status.File_Para[Area_No], sizeof(U_File_Para)); 
    if(Len EQ 0)
    {
      ASSERT_FAILED();
      return AREA_END;
    }
  }

  Len = Read_Show_Data(Area_No, \
                 Prog_Status.Area_Status[Area_No].File_No, \
                 Prog_Status.File_Para[Area_No].Pic_Para.Flag,\
                 Prog_Status.Area_Status[Area_No].SNum,\
                 &Show_Data_Bak);

  if(Len EQ 0)
    ASSERT_FAILED();
  
  Prog_Status.Area_Status[Area_No].SNum ++; //��ʾ��������
  
  //SNum��ʾ��ǰ�ļ��ܵ���Ļ����ֻ��ͼ�ĵ���Ļ�������1����
  if(Prog_Status.File_Para[Area_No].Pic_Para.Flag EQ SHOW_PIC)
    SNum = Prog_Status.File_Para[Area_No].Pic_Para.SNum;
  else
    SNum = 1;
  
  if(Prog_Status.Area_Status[Area_No].SNum >= SNum)
    Prog_Status.Area_Status[Area_No].SNum = 0;

    
  return AREA_OK;
}


//��������ʾ����������
INT8U Check_Update_Show_Data_Bak()
{
  INT8U i;
  INT32U Stay_Time;
  
  for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
    Stay_Time = Get_File_Stay_Time(i);
    //Ŀǰ��ʾ�Ĳ����Ѿ���100%����Ŀǰͣ��ʱ���Ѿ��ﵽ�ļ���ͣ��ʱ�䣬����Ϊ�����Ѿ���ʾ��ϣ��л�������
    if(Stay_Time < MIN_STAY_TIME)
      Set_File_Stay_Time(i, MIN_STAY_TIME);

    //Step>=100��ʾ�����ƶ�������ɣ�Stay_Time>=��ʾͣ��ʱ�䵽���������Ϊ��һ������
    if(Prog_Status.Area_Status[i].Step >= 100 &&\
       Prog_Status.Area_Status[i].Stay_Time >= Stay_Time)
    {
      Update_Show_Data_Bak(Prog_Para.Prog_No, i);// == FILE_END)

    }
  }
  return 1;
}

void Clr_Prog_Status()
{
  memset(&Prog_Status, 0, sizeof(Prog_Status));
  SET_HT(Prog_Status);
  
}

INT8U Check_Prog_End()
{
  //����ģʽ
  if(Prog_Para.Mode EQ PROG_COUNTS_MODE)
  {
    if(Prog_Status.Counts >= Prog_Para.Counts)
      return 0;
    else
      return 1;
  }
  else if(Prog_Para.Mode EQ PROG_TIME_MODE)
  {
    if(Prog_Status.Time >= Prog_Para.Time)
      return 0;
    else
      return 1;    
  }
  else
  {
    if(Prog_Status.Counts >= 1)
      return 0;
    else
      return 1;   
  } 
}

INT8U Check_Prog_Play_Time()
{
  
}

//ÿ��MOVE_STEP_TIMER ms ���øú�����ʵ���ƶ�Ч��
void Show_Timer_Proc()
{
  Update_Show_Data(); //������ʾ����

}


void Check_Update_Program_Para()
{
  INT8U Re;
  INT8U i,Count = 0;
  INT16U Len, Min_Counts = 0xFFFF;
  static S_Int8U Sec = {CHK_BYTE, 0xFF, CHK_BYTE};
  static S_Int8U Min = {CHK_BYTE, 0xFF, CHK_BYTE};
  
  if(Sec.Var EQ Cur_Time.Time[T_SEC])
    return;
  
  Sec.Var = Cur_Time.Time[T_SEC];
  
  Re = CHK_HT(Prog_Status);
  if(Re EQ 0)
    ASSERT_FAILED();
  
  if(Prog_Status.Play_Flag EQ 0) //��һ�β��Ÿý�Ŀ�����ȡ��Ŀ����
  {
    while(1) //Ѱ����һ���ɲ��ŵĽ�Ŀ
    {
      Prog_Status.Prog_No ++;
      Count ++;
      
      if(Prog_Status.Prog_No >= Screen_Para.Prog_Num || Prog_Status.Prog_No >= MAX_PROG_NUM)
        Prog_Status.Prog_No = 0;
  
      Len = Read_Prog_Para(Prog_Status.Prog_No); //���¸��½�Ŀ����
      if(Len > 0 && Check_Prog_Play_Time() > 0)
      {
        //��ȡ�ý�Ŀ�Ĵ洢����
        Clr_Prog_Status(); //�����Ŀ״̬
        Read_Prog_Block_Index(Prog_Status.Prog_No);//���¶�ȡ��Ŀ�Ĵ洢����
        break;
      }
      
      //����ѯ����������Screen_Para.Prog_Num��MAX_PROG_NUM��
      if(Count > Screen_Para.Prog_Num || Count > MAX_PROG_NUM)
        break;
    } 
  }
  
  Prog_Status.Play_Flag = 1; //�����Ŀ����״̬
  
  if(Min.Var != Cur_Time.Time[T_MIN]) //ÿ����+1����ǰ��Ŀ�Ĳ���ʱ��
  {
    Min.Var = Cur_Time.Time[T_MIN];
    Prog_Status.Time ++;
  }
 
  
  //��С���Ŵ����ǽ�Ŀ�Ĳ��Ŵ���---����Ҳ�ɲ����������Ĳ��Ŵ���
  for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
    if(Prog_Status.Area_Status[i].Counts < Min_Counts)
      Min_Counts = Prog_Status.Area_Status[i].Counts;
  }
  
  Prog_Status.Counts = Min_Counts; //�����з����ڵ���С���Ŵ������ǽ�Ŀ���ܲ��Ŵ���
  
  
  if(Check_Prog_End() > 0)//>0��ʾ��Ŀ����
  {
    Prog_Status.Time = 0;
    Prog_Status.Counts = 0;
    Prog_Status.Play_Flag = 0; //--��ǰ��Ŀ�������
  }
}


//��ʾ��ش���
void Show_Main_Proc()
{
  Check_Update_Program_Para(); //����Ƿ���Ҫ���½�Ŀ
  Check_Update_Show_Data_Bak(); //����Ƿ���Ҫ������ʾ����������
}


