#define LED_CX_DRV_C
#include "Includes.h"

#if defined(CARD_C)

#define  AFIO_MAPR      (*(volatile unsigned long *)0x40010004)//������ӳ��͵���I/O���üĴ���

 //IO�ڳ�ʼ�� -ֻ���ʼ����ȫ��ΪIO���õ����ţ��������õ���������Ӧ�Ĺ���ģ���г�ʼ��
void GPIO_Configuration()
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};  

  //AFIO_MAPR = 0x02000000; //�ͷų�����JTAG�Ŀ�,����ͨIO����  //�ͷų�����JTAG�Ŀ�,����ͨIO����  //�ͷų�����JTAG�Ŀ�,����ͨIO����
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);

  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

  //-------------------IO�ڳ�ʼ��-----------------------
  //------------�����----
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //PA11ΪCh376�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //PA11Ӧ����Ϊ���������,CH376��������  
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //PC9Ϊ28J60�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //PA11Ӧ����Ϊ���������,CH376��������  
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  //------------�����----
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  //PA�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_15;   
  GPIO_Init(GPIOA, &GPIO_InitStructure);

 
  //PB�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |\
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15;   
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  //PC�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |\
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;   
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  //PD�������
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_All;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  //PE�������
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_All;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  SET_R1(1);
  SET_R2(1);
  SET_R3(1);
  SET_R4(1);
  SET_R5(1);
  SET_R6(1);
  SET_R7(1);
  SET_R8(1);
  SET_R9(1);
  SET_R10(1);
  SET_R11(1);
  SET_R12(1);
  SET_R13(1);
  SET_R14(1);
  SET_R15(1);
  SET_R16(1);

  SET_G1(1);
  SET_G2(1);
  SET_G3(1);
  SET_G4(1);
  SET_G5(1);
  SET_G6(1);
  SET_G7(1);
  SET_G8(1);
  SET_G9(1);
  SET_G10(1);
  SET_G11(1);
  SET_G12(1);
  SET_G13(1);
  SET_G14(1);
  SET_G15(1);
  SET_G16(1);

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



void Hardware_Init(void)
{
  RCC_Configuration();

  SysTick_Configuration();
  NVIC_Configuration();

  GPIO_Configuration();

  //TIM1_Configuration();    
  TIM2_Configuration();
  TIM3_Configuration();
  TIM4_Configuration();

  UART2_Init();
  UART3_Init();

  Unselect_SPI_Device(); //��ѡ���κ�һ��SPI�豸

  SPI1_FLASH_Init();

  

}

#endif
