#define STM32_C
#include "Includes.h"

extern void Set_Clock_Normal_Speed(void);
extern void Set_OE_Duty_Polarity(INT8U Duty, INT8U Polarity);

void Clr_Watch_Dog(void)
{

}

/** 
  * @brief  Configures the clock 
  * @param  None 
  * @retval None 
  */ 
#if HSE_VALUE EQ 25000000 //�ⲿ����Ƶ��
void RCC_Configuration(void) 
{ 
 RCC_ClocksTypeDef RCC_ClockFreq; 
 ErrorStatus HSEStartUpStatus;
   /* RCC system reset(for debug purpose) */ 
  RCC_DeInit(); 

  /* Enable HSE */ 
  RCC_HSEConfig(RCC_HSE_ON); 

  /* Wait till HSE is ready */ 
  HSEStartUpStatus = RCC_WaitForHSEStartUp(); 

  if(HSEStartUpStatus != ERROR) 
  { 
    /* Enable Prefetch Buffer */ 
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); 

 /****************************************************************/ 
 /*      HSE=25MHz, HCLK=72MHz, PCLK2=72MHz, PCLK1=36MHz         */ 
 /****************************************************************/ 
    /* Flash 2 wait state */ 
    FLASH_SetLatency(FLASH_Latency_2); 
    /* HCLK = SYSCLK */ 
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    /* PCLK2 = HCLK */ 
    RCC_PCLK2Config(RCC_HCLK_Div1); 
    /* PCLK1 = HCLK/2 */ 
    RCC_PCLK1Config(RCC_HCLK_Div2); 
    /*  ADCCLK = PCLK2/4 */ 
    //RCC_ADCCLKConfig(RCC_PCLK2_Div6); 
     /* Get HSE clock = 25MHz on PA8 pin(MCO) */ 
    //RCC_MCOConfig(RCC_MCO_HSE); 
    /* Configure PLLs *********************************************************/ 
    /* PPL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */ 
    RCC_PREDIV2Config(RCC_PREDIV2_Div5); 
    RCC_PLL2Config(RCC_PLL2Mul_8); 

    /* Enable PLL2 */ 
    RCC_PLL2Cmd(ENABLE); 

    /* Wait till PLL2 is ready */ 
    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET) 
    {} 

    /* PPL1 configuration: PLLCLK = (PLL2 / 5) * 9 = 72 MHz */ 
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5); 
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
	
	RCC->CFGR&=~0x400000;       //OTG prescale is 3, 72*2/3->48M 
    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE); 

    /* Wait till PLL is ready */ 
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) 
    {} 

    /* Select PLL as system clock source */ 
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 

    /* Wait till PLL is used as system clock source */ 
    while (RCC_GetSYSCLKSource() != 0x08) 
    {} 
  } 

  RCC_GetClocksFreq(&RCC_ClockFreq); 
#if 0
  /* Enable USART2 clock */ 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 


  /* Enable ETHERNET clock  */ 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ETH_MAC | RCC_AHBPeriph_ETH_MAC_Tx | 
                        RCC_AHBPeriph_ETH_MAC_Rx, ENABLE); 

  /* Enable GPIOs clocks */ 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | 
                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE| RCC_APB2Periph_AFIO, ENABLE); 
  /* Enable ADC1 clock */ 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 
#endif
} 
#else
/*******************************************************************************
* Function Name : RCC_Configuration     ��λʱ�ӿ�������
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
    RCC_ClocksTypeDef RCC_Clocks;
	/* system clocks configuration -----------------ϵͳʱ������-------------------*/
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();                                    //������RCC�Ĵ�������Ϊȱʡֵ
	/* Enable HSE */
#if HSE_VALUE > 16000000
	RCC_HSEConfig(RCC_HSE_Bypass);                    //�����ⲿ���پ���HSE��
#else
    RCC_HSEConfig(RCC_HSE_ON);                    //�����ⲿ���پ���HSE��
#endif	
	/* Wait till HSE is ready */ 
	//HSEStartUpStatus = RCC_WaitForHSEStartUp();    //�ȴ�HSE����
	if(RCC_WaitForHSEStartUp() == SUCCESS)               //���ɹ����񣬣�����Ϊϵͳ����ʱ�����ã�
	{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //ʹ��FLASHԤȡָ����
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);   //����FLASH�洢����ʱʱ��������(���ݲ�ͬ��ϵͳʱ��ѡȡ��ͬ��ֵ)
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);   //����AHB��Ƶϵ��Ϊ1
		RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE); //�����ⲿʱ��ΪHSE
		//_RCC_HCLKConfig(RCC_SYSCLK_Div1);   //����AHBʱ��=AHB_FREQ MHz
		RCC_PCLK1Config(PCLK1_DIV);   //����APB1ʱ��=36 MHz(APB1ʱ�����ֵ)
		RCC_PCLK2Config(PCLK2_DIV);   //����APB2ʱ��=72 MHz
		RCC_PLLCmd(DISABLE); //�ر�PLL
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, HCLK_MUL); //PLL�������伤��ǰ������ã�����PLLʱ��Դ����Ƶϵ����
		RCC_PLLCmd(ENABLE);
		// Wait till PLL is ready 
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}
		// Select PLL as system clock source 
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		// Wait till PLL is used as system clock source 
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}

	RCC_GetClocksFreq(&RCC_Clocks);
/*
  uint32_t SYSCLK_Frequency; 
  uint32_t HCLK_Frequency;   
  uint32_t PCLK1_Frequency;   
  uint32_t PCLK2_Frequency; 
  uint32_t ADCCLK_Frequency;
*/
	if(RCC_Clocks.SYSCLK_Frequency != HCLK_VALUE ||\
	   RCC_Clocks.HCLK_Frequency != HCLK_VALUE ||\
	   RCC_Clocks.PCLK1_Frequency != PCLK1_VALUE ||\
	   RCC_Clocks.PCLK2_Frequency != PCLK2_VALUE)
	{
	  ASSERT_FAILED();
	  while(1);
	}
}
#endif
//static INT8U  fac_us=0;//us��ʱ������
//static INT16U fac_ms=0;//ms��ʱ������
//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void SysTick_Configuration(void)
{
	//SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ��  HCLK/8
    if (SysTick_Config(HCLK_VALUE / 1000 * MOVE_STEP_PERIOD))     // (72MHz/1000)*SYSCLK=1MS
	{ 
	   /* Capture error */
	   ASSERT_FAILED(); 
	    while (1);
	}
}	
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void Delay_ms(INT16U nms)
{
  INT32U ms,counts = 0;

  ms = Pub_Timer.Ms;

  while(1)
  {
    if(ms != Pub_Timer.Ms)
	{
	  ms = Pub_Timer.Ms;
	  counts ++;
	  if(counts > nms + 1)
	   return;
	}
  }
} 

 
//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void Delay_us(INT32U nus)
{
  volatile INT32U i;
  volatile INT32U j; 
   
  i =0;
 
  j = 28 * nus * (HCLK_VALUE / 1000000) / 72;
  while(i <= j) 
  {
    i++;
	}
}

//secΪҪ��ʱ����
void Delay_sec(INT16U sec)
{
  INT16U i;

  sec = sec * 10;
  for(i = 0; i < sec; i ++)
  {
    Delay_ms(100);
    Clr_Watch_Dog();
  }

}

//���͵�����Ϣһ���ֽ�
void OS_Put_Char(char Data)
{
   while (!(USART2->SR & USART_FLAG_TXE));
   USART2->DR = (Data & (uint16_t)0x01FF);
}

//����һ���ֽ�ͨ������
void Com_Send_Byte(INT8U Ch, INT8U Data)
{
  if(Ch EQ CH_COM)
  {
     while (!(USART1->SR & USART_FLAG_TXE));
     USART1->DR = (Data & (uint16_t)0x01FF);
  }
  else if(Ch EQ CH_GPRS)
  {
#if GPRS_EN
     while (!(USART3->SR & USART_FLAG_TXE));
     USART3->DR = (Data & (uint16_t)0x01FF);
#else
     ASSERT_FAILED();
#endif
  }
  else if(Ch EQ CH_NET)
  {

  }
}
/*******************************************************************************
* Function Name  : SPI_FLASH_Init
* Description    : Initializes the peripherals used by the SPI FLASH driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI1_FLASH_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable SPI1 and GPIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);

  /* Configure SPI1 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure I/O for Flash Chip select */
  //PA4����Flash_CS
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
  SPI_Cmd(SPI1, DISABLE);
  /* SPI1 configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
  /* Enable SPI1  */
  SPI_Cmd(SPI1, ENABLE);
}

void SPI1_CH376_Init(void)
{
   SPI_InitTypeDef SPI_InitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;

   /* Enable SPI1 and GPIOA clocks */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);

   /* Configure SPI1 pins: NSS, SCK, MISO and MOSI */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
/*
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   //��������
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);           //CH376_CS
*/
   /* SPI1 configuration */ 
   SPI_Cmd(SPI1, DISABLE);

   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
   SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
   SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
   SPI_InitStructure.SPI_CRCPolynomial = 7;
   SPI_Init(SPI1, &SPI_InitStructure);

   /* Enable SPI1  */
   SPI_Cmd(SPI1, ENABLE);

}

/*******************************************************************************
* Function Name  : SPI_FLASH_Init
* Description    : Initializes the peripherals used by the SPI FLASH driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI2_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable SPI1 and GPIO clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

  /* Configure SPI1 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Deselect the FLASH: Chip Select high */
  //SPI_FLASH_CS_HIGH();
  //SPI_Cmd(SPI2, DISABLE);
  /* SPI1 configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
#if 1// MAX_SCAN_BLOCK_NUM == 16
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;//SPI_DataSize_8b;
#else
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
#endif
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);
  /* Enable SPI1  */
  SPI_Cmd(SPI2, ENABLE);
/*
  while(1)
  {
  SPI_I2S_SendData(SPI2, 0x55);
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
  }
*/
  SPI_I2S_SendData(SPI2, 0xFF);
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
  
  //SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
}

//SPI1��дһ�ֽ�����
INT8U SPI1_ReadWrite(INT8U writedat)
{
   /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI1, writedat);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI1);
}

//SPI2���ͽ���һ���ֽ�
INT8U SPI2_ReadWrite(INT8U writedat)
{
   /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI2, writedat);

  /* Wait to receive a byte */
  //while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  //return SPI_I2S_ReceiveData(SPI2);
  return 1;
}

void NVIC_Configuration(void)
{
    //----------�ж����ȼ�����--------

	NVIC_InitTypeDef NVIC_InitStructure = {0};
	
	/* Configure the NVIC Preemption Priority Bits */  
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	//�������ȼ����飺��ռ���ȼ�0λ,�����ȼ�4λ
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�������ȼ����飺��ռ���ȼ�2λ,�����ȼ�2λ
	
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   //������λ��FLASH
	
	
    /* Enable the USARTy Interrupt */
	//���ڽ����жϣ����ȼ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		//USART1�ж�,���ڽ���ͨ������
 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
 
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;		//USART3�ж�,���ڽ��մ���������
 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1

#if TIM1_EN
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //1ms�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
#else 	 	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //1ms�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
#endif
 /*
#ifdef CHIP_USB_HOST	
	NVIC_InitStructure.NVIC_IRQChannel = OTG_FS_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
   */
	//ɨ���ж�
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //ɨ����Ч
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	//��Ч�ж�
    NVIC_SetPriority (SysTick_IRQn, 0x0C);                //��ռ���ȼ�Ϊ1
}

//INT8U SPI2_DMA_Data[] = {0x24, 0x92, 0x49};
//INT8U SPI2_DMA_Data[] = {0x11, 0x11, 0x11, 0x11};
//INT16U SPI2_DMA_Data[] = {0x0303, 0x0303, 0x0303, 0x0303};
//INT16U SPI2_DMA_Data[] = {0x0204, 0x0810, 0x2040, 0x81FF};
//INT16U SPI2_DMA_Data[] = {0x0F0F, 0x0F0F, 0x0F0F, 0x0F0F};
//DMA��ʼ����
#if MAX_SCAN_BLOCK_NUM EQ 16
INT16U SPI2_DMA_Data[] = {0x0101, 0x0101, 0x0101, 0x0101};
void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
/*
  DMA_DeInit(DMA1_Channel5);

  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI2_DMA_Data; //��Ҫ���͵�Dma����
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 4;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel5, &DMA_InitStructure);
 */
  /* DMA1 Channel1 enable */
  //DMA_Cmd(DMA1_Channel1, ENABLE);

  DMA_DeInit(DMA1_Channel5);

  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&GPIOE->ODR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Scan_Data0[1][2]; //��ɫ������ʼ��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 8;
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

  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&GPIOD->ODR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Scan_Data0[0][2]; //��ɫ������ʼ��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 8;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel7, &DMA_InitStructure);

  /* DMA1 Channel5 enable */
  DMA_Cmd(DMA1_Channel7, ENABLE);
}
#elif MAX_SCAN_BLOCK_NUM EQ 8
INT16U SPI2_DMA_Data[] = {0x0101, 0x0101, 0x0101, 0x0101};
void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  DMA_DeInit(DMA1_Channel5);

  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&GPIOC->ODR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Scan_Data0[1][2]; //��ɫ������ʼ��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 8;
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

  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&GPIOB->ODR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Scan_Data0[0][2]; //��ɫ������ʼ��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 8;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel7, &DMA_InitStructure);

  /* DMA1 Channel5 enable */
  DMA_Cmd(DMA1_Channel7, ENABLE);
}
#elif MAX_SCAN_BLOCK_NUM EQ 4
INT16U SPI2_DMA_Data[] = {0x0303, 0x0303, 0x0303, 0x0303};
//INT8U SPI2_DMA_Data[] = {0x0
//INT8U SPI2_DMA_Data[] = {0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x81};
//INT16U SPI2_DMA_Data[] = {0x0101, 0x0101, 0x0101, 0x0101};
 void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
/*
  DMA_DeInit(DMA1_Channel5);

  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI2_DMA_Data; //��Ҫ���͵�Dma����
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 4;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel5, &DMA_InitStructure);
 */
  DMA_DeInit(DMA1_Channel7);

  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&GPIOB->ODR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Scan_Data0[0][2]; //��ɫ������ʼ��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 8;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel7, &DMA_InitStructure);

  /* DMA1 Channel5 enable */
  DMA_Cmd(DMA1_Channel7, ENABLE);
}
#endif

//��ʱ��2,���벶���ж�!!����ͨ�����½��ز���
void TIM2_Configuration(void)
{
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = 100 / 10 * (PCLK1_VALUE * 2/100000); //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =0;//(PCLK1_VALUE * 2/100000-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* Enables the Update event for TIM3 */
	//TIM_UpdateDisableConfig(TIM3,ENABLE); 	//ʹ�� TIM4 �����¼� 
	
	/* TIM IT enable */
#if TIM1_EN EQ 0
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM4
		TIM_IT_Update,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
#endif

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;// | TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM2, &TIM_ICInitStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;// | TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//TIM_ICPolarity_Falling;
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

//ɨ���ж�
void TIM3_Configuration(void)
{
    //RCC_ClocksTypeDef RCC_Clocks;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
	/* TIM4 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//RCC_GetClocksFreq(&RCC_Clocks);
	/* ---------------------------------------------------------------
	TIM4CLK ��PCLK1=36MHz
	TIM4CLK = 36 MHz, Prescaler = 7200, TIM4 counter clock = 5K,���ı�һ��Ϊ5K,���ھ�Ϊ10K
	--------------------------------------------------------------- */
	/* Time base configuration */
	//����Ϊ1ms
	TIM_TimeBaseStructure.TIM_Period = SCAN_SCREEN_PERIOD / 10; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
    TIM_TimeBaseStructure.TIM_Prescaler =(PCLK1_VALUE * 2/100000-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* Enables the Update event for TIM3 */
	//TIM_UpdateDisableConfig(TIM3,ENABLE); 	//ʹ�� TIM4 �����¼� 
	
	/* TIM IT enable */
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM4
		TIM_IT_Update,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	
	/* TIM4 enable counter */
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����

}

//101ϵ�в�����TIM1��ʱ��

//��ʱ���жϣ����ڻ��Ʊ߿�

void TIM1_Configuration(void)
{
#if TIM1_EN
    //RCC_ClocksTypeDef RCC_Clocks;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 

	TIM_TimeBaseStructure.TIM_Period = 1000; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms

#if  PCLK2_VALUE ==	HCLK_VALUE   
	TIM_TimeBaseStructure.TIM_Prescaler =(PCLK2_VALUE /1000000-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
#else
	TIM_TimeBaseStructure.TIM_Prescaler =(PCLK2_VALUE * 2 /1000000-1); 
#endif

	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM1, TIM_FLAG_Update); 
	TIM_ARRPreloadConfig(TIM1, DISABLE); 
	
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); 
	TIM_Cmd(TIM1, ENABLE);
#endif
}


//����OEռ�ձȺͼ���

//����OE-PWM���.
void TIM4_Configuration(void)
{
    //RCC_ClocksTypeDef RCC_Clocks;
 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
	TIM_OCInitTypeDef  TIM_OCInitStructure = {0};
	GPIO_InitTypeDef GPIO_InitStructure = {0};
/*
 	//----------PB0��ΪOE-PWM���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	return;
	//---------------------------
  */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��ʹ��

	//PB0�������
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	//GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//PB0��ΪOE-PWM���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	//����Ƶ��PWMƵ��=72000000/900=80Khz
	/* ---------------------------------------------------------------
	TIM3CLK ��PCLK1=36MHz
	TIM3 Configuration: generate 1 PWM signals :
    TIM3CLK = 36 MHz, Prescaler = 0x0, TIM3 counter clock = 36 MHz
    TIM3 ARR Register = 900 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
    TIM3 Frequency = 36 KHz.
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 
	TIM3CLK = 36 MHz, Prescaler = 0, TIM3 counter clock = 36MHz
	--------------------------------------------------------------- */
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = (PCLK1_VALUE * 2 / OE_PWM_FREQ / 10)/10; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* Output Compare Active Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
/*
#if TIM1_EN EQ 0	
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM4, //TIM4
		TIM_IT_Update,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
#endif
*/
	/* TIM3 enable counter */
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����

    Set_OE_Duty_Polarity(50, 0);

}

INT8U Chk_JP_Status(void)
{
  //return SELF_TEST_STATUS;
 /*
  if(CHK_JP_STATUS0 && CHK_JP_STATUS1) //�Լ�״̬
  {
    return SELF_TEST_STATUS;
  }
  else if(CHK_JP_STATUS0)
  {
	return SELF_TEST_STATUS; //�Լ�״̬
  }
  else if(CHK_JP_STATUS1)
  {
	return FAC_STATUS; //����״̬
  }
  else
    return NORMAL_STATUS;  //��������״̬
	*/

  if(CHK_FAC_JP_STATUS())
    return FAC_STATUS;
  else
    return NORMAL_STATUS;
}

void UART2_Init(void) //����2��ʼ��
{
    USART_InitTypeDef USART_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE );
  /*
	//PA3����1����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
*/	
	//PA2����1����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//����2����������Ϣ���
	USART_InitStructure.USART_BaudRate            = 115200;//Get_Com_Baud();
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx;	//ֻ������
	USART_Init(USART2, &USART_InitStructure);
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);

}

//�������������ݵĴ���
void UART3_Init(void)
{
    USART_InitTypeDef USART_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE );

	//PB11����3����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//PB10����3����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//����3�������մ���������
	USART_InitStructure.USART_BaudRate            = 9600;//Get_Com_Baud();
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);
}

//����1����232/485ͨ��
void UART1_Init(void)
{
	USART_InitTypeDef USART_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );

	//PA10����1����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PA9����1����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  	
	//����1����������ͨ��					    
	USART_InitStructure.USART_BaudRate            = Get_Com_Baud();
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE); 
}

//��ʼ������
void Com_Init(void) 
{
   UART1_Init();

//	Com_Send_Byte(CH_COM, 0x77);
//	Com_Send_Byte(CH_COM, 0x88);
}

void Soft_Rest(void) //�����λ
{
  while(1);
}

/*
typedef struct
{
  INT8U Direct; //���뷽��
  INT8U Rows; //ɨ��1��2��4��8��16ɨ
  INT8U Rows_Fold; //ÿ��������
  INT8U Cols_Fold; //ÿ��������
  INT8S Line_Order; //�����,0,+1,-1
  
  INT8U Line_Hide; //������ʱ��
  INT8U Clk_Freq; //��λʱ��Ƶ��
  INT8U Screen_Freq; //��Ļˢ��Ƶ��
  
  INT8U Data_Polarity; //���ݼ���
  INT8U OE_Polarity; //OE����
  INT8U RG_Reverse; //���̷�ת
}S_Scan_Para;
*/

//���ÿ�ʹ���ź�
void Set_Block_OE_En(INT8U Value)
{
  if(Value > 0)
    TIM_Cmd(TIM3, ENABLE);
  else
   	TIM_Cmd(TIM3, DISABLE);
}

void Unselect_SPI_Device(void)
{
  SET_FLASH_CS(1); //��ѡ��Flash
  SET_CH376_CS(1);	//��ѡ��CH376
  SET_DS1302_CS(0);	//��ѡ��DS1302

}

void RST_Periph(void)
{
  SET_RST(0);
  Delay_us(100);
  SET_RST(1);
  Delay_ms(100);
  SET_RST(0);
}

//���е������������ڴ��ļ��ж���
//������洢��
#ifndef DEF_WR_PHY_MEM
INT8U Read_PHY_Mem(INT32U Offset, void *pDst, INT16U RD_Len, void *pDst_Start, INT16U DstLen)
{
#ifdef USE_SPI_FLASH
  SPI_FLASH_BufferRead(pDst, Offset, RD_Len);
#else
#endif
  return 1;
}

//д����洢��
INT8U Write_PHY_Mem(INT32U Offset, void *pSrc, INT16U SrcLen)
{
#ifdef USE_SPI_FLASH
  SPI_FLASH_BufferWrite(pSrc, Offset, SrcLen);
#else
#endif
  return 1;
}

//���³�ʼ���ڴ�Ķ˿ڣ�SPIFlash��Ҫ���øú���
void ReInit_Mem_Port(void)
{
#ifdef USE_SPI_FLASH
  SPI1_FLASH_Init();
#else
#endif
}

//������ʾ�Ƶ���˸
void Test_LED_Flash(INT8U Counts, INT16U nms)
{
  INT8U i;

  for(i = 0; i < Counts; i ++)
  {
    SET_STATUS_LED_OFF();
	Delay_ms(nms);
	SET_STATUS_LED_ON();
	Delay_ms(nms);
  }
}

INT8U Chk_Test_Key_Up(void)
{
  INT8U i;

  for(i = 0; i < 20; i ++)
  {
	  if(CHK_TEST_KEY_STATUS())
	    break;

	  Delay_ms(1);
  }

  if(i EQ 20)
    return 1;

  return 0;

}

INT8U Chk_Test_Key_Down(void)
{
  INT8U i;

  for(i = 0; i < 20; i ++)
  {
	  if(CHK_TEST_KEY_STATUS() EQ 0)
	    break;

	  Delay_ms(1);
  }

  if(i EQ 20)
    return 1;

  return 0;
}

//����Ӳ���ļ��
void Self_Test(void)
{
  INT32U Data = 0x55AA5AA5;
  INT8U Re = 1;
  INT8U ErrFlag = 0;
  S_Time TempTime,TempTime1;

   //��ǰ�ڹ���״̬�Ұ��²��Լ�������Լ�״̬
  if(!(Chk_Test_Key_Down() && Chk_JP_Status() EQ FAC_STATUS))
    return;

  debug("-----------ϵͳ�Լ쿪ʼ---------------");
#if QT_EN EQ 0
  //--------�Դ洢���Ĳ���---------------
  Write_Storage_Data(SDI_TEST_DATA, &Data, sizeof(Data));
  Delay_ms(10);
  memset(&Data, 0x00, sizeof(Data));
  Read_Storage_Data(SDI_TEST_DATA, &Data, &Data, sizeof(Data));

  if(0x55AA5AA5 EQ Data)
  {
    debug("SPI Flash �Լ�ɹ�");
    Re = Re & 1;
  }
  else
  { 
    debug("SPI Flash �Լ�ʧ��"); 
	Re = 0;
	ErrFlag	|= 0x01;

	Test_LED_Flash(1, 500);
  }
  //-----------------------------------------

  //--------��ʱ�ӵĲ���---------------------
  
  //while(1)
  {
 // DS1302_Init();

  Re &= _Get_Cur_Time(TempTime.Time);
  Print_Cur_Time();
  Delay_sec(1);//Delay_sec(2);
  Re &=_Get_Cur_Time(TempTime1.Time);

  }
 
  if(Re > 0 && TempTime.Time[T_SEC] != TempTime1.Time[T_SEC])
  {
    debug("ʱ���Լ�ɹ�");
    Re = Re & 1;
  }
  else
  {
    debug("ʱ���Լ�ʧ��"); 
	Re = 0;
	ErrFlag	|= 0x02;

	Test_LED_Flash(2, 500);
  }
  //-----------------------------------------

  //---------��485��232�Ĳ���---------------
  Screen_Status.Rcv_Posi = 0;
  Com_Send_Byte(CH_COM, 0xA5);
  Delay_ms(5); 
  if(RCV_DATA_BUF[0] EQ 0xA5) //�Լ�ɹ�
  {
    debug("�����Լ�ɹ�");
    Re = Re & 1;
  }
  else
  {
    debug("�����Լ�ʧ��"); 
	Re = 0;
	ErrFlag	|= 0x04;

	Test_LED_Flash(3, 500);
  }
  //---------------------------------------

  if(Re EQ 0)
	debug("��Χ�����Լ�ʧ�ܣ�");
  else
	debug("��Χ�����Լ�ɹ���");

#endif
}

 //����״̬�Լ�
 void Fac_Status_Self_Test(void)
 {
  Self_Test(); //����Ӳ�����

 }

/*
//���ڲ���DMA��ʽ
//--------------------------------------------
void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  DMA_DeInit(DMA1_Channel5);

  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&GPIOD->ODR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SRC_Buffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel5, &DMA_InitStructure);

  DMA_Cmd(DMA1_Channel5, ENABLE);
}
*/

//-------------------------------------
#endif
