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

#define COM_MODE   0x00 //串口
#define ETH_MODE   0x01 //以太网模式
#define GPRS_MODE  0x02 //GPRS模式
#define UDISK_MODE 0x03 //u盘
#define WIFI_MODE  0x04 //Wifi
#define PREVIEW_MODE   0x05 //预览模式
#define SIM_MODE  0x06 //仿真模式
#define NULL_MODE 0xFF

#define COM_MODE_STR  "串口"
#define ETH_MODE_STR  "网口"
#define GPRS_MODE_STR "GPRS"
#define WIFI_MODE_STR "WIFI"
#define UDISK_MODE_STR "U盘"

#define PROTO_FILE_FLAG 0x00
#define PROTO_BUF_FLAG 0x01

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
  S_Net_Para Net_Para;
  //S_GPRS_Para GPRS_Para;

  INT8U Com_Port; //串口的端口号-主台用
  INT8U Com_Mode; //选用通信模式-主台用

  QextSerialPort * port;

  INT8U Rcv_Buf[1000];
  INT16U Rcv_Posi;

  int status;
}S_COM_Status;
*/
EXT S_Frame_Info frameInfo;
//EXT S_COM_Status comStatus; //通信状态
//INT8U initComStatus();
//INT8U connectScreen();
//INT8U disconnectScreen();

INT8U sendProtoData(char *pFrame, int len);
int _makeFrame(char *data, int dataLen, INT16U addr, char cmd0, char cmd1, char seq, INT16U seq0, char *pDst);
int makeFrame(char *data, int dataLen, char cmd, char seq, char *pDst);
INT8U makeProtoBufData(QString screenStr, int mode, INT8U cmd , char buf[], int bufLen);
INT8U makeProtoFileData(QString screenStr, int mode, int flag);
#endif // MAKEPROTO_H
