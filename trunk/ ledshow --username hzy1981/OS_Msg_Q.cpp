#define OS_MSG_Q_C
#include "OS_Includes.h"

#if OS_MSG_Q_EN>0
//��ʼ����Ϣ����,��Ϣ��ID��Ӧ�ó����Լ��̶�
//pMsg_Q_Infoָ��һ���Ѿ���ʼ���õ�S_Msg_Q_Info���ͱ���������������Ϣ���е����ԡ��������ǰ�����Ѿ���ʼ����
//pMsg_Q_Info->pMsg���뱣֤��ֵ��һ�������λ���ϣ�������ܱ�4����
//�����ɹ�����1��ʧ�ܷ���0
OS_INT8U OS_Msg_Q_Init(OS_INT8U ID,S_Msg_Q_Info *pMsg_Q_Info)
{
  OS_INT8U i;
  S_Msg_Q_H_Info *p;
    
  if(ID>=OS_EVENT_NUM)
  {
    OS_ASSERT_FAILED();
    return 0;
  }

  /*
  //��֤��Ϣ����������ʼ��ַ��һ�������λ��
  if((OS_INT32U)pMsg_Q_Info->pMsg%4!=0)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  */
  
  //ÿ����Ϣ������ڴ��С������ڱ����Ĵ�С
  if(pMsg_Q_Info->Msg_Mem_Size<=MSG_RESERVE_SIZE)
  {
    OS_ASSERT_FAILED();
    return 0;    
  }
     
  OS_Event[ID].Type=OS_MSG_Q;
  OS_Event[ID].pData=pMsg_Q_Info;
  OS_Event[ID].Rcv_Flag=pMsg_Q_Info->Msg_Rcv_Flag;
  
  OS_SET_STRUCT_HT(OS_Event[ID]); 
  
  pMsg_Q_Info->Msg_Flag=OS_MSG_Q;  
  pMsg_Q_Info->Msg_Send_Index=0;//��������
  for(i=0;i<OS_TASK_NUM;i++)
    pMsg_Q_Info->Msg_Rcv_Index[i]=0;//��������
  
  pMsg_Q_Info->Head=CHK_BYTE;//ͷβ�������ֽ�
  pMsg_Q_Info->Tail=CHK_BYTE;

#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(OS_Event[ID]);//����У���
  OS_Set_STRUCT_Sum(pMsg_Q_Info,sizeof(S_Msg_Q_Info),pMsg_Q_Info->CS,sizeof(pMsg_Q_Info->CS));
#endif

  //��ÿ����Ϣ��Ӧ���ڴ����г�ʼ��
  for(i=0;i<pMsg_Q_Info->Msg_Max_Num;i++)
  {
    p=(S_Msg_Q_H_Info *)((OS_INT8U *)pMsg_Q_Info->pMsg+(pMsg_Q_Info->Msg_Mem_Size)*i);//��i����Ϣ��Ӧ�ڴ��ĳ�ʼλ��
    p->Head=CHK_BYTE;//��Ϣ���ͷ��β
    p->Tail=CHK_BYTE;
    p->Rcv_Flag=0; //���ձ�־����ʾ��Щ������ո���Ϣ
  #if OS_CS_EN>0
    OS_Set_STRUCT_Sum(p,sizeof(S_Msg_Q_H_Info),p->CS,sizeof(p->CS));
  #endif
    *((OS_INT8U *)p+pMsg_Q_Info->Msg_Mem_Size-1)=CHK_BYTE; //�����ڴ���β 
  }
  return 1;
}

//������Ϣ��ĳ����Ϣ������,ע��:��Ϣ�ĳ��Ȳ��ܳ�������Ϣ���е������Ϣ����,�����Ϣ����
OS_INT8U OS_Msg_Q_Send(OS_INT8U ID,void *pMsg,OS_INT16U Msg_Len,OS_INT16U Time_Out)
{
  S_Msg_Q_Info *pMsg_Q;
  S_Msg_Q_H_Info *pMsg_H;
  OS_INT32U Counts;

#if OS_CS_EN>0
  if(OS_CHECK_STRUCT_SUM(OS_Event[ID]) EQ 0)
    OS_ASSERT_FAILED();
#endif
  
  if(OS_Event[ID].Type!=OS_MSG_Q)
  {
    OS_ASSERT_FAILED();
    return 0; 
  }
  
  //pMsg_Qָ�����Ϣ���еĿ�����Ϣ��
  pMsg_Q=(S_Msg_Q_Info *)OS_Event[ID].pData;
  
  if(pMsg_Q->Head!=CHK_BYTE || pMsg_Q->Tail!=CHK_BYTE)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
#if OS_CS_EN>0
  if(OS_Check_STRUCT_Sum(pMsg_Q,sizeof(S_Msg_Q_Info),pMsg_Q->CS,sizeof(pMsg_Q->CS)) EQ 0)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
#endif
  
  //pMsg_Hָ����Ϣ�����ڴ���ͷλ��
  pMsg_H=(S_Msg_Q_H_Info *)((OS_INT8U *)(pMsg_Q->pMsg)+(pMsg_Q->Msg_Mem_Size)*(pMsg_Q->Msg_Send_Index));
  
  //�����Ϣ�ڴ��ͷ��Ϣ��ͷβУ��
  if(pMsg_H->Head!=CHK_BYTE || pMsg_H->Tail!=CHK_BYTE)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
  //�����Ϣ�ڴ��ͷ��Ϣ��У���
#if OS_CS_EN>0
  if(OS_Check_STRUCT_Sum(pMsg_H,sizeof(S_Msg_Q_H_Info),pMsg_H->CS,sizeof(pMsg_H->CS)) EQ 0)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
#endif

  //�����Ϣ�ڴ��β
  if(*((OS_INT8U *)pMsg_H+pMsg_Q->Msg_Mem_Size-1)!=CHK_BYTE)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
  //�����Ϣ�����Ƿ񳬣�
  if((Msg_Len+sizeof(S_Msg_Q_H_Info)+1)>pMsg_Q->Msg_Mem_Size)
  {
    OS_ASSERT_FAILED();
    return 0;
  }

  if(Time_Out!=0)
  {
    OS_Core_Wait_Ms(pMsg_H->Rcv_Flag EQ 0,Time_Out);//�ȴ���ǰд��Ϣ��λ��Ϊ��
    if(pMsg_H->Rcv_Flag!=0)
      return 0;
  }
  else//����ʱ�ȴ���ǰд��Ϣ��λ��Ϊ��
  {
    Counts=0;
    //Ŀǰ��������Ӧ����Ϣ�Ƿ�Ϊ�գ�Ϊ�ղ���������ڴ������Ϣ
    while(1)
    {
      OS_Core_Wait_Sec(pMsg_H->Rcv_Flag EQ 0,OS_MSG_Q_WAIT_WARN_TIME);
      if(pMsg_H->Rcv_Flag!=0)
      {
        Counts++;
        OS_Debug_Print("\r\nOS:Task %d send Msg_Q wait %d free time out,Rcv_Flag=%x,Counts=%d",\
                           Task_Info.Cur_Task_ID,ID,pMsg_H->Rcv_Flag,Counts); 
      }
      else
        break;
    }
  }
  
  //��䱾����Ϣ������
  pMsg_H->Rcv_Flag=pMsg_Q->Msg_Rcv_Flag;//���͸���Щ����?
  pMsg_H->Msg_Len=Msg_Len;
  //������Ϣ����
  OS_memcpy((OS_INT8U *)pMsg_H+sizeof(S_Msg_Q_H_Info),pMsg,Msg_Len,\
            (OS_INT8U *)pMsg_H+sizeof(S_Msg_Q_H_Info),pMsg_Q->Msg_Mem_Size-sizeof(S_Msg_Q_H_Info)-1);
  
  //����������Ϣ��д����
  pMsg_Q->Msg_Send_Index++;
  if(pMsg_Q->Msg_Send_Index>=pMsg_Q->Msg_Max_Num)
    pMsg_Q->Msg_Send_Index=0;
  
#if OS_CS_EN>0
  OS_Set_STRUCT_Sum(pMsg_H,sizeof(S_Msg_Q_H_Info),pMsg_H->CS,sizeof(pMsg_H->CS));
  OS_Set_STRUCT_Sum(pMsg_Q,sizeof(S_Msg_Q_Info),pMsg_Q->CS,sizeof(pMsg_Q->CS));  
#endif 
  
  return 1;    
}

//�ȴ�ĳ��ϢΪ��,��û����Ϣ�ڵȴ�����,Time_OutΪ��ʱʱ�䣬��λms,0Ϊ��Զ�ȴ�֪����ϢΪ�գ�>0Ϊ��ʱʱ��
//����0��ʾ�ȴ���ʱ��1��ʾ��Ϣ��Ϊ��
OS_INT16U OS_Msg_Q_Rcv_Start(OS_INT8U ID,OS_INT8U **ppMsg,OS_INT16U Time_Out)
{
  S_Msg_Q_Info *pMsg_Q;
  S_Msg_Q_H_Info *pMsg_H;
  OS_INT32U Counts;

#if OS_CS_EN>0
  if(OS_CHECK_STRUCT_SUM(OS_Event[ID]) EQ 0)
    OS_ASSERT_FAILED();
#endif
  
  if(OS_Event[ID].Type!=OS_MSG_Q)
  {
    OS_ASSERT_FAILED();
    return 0; 
  }
  
  //pMsg_Qָ�����Ϣ���еĿ�����Ϣ��
  pMsg_Q=(S_Msg_Q_Info *)OS_Event[ID].pData;

  if(pMsg_Q->Head!=CHK_BYTE || pMsg_Q->Tail!=CHK_BYTE)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
#if OS_CS_EN>0
  if(OS_Check_STRUCT_Sum(pMsg_Q,sizeof(S_Msg_Q_Info),pMsg_Q->CS,sizeof(pMsg_Q->CS)) EQ 0)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
#endif
  
  //pMsg_Hָ����Ϣ��ͷλ��
  pMsg_H=(S_Msg_Q_H_Info *)((OS_INT8U *)(pMsg_Q->pMsg)+(pMsg_Q->Msg_Mem_Size)*(pMsg_Q->Msg_Rcv_Index[Task_Info.Cur_Task_ID]));

  //��Ϣ��Ϣ���ͷ��β��ȷ?
  if(pMsg_H->Head!=CHK_BYTE || pMsg_H->Tail!=CHK_BYTE)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
#if OS_CS_EN>0
  if(OS_Check_STRUCT_Sum(pMsg_H,sizeof(S_Msg_Q_H_Info),pMsg_H->CS,sizeof(pMsg_H->CS)) EQ 0)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
#endif
 
  //��Ϣ������ȷ?
  if((pMsg_H->Msg_Len+sizeof(S_Msg_Q_H_Info)+1)>pMsg_Q->Msg_Mem_Size)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
  //��Ϣ�ڴ���β��ȷ�� 
  if(*((OS_INT8U *)pMsg_H+pMsg_Q->Msg_Mem_Size-1)!=CHK_BYTE)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
  if(Time_Out!=0)
  {
    OS_Core_Wait_Ms(OS_GET_BIT(pMsg_H->Rcv_Flag,Task_Info.Cur_Task_ID),Time_Out);//�ȴ���ǰ������������Ҫ����
    if(OS_GET_BIT(pMsg_H->Rcv_Flag,Task_Info.Cur_Task_ID) EQ 0)
      return 0;
  }
  else//����ʱ�ȴ���ֱ����������Ҫ����
  {
    Counts=0;  
    //Time_Out EQ 0������£����޵ȴ���Ϣ
    while(1)
    {
      OS_Core_Wait_Sec(OS_GET_BIT(pMsg_H->Rcv_Flag,Task_Info.Cur_Task_ID),OS_MSG_Q_WAIT_WARN_TIME);//�ȴ��������񶼿�ʼ��������
      if(OS_GET_BIT(pMsg_H->Rcv_Flag,Task_Info.Cur_Task_ID) EQ 0)
      {
        Counts++;
        OS_Debug_Print("\r\nOS:Task:%d rcv Msg_Q %d wait time out,Counts=%d",Task_Info.Cur_Task_ID,ID,Counts);
      }
      else
        break;
    }
  }

  /*
  OS_CLR_BIT(pMsg_H->Rcv_Flag,Task_Info.Cur_Task_ID);
  pMsg_Q->Msg_Rcv_Index[Task_Info.Cur_Task_ID]++;
  
#if OS_CS_EN>0
  OS_Set_STRUCT_Sum(pMsg_H,sizeof(S_Msg_Q_H_Info),pMsg_H->CS,sizeof(pMsg_H->CS));
  OS_Set_STRUCT_Sum(pMsg_Q,sizeof(S_Msg_Q_Info),pMsg_Q->CS,sizeof(pMsg_Q->CS));  
#endif
  */
  *ppMsg=(OS_INT8U *)pMsg_H+sizeof(S_Msg_Q_H_Info);
  return pMsg_H->Msg_Len;  
}

//�ȴ�ĳ��ϢΪ��,��û����Ϣ�ڵȴ�����,Time_OutΪ��ʱʱ�䣬��λms,0Ϊ��Զ�ȴ�֪����ϢΪ�գ�>0Ϊ��ʱʱ��
//����0��ʾ�ȴ���ʱ��1��ʾ��Ϣ��Ϊ��
OS_INT16U OS_Msg_Q_Rcv_End(OS_INT8U ID)
{
  S_Msg_Q_Info *pMsg_Q;
  S_Msg_Q_H_Info *pMsg_H;

#if OS_CS_EN>0
  if(OS_CHECK_STRUCT_SUM(OS_Event[ID]) EQ 0)
    OS_ASSERT_FAILED();
#endif
  
  if(OS_Event[ID].Type!=OS_MSG_Q)
  {
    OS_ASSERT_FAILED();
    return 0; 
  }
  
   //pMsg_Qָ�����Ϣ���еĿ�����Ϣ��
  pMsg_Q=(S_Msg_Q_Info *)OS_Event[ID].pData;

  if(pMsg_Q->Head!=CHK_BYTE || pMsg_Q->Tail!=CHK_BYTE)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
#if OS_CS_EN>0
  if(OS_Check_STRUCT_Sum(pMsg_Q,sizeof(S_Msg_Q_Info),pMsg_Q->CS,sizeof(pMsg_Q->CS)) EQ 0)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
#endif

 //pMsg_Hָ����Ϣ��ͷλ��
  pMsg_H=(S_Msg_Q_H_Info *)((OS_INT8U *)(pMsg_Q->pMsg)+(pMsg_Q->Msg_Mem_Size)*(pMsg_Q->Msg_Rcv_Index[Task_Info.Cur_Task_ID]));

  if(pMsg_H->Head!=CHK_BYTE || pMsg_H->Tail!=CHK_BYTE)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
    
#if OS_CS_EN>0
  if(OS_Check_STRUCT_Sum(pMsg_H,sizeof(S_Msg_Q_H_Info),pMsg_H->CS,sizeof(pMsg_H->CS)) EQ 0)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
#endif

  if((pMsg_H->Msg_Len+sizeof(S_Msg_Q_H_Info)+1)>pMsg_Q->Msg_Mem_Size)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
    
  if(*((OS_INT8U *)pMsg_H+pMsg_Q->Msg_Mem_Size-1)!=CHK_BYTE)
  {
    OS_ASSERT_FAILED();
    return 0;
  }

  OS_CLR_BIT(pMsg_H->Rcv_Flag,Task_Info.Cur_Task_ID);//����ձ�־����ʾ�����Ѿ����յ���Ϣ
  pMsg_Q->Msg_Rcv_Index[Task_Info.Cur_Task_ID]++;//��Ҫ���յ�������Ϣ������
  if(pMsg_Q->Msg_Rcv_Index[Task_Info.Cur_Task_ID]>=pMsg_Q->Msg_Max_Num)
    pMsg_Q->Msg_Rcv_Index[Task_Info.Cur_Task_ID]=0;
  
#if OS_CS_EN>0
  OS_Set_STRUCT_Sum(pMsg_H,sizeof(S_Msg_Q_H_Info),pMsg_H->CS,sizeof(pMsg_H->CS));
  OS_Set_STRUCT_Sum(pMsg_Q,sizeof(S_Msg_Q_Info),pMsg_Q->CS,sizeof(pMsg_Q->CS));  
#endif
  
  return 1;
}

//��ӡ��Ϣ���е������Ϣ
void OS_Msg_Q_Info_Print(void)
{
  OS_INT8U i,j;
  S_Msg_Q_Info *pMsg_Q;
  
  OS_Debug_Print("\r\nOS:Msg_Q Use Info:");
  
  for(i=0;i<OS_EVENT_NUM;i++)
  {
    if(OS_Event[i].Type!=OS_MSG_Q)
      continue;
  
    pMsg_Q=(S_Msg_Q_Info *)OS_Event[i].pData;
    OS_Debug_Print("\r\n  Msg_Q %d Rcv_Fag=0x%x, Send_Index=%d, Rcv_Index:",i,pMsg_Q->Msg_Rcv_Flag,pMsg_Q->Msg_Send_Index);
    for(j=0;j<OS_TASK_NUM;j++)
    {
      if(GET_BIT(pMsg_Q->Msg_Rcv_Flag,j) EQ 1)
      {
        OS_Debug_Print("\r\n  Task:%d Rcv_Inex=%d",j,pMsg_Q->Msg_Rcv_Index[j]); 
      }
    }
  }
}
#endif
#undef OS_MSG_Q_C

