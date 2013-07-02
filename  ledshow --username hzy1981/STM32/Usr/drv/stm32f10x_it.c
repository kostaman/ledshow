/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    10/15/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "usb_bsp.h"
#include "usb_hcd_int.h"
#include "usbh_core.h"
#include "includes.h"

extern USB_OTG_CORE_HANDLE          USB_OTG_Core;
extern USBH_HOST                    USB_Host;

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  static int FaultFlag = 0;
  /* Go to infinite loop when Hard Fault exception occurs */
  while (FaultFlag EQ 0)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  //volatile INT32U i = 0;

  //SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

  Show_Timer_Proc();
  //Delay_us(5);

  //GPIO_ResetBits(GPIOB,GPIO_Pin_9); //�������
  //SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief  OTG_FS_IRQHandler
  *          This function handles USB-On-The-Go FS global interrupt request.
  *          requests.
  * @param  None
  * @retval None
  */
#if UDISK_EN  //u��ʹ��
#ifdef CHIP_USB_HOST //�����ʾʹ��Ƭ��USB HOST�ӿ�
void OTG_FS_IRQHandler(void)
{
  USBH_OTG_ISR_Handler(&USB_OTG_Core);
/*
  if(Screen_Status.UDisk_Flag EQ UDISK_NULL) //��һ��ɨ�赽U��,������ٶ�ȡU��
  {
    Set_Screen_Com_Time(3); //ͨ�ŵȴ�״̬��ֹͣɨ��
    //RT_Play_Status_Enter(0);	//ʵʱ��ʾ״̬��ֹͣ��ȡ�����ļ�
  }*/
}
#endif
#endif
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval None
  */

/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */
extern void LED_Scan_One_Row(void);

void TIM3_IRQHandler(void)   //TIM3�ж�--����ɨ��
{

	//GPIOB->BSRR = GPIO_Pin_0;
	TIM_Cmd(TIM3, DISABLE);
	
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		LED_Scan_One_Row();
	}
	
	TIM_Cmd(TIM3, ENABLE);
	//GPIOB->BRR = GPIO_Pin_0;
}


#if TIM1_EN EQ 0
//���ж�Ϊ100usһ��,pwmƵ��Ϊ10k���������100us
void TIM2_IRQHandler(void)   //TIM3�ж�--100ms����
{
    //DQ_Write_0() ;  //��λ����
	//if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	if((TIM2->SR & TIM_IT_Update))
	{
		//TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		TIM2->SR = (uint16_t)~TIM_IT_Update;
		Pub_Timer_Proc();
	}

	//DQ_Write_1() ;  //��λ����
}
#else
//���ж�Ϊ1msһ��
void TIM1_UP_IRQHandler(void)   //TIM1�ж�
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
	 TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
	 Pub_Timer_Proc();
	}
}
#endif

/**
  * @brief  This function handles TIM3 global interrupt request.
  * @param  None
  * @retval None
  */
extern void Com_Rcv_Byte(u8 Ch, u8 Byte);	 
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ��� 
void USART1_IRQHandler(void)	//����1�жϷ������
{
   u8 Res;
   //STM_EVAL_LEDToggle(LED2);
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
	Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
	Com_Rcv_Byte(CH_COM, Res);
	}
}

extern void Shell_Rcv_Byte(u8 Byte);
void USART2_IRQHandler(void)	//����2�жϷ������
{
   u8 Res;
   //STM_EVAL_LEDToggle(LED2);
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
	Res =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
  	Shell_Rcv_Byte(Res);	 
	}
}

//�����ж�3���ڽ��ջ�����������
void USART3_IRQHandler(void)	//����3�жϷ������
{
}

//�����ж�4���ڽ���GPRS����
#if SMS_EN || GPRS_EN
void UART4_IRQHandler(void)	//����4�жϷ������
{
   u8 Res;
   //STM_EVAL_LEDToggle(LED2);
   if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
	 Res =USART_ReceiveData(UART4);//(USART1->DR);	//��ȡ���յ�������

	 if(SMS_GPRS_Rcv_Buf.WRPosi < sizeof(SMS_GPRS_Rcv_Buf.Buf) - 1)
	 {
       SMS_GPRS_Rcv_Buf.Buf[SMS_GPRS_Rcv_Buf.WRPosi ++] = Res;
	   SMS_GPRS_Rcv_Buf.Buf[SMS_GPRS_Rcv_Buf.WRPosi] = 0;
	 }

	 //USART2->DR = (Res & (uint16_t)0x01FF);
   
	 Clr_Watch_Dog();
     if(Chk_JP_Status() EQ FAC_STATUS) //����״̬�������ӡ������Ϣ 
	 {
	    //while (!(USART2->SR & USART_FLAG_TXE));
        USART2->DR = (Res & (uint16_t)0x01FF);
	 } 	 	 
	}
	
}
#endif
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
