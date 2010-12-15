#ifndef OS_MSG_Q_H
#define OS_MSG_Q_H

#if OS_MSG_Q_EN>0

#undef OS_EXT
#ifndef OS_MSG_Q_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

typedef struct
{
  OS_INT8U Head;
  
  OS_INT32U Rcv_Flag;//���մ���Ϣ������
  OS_INT16U Msg_Len;//��Ϣ�ĳ���
  
#if OS_CS_EN>0
  OS_INT8U CS[OS_CS_BYTES];
#endif 
  
  OS_INT8U Tail;
}S_Msg_Q_H_Info;

//ÿ����Ϣ�ڴ���ڱ����Ĵ�С,Ԥ������Ϣͷ��β
#define MSG_RESERVE_SIZE (sizeof(S_Msg_Q_H_Info)+1) 

typedef struct
{
  OS_INT8U Head;
  
  OS_INT8U Msg_Flag;//��Ϣ���б�־��
  OS_INT32U Msg_Rcv_Flag; //���ձ�־����ʾ��Щ������Դ������Ϣ�����н�����Ϣ
  OS_INT8U Msg_Rcv_Index[OS_TASK_NUM]; //��Ϣ�Ľ�������
  OS_INT8U Msg_Send_Index;//��Ϣ�ķ�������
  OS_INT8U Msg_Max_Num; //��Ϣ�ĸ���
  OS_INT8U Msg_Mem_Size; //ÿ����Ϣ�ĳ���,������ͷ��β��λ��,��˲�����ʵ����Ϣ����󳤶�
  void *pMsg;       //ָ����Ϣ����
  
#if OS_CS_EN>0
  OS_INT8U CS[OS_CS_BYTES];
#endif
  
  OS_INT8U Tail;
}S_Msg_Q_Info;  

//ʹ��OS_ALIGN_TYPE��֤ÿ����Ϣ��Ӧ��bug����ʼλ�ö�����һ�������λ����
//��Ϊÿ����Ϣbug����ʼλ�ö�������һ��S_Msg_Q_H_Info�ṹ�壬���봦��һ�������λ����
#define DECLARE_MSG_Q(Q_Info_Name,Msg_Num,Msg_Len,Rcv_Flag) typedef struct{\
                                                                           OS_ALIGN_TYPE Head;\
                                                                           OS_INT8U Buf[(Msg_Num)][(((Msg_Len)+MSG_RESERVE_SIZE)/sizeof(OS_ALIGN_TYPE)+1)*sizeof(OS_ALIGN_TYPE)];\
                                                                           OS_ALIGN_TYPE Tail;\
                                                                           }S_##Q_Info_Name##_QBuf;\
                                 S_##Q_Info_Name##_QBuf Q_Info_Name##_QBuf={\
                                                                            CHK_BYTE,\
                                                                            {{0}},\
                                                                            CHK_BYTE,\
                                                                            };\
                                                  S_Msg_Q_Info Q_Info_Name={\
                                                                            CHK_BYTE,\
                                                                            OS_MSG_Q,\
                                                                            (Rcv_Flag),\
                                                                            {0},\
                                                                            0,\
                                                                            (Msg_Num),\
                                                                            (((Msg_Len)+MSG_RESERVE_SIZE)/sizeof(OS_ALIGN_TYPE)+1)*sizeof(OS_ALIGN_TYPE),\
                                                                            Q_Info_Name##_QBuf.Buf,\
                                                                            CHK_BYTE,};

OS_EXT OS_INT8U OS_Msg_Q_Init(OS_INT8U ID,S_Msg_Q_Info *pMsg_Q_Info);
OS_EXT OS_INT8U OS_Msg_Q_Send(OS_INT8U ID,void *pMsg,OS_INT16U Msg_Len,OS_INT16U Time_Out);
OS_EXT OS_INT16U OS_Msg_Q_Rcv_Start(OS_INT8U ID,OS_INT8U **ppMsg,OS_INT16U Time_Out);
OS_EXT OS_INT16U OS_Msg_Q_Rcv_End(OS_INT8U ID);
OS_EXT void OS_Msg_Q_Info_Print(void);
#endif

#endif

