#ifndef OS_CORE_H
#define OS_CORE_H

#undef OS_EXT
#ifndef OS_CORE_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

//�����ջ�����
#define CHK_STK_BYTE (OS_INT8U)0x00

#define OS_TASK_WAITING 0x00//�ȴ�״̬
#define OS_TASK_SUSPEND 0x11//����״̬
#define OS_TASK_RUNNING 0x22//����״̬

//��������λ������
#define OS_SET_BIT(x,y) ((x)|=0x01<<(y))
#define OS_CLR_BIT(x,y) ((x)&=~(0x01<<(y)))
#define OS_GET_BIT(x,y) (((x)>>(y))&0x01)

//�����ȴ�,ע��Condition�е�ȫ�ֱ���������Volatile����
#define OS_Core_Wait(Condition)\
do{ while(!(Condition))\
      OS_Task_Switch_Proc();\
  }while(0)

//����������ƿ���Ϣ
typedef struct{
  OS_ALIGN_TYPE Head;   //����У���ͷ,����OS_Align_Type��Ϊ����ĳЩ��������ȷ�� Env����һ������ĵ�ַ
 
  OS_Task_Env Env;          //��ǰ���񻷾�
  void (*pEntry)();         //�������
  OS_STK *pStk;             //��ջ��ʼָ��
  OS_INT32U Stk_Size;       //��ջ��С

#if OS_TASK_NAME_EN>0        //ʹ����������
  OS_INT8S Name[OS_TASK_NAME_SIZE];//��������,�ౣ��һ���ֽ���0
#endif

#if OS_CS_EN>0            //ʹ��У���,���ڱ���TCB��Ϣ
  OS_INT8U CS[OS_CS_BYTES];
#endif

  volatile OS_INT8U Status;//����״̬��־��־
  
  volatile OS_INT32U Time_Dly;       //��ʱʱ�䣬��λms,��ʱ������Ϊ������Ҫ�޸ģ�������У�����,��ֹ����ϵͳ����ռ��̫��cpuʱ��
  
  OS_ALIGN_TYPE Tail;
}OS_TCB;

typedef struct{
  OS_INT8U Head;
  
  OS_INT8U Cur_Task_ID;   //��ǰ����ID��
  OS_INT8U Cur_Task_Num;  //��ǰ�������� 
  
#if OS_CS_EN>0           //ʹ��У���,���ڱ���Task_Info��Ϣ
  OS_INT8U CS[OS_CS_BYTES];
#endif
  
  OS_INT16U Tail;
  
}OS_Task_Info;

#ifdef OS_CORE_C //ֻ�ṩ��OS_Core.c�ļ�
OS_EXT volatile OS_SP Old_SP;//���ڴ�������ʱ�����ϵ������ջָ��,SAVE_TASK_SP()����ǰSP���浽Old_SP��
OS_EXT volatile OS_SP New_SP;//���ڴ�������ʱ�ָ��ϵ������ջָ��,RESTORE_TASK_SP()����ǰNew_SP���浽SP��
#endif

#if OS_TICK_ISR_EN>0
OS_EXT volatile S_Int8U Tick_ISR_Flag;//�жϱ�־���ñ�־��1��ʾһ��ʱ�����ڹ�ȥ
#endif

OS_EXT OS_TCB Tcb[OS_TASK_NUM];//���������Ϣ��
OS_EXT volatile OS_Task_Info Task_Info;//��ǰ������Ϣ

OS_EXT void OS_Init(void);
OS_EXT void OS_Change_Cur_Task_ID(void);
OS_EXT void OS_Task_Switch_Proc(void);
OS_EXT OS_INT8U OS_Create_Task(void(*pEntry)(),OS_STK *pStk,OS_INT32U Stk_Size,CONST OS_INT8S Name[]);
OS_EXT void OS_Task_Suspend(OS_INT8U Task_ID);
OS_EXT void OS_Task_Unsuspend(OS_INT8U Task_ID);
OS_EXT void OS_Start(void);

#if OS_TICK_ISR_EN>0
OS_EXT void OS_Tick_ISR(void);//����ʱ���жϷ���
#endif

#endif
