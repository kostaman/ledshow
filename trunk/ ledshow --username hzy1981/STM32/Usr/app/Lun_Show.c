#define LUN_SHOW_C
#include "Includes.h"
#include "nongli.h"

#if LUN_SHOW_EN

#define TIANGAN_LEN 6
#define NONGLI_LEN  8
#define JIEQI_LEN   10
/*
GetChinaCalendar   (2007,2,8,NLyear);  //NLyear={20,06,12,21}
GetChinaCalendarStr(2007,2,8,str);     //str   ={"����������إһ"}
GetNongli            (2007,2,8,&Nongli);   //Nongli  =4
GetJieQi           (2007,2,8,&JQTiangan); //JQTiangan=4 ��˼Ϊ���µ�4���Ǹ�����
GetJieQiStr        (2007,2,4,str);     //str   ={"����"}
GetJieQiStr        (2007,2,8,str);     //str   ={"����ˮ11��"}
*/
//��ȡ������ʾ����С���,������Ҫ�иÿ�Ȳ�����ʾ������ϵ���������
//Area_NoΪ������
INT16U Get_Lun_Min_Width(INT8U Area_No)
{
    INT16U Width = 0, Width0 = 0;
    INT8U i = 0;

    if(Prog_Status.File_Para[Area_No].Lun_Para.SmLineFlag == SLINE_MODE)//����
    {
        if(Prog_Status.File_Para[Area_No].Lun_Para.Text_Width > 0)
        {
            Width = Prog_Status.File_Para[Area_No].Lun_Para.Text_Width;
            i ++;
        }

        if(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Type > 0)
        {
            Width += TIANGAN_LEN*Get_Font_Width(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font);//Get_TianganStr_Pix_Width(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Type - 1, Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font);
            i++;
        }

        if(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Type > 0)
        {
            Width += NONGLI_LEN*Get_Font_Width(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font);//Get_NongliStr_Type_Max_Pix_Width(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Type - 1, Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font);
            i++;
        }

        if(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Type > 0)
        {
            Width += JIEQI_LEN*Get_Font_Width(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font);//Get_JieqiStr_Pix_Width(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Type - 1, Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font);
            i++;
        }

        if(i>0)
            Width += (i- 1)*Prog_Status.File_Para[Area_No].Lun_Para.LineSpace;
    }
    else
    {

        Width = Prog_Status.File_Para[Area_No].Lun_Para.Text_Width;

        if(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Type > 0)
        {
            Width0 = TIANGAN_LEN*Get_Font_Width(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font);//Get_TianganStr_Pix_Width(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Type - 1, Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font);
            Width = MAX_2(Width, Width0);
        }

        if(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Type > 0)
        {
            Width0 = NONGLI_LEN*Get_Font_Width(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font);//Get_NongliStr_Type_Max_Pix_Width(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Type - 1, Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font);
            Width = MAX_2(Width, Width0);
        }

        if(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Type > 0)
        {
            Width0 = JIEQI_LEN*Get_Font_Width(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font);//Get_JieqiStr_Pix_Width(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Type - 1, Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font);
            Width = MAX_2(Width, Width0);

        }

    }

    return Width;
}



//��ȡ������ʾ����С�߶�,��Ҫ�ø߶Ȳ�����ʾ������ʾ�����еĽ�������
//Area_NoΪ������
INT16U Get_Lun_Min_Height(INT8U Area_No)
{
    INT16U Height,Height0;

    if(Prog_Status.File_Para[Area_No].Lun_Para.SmLineFlag == SLINE_MODE)//����
    {
        Height = Prog_Status.File_Para[Area_No].Lun_Para.Text_Height;

        if(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Type > 0)
        {
            Height0 = Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font);
            Height = MAX_2(Height, Height0);
        }

        if(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Type > 0)
        {
            Height0 = Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font);
            Height = MAX_2(Height, Height0);
        }

        if(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Type > 0)
        {
            Height0 = Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font);
            Height = MAX_2(Height, Height0);
        }
    }
    else
    {
        Height = Prog_Status.File_Para[Area_No].Lun_Para.Text_Height;

        if(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Type > 0)
        {
          if(Height > 0)
            Height += Prog_Status.File_Para[Area_No].Lun_Para.LineSpace;       
          Height += Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font);
        }
        
        if(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Type > 0)
        {
          if(Height > 0)
            Height += Prog_Status.File_Para[Area_No].Lun_Para.LineSpace;          
          Height += Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font);
        }
        
        if(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Type > 0)
        {
          if(Height > 0)
            Height += Prog_Status.File_Para[Area_No].Lun_Para.LineSpace;          
          Height += Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font); 
        }
    }

    return Height;
}

INT16U Get_TianganStr_Width(INT8U Font)
{
  return TIANGAN_LEN*Get_Font_Width(Font);
}

INT16U Get_NongliStr_Width(INT8U Font, char str[])
{
  return strlen(str)*Get_Font_Width(Font);
}

INT16U Get_JieqiStr_Width(INT8U Font)
{
  return JIEQI_LEN*Get_Font_Width(Font);
}

//extern void GetChinaCalendarStr(unsigned int  year,unsigned char month,unsigned char day,char *str);


//���½�������
void Update_Lun_Data(S_Show_Data *pDst, INT8U Area_No)
{
  INT16U X, Y;
  S_Point P0;
  INT16U Width,Height;
  INT16U Min_Width, Min_Height;
  char Tiangan[20];
  char Nongli[20];
  char Jieqi[20];

  memset(Tiangan, 0, sizeof(Tiangan));
  memset(Nongli, 0, sizeof(Nongli));
  memset(Jieqi, 0, sizeof(Jieqi));

  //������ɺ�ũ��
  GetChinaCalendarStr(Cur_Time.Time[T_YEAR] + 2000, Cur_Time.Time[T_MONTH], Cur_Time.Time[T_DATE],\
                      Tiangan);

  memcpy(Nongli, Tiangan + TIANGAN_LEN, NONGLI_LEN);
  Tiangan[TIANGAN_LEN] = '\0';

  //�������
  GetJieQiStr(Cur_Time.Time[T_YEAR] + 2000, Cur_Time.Time[T_MONTH], Cur_Time.Time[T_DATE],\
              Jieqi);

  Width = Get_Area_Width(Area_No);
  Height = Get_Area_Height(Area_No);

  Min_Width = Get_Lun_Min_Width(Area_No); //��ʾũ������С���
  Min_Height = Get_Lun_Min_Height(Area_No); //����ũ������С�߶�

  if(Prog_Status.File_Para[Area_No].Lun_Para.SmLineFlag == SLINE_MODE)//����
  {
    if(Width > Min_Width)
    {
      P0.X = (Width - Min_Width) / 2;
    }
    else
    {
      P0.X = 0;
    }
/*
    if(Height > Prog_Status.File_Para[Area_No].Lun_Para.Text_Height)
      P0.Y = (Height - Prog_Status.File_Para[Area_No].Lun_Para.Text_Height)/2;
    else
      P0.Y = 0;//(Height - Prog_Status.File_Para[Area_No].Lun_Para.Text_Height)/2;
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Status.File_Para[Area_No].Lun_Para.Text_Width, Prog_Status.File_Para[Area_No].Lun_Para.Text_Height, &Show_Data, &P0);//&Point);
*/
    X = P0.X + Prog_Status.File_Para[Area_No].Lun_Para.Text_Width;

    if(X > P0.X)
      X += Prog_Status.File_Para[Area_No].Lun_Para.LineSpace;//Get_Font_Width(Prog_Status.File_Para[Area_No].Lun_Para.);
    else
      X = P0.X;


    if(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Type > 0)//��Ҫ��ʾ���?
    {
        P0.X = X;
        if(Height > Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font))
          P0.Y = (Height - Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font))/2;
        else
          P0.Y = 0;

        //Show_Tiangan(&Show_Data, Area_No, P0.X, P0.Y, &Cur_Time,
                     //Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font, Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Color);

        LED_Print(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font, Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Color,\
                  pDst, Area_No, P0.X, P0.Y,\
                  "%s", Tiangan);
        X +=  Prog_Status.File_Para[Area_No].Lun_Para.LineSpace + Get_TianganStr_Width(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font);
    }

    if(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Type > 0)//��Ҫũ��?
    {
        P0.X = X;
        if(Height > Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font))
          P0.Y = (Height - Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font))/2;
        else
          P0.Y = 0;

        //Show_Nongli(&Show_Data, Area_No, P0.X, P0.Y, &Cur_Time,
                    //Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font, Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Color);
        LED_Print(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font, Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Color,\
                  pDst, Area_No, P0.X, P0.Y,\
                  "%s", Nongli);
        //��ʾũ��ҪԤ����󳤶�
        X += Prog_Status.File_Para[Area_No].Lun_Para.LineSpace + NONGLI_LEN * Get_Font_Width(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font);//Get_NongliStr_Width(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font, Nongli);
    }

    if(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Type > 0)//��Ҫ����?
    {
        P0.X = X;
        if(Height > Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font))
          P0.Y = (Height - Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font))/2;
        else
          P0.Y = 0;

        //Show_Jieqi(&Show_Data, Area_No, P0.X, P0.Y, &Cur_Time,
                   //Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font, Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Color);
        LED_Print(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font, Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Color,\
                  pDst, Area_No, P0.X, P0.Y,\
                  "%s", Jieqi);
        X += Prog_Status.File_Para[Area_No].Lun_Para.LineSpace + Get_JieqiStr_Width(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font);
    }
  }
  else //����
  {
      if(Height > Min_Height)
      {
        P0.Y = (Height - Min_Height) / 2;
      }
      else
      {
        P0.Y = 0;
      }
/*
      if(Width > Prog_Status.File_Para[Area_No].Lun_Para.Text_Width)
        P0.X = (Width - Prog_Status.File_Para[Area_No].Lun_Para.Text_Width)/2;
      else
        P0.X = 0;//(Height - Prog_Status.File_Para[Area_No].Lun_Para.Text_Height)/2;
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Status.File_Para[Area_No].Lun_Para.Text_Width, Prog_Status.File_Para[Area_No].Lun_Para.Text_Height, &Show_Data, &P0);//&Point);
*/
      Y = P0.Y + Prog_Status.File_Para[Area_No].Lun_Para.Text_Height;
      if(Prog_Status.File_Para[Area_No].Lun_Para.Text_Height > 0)
        Y += Prog_Status.File_Para[Area_No].Lun_Para.LineSpace;

      if(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Type > 0)//��Ҫ��ʾ���?
      {
          P0.Y = Y;
          if(Width > Get_TianganStr_Width(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font))
            P0.X = (Width - Get_TianganStr_Width(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font))/2;
          else
            P0.X = 0;

          //Show_Tiangan(&Show_Data, Area_No, P0.X, P0.Y, &Cur_Time,
                      //Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font, Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Color);
          LED_Print(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font, Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Color,\
                    pDst, Area_No, P0.X, P0.Y,\
                    "%s", Tiangan);
          Y += Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font);//Get_TianganStr_Pix_Width(Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Type - 1, Prog_Status.File_Para[Area_No].Lun_Para.Tiangan_Font);
          Y += Prog_Status.File_Para[Area_No].Lun_Para.LineSpace;
      }

      if(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Type > 0)//��Ҫũ��?
      {
          P0.Y = Y;
          if(Width > Get_NongliStr_Width(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font, Nongli))
            P0.X = (Width - Get_NongliStr_Width(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font, Nongli))/2;
          else
            P0.X = 0;

          //Show_Nongli(&Show_Data, Area_No, P0.X, P0.Y, &Cur_Time,
                      //Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font, Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Color);
          LED_Print(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font, Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Color,\
                    pDst, Area_No, P0.X, P0.Y,\
                    "%s", Nongli);
          Y += Get_Font_Height(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font);//Prog_Status.File_Para[Area_No].Lun_Para.LineSpace + Get_NongliStr_Type_Max_Pix_Width(Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Type - 1, Prog_Status.File_Para[Area_No].Lun_Para.Nongli_Font);
          Y += Prog_Status.File_Para[Area_No].Lun_Para.LineSpace;
      }

      if(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Type > 0)//��Ҫ����?
      {
          P0.Y = Y;
          if(Width > Get_JieqiStr_Width(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font))
            P0.X = (Width - Get_JieqiStr_Width(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font))/2;
          else
            P0.X = 0;

          //Show_Jieqi(&Show_Data, Area_No, P0.X, P0.Y, &Cur_Time,
                     //Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font, Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Color);
          LED_Print(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font, Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Color,\
                    pDst, Area_No, P0.X, P0.Y,\
                    "%s", Jieqi);
          //X += Prog_Status.File_Para[Area_No].Lun_Para.LineSpace + Get_JieqiStr_Pix_Width(Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Type - 1, Prog_Status.File_Para[Area_No].Lun_Para.Jieqi_Font);
      }
  }
  

  //Prog_Status.Area_Status[Area_No].Step = 100; //һ����ʾ��λ��ֱ��100%
}
#endif
