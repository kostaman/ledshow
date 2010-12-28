#define TIMER_SHOW_C
#include "Includes.h"

#define DAY_SEC (1440*60)
#define HOUR_SEC 3600
#define MIN_SEC 60

/*
    styleCombo->addItem(tr("%3d��%2dʱ%2d��%2d��"));
    styleCombo->addItem(tr("%2d��%2dʱ%2d��%2d��"));
    styleCombo->addItem(tr("%3d��%2dʱ%2d��"));
    styleCombo->addItem(tr("%2d��%2dʱ%2d��"));
    styleCombo->addItem(tr("%3d��%2dʱ"));
    styleCombo->addItem(tr("%2d��%2dʱ"));
    styleCombo->addItem(tr("%3d��"));
    styleCombo->addItem(tr("%2d��"));
    styleCombo->addItem(tr("%2dʱ%2d��%2d��"));
    styleCombo->addItem(tr("%2dʱ%2d��"));
    styleCombo->addItem(tr("%2dʱ"));
    styleCombo->addItem(tr("%2d��%2d��"));
    styleCombo->addItem(tr("%2d��"));
 */
const S_Format_Str TimerStr[]=
{
    {"%4d��%2dʱ%2d��%2d��", 18},
    {"%3d��%2dʱ%2d��%2d��", 17}, //0-14
    {"%2d��%2dʱ%2d��%2d��", 16}, //1-12
    {"%4d��%2dʱ%2d��",14},
    {"%3d��%2dʱ%2d��",13},    //2-9
    {"%2d��%2dʱ%2d��",12},    //3-9
    {"%4d��%2dʱ",10},
    {"%3d��%2dʱ",9},    //4
    {"%2d��%2dʱ",8},    //5
    {"%4d��",6},
    {"%3d��",5},      //6
    {"%2d��", 4},   //7
    {"%2dʱ%2d��%2d��", 12},   //8
    {"%2dʱ%2d��", 8},            //9
    {"%2dʱ", 4},           //10
    {"%2d��%2d��", 8},            //9
    {"%2d��", 4},            //9
    {"%2d��", 4}           //10
};

INT16U Show_Timer(S_Show_Data *pDst_Buf, INT8U Area_No, INT16U X, INT16U Y, S_Time *pCurTime, S_Time *pDstTime, INT8U Type, INT8U Font, INT8U Color)
{
    INT16U d,h,m,s,Len = 0;
    time_t CurSec, DstSec, DiffSec;
    struct tm tTime;
    
    S_Time_2_tm(pCurTime, &tTime);
    CurSec = mktime(&tTime);
    S_Time_2_tm(pDstTime, &tTime);
    DstSec = mktime(&tTime);

    if(CurSec > DstSec)
        DiffSec = CurSec - DstSec;
    else
        DiffSec = DstSec - CurSec;

    if(Type <= 2)
    {
        d = DiffSec / DAY_SEC;
        h = (DiffSec % DAY_SEC) / HOUR_SEC;
        m = ((DiffSec % DAY_SEC) % HOUR_SEC) / MIN_SEC;
        s = DiffSec % MIN_SEC;

        Len = LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d,h,m,s);
    }
    else if(Type >= 3 && Type <= 5)
    {
        d = DiffSec / DAY_SEC;
        h = (DiffSec % DAY_SEC) / HOUR_SEC;
        m = ((DiffSec % DAY_SEC) % HOUR_SEC) / MIN_SEC;

        Len = LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d,h,m);
    }
    else if(Type >= 6 && Type <= 8)
    {
        d = DiffSec / DAY_SEC;
        h = (DiffSec % DAY_SEC) / HOUR_SEC;

        Len = LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d,h);
    }
    else if(Type >= 9 && Type <= 11)
    {
        d = DiffSec / DAY_SEC;

        Len = LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d);
    }
    else if(Type EQ 12)
    {
        h = DiffSec / HOUR_SEC;
        m = (DiffSec % HOUR_SEC) / MIN_SEC;
        s = DiffSec % MIN_SEC;

        Len = LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, h,m,s);
    }
    else if(Type EQ 13)
    {
        h = DiffSec / HOUR_SEC;
        m = (DiffSec % HOUR_SEC) / MIN_SEC;

        Len = LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, h,m);
    }
    else if(Type EQ 14)
    {
        h = DiffSec / HOUR_SEC;

        Len = LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str);
    }
    else if(Type EQ 15)
    {
        m = DiffSec / MIN_SEC;
        s = (DiffSec % MIN_SEC) % MIN_SEC;

        Len = LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, m,s);
    }
    else if(Type EQ 16)
    {
        m = DiffSec / MIN_SEC;

        Len = LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, m);
    }
    else if(Type EQ 17)
    {
        s = DiffSec;

        Len = LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, s);
    }

    return Len;
/*
    if(Type >= 0 )
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d,h,m,s);
    else if(Type EQ 1)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d,h,m,s);
    else if(Type EQ 2)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d,h,m);
    else if(Type EQ 3)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d,h,m);
    else if(Type EQ 4)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d,h);
    else if(Type EQ 5)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d,h);
    else if(Type EQ 6)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d);
    else if(Type EQ 7)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, d);
    else if(Type EQ 8)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, h,m,s);
    else if(Type EQ 9)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, h,m);
    else if(Type EQ 10)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, m,s);
    else if(Type EQ 11)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, m);
    else if(Type EQ 12)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimerStr[Type].str, s);
    else
        ASSERT_FAILED();
 */
}

//��ʱ�ַ��������ؿ��
INT16U Get_TimerStr_Pix_Width(INT8U Type, INT8U Font)
{
   return TimerStr[Type].Len*Get_Font_Width(Font);
}

//��ʾ��ʱ��Ϣ����С���
INT16U Get_Timer_Min_Width(INT8U Area_No)
{
    INT16U StrWidth;
    //INT8U Font,Type;
    StrWidth = Get_TimerStr_Pix_Width(Prog_Status.File_Para[Area_No].Timer_Para.Timer_Type, \
                                      Prog_Status.File_Para[Area_No].Timer_Para.Timer_Font);


   if(Prog_Status.File_Para[Area_No].Timer_Para.SmLineFlag == SLINE_MODE)//����
   {
      return Prog_Status.File_Para[Area_No].Timer_Para.Text_Width + SPACE_WIDTH + StrWidth;
   }
   else
   {
      if(Prog_Status.File_Para[Area_No].Timer_Para.Text_Width > StrWidth)
          return Prog_Status.File_Para[Area_No].Timer_Para.Text_Width;
      else
          return StrWidth;
   }
}

//��ʾ��ʱ��Ϣ����С�߶�
INT16U Get_Timer_Min_Height(INT8U Area_No)
{
    INT16U StrHeight;
    INT16U Height;

    StrHeight = Get_Font_Height(Prog_Status.File_Para[Area_No].Timer_Para.Timer_Font);

    if(Prog_Status.File_Para[Area_No].Timer_Para.SmLineFlag == SLINE_MODE)//����
    {
        if(Prog_Status.File_Para[Area_No].Timer_Para.Text_Height > StrHeight)
            return Prog_Status.File_Para[Area_No].Timer_Para.Text_Height;
        else
            return StrHeight;
    }
    else
    {
        Height = Prog_Status.File_Para[Area_No].Timer_Para.Text_Height + StrHeight;
        if(Prog_Status.File_Para[Area_No].Timer_Para.Text_Height > 0)
          Height += Prog_Status.File_Para[Area_No].Timer_Para.LineSpace;
        return Height;
    }
}

//���¶�ʱ������
void Update_Timer_Data(INT8U Area_No)
{
    //INT16U X, Y;
    S_Point P0;
    INT16U Width,Height;
    INT16U Min_Width, Min_Height;
    S_Time Dst_Time;

    Width = Get_Area_Width(Area_No);
    Height = Get_Area_Height(Area_No);

    Min_Width = Get_Timer_Min_Width(Area_No);
    Min_Height = Get_Timer_Min_Height(Area_No);

    Dst_Time.Time[T_YEAR] = Prog_Status.File_Para[Area_No].Timer_Para.Dst_Year;
    Dst_Time.Time[T_MONTH] = Prog_Status.File_Para[Area_No].Timer_Para.Dst_Month;
    Dst_Time.Time[T_DATE] = Prog_Status.File_Para[Area_No].Timer_Para.Dst_Date;
    Dst_Time.Time[T_HOUR] = Prog_Status.File_Para[Area_No].Timer_Para.Dst_Hour;
    Dst_Time.Time[T_MIN] = Prog_Status.File_Para[Area_No].Timer_Para.Dst_Min;
    Dst_Time.Time[T_SEC] = Prog_Status.File_Para[Area_No].Timer_Para.Dst_Sec;

    if(Prog_Status.File_Para[Area_No].Timer_Para.SmLineFlag == SLINE_MODE)//����
    {
      if(Width > Min_Width)
        P0.X = (Width - Min_Width) / 2;
      else
        P0.X = 0;

      if(Height > Prog_Status.File_Para[Area_No].Timer_Para.Text_Height)
        P0.Y = (Height - Prog_Status.File_Para[Area_No].Timer_Para.Text_Height)/2;
      else
        P0.Y = 0;//(Height - Prog_Status.File_Para[Area_No].Timer_Para.Text_Height)/2;
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Status.File_Para[Area_No].Timer_Para.Text_Width, Prog_Status.File_Para[Area_No].Timer_Para.Text_Height, &Show_Data, &P0);//&Point);


      P0.X = P0.X + Prog_Status.File_Para[Area_No].Timer_Para.Text_Width;
      if(P0.X > 0)
        P0.X += SPACE_WIDTH;//Get_Font_Width(Prog_Status.File_Para[Area_No].Timer_Para.);

      if(Height > Get_Font_Height(Prog_Status.File_Para[Area_No].Timer_Para.Timer_Font))
        P0.Y = (Height - Get_Font_Height(Prog_Status.File_Para[Area_No].Timer_Para.Timer_Font))/2;
      else
        P0.Y = 0;

      Show_Timer(&Show_Data, Area_No, P0.X, P0.Y, &Cur_Time, &Dst_Time, \
                 Prog_Status.File_Para[Area_No].Timer_Para.Timer_Type, Prog_Status.File_Para[Area_No].Timer_Para.Timer_Font,Prog_Status.File_Para[Area_No].Timer_Para.Timer_Color);
  }
  else
  {
      if(Height > Min_Height)
        P0.Y = (Height - Min_Height) / 2;
      else
        P0.Y = 0;

      if(Width > Prog_Status.File_Para[Area_No].Timer_Para.Text_Width)
        P0.X = (Width - Prog_Status.File_Para[Area_No].Timer_Para.Text_Width)/2;
      else
        P0.X = 0;//(Height - Prog_Status.File_Para[Area_No].Timer_Para.Text_Height)/2;
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Status.File_Para[Area_No].Timer_Para.Text_Width, Prog_Status.File_Para[Area_No].Timer_Para.Text_Height, &Show_Data, &P0);//&Point);

      P0.Y = P0.Y + Prog_Status.File_Para[Area_No].Timer_Para.Text_Height;
      
      if(Prog_Status.File_Para[Area_No].Timer_Para.Text_Height > 0)
        P0.Y += Prog_Status.File_Para[Area_No].Timer_Para.LineSpace;
      
      if(Width > Get_TimerStr_Pix_Width(Prog_Status.File_Para[Area_No].Timer_Para.Timer_Type, Prog_Status.File_Para[Area_No].Timer_Para.Timer_Font))
        P0.X = (Width - Get_TimerStr_Pix_Width(Prog_Status.File_Para[Area_No].Timer_Para.Timer_Type, Prog_Status.File_Para[Area_No].Timer_Para.Timer_Font))/2;
      else
        P0.X = 0;

      Show_Timer(&Show_Data, Area_No, P0.X, P0.Y, &Cur_Time, &Dst_Time, \
                 Prog_Status.File_Para[Area_No].Timer_Para.Timer_Type, Prog_Status.File_Para[Area_No].Timer_Para.Timer_Font,Prog_Status.File_Para[Area_No].Timer_Para.Timer_Color);

  }
  
  Prog_Status.Area_Status[Area_No].Step = 100; //һ����ʾ��λ��ֱ��100%
}
