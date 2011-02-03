#ifndef LED_SHOW_H
#define LED_SHOW_H

#include "Pub.h"
#include "LED_Para.h"
//#include "LED_Show.h"


#undef EXT
#ifdef LED_SHOW_C
#define EXT
#else
#define EXT extern
#endif

#define PI 3.1415926535

#define MAX_STEP_NUM 1000

#define SLINE_MODE 0x00
#define MLINE_MODE 0x01

#define GET_LINE_Y(X0,Y0,X1,Y1,X) ((X1 != X0)?(((Y1)-(Y0))*((X)-(X0))/((X1)-(X0)) + (Y0)):Y0)
#define GET_LINE_X(X0,Y0,X1,Y1,Y) ((Y1 != Y0)?(((X1)-(X0))*((Y)-(Y0))/((Y1)-(Y0)) + (X0)):X0)

#define AREA_ERR 2 //������ʾ�ļ�����
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
/*
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
*/
//��Ķ���
typedef struct
{
  INT16U X;
  INT16U Y;
}S_Point;

//�������״̬
typedef struct
{
  INT8U Head;

  INT16U SNum;      //��ǰ�Ѿ������ڼ���������?

  INT8U New_File_Flag:4;
  INT8U New_SCN_Flag:4;

  INT8U File_No;    //��ǰ�ļ���
  INT32U Step;        //��ǰ�ƶ��Ľ���
  INT32U Step_Timer;  //�Ѿ��߹�Timer����λms
  INT32U Stay_Time;   //�Ѿ�ͣ����ʱ�䣬��λms
  INT32U Out_Time;   //�˳�ʱ��
  INT8U Counts;
  
  INT8U In_Mode;
  INT8U Out_Mode;

  INT8U Play_Flag; //���ű�־��0��ʾδ���벥��״̬��1��ʾ���벥��״̬--��Ҫ�������ж���ʾͬ��
  INT8U Tail;
}S_Area_Status;

typedef struct
{
  INT8U Head;
  INT32U Step;   //����
  INT16U Timer; //�Ѿ��߹���Timer
  INT8U Tail;  
}S_Border_Status;



//�����Ŀ״̬
typedef struct
{
  INT8U Head;
  
  INT8U Prog_No; //��ǰ��Ŀ��
  INT32U Time; //�Ѿ�����ʱ��
  INT16U Counts; //�Ѿ����Ŵ���

  INT8U Play_Flag:4; //�Ƿ񲥷ű�־--��Ҫ�������ж���ʾͬ��
  INT8U New_Prog_Flag:4;

  S_Border_Status Border_Status;
  U_File_Para File_Para[MAX_AREA_NUM]; //ÿ�������ĵ�ǰ�ļ�����
  S_Area_Status Area_Status[MAX_AREA_NUM]; //ÿ��������״̬ 
  S_Prog_Block_Index Block_Index; //��ǰ��Ŀ������

  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Prog_Status;

typedef struct
{
  INT8U Head;
  INT8U Lightness;
  INT8U Open_Flag;
  INT8U CS[CS_BYTES];
  INT8U Tail;  
}S_Screen_Status;

//EXT S_Area_Status Area_Status[MAX_AREA_NUM]; //����״̬��Ϣ
EXT S_Prog_Status Prog_Status;   //��Ŀ״̬��Ϣ
EXT S_Screen_Status Screen_Status;

EXT S_Show_Data Show_Data;  //��ʾ����
EXT S_Show_Data Show_Data_Bak; //��ʾ���ݱ���

//#define Pub_Buf Show_Data.Color_Data

//��ȡ��ǰ��ɫ����
EXT INT8U Get_Color(); //��ȡ��ǰ����ɫ����
EXT INT8U Get_Bit(INT8U *p,INT16U X_Size,INT16U X,INT16U Y);
EXT INT8U Get_Buf_Bit(INT8U Buf[], INT32U Buf_Size, INT32U Index);
EXT INT8U Get_Rect_Buf_Bit(INT8U Buf[], INT16U Buf_Size, INT16U Width, INT16U X, INT16U Y);
EXT void Set_Buf_Bit(INT8U Buf[], INT32U Buf_Size, INT32U Index, INT8U Value);
EXT INT16U Get_Area_Width(INT8U Area_No);
EXT INT16U Get_Area_Height(INT8U Area_No);
EXT INT32U Get_Area_Size(INT8U Area_No);
EXT INT8U Get_Area_TopLeft(INT8U Area_No, S_Point *pPoint);
EXT INT32U Get_Area_Point_Index(INT8U Area_No, INT16U X, INT16U Y); //��ȡĳ����������ݻ�������ʼ
//��λ�Ŀ���
EXT void Bits_Copy(INT8U *pSrc, INT16U Src_Len, INT32U Src_Index, INT32U Bits, INT8U *pDst, INT16U Dst_Len, INT32U Dst_Index);
EXT INT8U Get_Buf_Point_Data(INT8U Buf[], INT16U Buf_Len, INT8U Color, INT16U Width, INT16U X, INT16U Y);
EXT void Set_Buf_Point_Data(INT8U Buf[], INT16U Buf_Len, INT8U Color, INT8U Width, INT16U X, INT16U Y, INT8U Value);
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
//������һ�����õľ���
EXT void Rev_Copy_Filled_Rect(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len, S_Show_Data *pDst_Buf, S_Point *pPoint1);
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
EXT void Copy_Filled_Polygon(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT8U Point_Num, S_Show_Data *pDst_Buf, S_Point *pPoint1);
//���һ�������
EXT void Fill_Polygon(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint0, INT8U Point_Num, INT8U Value);
//��ȡĳ���һ��һ���ǶȺͳ��ȵĵ�
EXT void Get_Angle_Point(S_Point *pPoint0, INT16S Angle, INT16U Len, S_Point *pPoint1);
//������ʱ������
EXT void Fill_Clock_Point(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pCenter, INT16S Angle, INT16U Len, INT16U Radius, INT8U Style, INT8U Value);
//���ʱ�ӡ����ӻ����ӵ�ָ��
EXT void Fill_Clock_Line(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pCenter, INT16S Angle, INT16U Len, INT16U Width, INT8U Value);

EXT void Copy_Buf_2_Area_Rect_0(INT8U *pSrc, INT16U Src_Len, INT16U Src_Off, \
                            S_Show_Data *pDst, INT8U Area_No, INT16U X, INT16U Y, INT16U X_Len, INT16U Y_Len);

EXT void Move_Show_RightNow(INT8U Area_No);
EXT void Move_Left_Continuous(INT8U Area_No);
EXT void Move_Right_Continuous(INT8U Area_No);
EXT void Move_Up_Continuous(INT8U Area_No);
EXT void Move_Down_Continuous(INT8U Area_No);
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
EXT void Move_Spin_CW(INT8U Area_No);
EXT void Move_Spin_CCW(INT8U Area_No);
EXT void Move_Up_Snow(INT8U Area_No);
EXT void Move_Down_Snow(INT8U Area_No);
EXT void Clear_Area_Data(S_Show_Data *pDst_Buf, INT8U Area_No);
#endif
