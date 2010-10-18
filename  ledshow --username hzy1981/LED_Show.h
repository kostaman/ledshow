#ifndef LED_SHOW_H
#define LED_SHOW_H

//extern "c"
//{
//#include "LED_Cfg.h"
#include "pub.h"
#include "LED_Para.h"

#undef EXT
#ifdef LED_SHOW_C
#define EXT
#else
#define EXT extern
#endif

#define PI 3.1415926

#define SHOW_NULL  0x00
#define SHOW_PIC   0x01
#define SHOW_CLOCK 0x02
#define SHOW_TIME  0x03
#define SHOW_TIMER 0x04
#define SHOW_TEMP  0x05


#define FONT_SIZE16 0
#define FONT_SIZE24 1
#define FONT_SIZE48 2

#define GET_LINE_Y(X0,Y0,X1,Y1,X) ((X1 != X0)?(((Y1)-(Y0))*((X)-(X0))/((X1)-(X0)) + (Y0)):Y0)
#define GET_LINE_X(X0,Y0,X1,Y1,Y) ((Y1 != Y0)?(((X1)-(X0))*((Y)-(Y0))/((Y1)-(Y0)) + (X0)):X0)

#define AREA_ERR -1//������ʾ�ļ�����
#define AREA_END 0 //�÷�������
#define AREA_OK  1 //���³ɹ�

#define PROG_END 0 //��Ŀ����
#define PROG_OK  1 //��Ŀok
//#define PUB_BUF Show_Data_Bak.Pub_Buf.Buf //����������������ʾ���ݹ���
/*
//ʱ��
typedef struct
{
INT8U Head;
INT8U Time[5]; //�ꡢ�¡��ա�ʱ����	
INT8U Tail;
}S_Time;
*/
//��ɫ��ʾ����
typedef struct
{
  INT8U Head;
  INT8U Color0[MAX_POINTS/3]; //��ɫ
  INT8U Color1[MAX_POINTS/3]; //��ɫ
  INT8U Color2[MAX_POINTS/3]; //��ɫ
  INT8U Tail;
}S_Show_3Color_Data;

//˫ɫ��ʾ����
typedef struct
{
  INT8U Head;
  INT8U Color0[MAX_POINTS/2];
  INT8U Color1[MAX_POINTS/2];
  INT8U Tail;
}S_Show_2Color_Data;

//��ɫ��ʾ����
typedef struct
{
  INT8U Head;
  INT8U Color0[MAX_POINTS];
  INT8U Tail;
}S_Show_1Color_Data;

//��Ķ���
typedef struct
{
  INT16U X;
  INT16U Y;
}S_Point;

typedef struct
{/*
  S_Pub_Buf Pub_Buf;  //����buf
  S_Show_1Color_Data One_Color_Data;
  S_Show_2Color_Data Two_Color_Data;
  S_Show_3Color_Data Three_Color_Data;
  */
  INT8U Head;
  INT8U Color_Data[3*MAX_POINTS/8];
  INT8U Tail;
}S_Show_Data;

//�������״̬
typedef struct
{
  INT8U Head;
  
  INT8U File_No; //��ǰ�ļ���
  INT8U File_Type; //�ļ�����
  INT8U File_Offset; //��ǰ�ļ�ƫ��
  INT8U Step;        //��ǰ�ƶ��Ľ���
  INT16U Step_Timer;  //�Ѿ��߹�Timer����λms
  INT32U Stay_Time;   //�Ѿ�ͣ����ʱ�䣬��λms
  
  INT8U Tail;
}S_Area_Status;

//�����Ŀ״̬
typedef struct
{
  INT8U Time; //�Ѿ�����ʱ��
  
}S_Program_Status;

//extern char * Get_Program_Data_File_Name(INT8U Prog_No, INT8U Area_No, char File_Name[]);
typedef struct{
  INT16U Unicode;
  INT8U CN16_Dot[32]; //16*16
  INT8U CN24_Dot[72]; //24*24
  INT8U CN36_Dot[162]; //36*36
}CNZK_Info;

typedef struct
{
  void (*Func)(INT8U);
}S_Mode_Func;

EXT S_Show_Data Show_Data;  //��ʾ����
EXT S_Show_Data Show_Data_Bak; //��ʾ���ݱ���
EXT S_Area_Status Area_Status[MAX_AREA_NUM]; //����״̬��Ϣ
EXT S_Program_Status Program_Status;   //��Ŀ״̬��Ϣ

//��ȡ��ǰ��ɫ����
EXT INT8U Get_Color(); //��ȡ��ǰ����ɫ����
EXT INT8U Get_Bit(INT8U *p,INT16U X_Size,INT16U X,INT16U Y);
EXT INT8U Get_Buf_Bit(INT8U Buf[], INT32U Buf_Size, INT32U Index);
EXT void Set_Buf_Bit(INT8U Buf[], INT32U Buf_Size, INT32U Index, INT8U Value);
EXT INT32U Get_Area_Point_Index(INT8U Area_No, INT16U X, INT16U Y); //��ȡĳ����������ݻ�������ʼ
//��λ�Ŀ���
EXT void Bits_Copy(INT8U *pSrc, INT16U Src_Len, INT32U Src_Index, INT32U Bits, INT8U *pDst, INT16U Dst_Len, INT32U Dst_Index);
//��ȡһ�������е�һ����
EXT INT8U Get_Area_Point_Data(S_Show_Data *pSrc_Buf, INT8U Area_No, INT16U X, INT16U Y); //��ȡһ��������һ���������
//����һ�������е�һ����
EXT void Set_Area_Point_Data(S_Show_Data *pDst_Buf, INT8U Area_No, INT16U X, INT16U Y, INT8U Data); //����һ������ĵ�
//����һ����
EXT void Draw_Line(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1, INT8U Value);
//����һ����
EXT void Copy_Line(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1, S_Show_Data *pDst_Buf, S_Point *pPoint2);
//����һ�����õľ���
EXT void Copy_Filled_Rect(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len, S_Show_Data *pDst_Buf, S_Point *pPoint1);
//���һ������
EXT void Fill_Rect(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len,INT8U Value);
//����һ������������
EXT void Copy_Filled_Triangle(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pSrc_Point0, S_Point *pSrc_Point1,S_Point *pSrc_Point2,\
  S_Show_Data *pDst_Buf, S_Point *pDst_Point0);  //����һ������������
//���һ����������
EXT void Fill_Triangle(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1,S_Point *pPoint2, INT8U Value);
//����һ��ʵ��Բ
EXT void Copy_Filled_Round(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pCenter0, INT16U Radius, S_Show_Data *pDst_Buf, S_Point *pCenter1);
//���һ��ʵ��Բ
EXT void Fill_Round(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pCenter, INT16U Radius, INT8U Value);
//����һ�������
EXT void Copy_Filled_Polygon(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1,S_Point *pPoint2, S_Point *pPoint3,S_Show_Data *pDst_Buf, S_Point *pPoint4);
//���һ�������
EXT void Fill_Polygon(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1,S_Point *pPoint2, S_Point *pPoint3, INT8U Value);
//��ȡĳ���һ��һ���ǶȺͳ��ȵĵ�
EXT void Get_Angle_Point(S_Point *pPoint0, INT16S Angle, INT16U Len, S_Point *pPoint1);
//������ʱ������
EXT void Fill_Clock_Point(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pCenter, INT16S Angle, INT16U Len, INT16U Radius, INT8U Value);
//���ʱ�ӡ����ӻ����ӵ�ָ��
EXT void Fill_Clock_Line(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pCenter, INT16S Angle, INT16U Len, INT16U Width, INT8U Value);

EXT void Move_Left(INT8U Area_No);
EXT void Move_Right(INT8U Area_No);
EXT void Move_Up(INT8U Area_No);
EXT void Move_Down(INT8U Area_No);
EXT void Move_Left_Cover(INT8U Area_No);
EXT void Move_Right_Cover(INT8U Area_No);
EXT void Move_Up_Cover(INT8U Area_No);
EXT void Move_Down_Cover(INT8U Area_No);
EXT void Move_Left_Up_Cover(INT8U Area_No);
EXT void Move_Right_Up_Cover(INT8U Area_No);
EXT void Move_Left_Down_Cover(INT8U Area_No);
EXT void Move_Right_Down_Cover(INT8U Area_No);
EXT void Move_Left_Right_Open(INT8U Area_No);
EXT void Move_Up_Down_Open(INT8U Area_No);
EXT void Move_Left_Right_Close(INT8U Area_No);
EXT void Move_Up_Down_Close(INT8U Area_No);
EXT INT8S Update_Show_Data_Bak(INT8U Prog_No, INT8U Area_No);
EXT INT8S Check_Update_Show_Data_Bak();
EXT void Show_Clock(S_Show_Data *pDst_Buf, INT8U Area_No, S_Time *pTime, S_Clock_Para *pClock_Para);
EXT void Clear_Area_Data(S_Show_Data *pDst_Buf, INT8U Area_No);
#endif
