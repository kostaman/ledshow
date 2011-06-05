#ifndef LED_CFG_H
#define LED_CFG_H

#define CARD_AX 0x00
#define CARD_BX 0x10
#define CARD_CX 0x20
#define CARD_DX 0x30
#define CARD_EX 0x40


//节目特征字
#define BORDER_SHOW_BIT 0x00
#define PIC_SHOW_BIT    0x01
#define CLOCK_SHOW_BIT  0x02
#define TIME_SHOW_BIT   0x03
#define TIMER_SHOW_BIT  0x04
#define LUN_SHOW_BIT    0x05
#define TEMP_SHOW_BIT   0x06
#define HUMIDITY_SHOW_BIT 0x07
#define NOISE_SHOW_BIT  0x08
#define TEXT_SHOW_BIT   0x09

#define CS_BYTES 1
#define ROM_CS_BYTES 2

#define MAX_LIGHTNESS_LEVEL 16 //最大亮度等级
#define MAX_OPEN_CLOSE_TIME 4 //最大开关机时段
#define MAX_LIGHTNESS_TIME 4 //最大亮度控制时段

#define QT_EN 1 //在QT环境下编译使用QT
#define QT_SIM_EN 1//使用QT仿真STM32情况。不同于预览
#define CARD_TYPE CARD_AX //A系列板卡针对小条屏，其他针对中大屏
//QT_EN=1,QT_SIM_EN=1表示预览功能，完全模仿QT_SIM_EN=0表示正常预览

#define SCAN_SCREEN_PERIOD 40//扫屏周期,单位ms
#define OE_PWM_FREQ 80000 //80KPWM频率

#if (CARD_TYPE & 0xF0) == (CARD_AX & 0xF0)
#define APP_NAME "条屏LED播放系统"
#define MAX_PROG_NUM 10 //最大节目数
#define MAX_AREA_NUM 2 //每个节目下最大分区数
#define MAX_FILE_NUM 8 //每个分区下最大文件数
#define BLOCK_DATA_LEN 129 //每块数据的大小
#define MAX_BORDER_POINTS (16*8) //边框数据大小
#else
#define APP_NAME "大屏LED播放系统"
#define MAX_PROG_NUM 10 //最大节目数
#define MAX_AREA_NUM 8 //每个节目下最大分区数
#define MAX_FILE_NUM 8 //每个分区下最大文件数
#define BLOCK_DATA_LEN 489 //每块数据的大小
#define MAX_BORDER_POINTS (40*8) //边框数据大小
#endif

#if QT_EN
#define ASSERT_EN 1
#include "QT_SIM.h"


//显示效果配置
#define MOVE_STEP_PERIOD 40 //移动步进时间,单位为ms
//#define MIN_STAY_TIME  10//每屏最小停留时间,单位为ms
#define MOVE_STEP 2 //每个调度单位移动的数据百分比 单位%
 

#define IN_SPEC_EFFECT_NUM 43 //进入特效个数
#define OUT_SPEC_EFFECT_NUM 20 //退出特效个数
#define FONT_NUM 2 //内嵌字体个数

//----根据不同的屏幕和硬件配置下列项目
#define MAX_POINTS (1024*256L) //最大点数--此处是三色屏的最大点数！单色屏的点数在此基础上*3

#define DATA_PREP_EN 0
#define MAX_BLOCK_NUM  4000
#define MAX_SCAN_BLOCK_NUM 10

#define BORDER_SHOW_EN 1 //边框显示使能
#define PIC_SHOW_EN    1 //图文显示使能
#define CLOCK_SHOW_EN  1 //表盘显示使能
#define LUN_SHOW_EN    1 //农历显示使能
#define TEMP_SHOW_EN   1 //温度显示使能
#define TIME_SHOW_EN   1 //时间显示使能
#define TIMER_SHOW_EN  1 //定时显示使能
#define HUMIDITY_SHOW_EN 1 //湿度湿度
#define NOISE_SHOW_EN  1 //噪音
#define TEXT_SHOW_EN   1 //内码文字

#else //没有使能QT仿真 ---STM32的环境下
#define ASSERT_EN 1
#include "STM32.h"


#if CARD_TYPE == CARD_AX
#include "LED_AX_Cfg.h"
#include "LED_AX_Drv.h"
#elif CARD_TYPE == CARD_BX
#include "LED_BX_Cfg.h"
#include "LED_BX_Drv.h"
#elif CARD_TYPE == CARD_CX
#include "LED_CX_Cfg.h"
#include "LED_CX_Drv.h"
#elif CARD_TYPE == CARD_DX
#include "LED_DX_Cfg.h"
#include "LED_DX_Drv.h"
#elif CARD_TYPE == CARD_EX
#include "LED_EX_Cfg.h"
#include "LED_EX_Drv.h"
#else
#error "Card type error"
#endif

#endif

//节目特征字
#define FILE_EN_WORD ((BORDER_SHOW_EN<<BORDER_SHOW_BIT) |\
                       (PIC_SHOW_EN << PIC_SHOW_BIT) |\
                       (CLOCK_SHOW_EN<<CLOCK_SHOW_BIT) |\
                       (TIME_SHOW_EN << TIME_SHOW_BIT) |\
                       (TIMER_SHOW_EN << TIMER_SHOW_BIT) |\
                       (LUN_SHOW_EN << LUN_SHOW_BIT) |\
                       (TEMP_SHOW_EN << TEMP_SHOW_BIT) |\
                       (HUMIDITY_SHOW_EN << HUMIDITY_SHOW_BIT) |\
                       (NOISE_SHOW_EN << NOISE_SHOW_BIT) |\
                       (TEXT_SHOW_EN << TEXT_SHOW_EN))L

//-----------------以下为了兼容STM32程序--------------
#define CARD_SUB_A0 0x00
#define CARD_SUB_A1 0x01
#define CARD_SUB_A2 0x02

#define CARD_SUB_TYPE CARD_SUB_A0 //AX系列子卡类型

#define CARD_NAME "CARD_A0"  //卡名称

#define UDIS_EN  1//u盘使能
#define NET_EN	 1//网络使能
#define GPRS_EN  1//GPRS使能
#endif



