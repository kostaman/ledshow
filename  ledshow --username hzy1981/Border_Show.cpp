#define BORDER_SHOW_C
#include "Includes.h"

#if BORDER_SHOW_EN > 0
//获取边框数据
//X\Y表示在边框数据块内的索引
INT8U Get_Border_Point_Data(INT8U Area_No, INT16U X, INT16U Y) //获取一个区域内一个点的数据
{
  if(Area_No EQ MAX_AREA_NUM)
    return Get_Buf_Point_Data(Prog_Para.Border_Data, sizeof(Prog_Para.Border_Data), Screen_Para.Color, Prog_Para.Border_Width, X, Y);   
  else
    return 0;
}
                     
//绘制边框
//pDst表示目标绘制区
//Area_No表示目标分区
//Width表示边框单元图像的宽度
//Height表示边框单元图像的高度
//pData表示数据
//Step表示显示步进
void Draw_Border(S_Show_Data *pDst, INT8U Area_No, INT8U *pData, INT8U Width, INT8U Height,  INT8U Step)
{
   INT8U Re;
   INT16U i,j;
   INT16U Area_Width, Area_Height;
   
  
   Area_Width = Get_Area_Width(Area_No); //分区的宽度和高度
   Area_Height = Get_Area_Height(Area_No);
   
   //上下边框
   for(i = 0; i < Area_Width; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = Get_Border_Point_Data(Area_No, (i + Prog_Para.Border_Width *Step / 100) % Prog_Para.Border_Width, j);  
       Set_Area_Point_Data(pDst, Area_No, i, j, Re); //上边框
       Set_Area_Point_Data(pDst, Area_No, Area_Width-1 - i, Area_Height-1 - j, Re); //下边框
     }
  
   //左右边框
   for(i = 0; i < Area_Height; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = Get_Border_Point_Data(Area_No, (i + Prog_Para.Border_Width *Step / 100) % Prog_Para.Border_Width, j);  
       Set_Area_Point_Data(pDst, Area_No, j, i, Re); //左边框
       Set_Area_Point_Data(pDst, Area_No, Area_Width-1 -j, Area_Height-1-i, Re); //右边框
     }   
}

//清除边界--闪烁时调用
void Clr_Border(S_Show_Data *pDst, INT8U Area_No, INT8U Width, INT8U Height)
{
   INT8U Re;
   INT16U i,j;
   INT16U Area_Width, Area_Height;
   
  
   Area_Width = Get_Area_Width(Area_No); //分区的宽度和高度
   Area_Height = Get_Area_Height(Area_No);
   
   //上下边框
   for(i = 0; i < Area_Width; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = 0;//Get_Border_Point_Data((i + Prog_Para.Border_Width *Step / 100) % Prog_Para.Border_Width, j);  
       Set_Area_Point_Data(pDst, Area_No, i, j, Re); //上边框
       Set_Area_Point_Data(pDst, Area_No, Area_Width - i, Area_Height - j, Re); //下边框
     }
  
   //左右边框
   for(i = 0; i < Area_Height; i ++)
     for(j = 0; j < Height; j ++)
     {
       Re = 0;//Get_Border_Point_Data((i + Prog_Para.Border_Width *Step / 100) % Prog_Para.Border_Width, j);  
       Set_Area_Point_Data(pDst, Area_No, j, i, Re); //左边框
       Set_Area_Point_Data(pDst, Area_No, Area_Width -j, Area_Height-j, Re); //右边框
     }  
  
}

//获取某个分区的宽度
INT8U Get_Area_Border_Width(INT8U Area_No)
{
  if(Area_No EQ MAX_AREA_NUM)
    return Prog_Para.Border_Width;
  else
    return 0;
}

//获取某个分区的高度
INT8U Get_Area_Border_Height(INT8U Area_No)
{
  if(Area_No EQ MAX_AREA_NUM)
    return Prog_Para.Border_Height;
  else
    return 0;
}

//更新边框数据
void Update_Border_Data(INT8U Area_No)
{
  //INT8U In_Mode;
  //还在移动状态
  static S_Int8U Flag = {CHK_BYTE, 0, CHK_BYTE}; 
    
  INT32U Step_Time = 0; //步进时间
  INT8U Border_Width,Border_Height;
  
  if(Prog_Para.Border_Check EQ 0)
      return;

  Prog_Status.Border_Status.Timer += MOVE_STEP_TIMER;
  
  Border_Width = Get_Area_Border_Width(Area_No);
  Border_Height = Get_Area_Border_Height(Area_No);
  
  if(Prog_Status.Border_Status.Timer >= Step_Time)
  {
    Prog_Status.Border_Status.Timer = 0;
    Step_Time = (Prog_Para.Border_Speed+ 1)*100; //100ms的的一个速度步进
  
    if(Prog_Status.Border_Status.Step < 100)
      Prog_Status.Border_Status.Step += MOVE_STEP;
    
    if(Prog_Status.Border_Status.Step > 100)
      Prog_Status.Border_Status.Step = 0;
    
    if(Prog_Para.Border_Mode EQ BORDER_STATIC) //静态 
    {
      Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                  Border_Width,  Border_Height, 0);
    }
    else if(Prog_Para.Border_Mode EQ BORDER_FLASH) //闪烁
    {
      if(Flag.Var EQ 0)
        Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                    Border_Width, Border_Height, 0);
      else
        Clr_Border(&Show_Data, Area_No, Border_Width, Border_Height);
    }
    else if(Prog_Para.Border_Mode EQ BORDER_CLKWS) //顺时针
    {
      Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                  Border_Width, Border_Height, 100 - Prog_Status.Border_Status.Step);      
    }
    else if(Prog_Para.Border_Mode EQ BORDER_CCLKWS) //逆时针
    {
      Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                  Border_Width, Border_Height, Prog_Status.Border_Status.Step);      
    }
    else if(Prog_Para.Border_Mode EQ BORDER_CLKWS_FLASH) //顺时针闪烁
    {
      if(Flag.Var EQ 0)
        Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                    Border_Width, Border_Height, 100 - Prog_Status.Border_Status.Step);
      else
        Clr_Border(&Show_Data, Area_No, Border_Width, Border_Height);      
    }
    else if(Prog_Para.Border_Mode EQ BORDER_CCLKWS_FLASH) //逆时针闪烁
    {
      if(Flag.Var EQ 0)      
        Draw_Border(&Show_Data, Area_No, Prog_Para.Border_Data, \
                    Border_Width, Border_Height, Prog_Status.Border_Status.Step);
      else
        Clr_Border(&Show_Data, Area_No, Border_Width, Border_Height);        
    }    
      
  }
  
  if(Flag.Var > 0)
    Flag.Var = 0;
  else
    Flag.Var = 1;
}
#endif
#undef BORDER_SHOW_C
