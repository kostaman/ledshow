#define OS_TIME_C
#include "OS_Includes.h"

//������ϵͳ��һ��ʱ���Ƿ�
OS_INT8U OS_Check_Sys_Tick(void)
{
#if OS_TICK_ISR_EN>0 //ʹ��OS_Tick_ISR��Tick_ISR_Flag��1
  if(1 EQ Tick_ISR_Flag.Var)//���ж��иñ�־��1��ʾһ��ʱ�����ڵ�
  {
    Tick_ISR_Flag.Var=0;
    return 1;
  }
#else
  if(OS_Check_Tick())//��ѯ��ʱ����ȷ��ʱ�����ú������ݾ���CPU��ʵ��
    return 1;
#endif
  return 0;
  
}

//����������ʱʱ��,ÿ��ʱ������һ�θú���
void OS_TaskDly_Proc(void)
{
  OS_INT16U i;

  for(i=0;i<Task_Info.Cur_Task_Num;i++)//�޸�ÿ���������ʱʱ��
  {
    if(0!=Tcb[i].Time_Dly)//����ʱ��0�ĺ�������������ʱ
    {
      //��ÿ���������ʱ���м���
      if(Tcb[i].Time_Dly>OS_MS_PER_TICK)
        Tcb[i].Time_Dly-=OS_MS_PER_TICK;
      else
        Tcb[i].Time_Dly=0;
    }
  }
}

//�����������ʱ�����������Ͻ�����ʱ״̬
void OS_Set_Task_TimeDly(OS_INT16U Hour,OS_INT16U Min,OS_INT16U Sec,OS_INT16U m_Sec)
{
  Tcb[Task_Info.Cur_Task_ID].Time_Dly=(OS_INT32U)Hour*3600L*1000L+(OS_INT32U)Min*60L*1000L+(OS_INT32U)Sec*1000L+(OS_INT32U)m_Sec+(OS_INT32U)OS_MS_PER_TICK;
}  

//������ʱ����
void OS_TimeDly(OS_INT16U Hour,OS_INT16U Min,OS_INT16U Sec,OS_INT16U m_Sec)
{
  OS_Set_Task_TimeDly(Hour, Min, Sec, m_Sec);		
  OS_Core_Wait((Tcb[Task_Info.Cur_Task_ID].Time_Dly EQ 0));
}

//��鵱ǰ�����Ƿ�����ʱ״̬���Ƿ���1�����򷵻�0
OS_INT8U OS_Check_Task_TimeDly(void)
{
  if(Tcb[Task_Info.Cur_Task_ID].Time_Dly!=0)
    return 1;
  else
    return 0;
}

#undef OS_TIME_C
