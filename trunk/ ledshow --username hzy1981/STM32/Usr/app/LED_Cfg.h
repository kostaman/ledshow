#ifndef LED_CFG_H
#define LED_CFG_H

#define CARD_A0 0x00
#define CARD_B0 0x10
#define CARD_C0 0x20
#define CARD_D0 0x30
#define CARD_E0 0x40


//��Ŀ������
#define BORDER_SHOW_BIT 0x00
#define PIC_SHOW_BIT    0x01
#define CLOCK_SHOW_BIT  0x02
#define TIME_SHOW_BIT   0x03
#define TIMER_SHOW_BIT  0x04
#define LUN_SHOW_BIT    0x05
#define TEMP_SHOW_BIT   0x06
#define HUMIDITY_SHOW_BIT 0x07
#define NOISE_SHOW_BIT  0x08

#define CS_BYTES 1
#define ROM_CS_BYTES 2

#define MAX_LIGHTNESS_LEVEL 16 //������ȵȼ�
#define MAX_OPEN_CLOSE_TIME 4 //��󿪹ػ�ʱ��
#define MAX_LIGHTNESS_TIME 4 //������ȿ���ʱ��

#define QT_EN 0 //��QT�����±���ʹ��QT
#define QT_SIM_EN 0//ʹ��QT����STM32�������ͬ��Ԥ��
#define CARD_TYPE CARD_A0 //Aϵ�а忨���С��������������д���
//QT_EN=1,QT_SIM_EN=1��ʾԤ�����ܣ���ȫģ��QT_SIM_EN=0��ʾ����Ԥ��

#define SCAN_SCREEN_PERIOD 40//ɨ������,��λms
#define OE_PWM_FREQ 80000 //80KPWMƵ��

#if (CARD_TYPE & 0xF0) == (CARD_A0 & 0xF0)
#define APP_NAME "����LED����ϵͳ"
#define MAX_PROG_NUM 10 //����Ŀ��
#define MAX_AREA_NUM 2 //ÿ����Ŀ����������
#define MAX_FILE_NUM 8 //ÿ������������ļ���
#define BLOCK_DATA_LEN 129 //ÿ�����ݵĴ�С
#define MAX_BORDER_POINTS (10*8) //�߿����ݴ�С
#else
#define APP_NAME "����LED����ϵͳ"
#define MAX_PROG_NUM 10 //����Ŀ��
#define MAX_AREA_NUM 8 //ÿ����Ŀ����������
#define MAX_FILE_NUM 8 //ÿ������������ļ���
#define BLOCK_DATA_LEN 489 //ÿ�����ݵĴ�С
#define MAX_BORDER_POINTS (40*8) //�߿����ݴ�С
#endif

#if QT_EN

#include "QT_SIM.h"
#define ASSERT_EN 1

//��ʾЧ������
#define MOVE_STEP_PERIOD 40 //�ƶ�����ʱ��,��λΪms
//#define MIN_STAY_TIME  10//ÿ����Сͣ��ʱ��,��λΪms
#define MOVE_STEP 2 //ÿ�����ȵ�λ�ƶ������ݰٷֱ� ��λ%
 

#define IN_SPEC_EFFECT_NUM 43 //������Ч����
#define OUT_SPEC_EFFECT_NUM 20 //�˳���Ч����
#define FONT_NUM 2 //��Ƕ�������

//----���ݲ�ͬ����Ļ��Ӳ������������Ŀ
#define MAX_POINTS (1024*256L) //������--�˴�����ɫ��������������ɫ���ĵ����ڴ˻�����*3

#define DATA_PREP_EN 0
#define MAX_BLOCK_NUM  4000
#define MAX_SCAN_BLOCK_NUM 10

#define BORDER_SHOW_EN 1 //�߿���ʾʹ��
#define PIC_SHOW_EN    1 //ͼ����ʾʹ��
#define CLOCK_SHOW_EN  1 //������ʾʹ��
#define LUN_SHOW_EN    1 //ũ����ʾʹ��
#define TEMP_SHOW_EN   1 //�¶���ʾʹ��
#define TIME_SHOW_EN   1 //ʱ����ʾʹ��
#define TIMER_SHOW_EN  1 //��ʱ��ʾʹ��
#define HUMIDITY_SHOW_EN 1 //ʪ��ʪ��
#define NOISE_SHOW_EN  1

#else //û��ʹ��QT���� ---STM32�Ļ�����

#include "STM32.h"
#define ASSERT_EN 1

#if CARD_TYPE == CARD_A0
#include "LED_A0_Cfg.h"
#include "LED_A0_Drv.h"
#elif CARD_TYPE == CARD_B0
#include "LED_B0_Cfg.h"
#include "LED_B0_Drv.h"
#elif CARD_TYPE == CARD_C0
#include "LED_C0_Cfg.h"
#include "LED_C0_Drv.h"
#elif CARD_TYPE == CARD_D0
#include "LED_D0_Cfg.h"
#include "LED_D0_Drv.h"
#elif CARD_TYPE == CARD_E0
#include "LED_E0_Cfg.h"
#include "LED_E0_Drv.h"
#else
#error "Card type error"
#endif

#endif

//��Ŀ������
#define FILE_EN_WORD ((BORDER_SHOW_EN<<BORDER_SHOW_BIT) |\
                       (PIC_SHOW_EN << PIC_SHOW_BIT) |\
                       (CLOCK_SHOW_EN<<CLOCK_SHOW_BIT) |\
                       (TIME_SHOW_EN << TIME_SHOW_BIT) |\
                       (TIMER_SHOW_EN << TIMER_SHOW_BIT) |\
                       (LUN_SHOW_EN << LUN_SHOW_BIT) |\
                       (TEMP_SHOW_EN << TEMP_SHOW_BIT) |\
                       (HUMIDITY_SHOW_EN << HUMIDITY_SHOW_BIT) |\
                       (NOISE_SHOW_EN << NOISE_SHOW_BIT))L


 #endif



