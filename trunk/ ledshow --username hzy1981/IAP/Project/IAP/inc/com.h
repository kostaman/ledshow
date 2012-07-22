#ifndef COM_H
#define COM_H

#include "stm32f10x.h"

#undef EXT
#ifdef COM_C
#define EXT
#else
#define EXT extern
#endif

#define FRAME_HEAD 0x5A
#define FRAME_TAIL 0xAA
#define COM_BYTE 0x68

#define FHEAD  0x00 //֡ͷ,1
#define FLEN   0x01 //֡����,2
#define FADDR  0x03 //֡��ַ,2
#define FSEQ   0x05 //֡���,1
#define FSEQ0  0x06 //֡�����,2
#define FCMD   0x08 //������,2
#define FDATA  0x0A //��������

#define ASSERT_FAILED()

typedef struct
{
  uint8_t Head;

 uint8_t buf[5000];
 uint32_t posi;

  uint8_t Tail;
}S_Rcv_Buf;

EXT S_Rcv_Buf rcvBuf;

#endif
