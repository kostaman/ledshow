#define LED_A0_DRV_C
#include "Includes.h"

#if CARD_TYPE == CARD_A0

void OS_Put_Char(char Chr)
{
  //qDebug("%c", Chr);
}

void Put_Char(char c)
{
  
}

//��ȡ��ǰʱ��
INT8U Get_Cur_Time()//S_Time *pTime)
{
  return 1;
}

//���õ�ǰʱ��
INT8U Set_Cur_Time(INT8U Time[])
{
  return 1;
}

void Mem_Init()
{

}

INT8U Read_PHY_Mem(INT32U Offset, void *pDst, INT16U RD_Len, void *pDst_Start, INT16U DstLen)
{
  return 1;
}

INT8U Write_PHY_Mem(INT32U Offset, void *pSrc, INT16U SrcLen)
{
  return 1;
}

INT16S Get_Cur_Temp()
{
  return -215; 
}


INT16U Get_Cur_Humidity()
{
  return 60; 
}

INT16U Get_Cur_Noise()
{
  return 60;
}
//������λ����
//Block��ʾ���
//RGB��ʾ��ɫ0-R��1-G��2-B
//Bit��ʾλ
void Set_Shift_Bit(INT16U Block, INT8U RGB, INT8U Bit)
{
  
}

//������λʱ��
void Set_Shift_Bit_Clk(INT8U Value)
{
  
}

//���ÿ�ʹ���ź�
void Set_Block_OE(INT8U Value)
{
  
}


//���ÿ������ź�
void Set_Block_Latch(INT8U Value)
{
  
}

//���ÿ��к�
void Set_Block_Row(INT16U Row)
{
  
}

//����ɨ�趨ʱ��,Freq��ʾɨ��Ƶ��
void Reset_Scan_Timer(INT32U Freq)
{
  
}

//��ʱus
void Delay_us(INT32U Value)
{
  
}


#endif
