#ifndef LED_DX_CFG_H
#define LED_DX_CFG_H
						 
//#define CARD_SUB_B0 0x00
//#define CARD_SUB_B1 0x01
//#define CARD_SUB_B2 0x02

//#define CARD_SUB_TYPE CARD_SUB_B0 //BXϵ���ӿ�����

 //-------------------ʱ���������---------------
#define HSE_VALUE 12000000 //�ⲿ����Ƶ��
#define HCLK_VALUE  HSE_VALUE*7
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_7	//��������ʱAHB�ٶ�
#define PCLK1_DIV RCC_HCLK_Div2 //���APB/2--������������ʱ�ٶ�,���ﲻ��ΪDIV1����Ϊ��ʱ��ʹ�õķ�Ƶϵ��Ĭ��PCLK1��Ƶ>1
#define PCLK2_DIV RCC_HCLK_Div1 //��ߺ�AHBһ��,ע��SPIFlash���ٶ���APB2/2���ܳ���50M,CH376���ٶ���APB2/8���ܳ���24M

#define TIM1_EN 1

#define MAX_PROG_NUM 16 //����Ŀ��
#define MAX_AREA_NUM 8 //ÿ����Ŀ����������
#define MAX_FILE_NUM 50 //ÿ����Ŀ������ļ���

//----------------------------------------
#if defined(CARD_D)
#if CARD_TYPE == CARDD //
#define CARD_NAME "D"  //������
#elif CARD_TYPE == CARDDU
#define CARD_NAME "DU"  //������
#elif CARD_TYPE == CARDDE
#define CARD_NAME "DE"  //������
#elif CARD_TYPE == CARDDM
#define CARD_NAME "DM"  //������
#else
#error "card DX name error"
#endif
#endif

#define SCAN_SCREEN_PERIOD 100//ɨ������,��λus
#define MOVE_STEP_PERIOD 5//5 //�ƶ�����ʱ��,��λΪms
#define MOVE_STEP 1 //ÿ�����ȵ�λ�ƶ������ݰٷֱ� ��λ%

#define IN_SPEC_EFFECT_NUM 86 //������Ч����
#define OUT_SPEC_EFFECT_NUM 48 //�˳���Ч����
#define FONT_NUM 2 //��Ƕ�������

//----���ݲ�ͬ����Ļ��Ӳ������������Ŀ
#define MAX_POINTS (1200*64) //������--�˴���˫ɫ��������������ɫ���ĵ����ڴ˻�����*2
#define MAX_STORA_BLOCK_NUM  3000 //���洢����
#define DATA_FLASH_SIZE 2000000	//dataflash��С
#define MAX_SCAN_BLOCK_NUM 16 //���ɨ���
#define MAX_SCAN_WIDTH 2056 //���ɨ����

#define DATA_PREP_EN 0 //����Ԥ׼��
#define BUILD_SCAN_DATA_INDEX_EN 0 //����ɨ����������ʹ��
#define SCAN_DATA_MODE SCAN_SOFT_MODE0 //0��ʾ���ɨ�跽ʽ��1��ʾӲ��ɨ�跽ʽ

#define CLOCK_EN       1 //ʱ��ʹ��

#define BORDER_SHOW_EN 1 //�߿���ʾʹ��
#define PIC_SHOW_EN    1 //ͼ����ʾʹ��
#define CLOCK_SHOW_EN  1 //������ʾʹ��
#define LUN_SHOW_EN    1 //ũ����ʾʹ��
#define TEMP_SHOW_EN   1 //�¶���ʾʹ��
#define TIME_SHOW_EN   1 //ʱ����ʾʹ��
#define TIMER_SHOW_EN  1 //��ʱ��ʾʹ�� 
#define HUMIDITY_SHOW_EN 1 //ʪ����ʾʹ��
#define NOISE_SHOW_EN  1 //������ʾʹ��
#define TXT_SHOW_EN    0

#define USE_SPI_FLASH //����SPIFlash
//#define USE_NOR_FLASH //����NORFlash
#if CARD_TYPE == CARDD
#define UDISK_EN  0//u��ʹ��
#define NET_EN	 0//����ʹ��
#elif CARD_TYPE == CARDDU
#define UDISK_EN  1//u��ʹ��
#define NET_EN	 0//����ʹ��
#elif CARD_TYPE == CARDDE
#define UDISK_EN  0//u��ʹ��
#define NET_EN	 1//����ʹ��
#elif CARD_TYPE == CARDDM
#define UDISK_EN  1//u��ʹ��
#define NET_EN	 1//����ʹ��
#endif

#define GPRS_EN  0//GPRSʹ��
#define SMS_EN   0//����ʹ��
//#define COM_BUF_ID 0x00
//#define NET_BUF_ID 0x01
//#define GPRS_BUF_ID 0x02



#define SHELL_EN 0//shellʹ��
//#if !defined (STM32F10X_LD)
//#define STM32F10X_LD
//#endif

#endif














