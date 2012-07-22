#define COM_C
#include "com.h"
#include "string.h"

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
  uint16_t Sum;
  uint16_t addr;
  
  if(Frame[FHEAD] != FRAME_HEAD) //ͷ��ȷ
  {
    ASSERT_FAILED();
    return 0;
  }
  
  memcpy(&addr, &Frame[FADDR], 2);

  if(addr != 0x9999) //����֡�ĵ�ַ������0x9999
    return 0;
	 
  Len = Frame[FLEN] + (uint16_t)Frame[FLEN + 1] * 256; //֡��

  if(Len > Frame_Len || Frame[Len - 1] != FRAME_TAIL) //β��ȷ
  {
    ASSERT_FAILED();
    return 0;
  }
  
  Sum = Sum_2Bytes(Frame, Len - 3); //��3���ֽ���У��ͺ�֡β
  if(memcmp((uint8_t *)&Sum, Frame + Len - 3, 2) == 0)
    return 1;
  else
  {
    ASSERT_FAILED();
     return 0;
  }  
  
}

//����һ���ֽ�
uint8_t Rcv_Byte (uint32_t timeout)
{
  while (timeout-- > 0)
  {
	  if ( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
	  {
	    if(rcvBuf.posi >= sizeof(rcvBuf.buf))
		  rcvBuf.posi = 0;

	    rcvBuf.buf[rcvBuf.posi ++] = (uint8_t)USART1->DR;
	    return 1;
	  }
  }
  return 0;
}

//����һ֡������
void Rcv_Frame_Proc(void)
{
//  uint8_t byte;
   uint16_t i;
  //�ȴ����յ�һ���ֽ�
  while(Rcv_Byte(1) == 0);
  //�յ���һ���ֽ�֮�󣬼������գ�ֱ����ʱ�� 
  while(Rcv_Byte(0x100000) > 0);

  for(i = 0; i < rcvBuf.posi; i ++)
  {
	if(Check_Frame_Format(rcvBuf.buf + i, rcvBuf.posi - i)) //�ҵ�һ֡������
	{


	}
  }

}
