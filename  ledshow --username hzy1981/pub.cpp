#define PUB_C
#include "Includes.h"

CONST INT16U Crc_Table0[16]={0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
                                0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef};

CONST INT16U Crc_Table1[256]={ 
  0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
  0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
  0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
  0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
  0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
  0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
  0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
  0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
  0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
  0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
  0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
  0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
  0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
  0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
  0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
  0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
  0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
  0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
  0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
  0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
  0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
  0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
  0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
  0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
  0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
  0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
  0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
  0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
  0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
  0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
  0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
  0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0};

//����format��ap���������������Ϣ
void vsPrintf(CONST INT8S *format, va_list ap)
{
  
  static CONST INT8S Chr[]="0123456789ABCDEF";

  static CONST INT32U Oct[12]=
  {
    01,010,0100,01000,010000,0100000,01000000,010000000,
    0100000000,01000000000,010000000000,010000000000,
  }; //�˽���
  static CONST INT32U Dec[11]=
  {
    1,10,100,1000,10000,100000,1000000,
    10000000,100000000,1000000000,1000000000,
  }; //ʮ����
  static CONST INT32U Hex[8]=
  {
    0x1,0x10,0x100,0x1000,0x10000,
    0x100000,0x1000000,0x10000000,
  }; //ʮ������
  
  INT8U LintFlag;
  INT32U CONST *p;
  INT8S *pSrc;
  
  unsigned long int uParaValue;//�޷�����
  long int sParaValue;//�з�����
  
  INT8U c;
  INT8U i,Width,Len;
 
  for(;;)    //��������������
  {
    while((c=*format++)!='%')//%����֮ǰȫ���ַ���
    {
      if(!c)
        return;
      Put_Char(c);
    }

    c=*format++;
    //����ֵ���ʹ���
    switch(c)
    {
      case 'c':
        c = va_arg(ap, int);
        Put_Char(c);
        break;
      case 's':
        pSrc= va_arg(ap,INT8S *);
        while((c = *pSrc++)!=0)
          Put_Char(c);
        break;
      default:
        break;
    }
    
    //��ֵ���ʹ���
    if(c>='1' && c<='9')
    {
      Width=c-'0';
      c=*format++;
    }
    else
      Width=1;//���ٴ�ӡһ���ַ�
    
    if(c EQ 'l' || c EQ 'L')//�Ƿ���һ��������?
    {
      LintFlag=1;
      c=*format++;
    }
    else
      LintFlag=0;
    
    switch(c)//��ӡ��������
    {
      case 'o':
        p=Oct;
        Len=12;
        break;
      case 'd':
      case 'u':
        p=Dec;
        Len=11;
        break;
      case 'x':
        p=Hex;
        Len=8;
        break;

      default:
        continue;
    }
    
    //��ȡ������ֵ
    if(c EQ 'd')//�з�����
    {
      if(LintFlag)//������
        sParaValue=va_arg(ap,long int);
      else
        sParaValue=va_arg(ap,int);
      
      if(sParaValue<0)
      {
        Put_Char('-');
        sParaValue=0-sParaValue;
      }
      uParaValue=(unsigned long int)sParaValue;//��ֵ��uParaValue,ͳһ����
    }
    else//�޷�����
    {
      if(LintFlag)//������
        uParaValue=va_arg(ap,unsigned long int);
      else
        uParaValue=va_arg(ap,INT16U);  
    }
    
    //�������ݱ���ĳ���
    for(i=0;i<Len;i++)
    {
       if(uParaValue<*(p+i))
         break;
    }
    
    if(Width<i)//i��ʾ���ݱ����ȣ�Width��ʾ��Ҫ��ӡ�ĳ���
      Width=i;
    
    //�ֱ��ӡÿ���ַ�
    i=0;//��ʾ�Ƿ��Ѿ��ҵ���һ����0λ
    for(;Width!=0;Width--)
    {
      c=(INT8U)(uParaValue/(*(p+Width-1)));
      uParaValue=uParaValue%(*(p+Width-1));
      //ǰ���0ȫ����ɿո�

      if(c EQ 0 && i EQ 0 && Width>1)//��λΪ0����֮ǰ��λҲ��Ϊ0,�Ҳ������һλ(��ֵ����Ϊ0)
        c=' ';
      else
      {
        i=1;//��ʾ�Ѿ���һ����0λ��
        c=Chr[c];
      }
      Put_Char(c);
    }
  }
}

//������Ϣ�������
//ע��Ŀǰֻ֧��%c,%s,%d,%u,%o,%x���ݲ�֧�ָ�����
void _Debug_Print(CONST INT8S *format, ...)
{
  va_list ap;
  
  va_start(ap,format);
  vsPrintf(format,ap);
  va_end(ap);
}

INT8U Debug_Print_En(void)
{
    return 1;
}

//������Ϣ�������
//ע��Ŀǰֻ֧��%c,%s,%d,%u,%o,%x���ݲ�֧�ָ�����
//�ú�����ֻ����Debug_Print_En()����>0ʱ�����
void Debug_Print(CONST INT8S *format, ...)
{
  va_list ap;
  
  if(Debug_Print_En() EQ 0)
    return;
  
  va_start(ap,format);
  vsPrintf(format,ap);
  va_end(ap);
}

#if TRACE_HOOK_EN>0
extern void Trace_Hook(void);
void _Trace_Hook(void)
{
  INT8U Temp;
  
  Temp=Trace_Info.On_Off_Flag;
  Trace_Ctrl(0);//�ر����������Trace���ܣ�ʹTrace_Hook���������������
  Trace_Hook();
  Trace_Ctrl(Temp);
}
#endif

//�켣���ٺ�������ڲ���File�����Ѿ����������������TRACE_BUF_LEN���ַ�
void Trace0(CONST INT8S File[],CONST INT8S Function[],INT16U Line)
{ 
  //��¼�µ��˵��õĺ���
  //�ôε��ú��ϴε��õ��кŲ����,�������ε��õĺ������ֲ�һ��,���߲�����ͬһ��������,��Ϊ�����β�ͬ�ĵ���
  if(Trace_Info.Line[Trace_Info.Index]!=Line ||\
     strcmp(Trace_Info.File[Trace_Info.Index],File)!=0)
  {
    Trace_Info.Index++;
    if(Trace_Info.Index>=TRACE_NUM)
      Trace_Info.Index=0;
    
    //��¼��ǰ�����,���к�
    Trace_Info.Task_ID[Trace_Info.Index]=0;//Task_Info.Cur_Task_ID;//��������ID
    //��¼�ļ���
    memcpy(Trace_Info.File[Trace_Info.Index],File,TRACE_BUF_LEN-1);//��¼�¸ôε��õĺ�������
    //���һ���ַ���0
    Trace_Info.File[Trace_Info.Index][TRACE_BUF_LEN-1]='\0';
    //��¼������
    memcpy(Trace_Info.Func,Function,TRACE_BUF_LEN-1);//��¼�¸ôε��õĺ�������
    //���һ���ַ���0
    Trace_Info.Func[TRACE_BUF_LEN-1]='\0';  
    
    Trace_Info.Line[Trace_Info.Index]=Line;//�����к�
    Trace_Info.Counts[Trace_Info.Index]=1;//���ô���

  }
  else
  {
    if(Trace_Info.Index>=TRACE_NUM)
      Trace_Info.Index=0;    
    Trace_Info.Counts[Trace_Info.Index]++;//��Ϊ�ڷ�������ͬһ�����������ӵ��ô����ļ�¼
  } 
}

//����ϵͳ�Ĺ켣���ٺ�����File��ʾ�ļ�����Line��ʾ�к�
void Trace(CONST INT8S File[],CONST INT8S Function[],INT16U Line)
{
  INT16U Len;
  INT8S *pFile;

  //�켣���ܹر�����¼�¼��������
#if TRACE_CTRL_EN>0
  if(GET_BIT(Trace_Info.On_Off_Flag,0) EQ 0)
    return;   
#endif

  //Flag=1��ʾ�Ѿ���Trace�������ˣ���ֹ�ظ�����
  if(Trace_Info.Entry_Flag EQ 1)
  {
    Debug_Print("\r\nOS:Trace Reentry!");
    return;    
  }
  
  Trace_Info.Entry_Flag=1;//��ʾ�Ѿ����룬���²��ֲ������� 
  
  Len=strlen((INT8S *)File)+1;
  
  if(Len>TRACE_BUF_LEN)
    pFile=(INT8S *)File+Len-TRACE_BUF_LEN;//ȡ�ļ�������ʼλ��
  else
    pFile=(INT8S *)File;
  
  Trace0(pFile,Function,Line);
  
#if TRACE_HOOK_EN>0  
  _Trace_Hook();//���ù��Ӻ���
#endif

  //Entry_Flag=0��ʾ�˳�Trace����
  Trace_Info.Entry_Flag=0;   
}

//�켣��¼�򿪹رյĿ��ƹ���
void Trace_Ctrl(INT32U Flag)
{
  Trace_Info.On_Off_Flag=Flag;//�򿪻��߹رն��ԣ�ÿλ��Ӧһ������
}

//���Trace_Info��Ϣ�Ƿ��������
void Trace_Info_Check(void)
{
  if(CHECK_STRUCT_HT(Trace_Info) EQ 0)
  {
    ASSERT_FAILED();
    Debug_Print("\r\nOS:Trace_Info HT error");
  }
}

//��ӡ�������ù켣
void Print_Trace_Info(void)
{
  INT8U i, Index;
  //��ӡǰ���ε��õĺ���
  if(Trace_Info.Index>=TRACE_NUM)
  {
    Debug_Print("\r\nOS:Trace Index error %d",Trace_Info.Index);
    Trace_Info.Index=0;
  }

  Debug_Print("\r\nOS:Trace_Info:");
  
  Index=Trace_Info.Index; //���һ�ε�����Ϣ����   
  for(i=0;i<TRACE_NUM;i++)//��ӡ��ǰTRACE_NUM�ε��õĺ���
  {
    Trace_Info.File[Index][TRACE_BUF_LEN-1]=0;
    
    Debug_Print("\r\n  Call:Task:%u,File:%s,Func:%s,Line:%u,Counts:%u",\
      Trace_Info.Task_ID[Index],\
      Trace_Info.File[Index],\
      Trace_Info.Func,\
      Trace_Info.Line[Index],\
      Trace_Info.Counts[Index]);
    //ǰһ�ε�����Ϣ
    if(Index EQ 0)
      Index=TRACE_NUM-1;
    else
      Index--;
  }  
}

#if ASSERT_HOOK_EN>0
extern void Assert_Hook(CONST INT8S File[],CONST INT8S Function[],INT16U Line);
#endif

//����ʧ��ʱ�������Ϣ
//File�������ڵ��ļ�
//Function�������ڵĺ���
//Line�������ڵ��к�
void Assert_Failed(CONST INT8S File[],CONST INT8S Function[],INT16U Line)
{
  INT16U Len;
  INT8S *pFile;
  
  Len=strlen((INT8S *)File)+1;
    
  if(Len>TRACE_BUF_LEN)
    pFile=(INT8S *)File+Len-TRACE_BUF_LEN;//ȡ�ļ�������ʼλ��
  else
    pFile=(INT8S *)File;
 /* 
  //��ӡ�������ֻ���ID
#if TASK_NAME_EN>0    
  Debug_Print("\r\nASSERT Task Name:%s",Tcb[Task_Info.Cur_Task_ID].Name);
#else
  Debug_Print("\r\nASSERT Task ID:%u",Task_Info.Cur_Task_ID);
#endif
*/
  //��ӡ�����ļ�
  Debug_Print("\r\n  Err File:%s,Function:%s,Line:%u",pFile,Function,Line); 
  
  //��ӡ�������ù켣
#if TRACE_EN>0  
  Print_Trace_Info();
#endif
  
#if ASSERT_HOOK_EN>0
  Assert_Hook(pFile,Function,Line);
#endif  

}

//�������
//Condition��ʾ����
//File�������ڵ��ļ�
//Function�������ڵĺ���
//Line�������ڵ��к�
//���أ���������Ϊ1��������Ϊ0
//ע�⣺�ú����ڲ����ܵ��ò���ϵͳ�ĵ��ã���������ʱ������
void Assert(BOOL Condition,CONST INT8S File[],CONST INT8S Function[],INT16U Line)
{
  if(Condition EQ 0)
  {
    Assert_Failed(File,Function,Line);
  }
}

//memcpy����
//pDst��ʾĿ�껺����
//pSrc��ʾԴ������
//SrcLen��ʾ��������
//pDst_Start��DstLenһ������pDst��SrcLen�ķ�Χ
//��������ASSERT(A_WARNING,(INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+SrcLen<=(INT8U *)pDst_Start+DstLen);
void mem_cpy(void *pDst,void *pSrc,INT32U SrcLen,void *pDst_Start,INT32U DstLen)
{
  if(!((INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+SrcLen<=(INT8U *)pDst_Start+DstLen))//pDst�������������
  {
    ASSERT_FAILED();
    return;
  }
  memcpy(pDst,pSrc,SrcLen);
}

//memset����
//pDst��ʾĿ�껺����
//Value��ʾ��Ҫ���õ�ֵ
//SetLen��ʾ��������
//pDst_Start��DstLenһ������pDst��SetLen�ķ�Χ
//��������ASSERT(A_WARNING,(INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+SetLen<=(INT8U *)pDst_Start+DstLen);
void mem_set(void *pDst, INT8U Value,INT32U SetLen,void *pDst_Start,INT32U DstLen)
{
  if(!((INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+SetLen<=(INT8U *)pDst_Start+DstLen))//pDst�������������
  {
    ASSERT_FAILED();
    return;
  }
  memset(pDst,Value,SetLen);
}


//CRCУ���㷨0�����ڿռ�Ƚ�С�����,���ٶ�Ҫ�󲻸ߵ����
INT16U Crc16_0(INT8U *pSrc, INT16U Len) 
{
  INT16U Crc=0;
  INT8U Temp;

  while(Len--!=0)
  {
    Temp=(INT8U)(Crc>>12); 
    Crc<<=4; 
    Crc^=Crc_Table0[Temp^(*pSrc/16)]; 
                              
    Temp=(INT8U)(Crc>>12); 
    Crc<<=4; 
    Crc^=Crc_Table0[Temp^(*pSrc&0x0F)]; 
    pSrc++;
  }
  return(Crc);
}

//CRCУ���㷨1�����ڿռ�Ƚϴ�����,���ٶ�Ҫ��ϸߵ����
INT16U Crc16_1(INT8U *pSrc, INT16U Len)
{
  INT16U Crc=0;
  INT16U Temp;
  
  while(Len--!=0)
  {
    Temp=Crc;
    Crc=Crc_Table1[(Temp>>8)^*pSrc++];
    Crc=Crc^(Temp<<8);
  }
  return(Crc);
}

//ͨ�ü��У��ͺ���
//pSrc��ʾ��Ҫ�������ݻ�����
//SrcLen��ʾ���ݻ���������
//pCS��ʾУ��͵���ʼ��ַ
//CS_Bytes��ʾУ��ͳ���
//ע�⣺�������Ҫ��Set_Sum�ɶ�ʹ�ã���Ϊ�ڲ����Ǽ���򵥵�У���
INT8U Check_Sum(void *pSrc,INT16U SrcLen,void *pCS,INT8U CS_Bytes)
{
  INT32U Sum=0;
  
  if(!(CS_Bytes EQ 1 || CS_Bytes EQ 2 || CS_Bytes EQ 4))//�ֽ���������1��2��4
  {
    ASSERT_FAILED();
    return 0;
  }
  
#if CS_TYPE EQ CS_CRC16_0
  Sum=(INT32U)Crc16_0((INT8U *)pSrc,SrcLen);
#elif CS_TYPE EQ CS_CRC16_1
  Sum=(INT32U)Crc16_1((INT8U *)pSrc,SrcLen);
#else
  while(SrcLen--!=0)
  {
    Sum+=*((INT8U *)pSrc+SrcLen);
  }
#endif

  Sum=Sum^CHK_CS_BYTES;//���м򵥱任,ĳЩλȡ��,��ֹ����ȫΪ0�������У���ҲΪ0 
  if(memcmp(&Sum,pCS,CS_Bytes) EQ 0)
    return 1;
  else
    return 0;
}

//ͨ������У��ͺ���
//pSrc��ʾ��Ҫ����У��͵����ݻ�����
//SrcLen��ʾ���ݻ���������
//pDst��ʾУ��͵���ʼ��ַ
//CS_Bytes��ʾУ��ͳ���
//pDst_Start��pDst��Χ���޶�
//DstLen��pDst��Χ���޶�,
//��Ҫ����ASSERT(A_WARNING,(INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+CS_Bytes<=(INT8U *)pDst_Start+DstLen);
//�������Ҫ��Check_Sum�ɶ�ʹ�ã���Ϊ���ɵ�У�鲻�Ǽ򵥵�У��ͣ����ǽ����˼򵥵ı任
void Set_Sum(void *pSrc,INT16U SrcLen,void *pDst,INT8U CS_Bytes,void *pDst_Start,INT16U DstLen)
{
  INT32U Sum=0;
  
  if(!(CS_Bytes EQ 1 || CS_Bytes EQ 2 || CS_Bytes EQ 4))
  {
    ASSERT_FAILED();
    return;
  }
  
  if(!((INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+CS_Bytes<=(INT8U *)pDst_Start+DstLen))
  {
    ASSERT_FAILED();
    return;
  }

#if CS_TYPE EQ CS_CRC16_0
  Sum=(INT32U)Crc16_0((INT8U *)pSrc,SrcLen);
#elif CS_TYPE EQ CS_CRC16_1
  Sum=(INT32U)Crc16_1((INT8U *)pSrc,SrcLen);
#else
  while(SrcLen--!=0)
  {
    Sum+=*((INT8U *)pSrc+SrcLen);
  }
#endif 
  
  Sum=Sum^CHK_CS_BYTES;//���м򵥱任,ĳЩλȡ��,��ֹ����ȫΪ0�������У���ҲΪ0  
  mem_cpy(pDst,&Sum,CS_Bytes,pDst_Start,DstLen);
}

//���ĳ���ṹ���У����Ƿ���ȷ,�ýṹ��Ķ�������������·�ʽ
//
//typedef struct{
//     ...
//     ...
//     INT8U CS[CS_BYTES];//���һ���������У��ͣ��ҳ���ΪCS_BYTES
//    }sturct_name;
//
//pSrcΪ�ṹ���������ʼָ��
//SrcLenΪ�ṹ���������
//CSΪ�ṹ�������У���,ע��ñ�������Ϊ�ṹ���е�һ����
//ע�⣺�������Ҫ��Set_STRUCT_Sum�ɶ�ʹ�ã���ΪУ������㷨һ��
INT8U Check_STRUCT_Sum(void *pSrc,INT16U SrcLen,INT8U *pCS,INT8U CS_Bytes)
{
  INT16U Len;
  
  if(!(pCS>(INT8U *)pSrc && pCS+CS_Bytes<=(INT8U *)pSrc+SrcLen))//�ж�CS��λ���Ƿ�Ϸ�
  {
    ASSERT_FAILED();
    return 0;
  }
  
  Len=(INT16U)((INT8U *)pCS-(INT8U *)pSrc);//������Ҫ����У��͵����ݳ���
  return Check_Sum(pSrc,Len,pCS,CS_Bytes);
}

//���ýṹ�������У���,�ýṹ��Ķ�������������·�ʽ
//
//typedef struct{
//     ...
//     ...
//     INT8U CS[CS_BYTES];//���һ���������У��ͣ��ҳ���ΪCS_BYTES
//    }sturct_name;
//
//pSrcΪ�ṹ���������ʼָ��
//SrcLenΪ�ṹ���������
//CSΪ�ṹ�������У���,ע��ñ�������Ϊ�ṹ���е�һ����
//ע�⣺�������Ҫ��Check_STRUCT_Sum�ɶ�ʹ�ã���ΪУ������㷨һ��
void Set_STRUCT_Sum(void *pSrc,INT16U SrcLen,INT8U *pCS,INT8U CS_Bytes)
{
  INT16U Len;

  if(!(pCS>(INT8U *)pSrc && pCS+CS_Bytes<=(INT8U *)pSrc+SrcLen))//�ж�CS��λ���Ƿ�Ϸ�
  {
    ASSERT_FAILED();
    return;    
  }
  
  Len=(INT16U)((INT8U *)pCS-(INT8U *)pSrc);//������Ҫ����У��͵����ݳ���
  Set_Sum(pSrc,Len,pCS,CS_Bytes,pSrc,SrcLen);
}

INT16U Sum_2Bytes(INT8U Src[], INT16U SrcLen)
{
  INT16U CS = 0;
  INT16U i;

  for(i = 0; i < SrcLen; i ++)
  {
    CS += Src[i]; 
  }
  return CS;
}

#undef PUB_C
