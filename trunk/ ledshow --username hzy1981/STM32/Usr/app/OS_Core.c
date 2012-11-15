#define OS_CORE_C
#include "OS_Includes.h"

//����������
//pEntry��ʾ���������
//pStk��ʾ��ջ����ʼ��ַ
//Stk_Size��ջ�ĳ��ȣ����ֽ�Ϊ��λ
//Name���������,ֻ�е�OS_TASK_NAME_EN�����Ϊ1ʱ�����ֲ�������
OS_INT8U OS_Create_Task(void(*pEntry)(),OS_STK *pStk,OS_INT32U Stk_Size,CONST OS_INT8S Name[])
{
  OS_INT8U i=0;
  static OS_INT8U Task_ID;//ʹ�þ�̬�ֲ���������ֹ�����ı仯ʱ�ֲ������ı仯

  if(Task_Info.Cur_Task_Num>=OS_TASK_NUM)
  {
    OS_ASSERT_FAILED();
    return 0;  
  }
  
  i=0;
  Task_ID=Task_Info.Cur_Task_Num;
  
  Task_Info.Cur_Task_Num++; 
  
#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(Task_Info);
#endif
  
  OS_SET_STRUCT_HT(Tcb[Task_ID]);
  Tcb[Task_ID].pEntry=pEntry;  
  Tcb[Task_ID].pStk=pStk;
  Tcb[Task_ID].Stk_Size=Stk_Size;
  Tcb[Task_ID].Time_Dly=0;
  Tcb[Task_ID].Status=OS_TASK_RUNNING;

#if OS_TASK_NAME_EN>0 //���ʹ������ 
  while(i<OS_TASK_NAME_SIZE-1 && Name[i]!=0)
  {
    Tcb[Task_ID].Name[i]=Name[i];  
    i++;
  }
  Tcb[Task_ID].Name[i]=0;
#else
  (void)i;//��ֹ���뾯��
#endif
    
  //����ջ���ݳ�ʼ���������ַ�����ͳ�ƶ�ջ����
  //ͬʱ������ջ��ͷβ�����ֽڣ������ж϶�ջ�Ƿ�������߱�����
#if OS_STK_GROWTH>0//��ջ�Ӹߵ�ַ��͵�ַ�ݼ�
  OS_memset(pStk-Stk_Size/sizeof(OS_STK)+1,CHK_STK_BYTE,Stk_Size,pStk-Stk_Size/sizeof(OS_STK)+1,Stk_Size);
  pStk--;
#else  //��ջ�ӵ͵�ַ��ߵ�ַ����
  OS_memset((OS_INT8U *)pStk,CHK_STK_BYTE,Stk_Size,(OS_INT8U *)pStk,Stk_Size);
  pStk++;
#endif
  
  SAVE_TASK_SP();//��SP���浽Old_SP
  New_SP=(OS_SP)pStk;
  RESTORE_TASK_SP();//��New_SP�ָ���SP��
  //�˴���ʼ�������ջ������
  if(OS_Save_Env(Tcb[Task_ID].Env) EQ 0)//���浱ǰ��������
  { 
    New_SP=Old_SP;
    RESTORE_TASK_SP();//�ָ��ϵ�SP
    
#if OS_CS_EN>0
    OS_SET_STRUCT_SUM(Tcb[Task_ID]);//���õ�ǰ���񻷾���У���
#endif
  
  }
  else//else�ڳ�����������������
  {
    Tcb[Task_Info.Cur_Task_ID].pEntry();//Entry���л��������ջ����ܶ�ʧ����˲���pEntry  
  }
  return 1;
}

//�޸ĵ�ǰ����ID���Ա���ȵ���һ������
void OS_Change_Cur_Task_ID(void)
{
  OS_INT8U i=0;
  
  if(OS_CHECK_STRUCT_HT(Task_Info) EQ 0)
    OS_ASSERT_FAILED();
 
//���Ҫϵͳ�ٶȸ��죬�ɰ�У���������Σ�ֻ����ͷβ����
#if OS_CS_EN>0
  if(OS_CHECK_STRUCT_SUM(Task_Info) EQ 0)
    OS_ASSERT_FAILED();
#endif 

#if OS_TASK_SUSPEND_EN>0 //�������������
  for(i=0;i<Task_Info.Cur_Task_Num;i++)
  {
    Task_Info.Cur_Task_ID++;
    
    if(Task_Info.Cur_Task_ID>=Task_Info.Cur_Task_Num) 
      Task_Info.Cur_Task_ID=0;     
    
    if(Tcb[Task_Info.Cur_Task_ID].Status!=OS_TASK_SUSPEND)//ֱ���ҵ�һ��û�б����������
      break;
  }
#else  
  (void)i;
  
  Task_Info.Cur_Task_ID++;
  
  if(Task_Info.Cur_Task_ID>=Task_Info.Cur_Task_Num) 
    Task_Info.Cur_Task_ID=0;
#endif
  
//���Ҫϵͳ�ٶȸ��죬�ɰ�У���������Σ�ֻ����ͷβ����  
#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(Task_Info);
#endif  
}

#if OS_TASK_SWITCH_HOOK_EN>0
extern void OS_Task_Switch_Hook(void);
#endif 

#if OS_TICK_HOOK_EN>0
extern void OS_Tick_Hook(void);//ʱ�����Ӻ���
#endif

//�����л�ʱ����ش���
void OS_Task_Switch_Proc(void)
{
  if(OS_Save_Env(Tcb[Task_Info.Cur_Task_ID].Env) EQ 0)
  {
  #if OS_TASK_SWITCH_HOOK_EN>0
    OS_Task_Switch_Hook();
  #endif  
  
    if(OS_Check_Sys_Tick())//����ϵͳ��һ��ʱ����
    {
      OS_TaskDly_Proc();//���������ʱ
      
  #if OS_TICK_HOOK_EN>0    
      OS_Tick_Hook();//ʱ�����Ӻ���
  #endif
      
    }
    OS_Check_Task_Env();//������񻷾�
    OS_Change_Cur_Task_ID();//�޸�����ID
    OS_Restore_Env(Tcb[Task_Info.Cur_Task_ID].Env);
  }
}

//�������ΪTask_ID���������
void OS_Task_Suspend(OS_INT8U Task_ID)
{
  if(Task_ID>=Task_Info.Cur_Task_Num || Task_ID>=OS_TASK_NUM)
  {
    OS_ASSERT_FAILED();
    return;
  }
  
  Tcb[Task_ID].Status=OS_TASK_SUSPEND;
  
  if(Task_ID EQ Task_Info.Cur_Task_ID)//�������ľ��ǵ�ǰ���������Ϲ����Լ�
    OS_Core_Wait(Tcb[Task_ID].Status!=OS_TASK_SUSPEND);
}

//�������ΪTask_ID������ȡ������
void OS_Task_Unsuspend(OS_INT8U Task_ID)
{
  if(Task_ID>=Task_Info.Cur_Task_Num || Task_ID>=OS_TASK_NUM)
  {
    OS_ASSERT_FAILED();
    return;
  }
  
  Tcb[Task_ID].Status=OS_TASK_RUNNING;
}

#if OS_TICK_ISR_EN>0 //ʹ���ж���ΪTick��׼
void OS_Tick_ISR(void) //����ms��ʱ��,ÿ�����жϵ���
{
  Tick_ISR_Flag.Var=1;
}
#endif

//����ϵͳ��������
void OS_Start(void)
{
  OS_Restore_Env(Tcb[0].Env);//�л�����һ�������ִ�л���   
}

//����ϵͳ��ʼ������
void OS_Init(void)
{
#if OS_TICK_ISR_EN>0
  Tick_ISR_Flag.Var=0;
  OS_SET_STRUCT_HT(Tick_ISR_Flag);
#endif

#if (OS_MUTEX_EN>0) && (OS_MUTEX_LOCK_CHK_EN>0)
  OS_Task_Event_Init();
#endif

#if (OS_MUTEX_EN>0) || (OS_SEM_EN>0) || (OS_MSG_EN>0) || (OS_MSG_Q_EN>0)
  OS_Event_Init();
#endif
  
#if OS_TRACE_EN>0
  OS_SET_STRUCT_HT(Trace_Info);
  Trace_Info.Entry_Flag=0;
#endif
  
  Task_Info.Cur_Task_ID=0;
  Task_Info.Cur_Task_Num=0;
  OS_SET_STRUCT_HT(Task_Info);
  
#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(Task_Info);
#endif
}

#undef OS_CORE_C
