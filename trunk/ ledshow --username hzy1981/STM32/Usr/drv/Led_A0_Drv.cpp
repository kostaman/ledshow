#define LED_A0_DRV_C
#include "Includes.h"

#if CARD_TYPE == CARD_A0

#if 0
void RCC_Configuration()
{
  //------������ʱ��1��2-----------
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_ALL, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ALL, ENABLE);  
}

void NVIC_Configuration()
{
 //----------�ж����ȼ�����--------
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the USARTz Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
}

void GPIO_Configuration()
{
  GPIO_InitTypeDef GPIO_InitStructure;  
  


  //-------------------IO�ڳ�ʼ��-----------------------
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //PA�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 |\
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_12;   
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  //PB�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |\
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15;   
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  //PC�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6 |\
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;   
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
   //PD�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  
}

void Timer_Configuration()
{
  //uint16_t PrescalerValue = 0;
  TIM_TimeBaseInitTypeDef timInitStruct;

  //�����Ĭ��Ϊ����ڻ��ض����ܿ�
  //----------IO �ڳ�ʼ�����---------------//

 
  /* ---------------------------------------------------------------
    TIM2 Configuration: Output Compare Timing Mode:
    TIM2 counter clock at 6 MHz
    CC1 update rate = TIM2 counter clock / CCR1_Val = 146.48 Hz
    CC2 update rate = TIM2 counter clock / CCR2_Val = 219.7 Hz
    CC3 update rate = TIM2 counter clock / CCR3_Val = 439.4 Hz
    CC4 update rate = TIM2 counter clock / CCR4_Val = 878.9 Hz
  --------------------------------------------------------------- */

  /* Compute the prescaler value */
  //PrescalerValue = (uint16_t) (SystemCoreClock / 12000000) - 1;

  /* Time base configuration */
  timInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;   // ��ʱ����׼Ƶ��72MHz
  timInitStruct.TIM_Prescaler = 32000;                    // ����Ƶ��Ϊ1KHz
  timInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���
  timInitStruct.TIM_RepetitionCounter = 0;
  timInitStruct.TIM_Period = 0; // ���ֵʵ���Ͼ���TIMX->ARR����ʱ��ʼʱ�����趨����
  
  TIM_TimeBaseInit(TIM2, &timInitStruct);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // �������ʱ�����ж�
  TIM_Cmd(TIM2, DISABLE);



  TIM_TimeBaseInit(TIM2, &timInitStruct);  
}
#endif

void SPI1_Init(void)
{
   SPI_InitTypeDef SPI_InitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;

   /* Enable SPI1 and GPIOA clocks */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOD, &GPIO_InitStructure);

   /* Configure SPI1 pins: NSS, SCK, MISO and MOSI */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   //��������
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);           //CH376_CS

   /* SPI1 configuration */ 
   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
   SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
   SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
   SPI_InitStructure.SPI_CRCPolynomial = 7;
   SPI_Init(SPI1, &SPI_InitStructure);

   /* Enable SPI1  */
   SPI_Cmd(SPI1, ENABLE);
}

//SPI1��дһ�ֽ�����
unsigned char SPI1_ReadWrite(unsigned char writedat)
{
   /* Loop while DR register in not emplty */
   while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);

   /* Send byte through the SPI1 peripheral */
   SPI_SendData(SPI1, writedat);

   /* Wait to receive a byte */
   while (SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET);

   /* Return the byte read from the SPI bus */
   return SPI_ReceiveData(SPI1);
}
/*
//GPIO��ʼ��
void GPIO_Init()
{
  
}

//SPI��ʼ��
void SPI_Init()
{
  
}

//UART��ʼ��
void UART_Init()
{
  
}
*/

//CPU
void Hardware_Init(void)
{



  
}

void OS_Put_Char(char Chr)
{
  //qDebug("%c", Chr);
}

void Put_Char(char c)
{
  
}

//��ȡ��ǰʱ��
INT8U Get_Cur_Time(void)//S_Time *pTime)
{
  return 1;
}

//���õ�ǰʱ��
INT8U Set_Cur_Time(INT8U Time[])
{
  return 1;
}

//�洢����ʼ��
void Mem_Init(void)
{

}

//��ȡ��ǰ�¶�
INT16S Get_Cur_Temp(void)
{
  return -215; 
}

//��ȡ��ǰʪ��
INT16U Get_Cur_Humidity(void)
{
  return 60; 
}

//��ȡ��ǰ����
INT16U Get_Cur_Noise(void)
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