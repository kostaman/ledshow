#define BORDER_SHOW_C
#include "Includes.h"

#if BORDER_SHOW_EN > 0
/*
const INT8U B0Data0[] = {0xFF, 0xFF,0xFF, 0xFF, 0xFF};//, 0xFF};
const INT8U B0Data1[] = {0xFF, 0xFF,0xF0, 0x00, 0x00};//, 0x00};
const INT8U B0Data2[] = {0x0F, 0x0F,0x0F, 0x0F, 0x0F};//, 0x0F};
const INT8U B0Data3[] = {0xFF, 0xFF,0xFF, 0xFF, 0xFF,\
                         0xFF, 0xFF, 0xFF,0xFF, 0xFF};// 0xFF, 0xFF};
const INT8U B0Data4[] = {0xFF, 0xFF,0xFF, 0x00, 0x00, 0x00,\
                         0xFF, 0xFF,0xFF, 0x00, 0x00, 0x00};
const INT8U B0Data5[] = {0x0F, 0x0F,0x0F, 0x0F, 0x0F, 0x0F,\
                         0x0F, 0x0F,0x0F, 0x0F, 0x0F, 0x0F};
const INT8U B0Data6[] = {0x80, 0x01, 0x80, 0x01, 0x80, 0x01,\
                         0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x07,\
                         0xF8, 0x1F, 0xF8, 0x1F, 0xF8, 0x1F,\
                         0xFE, 0x7F, 0xFE, 0x7F, 0xFE, 0x7F};

//const INT8U B0Data6[] = {0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF};

const S_Simple_Border_Data Simple_Border_Data0[] =
{
    {40, 1,  B0Data0},
    {40, 1,  B0Data1},
    {40, 1,  B0Data2},
    {40, 2,  B0Data3},
    {40, 2,  B0Data4},
    {40, 2,  B0Data5},
    {40, 3,  B0Data6}

};

const S_Simple_Border_Data Simple_Border_Data1[] =
{
    {48, 1,  B0Data0},
    {48, 1,  B0Data1},
    {48, 1,  B0Data2},
    {48, 2,  B0Data3},
    {48, 2,  B0Data4},
    {48, 2,  B0Data5}
};
//const INT8U Bit_Mask[9] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};

//��ȡ�߿�����
INT8U Get_Simple_Border_Num(INT8U Type)
{
    if(Type EQ 0)
        return S_NUM(Simple_Border_Data0);
    else
        return S_NUM(Simple_Border_Data1);
}

S_Simple_Border_Data *Get_Simple_Border_Info(INT8U Index)
{
  INT8U Type;

  Type = Index >> 7;

  Index = Index & 0x7F;

  if(Type EQ 0)
  {
      if(Index >= S_NUM(Simple_Border_Data0))
          Index = 0;

      return (S_Simple_Border_Data *)&Simple_Border_Data0[Index];
  }
  else
  {
      if(Index >= S_NUM(Simple_Border_Data1))
          Index = 0;

      return (S_Simple_Border_Data *)&Simple_Border_Data1[Index];
  }
}

INT8U Get_Simple_Border_Width(INT8U Index)
{
    S_Simple_Border_Data *p;

    p = Get_Simple_Border_Info(Index);
    return p->Width;
}

INT8U Get_Simple_Border_Height(INT8U Index)
{
  S_Simple_Border_Data *p;

  p = Get_Simple_Border_Info(Index);
  return p->Height;
}
*/

//��ȡ�߿�����
//X\Y��ʾ�ڱ߿����ݿ��ڵ�����
INT8U Get_Border_Point_Data(INT8U *pData, INT8U Area_No, INT16U X, INT16U Y) //��ȡһ��������һ���������
{
    if(Area_No EQ MAX_AREA_NUM)
      return Get_Buf_Point_Data(pData, BORDER_DATA_LEN, Screen_Para.Base_Para.Color, Prog_Para.Border_Width, X, Y);
    else
    {
      return Get_Buf_Point_Data(pData, BORDER_DATA_LEN, Screen_Para.Base_Para.Color, Prog_Status.File_Para[Area_No].Pic_Para.Border_Width, X, Y);
    }
}

void Draw_Border(S_Show_Data *pDst, INT8U Area_No, INT8U *pData, INT32U Step, INT8U Flag)
{
   INT8U Re;
   INT16U i,j,Len;
   INT16U Area_Width, Area_Height;
   INT8U Width, Height;
   S_Point P0,P1;

   Area_Width = Get_Area_Width(Area_No); //�����Ŀ�Ⱥ͸߶�
   Area_Height = Get_Area_Height(Area_No);
   Width = Get_Area_Border_Width(Area_No);
   Height = Get_Area_Border_Height(Area_No);

   //��Pub_Buf�н���һ��Show_Data,���ڸ�������
   //pShow_Data = (S_Show_Data *) &_Pub_Buf;

   //���±߿�
   for(i = 0; i < Width; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = Get_Border_Point_Data(pData, Area_No, i/*(i + Step) % Width*/, j);
       Set_Area_Point_Data(pDst, Area_No, i, j, Re); //�ϱ߿�
       Set_Area_Point_Data(pDst, Area_No, Width - 1 - i, Area_Height-1 - j, Re); //�±߿�
     }

   if(Flag)
   {
       P0.X = 0;
       P0.Y = 0;

       P1.X = 0;
       P1.Y = 0;
       while(P1.X < Area_Width)
       {
          P1.X = P1.X + Width;
          P0.Y = 0;
          P1.Y = 0;
          Copy_Filled_Rect(pDst, Area_No,&P0, Width, Height, pDst, &P1, 0);

          P0.Y = Area_Height - Height;
          P1.Y = Area_Height - Height;
          Copy_Filled_Rect(pDst, Area_No,&P0, Width, Height, pDst, &P1, 0);
       }
   }

   //���ұ߿�
   if(Width + Height > Area_Height) //��Ӧ�����߶�
   {
     if(Area_Height > Height)
       Width = Area_Height - Height;
     else
       Width = 0;
   }

   for(i = 0; i < Width; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = Get_Border_Point_Data(pData, Area_No, i, j);
       Set_Area_Point_Data(pDst, Area_No, j, Height + i, Re); //��߿�
       Set_Area_Point_Data(pDst, Area_No, Area_Width - 1 - j, Height + Width -1 - i, Re); //�ұ߿�
     }

   if(Flag)
   {
       P0.X = 0;
       P0.Y = Height;

       P1.X = 0;
       P1.Y = Width + Height;
       while((INT32S)P1.Y < (INT32S)(Area_Height - Height))
       {
          if(P1.Y + Width >= (INT32S)(Area_Height - Height))
              Len = Area_Height - Height - P1.Y;
          else
              Len = Width;

          P0.X = 0;
          P1.X = 0;
          Copy_Filled_Rect(pDst, Area_No,&P0,Height, Len,  pDst, &P1, 0);

          P0.X = Area_Width - Height;
          P1.X = Area_Width - Height;
          Copy_Filled_Rect(pDst, Area_No,&P0,Height, Len, pDst, &P1, 0);

          P1.Y = P1.Y + Len;
       }
    }
}

void Copy_Border(INT8U Area_No, INT32U Step)
{
    INT8U Re;
    INT16U i,j,Len;
    INT16U Area_Width, Area_Height;
    INT8U Width, Height;
    S_Point P0,P1;
    //INT8U Color;
    S_Show_Data *pDst;
    //INT16U Temp;

    //Step = 0;
    pDst = &Show_Data;
    Area_Width = Get_Area_Width(Area_No); //�����Ŀ�Ⱥ͸߶�
    Area_Height = Get_Area_Height(Area_No);
    Width = Get_Area_Border_Width(Area_No);
    Height = Get_Area_Border_Height(Area_No);

    //��Pub_Buf�н���һ��Show_Data,���ڸ�������
    //pShow_Data = (S_Show_Data *) &_Pub_Buf;

    //���±߿�
    for(i = 0; i < Width; i ++)
      for(j = 0; j < Height; j ++)
      {
        Re = Get_Area_Point_Data(&Show_Data_Bak, Area_No, (i + Step) % Width, j);
        Set_Area_Point_Data(pDst, Area_No, i, j, Re); //�ϱ߿�
        Set_Area_Point_Data(pDst, Area_No, Width - 1 - i, Area_Height-1 - j, Re); //�±߿�
      }

    P0.X = 0;
    P0.Y = 0;

    P1.X = 0;
    P1.Y = 0;
    while(P1.X < Area_Width)
    {
       P1.X = P1.X + Width;
       P0.Y = 0;
       P1.Y = 0;
       Copy_Filled_Rect(pDst, Area_No,&P0, Width, Height, pDst, &P1, 0);

       P0.Y = Area_Height - Height;
       P1.Y = Area_Height - Height;
       Copy_Filled_Rect(pDst, Area_No,&P0, Width, Height, pDst, &P1, 0);
    }

    //���ұ߿�
    if(Width + Height > Area_Height) //��Ӧ�����߶�
    {
      if(Area_Height > Height)
        Width = Area_Height - Height;
      else
        Width = 0;
    }

    for(i = 0; i < Width; i ++)
      for(j = 0; j < Height; j ++)
      {
        Re = Get_Area_Point_Data(&Show_Data_Bak, Area_No, (i + Step) % Width, j);
        Set_Area_Point_Data(pDst, Area_No, j,Height + Width -1 - i, Re); //��߿�
        Set_Area_Point_Data(pDst, Area_No, Area_Width - 1 - j,Height + i, Re); //�ұ߿�
      }

    P0.X = 0;
    P0.Y = Height;

    P1.X = 0;
    P1.Y = Width + Height;
    while((INT32S)P1.Y < (INT32S)(Area_Height - Height))
    {
       if(P1.Y + Width >= (INT32S)(Area_Height - Height))
           Len = Area_Height - Height - P1.Y;
       else
           Len = Width;

       P0.X = 0;
       P1.X = 0;
       Copy_Filled_Rect(pDst, Area_No,&P0,Height, Len,  pDst, &P1, 0);

       P0.X = Area_Width - Height;
       P1.X = Area_Width - Height;
       Copy_Filled_Rect(pDst, Area_No,&P0,Height, Len, pDst, &P1, 0);

       P1.Y = P1.Y + Len;
    }
}

//����߽�--��˸ʱ����
void Clr_Border(S_Show_Data *pDst, INT8U Area_No)
{

    INT16U Area_Width, Area_Height;//, Border_Width, Border_Height;
    INT8U Width, Height;
    S_Point P0;

    Area_Width = Get_Area_Width(Area_No); //�����Ŀ�Ⱥ͸߶�
    Area_Height = Get_Area_Height(Area_No);
    Width = Get_Area_Border_Width(Area_No);
    Height = Get_Area_Border_Height(Area_No);
    //Border_Width = Get_Area_Border_Width(Area_No);
    //Border_Height = Get_Area_Border_Height(Area_No);

    P0.X = 0;
    P0.Y = 0;

    Fill_Rect(pDst, Area_No, &P0, Area_Width, Height, 0);

    P0.Y = Area_Height - Height;
    Fill_Rect(pDst, Area_No, &P0, Area_Width, Height, 0);

    P0.Y = 0;
    Fill_Rect(pDst, Area_No, &P0, Height, Area_Height, 0);

    P0.X = Area_Width - Height;
    Fill_Rect(pDst, Area_No, &P0, Height, Area_Height, 0);
}

//��ȡĳ�������Ŀ��
INT8U Get_Area_Border_Width(INT8U Area_No)
{
  if(Area_No EQ MAX_AREA_NUM)
    return Prog_Para.Border_Width;
  else
    return Prog_Status.File_Para[Area_No].Pic_Para.Border_Width;
}

//��ȡĳ�������ĸ߶�
INT8U Get_Area_Border_Height(INT8U Area_No)
{
  if(Area_No >= MAX_AREA_NUM)
    return Prog_Para.Border_Height;
  else
  {
      return Prog_Status.File_Para[Area_No].Pic_Para.Border_Height;
  }
}

//�ָ����߿򸲸ǵ�����
void Restore_Border_Data(INT8U Area_No)
{
  INT8U Data;
  INT16U i,j;
  INT16U Area_Height,Area_Width,Border_Height;

  Border_Height = Get_Area_Border_Height(Area_No);
  Area_Width = Get_Area_Width(Area_No);
  Area_Height = Get_Area_Height(Area_No);

  //���±߿����ݵĻָ�
  for(i = 0; i < Area_Width; i ++)
    for(j = 0; j < Border_Height; j ++)
  {
    Data = Get_Area_Point_Data(&Show_Data_Bak, Area_No, i, j);
    Set_Area_Point_Data(&Show_Data, Area_No, i, j, Data);

    Data = Get_Area_Point_Data(&Show_Data_Bak, Area_No, i, Area_Height - 1- j);
    Set_Area_Point_Data(&Show_Data, Area_No, i, Area_Height - 1- j, Data);
  }

  //���ұ߿����ݵĻָ�
  for(i = 0; i < Area_Height; i ++)
    for(j = 0; j < Border_Height; j ++)
  {
    Data = Get_Area_Point_Data(&Show_Data_Bak, Area_No, j, i);
    Set_Area_Point_Data(&Show_Data, Area_No, j, i, Data);

    Data = Get_Area_Point_Data(&Show_Data_Bak, Area_No, Area_Width - 1- j, i);
    Set_Area_Point_Data(&Show_Data, Area_No, Area_Width - 1- j, i,  Data);
  }
}

//���±߿�����
void Update_Border_Data(INT8U Area_No)
{
  INT32U Max_Step;//, Size;
  static S_Int8U InitFlag = {CHK_BYTE, 0, CHK_BYTE};
  //S_Simple_Border_Data *p;
  INT8U i;

  //�����ƶ�״̬
  static S_Int16U Timer[MAX_AREA_NUM + 1];// = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Flag[MAX_AREA_NUM + 1];// = {CHK_BYTE, 0, CHK_BYTE};
    
  INT16U Step_Time = 0; //����ʱ��
  INT8U Border_Width,Border_Height;
  //INT8U *pBorder_Data;
  INT8U Border_Mode;
  //INT8U Type;

  if(Prog_Status.Play_Status.New_Prog_Flag ||\
     (Area_No < MAX_AREA_NUM &&\
     (Prog_Status.Area_Status[Area_No].New_File_Flag ||\
      Prog_Status.Area_Status[Area_No].New_SCN_Flag))) //�ý�Ŀ��÷�����û�н��벥��״̬?
    return;

  //��һ�ν���ú�������ʼ����غ���ͷβ
  if(InitFlag.Var EQ 0)
  {
      InitFlag.Var = 1;
      for(i = 0; i < MAX_AREA_NUM + 1; i ++)
      {
          SET_HT(Timer[i]);
          SET_HT(Flag[i]);
      }
  }

  if(Area_No EQ MAX_AREA_NUM) //�ܵĽ�Ŀ�ı߿�
  {
      if(Prog_Para.Border_Check EQ 0)
          return;

      TRACE();

      Step_Time = (INT16U)(Prog_Para.Border_Speed + 1)*MOVE_STEP_PERIOD;//(Prog_Para.Border_Speed+ 1)*MAX_STEP_NUM; //MAX_STEP_NUMms�ĵ�һ���ٶȲ���
      Prog_Status.Border_Status[Area_No].Timer += MOVE_STEP_PERIOD;
      Max_Step = 0xFFFFFFFF;//Screen_Para.Base_Para.Width + Screen_Para.Base_Para.Height;
      Border_Mode = Prog_Para.Border_Mode;
  }
  else
  {
      if(Area_No > MAX_AREA_NUM)
      {
          ASSERT_FAILED();
          return;
      }

      if(Prog_Status.File_Para[Area_No].Pic_Para.Border_Check EQ 0)
          return;

      TRACE();

      Step_Time = (INT16U)(Prog_Status.File_Para[Area_No].Pic_Para.Border_Speed + 1)*MOVE_STEP_PERIOD;//(Prog_Para.Border_Speed+ 1)*MAX_STEP_NUM; //MAX_STEP_NUMms�ĵ�һ���ٶȲ���
      Prog_Status.Border_Status[Area_No].Timer += MOVE_STEP_PERIOD;
      Max_Step = 0xFFFFFFFF;
      Border_Mode = Prog_Status.File_Para[Area_No].Pic_Para.Border_Mode;

  }

  Border_Width = Get_Area_Border_Width(Area_No);
  Border_Height = Get_Area_Border_Height(Area_No);

  if(Prog_Status.Border_Status[Area_No].Timer >= Step_Time)
  {
    Prog_Status.Border_Status[Area_No].Timer = 0;

	if(Prog_Status.Border_Status[Area_No].Step + MOVE_STEP + Border_Width >= Max_Step)
	  Prog_Status.Border_Status[Area_No].Step = 0;//Max_Step - Prog_Status.Border_Status[Area_No].Step;
    
      Prog_Status.Border_Status[Area_No].Step += MOVE_STEP;


    Timer[Area_No].Var ++;
    if(Timer[Area_No].Var >= 2)
    {
        Timer[Area_No].Var = 0;
        Flag[Area_No].Var = 1 - Flag[Area_No].Var;
    }
  

    if(Border_Mode EQ BORDER_STATIC) //��̬
    {
      Copy_Border(Area_No, 0);
    }
    else if(Border_Mode EQ BORDER_FLASH) //��˸
    {
      if(Flag[Area_No].Var EQ 0)
        Copy_Border(Area_No, 0);
      else
        Clr_Border(&Show_Data, Area_No);
    }
    else if(Border_Mode EQ BORDER_CLKWS) //˳ʱ��
    {
      Copy_Border(Area_No, Max_Step - Border_Width - Prog_Status.Border_Status[Area_No].Step);
    }
    else if(Border_Mode EQ BORDER_CCLKWS) //��ʱ��
    {
      Copy_Border(Area_No, Prog_Status.Border_Status[Area_No].Step);
    }
    else if(Border_Mode EQ BORDER_CLKWS_FLASH) //˳ʱ����˸
    {
      if(Flag[Area_No].Var EQ 0)
        Copy_Border(Area_No, Max_Step - Border_Width - Prog_Status.Border_Status[Area_No].Step);
      else
        Clr_Border(&Show_Data, Area_No);
    }
    else if(Border_Mode EQ BORDER_CCLKWS_FLASH) //��ʱ����˸
    {
      if(Flag[Area_No].Var EQ 0)
        Copy_Border(Area_No, Prog_Status.Border_Status[Area_No].Step);
      else
        Clr_Border(&Show_Data, Area_No);
    }
   }
      
  //}

 /*
  if(Timer[Area_No].Var >= 500)
  {
      Timer[Area_No].Var = 0;
      if(Flag[Area_No].Var > 0)
        Flag[Area_No].Var = 0;
      else
        Flag[Area_No].Var = 1;
    }
    */
}

void Border_Show_Proc(void)
{
  INT8U i;

  Update_Border_Data(MAX_AREA_NUM); //��Ŀ�߿�

  for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
      if(Screen_Status.Rcv_Flag EQ FRAME_FLAG) //�յ�һ֡���ȴ����֡
          return;

      Update_Border_Data(i); //���±߿�����
  }
}
#endif
#undef BORDER_SHOW_C
