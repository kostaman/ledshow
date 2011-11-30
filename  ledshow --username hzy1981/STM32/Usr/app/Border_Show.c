#define BORDER_SHOW_C
#include "Includes.h"

#if BORDER_SHOW_EN > 0

const INT8U B0Data0[] = {0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF};
const INT8U B0Data1[] = {0xFF, 0xFF,0xFF, 0x00, 0x00, 0x00};
const INT8U B0Data2[] = {0x0F, 0x0F,0x0F, 0x0F, 0x0F, 0x0F};
const INT8U B0Data3[] = {0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF,\
                         0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF};
const INT8U B0Data4[] = {0xFF, 0xFF,0xFF, 0x00, 0x00, 0x00,\
                         0xFF, 0xFF,0xFF, 0x00, 0x00, 0x00};
const INT8U B0Data5[] = {0x0F, 0x0F,0x0F, 0x0F, 0x0F, 0x0F,\
                         0x0F, 0x0F,0x0F, 0x0F, 0x0F, 0x0F};
//const INT8U B0Data6[] = {0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF};

const S_Simple_Border_Data Simple_Border_Data0[] =
{
    {48, 1,  B0Data0},
    {48, 1,  B0Data1},
    {48, 1,  B0Data2},
    {48, 2,  B0Data3},
    {48, 2,  B0Data4},
    {48, 2,  B0Data5}

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

//��ȡ�߿�����
//X\Y��ʾ�ڱ߿����ݿ��ڵ�����
INT8U Get_Border_Point_Data(INT8U Area_No, INT16U X, INT16U Y) //��ȡһ��������һ���������
{
    INT8U Type,Data,Color,Index;
    //S_Simple_Border_Data *p;

    if(Area_No EQ MAX_AREA_NUM)
      return Get_Buf_Point_Data(Prog_Para.Border_Data, sizeof(Prog_Para.Border_Data), Screen_Para.Base_Para.Color, Prog_Para.Border_Width, X, Y);
    else
    {

      Type = Prog_Status.File_Para[Area_No].Pic_Para.Border_Type;

      if((Type >> 7) EQ 0)
      {
          if(Type >= S_NUM(Simple_Border_Data0))
             Type = 0;

          Index = GET_POINT_INDEX(Simple_Border_Data0[Type].Width,X,Y);

          Data = Get_Buf_Bit((INT8U *)Simple_Border_Data0[Type].Data, MAX_SBORDER_DATA_LEN,Index); //�߿��������һ�㲻����MAX_SBORDER_DATA_LEN�ֽ�
          Color = Prog_Status.File_Para[Area_No].Pic_Para.Border_Color;
          if(Color <= 0x01)
              return Data;
          else if(Color EQ 0x02)
              return Data<<1;
          else
              return (Data <<1) + Data;
      }
      else
      {
         Type = Type & 0x7F;

         if(Type >= S_NUM(Simple_Border_Data1))
            Type = 0;
         //--�����
      }
    }
}

void Draw_Border(S_Show_Data *pDst, INT8U Area_No, INT8U *pData, INT8U Width, INT8U Height,  INT32U Step)
{
   INT8U Re;
   INT16U i,j,Len;
   INT16U Area_Width, Area_Height;
   S_Point P0,P1;
   //INT8U Color;
   //S_Show_Data *pShow_Data;
   //INT16U Temp;

   Area_Width = Get_Area_Width(Area_No); //�����Ŀ�Ⱥ͸߶�
   Area_Height = Get_Area_Height(Area_No);
   Width = Get_Area_Border_Width(Area_No);

   //��Pub_Buf�н���һ��Show_Data,���ڸ�������
   //pShow_Data = (S_Show_Data *) &_Pub_Buf;

   //���±߿�
   for(i = 0; i < Width; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = Get_Border_Point_Data(Area_No, (i + Step) % Width, j);
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


   for(i = 0; i < Width; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = Get_Border_Point_Data(Area_No, (i + Step) % Width, j);
       Set_Area_Point_Data(pDst, Area_No, j, Width -1 - i, Re); //��߿�
       Set_Area_Point_Data(pDst, Area_No, Area_Width - 1 - j, i, Re); //�ұ߿�
     }

   P0.X = 0;
   P0.Y = 0;

   P1.X = 0;
   P1.Y = Width;
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
/*
//���Ʊ߿�
//pDst��ʾĿ�������
//Area_No��ʾĿ�����
//Width��ʾ�߿�Ԫͼ��Ŀ��
//Height��ʾ�߿�Ԫͼ��ĸ߶�
//pData��ʾ����
//Step��ʾ��ʾ����
void Draw_Border(S_Show_Data *pDst, INT8U Area_No, INT8U *pData, INT8U Width, INT8U Height,  INT32U Step)
{
   INT8U Re;
   INT16U i,j;
   INT16U Area_Width, Area_Height, Border_Width;
   INT16U Temp;
  
   Area_Width = Get_Area_Width(Area_No); //�����Ŀ�Ⱥ͸߶�
   Area_Height = Get_Area_Height(Area_No);
   Border_Width = Get_Area_Border_Width(Area_No);

   //�߿򳤿��Ƿ����
   if(Width*Height > MAX_BORDER_POINTS || Width EQ 0 || Height EQ 0 || Border_Width EQ 0)
   {
       ASSERT_FAILED();
       return;
   }

   //���±߿�
   for(i = 0; i < Area_Width; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = Get_Border_Point_Data(Area_No, (i + Step) % Border_Width, j);
       Set_Area_Point_Data(pDst, Area_No, i, j, Re); //�ϱ߿�
       Set_Area_Point_Data(pDst, Area_No, Area_Width-1 - i, Area_Height-1 - j, Re); //�±߿�
     }
  
   //���ұ߿�
   if(Area_Height > Height)
       Temp = Area_Height - Height;
   else
       Temp = 0;

   for(i = Height; i < Temp; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = Get_Border_Point_Data(Area_No, (i + Area_Width + Step) % Border_Width, j);
       Set_Area_Point_Data(pDst, Area_No, j, Area_Height - 1 - i, Re); //��߿�
       Set_Area_Point_Data(pDst, Area_No, Area_Width-1 -j, i, Re); //�ұ߿�
     }   
}
*/

//����߽�--��˸ʱ����
void Clr_Border(S_Show_Data *pDst, INT8U Area_No, INT8U Width, INT8U Height)
{

    INT16U Area_Width, Area_Height;//, Border_Width, Border_Height;
    S_Point P0;

    Area_Width = Get_Area_Width(Area_No); //�����Ŀ�Ⱥ͸߶�
    Area_Height = Get_Area_Height(Area_No);
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
    //INT8U Type;

  if(Area_No EQ MAX_AREA_NUM)
    return Prog_Para.Border_Width;
  else
  {
      if(1)//Prog_Status.File_Para[Area_No].Pic_Para.Border_Check > 0)
      {
        return Get_Simple_Border_Width(Prog_Status.File_Para[Area_No].Pic_Para.Border_Type);
      }
      else
      {
          return 0;
      }
  }
}

//��ȡĳ�������ĸ߶�
INT8U Get_Area_Border_Height(INT8U Area_No)
{
     INT8U Type;

  if(Area_No >= MAX_AREA_NUM)
    return Prog_Para.Border_Height;
  else
  {
      if(Prog_Status.File_Para[Area_No].Pic_Para.Border_Check > 0)
      {
        return Get_Simple_Border_Height(Prog_Status.File_Para[Area_No].Pic_Para.Border_Type);
      }
      else
      {
          return 0;
      }
    //return 0;
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
  S_Simple_Border_Data *p;
  INT8U i;

  //�����ƶ�״̬
  static S_Int16U Timer[MAX_AREA_NUM + 1];// = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Flag[MAX_AREA_NUM + 1];// = {CHK_BYTE, 0, CHK_BYTE};
    
  INT16U Step_Time = 0; //����ʱ��
  INT8U Border_Width,Border_Height;
  INT8U *pBorder_Data;
  INT8U Border_Mode;
  INT8U Type;

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
      //Timer[Area_No].Var += MOVE_STEP_PERIOD;
      Border_Mode = Prog_Para.Border_Mode;
      Border_Width = Get_Area_Border_Width(Area_No);
      Border_Height = Get_Area_Border_Height(Area_No);
      pBorder_Data = Prog_Para.Border_Data;
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
/*
      if(Prog_Status.Area_Status[Area_No].New_File_Flag > 0 ||\
	     Prog_Status.Area_Status[Area_No].New_SCN_Flag > 0)
          return;
		  */
/*
      if(Prog_Status.File_Para[Area_No].Pic_Para.In_Mode >= 2 &&
         Prog_Status.File_Para[Area_No].Pic_Para.In_Mode <= 7)
      {
         if(Prog_Status.Area_Status[Area_No].In_Step EQ 0)//����Ļ
          {
             Restore_Border_Data(Area_No);
             return;
         }

      }
*/
      TRACE();
//#if 0
      Step_Time = (INT16U)(Prog_Status.File_Para[Area_No].Pic_Para.Border_Speed + 1)*MOVE_STEP_PERIOD;//(Prog_Para.Border_Speed+ 1)*MAX_STEP_NUM; //MAX_STEP_NUMms�ĵ�һ���ٶȲ���
      Prog_Status.Border_Status[Area_No].Timer += MOVE_STEP_PERIOD;
      Max_Step = 0xFFFFFFFF;//Prog_Para.Area[Area_No].X_Len + Prog_Para.Area[Area_No].Y_Len;//Screen_Para.Base_Para.Width + Screen_Para.Base_Para.Height;
      //Timer[Area_No].Var += MOVE_STEP_PERIOD;
      Border_Mode = Prog_Status.File_Para[Area_No].Pic_Para.Border_Mode;
      Border_Width = Get_Area_Border_Width(Area_No);
      Border_Height = Get_Area_Border_Height(Area_No);
      p = Get_Simple_Border_Info(Prog_Status.File_Para[Area_No].Pic_Para.Border_Type);
      pBorder_Data = (INT8U *)(p->Data);
//#endif
/*
      Step_Time = 10;//Prog_Status.File_Para[Area_No].Pic_Para.Border_StayTime;//(Prog_Para.Border_Speed+ 1)*MAX_STEP_NUM; //MAX_STEP_NUMms�ĵ�һ���ٶȲ���
      Prog_Status.Border_Status[Area_No].Timer += MOVE_STEP_PERIOD;
      Timer[Area_No].Var += MOVE_STEP_PERIOD;

      Border_Width =  Get_Area_Border_Width(Area_No);
      Border_Height = Get_Area_Border_Height(Area_No);

      INT8U Type = Prog_Status.File_Para[Area_No].Pic_Para.Border_Type;
      pBorder_Data = (INT8U *)Simple_Border_Data[Type].Data;
      //pBorder_Data = Prog_Para.Border_Data;
*/
}
  //Size = Screen_Para.Base_Para.Width * Screen_Para.Base_Para.Height * GET_COLOR_NUM(Screen_Para.Base_Para.Color)/8;
  //MOVE_STEP = Calc_Move_Step();//Size / 8192 + 1;

  if(Prog_Status.Border_Status[Area_No].Timer >= Step_Time)
  {
    Prog_Status.Border_Status[Area_No].Timer = 0;

	if(Prog_Status.Border_Status[Area_No].Step + MOVE_STEP + Border_Width >= Max_Step)
	  Prog_Status.Border_Status[Area_No].Step = 0;//Max_Step - Prog_Status.Border_Status[Area_No].Step;
    
	//if(Prog_Status.Border_Status[Area_No].Step < Max_Step)
      Prog_Status.Border_Status[Area_No].Step += MOVE_STEP;

    //if(Prog_Status.Border_Status[Area_No].Step >= Max_Step)
     //Prog_Status.Border_Status[Area_No].Step = Prog_Status.Border_Status[Area_No].Step % Max_Step;


    Timer[Area_No].Var ++;
    if(Timer[Area_No].Var >= 2)
    {
        Timer[Area_No].Var = 0;
        Flag[Area_No].Var = 1 - Flag[Area_No].Var;
    }
  

    if(Border_Mode EQ BORDER_STATIC) //��̬
    {
      Draw_Border(&Show_Data, Area_No, pBorder_Data, \
                  Border_Width,  Border_Height, 0);
    }
    else if(Border_Mode EQ BORDER_FLASH) //��˸
    {
      if(Flag[Area_No].Var EQ 0)
        Draw_Border(&Show_Data, Area_No, pBorder_Data, \
                    Border_Width, Border_Height, 0);
      else
        Clr_Border(&Show_Data, Area_No, Border_Width, Border_Height);
    }
    else if(Border_Mode EQ BORDER_CLKWS) //˳ʱ��
    {
      Draw_Border(&Show_Data, Area_No, pBorder_Data, \
                  Border_Width, Border_Height, Max_Step - Border_Width - Prog_Status.Border_Status[Area_No].Step);
    }
    else if(Border_Mode EQ BORDER_CCLKWS) //��ʱ��
    {
      Draw_Border(&Show_Data, Area_No, pBorder_Data, \
                  Border_Width, Border_Height, Prog_Status.Border_Status[Area_No].Step);
    }
    else if(Border_Mode EQ BORDER_CLKWS_FLASH) //˳ʱ����˸
    {
      if(Flag[Area_No].Var EQ 0)
        Draw_Border(&Show_Data, Area_No, pBorder_Data, \
                    Border_Width, Border_Height, Max_Step - Border_Width - Prog_Status.Border_Status[Area_No].Step);
      else
        Clr_Border(&Show_Data, Area_No, Border_Width, Border_Height);      
    }
    else if(Border_Mode EQ BORDER_CCLKWS_FLASH) //��ʱ����˸
    {
      if(Flag[Area_No].Var EQ 0)
        Draw_Border(&Show_Data, Area_No, pBorder_Data, \
                    Border_Width, Border_Height, Prog_Status.Border_Status[Area_No].Step);
      else
        Clr_Border(&Show_Data, Area_No, Border_Width, Border_Height);        
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
