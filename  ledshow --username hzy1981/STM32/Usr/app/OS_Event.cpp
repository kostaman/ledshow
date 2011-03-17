#define OS_EVENT_C
#include "OS_Includes.h"

#if (OS_MUTEX_EN>0) || (OS_SEM_EN>0) || (OS_MSG_EN>0) || (OS_MSG_Q_EN>0)

#if (OS_MUTEX_EN>0) && (OS_MUTEX_LOCK_CHK_EN>0)
//��ѯ��ǰ����������ź����Ƿ�����,��������������1�����򷵻�0
OS_INT8U OS_Check_Task_Event_Lock(OS_INT8U Task_ID)
{
  OS_INT32U Wait_Flag;
  OS_INT8U i;
  
  if(OS_CHECK_STRUCT_HT(OS_Task_Event[Task_ID]) EQ 0)
    OS_ASSERT_FAILED();
  
  Wait_Flag=OS_Task_Event[Task_ID].Wait_Event_Flag;  
  while(1)
  {
    for(i=0;i<Task_Info.Cur_Task_Num;i++)
    {
      if((OS_Task_Event[i].Hold_Event_Flag & Wait_Flag)!=0)//��ǰ�ȴ����ź�����������i��ռ�е��ź���
      {
         Wait_Flag=OS_Task_Event[i].Wait_Event_Flag;//�滻�ȴ��ź���
         //������ȴ����ź�������Task_IDռ�е��ź������γ���һ��������Ȧ
         if((Wait_Flag & OS_Task_Event[Task_ID].Hold_Event_Flag)!=0)
           return 1;
         else if(Wait_Flag EQ 0)//ռ�и��ź���������û�еȴ��ź����ˣ������γ�Ȧ
           return 0;
         else  //���´ӵ�0���������
           break;
      }
    }
    //û��һ������ռ�е��ź�������Wait_Flag˵���޷��γ�һ��Ȧ����������
    if(i EQ Task_Info.Cur_Task_Num)
      return 0;
  }
}
#endif

//��ʼ���¼�
void OS_Event_Init(void)
{
  OS_INT8U i;
  
  OS_memset((void *)&OS_Event,0,sizeof(OS_Event),(void *)&OS_Event,sizeof(OS_Event));
  
  for(i=0;i<OS_EVENT_NUM;i++)
  {
    OS_SET_STRUCT_HT(OS_Event[i]);
    
#if OS_CS_EN>0
    OS_SET_STRUCT_SUM(OS_Event[i]);
#endif    
  }
}

//�����¼���Ϣ��ʼ��
#if (OS_MUTEX_EN>0) && (OS_MUTEX_LOCK_CHK_EN>0)
void OS_Task_Event_Init(void)
{
  OS_INT8U i;
  
  for(i=0;i<OS_TASK_NUM;i++)
  {
    OS_Task_Event[i].Wait_Event_Flag=0;
    OS_Task_Event[i].Hold_Event_Flag=0;
    OS_SET_STRUCT_HT(OS_Task_Event[i]);
  } 
}
#endif

//���OS_Event��OS_Task_Event����Ϣ�Ƿ���ȷ
void OS_Event_Check(void)
{ 
  OS_INT8U i;
  
  for(i=0;i<OS_EVENT_NUM;i++)
  {
#if OS_CS_EN>0
    if(OS_CHECK_STRUCT_SUM(OS_Event[i]) EQ 0)
    {
      OS_ASSERT_FAILED();      
      OS_Debug_Print("\r\nOS:OS_Event[%d] CS error",i);
    }
#endif
    
    if(OS_CHECK_STRUCT_HT(OS_Event[i]) EQ 0)
    {
      OS_ASSERT_FAILED();       
      OS_Debug_Print("\r\nOS:OS_Event[%d] head or tail check error",i);
    }
  }
  
#if (OS_MUTEX_EN>0) && (OS_MUTEX_LOCK_CHK_EN>0)  
  for(i=0;i<OS_TASK_NUM;i++)
  {
    if(OS_CHECK_STRUCT_HT(OS_Task_Event[i]) EQ 0)
    {
      OS_ASSERT_FAILED();      
      OS_Debug_Print("\r\nOS:OS_Task_Event[%d] head or tail check error",i);
    }
  }
#endif  
}

#endif

#undef OS_EVENT_C


