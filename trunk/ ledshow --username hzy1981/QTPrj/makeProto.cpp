#define MAKE_PROTO_C
#include "makeProto.h"
#include "..\Includes.h"

#define PROTO_SHOW_DATA_LEN (BLOCK_DATA_LEN - 20)
/*
#define FLEN   0x01
#define FADDR  0x03
#define FSEQ   0x05
#define FSEQ0  0x06
#define FCTRL  0x07
#define FDATA  0x09

1	0x5A	֡ͷ���ֽ�
2	Len0	֡���ȵ��ֽ�(��֡ͷ��֡β)
3	Len1	֡���ȸ��ֽ�
4	Addr0	��ַ���ֽ�,
5	Addr1	��ַ���ֽ�
6	Seq	֡���, 0-255 ѭ������,�ط���������Ų���
7	Seq0	֡�����,0-255 ѭ������
8	Cmd0	��������ֽ�
9	Cmd1	��������ֽ�
10	��	֡����������
        ��
        CS0	У������ֽ�,��֡ͷ��CS0ǰһ���ֽڵĺ�
        CS1	У������ֽ�
        0xAA	֡β

      Cmd0����:
0x01 ����������ɫ���ɶ���д
0x02 ����ַ���ɶ���д
0x03 ��IP�������ɶ���д
0x04 ͨ�����ʣ��ɶ���д
0x05 ��ʱ���ػ����ɶ���д
0x06 ��ǰʱ�䣬�ɶ���д
0x07 �������ã��ɶ���д
0x08 ��Ŀ�����ã��ɶ���д
0x09 ��Ŀ�������ã��ɶ���д
0x0A �����������ã��ɶ���д
0x0B ����Ϣ(ֻ��)
0x0C �̼�����

  Cmd1����:
Bit0->Bit7 �������λ�����λ
Bit2: 0 ��ʾ��վ����������֡��1��ʾ��վ������Ӧ��֡
Bit1: 0 ��ʾ����Ӧ��֡��1��ʾ�쳣Ӧ��֡
Bit0:0 ��ʾ�޺���֡��1��ʾ�к���֡
Bit3->Bit7 ����

 */
//����һ��֡
//dataΪ������,dataLen�����򳤶�
//cmd������
//seq���к�
//pDstΪĿ�껺����
int makeFrame(char *data, int dataLen, char cmd, char seq, char *pDst)
{
  int len;
  char type,cmd1 = 0;

  pDst[0] = FRAME_HEAD;//֡ͷ

  memcpy(pDst + FADDR, &Screen_Para.Addr, 2); //��ַ

  if(seq != frameInfo.seq) //һ���µ�֡��
  {
      frameInfo.seq = seq;
      frameInfo.seq0 = 0;
      frameInfo.off = 0;
  }

  if(frameInfo.off >= dataLen)
      return 0;

  if(cmd EQ C_PROG_DATA) //����������ʾ�����������Ҫ��֡
  {
    if(frameInfo.seq0 EQ 0) //��һ֡ȫ������ʾ����!!
    {
        frameInfo.len = 0;
        type = data[0];
        len = Get_Show_Para_Len(type); //��һ֡����
        frameInfo.seq0 ++;
        frameInfo.off = 0;
        if(dataLen > len)
            cmd1 |= 0x01;
    }
    else
    {
        if(frameInfo.off + PROTO_SHOW_DATA_LEN >= dataLen)
          len = dataLen - frameInfo.off; //����֡����
        else
        {
          len = PROTO_SHOW_DATA_LEN;
          cmd1 |= 0x01;
        }
    }
  }
  else
      len = dataLen;

  frameInfo.off += len;

  memcpy(pDst + FDATA, data + frameInfo.off, len);

  pDst[FSEQ] = frameInfo.seq;
  pDst[FSEQ0] = frameInfo.seq0;
  pDst[FCTRL] = cmd; //�����ֽڵĿ�����
  pDst[FCTRL + 1] = cmd1;

  len += F_NDATA_LEN; //������ + �������� = ����֡��
  memcpy(pDst + FLEN, &len, 2);

  INT16U sum = Sum_2Bytes((INT8U *)pDst, len - 3); //��3���ֽ���У��ͺ�֡β
  memcpy((char *)pDst + FLEN, (char *)&sum, 2);
  pDst[len - 1] = FRAME_TAIL;

  return len;
}

//����Э������
void makeProtoData()
{

}
