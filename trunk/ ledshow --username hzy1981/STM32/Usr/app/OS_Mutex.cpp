#define OS_MUTEX_C
#include "OS_Includes.h"

#if OS_MUTEX_EN>0
//��ʼ�������ź���,�����ź�����ID��Ӧ�ó����Լ��̶�
//ValΪ�����ź����ĳ�ʼֵ��1��ʾ��Դ��ռ�ã�0��ʾ��Դ���ͷ�
//�����ɹ�����1��ʧ�ܷ���0
OS_INT8U OS_Mutex_Init(OS_INT8U ID,OS_INT8U Val)
{
  if(ID>=OS_EVENT_NUM)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
  OS_Event[ID].Type=OS_MUTEX;
  OS_Event[ID].Value=(Val EQ 0)?0:1;
  
#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(OS_Event[ID]);//����У���
#endif
  
  OS_SET_STRUCT_HT(OS_Event[ID]);
  return 1; 
}

//Post�����ź���,�ɹ�����1��ʧ�ܷ���0
OS_INT8U OS_Mutex_Post(OS_INT8U ID)
{
#if OS_CS_EN>0
  if(OS_CHECK_STRUCT_SUM(OS_Event[ID]) EQ 0)
    OS_ASSERT_FAILED();
#endif

#if OS_MUTEX_LOCK_CHK_EN>0
  if(OS_CHECK_STRUCT_HT(OS_Task_Event[Task_Info.Cur_Task_ID]) EQ 0)
    OS_ASSERT_FAILED();
#endif
  
  if(ID>=OS_EVENT_NUM)
  {
    OS_ASSERT_FAILED();
    return 0;
  }

  if(OS_Event[ID].Type!=OS_MUTEX)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
#if OS_MUTEX_LOCK_CHK_EN>0
  /*
  //���ϵͳ�е��ź���������Դ������(��������ͬ��)�����Դ���γ��򣬱��������ͷ��ź���
  if(OS_GET_BIT(Tcb[Task_Info.Cur_Task_ID].Hold_Event_Flag,ID) EQ 0)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  */
  OS_CLR_BIT(OS_Task_Event[Task_Info.Cur_Task_ID].Hold_Event_Flag,ID);//�������ռ�л����ź�����־
#endif

  if(OS_Event[ID].Value!=0)//��������post���
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Mutex %d post multi-times,Cur task ID:%d",ID,Task_Info.Cur_Task_ID);
  }
  
  OS_Event[ID].Value=1;
  
#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(OS_Event[ID]);
#endif
 
  return 1;
}

//���뻥���ź���,�ɹ�����1��ʧ�ܷ���0���߲����� 
OS_INT8U OS_Mutex_Pend(OS_INT8U ID)
{
  OS_INT16U Counts;
  
#if OS_CS_EN>0
  if(OS_CHECK_STRUCT_SUM(OS_Event[ID]) EQ 0)
    OS_ASSERT_FAILED();
#endif

#if OS_MUTEX_LOCK_CHK_EN>0  
  if(OS_CHECK_STRUCT_HT(OS_Task_Event[Task_Info.Cur_Task_ID]) EQ 0)
    OS_ASSERT_FAILED();
#endif
  
  if(ID>=OS_EVENT_NUM)
  {
    OS_ASSERT_FAILED();
    return 0;
  }

  if(OS_Event[ID].Type!=OS_MUTEX)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
  if(OS_Event[ID].Value!=0)
  {
#if OS_MUTEX_LOCK_CHK_EN>0
    OS_SET_BIT(OS_Task_Event[Task_Info.Cur_Task_ID].Hold_Event_Flag,ID); 
#endif
    
    OS_Event[ID].Value=0;
    
#if OS_CS_EN>0
    OS_SET_STRUCT_SUM(OS_Event[ID]);
#endif
    
    return 1;
  }
  else
  {
    Counts=0;
#if OS_MUTEX_LOCK_CHK_EN>0
    OS_SET_BIT(OS_Task_Event[Task_Info.Cur_Task_ID].Wait_Event_Flag,ID);//��������ȴ������ź�����־
    //�ڵȴ����������ź���������£�ÿ��OS_MUTEX_WAIT_WARN_TIME S���һ���Ƿ���������״̬
    while(1)
    {
      OS_Core_Wait_Sec(OS_Event[ID].Value!=0,OS_MUTEX_WAIT_WARN_TIME);
      //�ȴ�1S����Ȼ���벻�������ź���������Ҫ��ѯ�Ƿ�����������
      if(OS_Event[ID].Value EQ 0)
      {
        if(OS_Check_Task_Event_Lock(Task_Info.Cur_Task_ID))//��ǰ��������Ļ����ź�����������
        {
        #if OS_MUTEX_LOCK_CHK_EN>0
          OS_SET_BIT(OS_Task_Event[Task_Info.Cur_Task_ID].Wait_Event_Flag,ID);//���ٵȴ��û����ź���
        #endif
          OS_ASSERT_FAILED();
          OS_Debug_Print("\r\nOS:Task %d pend mutex %d locked!",Task_Info.Cur_Task_ID,ID);
          OS_Mutex_Info_Print();
          OS_Debug_Print("\r\nOS:Task %d suspend!",Task_Info.Cur_Task_ID);
          OS_Core_Wait(0);
        }

        Counts++;
        OS_Debug_Print("\r\nOS:Task %d pend mutex %d time out,Counts=%d",Task_Info.Cur_Task_ID,ID,Counts);
      }
      else//�Ѿ����뵽
      {
        OS_CLR_BIT(OS_Task_Event[Task_Info.Cur_Task_ID].Wait_Event_Flag,ID);//�������ȴ������ź�����־
        OS_SET_BIT(OS_Task_Event[Task_Info.Cur_Task_ID].Hold_Event_Flag,ID);//��������ռ�л����ź�����־
        break;
      }
    }
#else
    while(1)
    {
      OS_Core_Wait_Sec(OS_Event[ID].Value!=0,OS_MUTEX_WAIT_WARN_TIME);
      if(OS_Event[ID].Value EQ 0)
      {
        Counts++;
        OS_Debug_Print("\r\nOS:Task %d pend mutex %d time out,Counts=%d",Task_Info.Cur_Task_ID,ID,Counts);        
      }
      else
        break;
    }
#endif
  }
  
  OS_Event[ID].Value=0;
   
#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(OS_Event[ID]);
#endif   
   return 1;  
}

//��ӡ�����ź����������Ϣ
void OS_Mutex_Info_Print(void)
{
  OS_INT8U i;
  
  OS_Debug_Print("\r\nOS:Mutex Use Info:");
  
  for(i=0;i<OS_EVENT_NUM;i++)
  {
    if(OS_Event[i].Type!=OS_MUTEX)
      continue;

    OS_Debug_Print("\r\n  Mutex %d Val=0x%x",i,OS_Event[i].Value);
  }
  
#if OS_MUTEX_LOCK_CHK_EN>0
  for(i=0;i<OS_TASK_NUM;i++)
  {
    OS_Debug_Print("\r\n  Task %d Wait_Flag=0x%x, Hold_Flag=0x%x",i,OS_Task_Event[i].Wait_Event_Flag,OS_Task_Event[i].Hold_Event_Flag);
  }
#endif  
}
#endif

#undef OS_MUTEX_C

