#define LED_DX_DRV_C
#include "Includes.h"

#if defined(CARD_D)

#define  AFIO_MAPR      (*(volatile unsigned long *)0x40010004)//������ӳ��͵���I/O���üĴ���

 //IO�ڳ�ʼ�� -ֻ���ʼ����ȫ��ΪIO���õ����ţ��������õ���������Ӧ�Ĺ���ģ���г�ʼ��
void GPIO_Configuration()
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};  

  //AFIO_MAPR = 0x02000000; //�ͷų�����JTAG�Ŀ�,����ͨIO����  //�ͷų�����JTAG�Ŀ�,����ͨIO����  //�ͷų�����JTAG�Ŀ�,����ͨIO����
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    //-------------------IO�ڳ�ʼ��-----------------------
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //PA11Ӧ����Ϊ���������,CH376��������  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  //-----------------------------------------------
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  //PA�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_15;   
  GPIO_Init(GPIOA, &GPIO_InitStructure);

 
  //PB�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |\
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15;   
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  SET_R1(1);
  SET_R2(1);
  SET_R3(1);
  SET_R4(1);
  SET_G1(1);
  SET_G2(1);
  SET_G3(1);
  SET_G4(1);


/*
  //PB0��ΪOE-PWM���
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
   
  //PC�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6 |\
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;   
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
   //PD�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  */
  /*
  GPIO_ResetBits(GPIOA,GPIO_Pin_15);
  GPIO_SetBits(GPIOA,GPIO_Pin_15)	;
  GPIO_ResetBits(GPIOA,GPIO_Pin_15)	;
  GPIO_SetBits(GPIOA,GPIO_Pin_15)	;
  SET_G1(0);
  SET_G1(1);
  SET_G1(0);
  SET_G1(1);
  */
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



void Put_Char(char c)
{
  
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
/*
void Set_Shift_Bit(INT16U Block, INT8U RGB, INT8U Bit)
{
  
}


//������λʱ��
void Set_Shift_Bit_Clk(INT8U Value)
{
  
}





//���ÿ������ź�
void Set_Block_Latch(INT8U Value)
{
  
}
*/
void RCC_Init(void)
{
  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
}

void Gpio_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM3 channel 2 pin (PA.07) configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void Nvic_Init(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void Timer2_Init(void)
{
  /* TIM3 configuration: Input Capture mode ---------------------
     The external signal is connected to TIM3 CH2 pin (PA.07)  
     The Rising edge is used as active edge,
     The TIM3 CCR2 is used to compute the frequency value 
  ------------------------------------------------------------ */
  TIM_ICInitTypeDef  TIM_ICInitStructure;

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;// | TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM2, &TIM_ICInitStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;// | TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM2, &TIM_ICInitStructure);
    
  /* TIM enable counter */
  TIM_Cmd(TIM2, ENABLE);

  /* Enable the CC2 Interrupt Request */
  TIM_DMACmd(TIM2, TIM_DMA_CC1, ENABLE);

  TIM_DMACmd(TIM2, TIM_DMA_CC2, ENABLE);

}

INT16U Data[] = {0xFFFF, 0x7FFF, 0x0000, 0x7FFF, 0xFFFF, 0x0};

void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  /* DMA1 Channel5 Config */
  DMA_DeInit(DMA1_Channel5);

  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&GPIOD->ODR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Data;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 6;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel5, &DMA_InitStructure);

  /* DMA1 Channel5 enable */
  DMA_Cmd(DMA1_Channel5, ENABLE);

  DMA_DeInit(DMA1_Channel7);

  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&GPIOE->ODR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Data;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 6;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel7, &DMA_InitStructure);

  /* DMA1 Channel5 enable */
  DMA_Cmd(DMA1_Channel7, ENABLE);
}

void Hardware_Init(void)
{
  RCC_Init();
  Nvic_Init();
  Gpio_Init();
  Timer2_Init();
  DMA_Configuration();
  while(1);
  RCC_Configuration();

  SysTick_Configuration();
  NVIC_Configuration();

  GPIO_Configuration();

  //TIM1_Configuration();    
  TIM2_Configuration();
  TIM3_Configuration();
  TIM4_Configuration();

  UART2_Init();

  Unselect_SPI_Device(); //��ѡ���κ�һ��SPI�豸

  SPI1_FLASH_Init();

  

}
#endif
