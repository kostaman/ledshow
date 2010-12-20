#define BORDER_SHOW_C

//��ȡ�߿�����
//X\Y��ʾ�ڱ߿����ݿ��ڵ�����
INT8U Get_Border_Point_Data(INT16U X, INT16U Y) //��ȡһ��������һ���������
{
  INT32U Index;

  Index = (((Y>>3) * Prog_Para.Border_Width) + X)*8 + (Y & 0x07);//Get_Area_Point_Index(Area_No, X, Y);
  
  if(Screen_Para.Color EQ 0)  //��ɫ��
    return Get_Buf_Bit(Prog_Para.Border_Data, sizeof(Prog_Para.Border_Data),Index);
  else if(Screen_Para.Color EQ 1) //˫ɫ��
    return Get_Buf_Bit(Prog_Para.Border_Data, sizeof(Prog_Para.Border_Data), ((Index>>3)<<4) + (Index & 0x07)) +\
      (Get_Buf_Bit(Prog_Para.Border_Data, sizeof(Prog_Para.Border_Data), ((Index>>3)<<4) + 8 + (Index & 0x07))<<1);
  else if(Screen_Para.Color EQ 2) //��ɫ��
    return Get_Buf_Bit(Prog_Para.Border_Data, sizeof(Prog_Para.Border_Data), (Index>>3)*24 + (Index & 0x07)) +\
      (Get_Buf_Bit(Prog_Para.Border_Data, sizeof(Prog_Para.Border_Data), (Index>>3)*24 + 8 + (Index & 0x07))<<1)+
      (Get_Buf_Bit(Prog_Para.Border_Data, sizeof(Prog_Para.Border_Data), (Index>>3)*24 + 16 + (Index & 0x07))<<2);
  else
    return 0;
}
                     
//���Ʊ߿�
//pDst��ʾĿ�������
//Area_No��ʾĿ�����
//Width��ʾ�߿�Ԫͼ��Ŀ��
//Height��ʾ�߿�Ԫͼ��ĸ߶�
//pData��ʾ����
//Step��ʾ��ʾ����
void Draw_Border(S_Show_Data *pDst, INT8U Area_No, INT8U *pData, INT8U Width, INT8U Height,  INT8U Step)
{
   INT8U Re;
   INT16U i,j;
   INT16U Width;
   
   //���±߿�
   for(i = 0; i < Screen_Para.Width; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = Get_Border_Point_Data((i + Prog_Para.Border_Width *Step / 100) % Prog_Para.Border_Width, j);  
       Set_Area_Point_Data(pDst, MAX_AREA_NUM, i, j, Re); //�ϱ߿�
       Set_Area_Point_Data(pDst, MAX_AREA_NUM, Screen_Para.Width - i, Screen_Para.Height - j, Re); //�±߿�
     }
  
   //���ұ߿�
   for(i = 0; i < Height; i ++)
     for(j = 0; j < Screen_Para.Width; j ++)
     {
       Re = Get_Border_Point_Data((i + Prog_Para.Border_Width *Step / 100) % Prog_Para.Border_Width, j);  
       Set_Area_Point_Data(pDst, MAX_AREA_NUM, i, j, Re); //��߿�
       Set_Area_Point_Data(pDst, MAX_AREA_NUM, i, Height-j, Re); //�ұ߿�
     }   
}

void Update_Border_Data()
{
  //INT8U In_Mode;
  //�����ƶ�״̬
  INT32U Step_Time = 0; //����ʱ��
  
  Prog_Status.Border_Status.Timer + =MOVE_STEP_TIMER;
  if(Prog_Status.Border_Status.Timer >= Step_Time)
  {
    if(Prog_Status.Border_Status.Step < 100)
      Prog_Status.Borer_Status.Step += MOVE_STEP;
  }
  
  
}

#undef BORDER_SHOW_C
