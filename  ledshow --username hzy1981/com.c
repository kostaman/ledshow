#define COM_C
#include "Includes.h"

const INT16U Frame_Data_Size[]=
{
  0,
  5,
  1,
  4,
  1,
  20,
  8,
  7	
};

//


INT8U Check_Frame_Format(INT8U Frame[], INT16U Frame_Len)
{
  INT16U Len;
  INT16U Sum;
  
  if(!(Frame[0] EQ FRAME_HEAD0 && Frame[1] EQ FRAME_HEAD1)) //ͷ��ȷ
  {
    ASSERT_FAILED();
    return 0;
  }
  
  Len = Frame[2] + (INT16U)Frame[3] * 256; //֡��

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
//Ctrl������
//Frame��������ʼ
//Len�����򳤶�
INT8U Para_Frame_Proc(INT16U Ctrl, INT8U Data[], INT16U Len)
{
  //INT16U Ctrl;
  //INT16U Len;
  
  //Ctrl = Frame[6] + (INT16U)Frame[7] * 256;
  //Len = FrameLen - 11;
  
  if(Ctrl EQ C_SCREEN_WH && Len >= Frame_Data_Size[Ctrl])
    mem_cpy((INT8U *)&Screen_Para.Width, Data, Frame_Data_Size[Ctrl], (INT8U *)&Screen_Para, sizeof(Screen_Para)); //��Ļ����
  else if(Ctrl EQ C_SCREEN_ADDR && Len >= Frame_Data_Size[Ctrl])
    mem_cpy((INT8U *)&Screen_Para.Addr, Data, Frame_Data_Size[Ctrl], (INT8U *)&Screen_Para, sizeof(Screen_Para)); //��Ļ��ַ
  else if(Ctrl EQ C_SCREEN_IP && Len >= Frame_Data_Size[Ctrl])
    mem_cpy((INT8U *)&Screen_Para.IP, Data, Frame_Data_Size[Ctrl], (INT8U *)&Screen_Para, sizeof(Screen_Para)); //IP��ַ	
  else if(Ctrl EQ C_SCREEN_BAUD && Len >= Frame_Data_Size[Ctrl])
    mem_cpy((INT8U *)&Screen_Para.Baud, Data, Frame_Data_Size[Ctrl], (INT8U *)&Screen_Para, sizeof(Screen_Para)); //ͨ�Ų�����
  else if(Ctrl EQ C_SCREEN_OC_TIME && Len >= Frame_Data_Size[Ctrl]) 	
    mem_cpy((INT8U *)&Screen_Para.Open_Close_Time, Data, Frame_Data_Size[Ctrl], (INT8U *)&Screen_Para, sizeof(Screen_Para)); //��ʱ���ػ�ʱ��
  else if(Ctrl EQ C_SCREEN_LIGNTNESS && Len >= Frame_Data_Size[Ctrl])
    mem_cpy((INT8U *)&Screen_Para.Lightness, Data, Frame_Data_Size[Ctrl], (INT8U *)&Screen_Para, sizeof(Screen_Para)); //��ʱ���ػ�ʱ��
  else if(Ctrl EQ C_SCREEN_TIME && Len >= Frame_Data_Size[Ctrl])
    ;//mem_cpy((INT8U *)&Screen_Para.Open_Close_Time, Frame, Frame_Data_Size[Ctrl], (INT8U *)&Screen_Para, sizeof(Screen_Para)); //��ʱ���ػ�ʱ��
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
  INT16U Ctrl_Code;
  S_Time TempTime;
  INT8U Re;
  
  Re = 1;
  Ctrl_Code = Frame[6] + (INT16U)Frame[7] * 256;
  if(Ctrl_Code EQ C_SCREEN_WH ||\
      Ctrl_Code EQ C_SCREEN_ADDR ||\
      Ctrl_Code EQ C_SCREEN_IP  ||\
      Ctrl_Code EQ C_SCREEN_BAUD ||\
      Ctrl_Code EQ C_SCREEN_OC_TIME ||\
      Ctrl_Code EQ C_SCREEN_LIGNTNESS)
  {
    Re &= Para_Frame_Proc(Ctrl_Code, Frame + 8, FrameLen - 11); //�����ڴ��еĲ���
    Re &= Save_Para_Frame_Proc(Frame, FrameLen); //�������
  }
  else if(Ctrl_Code EQ C_PROG_PROPERTY)//�����Ŀ����֡
  {
    Re &= Save_Prog_Property_Frame_Proc(Frame, FrameLen); 
  }
  else if(Ctrl_Code EQ C_PROG_DATA) //��ʾ���� 
  {
    Re &= Save_Prog_Data_Frame_Proc(Frame, FrameLen); //�����Ŀ��ʾ����
  }
  else if(Ctrl_Code EQ C_SCREEN_TIME) //����ʱ��
  {
    mem_cpy(TempTime.Time, Frame + 8, 7, TempTime.Time, sizeof(TempTime.Time));
    Re &= Set_Cur_Time(TempTime.Time);
  }
}