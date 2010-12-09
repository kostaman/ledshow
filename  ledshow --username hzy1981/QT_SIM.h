#ifndef QT_SIM_H
#define QT_SIM_H

#if QT_EN > 0
//#include "LED_Cfg.h"
#include <QtGlobal>

#undef EXT
#ifdef QT_SIM_C
#define EXT
#else
#define EXT extern
#endif


//�������,���ʹ�ã���������
#if ASSERT_EN>0
#define ASSERT(x) //Assert((BOOL)(x),__FILE__,__FUNCTION__,(INT16U)__LINE__)
#define ASSERT_FAILED() qDebug("file:%s, line:%d",__FILE__, __LINE__)//Assert_Failed(__FILE__,__FUNCTION__,(INT16U)__LINE__)
#else
#define ASSERT(x)
#define ASSERT_FAILED()
#endif

typedef unsigned int INT32U;
typedef int INT32S;
typedef unsigned short int INT16U;
typedef short int INT16S;
typedef unsigned char INT8U;
typedef char INT8S;
typedef unsigned char BOOL;

#define FILE_R  0
#define FILE_W  1
#define FILE_WR 2

#define FILE_T char *

#define FILE_FRAME_ERR -2 //�ļ�֡����

#define FILE_NULL -2 //�ļ������� 
#define FILE_ERR -1 //�ļ�����
#define FILE_END 0  //�ļ���β
#define FILE_OK  1 //�ļ�ok

#define START_SHOW_TIMER_INT
#define STOP_SHOW_TIMER_INT

typedef struct
{
  INT8U Head;
  
  INT32U Ms10;  //10ms
  INT32U Sec;
  
  INT8U Tail;
}S_Pub_Timer;

EXT S_Pub_Timer Pub_Timer;
EXT void Put_Char(char c);
EXT INT8U Get_Cur_Time(INT8U Time[]);//S_Time *pTime);
EXT INT8U Set_Cur_Time(INT8U Time[]);//S_Time *pTime);
EXT FILE_T File_Open(char File_Name[], INT8U WR_Flag);
EXT INT8S File_Read(FILE_T file, INT32U Offset, INT16U Len, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen);
EXT INT8S File_Write(FILE_T file, INT32U Offset, INT8U Buf[], INT16U Len);
EXT INT8S File_Close(FILE_T file);
EXT INT8S File_Delete(char File_Name[]);
EXT INT32S File_Size(FILE_T File);
#endif
#endif