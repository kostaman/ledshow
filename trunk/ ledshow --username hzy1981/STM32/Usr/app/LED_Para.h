#ifndef LED_PARA_H
#define LED_PARA_H

#include "pub.h"
#include "Storage.h"
#include "LED_Show.h"
//extern "c"
//{
#undef EXT
#ifdef LED_PARA_C
#define EXT
#else
#define EXT extern
#endif

//ʱ������
#define T_YEAR  0 //--�����պ�����������0��ʼ�����մ�1�������1900�����
#define T_MONTH 1
#define T_DATE  2
#define T_HOUR  3
#define T_MIN   4
#define T_SEC   5
#define T_WEEK  6

#define SHOW_NULL  0x00
#define SHOW_PIC   0x01 //ͼ��--����ͼƬҲ�����
#define SHOW_CLOCK 0x02 //����
#define SHOW_TIME  0x03 //ʱ��
#define SHOW_TIMER 0x04 //��ʱ
#define SHOW_TEMP  0x05 //�¶�
#define SHOW_LUN   0x06 //ũ��
#define SHOW_HUMIDITY 0x07
#define SHOW_NOISE    0x08
#define SHOW_FLASH 0x09 //����

//#define MAX_FILE_NAME_SIZE 20

#define SPACE_WIDTH 8

#define CHK_BYTE_LEN 3 //�ṹ��������У����ֽ���--һ����Head��Tail��CS
#define CHK_HEAD_LEN 1 //�ṹ��������У���ͷ�ֽ���--һ����Head

//#define PROG_NULL_MODE 0x00
#define PROG_COUNTS_MODE 0x00
#define PROG_TIME_MODE  0x01

#define COM_RS232 0x01
#define COM_RS485 0x02
#define COM_UDISK 0x04
#define COM_ETH   0x08
#define COM_GPRS  0x10

#define GET_TEXT_LEN(W,H) (((W)%8) EQ 0)?((W)*(H)/8):(((W)/8+1)*(H))//((H%8) EQ 0)?(W*H/8):(W*(H/8+1))
#define GET_POINT_INDEX(W,X,Y) ((((W)%8)?((W)/8 + 1)*8:(W))*(Y) + (X))//((W)*(Y) + (X))//

#define GET_COLOR_NUM(X) (((X) < 3)?1:2)

#pragma pack(1)
typedef struct
{
  //INT8U Head;
  INT8U Flag;
  INT8U Value; //����ֵ
  INT8U Start_Hour; //��ʼСʱ
  INT8U Start_Min;
  //INT8U Tail;
}S_Lightness;

typedef struct
{
  INT8U Direct; //���뷽��
  INT8U Rows; //ɨ��1��2��4��8��16ɨ
  INT8U Rows_Fold; //ÿ��������,0��ʾ������,1��ʾÿ1�д�һ���ۣ�ʵ�ʾ���2������
  INT8U Cols_Fold; //ÿ��������,0��ʾ������,1��ʾÿ1�д�һ����
  INT8S Line_Order; //�����,0,+1,-1
  
  INT8U Line_Hide; //������ʱ��
  INT8U Clk_Freq; //��λʱ��Ƶ��
  INT8U Screen_Freq; //��Ļˢ��Ƶ��
  
  INT8U Data_Polarity; //���ݼ���
  INT8U OE_Polarity; //OE����
  INT8U RG_Reverse; //���̷�ת

  INT8U _138Check; //�Ƿ�138��������0��ʾ�У�1��ʾû��
}S_Scan_Para;

typedef struct
{
    INT8U Mode; //�ֶ����ڻ��Ƕ�ʱ����?
    INT8U Manual_Lightness;
    S_Lightness Time_Lightness[MAX_LIGHTNESS_TIME];

}S_Screen_Lightness;
//���ػ�ʱ������
typedef struct
{
  //INT8U Head;
  INT8U Flag;
  INT8U Open_Hour;
  INT8U Open_Min;
  INT8U Close_Hour;
  INT8U Close_Min;

  //INT8U Tail;
}S_Open_Close_Time;

typedef struct
{
    INT8U Flag; //�Ƿ�ʱ���ػ�?
    S_Open_Close_Time Time[MAX_OPEN_CLOSE_TIME]; //��ʱ���ػ�ʱ�ζ���
}S_Screen_OC_Time;

typedef struct
{
  INT8U Week_Check;
  INT8U Week_Flag; //����--ȫ0��ʾ�����ţ���0λ��ʾ�����գ�1-6��ʾ����1-����6
  
  INT8U Date_Check;
  INT8U Start_Date[3]; //��ʼ������
  INT8U End_Date[3];	//����������  
  
  INT8U Time_Check;
  INT8U Start_Time[2]; //��ʼʱ��
  INT8U End_Time[2];	//����ʱ��
}S_Program_Timing;

//λ��
typedef struct
{
  INT16U X;
  INT16U Y;
  INT16U X_Len;
  INT16U Y_Len; 	
}S_Area;

typedef struct
{
  INT8U Head;
  INT32U Max_Points; //���֧�ֵ�����
  INT16U Max_Height; //���߶�
  INT16U Flag; //��0��ʾ��ʾ�Ƿ�֧��ȫ�ʣ�1֧�֣�2��֧�֣�����λ����
  INT8U Font_Num; //�����������
  INT8U InMode_Num; //������Ч����
  INT8U OutMode_Num; //������Ч����

  INT8U Max_Prog_Num; //����Ŀ��
  INT8U Max_Area_Num; //��������
  INT8U Max_File_Num; //ÿ��������ļ���

  INT8U Com_Mode; //֧�ֵ�ͨ�ŷ�ʽ,��0λRS232����1λRS485����2λ��̫������3λGPRS/GSM
  INT16U ROM_Size; //�洢�ռ��С,��λKB
  INT16U File_En_Word; //֧�ֵĽ�Ŀ����
  INT8U Tail;
}S_Card_Para;

typedef struct
{

    INT16U Width; //���
    INT16U Height; //�߶�
    INT8U Color; //��0λ��ɫ����һλ��ɫ���ڶ�λ��ɫ

}S_Screen_Base_Para;

//����ͨ�Ų���
typedef struct
{

    INT16U Addr; //��ַ
    //����
    INT8U Baud;  //������,0��ʾ57600,1��ʾ9600

    INT8U Bak; //����
}S_COM_Para;

//��̫������
typedef struct
{
    //��̫��
    INT32U IP; //IP��ַ
    INT16U Port; //�˿�
    INT32U Mac; //Mac��ַ
    INT32U Mask; //��������
    INT8U Mode; //0�̶�ip��ʽ��1�Զ���ȡ��ʽ
}S_ETH_Para;

typedef struct
{
    //��̫��
    //GPRS��������ַ
    INT32U Srv_IP; //������IP
    INT16U Srv_Port; //�������˿�
    INT8U APN[40];
    INT8U Mode; //0���ѷ�ʽ��1���߷�ʽ
}S_GPRS_Para;

typedef struct
{
    INT8U Time[5];
}S_Valid_Date;

//��Ļ����
//���ݼ���--������
//OE����--����Ч������Ч
//��˳��--������+1��-1
//������ʱ��--�������ӳ�������
//ɨ�跽ʽ
typedef struct
{
  INT8U Head;

  //����0
  /*
  INT8U Polarity; //���ݼ���
  INT8U OE; //OE����

  INT16U Width; //���
  INT16U Height; //�߶�
  INT8U Color; //��ɫ 0��ɫ��1˫ɫ��2��ɫ��3-255���Ҷ�
  
  INT16U Addr; //��ַ
  INT32U IP; //IP��ַ
  INT8U Baud;  //������
*/
  S_Screen_Base_Para Base_Para; //��������
//#if QT_EN > 0
  //INT8U Com_Port; //���ڵĶ˿ں�-��̨��
  //INT8U Com_Mode; //ѡ��ͨ��ģʽ-��̨��
//#endif

  S_COM_Para COM_Para; //ͨ�Ų���-����ͨ�Ų���

  S_ETH_Para ETH_Para; //��̫������

  S_GPRS_Para GPRS_Para; //GPRS����

  S_Scan_Para Scan_Para; //ɨ�����
  //����1
  S_Screen_OC_Time OC_Time;//Open_Close_Time[MAX_OPEN_CLOSE_TIME]; //���ػ�ʱ��
  //����2
  S_Screen_Lightness Lightness;//[MAX_LIGHTNESS_TIME]; //ǿ��

  S_Valid_Date Valid_Date; //��Ч����--��������ں��Զ��ر�--ȫ0��ʾ�����øĲ���
  //����3
  //INT8U Prog_Num; //��Ŀ��
  INT8U CS[CS_BYTES];

  INT8U Tail;
}S_Screen_Para;

typedef struct
{
  INT8U Head;
  INT8U Num;
  INT8U Tail;
  INT8U CS[CS_BYTES];
}S_Prog_Num;

//��Ŀ����
typedef struct
{
  INT8U Head;
  INT8U Prog_No; //��Ŀ��
  
  INT8U Mode; //���ŷ�ʽ��0��ʾѭ�����ţ�1��ʾ��������
  INT16U Counts; //ѭ������
  INT32U Time; //ͣ������
  
  S_Program_Timing Timing[3];//[3]; //��Ŀ��ʱ����
  INT8U Area_Num; //������
  INT8U Main_Area_No; //��������
  INT8U Area_File_Num[MAX_AREA_NUM]; //ÿ�����ļ���
  S_Area Area[MAX_AREA_NUM]; //������
  
  INT8U Border_Check; //�Ƿ���ʾ�߿�
  INT8U Border_Mode;  //�߿�ģʽ
  INT8U Border_Speed;

  INT8U Border_Width;   //�߿���
  INT8U Border_Height;  //�߿�߶�
  INT8U Temp;   //����
//#if BORDER_SHOW_EN > 0  
  INT8U Border_Data[2*MAX_BORDER_POINTS/8]; //�߿�����
//#endif  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Prog_Para;

/*
  INT8U Flag; \//��־
  INT8U Prog_No; \//��Ŀ��
  INT8U Area_No; \//������
  INT8U File_No; \//�ļ���
  INT8U In_Mode; \//���뷽ʽ
  INT16U In_Speed; \//�����ٶ�
  INT8U Add_Mode; \//׷�ӷ�ʽ
  INT16U Stay_Time; \//ͣ��ʱ�䣬���λΪ��λ��0��ʾs��1��ʾms
  INT8U Out_Mode; \//������ʽ
  INT16U Out_Speed; \//����ʱ��
  INT16U SNum; \//��������
  INT8U Play_Counts; \
  INT8U Border_Check; \//�Ƿ�߿�
  INT8U Border_Type; \//�߿�����
  INT8U Border_Color; \//�߿���ɫ
  INT8U Border_Mode; \//�߿�ģʽ
  INT8U Border_Speed //ͣ��ʱ��
*/
#define BASE_PIC_PARA  INT8U Flag; \
  INT8U Prog_No; \
  INT8U Area_No; \
  INT8U File_No; \
  INT8U In_Mode; \
  INT8U In_Speed; \
  INT16U Stay_Time; \
  INT8U Out_Mode; \
  INT8U Out_Speed; \
  INT16U SNum; \
  INT8U Play_Counts; \
  INT8U Border_Check; \
  INT8U Border_Type; \
  INT8U Border_Color; \
  INT8U Border_Mode; \
  INT8U Border_Speed;\

//ͼ�Ĳ���
typedef struct
{
  INT8U Head;
/*  
  INT8U Flag; //��־
  INT8U Prog_No; //��Ŀ��
  INT8U Area_No; //������
  INT8U File_No; //�ļ���
  INT8U In_Mode; //���뷽ʽ
  INT16U In_Speed; //�����ٶ�
  INT8U Add_Mode; //׷�ӷ�ʽ
  INT16U Stay_Time; //ͣ��ʱ�䣬���λΪ��λ��0��ʾs��1��ʾms
  INT8U Out_Mode; //������ʽ
  INT16U Out_Speed; //����ʱ��
  INT16U SNum; //��������

  INT8U Play_Counts;

  INT8U Border_Check; //�Ƿ�߿�
  INT8U Border_Type; //�߿�����
  INT8U Border_Color; //�߿���ɫ
  INT8U Border_Mode; //�߿�ģʽ
  INT8U Border_Speed; //ͣ��ʱ��
 */
  BASE_PIC_PARA
//-------------------------------------------

  //INT8U Color; //��ɫ

  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Pic_Para;

//���̲���
typedef struct
{
  INT8U Head;
  
  BASE_PIC_PARA
//-------------------------------------------
  INT8U Diff_Flag;  //ʱ���־,0�ӣ�1��  
  INT8U Hour_Diff;  //ʱ��Сʱ
  INT8U Min_Diff;   //ʱ�����
  //INT8U Sec_Diff;   //ʱ������
  
  INT8U Hour_Point_Radius; //����뾶
  INT8U Hour_Point_Color; ///������ɫ
  INT8U Hour_Point_Style; //������ʽ
  
  INT8U Hour369_Point_Radius; //369��뾶
  INT8U Hour369_Point_Color;  //369����ɫ
  INT8U Hour369_Point_Style;  //369����ʽ

  INT8U Min_Point_Radius; //�ֵ�뾶
  INT8U Min_Point_Color;  //�ֵ���ɫ
  INT8U Min_Point_Style;  //�ֵ���ʽ,0Բ�Σ�1���Σ�2���֣�3����

  INT8U Hour_Line_Width;  //ʱ�ӿ��
  INT8U Hour_Line_Color;  //ʱ����ɫ
  
  INT8U Min_Line_Width; //���ӿ��
  INT8U Min_Line_Color;  //������ɫ
  
  INT8U Sec_Line_Width; //���ӿ��
  INT8U Sec_Line_Color; //������ɫ
  
  INT8U Date_Type;  //���ڱ�־,0��ʾ����ʾ����
  INT8U Date_Font; //����
  INT8U Date_Color; //������ɫ
  INT16U Date_X; //����λ����X���ϵı���
  INT16U Date_Y; //����λ����Y���ϵı���

  INT8U Week_Type;  //���ڱ�־��0��ʾ����ʾ����
  INT8U Week_Font;  //����
  INT8U Week_Color; //������ɫ
  INT16U Week_X; //����λ����X���ϵı���
  INT16U Week_Y; //����λ����Y���ϵı���

  INT8U Text_Color; //������ɫ
  INT16U Text_X; //����X
  INT16U Text_Y; //����Y
  INT16U Text_Width; //�������
  INT16U Text_Height; //�����߶�
  
  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Clock_Para;

//��ʱ����
typedef struct
{
  INT8U Head;
  
  BASE_PIC_PARA
//-------------------------------------------
  INT8U Dst_Year; //Ŀ����
  INT8U Dst_Month; //Ŀ����
  INT8U Dst_Date; //Ŀ����
  INT8U Dst_Hour; //Ŀ��ʱ
  INT8U Dst_Min; //Ŀ���
  INT8U Dst_Sec; //Ŀ����
  
  INT8U SmLineFlag; //�����б�־
  INT8U LineSpace;  //�м�࣬�ڶ�����ʾʱ��--����

  INT8U Timer_Type;  //��ʾ��ʽ
  INT8U Timer_Color; //��ʾ��ɫ
  INT8U Timer_Font; //��ʾ�ֺ�
  //INT8U Show_Posi; //��ʾλ��
  
  INT8U Temp; //����
  
  INT8U Text_Color; //������ɫ
  INT16U Text_X; //����X
  INT16U Text_Y; //����Y
  INT16U Text_Width; //�������
  INT16U Text_Height; //�����߶�
  
  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Timer_Para;

//����ʱ�����
typedef struct
{
  INT8U Head;
  
  BASE_PIC_PARA
//-------------------------------------------
  INT8U Diff_Flag;  //ʱ���־,0�ӣ�1��
  INT8U Hour_Diff;  //ʱ��Сʱ
  INT8U Min_Diff;   //ʱ�����
  //INT8U Sec_Diff;   //ʱ������
  
  INT8U Show_Mode;  //��ʾ��ʽ 
  INT8U Show_Color; //��ʾ��ɫ
  INT8U Show_Font; //��ʾ�ֺ�
  INT8U Show_Posi; //��ʾλ��
  
  INT8U Temp; //����

  INT8U SmLineFlag; //�����б�־
  INT8U LineSpace;  //�м�࣬�ڶ�����ʾʱ��--����
  
  INT8U Date_Type;  //���ڱ�־,0��ʾ����ʾ����
  INT8U Date_Font; //����
  INT8U Date_Color; //������ɫ
  INT16U Date_X;
  INT16U Date_Y;

  INT8U Week_Type;  //���ڱ�־��0��ʾ����ʾ����
  INT8U Week_Font;  //����
  INT8U Week_Color; //������ɫ
  INT16U Week_X;
  INT16U Week_Y;

  INT8U Time_Type;  //���ڱ�־��0��ʾ����ʾ����
  INT8U Time_Font;  //����
  INT8U Time_Color; //������ɫ
  INT16U Time_X;
  INT16U Time_Y;

  INT8U Text_Color; //������ɫ
  INT16U Text_X; //����X
  INT16U Text_Y; //����Y
  INT16U Text_Width; //�������
  INT16U Text_Height; //�����߶�
  
  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Time_Para;

//ũ����ʾ����
typedef struct
{
  INT8U Head;

  BASE_PIC_PARA
//-------------------------------------------
  INT8U Show_Mode;  //��ʾ��ʽ
  INT8U Show_Color; //��ʾ��ɫ
  INT8U Show_Font; //��ʾ�ֺ�
  INT8U Show_Posi; //��ʾλ��

  INT8U Temp; //����

  INT8U SmLineFlag; //�����б�־
  INT8U LineSpace;  //�м�࣬�ڶ�����ʾʱ��--����
  
  INT8U Tiangan_Type;  //��ɵ�֧��־,0��ʾ����ʾ���
  INT8U Tiangan_Font; //����
  INT8U Tiangan_Color; //�����ɫ
  INT16U Tiangan_X;
  INT16U Tiangan_Y;

  INT8U Nongli_Type;  //ũ����־��0��ʾ����ʾũ��
  INT8U Nongli_Font;  //����
  INT8U Nongli_Color; //ũ����ɫ
  INT16U Nongli_X;
  INT16U Nongli_Y;

  INT8U Jieqi_Type;  //���ڱ�־��0��ʾ����ʾ����
  INT8U Jieqi_Font;  //����
  INT8U Jieqi_Color; //������ɫ
  INT16U Jieqi_X;
  INT16U Jieqi_Y;

  INT8U Text_Color; //������ɫ
  INT16U Text_X; //����X
  INT16U Text_Y; //����Y
  INT16U Text_Width; //�������
  INT16U Text_Height; //�����߶�

  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Lun_Para;

//�¶Ȳ���
typedef struct
{
  INT8U Head;
  
  BASE_PIC_PARA
//-------------------------------------------
  INT8U Show_Mode;  //��ʾ��ʽ 
  INT8U Show_Color; //��ʾ��ɫ
  INT8U Show_Font; //��ʾ�ֺ�
  INT8U Show_Posi; //��ʾλ��
  
  INT8U Temp; //����

  INT8U Temp_Type;  //�¶���ʾ��ʽ
  INT8U Temp_Font;  //�¶�����
  INT8U Temp_Color; //�¶���ɫ
  INT16U Temp_X;    
  INT16U Temp_Y;
  
  INT8U Text_Color; //������ɫ
  INT16U Text_X; //����X
  INT16U Text_Y; //����Y
  INT16U Text_Width; //�������
  INT16U Text_Height; //�����߶�

  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Temp_Para;

//ʪ�Ȳ���
typedef struct
{
  INT8U Head;
  
  BASE_PIC_PARA
//-------------------------------------------
  INT8U Show_Mode;  //��ʾ��ʽ 
  INT8U Show_Color; //��ʾ��ɫ
  INT8U Show_Font; //��ʾ�ֺ�
  INT8U Show_Posi; //��ʾλ��
  
  INT8U Humidity; //����

  INT8U Humidity_Type;  //ʪ����ʾ��ʽ
  INT8U Humidity_Font;  //ʪ������
  INT8U Humidity_Color; //ʪ����ɫ
  INT16U Humidity_X;    
  INT16U Humidity_Y;
  
  INT8U Text_Color; //������ɫ
  INT16U Text_X; //����X
  INT16U Text_Y; //����Y
  INT16U Text_Width; //�������
  INT16U Text_Height; //�����߶�

  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Humidity_Para;

//��������
typedef struct
{
  INT8U Head;
  
  BASE_PIC_PARA
//-------------------------------------------
  INT8U Show_Mode;  //��ʾ��ʽ 
  INT8U Show_Color; //��ʾ��ɫ
  INT8U Show_Font; //��ʾ�ֺ�
  INT8U Show_Posi; //��ʾλ��
  
  INT8U Noise; //����

  INT8U Noise_Type;  //������ʾ��ʽ
  INT8U Noise_Font;  //��������
  INT8U Noise_Color; //������ɫ
  INT16U Noise_X;    
  INT16U Noise_Y;
  
  INT8U Text_Color; //������ɫ
  INT16U Text_X; //����X
  INT16U Text_Y; //����Y
  INT16U Text_Width; //�������
  INT16U Text_Height; //�����߶�

  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Noise_Para;

//���в���������
typedef union
{
#if PIC_SHOW_EN  
  S_Pic_Para Pic_Para;
#endif
#if CLOCK_SHOW_EN  
  S_Clock_Para Clock_Para;
#endif
#if TIMER_SHOW_EN  
  S_Timer_Para Timer_Para;
#endif
#if TIME_SHOW_EN  
  S_Time_Para Time_Para;
#endif
#if LUN_SHOW_EN  
  S_Lun_Para Lun_Para;
#endif
#if TEMP_SHOW_EN  
  S_Temp_Para Temp_Para;
#endif  
#if HUMIDITY_SHOW_EN
  S_Humidity_Para Humidity_Para;
#endif
#if NOISE_SHOW_EN
  S_Noise_Para Noise_Para;
#endif  
}U_File_Para;



typedef struct
{
  INT8U Head;
  STORA_DI Index[MAX_AREA_NUM][MAX_FILE_NUM+1]; //��һ���ļ�����ʼ����ǰһ���ļ��Ľ���,[MAX_FILE_NUM + 1]��ʾ���һ���ļ��Ľ���λ��
  //INT16U Block_End;
  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Prog_Block_Index;

//�ļ���ĳ��������ƫ��
/*
typedef struct
{
  INT8U Ctrl_Code;
  INT16U Len;
}S_File_Para_Info;
*/
/*
typedef struct
{
  INT8U Prog_No;  //��Ŀ��
  INT8U Area_No:4; //������
  INT8U File_No:4; //�ļ���
  //INT8U Screen_No; //����
  //INT8U Block_No; //���
  INT16U Len;     //֡����
  INT8U Buf[ONE_BLOCK_SIZE];
  
}S_Prog_Show_Data;
*/
typedef struct
{
  INT8U Head;
  INT16U Index;
  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Cur_Block_Index;
/*
typedef struct
{
    INT8U Head;
    INT8U Buf[ONE_BLOCK_SIZE];
    INT16U Index;
    INT8U Tail;
}S_Rcv_Show_Data;
*/
typedef struct
{
  INT8U Prog_No;
  INT8U File_No:4;  
  INT8U Area_No:4;
  INT8U Type;
  
  INT16U Seq0;
   
  INT16U Len;
  INT16U Bak;
  
}S_File_Para_Info;

#pragma pack()

typedef struct
{/*
  S_Pub_Buf Pub_Buf;  //����buf
  S_Show_1Color_Data One_Color_Data;
  S_Show_2Color_Data Two_Color_Data;
  S_Show_3Color_Data Three_Color_Data;
  */
  INT8U Head;
  INT8U Color_Data[2*MAX_POINTS/8];//---������2���ֽڱ�ʾ�˸���3����ɫ!!
  INT8U Tail;
}S_Show_Data;

#define SCREEN_PARA_LEN (sizeof(S_Screen_Para) -CHK_BYTE_LEN)
#define PROG_PARA_LEN   (sizeof(S_Prog_Para)-CHK_BYTE_LEN)
#define PROG_NUM_LEN    (sizeof(S_Prog_Num)-CHK_BYTE_LEN)
#define FILE_PARA_LEN (sizeof(U_File_Para)-CHK_BYTE_LEN)
#define BLOCK_INDEX_LEN (sizeof(S_Prog_Block_Index) - CHK_BYTE_LEN)
//#define BLOCK_DATA_LEN 249
#define BLOCK_HEAD_DATA_LEN 9
#define BLOCK_SHOW_DATA_LEN (BLOCK_DATA_LEN -BLOCK_HEAD_DATA_LEN)


#define MAX(a,b,c,d) (((a)>(b)?(a):(b))>(c)?((a)>(b)?(a):(b)):(c))>(d)?(((a)>(b)?(a):(b))>(c)?((a)>(b)?(a):(b)):(c)):(d)
#define MAX_COM_BUF_LEN (MAX(BLOCK_DATA_LEN , SCREEN_PARA_LEN, FILE_PARA_LEN, PROG_PARA_LEN)) + 20

typedef struct
{
  INT8U Head;
  INT8U Buf[MAX_COM_BUF_LEN];
  INT8U Tail;
}S_Pub_Buf;

#ifdef LED_PARA_C
EXT S_Pub_Buf _Pub_Buf = {CHK_BYTE,{0}, CHK_BYTE};
#else
EXT S_Pub_Buf _Pub_Buf;
#endif

EXT S_Screen_Para Screen_Para; //��ʾ����ز���
EXT S_Card_Para Card_Para;   //�忨֧�ֵĲ���
EXT S_Prog_Para Prog_Para;  //��ǰ��Ŀ����[MAX_PROGRAM_NUM]; //��Ŀ����
EXT S_Prog_Num Prog_Num;
//EXT S_Prog_Block_Index Prog_Block_Index; //��ǰ��Ŀ�Ĵ洢����
EXT S_Cur_Block_Index Cur_Block_Index;
//EXT S_Clock_Para Clock_Para;
//EXT S_Rcv_Show_Data Rcv_Show_Data;

EXT S_Time Cur_Time; //��ǰʱ�� 
EXT INT8U Get_Screen_Color_Num(void);
EXT void Chk_Baud_Change(INT8U Old_Baud);
EXT void Clr_All_Show_Data(void);
EXT void Chk_Data_Polarity_Change(INT8U Old_Polarity);
EXT INT8U Write_Prog_Num(void);
EXT INT8U Read_Prog_Num(void);
EXT INT16U Read_Screen_Para(void);
EXT INT8U Write_Screen_Para(void);
EXT INT16U _Read_Prog_Para(INT8U Prog_No, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen);
EXT INT16U Read_Prog_Para(INT8U Prog_No, S_Prog_Para *pProg_Para);
EXT INT8U Write_Prog_Para(INT8U Prog_No, INT8U *pSrc,INT16U SrcLen);
EXT INT8U Write_File_Para(INT8U Prog_No, INT8U Area_No, INT8U File_No, void *pSrc, INT16U SrcLen);
EXT INT8U Write_Cur_Block_Index(void *pSrc, INT16U SrcLen);
EXT INT8U Get_Show_Para_Len(INT8U Type);
EXT STORA_DI Get_Show_Para_Stora_DI(INT8U Prog_No, INT8U Area_No, INT8U File_No);
EXT INT16U Read_File_Para(INT8U Prog_No, INT8U Area_No, INT8U File_No, void *pDst, void *pDst_Start, INT16U DstLen);
EXT INT8U Chk_File_Para_HT_Sum(U_File_Para *pPara);
EXT void Set_File_Para_HT_Sum(U_File_Para *pPara);
EXT INT8U Write_Prog_Block_Index(void);
EXT INT16U Read_Prog_Para(INT8U Prog_No, S_Prog_Para *pProg_Para);
EXT INT16U Read_Prog_Block_Index(INT8U Prog_No);
EXT INT16U _Read_Prog_Block_Index(INT8U Prog_No, void *pDst, void *pDst_Start, INT16U DstLen);
EXT INT16S Read_Show_Data_Point(INT8U Area_No, INT8U File_No, U_File_Para *pFile_Para, INT16U SIndex, \
                                  S_Show_Data *pShow_Data, INT16U X, INT16U Y);
EXT INT16S Read_Show_Data(INT8U Area_No, INT8U File_No, U_File_Para *pFile_Para, INT16U SIndex, \
                      S_Show_Data *pShow_Data, INT16U *pX, INT16U *pY, INT16U *pWidth, INT16U *pHeight);
//}
#endif // LED_PARA_H
