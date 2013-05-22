#ifndef LED_ABX_CFG_H
#define LED_ABX_CFG_H
						 
//#define CARD_SUB_A0 0x00
//#define CARD_SUB_A1 0x01
//#define CARD_SUB_A2 0x02

//#define CARD_SUB_TYPE CARD_SUB_A0 //AXϵ���ӿ�����

 //-------------------ʱ���������---------------
#ifdef CARD_A
#define HSE_VALUE 12000000 //�ⲿ����Ƶ��
#define HCLK_VALUE  HSE_VALUE*2
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_2	//��������ʱAHB�ٶ�
#define PCLK1_DIV RCC_HCLK_Div2 //���APB/2--������������ʱ�ٶ�,���ﲻ��ΪDIV1����Ϊ��ʱ��ʹ�õķ�Ƶϵ��Ĭ��PCLK1��Ƶ>1
#define PCLK2_DIV RCC_HCLK_Div1 //��ߺ�AHBһ��,ע��SPIFlash���ٶ���APB2/2���ܳ���50M,CH376���ٶ���APB2/8���ܳ���24M

#define TIM1_EN 0
#define SCAN_SCREEN_PERIOD 300//ɨ������,��λus

#elif defined(CARD_B)
#define HSE_VALUE 12000000 //�ⲿ����Ƶ��
#define HCLK_VALUE  HSE_VALUE*6
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_6	//��������ʱAHB�ٶ�
#define PCLK1_DIV RCC_HCLK_Div2 //���APB/2--������������ʱ�ٶ�,���ﲻ��ΪDIV1����Ϊ��ʱ��ʹ�õķ�Ƶϵ��Ĭ��PCLK1��Ƶ>1
#define PCLK2_DIV RCC_HCLK_Div1 //��ߺ�AHBһ��,ע��SPIFlash���ٶ���APB2/2���ܳ���50M,CH376���ٶ���APB2/4���ܳ���24M

#define TIM1_EN 1
#define SCAN_SCREEN_PERIOD 100//ɨ������,��λus

#endif
//#define H_HCLK_MUL  RCC_PLLMul_9  //��������ʱAHB�ٶ�
//#define H_PCLK1_DIV RCC_HCLK_Div2 //��������ʱAPB1�ٶ�--ȷ������������ʱ����һ�£������Ͳ���Ҫ�����������Clock 
//#define H_PCLK2_DIV RCC_HCLK_Div1 //��������ʱAPB2�ٶ�--ȷ������������ʱ����һ�£������Ͳ���Ҫ�����������Clock 
#define MAX_PROG_NUM 16 //����Ŀ��
#define MAX_FILE_NUM 50 //ÿ����Ŀ������ļ���

#if defined(CARD_A)
#define MAX_AREA_NUM 4 //ÿ����Ŀ����������
#else
#define MAX_AREA_NUM 6 //ÿ����Ŀ����������
#endif

//----------------------------------------
#if defined(CARD_A)
#if CARD_TYPE == CARDA0 //A0�Ϳ�����Ͷ˿�����֧��ʱ��,�������Ϳ���֧��
#define CARD_NAME "A0"  //������
#elif CARD_TYPE == CARDA1
#define CARD_NAME "A1"  //������
#elif CARD_TYPE == CARDA2
#define CARD_NAME "A2"  //������
#else
#error "card AX name error"
#endif
#elif defined(CARD_B)
#if CARD_TYPE == CARDB1 //A0�Ϳ�����Ͷ˿�����֧��ʱ��,�������Ϳ���֧��
#define CARD_NAME "B1"  //������
#else
#error "card BX name error"
#endif
#endif

#define MOVE_STEP_PERIOD 20//5 //�ƶ�����ʱ��,��λΪms
#define MOVE_STEP 1 //ÿ�����ȵ�λ�ƶ������ݰٷֱ� ��λ%

//----���ݲ�ͬ����Ļ��Ӳ������������Ŀ
#ifdef CARD_A
/*
#if CARD_TYPE == CARDA0
#define MAX_POINTS (144*64) //������--�˴���˫ɫ��������������ɫ���ĵ����ڴ˻�����*2
#else//if CARD_TYPE == CARDA1
#define MAX_POINTS (184*64) //������--�˴���˫ɫ��������������ɫ���ĵ����ڴ˻�����*2
#endif
*/
#define MAX_POINTS (128*64) //������--�˴���˫ɫ��������������ɫ���ĵ����ڴ˻�����*2

#define MAX_STORA_BLOCK_NUM  1600 //���洢����
#define FONT_NUM 1 //��Ƕ�������
#define DATA_FLASH_SIZE (1*1024*1024) //dataflash��С

#define IN_SPEC_EFFECT_NUM 35 //������Ч����
#define OUT_SPEC_EFFECT_NUM 25 //�˳���Ч����

#elif defined(CARD_B)
#define MAX_POINTS (504*64) //������--�˴���˫ɫ��������������ɫ���ĵ����ڴ˻�����*2
#define MAX_STORA_BLOCK_NUM  3200 //���洢����
#define FONT_NUM 2 //��Ƕ�������
#define DATA_FLASH_SIZE (2*1024*1024)	//dataflash��С

#define IN_SPEC_EFFECT_NUM 86 //������Ч����
#define OUT_SPEC_EFFECT_NUM 48 //�˳���Ч����

#endif

#define MAX_SCAN_BLOCK_NUM 4 //���ɨ���

#define DATA_PREP_EN 0 //����Ԥ׼��
#define BUILD_SCAN_DATA_INDEX_EN 0 //����ɨ����������ʹ��
#define SCAN_DATA_MODE SCAN_SOFT_MODE0 //0��ʾ���ɨ�跽ʽ��1��ʾӲ��ɨ�跽ʽ

#if CARD_TYPE == CARDA0 //A0�Ϳ�����Ͷ˿�����֧��ʱ��,�������Ϳ���֧��
#define CLOCK_EN       0 //�Ƿ���ʱ�ӹ���
#else
#define CLOCK_EN       1
#endif

#ifdef CARD_A //A�࿨����Ϊ����ռ����⣬û��ũ����ʾ
#if CLOCK_EN
#define CLOCK_SHOW_EN  0 //������ʾʹ��
#define TIME_SHOW_EN   1 //ʱ����ʾʹ��
#define TIMER_SHOW_EN  1 //��ʱ��ʾʹ��
#define LUN_SHOW_EN    0 //ũ����ʾʹ��
#else //A0���Ϳ�û��ʱ��
#define CLOCK_SHOW_EN  0 //������ʾʹ��
#define TIME_SHOW_EN   0 //ʱ����ʾʹ��
#define TIMER_SHOW_EN  0 //��ʱ��ʾʹ��
#define LUN_SHOW_EN    0 //ũ����ʾʹ��
#endif
#define BORDER_SHOW_EN 1 //�߿���ʾʹ��
#define PIC_SHOW_EN    1 //ͼ����ʾʹ��
#define TEMP_SHOW_EN   1 //�¶���ʾʹ��
#define HUMIDITY_SHOW_EN 0 //ʪ����ʾʹ��
#define NOISE_SHOW_EN  0 //������ʾʹ��
#define TXT_SHOW_EN    0
#else
#define BORDER_SHOW_EN 1 //�߿���ʾʹ��
#define PIC_SHOW_EN    1 //ͼ����ʾʹ��
#define CLOCK_SHOW_EN  1 //������ʾʹ��
#define LUN_SHOW_EN    1 //ũ����ʾʹ��
#define TEMP_SHOW_EN   1 //�¶���ʾʹ��
#define TIME_SHOW_EN   1 //ʱ����ʾʹ��
#define TIMER_SHOW_EN  1 //��ʱ��ʾʹ�� 
#define HUMIDITY_SHOW_EN 1 //ʪ����ʾʹ��
#define NOISE_SHOW_EN  0 //������ʾʹ��
#define TXT_SHOW_EN    0
#endif

#define USE_SPI_FLASH //����SPIFlash
//#define USE_NOR_FLASH //����NORFlash

#define UDISK_EN  0//u��ʹ��
#define NET_EN	 0//����ʹ��
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














