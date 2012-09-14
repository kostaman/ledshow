#ifndef PUB_H
#define PUB_H

//extern "c"
//{
//#include "OS_Includes.h"
#include "OS_Cfg.h"
#include "OS_Port.h"
#include "OS_Pub.h"
#include <time.h>
#include "LED_Cfg.h"

#undef EXT
#ifndef PUB_C
#define EXT extern
#else
#define EXT
#endif

typedef struct
{
  INT8U Head;
  INT8U Ms100_Counts;
  INT8U Us100_Counts;
  //INT32U Ms10;  //10ms
  INT32U Ms100;

  INT32U Ms;
  INT32U Ms_Counts; //ms
    
  INT32U Sec;

  INT8U Tail;
}S_Pub_Timer;

//#define CHK_BYTE 0x55
//#define EQ  ==

#define PUB_BUF_MUTEX_ID 0x00 //�ź���ID������Pub_Bufʹ�õĻ���

#define mem_cpy OS_memcpy
//#define mem_set OS_memset
//#define TRACE() App_Trace//OS_Trace
#define Check_Sum OS_Check_Sum
#define Set_Sum OS_Set_Sum

#if defined ( __CC_ARM   )
#define nop() __nop()
#elif defined ( __ICCARM__ )
#define nop() __no_operation()
#else
#define nop()
#endif

/*
#if QT_EN == 0
#define debug OS_Debug_Print
#else
#define debug qDebug
#endif
*/
#define S_NUM(X) (sizeof(X)/sizeof(X[0]))
#define S_OFF(X,Y) (INT32U)(&(((X *)0)->Y))//���һ���ṹ���ƫ��

#define MAX_2(a,b) ((a)>(b)?(a):(b))
#define MIN_2(a,b) ((a)>(b)?(b):(a))

#define MAX_3(a,b,c) (MAX_2(a,b) > (c)?MAX_2(a,b):(c))
#define MIN_3(a,b,c) (MIN_2(a,b) < (c)?MIN_2(a,b):(c))

//��������ĳ�������ĺ귽��
/*
#define SET_VAR(X,Y,X_Addr,X_Len) do{if(((INT8U *)&(X))>=(INT8U *)(X_Addr) && ((INT8U *)&(X))<(INT8U *)(X_Addr)+(X_Len))\
                                                                                   X=Y;\
                                                                                 else\
                                                                                  ASSERT_FAILED();\
                                                                                }while(0)
 */
#define CHK_SUM(Var) _Check_STRUCT_Sum((void *)&(Var),(OS_INT8U *)((Var).CS))//OS_Check_STRUCT_Sum((void *)&(Var),sizeof(Var),(OS_INT8U *)(Var.CS),sizeof(Var.CS))
#define SET_SUM(Var) _Set_STRUCT_Sum((void *)&(Var),(OS_INT8U *)((Var).CS))//OS_Set_STRUCT_Sum((void *)&(Var),sizeof(Var),(OS_INT8U *)(Var.CS),sizeof(Var.CS))

#define SET_HT(V) do{V.Head = CHK_BYTE; V.Tail = CHK_BYTE;}while(0)
#define CHK_HT(V) ((V.Head == CHK_BYTE && V.Tail == CHK_BYTE)?1:0)
#define GET_VAR(A) A.Var
#define SET_VAR(A,B) do{A.Var = B; /*SET_SUM(A)*/;}while(0)

typedef struct
{
  INT8U Head;
  INT8U Time[7];

  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Time;


typedef struct
{
  const char *str;
  INT8U Len;

}S_Format_Str;
//EXT NO_INIT S_Trace_Info Trace_Info;

#define Pub_Buf _Pub_Buf.Buf

EXT volatile S_Pub_Timer Pub_Timer;

#define SEC_TIMER Pub_Timer.Sec
#define MS10_TIMER  Pub_Timer.Ms10

EXT INT16U Sum_2Bytes(INT8U Src[], INT16U SrcLen);
EXT void Check(void);
EXT void Info_Print(void);
EXT void TRACE(void);
EXT void S_Time_2_tm(S_Time *pTime, struct tm *ptm);
EXT void tm_2_S_Time(struct tm *ptm, S_Time *pTime);
EXT float Sqrt(float number);
EXT INT8U Hex2Bcd_Byte(INT8U Byte);
EXT INT8U Bcd2Hex_Byte(INT8U Byte);
EXT void Pub_Timer_Proc(void);
EXT INT8U _Check_STRUCT_Sum(void *pSrc,INT8U *pCS);
EXT void _Set_STRUCT_Sum(void *pSrc,INT8U *pCS);
//�ⲿ��ɵ�����Ϣ�������
extern void Put_Char(INT8S Chr);
#endif
