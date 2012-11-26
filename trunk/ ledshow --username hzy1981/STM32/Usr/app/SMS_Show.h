#ifndef SMS_SHOW_H
#define SMS_SHOW_H

#include "Includes.h"

#undef EXT
#ifdef SMS_SHOW_C
#define EXT
#else
#define EXT extern
#endif

#define SMS_NO_ERR          0x00
#define SMS_INDEX_ERR       0x01 //���������Ŵ���
#define SMS_LEN_ERR         0x02 //���ų��ȴ���
#define SMS_STORA_ERR       0x03 //���Ŵ洢����
#define SMS_PLAY_COUNTS_ERR 0x04 //���Ŵ�������
#define SMS_IN_MODE_ERR     0x05 //������Ч����
#define SMS_OUT_MODE_ERR    0x06 //�˳���Ч����
#define SMS_SPEED_ERR       0x07 //�ٶȴ���
#define SMS_STAY_TIME_ERR   0x08 //ͣ��ʱ�����
#define SMS_FORMAT_ERR      0x09//���Ÿ�ʽ����
#define SMS_TIME_ERR        0x0A //ʱ���ʽ����
#define SMS_FONT_ERR        0x0B //�������
#define SMS_COLOR_ERR       0x0C //��ɫ����
#define SMS_TXTHEAD_ERR     0x0D //�ı���ʼ�ַ�����
#define SMS_SCN_BASE_ERR    0x0E //���β��Ϸ�
#define SMS_SCN_OE_ERR      0x0F //OE���Դ���
#define SMS_SCN_DE_ERR      0x10 //���ݼ��Դ���
#define SMS_SCN_SCAN_ERR    0x11 //ɨ�跽ʽ����
#define SMS_SCN_COLOR_ERR   0x12 //��Ļ��ɫ����
#define SMS_PN_FULL_ERR     0x13 //�ֻ�������
#define SMS_UNAVAIL_ERR   0x20 //����Ч���ţ�����Ӧ��

#define SMS_FILE_PARA_LEN 250
#define SMS_MAX_DATA_LEN (SMS_FILE_PARA_LEN - sizeof(S_Txt_Para))
#define SMS_SUB_DATA_LEN (SMS_MAX_DATA_LEN / 3)//�����3������

#define SMS_PHONE_NO_LEN sizeof(S_SMS_Phone_No)

#define NULL_SMS_NO 0xFFFF

typedef struct
{
    INT8U Head;
    INT8U Flag[MAX_SMS_NUM / 8];
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_SMS_File_Flag;

typedef struct
{
    INT8U Head;
    INT8U Data[200];
    INT8U Tail;
}S_SMS_Data;

typedef struct
{
    INT8U Head;
    INT16U No;
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_SMS_Cur_No;

typedef struct
{
    INT8U Head;
    char No[10][30];
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_SMS_Phone_No;

typedef struct
{
  INT8U Head;
  char Data[SMS_FILE_PARA_LEN];
  INT8U Tail;

}S_SMS_WR_Buf;

EXT S_SMS_File_Flag SMS_File_Flag;
EXT S_SMS_Phone_No SMS_Phone_No; //��Ч�绰����
EXT S_SMS_Cur_No SMS_Cur_No;
EXT S_SMS_Data SMS_Data;
EXT S_SMS_WR_Buf SMS_WR_Buf; //SMS��д��buf
EXT INT8U SMS_File_Play_End(void);
EXT void Read_SMS_File_Flag(void);
EXT void Reset_Cur_SMS_File_No(void);
EXT INT16U Read_Cur_SMS_File_Para(void *pDst, void *pDst_Start, INT16U DstLen);
EXT void Find_Next_SMS_File_No(void);
EXT INT8U One_SMS_Proc(char *p);//, S_Txt_Para *pPara, char *pUSC, INT16U *pIndex, INT8U *pSubIndex);
EXT void smsMessageProc(SM_PARAM* pMsg, INT8U Num);
#endif
