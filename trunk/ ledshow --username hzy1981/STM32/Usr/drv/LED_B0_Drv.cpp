#define LED_A0_DRV_C
#include "Includes.h"

#if CARD_TYPE == CARD_B0
 //IO�ڳ�ʼ��
void GPIO_Configuration()
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};  
  
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
}
#endif
