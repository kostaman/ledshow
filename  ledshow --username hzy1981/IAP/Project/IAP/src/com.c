#define COM_C
#include "com.h"
#include "stm32.h"
#include "stm32f10x_bkp.h"
#include "string.h"
#include "LED_Cfg.h"

#define CHK_CS_BYTES 0xAAAAAAAA

#define VERSION_OFF 1000 //ԭ���������ļ��а汾������ƫ��
#define FIRMWARE_FRAME_DATA_LEN 500 //�̼�����֡���������������ݳ���
#define VERSION_FRAME_DATA_LEN 50  //�̼�����֡��һ֡���汾��Ϣ֡�����򳤶�
#define VERSION_FRAME_SUM_OFF 30   //�汾��Ϣ֡������֡У��ƫ��,2�ֽ�
#define VERSION_FRAME_FCOUNTS_OFF 34  //�汾��Ϣ֡��֡����ƫ��,2�ֽ�
#define VERSION_FRAME_BINSIZE_OFF 36  //����bin�ļ���С

const uint16_t Crc_Table0[16]={0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
                                0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef};

uint8_t comSendBuf[200]; //���ͻ�����


//CRCУ���㷨0�����ڿռ�Ƚ�С�����,���ٶ�Ҫ�󲻸ߵ����
uint16_t OS_Crc16_0(uint8_t *pSrc, uint16_t Len) 
{
  uint16_t Crc=0;
  uint8_t Temp;

  while(Len--!=0)
  {
    Temp=(uint8_t)(Crc>>12); 
    Crc<<=4; 
    Crc^=Crc_Table0[Temp^(*pSrc/16)]; 
                              
    Temp=(uint8_t)(Crc>>12); 
    Crc<<=4; 
    Crc^=Crc_Table0[Temp^(*pSrc&0x0F)]; 
    pSrc++;
  }
  return(Crc);
}

//ͨ������У��ͺ���
//pSrc��ʾ��Ҫ����У��͵����ݻ�����
//SrcLen��ʾ���ݻ���������
//pDst��ʾУ��͵���ʼ��ַ
//CS_Bytes��ʾУ��ͳ���
//pDst_Start��pDst��Χ���޶�
//DstLen��pDst��Χ���޶�,
//��Ҫ����ASSERT(A_WARNING,(uint8_t *)pDst>=(uint8_t *)pDst_Start && (uint8_t *)pDst+CS_Bytes<=(uint8_t *)pDst_Start+DstLen);
//�������Ҫ��Check_Sum�ɶ�ʹ�ã���Ϊ���ɵ�У�鲻�Ǽ򵥵�У��ͣ����ǽ����˼򵥵ı任
void OS_Set_Sum(void *pSrc,uint16_t SrcLen,void *pDst,uint8_t CS_Bytes,void *pDst_Start,uint16_t DstLen)
{
  uint32_t Sum=0;
  
  if(!(CS_Bytes EQ 1 || CS_Bytes EQ 2 || CS_Bytes EQ 4))
  {
    ASSERT_FAILED();
    return;
  }
  
  if(!((uint8_t *)pDst>=(uint8_t *)pDst_Start && (uint8_t *)pDst+CS_Bytes<=(uint8_t *)pDst_Start+DstLen))
  {
    ASSERT_FAILED();
    return;
  }

  Sum=(uint32_t)OS_Crc16_0((uint8_t *)pSrc,SrcLen);
  
  Sum=Sum^CHK_CS_BYTES;//���м򵥱任,ĳЩλȡ��,��ֹ����ȫΪ0�������У���ҲΪ0  
  memcpy(pDst,&Sum,CS_Bytes);//,pDst_Start,DstLen);
}

uint16_t Sum_2Bytes(uint8_t Src[], uint16_t SrcLen)
{
  uint16_t CS = 0;
  uint16_t i;

  for(i = 0; i < SrcLen; i ++)
  {
    CS += Src[i]; 
  }
  return CS;
}

uint8_t Check_Frame_Format(uint8_t Frame[], uint16_t Frame_Len)
{
  uint16_t Len;
  uint16_t Sum, Sum1;
  uint16_t addr;
  uint8_t ctrlCode;
  
  if(Frame[FHEAD] != FRAME_HEAD) //ͷ��ȷ
  {
    ASSERT_FAILED();
    return 0;
  }
  
  //��ַ�̶�Ϊ0x9999
  memcpy(&addr, &Frame[FADDR], 2);

  if(addr != 0x9999) //����֡�ĵ�ַ������0x9999
    return 0;
	 
  Len = Frame[FLEN] + (uint16_t)Frame[FLEN + 1] * 256; //֡��

  if(Len == 0 || Len > Frame_Len || Frame[Len - 1] != FRAME_TAIL) //β��ȷ
  {
    ASSERT_FAILED();
    return 0;
  }
  
  ctrlCode = Frame[FCMD];

  Sum = Sum_2Bytes(Frame, Len - 3); //��3���ֽ���У��ͺ�֡β
  if(ctrlCode  EQ (C_UPDATE | WR_CMD) && memcmp((uint8_t *)&Sum, Frame + Len - 3, 2) == 0)
  {
    //�ڲ�CRCУ��
    OS_Set_Sum(Frame + FDATA, Len - F_NDATA_LEN - 2, &Sum1, 2, &Sum1, sizeof(Sum1));

	if(memcmp(&Sum1, Frame + FDATA + Len - F_NDATA_LEN - 2, 2) == 0)
      return 1;
	else
	  return 0;
  }
  else
  {
    ASSERT_FAILED();
     return 0;
  }  
  
}

//����һ��֡����
void Send_Frame_Proc(uint8_t Frame[], uint16_t FrameLen)
{
  uint16_t i;

    for(i = 0; i < FrameLen; i ++)
	{
     while (!(USART1->SR & USART_FLAG_TXE));
     USART1->DR = (Frame[i] & (uint16_t)0x01FF);
      //Com_Send_Byte(Ch, Frame[i]);
   }	 
}

//����һ֡
uint16_t Make_Frame(uint8_t *pData, uint16_t Len, uint8_t Addr[], uint8_t Cmd, uint8_t Cmd0, uint8_t Seq, uint16_t Seq0, char *pDst)
{
  uint16_t sum;

  pDst[0] = FRAME_HEAD;//֡ͷ
  memcpy(pDst + FADDR, Addr, 2); //��ַ
  memcpy(pDst + FDATA, pData, Len);

  pDst[FSEQ] = Seq;
  memcpy(pDst + FSEQ0, &Seq0, sizeof(Seq0));

  pDst[FCMD] = Cmd; //�����ֽڵĿ�����
  pDst[FCMD + 1] = Cmd0;

  Len += F_NDATA_LEN; //������ + �������� = ����֡��
  memcpy(pDst + FLEN, &Len, 2);

  sum = Sum_2Bytes((uint8_t *)pDst, Len - 3); //��3���ֽ���У��ͺ�֡β
  memcpy((char *)pDst + Len - 3, (char *)&sum, 2);
  pDst[Len - 1] = FRAME_TAIL;

  return Len;
}

//����һ���ֽ�
uint8_t Rcv_Byte (uint32_t timeout)
{
  while (timeout-- > 0)
  {
      Clr_Watch_Dog();

	  if ( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
	  {
	    if(rcvBuf.posi EQ 0 && (uint8_t)USART1->DR != FRAME_HEAD)
		  return 0;

	    if(rcvBuf.posi >= sizeof(rcvBuf.buf))
		  rcvBuf.posi = 0;

	    rcvBuf.buf[rcvBuf.posi ++] = (uint8_t)USART1->DR;
	    return 1;
	  }
  }
  return 0;
}
/*
uint8_t Rcv_Frame (void)
{
  uint8_t byte;
  uint16_t len;

  while (1)
  {
      Clr_Watch_Dog();

	  if ( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
	  {
  	    byte = (uint8_t)USART1->DR;

	    if(rcvBuf.posi EQ 0 && byte != FRAME_HEAD)
		  continue;

	    if(rcvBuf.posi >= sizeof(rcvBuf.buf))
		  rcvBuf.posi = 0;


	    rcvBuf.buf[rcvBuf.posi ++] = byte;

		if(rcvBuf.posi

		if(rcvBuf.posi >= F_NDATA_LEN && rcvBuf.posi) //�յ�֡β
		{
		  if(rcvBuf.posi >

		}
	    return 1;
	  }
  }
  return 0;
}
*/

//����һ֡������
void Rcv_Frame_Proc(void)
{
   uint8_t re = 1,endFlag = 0;
   uint16_t i, j, addr;
   uint16_t seq0, len;
   uint32_t size = 0, FlashDestination, off;
   uint8_t *pRamSource;
   uint32_t waitCounts;

  uint32_t EraseCounter = 0x0;
  uint32_t NbrOfPage = 0;
  FLASH_Status FLASHStatus = FLASH_COMPLETE;

  if(BKP_ReadBackupRegister(BKP_DR3) != 0x01) //576600�����˰�
    waitCounts = HCLK_VALUE	/ 10000;
  else
    waitCounts = HCLK_VALUE * 6	/ 10000; //9600

  //�ȴ����յ�һ���ֽ�
  while(1)
  {
  while(Rcv_Byte(1) == 0) 
    Clr_Watch_Dog();
  
  //�յ���һ���ֽ�֮�󣬼������գ�ֱ����ʱ�� 
  while(Rcv_Byte(waitCounts) > 0) 
    Clr_Watch_Dog();

  for(i = 0; i < rcvBuf.posi; i ++)
  {
    Clr_Watch_Dog();
	if(Check_Frame_Format(rcvBuf.buf + i, rcvBuf.posi - i)) //�ҵ�һ֡������
	{
	  memcpy(&seq0, rcvBuf.buf + i + FSEQ0, 2); //seq0֡����ţ�1��ʾʱ��һ֡����ʱӦ�ò���flash
	  if(seq0 == 0) //��һֻ֡�洢�汾��Ϣ��bin�ļ���Ϣ
	  {
	    memcpy(&size, rcvBuf.buf + i + FDATA + VERSION_FRAME_BINSIZE_OFF, 4); //����bin�ļ���С,ǰ4���ֽ�Ϊ�ļ���С
		
        NbrOfPage = Flash_PagesMask(size); //Flash��ҳ��С

        /* Erase the FLASH pages */
        for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
        {
		  Clr_Watch_Dog();
          FLASHStatus = FLASH_ErasePage(ApplicationAddress + (PAGE_SIZE * EraseCounter));
        }
		
		re = 1;		 
	  }
	  else	 //��һ֡�Ժ��֡��������������֡
	  {
		  //��4���Լ�Ϊ�ļ�ƫ��
		  memcpy(&off, rcvBuf.buf + i + FDATA, 4); //ƫ��
		  //���������򳤶�
		  memcpy(&len, rcvBuf.buf + i + FLEN, 2);	  
		  len = len - F_NDATA_LEN - 5 - 2;  //4�ֽ�ƫ�ơ�1�ֽڽ�����־,�����2�ֽ�У��
		 
		 //������־,0xA5��ʾ�����һ֡ 
		  if(rcvBuf.buf[i + FDATA + 4] EQ 0xA5)
		    endFlag = 0xA5;
	
		  //Ŀ���ַ
		  FlashDestination = ApplicationAddress + off;	//Ŀ��Flash��ַ
		  pRamSource = rcvBuf.buf + i + FDATA + 5;  //���������ʼ��ַ
		  
		  for (j = 0;(j < len) && (FlashDestination <  ApplicationAddress + size);j += 4)
	      {
		    Clr_Watch_Dog();
	        /* Program the data received into STM32F10x Flash */
	        FLASH_ProgramWord(FlashDestination, *(uint32_t*)pRamSource);
	
	        if (*(uint32_t*)FlashDestination != *(uint32_t*)pRamSource)
	        {
			  re = 0;
	          break;//return -2;
	        }
	
	        FlashDestination += 4;
	        pRamSource += 4;
	      }
	  }

	}

	addr = 0x9999;
	if(re) //�϶�Ӧ��
	  len = Make_Frame(comSendBuf + FDATA, 0, (uint8_t *)&addr, C_UPDATE | 0x40,  0, 0, seq0, (char *)comSendBuf);
	else
	  len = Make_Frame(comSendBuf + FDATA, 0, (uint8_t *)&addr, C_UPDATE | 0x80,  0, 0, seq0, (char *)comSendBuf);
	  
	Send_Frame_Proc(comSendBuf, len); //�������ݵ�ͨ������Ӧ������

	rcvBuf.posi = 0;
	memset(rcvBuf.buf, 0, sizeof(rcvBuf.buf)); //������ջ���������

	Clr_Watch_Dog(); //�幷

	if(endFlag EQ 0xA5)	 //�ȴ����Ź���λ
	{
	  BKP_WriteBackupRegister(BKP_DR1, 0x00);
	  BKP_WriteBackupRegister(BKP_DR2, 0x00);
	  BKP_WriteBackupRegister(BKP_DR3, 0x00);

	  while(1);
	 }
  }
  }

}
