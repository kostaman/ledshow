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
INT8U Update_XXX_Data_Bak(INT8U Area_No)
{
  INT8U Flag; 
  
  Flag = Prog_Status.File_Para[Area_No].Pic_Para.Flag;
  
  //ĳЩ��ͼ��������Ҫ��ʱˢ��!Ӧ�ñ�֤ÿ���ӽ���һ��
  if(Flag EQ SHOW_PIC)
    ;
#if CLOCK_SHOW_EN  
  else if(Flag EQ SHOW_CLOCK)
    Update_Clock_Data_Bak(Area_No);
#endif
#if TIME_SHOW_EN  
  else if(Flag EQ SHOW_TIME)
    Update_Time_Data_Bak(Area_No);
#endif
#if TIMER_SHOW_EN  
  else if(Flag EQ SHOW_TIMER)
    Update_Timer_Data_Bak(Area_No);
#endif
#if TEMP_SHOW_EN  
  else if(Flag EQ SHOW_TEMP)
    Update_Temp_Data_Bak(Area_No);
#endif
#if LUN_SHOW_EN  
  else if(Flag EQ SHOW_LUN)
    Update_Lun_Data_Bak(Area_No);
#endif  
  //else if(Flag EQ SHOW_FLASH)
    //Update_Flash_Data_Bak(Area_No);
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

//��ȡһ����ʾ����
//prog��Ŀ��
//area������
INT8U Update_Show_Data_Bak(INT8U Prog_No, INT8U Area_No)
{
  INT16U Len,SNum;
  INT8U File_No;
  INT8U Counts;
  
  if(Prog_Status.Area_Status[Area_No].SNum EQ 0) //��һ����ʾ--��ʾ���µ�һ���µ��ļ��ˣ������ض��ļ�����
  {
    //�Ƚ��ļ��������� 
    Prog_Status.Area_Status[Area_No].Play_Flag = 0; //�رձ�������ʾ
    Len = Read_File_Para(Prog_No, Area_No, Prog_Status.Area_Status[Area_No].File_No, \
                   &Prog_Status.File_Para[Area_No].Pic_Para.Flag, \
                   &Prog_Status.File_Para[Area_No], sizeof(U_File_Para)); 
    if(Len EQ 0)
    {
      ASSERT_FAILED();
      
      Prog_Status.Area_Status[Area_No].File_No ++;
      if(Prog_Status.Area_Status[Area_No].File_No >= Prog_Para.Area_File_Num[Area_No] ||\
         Prog_Status.Area_Status[Area_No].File_No >= MAX_FILE_NUM) //�����ļ�ȫ����������һ��
      {
        Prog_Status.Area_Status[Area_No].File_No = 0;
        Prog_Status.Area_Status[Area_No].Counts++; //�����ļ���������һ�Σ��򽫲��Ŵ���+1
      } 
      return 0;
    }

  }

  //������ʾ����
  Prog_Status.Area_Status[Area_No].Play_Flag = 0; //--��ȡ��ʾ���ݹ����н����ű�־��0���Ӷ��жϳ����в�����
  Len = Read_Show_Data(Area_No, \
                 Prog_Status.Area_Status[Area_No].File_No, \
                 Prog_Status.File_Para[Area_No].Pic_Para.Flag,\
                 Prog_Status.Area_Status[Area_No].SNum,\
                 &Show_Data_Bak);
  
  Prog_Status.Area_Status[Area_No].SNum ++; //��ʾ��������
  
  if(Len > 0)
    Prog_Status.Area_Status[Area_No].Play_Flag = 1; //�򿪱�������ʾ
  else
    ASSERT_FAILED();
  
  //SNum��ʾ��ǰ�ļ��ܵ���Ļ����ֻ��ͼ�ĵ���Ļ�������1����
  if(Prog_Status.File_Para[Area_No].Pic_Para.Flag EQ SHOW_PIC)
    SNum = Prog_Status.File_Para[Area_No].Pic_Para.SNum;
  else
    SNum = 1;
  
  
  //���з�������ʾ�����л����¸���ʾ�ļ�
  if(Prog_Status.Area_Status[Area_No].SNum >= SNum)
  {
    Prog_Status.Area_Status[Area_No].Play_Flag = 0; //�رձ�������ʾ
    Prog_Status.Area_Status[Area_No].SNum = 0; 
    
    //�ļ���
    Prog_Status.Area_Status[Area_No].File_No ++;
    if(Prog_Status.Area_Status[Area_No].File_No >= Prog_Para.Area_File_Num[Area_No] ||\
       Prog_Status.Area_Status[Area_No].File_No >= MAX_FILE_NUM) //�����ļ�ȫ����������һ��
    {
      Prog_Status.Area_Status[Area_No].File_No = 0;
      Prog_Status.Area_Status[Area_No].Counts++; //�����ļ���������һ�Σ��򽫲��Ŵ���+1
    }  
  }
  
  
  return AREA_OK;
}


//��������ʾ����������
INT8U Check_Update_Show_Data_Bak()
{
  INT8U i;
  INT32U Stay_Time;
  S_Int8U Sec = {CHK_BYTE, 0xFF, CHK_BYTE};
  
  for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
    Stay_Time = Get_File_Stay_Time(i);
    //Ŀǰ��ʾ�Ĳ����Ѿ���100%����Ŀǰͣ��ʱ���Ѿ��ﵽ�ļ���ͣ��ʱ�䣬����Ϊ�����Ѿ���ʾ��ϣ��л�������
    if(Stay_Time < MIN_STAY_TIME)
      Set_File_Stay_Time(i, MIN_STAY_TIME);

    //Step>=100��ʾ�����ƶ�������ɣ�Stay_Time>=��ʾͣ��ʱ�䵽���������Ϊ��һ������
    if(Prog_Status.Area_Status[i].Step EQ 0 &&\
       Prog_Status.Area_Status[i].Stay_Time EQ 0)
    {   
      Update_Show_Data_Bak(Prog_Para.Prog_No, i);// == FILE_END)
    }
  }
  
  //ÿ�����һ��ʱ�ӡ��¶ȡ���ʱ������
  if(Sec.Var != Cur_Time.Time[T_SEC])
  {
    Sec.Var = Cur_Time.Time[T_SEC];    
    for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
    {    
      Update_XXX_Data_Bak(i);
    }
  }
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
//����0��ʾ�����ˣ�1��ʾ��û�н���
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
  else if(Prog_Para.Mode EQ PROG_TIME_MODE)//ʱ��ģʽ
  {
    if(Prog_Status.Time >= Prog_Para.Time)
      return 0;
    else
      return 1;    
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  } 
}

INT8U Check_Prog_Play_Time()
{
 return 1;
}

//ÿ��MOVE_STEP_TIMER ms ���øú�����ʵ���ƶ�Ч��
void Show_Timer_Proc()
{
  Update_Show_Data(); //������ʾ����

}

INT8U Inc_Prog_No(INT8U Prog_No)
{
  return 1;
}

//����Ƿ���Ҫ���½�Ŀ����
void Check_Update_Program_Para()
{
  INT8U Re;
  INT8U i,Prog_No,Count = 0;
  INT16U Len, Min_Counts = 0xFFFF;
  static S_Int8U Sec = {CHK_BYTE, 0xFF, CHK_BYTE};
  static S_Int8U Min = {CHK_BYTE, 0xFF, CHK_BYTE};
  
  if(Sec.Var EQ Cur_Time.Time[T_SEC])
    return;
  
  Sec.Var = Cur_Time.Time[T_SEC];
  
  Re = CHK_HT(Prog_Status);
  if(Re EQ 0)
    ASSERT_FAILED();
  
  if(Prog_Status.Play_Flag EQ 0) //��δ�����Ŀ����״̬
  {
    while(1) //Ѱ����һ���ɲ��ŵĽ�Ŀ
    {
      Count ++;
      
      if(Prog_Status.Prog_No >= Screen_Para.Prog_Num ||\
         Prog_Status.Prog_No >= MAX_PROG_NUM)
        Prog_Status.Prog_No = 0;
  
      Len = Read_Prog_Para(Prog_Status.Prog_No); //���¸��½�Ŀ����
      if(Len > 0)
      {   
        Len = Read_Prog_Block_Index(Prog_Status.Prog_No);//���¶�ȡ��Ŀ�Ĵ洢����
        if(Len > 0)
        {       
          Prog_Status.Play_Flag = 1; //���벥��״̬��
          break;
        }
      }
      
      Prog_Status.Prog_No ++; //��û�ж�����Ŀ����������£���ȡ��һ����Ŀ�Ĳ���
      //����ѯ����������Screen_Para.Prog_Num��MAX_PROG_NUM��
      if(Count > Screen_Para.Prog_Num || Count > MAX_PROG_NUM)
        break;
    } 
  }
  
  if(Prog_Status.Play_Flag > 0)//--��ǰ�ڽ�Ŀ����״̬
  {
    if(Min.Var != Cur_Time.Time[T_MIN]) //ÿ����+1����ǰ��Ŀ�Ĳ���ʱ��
    {
      Min.Var = Cur_Time.Time[T_MIN];
      Prog_Status.Time ++;
    }
   
    
    //��С���Ŵ����ǽ�Ŀ�Ĳ��Ŵ���---����Ҳ�ɲ����������Ĳ��Ŵ���
    Min_Counts = 0xFFFF;
    for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
    {
      if(Prog_Status.Area_Status[i].Counts < Min_Counts)
        Min_Counts = Prog_Status.Area_Status[i].Counts;
    }
    
    Prog_Status.Counts = Min_Counts; //�����з����ڵ���С���Ŵ������ǽ�Ŀ���ܲ��Ŵ���
    
    if(Check_Prog_End() > 0)//>0��ʾ��Ŀ����
    {
      //��ȡ�ý�Ŀ�Ĵ洢����
      Prog_Status.Play_Flag = 0;
      Prog_No = Prog_Status.Prog_No;
      Clr_Prog_Status(); //�����Ŀ״̬--�����¸���Ŀ
      Prog_Status.Prog_No = Prog_No + 1;

      //��Ŀѭ������
      if(Prog_Status.Prog_No >= Screen_Para.Prog_Num ||\
         Prog_Status.Prog_No >= MAX_PROG_NUM)
        Prog_Status.Prog_No = 0;
    }
  }
}

//��鵱ǰ�Ƿ�����������ʱ�Σ����ܿ����˶�ʱ���ػ�
INT8U Check_Screen_Play_Time()
{
  
  
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
    else
      Re = 0;
    
    if(Re EQ 0)
      ASSERT_FAILED();
    
  }
  
}

//���ڴ��еı�����ʼ��ͷβ
void Ram_Init()
{
  SET_HT(Screen_Para);  
  SET_HT(Card_Para);
  SET_HT(Prog_Para);
  SET_HT(Prog_Status);
  SET_HT(Cur_Block_Index);
  SET_HT(Show_Data);
  SET_HT(Show_Data_Bak);
  SET_HT(Cur_Time);  
}

//��ʾ��ش���
void Show_Main_Proc()
{
  Screen_Proc();
  if(Get_Screen_Open_Status() > 0) //��ǰ�ڿ���״̬�Ž���
  {
    Check_Update_Program_Para(); //����Ƿ���Ҫ���½�Ŀ
    Check_Update_Show_Data_Bak(); //����Ƿ���Ҫ������ʾ����������
  }
}


