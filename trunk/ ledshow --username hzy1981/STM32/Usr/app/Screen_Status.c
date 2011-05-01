#define SCREEN_STATUS_C
#include "Includes.h"

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
  Screen_Status.Lightness = Get_Cur_Time_Lightness(&Cur_Time);  
  
}

//���ػ�����
void Screen_Open_Close_Proc(void)
{
  Screen_Status.Open_Flag = Get_Open_Close_Status(&Cur_Time);
  
}

//��ȡ��Ļ����
INT8U Get_Screen_Lightness(void)
{
  return Screen_Status.Lightness;
}

//��ȡ��Ļ����״̬
INT8U Get_Screen_Open_Status(void)
{
  return Screen_Status.Open_Flag;
}


void Set_Screen_Replay_Flag(void)
{
    Screen_Status.Replay_Flag = REPLAY_FLAG;
    SET_SUM(Screen_Status);
}

INT8U Chk_Screen_Replay_Flag(void)
{
    if(Screen_Status.Replay_Flag EQ REPLAY_FLAG)
      return 1;
    else
      return 0;
}

void Set_Screen_Com_Time(INT8U Sec)
{
    Screen_Status.Com_Time = Sec;
    SET_SUM(Screen_Status);
}

INT8U Get_Screen_Com_Time(void)
{
   return Screen_Status.Com_Time;
}

void Screen_Proc(void)
{
  Screen_Lightness_Proc();
  Screen_Open_Close_Proc();
  Screen_Com_Proc(); //��Ļͨ�Ŵ���
  Get_Cur_Time();
}
