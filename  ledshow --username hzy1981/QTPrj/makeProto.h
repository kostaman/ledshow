#ifndef MAKEPROTO_H
#define MAKEPROTO_H

#include "..\Includes.h"
#include <QString>

#undef EXT
#ifdef MAKE_PROTO_C
#define EXT
#else
#define EXT extern
#endif

#define COM_MODE   0x00 //����
#define UDISK_MODE 0x01 //u��
#define PREVIEW_MODE   0x02 //Ԥ��ģʽ
#define SIM_MODE  0x03 //����ģʽ

typedef struct
{
   char seq;
   INT16U seq0;
   int len;
   int off;
}S_Frame_Info;

EXT S_Frame_Info frameInfo;
INT8U sendProtoData(char *pFrame, int len, int mode);
int makeFrame(char *data, int dataLen, char cmd, char seq, char *pDst);
INT8U makeProtoData(QString screenStr, int mode);
#endif // MAKEPROTO_H
