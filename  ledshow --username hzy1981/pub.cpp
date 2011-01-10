#define PUB_C
#include "Includes.h"

//�˺������в�������������ĺ�����
INT8U OS_Debug_Print_En(void)
{
    return 1;
}

void OS_Trace_Hook(void)
{

}

void OS_Assert_Hook(CONST OS_INT8S File[],CONST OS_INT8S Function[],OS_INT16U Line)
{

}

INT16U Sum_2Bytes(INT8U Src[], INT16U SrcLen)
{
  INT16U CS = 0;
  INT16U i;

  for(i = 0; i < SrcLen; i ++)
  {
    CS += Src[i]; 
  }
  return CS;
}

//S_Time����ת��tm����
void S_Time_2_tm(S_Time *pTime, struct tm *ptm)
{
  ptm -> tm_sec = pTime->Time[T_SEC];
  ptm -> tm_min = pTime->Time[T_MIN];
  ptm -> tm_hour = pTime->Time[T_HOUR];
  ptm -> tm_mday = pTime->Time[T_DATE];
  ptm -> tm_mon = pTime->Time[T_MONTH] - 1;
  ptm -> tm_year = (int)pTime->Time[T_YEAR] + 2000 - 1900; 
  ptm -> tm_isdst = 0;
}

//tm����ת��S_Time����
void tm_2_S_Time(struct tm *ptm, S_Time *pTime)
{
  pTime->Time[T_SEC] = (INT8U)(ptm -> tm_sec);
  pTime->Time[T_MIN] = (INT8U)(ptm -> tm_min);
  pTime->Time[T_HOUR] = (INT8U)(ptm -> tm_hour);
  pTime->Time[T_DATE] = (INT8U)(ptm -> tm_mday);
  pTime->Time[T_MONTH] = (INT8U)(ptm -> tm_mon + 1);
  pTime->Time[T_YEAR] = (INT8U)(ptm -> tm_year + 1900 - 2000); 
}

#undef PUB_C
