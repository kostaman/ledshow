#ifndef MAKEPROTO_H
#define MAKEPROTO_H

#include "..\Stm32\usr\app\Includes.h"
#include <QextSerialPort>
#include <QextSerialEnumerator>
#include <QString>

#undef EXT
#ifdef MAKE_PROTO_C
#define EXT
#else
#define EXT extern
#endif

#define COM_MODE   0x00 //����
#define ETH_MODE   0x01 //��̫��ģʽ
#define GPRS_MODE  0x02 //GPRSģʽ
#define UDISK_MODE 0x03 //u��
#define PREVIEW_MODE   0x04 //Ԥ��ģʽ
#define SIM_MODE  0x05 //����ģʽ
#define NULL_MODE 0xFF

typedef struct
{
   char seq;
   INT16U seq0;
   int len;
   int off;
}S_Frame_Info;

/*
typedef struct
{
  S_COM_Para COM_Para;
  S_ETH_Para ETH_Para;
  S_GPRS_Para GPRS_Para;

  INT8U Com_Port; //���ڵĶ˿ں�-��̨��
  INT8U Com_Mode; //ѡ��ͨ��ģʽ-��̨��

  QextSerialPort * port;

  INT8U Rcv_Buf[1000];
  INT16U Rcv_Posi;

  int status;
}S_COM_Status;
*/
EXT S_Frame_Info frameInfo;
//EXT S_COM_Status comStatus; //ͨ��״̬
//INT8U initComStatus();
//INT8U connectScreen();
//INT8U disconnectScreen();
INT8U sendProtoData(char *pFrame, int len);
int makeFrame(char *data, int dataLen, char cmd, char seq, char *pDst);
INT8U makeProtoData(QString screenStr, int mode, int flag);
#endif // MAKEPROTO_H
