#ifndef COM_H
#define COM_H

#include "Pub.h"

#undef EXT
#ifdef COM_C
#define EXT
#else
#define EXT extern
#endif

#define FRAME_HEAD 0x5A
//#define FRAME_HEAD1 0xA5
#define FRAME_TAIL  0xAA

//�����붨��
//#define C_SCREEN_WH   0x01 //��Ļ���
//#define C_SCREEN_ADDR 0x02 //��Ļ��ַ
//#define C_SCREEN_IP   0x03 //IP��ַ
//#define C_SCREEN_BAUD 0x04 //ͨ������
#define C_SCREEN_BASE_PARA 0x03 //��������
#define C_SCREEN_COM_PARA 0x04 //ͨ�Ų���
#define C_SCAN_MODE      0x05 //ɨ�����
#define C_SCREEN_OC_TIME 0x06 //��ʱ���ػ�ʱ��
#define C_SCREEN_LIGNTNESS 0x07 //����
#define C_SCREEN_TIME 0x08 //ʱ��
#define C_PROG_NUM    0x09 //��Ŀ��
#define C_DEL_PROG    0x0A //ɾ����Ŀ
#define C_PROG_PARA  0x0B //��Ŀ����
#define C_PROG_DATA  0x0C //��ʾ����
#define C_SCREEN_INFO 0x0D //��Ļ��Ϣ
#define C_UPDATE      0x0E //�̼�����
/*
0	0x5A	֡ͷ
1	Len0	֡���ȵ��ֽ�(��֡ͷ��֡β)
2	Len1	֡���ȸ��ֽ�
3	Addr0	��ַ���ֽ�
4       Addr1   ��ַ���ֽ�
5	Seq	֡���, 0-255 ѭ������,�ط���������Ų���
6       Seq00   ֡����ŵ��ֽ�
7       Seq01   ֡����Ÿ��ֽ�
8	Cmd0	��������ֽ�
9	Cmd1	��������ֽ�
A	��	֡����������
        ��
        CS0	У������ֽ�,��֡ͷ��CS0ǰһ���ֽڵĺ�
        CS1	У������ֽ�
        0xAA	֡β
*/
#define FHEAD  0x00 //֡ͷ,1
#define FLEN   0x01 //֡����,2
#define FADDR  0x03 //֡��ַ,2
#define FSEQ   0x05 //֡���,1
#define FSEQ0  0x06 //֡�����,2
#define FCMD   0x08 //������,2
#define FDATA  0x0A //��������
//#define FTAIL  //֡β��

#define F_NDATA_LEN 13 //һ��֡�ڷ�������ĳ���

#define FRAME_FLAG  0xAF
/*
//ͨ�Ž������ݵĻ�����
typedef struct
{
  INT8U Head;
  INT8U Flag; //�Ƿ��յ�һ֡��־
  INT16U Posi; //��ǰ�洢λ��
  INT8U Data[BLOCK_DATA_LEN];
  INT8U Tail;
}S_Rcv_Buf;

EXT S_Rcv_Buf Rcv_Buf;
*/
EXT void Rcv_One_Byte(INT8U Byte);
EXT INT8U Check_Frame_Format(INT8U Frame[], INT16U Frame_Len);
EXT INT8U Screen_Para_Frame_Proc(INT16U Ctrl_Code, INT8U Data[], INT16U Len);
EXT INT8U Rcv_Frame_Proc(INT8U Frame[], INT16U FrameLen);
EXT INT16U Make_Frame(INT8U *pData, INT16U Len, INT8U Addr[], INT8U Cmd, INT8U Cmd0, INT8U Seq, INT16U Seq0, char *pDst);
EXT void Screen_Com_Proc();
#endif
