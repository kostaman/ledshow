#ifndef DS1302_H
#define DS1302_H

#undef EXT
#ifdef DS1302_C
#define EXT
#else
#define EXT extern
#endif

/*DSCK -PA4 DAT PA5 RST DAT*/
#define ds1302Clk GPIO_Pin_5   //��ʱ����������оƬ�Ĺܽ�
#define ds1302Data GPIO_Pin_7   //��������������оƬ�Ĺܽ�
#define ds1302Rst GPIO_Pin_8   //�븴λ��������оƬ�Ĺܽ�

//������ϣ�Ȼ��ʵ�ֵĴ���ͺܼ��ˣ����ֳɵĴ�����ֲ������

#define WrEnDisCmd  0x8e  //д����/��ָֹ�����
#define WrEnDat     0x00 //д��������
#define WrDisDat    0x80 //д��ֹ����
#define OscEnDisCmd 0x80 //��������/��ָֹ�����
#define OscEnDat    0x00 //������������
#define OscDisDat   0x80 //������ֹ����
#define WrMulti     0xbe //д�����ֽڵ�ָ�����
#define WrSingle    0x84 //д�뵥���ֽڵ�ָ�����
#define RdMulti     0xbf //��������ֽڵ�ָ�����

EXT INT8U _Get_Cur_Time(INT8U Time[]);
EXT INT8U Set_Cur_Time(INT8U Time[]);
EXT void SPI_DS1302_Init(void);
EXT void DS1302_Init(void);
#endif
