#include "Includes.h"
#if TXT_SHOW_EN

#define CHK_ASC(X) ((X>0xA0)?0:1)


typedef struct
{
    INT8U Head;
    INT8U Chr[2]; //��ȡ���ַ�
    INT8U Data[64*64 / 8];
    INT8U Tail;
}S_Font_Data;

S_Font_Data Font_Data;

typedef struct
{
  INT8U Head;
  INT16U Index;
  INT8U Data[BLOCK_DATA_LEN];
  INT8U Tail;
}S_Txt_Show_Data;

S_Txt_Show_Data Txt_Show_Data;

void Read_Txt_Show_Chr_Data(INT16U Index, INT8U *pDst, INT16U DstLen)
{
   if(Index EQ Txt_Show_Data.Index)
   {
       mem_cpy(pDst, Txt_Show_Data.Data, sizeof(Txt_Show_Data.Data), pDst, DstLen);
       return;
   }
   else
   {
       Txt_Show_Data.Index = Index;
       if(Read_Storage_Data(Index, Txt_Show_Data.Data, Txt_Show_Data.Data, sizeof(Txt_Show_Data.Data)) == 0)
           memset(Txt_Show_Data.Data, 0, BLOCK_DATA_LEN);

       mem_cpy(pDst, Txt_Show_Data.Data, BLOCK_DATA_LEN, pDst, DstLen);

   }
}

void Clr_Txt_Ram_Show_Data(void)
{
  Txt_Show_Data.Index = 0xFFFF;
  memset(Txt_Show_Data.Data, 0, BLOCK_DATA_LEN);
}

/*
0x0D��asc����13�� ָ���ǡ��س���   \r�ǰѹ�����ڱ�������

0x0A��asc����10�� ָ���ǡ����С�    \n�ǰѹ��������һ�е�ͬһ��

0x0D + 0x0A        �س�����          \r\n�ѹ��������һ������
*/
//��һ���ַ�
//pDstĿ�껺����
//Area_No��ʾ������
//X,Y��ʾλ��
//CharOff��ʾ��ʾĳ���ַ�����ʼλ��ƫ�ƣ���������
//Data��ʾ��Ҫ��ʾ������
//pointFlag��ʾ�Ƿ�ֻ��ȡĳ��,0��ʾ��ȡ����,>0��ʾ��ȡĳ��
INT8U Draw_Txt_Chr(S_Show_Data *pDst, INT8U Area_No, INT16U X, INT16U Y, INT8U Color, INT8U CharOff, INT8U FontSize, INT8U Data[],\
                  INT8U pointFlag, INT16U X0, INT16U Y0)
{
    //ÿ�����֣�ռ�����ֽ�, ȡ����λ��
    INT8U FontWidth,FontHeight,i,j,Re,RD_Flag = 0;
    INT32U offset, len, Width;
#if QT_EN    
	FILE *file;
#endif

    if(pointFlag & RD_TXT_NODATA_FLAG)
        return 1;

    if(CHK_ASC(Data[0]) EQ 0) //����
    {
      FontWidth = GET_HZ_FONT_WIDTH(FontSize);
      FontHeight = GET_HZ_FONT_HEIGHT(FontSize);
      len = GET_HZ_FONT_BYTES(FontSize);
      offset = (94*(Data[0] - 0xa0 -1)+(Data[1] - 0xa0 -1)) * len; //�õ�ƫ��λ��

      //ǰһ����ȡ���ַ��͵�ǰһ������Ҫ��ȡ��
      if(Font_Data.Chr[0] != Data[0] || Font_Data.Chr[1] != Data[1])
      {
        Font_Data.Chr[0] = Data[0];
        Font_Data.Chr[1] = Data[1];
        RD_Flag = 1;
      }
    }
    else //Ӣ��
    {
      FontWidth = GET_ASC_FONT_WIDTH(FontSize);
      FontHeight = GET_ASC_FONT_HEIGHT(FontSize);
      len = GET_ASC_FONT_BYTES(FontSize);
      offset = Data[0] * len;

      if(Font_Data.Chr[0] != Data[0])
      {
        Font_Data.Chr[0] = Data[0];
        //Font_Data.Chr[1] = 0;
        RD_Flag = 1;
      }
    }

    if(pointFlag & RD_TXT_POINT_FLAG)//��ȡĳ������
    {
      if(!(X0 >= X && X0 <X + FontWidth - CharOff &&
         Y0 >= Y && Y0 <Y + FontHeight))
          return 0;
    }

    Width = len * 8 / FontHeight ; //�ֿ�ռ�õĿ�ȣ�����������Ŀ��

    if(RD_Flag)
    {
#if QT_EN
        file = getFontFile(FontSize, (CHK_ASC(Data[0]))?0:1);
        fseek(file, offset, SEEK_SET);
        fread(Font_Data.Data, len , 1, file); //��ȡ���ݳ���
#endif
    }

    //�������嵽��ʾ������
    if(pointFlag & RD_TXT_POINT_FLAG)
    {
        for(i = CharOff; i < FontWidth; i ++)
          for(j = 0; j < FontHeight; j ++)
          {
            if(X + i - CharOff == X0 && Y + j == Y0)
            {
                Re = Get_Rect_Buf_Bit(Font_Data.Data, len, Width, ((i >>3) << 3) + (7 - (i % 8)), j);
                if(Re)
                  Set_Area_Point_Data(pDst, Area_No, X + i - CharOff, Y + j, Color);
                else
                  Set_Area_Point_Data(pDst, Area_No, X + i - CharOff, Y + j, 0);
            }
        }
     }
    else
    {
        for(i = CharOff; i < FontWidth; i ++)
          for(j = 0; j < FontHeight; j ++)
          {
            Re = Get_Rect_Buf_Bit(Font_Data.Data, len, Width, ((i >>3) << 3) + (7 - (i % 8)), j);
            if(Re)
              Set_Area_Point_Data(pDst, Area_No, X + i - CharOff, Y + j, Color);
            else
              Set_Area_Point_Data(pDst, Area_No, X + i - CharOff, Y + j, 0);
          }
    }

    return 1;
}

//����Txt���ֵ�Ļ��
//Data�ַ���
//FontSize,�����С
INT16U Calc_Txt_SNum(INT16U Area_Width, INT16U Area_Height, INT8U Data[], INT16U Data_Len, INT8U FontSize, INT8U Flag)
{
    //INT16U Area_Width, Area_Height;
    INT16U Width = 0, LineNo = 0, ScnNo = 0, i = 0, CharWidth,LineNum;
    INT8U CharOff = 0; //�ַ���ƫ��

    //Area_Width = Get_Area_Width(Area_No);
    //Area_Height = Get_Area_Height(Area_No);

    LineNum = Area_Height / FontSize;

    while(i < Data_Len && Data[i] != 0)
    {
       if(CHK_ASC(Data[i]) EQ 0)//����
         CharWidth = FontSize;
       else//Ӣ��
       {
         CharWidth = 0;

         if(Data[i] EQ '\r')
         {
             Width = 0;
             i++;
             continue;
         }
         else if(Data[i] EQ '\n')
         {
             Width = 0;
             LineNo ++;

             if(LineNo >= LineNum)
             {
                 LineNo = 0;
                 ScnNo++;
             }

             i++;
             continue;
         }
         else
           CharWidth = FontSize / 2;

       }

       //�ж��Ƿ���Ҫ���кͻ���
       if(Width + CharWidth > Area_Width)
       {
           if(LineNum > 1 || Flag > 0) //���л����Զ��Ű��־>0����Ҫ�Զ��Ű�
           {
             CharOff = 0;//Width + CharWidth - Area_Width;
             LineNo ++;
           }
           else //���ж��Ҳ���Ҫ�Զ��Ű�
           {
             CharOff = Width + CharWidth - Area_Width;
             LineNo ++;

             //if(ScnNo EQ SCN_No) //��ǰ�ַ��ڵ�ǰ��Ļ
               //Draw_Txt_Chr(pDst, Area_No, Width, LineNo * FontSize, Color, 0, FontSize, &Data[i]); //��ʾ�ַ�����
           }

           Width = 0;

           if(LineNo >= LineNum)
           {
               LineNo = 0;
               ScnNo++;
           }
       }

       Width += (CharWidth > CharOff)? (CharWidth - CharOff):0;
       CharOff = 0;

       if(CHK_ASC(Data[i]) EQ 0)//����
         i += 2;
       else//Ӣ��
         i ++;

    }

    return ScnNo + 1;

}

//��ȡTxt��ʾ����
//Area_No������
//data��Ҫ��ʾ���ַ���
//dataLen��ʾ����������
//FontSize�����С
//SCN_No��Ļ���
//Flag��ʾ��0��ʾ�Զ������л���1��ʾ���Զ����У������Ƶ���Ҫ��
//pointFlag��ʾ�Ƿ�ֻ��ȡĳ��,0��ʾ��ȡ����,>0��ʾ��ȡĳ��
INT16U Read_Txt_Show_Data(S_Show_Data *pDst, INT8U Area_No, S_Txt_Para *pPara, INT8U Data[], INT16U Data_Len, INT8U SCN_No,\
                          INT8U pointFlag, INT16U X, INT16U Y)
{
  INT8U FontHeight,Color,Flag,Border_Height;
  INT16U Area_Width, Area_Height,LineSpace = 0;
  INT16U Width = 0, LineNo = 0, ScnNo = 0, i = 0, CharWidth,LineNum;
  INT8U CharOff = 0,Re = 0; //�ַ���ƫ��

  Area_Width = Get_Area_Width(Area_No);
  Area_Height = Get_Area_Height(Area_No);

  Border_Height = Get_Area_Border_Height(Area_No);

  //Area_Width = Area_Width - 2*Border_Height;
  //Area_Height = Area_Height - 2*Border_Height;

  //DstLen = GET_TEXT_LEN(Width,Height);//(INT32U)Width * ((Height % 8) EQ 0 ? (Height / 8) : (Height / 8 + 1));
  //DstLen = DstLen * Get_Screen_Color_Num(); //��Ļ֧�ֵ���ɫ��//ÿ�����ֽ���

  //Index += (DstLen * SIndex) / BLOCK_SHOW_DATA_LEN;//��ƫ��
  //Index += Prog_Status.Block_Index.Index[Area_No][File_No]; //��ʼ���

  //Offset = (DstLen * SIndex) % BLOCK_SHOW_DATA_LEN; //�ڸÿ��е�����
  X += Border_Height;
  Y += Border_Height;

  FontHeight = GET_HZ_FONT_HEIGHT(pPara->Font_Size);
  Color = pPara->Color;
  Flag = (Prog_Status.File_Para[Area_No].Pic_Para.In_Mode != 2)?1:0; //����������Ҫ

  LineNum = (Area_Height  - 2*Border_Height) / FontHeight;
  LineSpace = (Area_Height - 2*Border_Height - LineNum * FontHeight) / (LineNum + 1);

  Width = Border_Height;

  while(i < Data_Len && Data[i] != 0)
  {
     if(CHK_ASC(Data[i]) EQ 0)//����
       CharWidth = GET_HZ_FONT_WIDTH(pPara->Font_Size);//FontSize;
     else//Ӣ��
     {
       CharWidth = 0;

       if(Data[i] EQ '\r')
       {
           Width = Border_Height;
           i++;
           continue;
       }
       else if(Data[i] EQ '\n')
       {
           Width = Border_Height;
           LineNo ++;

           if(LineNo >= LineNum)
           {
               LineNo = 0;
               ScnNo++;
           }

           i++;
           continue;
       }
       else
         CharWidth = GET_ASC_FONT_WIDTH(pPara->Font_Size);;

     }

     //�ж��Ƿ���Ҫ���кͻ���
     if(Width + CharWidth > (Area_Width - Border_Height))
     {
         if(LineNum > 1 || Flag > 0) //���л����Զ��Ű��־>0����Ҫ�Զ��Ű�
         {
           CharOff = 0;//Width + CharWidth - Area_Width;
           LineNo ++;
         }
         else //���ж��Ҳ���Ҫ�Զ��Ű�
         {
           CharOff = CharWidth - (Width + CharWidth - (Area_Width  - Border_Height));

           if(ScnNo EQ SCN_No) //��ǰ�ַ��ڵ�ǰ��Ļ
             Re |= Draw_Txt_Chr(pDst, Area_No, Width, Border_Height + LineNo * FontHeight + (LineNo + 1) * LineSpace, Color, 0, pPara->Font_Size, &Data[i], \
                          pointFlag, X, Y); //��ʾ�ַ�����

           LineNo ++;
         }

         Width = Border_Height;

         if(LineNo >= LineNum)
         {
             LineNo = 0;
             ScnNo++;
         }
     }


     if(ScnNo EQ SCN_No) //��ǰ�ַ��ڵ�ǰ��Ļ
     {
       Re |= Draw_Txt_Chr(pDst, Area_No, Width, Border_Height + LineNo * FontHeight + (LineNo + 1) * LineSpace, Color, CharOff, pPara->Font_Size, &Data[i],\
                    pointFlag, X, Y); //��ʾ�ַ�����
     }

     Width += (CharWidth > CharOff)? (CharWidth - CharOff):0;
     CharOff = 0;

     if(CHK_ASC(Data[i]) EQ 0)//����
       i += 2;
     else//Ӣ��
       i ++;

  }

  if((pointFlag & RD_TXT_POINT_FLAG) && Re EQ 0)
  {
    Set_Area_Point_Data(pDst, Area_No, X, Y, 0);
  }
  //������Ļ��
  if(pPara->SNum != ScnNo + 1)
  {
    pPara->SNum = ScnNo + 1;
    SET_SUM((*pPara));
  }

  return ScnNo + 1;
}
#endif

