#ifndef LED_PARA_H
#define LED_PARA_H

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
#define SHOW_FLASH 0x07 //����

//#define MAX_FILE_NAME_SIZE 20

#define SPACE_WIDTH 8

#define CHK_BYTE_LEN 3 //�ṹ��������У����ֽ���--һ����Head��Tail��CS
#define CHK_HEAD_LEN 1 //�ṹ��������У���ͷ�ֽ���--һ����Head

#define PROG_NULL_MODE 0x00
#define PROG_COUNTS_MODE 0x01
#define PROG_TIME_MODE  0x02

typedef struct
{
  INT8U Head;
  INT8U Time[7];
  //INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Time;

typedef struct
{
  //INT8U Head;
  INT8U Flag;
  INT8U Value; //����ֵ
  INT8U Start_Hour; //��ʼСʱ

  //INT8U Tail;
}S_Lightness;

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
  INT8U Week; //����--ȫ0��ʾ�����ţ���0λ��ʾ�����գ�1-6��ʾ����1-����6
  
  INT8U Start_Date[3]; //��ʼ������
  INT8U End_Date[3];	//����������  
  
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

//��Ļ����
typedef struct
{
  INT8U Head;

  INT16U Width; //���
  INT16U Height; //�߶�
  INT8U Color; //��ɫ 0��ɫ��1˫ɫ��2��ɫ��3-255���Ҷ�
  
  INT8U Addr; //��ַ
  INT32U IP; //IP��ַ
  INT8U Baud;  //������

  S_Open_Close_Time Open_Close_Time[MAX_OPEN_CLOSE_TIME]; //���ػ�ʱ��
  S_Lightness Lightness[MAX_LIGHTNESS_TIME]; //ǿ��

  INT8U Prog_Num; //��Ŀ��
  INT8U CS[CS_BYTES];

  INT8U Tail;
}S_Screen_Para;


//��Ŀ����
typedef struct
{
  INT8U Head;
  INT8U Prog_No; //��Ŀ��
  
  INT8U Mode; //���ŷ�ʽ��0��ʾѭ�����ţ�1��ʾ��������
  INT16U Counts; //ѭ������
  INT32U Time; //ͣ������
  
  S_Program_Timing Timing[3]; //��Ŀ��ʱ����
  INT8U Area_Num; //������
  INT8U Main_Area_No; //��������
  INT8U Area_File_Num[MAX_AREA_NUM]; //ÿ�����ļ���
  S_Area Area[MAX_AREA_NUM]; //������
  
  INT8U Border_Speed; //�߿������ٶ�
  INT8U Border_Mode;  //�߿�ģʽ
  INT8U Border_Width;   //�߿���
  INT8U Border_Height;  //�߿�߶�
  INT8U Temp;   //����
  INT8U Border_Data[3*MAX_BORDER_POINTS/8]; //�߿�����
  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Prog_Para;

typedef struct
{
  INT8U Head;
  
  INT8U Flag; //��־
  INT8U Prog_No; //��Ŀ��
  INT8U Area_No; //������
  INT8U File_No; //�ļ���
  INT8U In_Mode; //���뷽ʽ
  INT8U In_Speed; //�����ٶ�
  INT8U Add_Mode; //׷�ӷ�ʽ
  INT16U Stay_Time; //ͣ��ʱ�䣬���λΪ��λ��0��ʾs��1��ʾms
  INT8U Out_Mode; //������ʽ  
  
  INT8U Tail;
}S__Para;

//ͼ�Ĳ���
typedef struct
{
  INT8U Head;
  
  INT8U Flag; //��־
  INT8U Prog_No; //��Ŀ��
  INT8U Area_No; //������
  INT8U File_No; //�ļ���
  INT8U In_Mode; //���뷽ʽ
  INT8U In_Speed; //�����ٶ�
  INT8U Add_Mode; //׷�ӷ�ʽ
  INT16U Stay_Time; //ͣ��ʱ�䣬���λΪ��λ��0��ʾs��1��ʾms
  INT8U Out_Mode; //������ʽ	
  INT8U Color; //��ɫ
  INT16U SNum; //��������
  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Pic_Para;

//���̲���
typedef struct
{
  INT8U Head;
  
  INT8U Flag; //��־
  INT8U Prog_No; //��Ŀ��
  INT8U Area_No; //������
  INT8U File_No; //�ļ���
  INT8U In_Mode; //���뷽ʽ
  INT8U In_Speed; //�����ٶ�
  INT8U Add_Mode; //׷�ӷ�ʽ
  INT16U Stay_Time; //ͣ��ʱ�䣬���λΪ��λ��0��ʾs��1��ʾms
  INT8U Out_Mode; //������ʽ	
 
  INT8U Diff_Flag;  //ʱ���־,0�ӣ�1��  
  INT8U Hour_Diff;  //ʱ��Сʱ
  INT8U Min_Diff;   //ʱ�����
  //INT8U Sec_Diff;   //ʱ������
  
  INT8U Hour_Point_Radius; //����뾶
  INT8U Hour_Point_Color; ///������ɫ
  
  INT8U Hour369_Point_Radius; //369��뾶
  INT8U Hour369_Point_Color;  //369����ɫ
  
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
  
  INT8U Flag; //��־
  INT8U Prog_No; //��Ŀ��
  INT8U Area_No; //������
  INT8U File_No; //�ļ���
  INT8U In_Mode; //���뷽ʽ
  INT8U In_Speed; //�����ٶ�
  INT8U Add_Mode; //׷�ӷ�ʽ
  INT16U Stay_Time; //ͣ��ʱ�䣬���λΪ��λ��0��ʾs��1��ʾms
  INT8U Out_Mode; //������ʽ	

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
  
  INT8U Flag; //��־
  INT8U Prog_No; //��Ŀ��
  INT8U Area_No; //������
  INT8U File_No; //�ļ���
  INT8U In_Mode; //���뷽ʽ
  INT8U In_Speed; //�����ٶ�
  INT8U Add_Mode; //׷�ӷ�ʽ
  INT16U Stay_Time; //ͣ��ʱ�䣬���λΪ��λ��0��ʾs��1��ʾms
  INT8U Out_Mode; //������ʽ	

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

  INT8U Flag; //��־
  INT8U Prog_No; //��Ŀ��
  INT8U Area_No; //������
  INT8U File_No; //�ļ���
  INT8U In_Mode; //���뷽ʽ
  INT8U In_Speed; //�����ٶ�
  INT8U Add_Mode; //׷�ӷ�ʽ
  INT16U Stay_Time; //ͣ��ʱ�䣬���λΪ��λ��0��ʾs��1��ʾms
  INT8U Out_Mode; //������ʽ

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
  
  INT8U Flag; //��־
  INT8U Prog_No; //��Ŀ��
  INT8U Area_No; //������
  INT8U File_No; //�ļ���
  INT8U In_Mode; //���뷽ʽ
  INT8U In_Speed; //�����ٶ�
  INT8U Add_Mode; //׷�ӷ�ʽ
  INT16U Stay_Time; //ͣ��ʱ�䣬���λΪ��λ��0��ʾs��1��ʾms
  INT8U Out_Mode; //������ʽ	

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

//���в���������
typedef union
{
  S_Pic_Para Pic_Para;
  S_Clock_Para Clock_Para;
  S_Timer_Para Timer_Para;
  S_Time_Para Time_Para;
  S_Lun_Para Lun_Para;
  S_Temp_Para Temp_Para;
  
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
  
  INT8U Seq0;
   
  INT16U Len;
  INT16U Bak;
  
}S_File_Para_Info;

typedef struct
{/*
  S_Pub_Buf Pub_Buf;  //����buf
  S_Show_1Color_Data One_Color_Data;
  S_Show_2Color_Data Two_Color_Data;
  S_Show_3Color_Data Three_Color_Data;
  */
  INT8U Head;
  INT8U Color_Data[3*MAX_POINTS/8];//---������3���ֽڱ�ʾ�˸���3����ɫ!!
  INT8U Tail;
}S_Show_Data;

#define SCREEN_PARA_LEN (sizeof(S_Screen_Para) -CHK_BYTE_LEN)
#define PROG_PARA_LEN   (sizeof(S_Prog_Para)-CHK_BYTE_LEN)
#define FILE_PARA_LEN (sizeof(U_File_Para)-CHK_BYTE_LEN)
#define BLOCK_INDEX_LEN (sizeof(S_Prog_Block_Index) - CHK_BYTE_LEN)
#define BLOCK_DATA_LEN 300
#define BLOCK_HEAD_DATA_LEN 8
#define BLOCK_SHOW_DATA_LEN (BLOCK_DATA_LEN -BLOCK_HEAD_DATA_LEN)

EXT S_Screen_Para Screen_Para; //��ʾ����ز���

EXT S_Prog_Para Prog_Para;  //��ǰ��Ŀ����[MAX_PROGRAM_NUM]; //��Ŀ����
//EXT S_Prog_Block_Index Prog_Block_Index; //��ǰ��Ŀ�Ĵ洢����
EXT S_Cur_Block_Index Cur_Block_Index;
//EXT S_Clock_Para Clock_Para;
//EXT S_Rcv_Show_Data Rcv_Show_Data;

EXT S_Time Cur_Time; //��ǰʱ�� 

EXT INT8U Get_Screen_Color_Num();
EXT void Read_Screen_Para();
EXT INT8U Get_Show_Para_Len(INT8U Type);
EXT STORA_DI Get_Show_Para_Stora_DI(INT8U Prog_No, INT8U Area_No, INT8U File_No);
EXT INT8U Save_Para_Frame_Proc(INT8U Frame[], INT16U FrameLen);
EXT INT8U Save_Prog_Property_Frame_Proc(INT8U Frame[],INT16U FrameLen);
EXT INT8U Save_Show_Data_Frame_Proc(INT8U Frame[],INT16U FrameLen);
EXT INT16U Read_File_Para(INT8U Prog_No, INT8U Area_No, INT8U File_No, void *pDst, void *pDst_Start, INT16U DstLen);

EXT INT8U Check_Update_Prog_Para();
EXT INT16U Read_Prog_Para(INT8U Prog_No);
EXT INT16U Read_Prog_Block_Index(INT8U Prog_No);
EXT INT16U Read_Show_Data(INT8U Area_No, INT8U File_No, INT8U Flag, INT16U SIndex, \
                      S_Show_Data *pShow_Data);
//}
#endif // LED_PARA_H
