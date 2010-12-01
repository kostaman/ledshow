#define TIME_SHOW_C
#include "Includes.h"

const char WeekStr[][7][15] =
{
{"������","����һ","���ڶ�","������","������","������","������"},

//const char WeekStr1[][10] =
{"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday", "Saturday"},

//const char WeekStr2[][6] =
{ "Sun","Mon","Tues","Wed","Thur","Fri","Sat"},

//const char WeekStr3[][12] =
{"domenica","lunedi\��","martedi\��","mercoledi\��","giovedi\��","venerdi\��","sabato"},

//const char WeekStr4[][12] =
{"Sonntag","Montag","Dienstag","Mittwoch","Donnerstag","Freitag","Samstag"}, //����

//const char WeekStr5[][10] =
{"dimanche","lundi","mardi","mercredi","jeudi", "vendredi","samedi"},//����

//const char WeekStr6[][12] =
{"�ˤ��褦��","���Ĥ褦��","���褦��","�����褦��","�⤯�褦��","����褦��","�ɤ褦��"}
};

const S_Format_Str DateStr[]=
{
    {"%4d��%2d��%2d��", 14}, //0-14
    {"%2d��%2d��%2d��", 12}, //1-12
    {"%2d/%2d/%4d",10},    //2-9
    {"%4d/%2d/%2d",10},    //3-9
    {"%2d-%2d-%2d",8},    //4
    {"%2d.%2d.%2d",8},    //5
    {"%2d��%2d��",8},      //6
    {"%2d.%2d.%4d", 10},   //7
    {"%4d-%2d-%2d", 10},   //8
    {"%4d", 4},            //9
    {"%2d", 2},           //10
    {"%2d",2}             //11
};

const S_Format_Str TimeStr[] =
{
    {"%2dʱ%2d��%2d��", 12}, //0
    {"%2d:%2d:%2d",8},    //1
    {"%2dʱ%2d��", 8},      //2
    {"%2d:%2d",5},        //3
    {"%2dʱ",4},           //4
    {"%2d��",4},          //5
    {"%2d��",4},          //6
    {"���� %2d:%2d",10},    //7
    {"AM %2d:%2d", 8},    //8
    {"%2d:%2d ����",10},    //9
    {"%2d:%2d AM",8}      //10
};

//��ʾ����
void Show_Date(S_Show_Data *pDst_Buf, INT8U Area_No, INT16U X, INT16U Y, S_Time *pTime, INT8U Type, INT8U Font, INT8U Color)
{
  INT16U y,m,d;

  y = pTime->Time[T_YEAR];
  m = pTime->Time[T_MONTH];
  d = pTime->Time[T_DATE];

  if(Type EQ 0)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, y + 2000, m, d);
  else if(Type EQ 1)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, y, m, d);
  else if(Type EQ 2)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, m, d, y + 2000);
  else if(Type EQ 3)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, y + 2000, m, d);
  else if(Type EQ 4)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, y, m, d);
  else if(Type EQ 5)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, y, m, d);
  else if(Type EQ 6)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, m, d);
  else if(Type EQ 7)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, m, d, y + 2000);
  else if(Type EQ 8)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, y + 2000, m, d);
  else if(Type EQ 9)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, y + 2000);
  else if(Type EQ 10)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, m);
  else if(Type EQ 11)
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, DateStr[Type].str, d);
}

//��ȡ������ʾ�����ؿ��
INT16U Get_DateStr_Pix_Width(INT8U Type, INT8U Font)
{
  return DateStr[Type].Len*Get_Font_Width(Font)/2;
}

//��ȡ������ʾ�����ؿ��
INT16U Get_WeekStr_Pix_Width(INT8U Type, INT8U Font, INT8U Week)
{
  return strlen(WeekStr[Type][Week])*Get_Font_Width(Font)/2;
}

//��ȡʱ����ʾ�����ؿ��
INT16U Get_TimeStr_Pix_Width(INT8U Type, INT8U Font)
{
  return TimeStr[Type].Len*Get_Font_Width(Font)/2;

}

/*
    timeCombo->addItem(tr("12ʱ59��59��"));
    timeCombo->addItem(tr("12:59:59"));
    timeCombo->addItem(tr("12ʱ59��"));
    timeCombo->addItem(tr("12:59"));
    timeCombo->addItem(tr("12ʱ"));
    timeCombo->addItem(tr("59��"));
    timeCombo->addItem(tr("59��"));
    timeCombo->addItem(tr("���� 8:59"));
    timeCombo->addItem(tr("AM 8:59"));
    timeCombo->addItem(tr("8:59 ����"));
    timeCombo->addItem(tr("8:59 AM"));
 */
void Show_Time(S_Show_Data *pDst_Buf, INT8U Area_No, INT16U X, INT16U Y, S_Time *pTime, INT8U Type, INT8U Font, INT8U Color)
{
    INT16U h,m,s;

    h = pTime->Time[T_HOUR];
    m = pTime->Time[T_MIN];
    s = pTime->Time[T_SEC];

    if(Type EQ 0)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimeStr[Type].str, h, m, s);
    else if(Type EQ 1)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimeStr[Type].str, h, m, s);
    else if(Type EQ 2)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimeStr[Type].str, h, m);
    else if(Type EQ 3)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimeStr[Type].str, h, m);
    else if(Type EQ 4)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimeStr[Type].str, h);
    else if(Type EQ 5)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimeStr[Type].str, m);
    else if(Type EQ 6)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimeStr[Type].str, s);
    else if(Type EQ 7)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimeStr[Type].str, h, m);
    else if(Type EQ 8)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimeStr[Type].str, h, m);
    else if(Type EQ 9)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimeStr[Type].str, h, m);
    else if(Type EQ 10)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, TimeStr[Type].str, h, m);

}

//��ʾ���ڵ��ַ���
void Show_Week(S_Show_Data *pDst_Buf, INT8U Area_No, INT16U X, INT16U Y, S_Time *pTime, INT8U Language, INT8U Font, INT8U Color)
{
    INT8U Week;

    Week = pTime->Time[T_WEEK];
    LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, "%s", WeekStr[Language][Week]);
    /*
    if(Language EQ 0)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, "%s", WeekStr0[Week]);
    else if(Language EQ 1)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, "%s", WeekStr1[Week]);
    else if(Language EQ 2)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, "%s", WeekStr2[Week]);
    else if(Language EQ 3)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, "%s", WeekStr3[Week]);
    else if(Language EQ 4)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, "%s", WeekStr4[Week]);
    else if(Language EQ 5)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, "%s", WeekStr5[Week]);
    else if(Language EQ 6)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, "%s", WeekStr6[Week]);
     */
}

//����ʱ������
void Update_Time_Data(INT8U Area_No)
{
    S_Point Point;
    INT16U X_Len, Y_Len;

    Point.X = File_Para[Area_No].Clock_Para.Text_X;
    Point.Y = File_Para[Area_No].Clock_Para.Text_Y;
    X_Len = File_Para[Area_No].Clock_Para.Text_Width;
    Y_Len = File_Para[Area_No].Clock_Para.Text_Height;

    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point, X_Len, Y_Len, &Show_Data, &Point);
    if(File_Para[Area_No].Time_Para.SmLineFlag) //���б�־
    {
      //Point.Y +=
    }
    if(File_Para[Area_No].Time_Para.DateFlag)
    {
     // Show_Date()
    }
}
