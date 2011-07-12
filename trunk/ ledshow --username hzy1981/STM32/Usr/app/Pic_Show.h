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

#define FIX_MODE 0x00 //�̶�ϵ��
#define H_MODE  0x01 //����
#define V_MODE  0x02//����
#define HV_ADD_MODE 0x03 //+
#define HV_SQRT_MODE 0x04 //����,�Խ�

typedef struct
{
  void (*Func)(INT8U);
  INT8U Step_Mode; //����ģʽ,0-����1����3�ݺ�ͬ��
  float Fac; //0,1��ʾ1��������ʾ
#if QT_EN
  const char *name;
#endif  
}S_Mode_Func;

extern const S_Mode_Func In_Mode_Func[];
extern const S_Mode_Func Out_Mode_Func[];
EXT void Set_Area_Border_In(INT8U Area_No);
EXT void Set_Area_Border_Out(INT8U Area_No);
EXT void Calc_Screen_Color_Num(void);
EXT void Calc_Show_Mode_Step(INT8U Area_No);
EXT INT8U Chk_File_Play_Status(INT8U Area_No);
EXT void Update_Pic_Data(INT8U Area_No);
EXT INT8U Check_XXX_Data(INT8U Flag);
#endif
#endif

