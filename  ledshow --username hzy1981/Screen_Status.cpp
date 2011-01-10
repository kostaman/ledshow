#define SCREEN_STATUS_C
#include "Includes.h"

//���ȿ���--��ȡpTime����ʱ�ε�����
INT8U Get_Cur_Time_Lightness(S_Time *pTime)
{
  INT8U i;
  INT8U Min = 0xFF,Diff;
  INT8U Lightness;
  
  Lightness = MAX_LIGHTNESS_LEVEL; //������ȵǼ�
  
  for(i = 0; i < MAX_LIGHTNESS_TIME; i++)
  {
    if(Screen_Para.Lightness[i].Flag > 0) //���ø�ʱ�ε����ȿ���
    {
      //���㵱ǰʱ��͸ö�ʱ�䰴��ʱ���
      Diff = (pTime->Time[T_HOUR] + 24 - Screen_Para.Lightness[i].Start_Hour) % 24;
      if(Diff < Min)
      {
        Min = Diff;
        Lightness = Screen_Para.Lightness[i].Value;
      }
    }
  }
  
  return Lightness; 
}

//��ȡ��ǰ���ػ�״̬
//����1��ʾӦ���ڿ���״̬��0��ʾӦ���ڹػ�״̬
INT8U Get_Open_Close_Status(S_Time *pTime)
{
  INT8U i;
  INT16U Min, Min0,Min1;
  
  for(i = 0; i < MAX_OPEN_CLOSE_TIME; i++)
  {
    if(Screen_Para.Open_Close_Time[i].Flag > 0)
    {
      Min0 = Screen_Para.Open_Close_Time[i].Open_Hour*60 + Screen_Para.Open_Close_Time[i].Open_Min;
      Min1 = Screen_Para.Open_Close_Time[i].Close_Hour*60 + Screen_Para.Open_Close_Time[i].Close_Min;
      Min = pTime->Time[T_HOUR]*60 + pTime->Time[T_MIN];
      
      if(Min0 < Min1)
      {
        if(Min >= Min0 && Min <= Min1)
          return 1;
        else
          return 0;
      }
      else
      {
        if(Min >= Min0 || Min <= Min1)
          return 1;
        else
          return 0;      
      }
    }
  }
  
  return 1;
}

//���ȿ���
void Lightness_Proc()
{
  Screen_Status.Lightness = Get_Cur_Time_Lightness(&Cur_Time);  
  
}

//���ػ�����
void Open_Close_Proc()
{
  Screen_Status.Open_Flag = Get_Open_Close_Status(&Cur_Time);
  
}

//��ȡ��Ļ����
INT8U Get_Screen_Lightness()
{
  return Screen_Status.Lightness;
}

//��ȡ��Ļ����״̬
INT8U Get_Screen_Open_Status()
{
  return Screen_Status.Open_Flag;
}


void Screen_Proc()
{
  Lightness_Proc();
  Open_Close_Proc();
}
