#define TEMP_SHOW_C
#include "Includes.h"

#if TEMP_SHOW_EN
//#define TEMP_STR_MAX_WIDTH 250

//�¶�>=0��ʹ�����¸�ʽ�ַ���
const S_Format_Str TempStr0[]=
{
    {"�¶� %2d.%d��", 11},
    {"�¶� %2d��", 9}, 
    {" %2d.%d��", 7}, 
    {" %2d��",5}

};

//���¶�<0ʱ��ʹ�����¸�ʽ�ַ���
const S_Format_Str TempStr1[]=
{
    {"�¶�-%2d.%d��", 11},
    {"�¶�-%2d��", 9}, 
    {"-%2d.%d��", 7}, 
    {"-%2d��",5}

};

//��ȡ�¶���ʾ�����ؿ��
INT16U Get_TempStr_Pix_Width(INT8U Type, INT8U Font)
{
  if(Type < S_NUM(TempStr0)) //TempStr0��TempStr1�Ŀ����һ����
   return TempStr0[Type].Len*Get_Font_Width(Font);
  else
    return 0;
}

//��ʾ�¶ȵ���С
INT16U Get_Temp_Min_Width(INT8U Area_No)
{
    INT16U StrWidth;
    //INT8U Font,Type;
    StrWidth = Get_TempStr_Pix_Width(Prog_Status.File_Para[Area_No].Temp_Para.Temp_Type, \
                                     Prog_Status.File_Para[Area_No].Temp_Para.Temp_Font);


    if(Prog_Status.File_Para[Area_No].Temp_Para.Text_Width)
      return Prog_Status.File_Para[Area_No].Temp_Para.Text_Width + SPACE_WIDTH + StrWidth;
    else
      return StrWidth;
}

//��ʾ��ʱ��Ϣ����С�߶�
INT16U Get_Temp_Min_Height(INT8U Area_No)
{
    INT16U StrHeight;
    //INT16U Height;

    StrHeight = Get_Font_Height(Prog_Status.File_Para[Area_No].Temp_Para.Temp_Font);

    if(Prog_Status.File_Para[Area_No].Temp_Para.Text_Height > StrHeight)
        return Prog_Status.File_Para[Area_No].Temp_Para.Text_Height;
    else
        return StrHeight;
}
//��ʾ�¶�
//pDst_BufĿ����ʾ����
//Area_No����
//X��YΪ��ʾ����
//TempΪ�¶ȣ�С��Ϊ1λ
//
void Show_Temp(S_Show_Data *pDst_Buf, INT8U Area_No, INT16U X, INT16U Y, INT16S Temp, INT8U Type, INT8U Font, INT8U Color)
{
    char const *p;
    INT8U d; //iΪ�������֣�dΪС������
    INT8U i;
    //INT16U uTemp;
    
    if(Temp >= 0)
    {
      if(Type >= S_NUM(TempStr0))
        return;
     
      p = TempStr0[Type].str;
      d = Temp % 10;
      i = Temp / 10;
    }
    else
    {
      if(Type >= S_NUM(TempStr1))
        return;
      
      p = TempStr1[Type].str;
      d = (0 - Temp)% 10;
      i = (0 - Temp)/ 10;
    }
    
    if(Type EQ 0 || Type EQ 2)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, p, i,d);
    else if(Type EQ 1 || Type EQ 3)
      LED_Print(Font, Color, pDst_Buf, Area_No, X, Y, p, i);
}

//�����¶�����
void Update_Temp_Data(S_Show_Data *pDst, INT8U Area_No)
{
    S_Point P0;
    INT16U Width,Height;
    INT16U Min_Width;//, Min_Height;
    INT16S Temp;

    Width = Get_Area_Width(Area_No);
    Height = Get_Area_Height(Area_No);

    Min_Width = Get_Temp_Min_Width(Area_No);
    //Min_Height = Get_Temp_Min_Height(Area_No);
 
    if(Width > Min_Width)
      P0.X = (Width - Min_Width) / 2;
    else
      P0.X = 0;
/*
    if(Height > Prog_Status.File_Para[Area_No].Temp_Para.Text_Height)
      P0.Y = (Height - Prog_Status.File_Para[Area_No].Temp_Para.Text_Height)/2;
    else
      P0.Y = 0;//(Height - Prog_Status.File_Para[Area_No].Temp_Para.Text_Height)/2;
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Status.File_Para[Area_No].Temp_Para.Text_Width, Prog_Status.File_Para[Area_No].Temp_Para.Text_Height, &Show_Data, &P0);//&Point);
*/

    P0.X = P0.X + Prog_Status.File_Para[Area_No].Temp_Para.Text_Width;
    if(Prog_Status.File_Para[Area_No].Temp_Para.Text_Width)
      P0.X += SPACE_WIDTH;//Get_Font_Width(Prog_Status.File_Para[Area_No].Temp_Para.);

    if(Height > Get_Font_Height(Prog_Status.File_Para[Area_No].Temp_Para.Temp_Font))
      P0.Y = (Height - Get_Font_Height(Prog_Status.File_Para[Area_No].Temp_Para.Temp_Font))/2;
    else
      P0.Y = 0;

    Temp = Get_Cur_Temp(); //--��ȡ��ǰ�¶�
    Show_Temp(pDst, Area_No, P0.X, P0.Y, Temp, \
               Prog_Status.File_Para[Area_No].Temp_Para.Temp_Type, Prog_Status.File_Para[Area_No].Temp_Para.Temp_Font,Prog_Status.File_Para[Area_No].Temp_Para.Temp_Color);

      
    //Prog_Status.Area_Status[Area_No].Step = 100; //һ����ʾ��λ��ֱ��100%
}
#endif
