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

INT16U Make_Frame(INT8U *pData, INT16U Len, INT8U Addr[], INT8U Cmd, INT8U Cmd0, INT8U Seq, INT16U Seq0, char *pDst)
{
  pDst[0] = FRAME_HEAD;//֡ͷ
  memcpy(pDst + FADDR, Addr, 2); //��ַ
  memcpy(pDst + FDATA, pData, Len);

  pDst[FSEQ] = Seq;
  memcpy(pDst + FSEQ0, &Seq0, sizeof(Seq0));

  pDst[FCMD] = Cmd; //�����ֽڵĿ�����
  pDst[FCMD + 1] = Cmd0;

  Len += F_NDATA_LEN; //������ + �������� = ����֡��
  memcpy(pDst + FLEN, &Len, 2);

  INT16U sum = Sum_2Bytes((INT8U *)pDst, Len - 3); //��3���ֽ���У��ͺ�֡β
  memcpy((char *)pDst + Len - 3, (char *)&sum, 2);
  pDst[Len - 1] = FRAME_TAIL;

  return Len;
}


//��֡�ж�ȡ�����������û�������������
//Cmd������
//Frame��������ʼ
//Len�����򳤶�
INT8U Screen_Para_Frame_Proc(INT16U Cmd, INT8U Data[], INT16U Len)
{
  if(Cmd EQ C_SCREEN_BASE_PARA && Len >= sizeof(Screen_Para.Base_Para))
  {
    if(memcmp((INT8U *)&Screen_Para.Base_Para, Data, sizeof(Screen_Para.Base_Para)) != 0)
      {
      Set_Screen_Replay_Flag(); //�ز���Ŀ��־
      Screen_Para.Prog_Num = 0; //���ý�Ŀ��
    }
    mem_cpy((INT8U *)&Screen_Para.Base_Para, Data, sizeof(Screen_Para.Base_Para), (INT8U *)&Screen_Para, sizeof(Screen_Para));//��������
  }
  else if(Cmd EQ C_SCREEN_COM_PARA && Len >= sizeof(Screen_Para.COM_Para))
    mem_cpy((INT8U *)&Screen_Para.COM_Para, Data, sizeof(Screen_Para.COM_Para), (INT8U *)&Screen_Para, sizeof(Screen_Para));//ͨ�Ų���
  else if(Cmd EQ C_SCREEN_OC_TIME && Len >= sizeof(Screen_Para.OC_Time))
    mem_cpy((INT8U *)&Screen_Para.OC_Time, Data, sizeof(Screen_Para.OC_Time), (INT8U *)&Screen_Para, sizeof(Screen_Para)); //��ʱ���ػ�ʱ��
  else if(Cmd EQ C_SCREEN_LIGNTNESS && Len >= sizeof(Screen_Para.Lightness))
    mem_cpy((INT8U *)&Screen_Para.Lightness, Data, sizeof(Screen_Para.Lightness), (INT8U *)&Screen_Para, sizeof(Screen_Para)); //���Ȳ���
  else if(Cmd EQ C_PROG_NUM && Len>=sizeof(Screen_Para.Prog_Num))
  {
    if(memcmp((INT8U *)&Screen_Para.Prog_Num, Data, sizeof(Screen_Para.Prog_Num)!=0))
      Set_Screen_Replay_Flag(); //�ز���Ŀ��־
    mem_cpy((INT8U *)&Screen_Para.Prog_Num, Data, sizeof(Screen_Para.Prog_Num), (INT8U *)&Screen_Para, sizeof(Screen_Para));
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }

  SET_SUM(Screen_Para);
  Write_Screen_Para(); //������Ļ����
  return 1;
}

//���յ���һ֡�Ĵ���
INT8U Rcv_Frame_Proc(INT8U Frame[], INT16U FrameLen)
{
  INT16U Cmd_Code;
  S_Time TempTime;
  INT8U Re;

  Set_Screen_Com_Time(5); //����ʱ5s��5������²��Ž�Ŀ

  Re = 1;
  Cmd_Code = Frame[FCMD];// + (INT16U)Frame[FCMD + 1] * 256;
  if(Cmd_Code EQ  C_SCREEN_COM_PARA ||\
      Cmd_Code EQ C_SCREEN_OC_TIME ||\
      Cmd_Code EQ C_SCREEN_LIGNTNESS ||\
      Cmd_Code EQ C_SCREEN_BASE_PARA ||\
      Cmd_Code EQ C_PROG_NUM)
  {
    Re &= Screen_Para_Frame_Proc(Cmd_Code, Frame + FDATA, FrameLen - F_NDATA_LEN); //�����ڴ��еĲ���
    //Re &= Write_Screen_Para();//Save_Screen_Para_Frame_Proc(Frame, FrameLen); //�������
  }
  else if(Cmd_Code EQ C_PROG_PARA)//�����Ŀ����֡
  {
    Re &= Save_Prog_Para_Frame_Proc(Frame, FrameLen);
    Set_Screen_Replay_Flag(); //�ز���Ŀ��־
  }
  else if(Cmd_Code EQ C_PROG_DATA) //��ʾ����
  {
     Re &= Save_Prog_Data_Frame_Proc(Frame, FrameLen); //�����Ŀ��ʾ����
     Set_Screen_Replay_Flag(); //�ز���Ŀ��־
  }
  else if(Cmd_Code EQ C_SCREEN_TIME) //����ʱ��
  {
    mem_cpy(TempTime.Time, Frame + FDATA, sizeof(TempTime.Time), TempTime.Time, sizeof(TempTime.Time));
    Re &= Set_Cur_Time(TempTime.Time);
  }

  return Re;
}

//�յ�һ���ֽ�,�ж��е��øú���
void Rcv_One_Byte(INT8U Byte)
{
  INT16U i;

  if(Screen_Status.Rcv_Flag EQ FRAME_FLAG) //��ǰ����һ֡��ֹͣ�������գ�����֡������
      return;

  if(Screen_Status.Rcv_Posi < sizeof(Screen_Status.Rcv_Data))
    {
      Screen_Status.Rcv_Data[Screen_Status.Rcv_Posi] = Byte;
      Screen_Status.Rcv_Posi++;
  }
  else
  {
      Screen_Status.Rcv_Data[0] = Byte;
      Screen_Status.Rcv_Posi = 0;
  }

  if(Byte EQ FRAME_TAIL) //�յ�֡β�ַ�
  {
      for(i = 0; i < Screen_Status.Rcv_Posi; i ++)
      {
          if(Screen_Status.Rcv_Data[i] EQ FRAME_HEAD && \
             Check_Frame_Format(Screen_Status.Rcv_Data + i, Screen_Status.Rcv_Posi - i))
          {
             if(i != 0) //�����ݸ��Ƶ���ʼ
                 memcpy(Screen_Status.Rcv_Data, Screen_Status.Rcv_Data + i, Screen_Status.Rcv_Posi - i);
             Screen_Status.Rcv_Flag = FRAME_FLAG;
             return;
          }
      }
  }
}

void Screen_Com_Proc()
{
    static S_Int32U Sec = {CHK_BYTE, 0xFFFFFFFF, CHK_BYTE};
   INT8U Re;

   if(Screen_Status.Rcv_Flag EQ FRAME_FLAG)
    {
     Re = Rcv_Frame_Proc(Screen_Status.Rcv_Data, Screen_Status.Rcv_Posi);

     Screen_Status.Rcv_Posi = 0;
     Screen_Status.Rcv_Flag = 0;

   }

   //�յ����һ֡��ĵ���ʱ
   if(Screen_Status.Com_Time > 0)
   {
      if(Sec.Var != SEC_TIMER)
       {
        Sec.Var = SEC_TIMER;

        Screen_Status.Com_Time--;
        //SET_SUM(Screen_Status);

        if(Screen_Status.Com_Time EQ 0)
        {
          if(Screen_Status.Replay_Flag EQ REPLAY_FLAG) //�����²��ű�־
          {
            //Clear_Show_Data()
            memset(Show_Data.Color_Data, 0, sizeof(Show_Data.Color_Data));
            memset(Show_Data_Bak.Color_Data, 0, sizeof(Show_Data_Bak.Color_Data));
#if DATA_PREP_EN
            memset(&Prep_Data, 0, sizeof(Prep_Data));
            SET_HT(Prep_Data);
#endif
            Screen_Status.Replay_Flag = 0; //������²��ű�־
            SET_SUM(Screen_Status);

            //���¿�ʼ�ӵ�0��Ŀ����
            Prog_Status.Play_Status.Last_Prog_No = 0xFF;
            Prog_Status.Play_Status.Prog_No = 0;
            Prog_Status.Play_Status.New_Prog_Flag = NEW_FLAG;
            SET_SUM(Prog_Status);
          }
        }
      }
   }
}
