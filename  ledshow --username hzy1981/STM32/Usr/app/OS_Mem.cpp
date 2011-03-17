#define OS_MEM_C
#include "OS_Includes.h"

#if OS_MEM_EN>0

//��̬�ڳ�ʼ��
void OS_Mem_Init(void)
{
  OS_INT8U i;
  
  OS_memset((void *)&Mem_Info,0,sizeof(Mem_Info),(void *)&Mem_Info,sizeof(Mem_Info));
  OS_SET_STRUCT_HT(Mem_Info);
  for(i=0;i<OS_MEM_BLOCK_NUM;i++)
  {
    if(!((CONST OS_INT8U *)Mem_Block_Info[i].pHead<Mem_Block_Info[i].pBuf &&\
         (CONST OS_INT8U *)Mem_Block_Info[i].pBuf+Mem_Block_Info[i].Buf_Size<=(OS_INT8U *)Mem_Block_Info[i].pTail))
    {
      OS_ASSERT_FAILED();
      OS_Debug_Print("\r\nOS:Mem_Block %d Init error",i); 
    }
    
    *(Mem_Block_Info[i].pHead)=CHK_BYTE;
    *(Mem_Block_Info[i].pTail)=CHK_BYTE; 

    OS_SET_STRUCT_HT(Mem_Info.Block_Use_Info[i]);
  }
  
#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(Mem_Info);
#endif
}

//����Ƿ���>Size�Ŀ���Block,���򷵻�1��ͬʱIndex����������
OS_INT8U OS_Check_Free_Block(OS_INT8U *pIndex,OS_INT16U Size)
{
  OS_INT8U i;  
  OS_INT16U Block_Max_Size;
  OS_INT8U Size_Flag=0,Task_Flag=0;
  
  for(i=0;i<OS_MEM_BLOCK_NUM;i++)
  {
    if(OS_CHECK_STRUCT_HT(Mem_Info.Block_Use_Info[i]) EQ 0)
      OS_ASSERT_FAILED();
    
    if(Mem_Block_Info[i].Buf_Size>=Size)
    {
      Size_Flag=1;
      if(Mem_Info.Block_Use_Info[i].Use_Flag EQ 0)
      {
        *pIndex=i;
        return 1;
      }
      else if(Mem_Info.Block_Use_Info[i].Task_ID!=Task_Info.Cur_Task_ID)
        Task_Flag=1;//������һ������Ҫ���block���Ǳ���������ռ��
    }
  }
  //���еĿ��С��С��������ڴ��С
  if(0 EQ Size_Flag)
  {
    Block_Max_Size=0;
    for(i=0;i<OS_MEM_BLOCK_NUM;i++)
    {
      if(Mem_Block_Info[i].Buf_Size>Block_Max_Size)
        Block_Max_Size=Mem_Block_Info[i].Buf_Size;
    }
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Malloc error,Task %d malloc size %d exceeded the max block size %d",\
                      Task_Info.Cur_Task_ID,Size,Block_Max_Size);
    OS_Debug_Print("\r\nOS:Task %d suspend!",Task_Info.Cur_Task_ID);
    OS_Core_Wait(0);//�������
  }
  
  //���б�size����ź���������������������!
  if(0 EQ Task_Flag)
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Malloc error,Task %d malloced all the blocks that size>=%d",Task_Info.Cur_Task_ID,Size);
    OS_Mem_Info_Print();
    OS_Debug_Print("\r\nOS:Task %d suspend!",Task_Info.Cur_Task_ID);
    OS_Core_Wait(0);//�������
  }
  return 0;
}

//�����ڴ�
void *OS_malloc(OS_INT16U Size)
{
  OS_INT8U Index;
  OS_INT32U Times,Counts1;
  
  OS_Mem_Check();
  Times=0;
  Counts1=0;
  while(1)
  {
    if(OS_Check_Free_Block(&Index,Size))
      break;
    
    Times+=OS_MS_PER_TICK*5;
    if(Times/1000>=OS_MEM_WAIT_WARN_TIME)//����OS_MEM_WAIT_WARN_TIME msû�еȵ�
    {
      Counts1++;
      OS_Debug_Print("\r\nOS:Malloc error,Task %d malloc wait time out,Counts=%d",Task_Info.Cur_Task_ID,Counts1);
      OS_Mem_Info_Print();
      Times=0;
    }
    OS_TimeDly_Ms(OS_MS_PER_TICK*5);//��ʱ5��Tick
  }

  OS_Mem_Block_Check(Index);

  Mem_Info.Block_Counts++;
  if(Mem_Info.Block_Counts>Mem_Info.Block_Counts_Max)
    Mem_Info.Block_Counts_Max=Mem_Info.Block_Counts;

  if(Mem_Info.Use_Time[Index]>Mem_Info.Max_Time)
    Mem_Info.Max_Time=Mem_Info.Use_Time[Index];
  
  Mem_Info.Block_Use_Info[Index].Use_Flag=1;
  Mem_Info.Block_Use_Info[Index].Task_ID=Task_Info.Cur_Task_ID;
  Mem_Info.Use_Time[Index]=0;

#if OS_CS_EN>0
  OS_SET_STRUCT_SUM(Mem_Info);
#endif
  
  return Mem_Block_Info[Index].pBuf;
}

//�ͷ��ڴ�
void OS_free(void *p)
{
  OS_INT8U i;
  
  OS_Mem_Check();
  for(i=0;i<OS_MEM_BLOCK_NUM;i++)
  {
    if(Mem_Block_Info[i].pBuf EQ (OS_INT8U *)p)
    {
      OS_Mem_Block_Check(i);//�����ڴ����Ϣ

      if(0 EQ Mem_Info.Block_Use_Info[i].Use_Flag)//���ڴ���Ѿ��ǿ��е�
        OS_ASSERT_FAILED();
      
      Mem_Info.Block_Use_Info[i].Use_Flag=0;
      
      if(Mem_Info.Block_Counts>0)
        Mem_Info.Block_Counts--;
      else
        OS_ASSERT_FAILED();
     
      if(Mem_Info.Block_Use_Info[i].Task_ID!=Task_Info.Cur_Task_ID)//������ͷ��ڴ治����ͬһ��������
        OS_Debug_Print("\r\nOS:Task %d free mem not in the malloc task",Task_Info.Cur_Task_ID);

#if OS_CS_EN>0      
      OS_SET_STRUCT_SUM(Mem_Info);
#endif
      return;
    }
  }
  OS_ASSERT_FAILED();
  OS_Debug_Print("\r\nOS:Task %d free mem 0x%lx error,the Mem_Block dose not exist!",Task_Info.Cur_Task_ID,(OS_INT32U)p);
}

//��̬�ڴ��ʹ����Ϣ����
//IndexΪ�ڴ������
void OS_Mem_Block_Check(OS_INT8U Index)
{
  if(*(Mem_Block_Info[Index].pHead)!=CHK_BYTE)//�ڴ���ͷ����
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Mem_Block %d head check error",Index);
  }

  if(*(Mem_Block_Info[Index].pTail)!=CHK_BYTE)//�ڴ���β���� 
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Mem_Block %d tail check error",Index);
  }
  
  if(OS_CHECK_STRUCT_HT(Mem_Info.Block_Use_Info[Index]) EQ 0)//�ڴ��ʹ����Ϣ��У��ʹ���
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Mem_Block %d use info CS error",Index);
  }
  
  if(Mem_Info.Use_Time[Index]/1000>=OS_MEM_WAIT_WARN_TIME)//�ڴ�ռ��ʱ��̫������
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Task %d use Mem_Block cost too much time:%dms",\
                    Mem_Info.Block_Use_Info[Index].Task_ID,Mem_Info.Use_Time[Index]);
  }
}

//��Mem_Info�ļ���
void OS_Mem_Check(void)
{
  OS_INT8U i;
  
  if(OS_CHECK_STRUCT_HT(Mem_Info) EQ 0)//�����ڴ�ʹ����Ϣ��ͷ��β����
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Mem_Info head or tail check error");
  }

#if OS_CS_EN>0  
  if(OS_CHECK_STRUCT_SUM(Mem_Info) EQ 0)//�����ڴ�ʹ����Ϣ��ͷ��β����
  {
    OS_ASSERT_FAILED();
    OS_Debug_Print("\r\nOS:Mem_Info CS check error");
  }
#endif
  
  for(i=0;i<OS_MEM_BLOCK_NUM;i++)
    OS_Mem_Block_Check(i);
}

//�ڴ��ʹ��ʱ��ͳ��
//���Ҫʹ���ڴ��ʱ��ͳ�ƹ��ܣ���ֹ�ڴ�����Ļ����ͱ��붨ʱ���øú���������ʱ����ΪMs��������
void OS_Mem_Use_Time_Stat(OS_INT16U Ms)
{
  OS_INT8U i;
  
  for(i=0;i<OS_MEM_BLOCK_NUM;i++)
  {
    if(Mem_Info.Block_Use_Info[i].Use_Flag EQ 1)
      Mem_Info.Use_Time[i]+=Ms;//���ڴ���ʹ��ʱ������
  }
}

//��ӡ�ڴ�ʹ����Ϣ
void OS_Mem_Info_Print(void)
{
  OS_INT8U i;
  OS_INT8U Usage;
 
  OS_Debug_Print("\r\nOS:Mem_Block Use Info:");
  
  OS_Debug_Print("\r\n  Mem_Block Max used=%d, Using=%d, Total=%d, ",\
                    Mem_Info.Block_Counts_Max,Mem_Info.Block_Counts,OS_MEM_BLOCK_NUM);
    
  Usage=Mem_Info.Block_Counts_Max*100/OS_MEM_BLOCK_NUM;
  if(100<=Usage)
    OS_Debug_Print("Usage=%d",Usage/100);
  else  
    OS_Debug_Print("Usage=0.%d",Usage);
  
  for(i=0;i<(sizeof(Mem_Block_Info)/sizeof(Mem_Block_Info[0]));i++)
  {
    OS_Debug_Print("\r\n  Mem_Block %u Size=%u, Using_Flag=%u, Using Task=%u",\
      i,Mem_Block_Info[i].Buf_Size,Mem_Info.Block_Use_Info[i].Use_Flag,Mem_Info.Block_Use_Info[i].Task_ID);
    
  }
}
#endif

#undef OS_MEM_C
