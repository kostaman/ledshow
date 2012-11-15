#define OS_EXT_C
#include "OS_Includes.h"

//���ĳ�����ջʹ���������ջʹ�������򷵻�0�����򷵻�1
//��Ҫ�ǲ�ѯ��ջ��ͷβ�ֽ�,ͷβ�ֽ���ȷ,������Ϊ��ջ����û�б��ƻ�����Խ��
OS_INT8U OS_Check_Task_Stk(OS_INT8U Task_ID)
{
  if(Task_ID>=Task_Info.Cur_Task_Num)
    OS_ASSERT_FAILED();
  
#if OS_STK_GROWTH>0//��ջ�Ӹߵ�ַ��͵�ַ�ݼ� 
  if(CHK_STK_BYTE EQ *(OS_INT8U *)(Tcb[Task_ID].pStk) &&\
     CHK_STK_BYTE EQ *(OS_INT8U *)(Tcb[Task_ID].pStk-Tcb[Task_ID].Stk_Size/sizeof(OS_STK)+1))
    return 1;
#else  //��ջ�ӵ͵�ַ��ߵ�ַ����
  if(CHK_STK_BYTE EQ *(OS_INT8U *)(Tcb[Task_ID].pStk) &&
     CHK_STK_BYTE EQ *(OS_INT8U *)(Tcb[Task_ID].pStk+Stk_Size-1))
    return 1;
#endif
  OS_ASSERT_FAILED();
  return 0;
}

//���ĳ������Ķ�ջ��ʣ����ٿռ�
OS_INT16U OS_Get_Task_Stk_Left(OS_INT8U Task_ID)
{
  OS_INT16U i;
  OS_INT8U *p;
  
  if(Task_ID>=Task_Info.Cur_Task_Num)
    OS_ASSERT_FAILED();
  
#if OS_STK_GROWTH>0//��ջ�Ӹߵ�ַ��͵�ַ�ݼ� 
  p=(OS_INT8U *)(Tcb[Task_ID].pStk-Tcb[Task_ID].Stk_Size/sizeof(OS_STK)+1);
#else  //��ջ�ӵ͵�ַ��ߵ�ַ����
  p=(OS_INT8U *)(Tcb[Task_ID].pStk);
#endif  
  
  i=0;
  while(1)
  {
    if(CHK_STK_BYTE!=*(p+i))
      return i;
    i++;
  } 
}

//��ȡ��ǰ�����ID��
OS_INT8U OS_Get_Cur_Task_ID(void)
{
  if(OS_CHECK_STRUCT_HT(Task_Info) EQ 0)
    OS_ASSERT_FAILED();

  return Task_Info.Cur_Task_ID;
}

//��ȡ��ǰ��������
OS_INT8U OS_Get_Cur_Task_Num(void)
{
  if(OS_CHECK_STRUCT_HT(Task_Info) EQ 0)
    OS_ASSERT_FAILED();

  return Task_Info.Cur_Task_Num;
}

#if OS_TASK_NAME_EN>0
//��ȡ���������
OS_INT8S * OS_Get_Task_Name(OS_INT8U Task_ID)
{
  if(Task_ID>=Task_Info.Cur_Task_Num)
    OS_ASSERT_FAILED();

  return Tcb[Task_ID].Name;  
}
#endif

//���������������Ƿ���ȷ��ע�⣺�ú����в��ܵ��ò���ϵͳ�ṩ�ĵ���
//ֻ��OS_USE_CS�ú�Ϊ1ʱ���ú�����������
void OS_Check_Task_Env(void)
{
  OS_INT8U Next_Task_ID;
  
  if(OS_CHECK_STRUCT_HT(Task_Info) EQ 0)//���Task_Info��ͷ��β
    OS_ASSERT_FAILED();
  
//���Ҫϵͳ�ٶȸ��죬�ɰ�У���������Σ�ֻ����ͷβ���� 
#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(Tcb[Task_Info.Cur_Task_ID]);
#endif

  Next_Task_ID=(Task_Info.Cur_Task_ID+1)%Task_Info.Cur_Task_Num;//�¸������ID

//���Ҫϵͳ�ٶȸ��죬�ɰ�У���������Σ�ֻ����ͷβ���� 
#if OS_CS_EN>0
  if(OS_CHECK_STRUCT_SUM(Tcb[Next_Task_ID]) EQ 0)//���У���
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Tcb[%d] sum error",Next_Task_ID);    
  }
#endif

  if(OS_CHECK_STRUCT_HT(Tcb[Next_Task_ID]) EQ 0)//���ͷβ�ֽ�
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Tcb[%d] head or tail check error",Next_Task_ID);     
  }
  
  if(OS_Check_Task_Stk(Next_Task_ID) EQ 0)//����ջ��ͷ��β
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Task %d stack error",Next_Task_ID); 
  }
}

//�����񻷾��ļ��
void OS_Task_Info_Check(void)
{
  OS_INT8U i;
  
#if OS_TICK_ISR_EN>0
  if(OS_CHECK_STRUCT_HT(Tick_ISR_Flag) EQ 0)
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Tick_ISR_Flag head or tail check error");
  }
#endif
  
  if(OS_CHECK_STRUCT_HT(Task_Info) EQ 0)
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Task Info head or tail check error");
  }

#if OS_CS_EN>0 
  if(OS_CHECK_STRUCT_SUM(Task_Info) EQ 0)
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Task_Info CS check error");
  }
#endif
  
  for(i=0;i<OS_TASK_NUM;i++)
  {
    if(OS_CHECK_STRUCT_HT(Tcb[i]) EQ 0)
    {
      OS_ASSERT_FAILED();
      OS_Debug_Print("\r\nOS:Task %d env head or tail check error", i);
    }
    
#if OS_CS_EN>0 
    if(OS_CHECK_STRUCT_SUM(Tcb[i]) EQ 0)
    {
      OS_ASSERT_FAILED();
      OS_Debug_Print("\r\nOS:Task %d env CS check error", i);
    }
#endif
  }
}

//��ӡ������ص���Ϣ����ջʣ���ֽ���
void OS_Task_Info_Print(void)
{
  OS_INT8U i,Task_Num;
  
  OS_Debug_Print("\r\nOS:Task remaining stack bytes:");
  Task_Num = OS_Get_Cur_Task_Num();
  for(i=0;i<Task_Num;i++)
    OS_Debug_Print("\r\n  Task %d:%d",i,OS_Get_Task_Stk_Left(i));
}

//��ȡ����ϵͳ�汾��
OS_INT32U OS_Get_Version(void)
{
  return OS_VERSION;
}

//��ӡ�汾��Ϣ����ʽ���汾-����ʱ��-��������
void OS_Version_Info_Print(void)
{
  OS_Debug_Print("\r\nOS:Version:%ld-%s-%s", OS_VERSION, __TIME__, __DATE__);
}

#undef OS_EXT_C

