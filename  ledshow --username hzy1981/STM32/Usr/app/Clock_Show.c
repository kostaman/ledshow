#define CLOCK_SHOW_C
#include "Includes.h"

#if CLOCK_SHOW_EN

void Show_Clock_Point(S_Show_Data *pDst_Buf, INT8U Area_No, S_Clock_Para *pClock_Para)
{
    INT16U Radius;
    INT16U Width,Height;
    S_Point Point;
    INT16S Angle;

    Width = Get_Area_Width(Area_No);
    Height = Get_Area_Height(Area_No);

    Radius = ((Width < Height)? Width:Height) * 95 /100 / 2; //���̵İ뾶

    //Get_Area_TopLeft(Area_No, &Point); //��������λ��
    Point.X = 0;
    Point.Y = 0;
    //��������λ��
    Point.X += Width/2;
    Point.Y += Height/2;

    //�ֵ�
    if(pClock_Para->Min_Point_Radius)
    {
            for(Angle = 0; Angle < 360; Angle = Angle + 360/60)
            {
              if(Angle % 90 == 0 || Angle % (360/12) == 0) //369���Ѿ����ƹ��ˣ�����
                continue;
              //�������ĵ�ĽǶ���Angle��������Radius * 0.9, �õ�뾶ΪHour369_Point_Radius,��ɫΪ Hour369_Point_Color
              Fill_Clock_Point(pDst_Buf, Area_No, &Point, Angle, (INT16S)(Radius * 0.9), \
                  pClock_Para->Min_Point_Radius, pClock_Para->Min_Point_Style, pClock_Para->Min_Point_Color);
            }
    }

    //����
    if(pClock_Para->Hour_Point_Radius)
    {
            for(Angle = 0; Angle < 360; Angle = Angle + 360/12)
            {
              if(Angle % 90 == 0) //369���Ѿ����ƹ��ˣ�����
                continue;
              //�������ĵ�ĽǶ���Angle��������Radius * 0.9, �õ�뾶ΪHour369_Point_Radius,��ɫΪ Hour369_Point_Color
              Fill_Clock_Point(pDst_Buf, Area_No, &Point, Angle, (INT16S)(Radius * 0.9), \
                  pClock_Para->Hour_Point_Radius, pClock_Para->Hour_Point_Style, pClock_Para->Hour_Point_Color);
            }
    }

    //369��
    if(pClock_Para->Hour369_Point_Radius)
    {
            for(Angle = 0; Angle < 360; Angle = Angle + 90)
            {
              //�������ĵ�ĽǶ���Angle��������Radius * 0.9, �õ�뾶ΪHour369_Point_Radius,��ɫΪ Hour369_Point_Color
               Fill_Clock_Point(pDst_Buf, Area_No, &Point, Angle, Radius * 9 / 10, \
                  pClock_Para->Hour369_Point_Radius, pClock_Para->Hour369_Point_Style, pClock_Para->Hour369_Point_Color);
            }
    }

}

//��ʾһ������
//pDst_BufĿ����ʾ������
//Area_No Ŀ�����
//pClock_Para ʱ�Ӳ���
void Show_Clock(S_Show_Data *pDst_Buf, INT8U Area_No, S_Time *pTime, S_Clock_Para *pClock_Para)
{
   INT16U Radius;
   INT16U Width,Height;
   S_Point Point;
   //INT16S Angle;

   //return;

   if(Area_No >= MAX_AREA_NUM)
   {
     ASSERT_FAILED();
     return;
   }

   if(pTime->Time[T_SEC] >= 60 ||\
      pTime->Time[T_MIN] >= 60 ||\
      pTime->Time[T_HOUR] >= 24)
	  return;
   

   Width = Get_Area_Width(Area_No);
   Height = Get_Area_Height(Area_No);

   Radius = ((Width < Height)? Width:Height) * 95 /100 / 2; //���̵İ뾶

   //Get_Area_TopLeft(Area_No, &Point); //��������λ��
   Point.X = 0;
   Point.Y = 0;
   //��������λ��
   Point.X += Width/2;
   Point.Y += Height/2;
/*
   //�ֵ�
   if(pClock_Para->Min_Point_Radius)
   {
	   for(Angle = 0; Angle < 360; Angle = Angle + 360/60)
	   {
	     if(Angle % 90 == 0 || Angle % (360/12) == 0) //369���Ѿ����ƹ��ˣ�����
	       continue;
	     //�������ĵ�ĽǶ���Angle��������Radius * 0.9, �õ�뾶ΪHour369_Point_Radius,��ɫΪ Hour369_Point_Color
	     Fill_Clock_Point(pDst_Buf, Area_No, &Point, Angle, (INT16S)(Radius * 0.9), \
	         pClock_Para->Min_Point_Radius, pClock_Para->Min_Point_Style, pClock_Para->Min_Point_Color);
	   }
   }
 
   //����
   if(pClock_Para->Hour_Point_Radius)
   {
	   for(Angle = 0; Angle < 360; Angle = Angle + 360/12)
	   {
	     if(Angle % 90 == 0) //369���Ѿ����ƹ��ˣ�����
	       continue;
	     //�������ĵ�ĽǶ���Angle��������Radius * 0.9, �õ�뾶ΪHour369_Point_Radius,��ɫΪ Hour369_Point_Color
	     Fill_Clock_Point(pDst_Buf, Area_No, &Point, Angle, (INT16S)(Radius * 0.9), \
	         pClock_Para->Hour_Point_Radius, pClock_Para->Hour_Point_Style, pClock_Para->Hour_Point_Color);
	   }
   }
 
   //369��
   if(pClock_Para->Hour369_Point_Radius)
   {
	   for(Angle = 0; Angle < 360; Angle = Angle + 90)
	   {
	     //�������ĵ�ĽǶ���Angle��������Radius * 0.9, �õ�뾶ΪHour369_Point_Radius,��ɫΪ Hour369_Point_Color
	      Fill_Clock_Point(pDst_Buf, Area_No, &Point, Angle, Radius * 9 / 10, \
	         pClock_Para->Hour369_Point_Radius, pClock_Para->Hour369_Point_Style, pClock_Para->Hour369_Point_Color);
	   }
   }
*/
   //----------����0-11�����еĵ㶼�Ѿ��������------------
   //ʱ��
   if(pClock_Para->Hour_Line_Width)
   Fill_Clock_Line(pDst_Buf, Area_No, &Point, 90 - (360 * ((pTime->Time[T_HOUR] % 12) * 60 + pTime->Time[T_MIN]) / 720), Radius * 8 / 10,\
                   pClock_Para->Hour_Line_Width, pClock_Para->Hour_Line_Color);
   //����
   if(pClock_Para->Min_Line_Width)
   Fill_Clock_Line(pDst_Buf, Area_No, &Point, 90 - 360 * pTime->Time[T_MIN] / 60, Radius * 10 / 10,\
                   pClock_Para->Min_Line_Width, pClock_Para->Min_Line_Color);
   //����
   //pTime->Time[T_SEC] = 15;
   if(pClock_Para->Sec_Line_Width)
   Fill_Clock_Line(pDst_Buf, Area_No, &Point, 90 - 360 * pTime->Time[T_SEC] / 60, Radius * 12 / 10,\
                   pClock_Para->Sec_Line_Width, pClock_Para->Sec_Line_Color);

}
/*
struct tm {
    int tm_sec;        seconds after the minute (from 0)
    int tm_min;        minutes after the hour (from 0)
    int tm_hour;       hour of the day (from 0)
    int tm_mday;       day of the month (from 1)
    int tm_mon;        month of the year (from 0)
    int tm_year;       years since 1900 (from 0)
    int tm_wday;       days since Sunday (from 0)
    int tm_yday;       day of the year (from 0)
    int tm_isdst;      Daylight Saving Time flag
    };
*/
//mem_cpy((INT8U *)&Prog_Status.File_Para[0], &filePara, sizeof(filePara), (INT8U *)&Prog_Status.File_Para[0], sizeof(Prog_Status.File_Para[0]));

//��ʾ���̵����㡢�ֵ㡢369���
void Update_Clock_Point(S_Show_Data *pDst, INT8U Area_No)
{
  Show_Clock_Point(pDst, Area_No, (S_Clock_Para *)&Prog_Status.File_Para[Area_No].Clock_Para);
}

//���±�������
void Update_Clock_Data(S_Show_Data *pDst, INT8U Area_No)
{
  S_Point P0;
  INT16S tmp;
  INT16U Width,Height;
  INT8U Font;
  INT16U StrWidth, StrHeight;
  time_t CurSec;
  S_Time sTime;
  struct tm tTime, *ptm;
  
  Width = Get_Area_Width(Area_No);
  Height = Get_Area_Height(Area_No);

  //�Ƿ���Ҫ����ʱ��
  if(Prog_Status.File_Para[Area_No].Clock_Para.Hour_Diff != 0 ||\
     Prog_Status.File_Para[Area_No].Clock_Para.Min_Diff != 0)
  {
    S_Time_2_tm(&Cur_Time, &tTime);
    CurSec = mktime(&tTime);
    
    if(Prog_Status.File_Para[Area_No].Clock_Para.Diff_Flag EQ 0) //����
      CurSec += Prog_Status.File_Para[Area_No].Clock_Para.Hour_Diff*3600 +\
                Prog_Status.File_Para[Area_No].Clock_Para.Min_Diff*60;
    else
      CurSec -= Prog_Status.File_Para[Area_No].Clock_Para.Hour_Diff*3600 +\
                Prog_Status.File_Para[Area_No].Clock_Para.Min_Diff*60;
    
    ptm = localtime(&CurSec);
    tm_2_S_Time(ptm, &sTime); 
  }
  else
  {
    mem_cpy(&sTime, &Cur_Time, sizeof(Cur_Time), &sTime, sizeof(sTime)); 
  }
  
  /*
  //----------�̶��ı�---------
  tmp = (INT16S)(Width * Prog_Status.File_Para[Area_No].Clock_Para.Text_X / 100) - (INT16S)Prog_Status.File_Para[Area_No].Clock_Para.Text_Width/2;
  if(tmp > 0)
    P0.X = (INT16U)tmp;
  else
    P0.X = 0;

  tmp = (INT16S)(Height * Prog_Status.File_Para[Area_No].Clock_Para.Text_Y / 100) - (INT16S)(Prog_Status.File_Para[Area_No].Clock_Para.Text_Height/2);
  if(tmp > 0)
    P0.Y = (INT16U)tmp;
  else
    P0.Y = 0;

  Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Status.File_Para[Area_No].Clock_Para.Text_Width, Prog_Status.File_Para[Area_No].Clock_Para.Text_Height, &Show_Data, &P0);//&Point);
*/
  //---------����---------
  if(Prog_Status.File_Para[Area_No].Clock_Para.Week_Type > 0)
  {
      INT8U Font = Prog_Status.File_Para[Area_No].Clock_Para.Week_Font; //����
      INT16U StrWidth = Get_WeekStr_Pix_Width(Prog_Status.File_Para[Area_No].Clock_Para.Week_Type - 1, Font, Cur_Time.Time[T_WEEK]);
      INT8U StrHeight = Get_Font_Height(Font);

      tmp = (INT16S)(Width*Prog_Status.File_Para[Area_No].Clock_Para.Week_X / 100) - (INT16S)StrWidth / 2;
      if(tmp > 0)
        P0.X = tmp;
      else
        P0.X = 0;

      tmp = (INT16S)Height * Prog_Status.File_Para[Area_No].Clock_Para.Week_Y / 100 - (INT16S)StrHeight/2;
      if(tmp > 0)
        P0.Y = tmp;
      else
        P0.Y = 0;

      Show_Week(pDst, Area_No, P0.X, P0.Y, &Cur_Time, Prog_Status.File_Para[Area_No].Clock_Para.Week_Type - 1, Prog_Status.File_Para[Area_No].Clock_Para.Week_Font, Prog_Status.File_Para[Area_No].Clock_Para.Week_Color);
   }

  //��ʾ����
  if(Prog_Status.File_Para[Area_No].Clock_Para.Date_Type > 0)
  {
      Font = Prog_Status.File_Para[Area_No].Clock_Para.Date_Font; //����
      StrWidth = Get_DateStr_Pix_Width(Prog_Status.File_Para[Area_No].Clock_Para.Date_Type - 1,Font);
      StrHeight = Get_Font_Height(Font);

      tmp = Width*Prog_Status.File_Para[Area_No].Clock_Para.Date_X / 100 - StrWidth / 2;
      if(tmp > 0)
        P0.X = tmp;
      else
        P0.X = 0;

      tmp = Height * Prog_Status.File_Para[Area_No].Clock_Para.Date_Y / 100 - StrHeight/2;
      if(tmp > 0)
        P0.Y = tmp;
      else
        P0.Y = 0;

      Show_Date(pDst, Area_No, P0.X, P0.Y, &Cur_Time, Prog_Status.File_Para[Area_No].Clock_Para.Date_Type - 1, Prog_Status.File_Para[Area_No].Clock_Para.Date_Font, Prog_Status.File_Para[Area_No].Clock_Para.Date_Color);
   }
  
   Show_Clock(pDst, Area_No, &sTime, (S_Clock_Para *)&Prog_Status.File_Para[Area_No].Clock_Para);
}
#endif

