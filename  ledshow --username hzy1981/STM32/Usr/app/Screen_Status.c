#define SCREEN_STATUS_C
#include "Includes.h"

#if QT_EN EQ 0
//��ȡ��ǰ�¶�
INT16S Get_Cur_Temp(void)
{
  return Screen_Status.Temp; 
}

//��ȡ��ǰʪ��
INT16U Get_Cur_Humidity(void)
{
  return Screen_Status.Humidity; 
}

//��ȡ��ǰ����
INT16U Get_Cur_Noise(void)
{
  return Screen_Status.Noise;
}
#endif

//������������
void Screen_Env_Proc()
{
#if ENV_VAR_EN
  static S_Int32U Sec = {CHK_BYTE, 0xFFFFFFFF, CHK_BYTE};
  static S_Int32U Counts = {CHK_BYTE, 0x00, CHK_BYTE};

  //���յ����ݴﵽһ֡����
  if(Screen_Status.Env_Rcv_Posi >= 3 + F_NDATA_LEN)
  {
    Screen_Status.Env_Frame_Flag = 1;

    if(Check_Frame_Format((INT8U *)Screen_Status.Env_Rcv_Data, Screen_Status.Env_Rcv_Posi))	  
	  Rcv_Frame_Proc(CH_ENV, (INT8U *)Screen_Status.Env_Rcv_Data, Screen_Status.Env_Rcv_Posi, sizeof(Screen_Status.Env_Rcv_Data)); 

	Clr_Env_Rcv_Data();
  }

  //ÿ�뷢��һ֡��ѯ����
  if(Sec.Var != Pub_Timer.Sec)
  {
    Sec.Var = Pub_Timer.Sec;
    Counts.Var ++;

	Clr_Env_Rcv_Data();

    Screen_Status.Env_Frame_Flag = 1; //���ý��ջ������������ݣ�����ڴ�������ڼ䲻�ܽ�������

	if(Counts.Var EQ 1)
      Send_Env_Frame(0x00);
	else if(Counts.Var EQ 2)
      Send_Env_Frame(0x01);
	else if(Counts.Var >= 3)
    { 
	  Send_Env_Frame(0x02);
	  Counts.Var = 0;
	 }

	 Screen_Status.Env_Frame_Flag = 0;
  }
#endif
}

//���ȿ���--��ȡpTime����ʱ�ε�����
INT8U Get_Cur_Time_Lightness(S_Time *pTime)
{
  INT8U i;
  INT8U Min = 0xFF,Diff;
  INT8U Lightness;
  
  if(Screen_Para.Lightness.Mode EQ MANUAL_ADJ)
  {
    Lightness = Screen_Para.Lightness.Manual_Lightness;
  }
  else if(Screen_Para.Lightness.Mode EQ TIME_ADJ)
  {
      Lightness = MAX_LIGHTNESS_LEVEL-1; //������ȵǼ�

      for(i = 0; i < MAX_LIGHTNESS_TIME; i++)
      {
        if(Screen_Para.Lightness.Time_Lightness[i].Flag > 0) //���ø�ʱ�ε����ȿ���
        {
          //���㵱ǰʱ��͸ö�ʱ�䰴��ʱ���
          Diff = (pTime->Time[T_HOUR] + 24 - Screen_Para.Lightness.Time_Lightness[i].Start_Hour) % 24;
          if(Diff < Min)
          {
            Min = Diff;
            Lightness = Screen_Para.Lightness.Time_Lightness[i].Value;
          }
        }
      }

      //return Lightness;
  }
  else
  {
    Lightness = MAX_LIGHTNESS_LEVEL / 2;
  }
  
  if(Lightness >= MAX_LIGHTNESS_LEVEL)
      Lightness = MAX_LIGHTNESS_LEVEL - 1;

  return Lightness; 
}

//��ȡ��ǰ���ػ�״̬
//����1��ʾӦ���ڿ���״̬��0��ʾӦ���ڹػ�״̬
INT8U Get_Open_Close_Status(S_Time *pTime)
{
  INT8U Flag = 0;
  INT8U i;
  INT16U Min, Min0,Min1;
  
  for(i = 0; i < MAX_OPEN_CLOSE_TIME; i++)
  {
     //�κ�һ��ʱ�ο�����Flag��1
    if(Screen_Para.OC_Time.Time[i].Flag > 0)
    {
      Flag = 1;
      Min0 = Screen_Para.OC_Time.Time[i].Open_Hour*60 + Screen_Para.OC_Time.Time[i].Open_Min;
      Min1 = Screen_Para.OC_Time.Time[i].Close_Hour*60 + Screen_Para.OC_Time.Time[i].Close_Min;
      Min = pTime->Time[T_HOUR]*60 + pTime->Time[T_MIN];
      
      if(Min0 < Min1)
      {
        if(Min >= Min0 && Min <= Min1)
          return 1;
      }
      else
      {
        if(Min >= Min0 || Min <= Min1)
          return 1;

      }
    }
  }
  
  if(Flag EQ 1) //����������һ��ʱ�Σ������ٸ�ʱ����
     return 0;
  else
     return 1; //û����������
}

//���ȿ���
void Screen_Lightness_Proc(void)
{
   INT8U Lightness;

   Lightness = Get_Cur_Time_Lightness(&Cur_Time); 
   Lightness = 100 * Lightness / (MAX_LIGHTNESS_LEVEL - 1); //ת��Ϊ�ٷ���
   if(Lightness >= 100)
     Lightness = 0;
   else
     Lightness = 100 - Lightness;
   Screen_Status.Lightness = Lightness;
   //Set_OE_Duty()
}

//���ػ�����
void Screen_Open_Close_Proc(void)
{
  if(Get_Open_Close_Status(&Cur_Time))
    Screen_Status.Time_OC_Flag = 0;
  else
    Screen_Status.Time_OC_Flag = CLOSE_FLAG;
  
}

//��ȡ��Ļ����
INT8U Get_Screen_Lightness(void)
{
  return Screen_Status.Lightness;
}

//��ȡ��Ļ����״̬
INT8U Get_Screen_Open_Status(void)
{
  return Screen_Status.Time_OC_Flag;
}

//�������²��ű�־
void Set_Screen_Replay_Flag(void)
{
    Screen_Status.Replay_Flag = REPLAY_FLAG;
    SET_SUM(Screen_Status);
}

//����Ƿ����²���
INT8U Chk_Screen_Replay_Flag(void)
{
    if(Screen_Status.Replay_Flag EQ REPLAY_FLAG)
      return 1;
    else
      return 0;
}

//����ͨ��ʱ��,��ͨ��ʱ�䷶Χ�ڣ�ɨ���жϲ�����ɨ
void Set_Screen_Com_Time(INT8U Sec)
{
    Screen_Status.Com_Time = Sec;
    //SET_SUM(Screen_Status);
}

INT8U Get_Screen_Com_Time(void)
{
   return Screen_Status.Com_Time;
}

//��ȡ��ǰʱ��
INT8U Get_Cur_Time()
{
  INT8U Re;
  INT8U Time[10];

  Re = _Get_Cur_Time(Time); //��ȡ��ǰʱ��
  if(Re)
  {
     memcpy(Cur_Time.Time, Time, sizeof(Cur_Time.Time));
     SET_SUM(Cur_Time);
  }

  return Re;
}

INT8U Chk_Time(S_Time *pTime)
{
  if(CHK_SUM((*pTime)) && CHK_HT((*pTime)))
  {
	if(pTime->Time[T_SEC] < 60 && pTime->Time[T_MIN] < 60 && pTime->Time[T_HOUR] < 24 &&\
	   pTime->Time[T_DATE] > 0 && pTime->Time[T_DATE] < 32 &&\
	   pTime->Time[T_MONTH] > 0 && pTime->Time[T_MONTH] < 32)
	   return 1;

  }

  return 0;
}

//ÿ���Ӷ�ȡһ��ʵʱʱ��
void Screen_Time_Proc()
{
  static S_Int32U Sec = {CHK_BYTE, 0, CHK_BYTE};
  INT32U Diff;
  
  Diff = Pub_Timer.Sec - Sec.Var;

  //if(Diff != 0)
  {
     Cur_Time.Time[T_SEC] += Diff;
	 if(Cur_Time.Time[T_SEC] >= 60 || Sec.Var EQ 0)
	 {
	   //Cur_Time.Time[T_SEC] = 0;
	   Get_Cur_Time();
	 }
         //Get_Cur_Time();//_Get_Cur_Time(Cur_Time.Time); //��ȡ��ǰʱ��
   }

   Sec.Var = Pub_Timer.Sec;
 
}

void Screen_Proc(void)
{
  Screen_Time_Proc();
  Screen_Lightness_Proc();
  Screen_Open_Close_Proc();
  Screen_Com_Proc(); //��Ļͨ�Ŵ���
  //Get_Cur_Time(Cur_Time.Time);
}
