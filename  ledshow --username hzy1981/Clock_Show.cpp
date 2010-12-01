#define CLOCK_SHOW_C
#include "Includes.h"


//��ʾһ������
//pDst_BufĿ����ʾ������
//Area_No Ŀ�����
//pClock_Para ʱ�Ӳ���
void Show_Clock(S_Show_Data *pDst_Buf, INT8U Area_No, S_Time *pTime, S_Clock_Para *pClock_Para)
{
   INT16U Radius;
   INT16U Width,Height;
   S_Point Point;
   INT16S Angle;

   if(Area_No >= MAX_AREA_NUM)
   {
     ASSERT_FAILED();
     return;
   }

   Width = Get_Area_Width(Area_No);
   Height = Get_Area_Height(Area_No);

   Radius = ((Width < Height)? Width:Height) * 95 /100 / 2; //���̵İ뾶

   Get_Area_TopLeft(Area_No, &Point); //��������λ��
   //��������λ��
   Point.X += Width/2;
   Point.Y += Height/2;

   //369��
   for(Angle = 0; Angle < 360; Angle = Angle + 90)
   {
     //�������ĵ�ĽǶ���Angle��������Radius * 0.9, �õ�뾶ΪHour369_Point_Radius,��ɫΪ Hour369_Point_Color
      Fill_Clock_Point(pDst_Buf, Area_No, &Point, Angle, Radius * 9 / 10, \
         pClock_Para->Hour369_Point_Radius, pClock_Para->Hour369_Point_Color);
   }

   //����
   for(Angle = 0; Angle < 360; Angle = Angle + 360/12)
   {
     if(Angle % 90 == 0) //369���Ѿ����ƹ��ˣ�����
       continue;
     //�������ĵ�ĽǶ���Angle��������Radius * 0.9, �õ�뾶ΪHour369_Point_Radius,��ɫΪ Hour369_Point_Color
     Fill_Clock_Point(pDst_Buf, Area_No, &Point, Angle, (INT16S)(Radius * 0.9), \
         pClock_Para->Hour_Point_Radius, pClock_Para->Hour_Point_Color);
   }
   //----------����0-11�����еĵ㶼�Ѿ��������------------
   //ʱ��
   Fill_Clock_Line(pDst_Buf, Area_No, &Point, 90 - 360 * (pTime->Time[T_HOUR] % 12) / 12, Radius * 8 / 10,\
                   pClock_Para->Hour_Line_Width, pClock_Para->Hour_Line_Color);
   //����
   Fill_Clock_Line(pDst_Buf, Area_No, &Point, 90 - 360 * pTime->Time[T_MIN] / 60, Radius * 10 / 10,\
                   pClock_Para->Min_Line_Width, pClock_Para->Min_Line_Color);
   //����
   Fill_Clock_Line(pDst_Buf, Area_No, &Point, 90 - 360 * pTime->Time[T_SEC] / 60, Radius * 12 / 10,\
                   pClock_Para->Sec_Line_Width, pClock_Para->Sec_Line_Color);
}


//���±�������
void Update_Clock_Data(INT8U Area_No)
{
  S_Point Point;
  INT16U X_Len, Y_Len;

  Show_Clock(&Show_Data, Area_No, &Cur_Time, &File_Para[Area_No].Clock_Para);
  //Index = Get_Area_Point_Index(Area_No, 0, 0);
  //Bits_Copy(Show_Data_Bak.Color_Data, sizeof(Show_Data_Bak.Color_Data), Index, ;
  //Copy_Buf_2_Area_Rect();
  Point.X = File_Para[Area_No].Clock_Para.Text_X;
  Point.Y = File_Para[Area_No].Clock_Para.Text_Y;
  X_Len = File_Para[Area_No].Clock_Para.Text_Width;
  Y_Len = File_Para[Area_No].Clock_Para.Text_Height;

  Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point, X_Len, Y_Len, &Show_Data, &Point);
}


