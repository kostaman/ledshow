#define STM32_C
#include "Includes.h"

void Clr_Watch_Dog(void)
{

}

//static INT8U  fac_us=0;//us��ʱ������
//static INT16U fac_ms=0;//ms��ʱ������
//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void Delay_Init(void)
{
	SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ��  HCLK/8
	//fac_us=SYSCLK/8;		    
	//fac_ms=(u16)fac_us*1000;
}	
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void Delay_ms(INT16U nms)
{	 		  	  
	INT32U temp;		   
	//SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->LOAD=(u32)nms*(SystemCoreClock / 8000000) * 1000;
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01 ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
}   
//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void Delay_us(INT32U nus)
{		
	INT32U temp;	    	 
	//SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->LOAD=nus*(SystemCoreClock / 8000000);;
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
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
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* SPI1 configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
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
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE);

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
INT8U SPI1_ReadWrite(INT8U writedat)
{
#if 0
   /* Loop while DR register in not emplty */
   while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);

   /* Send byte through the SPI1 peripheral */
   SPI_SendData(SPI1, writedat);

   /* Wait to receive a byte */
   while (SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET);

   /* Return the byte read from the SPI bus */
   return SPI_ReceiveData(SPI1);
#endif
   /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI1, writedat);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI1);
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
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		//USART1�ж�
 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1

	/* Enable the TIM2 global Interrupt */
	//ˢ���ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	/* Enable the TIM4 global Interrupt */
	//��Ч�ж�
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}

//��ʱ���жϣ�����ֱ��ɨ����
void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	
	/* ---------------------------------------------------------------
	TIM2CLK ��PCLK1=36MHz
	TIM2CLK = 36 MHz, Prescaler = 7200, TIM2 counter clock = 5K,���ı�һ��Ϊ5K,���ھ�Ϊ10K
	--------------------------------------------------------------- */
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = SCAN_SCREEN_PERIOD * 10; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =(SystemCoreClock/10000-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* Enables the Update event for TIM2 */
	//TIM_UpdateDisableConfig(TIM2,ENABLE); 	//ʹ�� TIM2 �����¼� 
	
	/* TIM IT enable */
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	
	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����

}

//��ʱ���жϣ�����ʵ����Ч����ʱ�ӱ�����ʾ���������Ƶ�������
void TIM4_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
	/* TIM4 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	
	/* ---------------------------------------------------------------
	TIM4CLK ��PCLK1=36MHz
	TIM4CLK = 36 MHz, Prescaler = 7200, TIM4 counter clock = 5K,���ı�һ��Ϊ5K,���ھ�Ϊ10K
	--------------------------------------------------------------- */
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = MOVE_STEP_PERIOD * 10; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =(SystemCoreClock/10000-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* Enables the Update event for TIM4 */
	//TIM_UpdateDisableConfig(TIM4,ENABLE); 	//ʹ�� TIM4 �����¼� 
	
	/* TIM IT enable */
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM4, //TIM4
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	
	/* TIM4 enable counter */
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����

}

//����OE-PWM���.
void TIM3_Configuration(void)
{
 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
	TIM_OCInitTypeDef  TIM_OCInitStructure = {0};
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��ʹ��

	//PB0�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//PB0��ΪOE-PWM���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
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
	TIM_TimeBaseStructure.TIM_Period = (SystemCoreClock / OE_PWM_FREQ); //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =0; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* Output Compare Active Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����

	TIM_SetCompare3(TIM3,150);	//ͨ���ı�TIM3->CCR2��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������ 
}

INT8U Chk_JP_Status(void)
{
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
void Self_Test(void)
{
  INT32U Data = 0x55AA5AA5;
  INT8U Re = 1,i,j,k, m;
  INT8U Direct;//,Rows_Fold,Cols_Fold;

  if(Chk_JP_Status() != SELF_TEST_STATUS)
    return;

  Delay_ms(10);

  if(Chk_JP_Status() != SELF_TEST_STATUS)
    return;

  //--------�Դ洢���Ĳ���---------------
  Write_Storage_Data(SDI_TEST_DATA, &Data, sizeof(Data));
  Delay_ms(10);
  Data = 0;
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
  }
  //-----------------------------------------

  //--------��ʱ�ӵĲ���---------------------

  //-----------------------------------------

  if(Re EQ 0)
	debug("��Χ�����Լ�ʧ�ܣ�");
  else
	debug("��Χ�����Լ�ɹ���");

  debug("������Ļ���״̬");

  //--------------ɨ�跽ʽ���---------------
  
  Set_RT_Show_Area(64, 32);

  while(1)
  {
    if(Chk_JP_Status() != SELF_TEST_STATUS) //�����Լ�״̬�˳�
	  break;

    for(i = 0; i < 4; i ++)
	{
	  if(i EQ 0)
	    Direct = 0x00;
      else if(i EQ 1)
	    Direct = 0x02;
	  else if(i EQ 2)
	    Direct = 0x01;
	  else
	    Direct = 0x03;

      for(j = 1; j <= MAX_ROWS_FOLD; j ++)
	  {
	    Screen_Para.Scan_Para.Rows_Fold = j;
		for(k = 1; k <= MAX_COLS_FOLD; k ++)
	    {
          Screen_Para.Scan_Para.Cols_Fold = k;
		  
		  //5��ɨ�跽ʽ������
		  for(m = 0; m < 5; m ++)
		  {
		    if(m EQ 0)
			  Screen_Para.Scan_Para.Rows = 16;  //1/16ɨ��
			else if(m EQ 1)
			  Screen_Para.Scan_Para.Rows = 8;	//1/8ɨ��
			else if(m EQ 2)
			  Screen_Para.Scan_Para.Rows = 4;	//1/4ɨ��
			else if(m EQ 3)
			  Screen_Para.Scan_Para.Rows = 2;	//1/2ɨ��
			else
			  Screen_Para.Scan_Para.Rows = 1;	//��̬ɨ��

			SET_SUM(Screen_Para);

		    LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "%2d%2d%2d%2d", m, Direct, j, k);
		    Delay_sec(2);
		  }
	    }
	   }
	 }

	 Restore_Show_Area();

  }

}

//���ÿ�ʹ���ź�
void Set_Block_OE_En(INT8U Value)
{
  if(Value > 0)
    TIM_Cmd(TIM3, ENABLE);
  else
   	TIM_Cmd(TIM3, DISABLE);
}

//���ÿ��к�
void Set_Block_Row(INT8U Row)
{
  if(Screen_Para.Scan_Para.Rows EQ 0)
  {
    Screen_Para.Scan_Para.Rows = 1;
	SET_SUM(Screen_Para);
  }

  Row = (INT8U)(((INT8S)Row + Screen_Para.Scan_Para.Line_Order) % Screen_Para.Scan_Para.Rows);
    
  SET_A((Row & 0x01));
  SET_B((Row & 0x02) >> 1);
  SET_C((Row & 0x04) >> 2);
  SET_D((Row & 0x08) >> 3);
}

//���е������������ڴ��ļ��ж���
//������洢��
#ifndef DEF_WR_PHY_MEM
INT8U Read_PHY_Mem(INT32U Offset, void *pDst, INT16U RD_Len, void *pDst_Start, INT16U DstLen)
{
  return 1;
}

//д����洢��
INT8U Write_PHY_Mem(INT32U Offset, void *pSrc, INT16U SrcLen)
{
  return 1;
}
#endif
