#ifndef COM_H
#define COM_H

//extern "c"
//{
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
#define C_SCREEN_WH   0x01 //��Ļ���
#define C_SCREEN_ADDR 0x02 //��Ļ��ַ
#define C_SCREEN_IP   0x03 //IP��ַ
#define C_SCREEN_BAUD 0x04 //ͨ������
#define C_SCREEN_OC_TIME 0x05 //��ʱ���ػ�ʱ��
#define C_SCREEN_LIGNTNESS 0x06 //����
#define C_SCREEN_TIME 0x07 //ʱ��
#define C_DEL_PROG    0x08 //ɾ����Ŀ
#define C_PROG_PROPERTY  0x09 //��Ŀ����
#define C_PROG_DATA  0x0A //��ʾ����
#define C_SCREEN_INFO 0x0B //��Ļ��Ϣ
#define C_UPDATE      0x0C //�̼�����

#define FLEN   0x01
#define FADDR  0x03
#define FSEQ   0x05
#define FSEQ0  0x06
#define FCTRL  0x07
#define FDATA  0x09

#define F_NDATA_LEN 12 

EXT INT8U Check_Frame_Format(INT8U Frame[], INT16U Frame_Len);
EXT INT8U Para_Frame_Proc(INT16U Ctrl_Code, INT8U Data[], INT16U Len);
//}
#endif
