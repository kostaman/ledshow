#define STM32_C
#include "stm32.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_iwdg.h"
#include "LED_Cfg.h"

//extern void Set_Clock_Normal_Speed(void);


void Clr_Watch_Dog(void)
{
// IWDG_ReloadCounter();
}

/** 
  * @brief  Configures the clock 
  * @param  None 
  * @retval None 
  */ 
#if HSE_VALUE == 25000000 //�ⲿ����Ƶ��
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


void IWDG_Init(void)
{
  RCC_LSICmd(ENABLE);
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET);//�ȴ�ֱ��LSI�ȶ�
  
  if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
  {
    /* Clear reset flags */
    RCC_ClearFlag();
  }
  else
  {

  }
  /* IWDG timeout equal to 280 ms (the timeout may varies due to LSI frequency
     dispersion) */
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /* IWDG counter clock: 40KHz(LSI) / 64 = 0.625 KHz, 1.6ms */
  IWDG_SetPrescaler(IWDG_Prescaler_64);

  /* Set counter reload value to 349, 1.28S */
  IWDG_SetReload(800);

  /* Reload IWDG counter */
  IWDG_ReloadCounter();

  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();
}

//���ݼĴ�����ʼ��
void BKP_Register_Init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE); 
  /* Enable write access to Backup domain */
  PWR_BackupAccessCmd(ENABLE);

  BKP_ClearFlag();


}

uint32_t Flash_PagesMask(__IO uint32_t Size)
{
  uint32_t pagenumber = 0x0;
  uint32_t size = Size;

  if ((size % PAGE_SIZE) != 0)
  {
    pagenumber = (size / PAGE_SIZE) + 1;
  }
  else
  {
    pagenumber = size / PAGE_SIZE;
  }
  return pagenumber;

}

