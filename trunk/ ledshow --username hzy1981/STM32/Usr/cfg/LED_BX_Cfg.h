#ifndef LED_BX_CFG_H
#define LED_BX_CFG_H

#define MOVE_STEP_PERIOD 20 //�ƶ�����ʱ��,��λΪms
//#define MIN_STAY_TIME  10//ÿ����Сͣ��ʱ��,��λΪms
#define MOVE_STEP 10 //ÿ�����ȵ�λ�ƶ������ݰٷֱ� ��λ%

#define IN_SPEC_EFFECT_NUM 10 //������Ч����
#define OUT_SPEC_EFFECT_NUM 10 //�˳���Ч����
#define FONT_NUM 1 //��Ƕ�������

//----���ݲ�ͬ����Ļ��Ӳ������������Ŀ
#define MAX_POINTS (1024*75L) //������--�˴�����ɫ��������������ɫ���ĵ����ڴ˻�����*3
#define MAX_BLOCK_NUM  4000 //���洢����
#define MAX_SCAN_BLOCK_NUM 8 //���ɨ���

#define BORDER_SHOW_EN 1 //�߿���ʾʹ��
#define CLOCK_SHOW_EN  1 //������ʾʹ��
#define PIC_SHOW_EN    1 //ͼ����ʾʹ��
#define LUN_SHOW_EN    1 //ũ����ʾʹ��
#define TEMP_SHOW_EN   1 //�¶���ʾʹ��
#define TIME_SHOW_EN   1 //ʱ����ʾʹ��
#define TIMER_SHOW_EN  1 //��ʱ��ʾʹ��
#define HUMIDITY_SHOW_EN 1 //ʪ����ʾʹ��
#define NOISE_SHOW_EN  1 //������ʾʹ��

#define UDIS_EN  1//u��ʹ��
#define NET_EN	 1//����ʹ��
#endif
