#ifndef BORDER_SHOW_H
#define BORDER_SHOW_H

#if BORDER_SHOW_EN > 0

#undef EXT
#ifdef BORDER_SHOW_C
#define EXT
#else
#define EXT extern
#endif

#define BORDER_STATIC 0x00 //��̬
#define BORDER_FLASH  0x01 //��˸
#define BORDER_CLKWS  0x02 //˳ʱ��
#define BORDER_CCLKWS 0x03 //��ʱ��
#define BORDER_CLKWS_FLASH  0x04 //˳ʱ����˸
#define BORDER_CCLKWS_FLASH 0x05 //��ʱ����˸

EXT INT8U Get_Border_Point_Data(INT8U Area_No, INT16U X, INT16U Y);
EXT void Draw_Border(S_Show_Data *pDst, INT8U Area_No, INT8U *pData, INT8U Width, INT8U Height,  INT8U Step);
EXT void Update_Border_Data(INT8U Area_No);
#endif

#endif
