#ifndef LED_CFG_H
#define LED_CFG_H

//���ֿ�Ԥ����
#define CARD_A0	 0x10 //A0�Ϳ���֧��ʱ�ӣ���򵥵Ŀ��������Ŀ���һ����
#define CARD_A1	 0x11
#define CARD_A2	 0x12
#define CARD_B0	 0x20
#define CARD_B1	 0x21
#define CARD_B2	 0x22
#define CARD_C0	 0x30
#define CARD_C1	 0x31
#define CARD_C2	 0x32
#define CARD_D0  0x40
#define CARD_D1	 0x41
#define CARD_D2	 0x42

#define SCAN_HARD_MODE   0x00//Ӳ��ɨ��ģʽ
#define SCAN_SOFT_MODE0	 0x01//���ɨ��ģʽ0 --��ɨ���ж��н�������ת��
#define SCAN_SOFT_MODE1	 0x02//���ɨ��ģʽ1 --����Ч�ж��н�������ת��

//��Ŀ������
#define BORDER_SHOW_BIT 0x00
#define PIC_SHOW_BIT    0x01
#define CLOCK_BIT       0x02
#define CLOCK_SHOW_BIT  0x03
#define TIME_SHOW_BIT   0x04
#define TIMER_SHOW_BIT  0x05
#define LUN_SHOW_BIT    0x06
#define TEMP_SHOW_BIT   0x07
#define HUMIDITY_SHOW_BIT 0x08
#define NOISE_SHOW_BIT  0x09
#define TEXT_SHOW_BIT   0x0A


#define CS_BYTES 1
#define ROM_CS_BYTES 2
#define DATA_CHK_EN 1

#define MAX_LIGHTNESS_LEVEL 16 //������ȵȼ�
#define MAX_OPEN_CLOSE_TIME 4 //��󿪹ػ�ʱ��
#define MAX_LIGHTNESS_TIME 4 //������ȿ���ʱ��

#if defined(__CC_ARM) || defined(__ICCARM__)
#define QT_EN 0//��QT�����±���ʹ��QT
#define QT_SIM_EN 0//ʹ��QT����STM32�������ͬ��Ԥ��
#define RMDK_SIM_EN	0
#else
#define QT_EN 1//��QT�����±���ʹ��QT
#define QT_SIM_EN 0//ʹ��QT����STM32�������ͬ��Ԥ��
#define RMDK_SIM_EN 0
#endif

//#define CARD_TYPE CARD_AX //Aϵ�а忨���С��������������д���
//QT_EN=1,QT_SIM_EN=1��ʾԤ�����ܣ���ȫģ��QT_SIM_EN=0��ʾ����Ԥ��


#define OE_PWM_FREQ 1000 //1KPWMƵ��
#define COMPANY_NAME "AS"

#define APP_ADDRESS_OFF 0x2000 //Ӧ�ó����ַƫ��

//#define APP_NAME "����LED����ϵͳ"
#define MAX_PROG_NUM 16 //����Ŀ��
#define MAX_AREA_NUM 6 //ÿ����Ŀ����������
#define MAX_FILE_NUM 8 //ÿ������������ļ���
#define BLOCK_DATA_LEN 459 //ÿ�����ݵĴ�С, BLOCK_DATA_LEN - 9Ӧ�ÿ�������2��3
#define MAX_BORDER_POINTS (40*8) //�߿����ݴ�С
//#endif

#if QT_EN
#define ASSERT_EN 1
#include "QT_SIM.h"

#define APP_NAME "LED���ʦ 2012"

#define SCAN_SCREEN_PERIOD 200//ɨ������,��λus
//��ʾЧ������
#define MOVE_STEP_PERIOD 10 //�ƶ�����ʱ��,��λΪms
//#define MIN_STAY_TIME  10//ÿ����Сͣ��ʱ��,��λΪms
#define MOVE_STEP 1 //ÿ�����ȵ�λ�ƶ������ݰٷֱ� ��λ%
 

#define IN_SPEC_EFFECT_NUM 61 //������Ч����
#define OUT_SPEC_EFFECT_NUM 24 //�˳���Ч����
#define FONT_NUM 2 //��Ƕ�������

//----���ݲ�ͬ����Ļ��Ӳ������������Ŀ
#define MAX_POINTS (4096*256L) //������--�˴�����ɫ��������������ɫ���ĵ����ڴ˻�����*3

#define DATA_PREP_EN 0
#define MAX_STORA_BLOCK_NUM  4000
#define MAX_SCAN_BLOCK_NUM 10
#define SCAN_DATA_MODE SCAN_SOFT_MODE0

#define CLOCK_EN       1 //ʱ��ʹ��

#define BORDER_SHOW_EN 1 //�߿���ʾʹ��
#define PIC_SHOW_EN    1 //ͼ����ʾʹ��
#define CLOCK_SHOW_EN  1 //������ʾʹ��
#define LUN_SHOW_EN    1 //ũ����ʾʹ��
#define TEMP_SHOW_EN   1 //�¶���ʾʹ��
#define TIME_SHOW_EN   1 //ʱ����ʾʹ��
#define TIMER_SHOW_EN  1 //��ʱ��ʾʹ��
#define HUMIDITY_SHOW_EN 1 //ʪ��ʪ��
#define NOISE_SHOW_EN  1 //����
#define TEXT_SHOW_EN   1 //��������

#define CARD_NAME "A0"  //������
//-----------------����Ϊ�˼���STM32����--------------
#else
/*
#if defined(CARD_A0)
#define CARD_NAME "A0"  //������
#elif defined(CARD_A1)
#define CARD_NAME "A1"  //������
#else
#error "card AX name error"
#endif

#define UDIS_EN  1//u��ʹ��
#define NET_EN	 1//����ʹ��
#define GPRS_EN  1//GPRSʹ��
#else //û��ʹ��QT���� ---STM32�Ļ�����
#define ASSERT_EN 0
*/
#include "STM32.h"


#if defined(CARD_A) || defined(CARD_B)
#define CARD_TYPE CARD_A0
#include "LED_ABX_Cfg.h"
#include "LED_ABX_Drv.h"
//#elif defined(CARD_BX)
//#include "LED_BX_Cfg.h"
//#include "LED_BX_Drv.h"
#elif defined(CARD_C)
#define CARD_TYPE CARD_C0
#include "LED_CX_Cfg.h"
#include "LED_CX_Drv.h"
#elif defined(CARD_D)
#define CARD_TYPE CARD_D0
#include "LED_DX_Cfg.h"
#include "LED_DX_Drv.h"
#elif defined(CARD_E)
#define CARD_TYPE CARD_E0
#include "LED_EX_Cfg.h"
#include "LED_EX_Drv.h"
#else
#error "Card type error"
#endif

#endif

#define ENV_VAR_EN (TEMP_SHOW_EN | HUMIDITY_SHOW_EN | NOISE_SHOW_EN)
//��Ŀ������
#define FILE_EN_WORD ((BORDER_SHOW_EN<<BORDER_SHOW_BIT) |\
                       (PIC_SHOW_EN << PIC_SHOW_BIT) |\
					   (CLOCK_EN<<CLOCK_BIT) |\
                       (CLOCK_SHOW_EN<<CLOCK_SHOW_BIT) |\
                       (TIME_SHOW_EN << TIME_SHOW_BIT) |\
                       (TIMER_SHOW_EN << TIMER_SHOW_BIT) |\
                       (LUN_SHOW_EN << LUN_SHOW_BIT) |\
                       (TEMP_SHOW_EN << TEMP_SHOW_BIT) |\
                       (HUMIDITY_SHOW_EN << HUMIDITY_SHOW_BIT) |\
                       (NOISE_SHOW_EN << NOISE_SHOW_BIT) |\
                       (TEXT_SHOW_EN << TEXT_SHOW_EN))L

#endif



