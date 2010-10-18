#ifndef PUB_H
#define PUB_H

//extern "c"
//{

#include "LED_Cfg.h"
#include "STM32.h"
#include "QT_SIM.h"


#undef EXT
#ifndef PUB_C
#define EXT extern
#else
#define EXT
#endif

//------------------------
#define TRACE_EN  0
#define TRACE_NUM 10
#define TRACE_BUF_LEN 20

//#define ASSERT_EN 0
#define ASSERT_HOOK_EN 0

#define CS_BYTES 1
//-----------------------

#define CONST const
#define NO_INIT //__no_init

#define CHK_CS_BYTES 0xAAAAAAAA//��������У���������
#define CHK_BYTE 0x55

#define PRINT_NULL  0//����ӡ
#define PRINT_STDIO 1//��׼IO
#define PRINT_COMM  2//ͨ�ſڴ�ӡ

#define CS_SUM         0//�򵥺�У��
#define CS_CRC16_0     1//CRC16�㷨0
#define CS_CRC16_1     2//CRC16�㷨1

#define S_NUM(X) (sizeof(X)/sizeof(X[0]))
#define EQ  == 

#define SET_BIT(x,y) ((x)|=0x01<<(y))
#define CLR_BIT(x,y) ((x)&=~(0x01<<(y)))
#define GET_BIT(x,y) (((x)>>(y))&0x01)

#if TRACE_EN>0
#define TRACE() Trace(__FILE__,__FUNCTION__,(INT16U)__LINE__)
#define TRACE_CTRL(x) Trace_Ctrl(x)
#else
#define TRACE()
#define TRACE_CTRL(x)
#endif

//�ṹ��У��͵ļ�������У��꣬�ȵ�����ʹ�÷���
#define CHECK_STRUCT_SUM(Var) Check_STRUCT_Sum((void *)&(Var),sizeof(Var),(INT8U *)((Var).CS),sizeof((Var).CS))
#define SET_STRUCT_SUM(Var) Set_STRUCT_Sum((void *)&(Var),sizeof(Var),(INT8U *)((Var).CS),sizeof((Var).CS))
//��Դ��±����ָ��Ľṹ���У������
#define SET_PSTRUCT_SUM(Var,Var_Addr,Var_Len) do{if((INT8U *)((Var).CS)>=(INT8U *)(Var_Addr) &&\
                                                      (INT8U *)((Var).CS)+sizeof((Var).CS)<=(INT8U *)(Var_Addr)+(Var_Len))\
                                                       SET_STRUCT_SUM(Var);\
                                                    else\
                                                       ASSERT_FAILED();\
                                                   }while(0)
//��������ĳ�������ĺ귽��
#define SET_VAR(X,Y,X_Addr,X_Len) do{if(((INT8U *)&(X))>=(INT8U *)(X_Addr) && ((INT8U *)&(X))<(INT8U *)(X_Addr)+(X_Len))\
										   X=Y;\
										 else\
										   ASSERT_FAILED();\
										}while(0)

//�������x=y/z,���ڲ��ж�Z!=0
#define DIV(x,y,z) do{if(z!=0) x=y/z; else ASSERT_FAILED();}while(0)

//Buf�����Ͷ���,�����ڹ���buf�Ķ���
#define DECLARE_HT_BUF_TYPE(Type,Len,Name) typedef struct{\
                                          INT8U Head;\
                                          Type Buf[Len];\
                                          INT8U Tail;\
                                          }Name

//���õ����������Ͷ���,�����ھ�̬�ֲ������Ķ��壬���߲��Ǻ���Ҫ��ȫ�ֱ���
#define DECLARE_HT_VAR_TYPE(Type,Name) typedef struct{\
                                      INT8U Head;\
                                      Type Var;\
                                      INT8U Tail;\
                                      }Name;
//����һ����ͷβ�ĵ��������ͱ���
#define DECLARE_HT_VAR(Ext,Type,Name)  typedef struct{\
                                      INT8U Head;\
                                      Type Var;\
                                      INT8U Tail;\
                                      }_##Type;\
                                      Ext _##Type _##Name;

//����һ��������ͷ��β
#define SET_VAR_HT(Var) do{_#Var.Head=CHK_BYTE;_#Var.Tail=CHK_BYTE}while(0)
//���һ��������ͷ��β
#define CHECK_VAR_HT(Var) ((CHK_BYTE EQ _#Var.Head && CHK_BYTE EQ _#Var.Tail)?1:0) 

//����Ҫȫ�ֱ������߾�̬�ֲ��������������·�ʽ����
/*
typedef struct
{
  INT8U Head;
  //�˴��������
  INT8U Tail;
}type_name;
*/

//���ṹ�������ͷ��β�Ƿ���ȷ
#define CHECK_STRUCT_HT(Var) ((CHK_BYTE EQ (Var).Head  && CHK_BYTE EQ (Var).Tail)?1:0)
//��ʼ���ṹ�������ͷ��β
#define SET_STRUCT_HT(Var)  do{(Var).Head=CHK_BYTE; (Var).Tail=CHK_BYTE;}while(0)

typedef struct
{
  INT8U Head;
  INT8U Buf[500];
  INT8U Tail;  
}S_Pub_Buf;

typedef struct
{
  INT8U Head;
  INT8U Var;
  INT8U Tail;
}S_Int8U;

/*
DECLARE_HT_VAR_TYPE(INT8U,S_Int8U);
DECLARE_HT_VAR_TYPE(INT16U,S_Int16U);
DECLARE_HT_VAR_TYPE(INT32U,S_Int32U);
DECLARE_HT_VAR_TYPE(INT8S,S_Int8S);
DECLARE_HT_VAR_TYPE(INT16S,S_Int16S);
DECLARE_HT_VAR_TYPE(INT32S,S_Int32S);
*/
typedef struct
{
  INT8U Head;
  
  INT8S File[TRACE_NUM][TRACE_BUF_LEN];
  INT8S Func[TRACE_BUF_LEN];
  INT8U Task_ID[TRACE_NUM];//���õ������
  INT16U Line[TRACE_NUM];//���õ��к�
  INT16U Counts[TRACE_NUM];//���õĴ���
  INT8U Index;//��ǰ��������
  
  INT32U On_Off_Flag;//���Կ��ر�־
  INT8U Entry_Flag; //������Ժ�����־
  
  INT8U Tail;
}S_Trace_Info;

EXT NO_INIT S_Trace_Info Trace_Info;
#ifdef PUB_C
EXT S_Pub_Buf _Pub_Buf = {CHK_BYTE,{0}, CHK_BYTE};
#else
EXT S_Pub_Buf _Pub_Buf;
#endif

#define Pub_Buf _Pub_Buf.Buf

EXT void Trace(CONST INT8S File[],CONST INT8S Function[],INT16U Line);
EXT void Assert_Failed(CONST INT8S File[],CONST INT8S Function[],INT16U Line);
EXT void Assert(BOOL Conditon,CONST INT8S File[],CONST INT8S Function[],INT16U Line);
EXT void Trace_Ctrl(INT32U Flag);
EXT void Trace_Info_Check(void);

EXT void Debug_Print(CONST INT8S *format,...);
EXT void _Debug_Print(CONST INT8S *format,...);
EXT void mem_cpy(void *pDst, void *pSrc,INT32U SrcLen,void *pDst_Start,INT32U DstLen);
EXT void mem_set(void *pDst, INT8U Value,INT32U SetLen,void *pDst_Start,INT32U DstLen);

EXT INT16U Crc16_0(INT8U *pSrc, INT16U Len);
EXT INT16U Crc16_1(INT8U *pSrc, INT16U Len);
EXT INT8U Check_Sum(void *pSrc,INT16U SrcLen,void *pCS,INT8U CS_Bytes);
EXT void Set_Sum(void *pSrc,INT16U SrcLen,void *pDst,INT8U CS_Bytes,void *pDst_Start,INT16U DstLen);

EXT INT8U Check_STRUCT_Sum(void *pSrc,INT16U SrcLen,INT8U *pCS,INT8U CS_Bytes);
EXT void Set_STRUCT_Sum(void *pSrc,INT16U SrcLen,INT8U *pCS,INT8U CS_Bytes);
EXT INT16U Sum_2Bytes(INT8U Src[], INT16U SrcLen);
EXT void Check(void);
EXT void Info_Print(void);
//�ⲿ��ɵ�����Ϣ�������
extern void Put_Char(INT8S Chr);
//}
#endif
