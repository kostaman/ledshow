#ifndef LED_PARA_H
#define LED_PARA_H

//extern "c"
//{
#undef EXT
#ifdef LED_PARA_C
#define EXT
#else
#define EXT extern
#endif

//ʱ������
#define T_YEAR  0
#define T_MONTH 1
#define T_DATE  2
#define T_HOUR  3
#define T_MIN   4
#define T_SEC   5
#define T_WEEK  6

#define FAC_PARA_FILE  0 //���������ļ�
#define USR_PARA_FILE  1 //�û������ļ�
#define PROG_PARA_FILE 2 //��Ŀ�����ļ�
#define PROG_DATA_FILE 3 //��Ŀ�����ļ�

#define FILE_R 0//�ļ���
#define FILE_W 1//�ļ�д
#define FILE_WR 2//�ļ�����д

#define MAX_FILE_NAME_SIZE 20

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

  INT8U Value; //����ֵ
  INT8U Start_Hour; //��ʼСʱ

  //INT8U Tail;
}S_Lightness;

//���ػ�ʱ������
typedef struct
{
  //INT8U Head;

  INT8U Open_Hour;
  INT8U Open_Min;
  INT8U Close_Hour;
  INT8U Close_Min;

  //INT8U Tail;
}S_Open_Close_Time;

typedef struct
{
  INT8U Week; //����
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

  S_Open_Close_Time Open_Close_Time; //���ػ�ʱ��
  S_Lightness Lightness; //ǿ��

  INT8U Program_Num; //��Ŀ��
  INT8U CS[CS_BYTES];

  INT8U Tail;
}S_Screen_Para;


//��Ŀ����
typedef struct
{
  INT8U Program_No; //��Ŀ��
  //INT8U Program_Cycles; //ѭ������
  //INT16U Program_Stay_Sec; //ͣ������
  S_Program_Timing Timing[3]; //��Ŀ��ʱ����
  INT8U Area_Num; //������
  S_Area Area[MAX_AREA_NUM]; //������
  INT8U Main_Area_No; //��������
  INT8U CS[CS_BYTES];
}S_Program_Para;

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
  
  INT8U Bk_Color; //������ɫ
  INT16U Bk_X; //����X
  INT16U Bk_Y; //����Y
  INT16U Bk_Width; //�������
  INT16U Bk_Height; //�����߶�
  
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
  
  INT8U Show_Mode;  //��ʾ��ʽ 
  INT8U Show_Color; //��ʾ��ɫ
  INT8U Show_Font; //��ʾ�ֺ�
  INT8U Show_Posi; //��ʾλ��
  
  INT8U Temp; //����
  
  INT8U Bk_Color; //������ɫ
  INT16U Bk_X; //����X
  INT16U Bk_Y; //����Y
  INT16U Bk_Width; //�������
  INT16U Bk_Height; //�����߶�
  
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

  INT8U Show_Mode;  //��ʾ��ʽ 
  INT8U Show_Color; //��ʾ��ɫ
  INT8U Show_Font; //��ʾ�ֺ�
  INT8U Show_Posi; //��ʾλ��
  
  INT8U Temp; //����
  
  INT8U Bk_Color; //������ɫ
  INT16U Bk_X; //����X
  INT16U Bk_Y; //����Y
  INT16U Bk_Width; //�������
  INT16U Bk_Height; //�����߶�
  
  INT8U Tail;
}S_Time_Para;

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
  
  INT8U Bk_Color; //������ɫ
  INT16U Bk_X; //����X
  INT16U Bk_Y; //����Y
  INT16U Bk_Width; //�������
  INT16U Bk_Height; //�����߶�
  
  INT8U Tail;
}S_Temp_Para;

//���в���������
typedef union
{
  S_Pic_Para Pic_Para;
  S_Clock_Para Clock_Para;
  S_Timer_Para Timer_Para;
  S_Time_Para Time_Para;
  S_Temp_Para Temp_Para;
  
}U_File_Para;


//�ļ���ĳ��������ƫ��
typedef struct
{
  INT8U Ctrl_Code;
  INT16U Len;
}S_File_Para_Info;

EXT S_Screen_Para Screen_Para; //��ʾ����ز���
EXT U_File_Para File_Para[MAX_AREA_NUM]; //��ǰ�������ļ������������ļ�ʱˢ��֮
EXT S_Program_Para Program_Para;  //��ǰ��Ŀ����[MAX_PROGRAM_NUM]; //��Ŀ����

//EXT S_Clock_Para Clock_Para;

EXT S_Time Cur_Time; //��ǰʱ�� 
EXT void Read_Screen_Para();
EXT char * Get_Program_Data_File_Name(INT8U Prog_No, INT8U Area_No, char File_Name[]);
EXT INT32S File_Read_One_Frame(FILE_T File, INT32U Offset, INT8U *pSeq, INT16U *pCtrl, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen);
EXT INT8U Save_Para_Frame_Proc(INT8U Frame[], INT16U FrameLen);
EXT INT8U Save_Prog_Property_Frame_Proc(INT8U Frame[],INT16U FrameLen);
EXT INT8U Save_Prog_Data_Frame_Proc(INT8U Frame[],INT16U FrameLen);
EXT INT8U Del_Prog_Data(INT8U Frame[], INT16U FrameLen);
EXT INT8U Check_Update_Program_Para();
EXT void Read_Para();
//}
#endif // LED_PARA_H
