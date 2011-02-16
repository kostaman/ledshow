#define HUMIDITY_SHOW_C
#include "Includes.h"

#if HUMIDITY_SHOW_EN
//#define HUMIDITY_STR_MAX_WIDTH 250

//ʪ��>=0��ʹ�����¸�ʽ�ַ���
const S_Format_Str HumidityStr0[]=
{
    //{"ʪ�� %2d.%d%RH", 12},
    {"ʪ�� %2d^RH", 10},
    //{"ʪ��%2d^RH", 9},
    {"%2d^RH", 5},
};


//��ȡʪ����ʾ�����ؿ��
INT16U Get_HumidityStr_Pix_Width(INT8U Type, INT8U Font)
{
  if(Type < S_NUM(HumidityStr0)) //HumidityStr0��HumidityStr1�Ŀ����һ����
   return HumidityStr0[Type].Len*Get_Font_Width(Font);
  else
    return 0;
}

//��ʾʪ�ȵ���С
INT16U Get_Humidity_Min_Width(INT8U Area_No)
{
    INT16U StrWidth;
    //INT8U Font,Type;
    StrWidth = Get_HumidityStr_Pix_Width(Prog_Status.File_Para[Area_No].Humidity_Para.Humidity_Type, \
                                     Prog_Status.File_Para[Area_No].Humidity_Para.Humidity_Font);


    return Prog_Status.File_Para[Area_No].Humidity_Para.Text_Width + SPACE_WIDTH + StrWidth;

}

//��ʾ��ʱ��Ϣ����С�߶�
INT16U Get_Humidity_Min_Height(INT8U Area_No)
{
    INT16U StrHeight;
    //INT16U Height;

    StrHeight = Get_Font_Height(Prog_Status.File_Para[Area_No].Humidity_Para.Humidity_Font);

    if(Prog_Status.File_Para[Area_No].Humidity_Para.Text_Height > StrHeight)
        return Prog_Status.File_Para[Area_No].Humidity_Para.Text_Height;
    else
        return StrHeight;
}
//��ʾʪ��
//pDst_BufĿ����ʾ����
//Area_No����
//X��YΪ��ʾ����
//HumidityΪʪ�ȣ�С��Ϊ1λ
//
void Show_Humidity(S_Show_Data *pDst_Buf, INT8U Area_No, INT16U X, INT16U Y, INT16U Humidity, INT8U Type, INT8U Font, INT8U Color)
{
    char const *p;
    INT8U d; //iΪ�������֣�dΪС������
    INT8U i;

    if(Type >= S_NUM(HumidityStr0))
      return;
    
    p = HumidityStr0[Type].str;
    d = Humidity % 10;
    i = Humidity / 10;
   
    if(Type EQ 0)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, p, i,d);
    else
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, p, i);
}

//����ʪ������
void Update_Humidity_Data(S_Show_Data *pDst, INT8U Area_No)
{
    S_Point P0;
    INT16U Width,Height;
    INT16U Min_Width;//, Min_Height;
    INT16S Humidity;

    Width = Get_Area_Width(Area_No);
    Height = Get_Area_Height(Area_No);

    Min_Width = Get_Humidity_Min_Width(Area_No);
    //Min_Height = Get_Humidity_Min_Height(Area_No);
 
    if(Width > Min_Width)
      P0.X = (Width - Min_Width) / 2;
    else
      P0.X = 0;
/*
    if(Height > Prog_Status.File_Para[Area_No].Humidity_Para.Text_Height)
      P0.Y = (Height - Prog_Status.File_Para[Area_No].Humidity_Para.Text_Height)/2;
    else
      P0.Y = 0;//(Height - Prog_Status.File_Para[Area_No].Humidity_Para.Text_Height)/2;
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Status.File_Para[Area_No].Humidity_Para.Text_Width, Prog_Status.File_Para[Area_No].Humidity_Para.Text_Height, &Show_Data, &P0);//&Point);
*/

    P0.X = P0.X + Prog_Status.File_Para[Area_No].Humidity_Para.Text_Width;
    if(P0.X > 0)
      P0.X += SPACE_WIDTH;//Get_Font_Width(Prog_Status.File_Para[Area_No].Humidity_Para.);

    if(Height > Get_Font_Height(Prog_Status.File_Para[Area_No].Humidity_Para.Humidity_Font))
      P0.Y = (Height - Get_Font_Height(Prog_Status.File_Para[Area_No].Humidity_Para.Humidity_Font))/2;
    else
      P0.Y = 0;

    Humidity = Get_Cur_Humidity(); //--��ȡ��ǰʪ��
    Show_Humidity(pDst, Area_No, P0.X, P0.Y, Humidity, \
               Prog_Status.File_Para[Area_No].Humidity_Para.Humidity_Type, Prog_Status.File_Para[Area_No].Humidity_Para.Humidity_Font,Prog_Status.File_Para[Area_No].Humidity_Para.Humidity_Color);

      
    //Prog_Status.Area_Status[Area_No].Step = 100; //һ����ʾ��λ��ֱ��100%
}
#endif
