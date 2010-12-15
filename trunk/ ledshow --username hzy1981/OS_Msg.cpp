#define OS_MSG_C
#include "OS_Includes.h"

#if OS_MSG_EN>0
//��Ϣ��ʼ��,��Ϣ��ID��Ӧ�ó����Լ��̶�
//ValΪ��Ϣ�ĳ�ʼֵ��1��ʾ��Դ��ռ�ã�0��ʾ��Դ���ͷ�
//�����ɹ�����1��ʧ�ܷ���0
OS_INT8U OS_Msg_Init(OS_INT8U ID)
{
  if(ID>=OS_EVENT_NUM)
  {
    OS_ASSERT_FAILED();
    return 0;
  }

  OS_Event[ID].Type=OS_MSG;
  
#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(OS_Event[ID]);//����У���
#endif

  OS_SET_STRUCT_HT(OS_Event[ID]);  
  return 1; 
}

/*
//�ȴ�ĳ��ϢΪ��,��û����Ϣ�ڵȴ�����,Time_OutΪ��ʱʱ�䣬��λms,0Ϊ��Զ�ȴ�֪����ϢΪ�գ�>0Ϊ��ʱʱ��
//����0��ʾ�ȴ���ʱ��1��ʾ��Ϣ��Ϊ��
OS_INT8U OS_Msg_Wait_Free(OS_INT8U ID,OS_INT16U Time_Out)
{
  OS_INT16U Counts;
  
  if(Time_Out!=0)
  {
    OS_Core_Wait_Ms(OS_Event[ID].Rcv_Flag EQ 0,Time_Out);//�ȴ��������񶼿�ʼ��������
    if(OS_Event[ID].Rcv_Flag!=0)
      return 0;
    else
      return 1;
  }
  
  Counts=0;
  while(1)
  {
    OS_Core_Wait_Sec(OS_Event[ID].Rcv_Flag EQ 0,OS_MSG_WAIT_WARN_TIME);
    if(OS_Event[ID].Rcv_Flag!=0)
    {
      Counts++;
      OS_Debug_Print("\r\nOS:Task %d wait msg %d free time out,Rcv_Flag=%x,Counts=%d",\
                         Task_Info.Cur_Task_ID,ID,OS_Event[ID].Rcv_Flag,Counts);        
    }
    else
      break;
  }
  return 1;
}

//����ĳ��Ϣ,���Ϸ���,���ȴ���������������,���øú���ǰ�ȵ���OS_Msg_Wait_Freeȷ����Ϣ�Ѿ�Ϊ��,��������������ǳɶ�ʹ�õ�
OS_INT8U OS_Msg_Send_NoWait(OS_INT8U ID,OS_INT16U Val,void *pMsg,OS_INT8U Rcv_Flag)
{
#if OS_CS_EN>0
  if(OS_CHECK_STRUCT_SUM(OS_Event[ID]) EQ 0)
    OS_ASSERT_FAILED();
#endif
  
  if(ID>=OS_EVENT_NUM)
  {
    OS_ASSERT_FAILED();
    return 0;
  }

  if(OS_Event[ID].Type!=OS_MSG)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
  //�ж���Ϣ�Ƿ�Ϊ�գ���Ϊ���򷵻ش���
  if(OS_Event[ID].Rcv_Flag!=0)
  {
    OS_ASSERT_FAILED();
    return 0;    
  }
  
  //����Ϣ��Ϣ����OS_Event��
  OS_Event[ID].Value=Val;
  OS_Event[ID].pData=pMsg;
  OS_Event[ID].Rcv_Flag=Rcv_Flag;
  
#if OS_CS_EN>0  
  OS_SET_STRUCT_SUM(OS_Event[ID]);
#endif
  
  return 1;  
}
*/

//������Ϣ,�ɹ�����1��ʧ�ܷ���0
//ID��ʾ��Ϣ��ID
//Val��ʾ��Ϣ��ֵ���û��Զ���������
//*pMsg��ʾָ����Ϣ��ָ��
//Rcv_Flag��ʾ���ո���Ϣ��ָ��,��NλΪ1��ʾ��N��������ո���Ϣ
//Time_Out��ʾ�ȴ���ô����룬��û�����������Ϣ�Ļ�����ʱ����
//����1��ʾ��Ϣ���ͳɹ���0��ʾʧ��
OS_INT8U OS_Msg_Send(OS_INT8U ID,OS_INT16U Val,void *pMsg,OS_INT8U Rcv_Flag,OS_INT16U Time_Out)
{
  OS_INT16U Counts;
  
  if(Time_Out!=0)
  {
    OS_Core_Wait_Ms(OS_Event[ID].Rcv_Flag EQ 0,Time_Out);//�ȴ��������񶼿�ʼ��������
    if(OS_Event[ID].Rcv_Flag!=0)
      return 0;
  }
  else//����ʱ�ȴ�֪������ϢΪ��
  {
    Counts=0;
    while(1)
    {
      OS_Core_Wait_Sec(OS_Event[ID].Rcv_Flag EQ 0,OS_MSG_WAIT_WARN_TIME);
      if(OS_Event[ID].Rcv_Flag!=0)
      {
        Counts++;
        OS_Debug_Print("\r\nOS:Task %d wait msg %d free time out,Rcv_Flag=%x,Counts=%d",\
                           Task_Info.Cur_Task_ID,ID,OS_Event[ID].Rcv_Flag,Counts);        
      }
      else
        break;
    }
  }
  
  //����Ϣ��Ϣ����OS_Event��
  OS_Event[ID].Value=Val;
  OS_Event[ID].pData=pMsg;
  OS_Event[ID].Rcv_Flag=Rcv_Flag;
  
#if OS_CS_EN>0  
  OS_SET_STRUCT_SUM(OS_Event[ID]);
#endif
  
  return 1; 
}

//������Ϣ��ʼ,�ɹ�����1��ʧ�ܷ���0���߲�����,�ú��������OS_Msg_Rcv_End�ɶ�ʹ��
//��OS_Msg_Rcv_Start��OS_Msg_Rcv_End�����������й�����,��Ϣ���ͺ����������������Ϣ��ID�Ϸ���Ϣ
//�Ӷ���������Ϣ���ᱻ����Ϣ����
OS_INT8U OS_Msg_Rcv_Start(OS_INT8U ID,OS_INT16U *pVal,OS_INT8U **ppMsg,OS_INT8U Time_Out)
{
  OS_INT16U Counts;
  
#if OS_CS_EN>0
  if(OS_CHECK_STRUCT_SUM(OS_Event[ID]) EQ 0)
    OS_ASSERT_FAILED();
#endif
  
  if(ID>=OS_EVENT_NUM)
  {
    OS_ASSERT_FAILED();
    return 0;
  }

  if(OS_Event[ID].Type!=OS_MSG)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
  if(Time_Out!=0)
  {
    OS_Core_Wait_Ms(OS_GET_BIT(OS_Event[ID].Rcv_Flag,Task_Info.Cur_Task_ID),Time_Out); 
    if(OS_GET_BIT(OS_Event[ID].Rcv_Flag,Task_Info.Cur_Task_ID) EQ 0)//����û����
      return 0;
  }
  else//����ʱ�ȴ�ֱ������Ϣ��Ҫ����
  {
    Counts=0;
    while(1)
    {
      OS_Core_Wait_Sec(OS_GET_BIT(OS_Event[ID].Rcv_Flag,Task_Info.Cur_Task_ID),OS_MSG_WAIT_WARN_TIME);
      if(OS_GET_BIT(OS_Event[ID].Rcv_Flag,Task_Info.Cur_Task_ID) EQ 0)
      {
        Counts++;
        OS_Debug_Print("\r\nOS:Task %d rcv msg %d start wait time out, Counts=%d",\
                          Task_Info.Cur_Task_ID,ID,Counts);        
      }
      else
        break;
    }
  }
  
  *ppMsg=(OS_INT8U *)OS_Event[ID].pData;//������Ϣ������ʼ��ַ
  *pVal=OS_Event[ID].Value; //������Ϣ��ֵ
  
#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(OS_Event[ID]);
#endif   
  
  return 1;  
}

//������Ϣ����,�ɹ�����1��ʧ�ܷ���0���߲����� 
//�������ź�����OS_Msg_Rcv_Flag()��OS_Msg_Proc_Flag()������������֮�䣬OS_Msg_Send()�����ǹ��𲻻᷵�ص�
//���Ҫע�����������������ڼ�ʱ�䲻Ҫ̫��
//����1��ʾ�ɹ���0��ʾʧ��
OS_INT8U OS_Msg_Rcv_End(OS_INT8U ID)
{
#if OS_CS_EN>0
  if(OS_CHECK_STRUCT_SUM(OS_Event[ID]) EQ 0)
    OS_ASSERT_FAILED();
#endif
  
  if(ID>=OS_EVENT_NUM)
  {
    OS_ASSERT_FAILED();
    return 0;
  }

  if(OS_Event[ID].Type!=OS_MSG)
  {
    OS_ASSERT_FAILED();
    return 0;
  }
  
  if(OS_GET_BIT(OS_Event[ID].Rcv_Flag,Task_Info.Cur_Task_ID) EQ 0)
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Task %d rcv msg %d end error,no message in the MSG box",Task_Info.Cur_Task_ID,ID);
  }
  
  OS_CLR_BIT(OS_Event[ID].Rcv_Flag,Task_Info.Cur_Task_ID);//��Ϣ�������
   
#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(OS_Event[ID]);
#endif 
  
   return 1;  
}

//��ӡ��Ϣ�������Ϣ
void OS_Msg_Info_Print(void)
{
  OS_INT8U i;
  
  OS_Debug_Print("\r\nOS:Msg Use Info:");
  
  for(i=0;i<OS_EVENT_NUM;i++)
  {
    if(OS_Event[i].Type!=OS_MSG)
      continue;

    OS_Debug_Print("\r\n  Msg %d Rcv_Flag=0x%x, Val=0x%x",i,OS_Event[i].Rcv_Flag,OS_Event[i].Value);
  }
}
#endif

#undef OS_MSG_C

