#ifndef LED_A0_CFG_H
#define LED_A0_CFG_H

#define MOVE_STEP_PERIOD 20 //�ƶ�����ʱ��,��λΪms
//#define MIN_STAY_TIME  10//ÿ����Сͣ��ʱ��,��λΪms
#define MOVE_STEP 10 //ÿ�����ȵ�λ�ƶ������ݰٷֱ� ��λ%

#define IN_SPEC_EFFECT_NUM 5 //������Ч����
#define OUT_SPEC_EFFECT_NUM 5 //�˳���Ч����
#define FONT_NUM 1 //��Ƕ�������

//----���ݲ�ͬ����Ļ��Ӳ������������Ŀ
#define MAX_POINTS (128*32L) //������--�˴�����ɫ��������������ɫ���ĵ����ڴ˻�����*3
#define MAX_BLOCK_NUM  4000 //���洢����
#define MAX_SCAN_BLOCK_NUM 4 //���ɨ���

#define DATA_PREP_EN 0 //����Ԥ׼��

#define BORDER_SHOW_EN 1 //�߿���ʾʹ��
#define PIC_SHOW_EN    1 //ͼ����ʾʹ��
#define CLOCK_SHOW_EN  0 //������ʾʹ��
#define LUN_SHOW_EN    0 //ũ����ʾʹ��
#define TEMP_SHOW_EN   0 //�¶���ʾʹ��
#define TIME_SHOW_EN   0 //ʱ����ʾʹ��
#define TIMER_SHOW_EN  0 //��ʱ��ʾʹ�� 
#define HUMIDITY_SHOW_EN 0 //ʪ����ʾʹ��
#define NOISE_SHOW_EN  0 //������ʾʹ��

#define USE_SPI_FLASH //����SPIFlash
//#define USE_NOR_FLASH //����NORFlash

#define UDIS_EN  1//u��ʹ��
#define NET_EN	 0//����ʹ��
#define GPRS_EN  0//GPRSʹ��

//#define COM_BUF_ID 0x00
//#define NET_BUF_ID 0x01
//#define GPRS_BUF_ID 0x02



#define SHELL_EN 1//shellʹ��
//#if !defined (STM32F10X_LD)
//#define STM32F10X_LD
//#endif

#endif














