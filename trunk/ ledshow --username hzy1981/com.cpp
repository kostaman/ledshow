#define COM_C
#include "Includes.h"
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

/*
#define FHEAD  0x00 //֡ͷ,1
#define FLEN   0x01 //֡����,1
#define FADDR  0x03 //֡��ַ,2
#define FSEQ   0x05 //֡���,1
#define FSEQ0  0x06 //֡�����,2
#define FCMD   0x08 //������,2
#define FDATA  0x0A //��������
*/
INT8U Check_Frame_Format(INT8U Frame[], INT16U Frame_Len)
{
  INT16U Len;
  INT16U Sum;
  
  if(Frame[FHEAD] != FRAME_HEAD) //ͷ��ȷ
  {
    ASSERT_FAILED();
    return 0;
  }
  
  Len = Frame[FLEN] + (INT16U)Frame[FLEN + 1] * 256; //֡��

  if(Len!= Frame_Len || Frame[Len - 1] != FRAME_TAIL) //β��ȷ
  {
    ASSERT_FAILED();
    return 0;
  }
  
  Sum = Sum_2Bytes(Frame, Len - 3); //��3���ֽ���У��ͺ�֡β
  if(memcmp((INT8U *)&Sum, Frame + Len - 3, 2) EQ 0)
    return 1;
  else
  {
    ASSERT_FAILED();
     return 0;
  }  
  
}

//��֡�ж�ȡ�����������û�������������
//Cmd������
//Frame��������ʼ
//Len�����򳤶�
INT8U Screen_Para_Frame_Proc(INT16U Cmd, INT8U Data[], INT16U Len)
{
  //INT16U Cmd;
  //INT16U Len;
  
  //Cmd = Frame[6] + (INT16U)Frame[7] * 256;
  //Len = FrameLen - 11;
  
  if(Cmd EQ C_SCREEN_WH && Len >= sizeof(Screen_Para.Base_Para.Width))
    mem_cpy((INT8U *)&Screen_Para.Base_Para.Width, Data, sizeof(Screen_Para.Base_Para.Width), (INT8U *)&Screen_Para, sizeof(Screen_Para)); //��Ļ����
  else if(Cmd EQ C_SCREEN_ADDR && Len >= sizeof(Screen_Para.Base_Para.Addr))
    mem_cpy((INT8U *)&Screen_Para.Base_Para.Addr, Data, sizeof(Screen_Para.Base_Para.Addr), (INT8U *)&Screen_Para, sizeof(Screen_Para)); //��Ļ��ַ
  else if(Cmd EQ C_SCREEN_IP && Len >= sizeof(Screen_Para.Base_Para.IP))
    mem_cpy((INT8U *)&Screen_Para.Base_Para.IP, Data, sizeof(Screen_Para.Base_Para.IP), (INT8U *)&Screen_Para, sizeof(Screen_Para)); //IP��ַ
  else if(Cmd EQ C_SCREEN_BAUD && Len >= sizeof(Screen_Para.Base_Para.Baud))
    mem_cpy((INT8U *)&Screen_Para.Base_Para.Baud, Data, sizeof(Screen_Para.Base_Para.Baud), (INT8U *)&Screen_Para, sizeof(Screen_Para)); //ͨ�Ų�����
  else if(Cmd EQ C_SCREEN_OC_TIME && Len >= sizeof(Screen_Para.OC_Time))
    mem_cpy((INT8U *)&Screen_Para.OC_Time, Data, sizeof(Screen_Para.OC_Time), (INT8U *)&Screen_Para, sizeof(Screen_Para)); //��ʱ���ػ�ʱ��
  else if(Cmd EQ C_SCREEN_LIGNTNESS && Len >= sizeof(Screen_Para.Lightness))
    mem_cpy((INT8U *)&Screen_Para.Lightness, Data, sizeof(Screen_Para.Lightness), (INT8U *)&Screen_Para, sizeof(Screen_Para)); //���Ȳ���
  else if(Cmd EQ C_SCREEN_TIME && Len >= sizeof(Cur_Time.Time))
    ;//mem_cpy((INT8U *)&Screen_Para.Open_Close_Time, Frame, Frame_Data_Size[Cmd], (INT8U *)&Screen_Para, sizeof(Screen_Para)); //��ʱ���ػ�ʱ��
  else if(Cmd EQ C_SCREEN_BASE_PARA && Len >= sizeof(Screen_Para.Base_Para))
    mem_cpy((INT8U *)&Screen_Para.Base_Para, Data, sizeof(Screen_Para.Base_Para), (INT8U *)&Screen_Para, sizeof(Screen_Para));
  else
  {
    ASSERT_FAILED();
    return 0;
  }	
  return 1;
}

//���յ���һ֡�Ĵ���
void Rcv_Frame_Proc(INT8U Frame[], INT16U FrameLen)
{
  INT16U Cmd_Code;
  S_Time TempTime;
  INT8U Re;
  
  if(Check_Frame_Format(Frame, FrameLen) EQ 0)
  {
      ASSERT_FAILED();
      return;
  }

  Re = 1;
  Cmd_Code = Frame[FCMD];// + (INT16U)Frame[FCMD + 1] * 256;
  if(Cmd_Code EQ C_SCREEN_WH ||\
      Cmd_Code EQ C_SCREEN_ADDR ||\
      Cmd_Code EQ C_SCREEN_IP  ||\
      Cmd_Code EQ C_SCREEN_BAUD ||\
      Cmd_Code EQ C_SCREEN_OC_TIME ||\
      Cmd_Code EQ C_SCREEN_LIGNTNESS ||\
      Cmd_Code EQ C_SCREEN_BASE_PARA)
  {
    Re &= Screen_Para_Frame_Proc(Cmd_Code, Frame + FDATA, FrameLen - F_NDATA_LEN); //�����ڴ��еĲ���
    Re &= Save_Screen_Para_Frame_Proc(Frame, FrameLen); //�������
  }
  else if(Cmd_Code EQ C_PROG_PARA)//�����Ŀ����֡
  {
    Re &= Save_Prog_Para_Frame_Proc(Frame, FrameLen);
  }
  else if(Cmd_Code EQ C_PROG_DATA) //��ʾ����
  {
     Re &= Save_Prog_Data_Frame_Proc(Frame, FrameLen); //�����Ŀ��ʾ����
  }
  else if(Cmd_Code EQ C_SCREEN_TIME) //����ʱ��
  {
    mem_cpy(TempTime.Time, Frame + FDATA, sizeof(TempTime.Time), TempTime.Time, sizeof(TempTime.Time));
    Re &= Set_Cur_Time(TempTime.Time);
  }
}
