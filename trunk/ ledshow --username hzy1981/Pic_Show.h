#ifndef PIC_SHOW_H
#define PIC_SHOW_H

#include "Includes.h"

#if PIC_SHOW_EN

#undef EXT
#ifdef PIC_SHOW_C
#define EXT
#else
#define EXT extern
#endif

#define H_MODE  0x00
#define V_MODE  0x01
#define HV_MODE 0x02

typedef struct
{
  void (*Func)(INT8U);
  INT8U Step_Mode; //����ģʽ,0-����1����3�ݺ�ͬ��
  INT8U Fac; //0,1��ʾ1��������ʾ
}S_Mode_Func;

EXT void Update_Pic_Data(INT8U Area_No);
#endif
#endif

