#ifndef COM_H
#define COM_H

#include "Pub.h"
#include "LED_Cfg.h"

#undef EXT
#ifdef COM_C
#define EXT
#else
#define EXT extern
#endif

#define FRAME_HEAD 0x5A
#define FRAME_TAIL 0xAA
#define COM_BYTE 0x68

#define RD_CMD  0x00
#define WR_CMD  0x20

#define COM_STANDBY_SEC 3

//�������2λ�������Ӧ��֡�ǿ϶�Ӧ���Ƿ�Ӧ��,0x40��ʾ�϶�Ӧ��,0x80��ʾ��Ӧ��
//��5λ��ʾ������д,1��ʾд,0��ʾ��
//��0-5λ��ʾ������

//�����붨��
//#define C_SCREEN_WH   0x01 //��Ļ���
//#define C_SCREEN_ADDR 0x02 //��Ļ��ַ
//#define C_SCREEN_IP   0x03 //IP��ַ
//#define C_SCREEN_BAUD 0x04 //ͨ������
#define C_SCREEN_BASE_PARA 0x00 //��������
#define C_SCREEN_COM_PARA 0x01 //����ͨ�Ų���
#define C_SCREEN_ETH_PARA 0x02 //��̫������
#define C_SCREEN_GPRS_PARA 0x03 //GPRS����
#define C_SCREEN_PARA    0x04 //������Ļ����
#define C_SCAN_PARA      0x05 //ɨ�����
#define C_SCREEN_OC_TIME 0x06 //��ʱ���ػ�ʱ��
#define C_SCREEN_OC    0x07 //���ػ�
#define C_SCREEN_LIGNTNESS 0x08 //����
#define C_SCREEN_TIME 0x09 //ʱ��
#define C_PROG_NUM    0x0A //��Ŀ��
#define C_PROG_PARA  0x0B //��Ŀ����
#define C_PROG_DATA  0x0C //��ʾ����
#define C_SOFT_VERSION 0x0D //��Ļ��Ϣ
#define C_SELF_TEST 0x0E //�Զ����
#define C_UPDATE      0x0F //�̼�����

#define CLOSE_FLAG 0x5A
#define OPEN_FLAG  0xA5

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

#define SOFT_VERSION_LEN 30

#define FRAME_FLAG  0xAF

#define CH_COM  0x00
#define CH_GPRS  0x01
#define CH_NET 0x02
#define CH_UDISK  0x03 //UDisk����Ҫ������Buf������ʹ�� COM_BUF�����Ǵ���ͨ�ŵ�Buf
#define CH_SIM 0x04 //����
//#define RCV_BUF_NUM 1

#define READ_FLAG 0x00
#define SET_FLAG  0x01

#define COM_ERR_PARA_INVALID 0x01 //�������Ϸ�
#define COM_ERR_PARA_LEN_ERR 0x02 //�������ȴ���

#define RCV_DATA_BUF Screen_Status.Rcv_Data
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
EXT void Send_Frame_Proc(INT8U Ch, INT8U Frame[], INT16U FrameLen);
EXT INT32U Get_Com_Baud(void);
EXT void Com_Rcv_Byte(INT8U Ch, INT8U Byte);
EXT INT8U Check_Frame_Format(INT8U Frame[], INT16U Frame_Len);
EXT INT8U Save_Prog_Para_Frame_Proc(INT8U Frame[],INT16U FrameLen);
EXT INT8U Save_Prog_Data_Frame_Proc(INT8U Frame[],INT16U FrameLen);
EXT INT8U Save_Screen_Para_Frame_Proc(INT16U Ctrl_Code, INT8U Data[], INT16U Len);
EXT void Clr_Rcv_Flag(void);
EXT INT16U Rcv_Frame_Proc(INT8U Ch, INT8U Frame[], INT16U FrameLen, INT16U Frame_Buf_Len);
EXT INT16U Make_Frame(INT8U *pData, INT16U Len, INT8U Addr[], INT8U Cmd, INT8U Cmd0, INT8U Seq, INT16U Seq0, char *pDst);
EXT void Screen_Com_Proc(void);
#endif
