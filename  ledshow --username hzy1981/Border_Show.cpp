#define BORDER_SHOW_C
#include "Includes.h"

#if BORDER_SHOW_EN > 0
//��ȡ�߿�����
//X\Y��ʾ�ڱ߿����ݿ��ڵ�����
INT8U Get_Border_Point_Data(INT8U Area_No, INT16U X, INT16U Y) //��ȡһ��������һ���������
{
  if(Area_No EQ MAX_AREA_NUM)
    return Get_Buf_Point_Data(Prog_Para.Border_Data, sizeof(Prog_Para.Border_Data), Screen_Para.Base_Para.Color, Prog_Para.Border_Width, X, Y);
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
   INT16U Area_Width, Area_Height;
   
  
   Area_Width = Get_Area_Width(Area_No); //�����Ŀ�Ⱥ͸߶�
   Area_Height = Get_Area_Height(Area_No);

   //�߿򳤿��Ƿ����
   if(Width*Height > MAX_BORDER_POINTS || Width EQ 0 || Height EQ 0)
   {
       ASSERT_FAILED();
       return;
   }

   //���±߿�
   for(i = 0; i < Area_Width; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = Get_Border_Point_Data(Area_No, (i + Prog_Para.Border_Width *Step / 100) % Prog_Para.Border_Width, j);  
       Set_Area_Point_Data(pDst, Area_No, i, j, Re); //�ϱ߿�
       Set_Area_Point_Data(pDst, Area_No, Area_Width-1 - i, Area_Height-1 - j, Re); //�±߿�
     }
  
   //���ұ߿�
   for(i = 0; i < Area_Height; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = Get_Border_Point_Data(Area_No, (i + Prog_Para.Border_Width *Step / 100) % Prog_Para.Border_Width, j);  
       Set_Area_Point_Data(pDst, Area_No, j, Area_Height - 1 - i, Re); //��߿�
       Set_Area_Point_Data(pDst, Area_No, Area_Width-1 -j, i, Re); //�ұ߿�
     }   
}

//����߽�--��˸ʱ����
void Clr_Border(S_Show_Data *pDst, INT8U Area_No, INT8U Width, INT8U Height)
{
    INT8U Re;
    INT16U i,j;
    INT16U Area_Width, Area_Height;


    Area_Width = Get_Area_Width(Area_No); //�����Ŀ�Ⱥ͸߶�
    Area_Height = Get_Area_Height(Area_No);

    //�߿򳤿��Ƿ����
    if(Width*Height > MAX_BORDER_POINTS || Width EQ 0 || Height EQ 0)
    {
        ASSERT_FAILED();
        return;
    }

    //���±߿�
    for(i = 0; i < Area_Width; i ++)
      for(j = 0; j < Height; j ++)
      {
        Re = 0;//Get_Border_Point_Data(Area_No, (i + Prog_Para.Border_Width *Step / 100) % Prog_Para.Border_Width, j);
        Set_Area_Point_Data(pDst, Area_No, i, j, Re); //�ϱ߿�
        Set_Area_Point_Data(pDst, Area_No, Area_Width-1 - i, Area_Height-1 - j, Re); //�±߿�
      }

    //���ұ߿�
    for(i = 0; i < Area_Height; i ++)
      for(j = 0; j < Height; j ++)
      {
        Re = 0;//Get_Border_Point_Data(Area_No, (i + Prog_Para.Border_Width *Step / 100) % Prog_Para.Border_Width, j);
        Set_Area_Point_Data(pDst, Area_No, j, Area_Height - 1 - i, Re); //��߿�
        Set_Area_Point_Data(pDst, Area_No, Area_Width-1 -j, i, Re); //�ұ߿�
      }
}

//��ȡĳ�������Ŀ��
INT8U Get_Area_Border_Width(INT8U Area_No)
{
  if(Area_No EQ MAX_AREA_NUM)
    return Prog_Para.Border_Width;
  else
    return 0;
}

//��ȡĳ�������ĸ߶�
INT8U Get_Area_Border_Height(INT8U Area_No)
{
  if(Area_No EQ MAX_AREA_NUM)
    return Prog_Para.Border_Height;
  else
    return 0;
}

//���±߿�����
void Update_Border_Data(INT8U Area_No)
{
  //INT8U In_Mode;
  //�����ƶ�״̬
    static S_Int16U Timer = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Flag = {CHK_BYTE, 0, CHK_BYTE}; 
    
  INT16U Step_Time = 0; //����ʱ��
  INT8U Border_Width,Border_Height;
  
  if(Prog_Para.Border_Check EQ 0)
      return;

  Step_Time = Prog_Para.Border_StayTime;//(Prog_Para.Border_Speed+ 1)*100; //100ms�ĵ�һ���ٶȲ���
  Prog_Status.Border_Status.Timer += MOVE_STEP_TIMER;
  Timer.Var += MOVE_STEP_TIMER;

  Border_Width = Get_Area_Border_Width(Area_No);
  Border_Height = Get_Area_Border_Height(Area_No);
  
  if(Prog_Status.Border_Status.Timer >= Step_Time)
  {
    Prog_Status.Border_Status.Timer = 0;

    if(Prog_Status.Border_Status.Step >= 100)
      Prog_Status.Border_Status.Step = 0;

    if(Prog_Status.Border_Status.Step < 100)
      Prog_Status.Border_Status.Step += MOVE_STEP;
        
    if(Prog_Para.Border_Mode EQ BORDER_STATIC) //��̬ 
    {
      Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                  Border_Width,  Border_Height, 0);
    }
    else if(Prog_Para.Border_Mode EQ BORDER_FLASH) //��˸
    {
      if(Flag.Var EQ 0)
        Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                    Border_Width, Border_Height, 0);
      else
        Clr_Border(&Show_Data, Area_No, Border_Width, Border_Height);
    }
    else if(Prog_Para.Border_Mode EQ BORDER_CLKWS) //˳ʱ��
    {
      Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                  Border_Width, Border_Height, 100 - Prog_Status.Border_Status.Step);      
    }
    else if(Prog_Para.Border_Mode EQ BORDER_CCLKWS) //��ʱ��
    {
      Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                  Border_Width, Border_Height, Prog_Status.Border_Status.Step);      
    }
    else if(Prog_Para.Border_Mode EQ BORDER_CLKWS_FLASH) //˳ʱ����˸
    {
      if(Flag.Var EQ 0)
        Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                    Border_Width, Border_Height, 100 - Prog_Status.Border_Status.Step);
      else
        Clr_Border(&Show_Data, Area_No, Border_Width, Border_Height);      
    }
    else if(Prog_Para.Border_Mode EQ BORDER_CCLKWS_FLASH) //��ʱ����˸
    {
      if(Flag.Var EQ 0)      
        Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                    Border_Width, Border_Height, Prog_Status.Border_Status.Step);
      else
        Clr_Border(&Show_Data, Area_No, Border_Width, Border_Height);        
    }    
      
  }
  
  if(Timer.Var >= 500)
  {
      Timer.Var = 0;
      if(Flag.Var > 0)
        Flag.Var = 0;
      else
        Flag.Var = 1;
    }
}
#endif
#undef BORDER_SHOW_C
