#ifndef LED_CX_CFG_H
#define LED_CX_CFG_H
						 
//#define CARD_SUB_B0 0x00
//#define CARD_SUB_B1 0x01
//#define CARD_SUB_B2 0x02

//#define CARD_SUB_TYPE CARD_SUB_B0 //BXϵ���ӿ�����

 //-------------------ʱ���������---------------
#define HSE_VALUE 25000000 //�ⲿ����Ƶ��
#define HCLK_VALUE  72000000
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_9	//��������ʱAHB�ٶ�
#define PCLK1_DIV RCC_HCLK_Div2 //���APB/2--������������ʱ�ٶ�,���ﲻ��ΪDIV1����Ϊ��ʱ��ʹ�õķ�Ƶϵ��Ĭ��PCLK1��Ƶ>1
#define PCLK2_DIV RCC_HCLK_Div1 //��ߺ�AHBһ��,ע��SPIFlash���ٶ���APB2/2���ܳ���50M,CH376���ٶ���APB2/8���ܳ���24M

#define TIM1_EN 1
//----------------------------------------
#if defined(CARD_C)
#define CARD_NAME "C"  //������
#else
#error "card CX name error"
#endif

#define SCAN_SCREEN_PERIOD 100//ɨ������,��λus
#define MOVE_STEP_PERIOD 5//5 //�ƶ�����ʱ��,��λΪms
#define MOVE_STEP 1 //ÿ�����ȵ�λ�ƶ������ݰٷֱ� ��λ%

#define IN_SPEC_EFFECT_NUM 53 //������Ч����
#define OUT_SPEC_EFFECT_NUM 22 //�˳���Ч����
#define FONT_NUM 1 //��Ƕ�������

//----���ݲ�ͬ����Ļ��Ӳ������������Ŀ
#define MAX_POINTS (744*64) //������--�˴���˫ɫ��������������ɫ���ĵ����ڴ˻�����*2
#define MAX_STORA_BLOCK_NUM  4000 //���洢����
#define MAX_SCAN_BLOCK_NUM 8 //���ɨ���
#define MAX_SCAN_WIDTH 2056 //���ɨ����

#define DATA_PREP_EN 0 //����Ԥ׼��
#define BUILD_SCAN_DATA_INDEX_EN 0 //����ɨ����������ʹ��
#define SCAN_DATA_MODE SCAN_SOFT_MODE0 //0��ʾ���ɨ�跽ʽ��1��ʾӲ��ɨ�跽ʽ

#define BORDER_SHOW_EN 1 //�߿���ʾʹ��
#define PIC_SHOW_EN    1 //ͼ����ʾʹ��
#define CLOCK_SHOW_EN  1 //������ʾʹ��
#define LUN_SHOW_EN    1 //ũ����ʾʹ��
#define TEMP_SHOW_EN   1 //�¶���ʾʹ��
#define TIME_SHOW_EN   1 //ʱ����ʾʹ��
#define TIMER_SHOW_EN  1 //��ʱ��ʾʹ�� 
#define HUMIDITY_SHOW_EN 0 //ʪ����ʾʹ��
#define NOISE_SHOW_EN  0 //������ʾʹ��

#define USE_SPI_FLASH //����SPIFlash
//#define USE_NOR_FLASH //����NORFlash

#define UDISK_EN  1//u��ʹ��
#define CHIP_USB_HOST //�����ʾʹ��Ƭ��USB HOST�ӿ�
#define NET_EN	 0//����ʹ��
#define GPRS_EN  0//GPRSʹ��

//#define COM_BUF_ID 0x00
//#define NET_BUF_ID 0x01
//#define GPRS_BUF_ID 0x02



#define SHELL_EN 0//shellʹ��
//#if !defined (STM32F10X_LD)
//#define STM32F10X_LD
//#endif

#endif














