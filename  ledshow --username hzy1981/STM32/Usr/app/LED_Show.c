#define LED_SHOW_C
#include "Includes.h"

//����*100����λ�ķ�ʽ�ٶȸ��죿δ����
#define GET_LINE_Y(X0,Y0,X1,Y1,X) ((X1 != X0)?((((100*((Y1)-(Y0))*((X)-(X0)))/((X1)-(X0)) + 100*(Y0)) + 50) / 100):((Y0) + 0.5))
#define GET_LINE_X(X0,Y0,X1,Y1,Y) ((Y1 != Y0)?((((100*((X1)-(X0))*((Y)-(Y0)))/((Y1)-(Y0)) + 100*(X0)) + 50) / 100):((X0) + 0.5))

#define STRETCH_RATIO 2//�������
//#define TENSILE_STEP 10//Tensile
//#define COMPRESSION_RATIO
#define REV_FLAG 0x01
#define SCAN_DIS_FLAG 0x02

#define REEL_WIDTH 4

extern void LED_Scan_Screen(void);
extern void Clr_Cur_Scan_Row(void);
//��ȡ�������е�Indexλ��ֵ
INT8U Get_Buf_Bit(INT8U Buf[], INT32U Buf_Size, INT32U Index)
{

#if DATA_CHK_EN
  if(Index >= (INT32U)Buf_Size * 8)
  {
    ASSERT_FAILED();
    return 0;
 }
#endif

  return (Buf[Index >>3] & (0x01 << (Index & 0x07)))>0?1:0;
}


//���û������е�Indexλ��ֵ
void Set_Buf_Bit(INT8U Buf[], INT32U Buf_Size, INT32U Index, INT8U Value)
{

#if DATA_CHK_EN
  if(Index >= Buf_Size * 8)
  {
    ASSERT_FAILED();
    return;
  }
#endif 
 
  if(Value EQ 0)
    Buf[Index >>3] = (Buf[Index >>3] & (~(0x01 << (Index & 0x07))));
  else
    Buf[Index >>3] = (Buf[Index >>3] | (0x01 << (Index & 0x07)));
}

//��ȡһ���������ݻ�������ĳ������ֵ 
//Buf_SizeΪ����������,WidthΪ����������
//X\YΪ�����е������
INT8U Get_Rect_Buf_Bit(INT8U Buf[], INT16U Buf_Size, INT16U Width, INT16U X, INT16U Y)
{
  INT16U Index;
  
  //Index = ((Y/8 * Width) + X)*8 + Y %8;
  Index = GET_POINT_INDEX(Width,X,Y);
  return Get_Buf_Bit(Buf, Buf_Size, Index);//Index;
  
}

//����һ���������ݻ�������ĳ������ֵ 
//Buf_SizeΪ����������,WidthΪ����������
//X\YΪ�����е������
//ValueΪ�õ�ֵ
void Set_Rect_Buf_Bit(INT8U Buf[], INT16U Buf_Size, INT16U Width, INT16U X, INT16U Y, INT8U Value)
{
  INT16U Index;
  
  //Index = ((Y/8 * Width) + X)*8 + Y %8;
  Index = GET_POINT_INDEX(Width,X,Y);
  Set_Buf_Bit(Buf, Buf_Size, Index, Value);//Index;  
}

/*
//Buf��������ӳ��
INT32U Buf_2_Area_Bit_Index_Map(INT32U Buf_Bit, INT8U Area_No, INT16U X, INT16U Y, INT16U X_Len, INT16U Y_Len)
{
  INT32U Index;
  INT32U X0, Y0;

  X0 = Buf_Bit % X_Len;
  Y0 = Buf_Bit / X_Len;

  Get_Area_Point_Index(Area_No, X + X0, Y + Y0);
}
*/

//����һ��Buf�������е�һ��Rect��
//pSrc��Դ������
//Src_Size��ʾԴ����������󳤶�
//pDst��ʾĿ����ʾ������
//Area_No��ʾĿ�����
//X,Y,X_Len,Y_LenĿ�껺���е�һ��Rect
void Copy_Buf_2_Area_Rect(INT8U *pSrc, INT16U Src_Size, S_Show_Data *pDst, INT8U Area_No, INT16U X, INT16U Y, INT16U X_Len, INT16U Y_Len)
{
  INT32U i,j;
  INT8U Re;

  for(i = 0; i <X_Len; i ++)
    for(j = 0; j <Y_Len; j ++)
    {
      Re = Get_Rect_Buf_Bit(pSrc, Src_Size, X_Len, i, j);
      Set_Area_Point_Data(pDst, Area_No, X + i, Y + j, Re);
    }
}

//���ڷֶο��������������ݵ���ʾ������
//pSrc��ʾԴ���ݻ���
//Src_LenԴ���峤��
//Src_Off��ʾ��ǰ���Ƶ��������������������е���ʼƫ��
//pDstĿ����ʾ������
//Area_NoĿ�������
//X,Y,X_Len,Y_Len��ʾĿ������е�һ�����Σ�����pSrc��ʾ���ݵ����������
void Copy_Buf_2_Area_Rect_0(INT8U *pSrc, INT16U Src_Len, INT16U Src_Off, \
                            S_Show_Data *pDst, INT8U Area_No, INT16U X, INT16U Y, INT16U X_Len, INT16U Y_Len)
{
  INT32U i;//j,Index;
  INT16U X0,Y0;
  INT8U Re;
  INT16U Row_Points;

  Row_Points = ((X_Len % 8) EQ 0)?X_Len:((X_Len / 8 + 1)*8);
  
  if(Row_Points EQ 0)
    return;
  
  for(i = 0; i <Src_Len *8; i ++)
  {
    Re = Get_Buf_Bit(pSrc, Src_Len, i);

    X0 = (Src_Off*8 + i) % Row_Points;
    Y0 = (Src_Off*8 + i) / Row_Points;

    if(X0 < X_Len && Y0 < Y_Len) //X0,Y0������X_Len��Y_Len�ķ�Χ��
      Set_Area_Point_Data(pDst, Area_No, X+X0, Y+Y0, Re);
  }
}
//����һ�������еľ������ݵ�Ŀ�껺������
//pDstĿ�껺����
//Dst_SizeĿ�껺�����Ĵ�С
//pSrcԴ��ʾ��
//Դ����
//X,Y,X_Len,Y_Len��ʾԴ�����еľ���
void Copy_Area_Rect_2_Buf(INT8U *pDst, INT16U Dst_Size, S_Show_Data *pSrc, INT8U Area_No, INT16U X, INT16U Y, INT16U X_Len, INT16U Y_Len)
{
  INT32U i,j;
  INT8U Re;


  for(i = 0; i <X_Len; i ++)
    for(j = 0; j <Y_Len; j ++)
    {
      Re = Get_Area_Point_Data(pSrc, Area_No, X + i, Y + j);
      Set_Rect_Buf_Bit(pDst, Dst_Size, X_Len, i, j, Re);
    }
}

//��ȡĳ�������Ŀ��
//Area_No������
INT16U Get_Area_Width(INT8U Area_No)
{
  if(Area_No < MAX_AREA_NUM)
    return Prog_Para.Area[Area_No].X_Len;
  else if(Area_No EQ MAX_AREA_NUM)
    return Screen_Para.Base_Para.Width;
  else
  {
    ASSERT_FAILED();
    return 0; 
  } 
}

//��ȡĳ�������ĸ߶�
//Area_No������
INT16U Get_Area_Height(INT8U Area_No)
{
  if(Area_No < MAX_AREA_NUM)
    return Prog_Para.Area[Area_No].Y_Len;
  else if(Area_No EQ MAX_AREA_NUM)
    return Screen_Para.Base_Para.Height;
  else
  {
    ASSERT_FAILED();
    return 0; 
  }  
}

//��ȡһ�����������ظ���,Area_No��ʾ������
INT32U Get_Area_Size(INT8U Area_No)
{
  if(Area_No >= MAX_AREA_NUM)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  return (INT32U)Prog_Para.Area[Area_No].X_Len * Prog_Para.Area[Area_No].Y_Len;  
}

//��ȡ���������ϵ�λ��
INT8U Get_Area_TopLeft(INT8U Area_No, S_Point *pPoint)
{
  if(Area_No >= MAX_AREA_NUM)
  {
    ASSERT_FAILED();
    pPoint -> X = 0;
    pPoint -> Y = 0;
    return 0;
  }
  
  pPoint->X = Prog_Para.Area[Area_No].X;
  pPoint->Y = Prog_Para.Area[Area_No].Y;
  
  return 1;
}

//INT16U TempX, TempY;
INT32U Get_Area_Point_Index0(INT8U Area_No, INT16U X, INT16U Y)
{
  INT32U Index;
  //INT8U Rows_Fold;
  //INT16U X0,Y0,Bit;
#if QT_EN
  Index = Get_Area_Point_Index(Area_No, X, Y);
  return Index;
#else
  
  if(Area_No < MAX_AREA_NUM)
  {
    X += Prog_Para.Area[Area_No].X;
    Y += Prog_Para.Area[Area_No].Y;
  }

  Index = Screen_Para.Base_Para.Width*Y + X;//GET_POINT_INDEX(Screen_Para.Base_Para.Width,X,Y);
  
  return Index;
#endif
}
//��ȡ������ĳ�������
//Area_No��ʾ������
//x,y��ʾ�ڷ����ڵ�����
INT32U Get_Area_Point_Index(INT8U Area_No, INT16U X, INT16U Y)
{
  INT32U Index;

  
  if(Area_No < MAX_AREA_NUM)
  {


    X += Prog_Para.Area[Area_No].X;
    Y += Prog_Para.Area[Area_No].Y;
/*
#if DATA_CHK_EN   
    if(X >= Screen_Para.Base_Para.Width ||\
       Y >= Screen_Para.Base_Para.Height)
    {
      ASSERT_FAILED();
      return 0;
    }
#endif 
*/ 
    //Index = (((Y>>3) * Screen_Para.Base_Para.Width) + X)*8 + (Y & 0x07);

  }

#if QT_EN
    Index = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X,Y);
#else
    Index = Screen_Para.Base_Para.Width*Y + X;//GET_POINT_INDEX(Screen_Para.Base_Para.Width,X,Y);
#endif
    return Index;
}

//λ����
//pSrcԴ������
//Src_LenԴ����������
//Src_Indexλ��������ʼλ��
//Bits������λ��
//pDstĿ�껺����
//Dst_IndexĿ�����ʼλ
//Dst_LenĿ�껺�����ĳ���
/*
void Bits_Copy(INT8U *pSrc, INT16U Src_Len, INT32U Src_Index, INT32U Bits, \
               INT8U *pDst, INT16U Dst_Len, INT32U Dst_Index)
{
  INT32U i;
  INT8U Re;
  
  for(i = 0 ; i < Bits; i ++)
  {
    Re = Get_Buf_Bit(pSrc, Src_Len, Src_Index + i);
    Set_Buf_Bit(pDst, Dst_Len, Dst_Index + i, Re);
  }
  
}*/

//λ����
//pSrcԴ������
//Src_LenԴ����������
//Src_Indexλ��������ʼλ��
//Bits������λ��
//pDstĿ�껺����
//Dst_IndexĿ�����ʼλ
//Dst_LenĿ�껺�����ĳ���
/*
void Copy_Bits_2_Area(INT8U *pSrc, INT16U Src_Len, INT16U Width, INT32U Bits, \
               S_Show_Data *pDst, INT8U Area_No, INT16U X, INT16U Y, INT16U X_Len, INT16U Y_Len, INT16U Dst_Index)
{
  INT32U i;
  INT8U Re;
  
  for(i = 0 ; i < Bits; i ++)
  {
    Re = Get_Rect_Buf_Bit(pSrc, Src_Len, Width, X, Y);
    Set_Area_Point_Data(pDst, Area_No, Dst_Len, Dst_Index + i, Re);
  }
  
}
*/

INT8U Get_Buf_Point_Data(INT8U Buf[], INT16U Buf_Len, INT8U Color, INT16U Width, INT16U X, INT16U Y)
{
  INT32U Index;

  //Index = (((Y>>3) * Width) + X)*8 + (Y & 0x07);
 Index = GET_POINT_INDEX(Width,X,Y);
 
 if(Color < 3 || Color EQ 4)  //0,1,2,4��ɫ��
    return Get_Buf_Bit(Buf, Buf_Len,Index);
  else if(Color EQ 3 || Color EQ 5 || Color EQ 6) //˫ɫ��
    return Get_Buf_Bit(Buf, Buf_Len, ((Index>>3)<<4) + (Index & 0x07)) +\
      (Get_Buf_Bit(Buf, Buf_Len, ((Index>>3)<<4) + 8 + (Index & 0x07))<<1);
  else if(Color EQ 7) //��ɫ��
    return Get_Buf_Bit(Buf, Buf_Len, (Index>>3)*24 + (Index & 0x07)) +\
      (Get_Buf_Bit(Buf, Buf_Len, (Index>>3)*24 + 8 + (Index & 0x07))<<1)+
      (Get_Buf_Bit(Buf, Buf_Len, (Index>>3)*24 + 16 + (Index & 0x07))<<2);
  else
    return 0;  

}

//INT8U Get_Area_Point_Data(S_Show_Data *pSrc_Buf, INT8U Area_No, INT16U X, INT16U Y) //��ȡһ��������һ���������
//��ǰ��Ŀ��ĳ������,��0λ����2λ�ֱ�Ϊ������ɫ
//pSrc_Buf����ʾ����buf
//Area_No��������
//x,y��������
INT8U Get_Area_Point_Data(S_Show_Data *pSrc_Buf, INT8U Area_No, INT16U X, INT16U Y) //��ȡһ��������һ���������
{
  INT32U Index;
  INT32U Temp;
  INT8U Value;


  Index = Get_Area_Point_Index(Area_No, X, Y);

  if(Screen_Status.Color_Num <2)//Screen_Para.Base_Para.Color < 3 || Screen_Para.Base_Para.Color EQ 4)  //0,1,2,4��ɫ��
    Value = Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data),Index);
  else if(Screen_Status.Color_Num EQ 2)//Screen_Para.Base_Para.Color EQ 3 || Screen_Para.Base_Para.Color EQ 5 || Screen_Para.Base_Para.Color EQ 6) //˫ɫ��
  {
    Temp = ((Index>>3)<<4);
    Value = Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), Temp + (Index & 0x07)) +\
      (Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), Temp + 8 + (Index & 0x07))<<1);
  }
  else if(Screen_Status.Color_Num EQ 3)// //��ɫ��
  {
     Temp = (Index>>3)*24;
     Value = Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), Temp + (Index & 0x07)) +\
      (Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), Temp + 8 + (Index & 0x07))<<1)+
      (Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), Temp + 16 + (Index & 0x07))<<2);
  } 
  else
    Value = 0;

#if QT_EN EQ 0
        //if(pSrc_Buf EQ &Show_Data && Screen_Para.Scan_Para.Data_Polarity EQ 0) //���ݼ��Ե��ж�
      //Value = ~Value;
#endif
    return Value;
}
/*
INT8U Get_Area_Offset_Len(S_Show_Data *pBuf, INT8U Area_No, INT8U **pOff, INT16U *pLen)
{
  INT32U Index;
  
  Index = Get_Area_Point_Index(Area_No, X, Y);
 
  if(Screen_Para.Base_Para.Color < 3 || Screen_Para.Base_Para.Color EQ 4)  //��ɫ��
    return Get_Buf_Bit(pSrc_Buf->One_Color_Data.Color0, sizeof(pSrc_Buf->One_Color_Data.Color0),Index);
  else if(Screen_Para.Base_Para.Color EQ 3 || Screen_Para.Base_Para.Color EQ 5 || Screen_Para.Base_Para.Color EQ 6) //˫ɫ��
    return Get_Buf_Bit(pSrc_Buf->Two_Color_Data.Color0, sizeof(pSrc_Buf->Two_Color_Data.Color0), Index) +\
      (Get_Buf_Bit(pSrc_Buf->Two_Color_Data.Color1, sizeof(pSrc_Buf->Two_Color_Data.Color1), Index) << 1);
  else if(Screen_Para.Base_Para.Color EQ 7) //��ɫ��
    return Get_Buf_Bit(pSrc_Buf->Three_Color_Data.Color0, sizeof(pSrc_Buf->Two_Color_Data.Color0), Index) + \
      (Get_Buf_Bit(pSrc_Buf->Three_Color_Data.Color1, sizeof(pSrc_Buf->Three_Color_Data.Color1), Index) << 1) +\
        (Get_Buf_Bit(pSrc_Buf->Three_Color_Data.Color2, sizeof(pSrc_Buf->Three_Color_Data.Color2), Index) << 2);
  else
    return 0;  
  
}
*/

void Set_Buf_Point_Data(INT8U Buf[], INT16U Buf_Len, INT8U Color, INT8U Width, INT16U X, INT16U Y, INT8U Value)
{
  INT32U Index;
  
  //Index = (((Y>>3) * Width) + X)*8 + (Y & 0x07);
  Index = GET_POINT_INDEX(Width,X,Y);
  
  if(Color < 3 || Color EQ 4)  //��ɫ��
    Set_Buf_Bit(Buf, Buf_Len,Index, (Value & 0x01));
  else if(Color EQ 3 || Color EQ 5 || Color EQ 6) //˫ɫ��
  {
    Index = ((Index>>3)<<4) + (Index & 0x07);
    Set_Buf_Bit(Buf, Buf_Len, Index, (Value & 0x01));
    Set_Buf_Bit(Buf, Buf_Len, Index + 8, (Value & 0x02)>>1);
  }
  else if(Color EQ 7) //��ɫ��
  {
    Index = (Index>>3)*24 + (Index & 0x07);
    Set_Buf_Bit(Buf, Buf_Len, Index, (Value & 0x01));
    Set_Buf_Bit(Buf, Buf_Len, Index + 8, (Value & 0x02)>>1);
    Set_Buf_Bit(Buf, Buf_Len, Index + 16, (Value & 0x04)>>2);
  }
}


//����ĳ��Ŀ������ĳ�������,��0-2λ�ֱ��ʾ������ɫ
//pDst_Buf�����ø���ʾ�����еĵ�
//Area_No��ʾ������
//x,y����λ��
//Value��
void Set_Area_Point_Data(S_Show_Data *pDst_Buf, INT8U Area_No, INT16U X, INT16U Y, INT8U Value) //����һ������ĵ�   
{
  INT32U Index;

  if(Area_No < MAX_AREA_NUM)
  {
    if(X >= Prog_Para.Area[Area_No].X_Len ||\
       Y >= Prog_Para.Area[Area_No].Y_Len)
    {
      //ASSERT_FAILED();
      return;
    }
  }
  else
  {
    if(X >= Screen_Para.Base_Para.Width ||\
       Y >= Screen_Para.Base_Para.Height)
      {
        ASSERT_FAILED();
        return;
    }
  }

  Index = Get_Area_Point_Index(Area_No, X, Y);

  if(Screen_Status.Color_Num <2)//Screen_Para.Base_Para.Color < 3 || Screen_Para.Base_Para.Color EQ 4)  //0,1,2,4��ɫ��
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data),Index, (Value & 0x01));
  else if(Screen_Status.Color_Num EQ 2)//Screen_Para.Base_Para.Color EQ 3 || Screen_Para.Base_Para.Color EQ 5 || Screen_Para.Base_Para.Color EQ 6) //˫ɫ��
  {
    Index = ((Index>>3)<<4) + (Index & 0x07);
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), Index , (Value & 0x01));
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), Index + 8, (Value & 0x02)>>1);
  }
  else if(Screen_Status.Color_Num EQ 3)//Screen_Para.Base_Para.Color EQ 7) //��ɫ��
  {
    Index = (Index>>3)*24 + (Index & 0x07);
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), Index , (Value & 0x01));
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), Index + 8, (Value & 0x02)>>1);
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), Index + 16, (Value & 0x04)>>2);
  }
 
} 
/*
//����һ����������
//pSrc_Buf ԭ��ʾ���ݻ�����
//Area_No������
//pSrc_Point Դ���е����ϵ�λ��
//X_Len���,Y_Len�߶�
//pDst_Buf Ŀ����ʾ����
//pDst_Point Ŀ����ε����ϵ�λ��
void Copy_Filled_Rect_Data(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pSrc_Point, INT16U X_Len, INT16U Y_Len,\
  S_Show_Data *pDst_Buf, S_Point *pDst_Point) //����һ����������
{
  
}
*/
S_Point * Get_Left_Point(S_Point *pPoint0, S_Point *pPoint1)
{
  if(pPoint0->X < pPoint1->X) //point0�������
  {
    return pPoint0;
  }
  else if(pPoint0->X > pPoint1->X)
  {
    return pPoint1;
  }  
  else
  {
    if(pPoint0->Y < pPoint1->Y)
        return pPoint0;
    else if(pPoint0 ->Y > pPoint1->Y)
        return pPoint1;
    else
        return pPoint0;
  }
}

//��ȡ������֮�е��ұ�һ���㣬X����ϴ��һ��
S_Point * Get_Right_Point(S_Point *pPoint0, S_Point *pPoint1)
{
  if(pPoint0->X > pPoint1->X) //point0�������
  {
    return pPoint0;
  }
  else if(pPoint0->X < pPoint1->X)
  {
    return pPoint1;
  }
  else
  {
    if(pPoint0->Y > pPoint1->Y)
        return pPoint0;
    else if(pPoint0 ->Y < pPoint1->Y)
        return pPoint1;
    else
        return pPoint0;
  }
}

S_Point * Get_Up_Point(S_Point *pPoint0, S_Point *pPoint1)
{
  if(pPoint0->Y < pPoint1->Y) //point0�����ϱ�
  {
    return pPoint0;
  }
  else if(pPoint0->Y > pPoint1->Y)
  {
    return pPoint1;
  }
  else
  {
      if(pPoint0->X < pPoint1->X)
          return pPoint0;
      else if(pPoint0->X > pPoint1->X)
          return pPoint1;
      else
          return pPoint0;
  }
}

//��ȡ������֮�е��±�һ���㣬Y����ϴ��һ��
S_Point * Get_Down_Point(S_Point *pPoint0, S_Point *pPoint1)
{
  if(pPoint0->Y > pPoint1->Y) //point0�����±�
  {
    return pPoint0;
  }
  else if(pPoint0->Y < pPoint1->Y)
  {
    return pPoint1;
  }
  else
  {
      if(pPoint0->X > pPoint1->X)
          return pPoint0;
      else if(pPoint0->X < pPoint1->X)
          return pPoint1;
      else
          return pPoint0;
  }
}

S_Point * Get_X_Mid_Point(S_Point *pPoint0, S_Point *pPoint1, S_Point *pPoint2)
{
  S_Point *pLeft, *pRight, *pMid;

  pLeft = Get_Left_Point(pPoint0, pPoint1);
  pLeft = Get_Left_Point(pLeft, pPoint2);

  pRight = Get_Right_Point(pPoint0, pPoint1);
  pRight = Get_Right_Point(pRight, pPoint2);

  if(pPoint0 != pLeft && pPoint0 != pRight)
      pMid = pPoint0;
  else if(pPoint1 != pLeft && pPoint1 != pRight)
      pMid = pPoint1;
  else
      pMid = pPoint2;

  return pMid;
}

S_Point * Get_Y_Mid_Point(S_Point *pPoint0, S_Point *pPoint1, S_Point *pPoint2)
{
    S_Point *pUp, *pDown, *pMid;

    pUp = Get_Up_Point(pPoint0, pPoint1);
    pUp = Get_Up_Point(pUp, pPoint2);

    pDown = Get_Down_Point(pPoint0, pPoint1);
    pDown = Get_Down_Point(pDown, pPoint2);

    if(pPoint0 != pUp && pPoint0 != pDown)
        pMid = pPoint0;
    else if(pPoint1 != pUp && pPoint1 != pDown)
        pMid = pPoint1;
    else
        pMid = pPoint2;

    return pMid;
}
//����һ����
//pSrc_Buf,Դ��ʾ����
//Area_No,������
//pPoint0, Դ�ߵ����
//pPoint1, Դ�ߵ��յ�
//pDst_Buf, Ŀ����ʾ����
//pPoint2, Ŀ���ߵ���ʼλ��
void Copy_Line(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1, \
  S_Show_Data *pDst_Buf, S_Point *pPoint2)  //����һ����
{/*
  INT8U Data;
  S_Point *p0, *p1;
  INT32S i,j;
  
  p0 = Get_Left_Point(pPoint0, pPoint1);
  p1 = Get_Right_Point(pPoint0, pPoint1);
  
  if(p0->X != p1->X) //�����ڴ�ֱ��һ������
  {
      for(i = p0 -> X; i <= p1->X ; i ++)
      {
        j = GET_LINE_Y((INT32S)p0->X,(INT32S)p0->Y, (INT32S)p1->X, (INT32S)p1->Y, i);//(INT32S)pLeft->Y + (INT32S)(i - pLeft ->X)((INT32S)(pRgiht->Y) - (INT32S)(pLeft->Y))/(pRight -> X - pLeft->X) ;

        if(j < 0)
          ASSERT_FAILED();

        Data = Get_Area_Point_Data(pSrc_Buf, Area_No, (INT16U)i, (INT16U)j);
        Set_Area_Point_Data(pDst_Buf, Area_No, (INT16U)(i + pPoint2->X - pPoint0->X), (INT16U)(j + pPoint2->Y - pPoint0->Y), Data);
      }
  }
  else
  {
      p0 = Get_Up_Point(pPoint0, pPoint1);
      p1 = Get_Down_Point(pPoint0, pPoint1);

      for(j = p0->Y; j <=p1->Y; j ++)
      {
        Data = Get_Area_Point_Data(pSrc_Buf, Area_No, p0->X, j);
        Set_Area_Point_Data(pDst_Buf, Area_No, pPoint2->X, j + pPoint2->Y - pPoint0->Y, Data);
      }
  }
  */
    S_Point *p0, *p1;//, *p2;
    S_Point P2;
    INT32S i,j;
    INT16U Y,k;
    INT8U Value;
    INT16S Xdiff,Ydiff;

    p0 = Get_Left_Point(pPoint0, pPoint1);
    p1 = Get_Right_Point(pPoint0, pPoint1);
    //p2 = pPoint2;

    Xdiff = (INT16S)pPoint2->X - (INT16S)pPoint0->X;
    Ydiff = (INT16S)pPoint2->Y - (INT16S)pPoint0->Y;

    Y = p0->Y;
    if(p0->X != p1->X && p0->Y != p1->Y) //��һ��б��
    {
        for(i = p0 -> X; i <= p1->X ; i ++)
        {
          j = (INT32S)GET_LINE_Y((INT32S)p0->X,(INT32S)p0->Y, (INT32S)p1->X, (INT32S)p1->Y, i);//(INT32S)pLeft->Y + (INT32S)(i - pLeft ->X)((INT32S)(pRgiht->Y) - (INT32S)(pLeft->Y))/(pRight -> X - pLeft->X) ;
          if(j < 0)
            ASSERT_FAILED();

          if((INT16U)j > Y + 1)
          {
            for(k = Y + 1; k < j; k ++)
            {
                Value = Get_Area_Point_Data(pSrc_Buf, Area_No, (INT16U)i, (INT16U)k);
                Set_Area_Point_Data(pDst_Buf, Area_No, (INT16U)(i + Xdiff), (INT16U)(k + Ydiff), Value);
            }
          }
          else if(Y > (INT16U)j + 1)
          {
              for(k = (INT16U)j + 1; k < Y; k ++)
              {
                  Value = Get_Area_Point_Data(pSrc_Buf, Area_No, (INT16U)i, (INT16U)k);
                  Set_Area_Point_Data(pDst_Buf, Area_No, (INT16U)(i + Xdiff), (INT16U)(k + Ydiff), Value);
              }
          }
          else
          {
             Value = Get_Area_Point_Data(pSrc_Buf, Area_No, (INT16U)i, (INT16U)j);
             Set_Area_Point_Data(pDst_Buf, Area_No, (INT16U)(i + Xdiff), (INT16U)(j + Ydiff), Value);
          }
          Y = j;
       }
    }
    else if(p0->X EQ p1->X)
    {
        p0 = Get_Up_Point(pPoint0, pPoint1);
        p1 = Get_Down_Point(pPoint0, pPoint1);

        P2.X = (INT16U)(p0->X + Xdiff);
        P2.Y = (INT16U)(p0->Y + Ydiff);
        Copy_Filled_Rect(pSrc_Buf, Area_No, p0, 1, p1->Y + 1 - p0->Y, pDst_Buf, &P2, 0);
    }
    else if(p0->Y EQ p1->Y)
    {
        p0 = Get_Left_Point(pPoint0, pPoint1);
        p1 = Get_Right_Point(pPoint0, pPoint1);

        P2.X = (INT16U)(p0->X + Xdiff);
        P2.Y = (INT16U)(p0->Y + Ydiff);
        Copy_Filled_Rect(pSrc_Buf, Area_No, p0, p1->X + 1 - p0->X, 1, pDst_Buf, &P2, 0);
    }

}

//����һ����
//pDst_Buf, Ŀ�껺��
//Area_No, ������
//pPoint0, ��ʼ��
//pPoint1, �յ�
//Value, ��ɫ
void Draw_Line(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1, INT8U Value)
{
  S_Point *p0, *p1;
  INT32S i,j;
  INT16U Y,k;
  
  p0 = Get_Left_Point(pPoint0, pPoint1);
  p1 = Get_Right_Point(pPoint0, pPoint1);
  
  Y = p0->Y;
  if(p0->X != p1->X && p0->Y != p1->Y)
  {
      for(i = p0 -> X; i <= p1->X ; i ++)
      {
        j = (INT32S)GET_LINE_Y((INT32S)p0->X,(INT32S)p0->Y, (INT32S)p1->X, (INT32S)p1->Y, i);//(INT32S)pLeft->Y + (INT32S)(i - pLeft ->X)((INT32S)(pRgiht->Y) - (INT32S)(pLeft->Y))/(pRight -> X - pLeft->X) ;

        if(j < 0)
          ASSERT_FAILED();
//--------------
        if((INT16U)j > Y + 1)
        {
          for(k = Y + 1; k < j; k ++)
              Set_Area_Point_Data(pDst_Buf, Area_No, (INT16U)i, (INT16U)k, Value);
        }
        else if(Y > (INT16U)j + 1)
        {
            for(k = (INT16U)j + 1; k < Y; k ++)
                Set_Area_Point_Data(pDst_Buf, Area_No, (INT16U)i, (INT16U)k, Value);
        }
        else
          Set_Area_Point_Data(pDst_Buf, Area_No, (INT16U)i, (INT16U)j, Value);

        Y = j;
     }
  }
  else if(p0->X EQ p1->X) //һ������
  {
      p0 = Get_Up_Point(pPoint0, pPoint1);
      p1 = Get_Down_Point(pPoint0, pPoint1);

      Fill_Rect(pDst_Buf, Area_No, p0, 1, p1->Y + 1 - p0->Y, Value);
  }
  else if(p0->Y EQ p1->Y) //һ������
  {
      p0 = Get_Left_Point(pPoint0, pPoint1);
      p1 = Get_Right_Point(pPoint0, pPoint1);

      Fill_Rect(pDst_Buf, Area_No, p0, p1->X + 1 - p0->X, 1, Value);
  }

}

//����һ������������--��ֱ��������
//pSrc_Buf Դ��ʾbuf
//pPoint0, pPoint1, pPoint2 ��ʾԴ���ǵĵ����������
//pDst_Buf Ŀ����ʾbuf
//pPoint3 Ŀ������λ�ã���ӦpPoint0
void Copy_Filled_Triangle(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1,S_Point *pPoint2,\
  S_Show_Data *pDst_Buf, S_Point *pPoint3)  //����һ������������

{
    S_Point *pLeft;  //����ߵĵ�
    S_Point *pRight; //���ұߵĵ�
    S_Point *pMid;  //�м�ĵ�
    S_Point Temp0, Temp1, Temp2;//,Temp0_Bk,Temp1_Bk;


    pLeft = Get_Left_Point(pPoint0, pPoint1);
    pLeft = Get_Left_Point(pLeft, pPoint2);

    pRight = Get_Right_Point(pPoint0, pPoint1);
    pRight = Get_Right_Point(pRight, pPoint2);

    pMid = Get_X_Mid_Point(pPoint0, pPoint1, pPoint2);

    //Draw_Line(pDst_Buf, Area_No, pPoint0, pPoint1, Value);
    //Draw_Line(pDst_Buf, Area_No, pPoint1, pPoint2, Value);
    //Draw_Line(pDst_Buf, Area_No, pPoint2, pPoint0, Value);

    Temp0.X = pLeft -> X;  //�м��X
    //Temp0_Bk.X = pLeft->X;
    //Temp0_Bk.Y = pLeft->Y;

    //Temp1_Bk.X = pLeft->X;
    //Temp1_Bk.Y = pLeft->Y;

    Temp2.X = pLeft->X + pPoint3->X - pPoint0->X;
    Temp2.Y = pLeft->Y + pPoint3->Y - pPoint0->Y;
    Copy_Line(pSrc_Buf, Area_No, pLeft, pRight, pDst_Buf, &Temp2);
/*
    Copy_Line(pSrc_Buf, Area_No, pLeft, pMid, pDst_Buf, &Temp2);
    Temp2.X = pMid->X + pPoint3->X - pPoint0->X;
    Temp2.Y = pMid->Y + pPoint3->Y - pPoint0->Y;
    Copy_Line(pSrc_Buf, Area_No, pRight, pMid, pDst_Buf, &Temp2);
*/
    while(Temp0.X <= pRight -> X)
    {
      Temp0.Y = (INT16U)GET_LINE_Y((INT32S)pLeft ->X, (INT32S)pLeft->Y, (INT32S)pRight->X, (INT32S)pRight->Y, (INT32S)Temp0.X);
      Temp1.X = Temp0.X;
      if(Temp1.X < pMid->X)
        Temp1.Y = (INT16U)GET_LINE_Y((INT32S)pLeft ->X, (INT32S)pLeft->Y, (INT32S)pMid->X, (INT32S)pMid->Y, (INT32S)Temp1.X);
      else
        Temp1.Y = (INT16U)GET_LINE_Y((INT32S)pMid->X, (INT32S)pMid->Y, (INT32S)pRight ->X, (INT32S)pRight->Y,  (INT32S)Temp1.X);


      Temp2.X = Temp0.X + pPoint3->X - pPoint0->X;
      Temp2.Y = Temp0.Y + pPoint3->Y - pPoint0->Y;
      Copy_Line(pSrc_Buf, Area_No, &Temp0, &Temp1, pDst_Buf, &Temp2);
/*
      Copy_Line(pSrc_Buf, Area_No, &Temp0, &Temp0_Bk, pDst_Buf, &Temp2);
      Temp2.X = Temp1.X + pPoint3->X - pPoint0->X;
      Temp2.Y = Temp1.Y + pPoint3->Y - pPoint0->Y;
      Copy_Line(pSrc_Buf, Area_No, &Temp1, &Temp1_Bk, pDst_Buf, &Temp2);

      Temp0_Bk.X = Temp0.X;
      Temp0_Bk.Y = Temp0.Y;

      Temp1_Bk.X = Temp1.X;
      Temp1_Bk.Y = Temp1.Y;
 */
      Temp0.X ++;
    }//while(Temp0.X < pRight -> X);
/*
    S_Point *pLeft;  //����ߵĵ�
    S_Point *pRight; //���ұߵĵ�
    S_Point *pMid;  //�м�ĵ�
    S_Point Temp0, Temp1, Temp2;

    pLeft = Get_Left_Point(pPoint0, pPoint1);
    pLeft = Get_Left_Point(pLeft, pPoint2);

    pRight = Get_Right_Point(pPoint0, pPoint1);
    pRight = Get_Right_Point(pRight, pPoint2);

    pMid = Get_X_Mid_Point(pPoint0, pPoint1, pPoint2);

    Temp0.X = pLeft -> X;  //�м��X

    Temp2.X = pLeft->X + pPoint3->X - pPoint0->X;
    Temp2.Y = pLeft->Y + pPoint3->Y - pPoint0->Y;
    Copy_Line(pSrc_Buf, Area_No, pLeft, pRight, pDst_Buf, &Temp2);

    while(Temp0.X <= pRight -> X)
    {
      Temp0.Y = GET_LINE_Y((INT32S)pLeft ->X, (INT32S)pLeft->Y, (INT32S)pRight->X, (INT32S)pRight->Y, (INT32S)Temp0.X);

      //Draw_Line(pDst_Buf, Area_No, &Temp0, &Temp1, Value);
      Temp2.X = Temp0.X + pPoint3->X - pPoint0->X;
      Temp2.Y = Temp0.Y + pPoint3->Y - pPoint0->Y;

      Copy_Line(pSrc_Buf, Area_No, &Temp0, pMid, pDst_Buf, &Temp2);
      Temp0.X ++;
    }//while(Temp0.X < pRight -> X);
    */
}

//���һ��������
//pDst_BufĿ����ʾ������
//Area_No������
//pPoint0,pPoint1,pPoint2 �����ε�������
//Value,��ɫ
void Fill_Triangle(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1,S_Point *pPoint2, INT8U Value)
{
  S_Point *pLeft;  //����ߵĵ�
  S_Point *pRight; //���ұߵĵ�
  S_Point *pMid;  //�м�ĵ�
  S_Point Temp0, Temp1;//,Temp0_Bk,Temp1_Bk;


  pLeft = Get_Left_Point(pPoint0, pPoint1);
  pLeft = Get_Left_Point(pLeft, pPoint2);

  pRight = Get_Right_Point(pPoint0, pPoint1);
  pRight = Get_Right_Point(pRight, pPoint2);

  pMid = Get_X_Mid_Point(pPoint0, pPoint1, pPoint2);

  //Draw_Line(pDst_Buf, Area_No, pPoint0, pPoint1, Value);
  //Draw_Line(pDst_Buf, Area_No, pPoint1, pPoint2, Value);
  //Draw_Line(pDst_Buf, Area_No, pPoint2, pPoint0, Value);

  Temp0.X = pLeft -> X;  //�м��X
  //Temp0_Bk.X = pLeft->X;
  //Temp0_Bk.Y = pLeft->Y;

  //Temp1_Bk.X = pLeft->X;
  //Temp1_Bk.Y = pLeft->Y;

  Draw_Line(pDst_Buf, Area_No, pLeft, pRight, Value);
  //Draw_Line(pDst_Buf, Area_No, pLeft, pMid, Value);
  //Draw_Line(pDst_Buf, Area_No, pMid, pRight,  Value);
//#if 0
  while(Temp0.X <= pRight -> X)
  {
    Temp0.Y = (INT16U)GET_LINE_Y((INT32S)pLeft ->X, (INT32S)pLeft->Y, (INT32S)pRight->X, (INT32S)pRight->Y, (INT32S)Temp0.X);
    Temp1.X = Temp0.X;
    if(Temp1.X < pMid->X)
      Temp1.Y = (INT16U)GET_LINE_Y((INT32S)pLeft ->X, (INT32S)pLeft->Y, (INT32S)pMid->X, (INT32S)pMid->Y, (INT32S)Temp1.X);
    else
      Temp1.Y = (INT16U)GET_LINE_Y((INT32S)pMid->X, (INT32S)pMid->Y, (INT32S)pRight ->X, (INT32S)pRight->Y,  (INT32S)Temp1.X);

    Draw_Line(pDst_Buf, Area_No, &Temp0, &Temp1, Value);
/*
    Draw_Line(pDst_Buf, Area_No, &Temp0, &Temp0_Bk, Value);
    Draw_Line(pDst_Buf, Area_No, &Temp1, &Temp1_Bk, Value);

    Temp0_Bk.X = Temp0.X;
    Temp0_Bk.Y = Temp0.Y;

    Temp1_Bk.X = Temp1.X;
    Temp1_Bk.Y = Temp1.Y;
*/
    Temp0.X ++;
  }//while(Temp0.X < pRight -> X);
//#endif
/*
  S_Point *pLeft;  //����ߵĵ�
  S_Point *pRight; //���ұߵĵ�
  S_Point *pMid;  //�м�ĵ�
  S_Point Temp0, Temp1, Temp2;

  pLeft = Get_Left_Point(pPoint0, pPoint1);
  pLeft = Get_Left_Point(pLeft, pPoint2);

  pRight = Get_Right_Point(pPoint0, pPoint1);
  pRight = Get_Right_Point(pRight, pPoint2);

  pMid = Get_X_Mid_Point(pPoint0, pPoint1, pPoint2);

  Temp0.X = pLeft -> X;  //�м��X

  Draw_Line(pDst_Buf, Area_No, pLeft, pRight, Value);
  //Draw_Line(pDst_Buf, Area_No, pLeft, pMid, Value);
  //Draw_Line(pDst_Buf, Area_No, pMid, pRight, Value);
  while(Temp0.X <= pRight -> X)
  {
    Temp0.Y = GET_LINE_Y((INT32S)pLeft ->X, (INT32S)pLeft->Y, (INT32S)pRight->X, (INT32S)pRight->Y, (INT32S)Temp0.X);

    //Draw_Line(pDst_Buf, Area_No, &Temp0, &Temp1, Value);
    //Temp2.X = Temp0.X + pPoint3->X - pPoint0->X;
    //Temp2.Y = Temp0.Y + pPoint3->Y - pPoint0->Y;

    Draw_Line(pDst_Buf, Area_No, &Temp0, pMid, Value);
    Temp0.X ++;
  }//while(Temp0.X < pRight -> X);
*/
}

//����һ�������
void Copy_Filled_Polygon(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT8U Point_Num,\
  S_Show_Data *pDst_Buf, S_Point *pPoint1)
{
    INT8U i;

    for(i = 1; i < Point_Num - 1; i ++)
    {
      Copy_Filled_Triangle(pSrc_Buf, Area_No, pPoint0, pPoint0 + i, pPoint0 + 1 + i, pDst_Buf, pPoint1);
      //Copy_Filled_Triangle(pSrc_Buf, Area_No, pPoint0, pPoint2, pPoint3, pDst_Buf, pPoint4);
    }
}

//���һ�������
void Fill_Polygon(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint0, INT8U Point_Num, INT8U Value)
{
    INT8U i;

    for(i = 1; i < Point_Num - 1; i ++)
    {
      Fill_Triangle(pDst_Buf, Area_No, pPoint0, pPoint0 + i, pPoint0 + 1 + i, Value);
      //Copy_Filled_Triangle(pSrc_Buf, Area_No, pPoint0, pPoint2, pPoint3, pDst_Buf, pPoint4);
    }

}

//����һ������
void Copy_Filled_Rect0(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len,\
  S_Show_Data *pDst_Buf, S_Point *pPoint1)
{
  INT16U i,j;
  INT8U Data;
  
  for(i = 0; i < X_Len;  i++)
  {
   SCAN_INT_DISABLE();
   for(j = 0; j < Y_Len; j++)
    {
      Data = Get_Area_Point_Data(pSrc_Buf, Area_No, pPoint0->X + i, pPoint0->Y + j);
      Set_Area_Point_Data(pDst_Buf, Area_No, pPoint1->X + i, pPoint1->Y + j, Data);
    }
   SCAN_INT_ENABLE();
	}
  
}
 

//�ú���Ϊ���и��Ƶķ�ʽ
/*
void Copy_Filled_Rect(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len,\
  S_Show_Data *pDst_Buf, S_Point *pPoint1, INT8U Flag)
{
    INT32U Index0, Index1;
    INT16U Len, Diff,i,j,Mask,X0,Y0, X1,Y1,Width,Height;//,Y1;
    //INT16S Width0,Width1;
    INT8U *pSrc, *pDst, *pSrc0, *pDst0, Data, Color_Num;

    //GPIO_SetBits(GPIOB,GPIO_Pin_9); //�������
///-----------�жϲ�������ȷ��---------------
    X0 = pPoint0->X; //Դ������������Ļ�е���ʼλ��
    Y0 = pPoint0->Y; //Դ������������Ļ�е���ʼλ��
    X1 = pPoint1->X; //Ŀ��������������Ļ�е���ʼλ��
    Y1 = pPoint1->Y;

    if(Area_No < MAX_AREA_NUM)
    {
        Width = Prog_Para.Area[Area_No].X_Len;
        Height = Prog_Para.Area[Area_No].Y_Len;
    }
    else
    {
        Width = Screen_Para.Base_Para.Width;
        Height = Screen_Para.Base_Para.Height;
    }

    if(X0 >= Width || Y0 >= Height ||\
       X1 >= Width || Y1 >= Height)
        return;

    if(X0 + X_Len >= Width)
        X_Len = Width - X0;

    if(Y0 + Y_Len >= Height)
        Y_Len = Height - Y0;

    if(X1 + X_Len >= Width)
        X_Len = Width - X1;

    if(Y1 + Y_Len >= Height)
        Y_Len = Height - Y1;

///---------------------------------------------

    if(Area_No < MAX_AREA_NUM)
    {
      X0 = Prog_Para.Area[Area_No].X + pPoint0->X; //Դ������������Ļ�е���ʼλ��
      X1 = Prog_Para.Area[Area_No].X + pPoint1->X; //Ŀ��������������Ļ�е���ʼλ��
    }
    else
    {
        X0 = pPoint0->X; //Դ������������Ļ�е���ʼλ��
        X1 = pPoint1->X; //Ŀ��������������Ļ�е���ʼλ��
    }

    if((X0 % 8) > (X1 % 8)) //Դ������Ҫ����
        Diff = (X0 % 8) - (X1 % 8);
    else
        Diff = (X1 % 8) - (X0 % 8);

    if(X_Len > (8 - (X1 % 8)) + (((X1 + X_Len - 1) % 8) + 1))
        Len = (X_Len - (8 - (X1 % 8)) - (((X1 + X_Len - 1) % 8) + 1))/8; //ÿ�е��ֽ�������ȥͷ��β���ֽ�,ͷ��β��Ҫ���⴦��
    else
      Len = 0;


    Color_Num = Screen_Status.Color_Num;
    Width = Screen_Para.Base_Para.Width/8 * Color_Num;

    Index0 = Get_Area_Point_Index(Area_No, pPoint0->X, pPoint0->Y); //Դ������
    Index1 = Get_Area_Point_Index(Area_No, pPoint1->X, pPoint1->Y); //Ŀ�������,Ŀ������Ӧ����Show_Data

    pSrc0 = pSrc_Buf->Color_Data + (Index0 >> 3) * Color_Num;
    pDst0 = pDst_Buf->Color_Data + (Index1 >> 3) * Color_Num;

    if((X0 % 8) >= (X1 % 8)) //Դ������Ҫ����
    {
        pSrc = pSrc0;// + i * Color_Num;     //���е�һ�����ݵ�Դ��ַ
        pDst = pDst0;// + i * (Screen_Para.Scan_Para.Rows_Fold + 1) * Color_Num; //���е�һ�����ݵ�Ŀ���ַ
		
        Mask = Bit_Mask[X1 & 0x07];
        if((X1 + X_Len - 1) /8 <= X1 / 8) //���Ŀ��������һ���ֽڿ���ڣ���Ӧ��
          Mask = Bit_Mask[X1 & 0x07] + (Bit_Mask[7 - ((X1 + X_Len - 1) & 0x07)] << (((X1 + X_Len - 1) & 0x07) + 1));// Data = ((Data << (7 - ((X0 + X_Len -1) % 8))) >> (7 - ((X0 + X_Len -1) % 8))) >> Diff;

        //��һ��
        STOP_SCAN_TIMER();

        for(j = 0; j < Y_Len; j ++) //ÿ�ж�����
        {
 
              Data = (*pSrc >> Diff) +  (*(pSrc + Color_Num) << (8 - Diff));
              *pDst = (*pDst & Mask)  + (Data & ~Mask); //����*pDst�ĵ�λ

              if(Color_Num > 1)
              {
                  Data = (*(pSrc + 1) >> Diff) +  (*(pSrc + 1 + Color_Num) << (8 - Diff));
                  *(pDst + 1) = (*(pDst + 1) & Mask)  + (Data & ~Mask); //����*pDst�ĵ�λ
              }

              pSrc += Width;//Screen_Para.Base_Para.Width/8 * Color_Num;
			  pDst += Width;
        }

        START_SCAN_TIMER();

        //�м�������
        for(i = 0; i < Len; i ++) //�������ֽ�
        {
          pSrc = pSrc0 + (i + 1) * Color_Num;     //���е�һ�����ݵ�Դ��ַ
          pDst = pDst0 + (i + 1) * Color_Num;//(Screen_Para.Scan_Para.Rows_Fold + 1) * Color_Num; //���е�һ�����ݵ�Ŀ���ַ

          STOP_SCAN_TIMER();

          for(j = 0; j < Y_Len; j ++) //ÿ�ж�����
          {
            Data = (*pSrc >> Diff) + (*(pSrc + Color_Num) << (8 - Diff));
            *pDst = Data;


            if(Color_Num > 1)
            {
                Data = (*(pSrc + 1) >> Diff) + (*(pSrc + 1 + Color_Num) << (8 - Diff));
                *(pDst + 1) = Data;
            }


            pSrc += Width;//Screen_Para.Base_Para.Width/8 * Color_Num;
		    pDst += Width;
          }

          START_SCAN_TIMER();
        }

        //�����
      if((X1 + X_Len - 1) /8 > X1 / 8)
      {
          pSrc = pSrc0 + (Len + 1) * Color_Num;     //���е�һ�����ݵ�Դ��ַ
          pDst = pDst0 + (Len + 1) * Color_Num;//(Screen_Para.Scan_Para.Rows_Fold + 1) * Color_Num; //���е�һ�����ݵ�Ŀ���ַ
          
          Mask = Bit_Mask[((X1 + X_Len - 1) & 0x07) + 1];

          STOP_SCAN_TIMER();

          for(j = 0; j < Y_Len; j ++) //ÿ�ж�����
          {
            Data = ((*pSrc) >> (Diff)) + (*(pSrc + Color_Num) << (8 - Diff));
            *pDst = ((*pDst) & ~Mask)  + (Data & Mask);

            if(Color_Num > 1)
            {
                Data = ((*(pSrc + 1)) >> (Diff)) + (*(pSrc + 1 + Color_Num) << (8 - Diff));
                *(pDst + 1) = ((*(pDst + 1)) & ~Mask)  + (Data & Mask);
            }

            pSrc += Width;//Screen_Para.Base_Para.Width/8 * Color_Num;
		    pDst += Width;
        }

        START_SCAN_TIMER();
      }
    }
    else
    {
        pSrc = pSrc0;// + i * Color_Num;     //���е�һ�����ݵ�Դ��ַ
        pDst = pDst0;// + i * (Screen_Para.Scan_Para.Rows_Fold + 1) * Color_Num; //���е�һ�����ݵ�Ŀ���ַ
	
        Mask = Bit_Mask[X1 & 0x07];
        if((X1 + X_Len - 1) /8 <= X1 / 8) //���Ŀ��������һ���ֽڿ���ڣ���Ӧ��
          Mask = Bit_Mask[X1 & 0x07] + (Bit_Mask[7 - ((X1 + X_Len - 1) & 0x07)] << (((X1 + X_Len - 1) & 0x07) + 1));// Data = ((Data << (7 - ((X0 + X_Len -1) % 8))) >> (7 - ((X0 + X_Len -1) % 8))) >> Diff;

        //��һ��
        STOP_SCAN_TIMER();

        for(j = 0; j < Y_Len; j ++) //ÿ�ж�����
        {
            Data = (*pSrc << Diff);
            *pDst = (*pDst & Mask)  + (Data & ~Mask);

            if(Color_Num > 1)
            {
                Data = (*(pSrc + 1) << Diff);
                *(pDst + 1) = (*(pDst + 1) & Mask)  + (Data & ~Mask);
            }

            pSrc += Width;//Screen_Para.Base_Para.Width/8 * Color_Num;
			pDst += Width;
        }

        START_SCAN_TIMER();

        for(i = 0; i < Len; i ++) //�������ֽ�
        {
          pSrc = pSrc0 + (i + 1) * Color_Num;     //���е�һ�����ݵ�Դ��ַ
          pDst = pDst0 + (i + 1) * Color_Num;//(Screen_Para.Scan_Para.Rows_Fold + 1) * Color_Num; //���е�һ�����ݵ�Ŀ���ַ

          STOP_SCAN_TIMER();

          for(j = 0; j < Y_Len; j ++)
          {
            Data =((*(pSrc - Color_Num)) >> (8 - Diff)) + (*pSrc << Diff);
            *pDst = Data;

            if(Color_Num > 1)
            {
               Data =((*(pSrc + 1 - Color_Num)) >> (8 - Diff)) + (*(pSrc + 1) << Diff);
               *(pDst + 1) = Data;
            }

            pSrc += Width;//Screen_Para.Base_Para.Width/8 * Color_Num;
			pDst += Width;
         }

         START_SCAN_TIMER();
      }

      if((X1 + X_Len - 1) /8 > X1 / 8)
      {
          pSrc = pSrc0 + (Len + 1) * Color_Num;     //���е�һ�����ݵ�Դ��ַ
          pDst = pDst0 + (Len + 1) * Color_Num;//(Screen_Para.Scan_Para.Rows_Fold + 1) * Color_Num; //���е�һ�����ݵ�Ŀ���ַ
          
          Mask = Bit_Mask[((X1 + X_Len - 1) & 0x07) + 1];

          STOP_SCAN_TIMER();

          for(j = 0; j < Y_Len; j ++) //ÿ�ж�����
          {
              Data = ((*(pSrc - Color_Num)) >> (8 -Diff)) + (*pSrc << Diff);
              *pDst = ((*pDst) & ~Mask)  + (Data & Mask);

              if(Color_Num > 1)
              {
                  Data = ((*(pSrc + 1 - Color_Num)) >> (8 -Diff)) + (*(pSrc + 1) << Diff);
                  *(pDst + 1) = ((*(pDst + 1)) & ~Mask)  + (Data & Mask);
              }

              pSrc += Width;//Screen_Para.Base_Para.Width/8 * Color_Num;
			  pDst += Width;
          }

          START_SCAN_TIMER();
      }
    }

	//for(i = 0 ; i< 16; i ++)
	  //LED_Scan_One_Row();

    //LED_Scan_Screen();
	//SCAN_INT_ENABLE();
        //GPIO_ResetBits(GPIOB,GPIO_Pin_9); //�������
}
*/

//�ú���Ϊ���и��Ƶķ�ʽ��
void Copy_Filled_Rect(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len,\
  S_Show_Data *pDst_Buf, S_Point *pPoint1, INT8U Flag)
{
    INT32U Index0, Index1;
    INT16U Len, Diff,i,j,Mask,X0,X1,Y0,Y1,Width,Height;//,Y1;
    INT8U *pSrc, *pDst, Data, Color_Num;

/*
      for(i = 0; i < X_Len;  i++)
        for(j = 0; j < Y_Len; j++)
        {
          Data = Get_Area_Point_Data(pSrc_Buf, Area_No, pPoint0->X + i, pPoint0->Y + j);
          Set_Area_Point_Data(pDst_Buf, Area_No, pPoint1->X + i, pPoint1->Y + j, Data);
        }
      return;
*/
    if(X_Len EQ 0 || Y_Len EQ 0)
        return;

    //GPIO_SetBits(GPIOB,GPIO_Pin_9); //�������
///-----------�жϲ�������ȷ��---------------
    X0 = pPoint0->X; //Դ������������Ļ�е���ʼλ��
    Y0 = pPoint0->Y; //Դ������������Ļ�е���ʼλ��
    X1 = pPoint1->X; //Ŀ��������������Ļ�е���ʼλ��
    Y1 = pPoint1->Y;

    if(Area_No < MAX_AREA_NUM)
    {
        Width = Prog_Para.Area[Area_No].X_Len;
        Height = Prog_Para.Area[Area_No].Y_Len;
    }
    else
    {
        Width = Screen_Para.Base_Para.Width;
        Height = Screen_Para.Base_Para.Height;
    }

    if(X0 >= Width || Y0 >= Height ||\
       X1 >= Width || Y1 >= Height)
        return;

    if(X0 + X_Len >= Width)
        X_Len = Width - X0;

    if(Y0 + Y_Len >= Height)
        Y_Len = Height - Y0;

    if(X1 + X_Len >= Width)
        X_Len = Width - X1;

    if(Y1 + Y_Len >= Height)
        Y_Len = Height - Y1;

///---------------------------------------------

    if(Area_No < MAX_AREA_NUM)
    {
      X0 = Prog_Para.Area[Area_No].X + pPoint0->X; //Դ������������Ļ�е���ʼλ��
      X1 = Prog_Para.Area[Area_No].X + pPoint1->X; //Ŀ��������������Ļ�е���ʼλ��
    }
    else
    {
        X0 = pPoint0->X; //Դ������������Ļ�е���ʼλ��
        X1 = pPoint1->X; //Ŀ��������������Ļ�е���ʼλ��
    }

    if((X0 % 8) > (X1 % 8)) //Դ������Ҫ����
        Diff = (X0 % 8) - (X1 % 8);
    else
        Diff = (X1 % 8) - (X0 % 8);

    if(X_Len > (8 - (X1 % 8)) + (((X1 + X_Len - 1) % 8) + 1))
        Len = (X_Len - (8 - (X1 % 8)) - (((X1 + X_Len - 1) % 8) + 1))/8; //ÿ�е��ֽ�������ȥͷ��β���ֽ�,ͷ��β��Ҫ���⴦��
    else
    {
      Len = 0;
      //return;
    }
    //X0 = Prog_Para.Area[Area_No].X + pPoint0->X; //Դ������������Ļ�е���ʼλ��
    //Y0 = Prog_Para.Area[Area_No].Y + pPoint0->Y;

    //X1 = Prog_Para.Area[Area_No].X + pPoint1->X; //Ŀ��������������Ļ�е���ʼλ��
    //Y1 = Prog_Para.Area[Area_No].Y + pPoint1->Y;
/*
    if((X0 % 8) > (X1 % 8)) //Դ������Ҫ����
        Diff = (X0 % 8) - (X1 % 8);
    else
        Diff = (X1 % 8) - (X0 % 8);

    //(8 - (X1 % 8))��ʾ��ʼ�ֽڵ�λ����((X1 + X_Len - 1) % 8) + 1)��ʾĩ�ֽڵ�λ��
    if(X_Len > (8 - (X1 % 8)) + (((X1 + X_Len - 1) % 8) + 1))
        Len = (X_Len - (8 - (X1 % 8)) - (((X1 + X_Len - 1) % 8) + 1))/8; //ÿ�е��ֽ�������ȥͷ��β���ֽ�,ͷ��β��Ҫ���⴦��
    else
      Len = 0;
*/
	//STOP_SCAN_TIMER();
	//LED_Scan_One_Row();
    //qDebug("len = %d",Len);
    Color_Num = Screen_Status.Color_Num;

    if(pSrc_Buf != pDst_Buf || (X0 >= X1 && Y0 >= Y1)) //����ǲ�ͬ��ʾ����俽������ͬһ������Դ��Ŀ�����Ͻǣ���������ң��������¸���
    {
    if((X0 % 8) >= (X1 % 8)) //Դ������Ҫ����
    {
        for(i = 0; i < Y_Len; i ++)
        {
		    //STOP_SCAN_TIMER();
            
            Index0 = Get_Area_Point_Index(Area_No, pPoint0->X, pPoint0->Y + i); //Դ������
            Index1 = Get_Area_Point_Index(Area_No, pPoint1->X, pPoint1->Y + i); //Ŀ�������

            pSrc = pSrc_Buf->Color_Data + (Index0 >> 3) * Color_Num;
            pDst = pDst_Buf->Color_Data + (Index1 >> 3) * Color_Num;

            //��һ���ֽ����⴦��
            Mask = Bit_Mask[X1 & 0x07];
            if((X1 + X_Len - 1) /8 <= X1 / 8) //���Ŀ��������һ���ֽڿ���ڣ���Ӧ��
              Mask = Bit_Mask[X1 & 0x07] + (Bit_Mask[7 - ((X1 + X_Len - 1) & 0x07)] << (((X1 + X_Len - 1) & 0x07) + 1));// Data = ((Data << (7 - ((X0 + X_Len -1) % 8))) >> (7 - ((X0 + X_Len -1) % 8))) >> Diff;

            Data = (*pSrc >> Diff) +  (*(pSrc + Color_Num) << (8 - Diff));
            *pDst = (*pDst & Mask)  + (Data & ~Mask); //����*pDst�ĵ�λ

            if(Color_Num > 1)
            {
                pSrc++;
                pDst++;

                Data = (*pSrc >> Diff) +  (*(pSrc + Color_Num) << (8 - Diff));
                *pDst = (*pDst & Mask)  + (Data & ~Mask); //����*pDst�ĵ�λ
            }

            for(j = 0; j < Len; j ++)
            {
                pDst++;
                pSrc++;

                Data = (*pSrc >> Diff) + (*(pSrc + Color_Num) << (8 - Diff));
                *pDst = Data;


                if(Color_Num > 1)
                {
                    pDst++;
                    pSrc++;

                    Data = (*pSrc >> Diff) + (*(pSrc + Color_Num) << (8 - Diff));
                    *pDst = Data;
                }
            }

            //���һ���ֽ����⴦��
            if((X1 + X_Len - 1) /8 > X1 / 8)
            {
                pDst++;
                pSrc++;

              //Data = (*pSrc) & Bit_Mask[((X0 + X_Len - 1) & 0x07) + 1];
              Mask = Bit_Mask[((X1 + X_Len - 1) & 0x07) + 1];
              Data = ((*pSrc) >> (Diff)) + (*(pSrc + Color_Num) << (8 - Diff));
              *pDst = ((*pDst) & ~Mask)  + (Data & Mask);

              if(Color_Num > 1)
              {
                  pSrc++;
                  pDst++;

                  Data = ((*pSrc) >> (Diff)) + (*(pSrc + Color_Num) << (8 - Diff));
                  *pDst = ((*pDst) & ~Mask)  + (Data & Mask);
              }
            }
			
			//START_SCAN_TIMER();
        }

    }
    else
    {

        for(i = 0; i < Y_Len; i ++)
        {
			

            Index0 = Get_Area_Point_Index(Area_No, pPoint0->X, pPoint0->Y + i); //Դ������
            Index1 = Get_Area_Point_Index(Area_No, pPoint1->X, pPoint1->Y + i); //Ŀ�������

            pSrc = pSrc_Buf->Color_Data + (Index0 >> 3) * Color_Num;
            pDst = pDst_Buf->Color_Data + (Index1 >> 3) * Color_Num;

            //��һ���ֽ����⴦��
            Mask = Bit_Mask[X1 & 0x07];
            if((X1 + X_Len - 1) /8 <= X1 / 8) //���Ŀ��������һ���ֽڿ���ڣ���Ӧ��
              Mask = Bit_Mask[X1 & 0x07] + (Bit_Mask[7 - ((X1 + X_Len - 1) & 0x07)] << (((X1 + X_Len - 1) & 0x07) + 1));// Data = ((Data << (7 - ((X0 + X_Len -1) % 8))) >> (7 - ((X0 + X_Len -1) % 8))) >> Diff;

            Data = (*pSrc << Diff);
            *pDst = (*pDst & Mask)  + (Data & ~Mask);

            if(Color_Num > 1)
            {
                pDst++;
                pSrc++;

                Data = (*pSrc << Diff);
                *pDst = (*pDst & Mask)  + (Data & ~Mask);
            }

            for(j = 0; j < Len; j ++)
            {
                pDst++;
                pSrc++;

                Data =((*(pSrc - Color_Num)) >> (8 - Diff)) + (*pSrc << Diff);
                *pDst = Data;

                if(Color_Num > 1)
                {
                    pDst++;
                    pSrc++;

                   Data =((*(pSrc - Color_Num)) >> (8 - Diff)) + (*pSrc << Diff);
                   *pDst = Data;
                }
            }

            //���һ���ֽ����⴦��
            if((X1 + X_Len - 1) /8 > X1 / 8)
            {
              pDst++;
              pSrc++;

              Mask = Bit_Mask[((X1 + X_Len - 1) & 0x07) + 1];

              Data = ((*(pSrc - Color_Num)) >> (8 -Diff)) + (*pSrc << Diff);
              *pDst = ((*pDst) & ~Mask)  + (Data & Mask);

              if(Color_Num > 1)
              {
                  pDst++;
                  pSrc++;

                  Data = ((*(pSrc - Color_Num)) >> (8 -Diff)) + (*pSrc << Diff);
                  *pDst = ((*pDst) & ~Mask)  + (Data & Mask);
              }
            }

		
        }
    }
   }
   else if(X0 <= X1 && Y0 >= Y1) //Դ��Ŀ�����ϣ�������������������¸���
    {
       if((X0 % 8) >= (X1 % 8)) //Դ������Ҫ����
       {
           for(i = 0; i < Y_Len; i ++)
           {
                       //STOP_SCAN_TIMER();

               Index0 = Get_Area_Point_Index(Area_No, pPoint0->X + X_Len - 1, pPoint0->Y + i); //Դ������
               Index1 = Get_Area_Point_Index(Area_No, pPoint1->X + X_Len - 1, pPoint1->Y + i); //Ŀ�������

               pSrc = pSrc_Buf->Color_Data + (Index0 >> 3) * Color_Num;
               pDst = pDst_Buf->Color_Data + (Index1 >> 3) * Color_Num;

               if(((X0 + X_Len - 1) % 8) < ((X1 + X_Len - 1) % 8))
                 pSrc -= Color_Num;

               //���һ���ֽ����⴦��
               //if((X1 + X_Len - 1) /8 > X1 / 8)
               {
                   //pDst++;
                   //pSrc++;

                 //Data = (*pSrc) & Bit_Mask[((X0 + X_Len - 1) & 0x07) + 1];
                 Mask = Bit_Mask[((X1 + X_Len - 1) & 0x07) + 1];
                 Data = ((*pSrc) >> (Diff)) + (*(pSrc + Color_Num) << (8 - Diff));
                 *pDst = ((*pDst) & ~Mask)  + (Data & Mask);

                 if(Color_Num > 1)
                 {
                     //pSrc++;
                     //pDst++;

                     Data = ((*(pSrc + 1)) >> (Diff)) + (*(pSrc + 1 + Color_Num) << (8 - Diff));
                     *(pDst + 1) = ((*(pDst + 1)) & ~Mask)  + (Data & Mask);
                 }
               }

               for(j = 0; j < Len; j ++)
               {
                   pDst -= Color_Num;
                   pSrc -= Color_Num;

                   Data = (*pSrc >> Diff) + (*(pSrc + Color_Num) << (8 - Diff));
                   *pDst = Data;


                   if(Color_Num > 1)
                   {
                       //pDst++;
                       //pSrc++;

                       Data = ((*(pSrc + 1)) >> (Diff)) + (*(pSrc + 1 + Color_Num) << (8 - Diff));
                       *(pDst + 1) = Data;
                   }
               }

               if((X1 + X_Len - 1) /8 > X1 / 8)
               {
               pDst -= Color_Num;
               pSrc -= Color_Num;

               //��һ���ֽ����⴦��
               Mask = Bit_Mask[X1 & 0x07];
               if((X1 + X_Len - 1) /8 <= X1 / 8) //���Ŀ��������һ���ֽڿ���ڣ���Ӧ��
                 Mask = Bit_Mask[X1 & 0x07] + (Bit_Mask[7 - ((X1 + X_Len - 1) & 0x07)] << (((X1 + X_Len - 1) & 0x07) + 1));// Data = ((Data << (7 - ((X0 + X_Len -1) % 8))) >> (7 - ((X0 + X_Len -1) % 8))) >> Diff;

               Data = (*pSrc >> Diff) +  (*(pSrc + Color_Num) << (8 - Diff));
               *pDst = (*pDst & Mask)  + (Data & ~Mask); //����*pDst�ĵ�λ

               if(Color_Num > 1)
               {
                   //pSrc++;
                   //pDst++;

                   Data = ((*(pSrc + 1)) >> (Diff)) + (*(pSrc + 1 + Color_Num) << (8 - Diff));
                   *(pDst + 1) = ((*(pDst + 1)) & Mask)  + (Data & ~Mask);
               }
           }
                           //START_SCAN_TIMER();
           }

       }
       else
       {

           for(i = 0; i < Y_Len; i ++)
           {


               Index0 = Get_Area_Point_Index(Area_No, pPoint0->X + X_Len - 1, pPoint0->Y + i); //Դ������
               Index1 = Get_Area_Point_Index(Area_No, pPoint1->X + X_Len - 1, pPoint1->Y + i); //Ŀ�������

               pSrc = pSrc_Buf->Color_Data + (Index0 >> 3) * Color_Num;
               pDst = pDst_Buf->Color_Data + (Index1 >> 3) * Color_Num;

               if(((X0 + X_Len - 1) % 8) > ((X1 + X_Len - 1) % 8))
                 pSrc += Color_Num;

               //���һ���ֽ����⴦��
               //if((X1 + X_Len - 1) /8 > X1 / 8)
               {
                 //pDst++;
                 //pSrc++;

                 Mask = Bit_Mask[((X1 + X_Len - 1) & 0x07) + 1];

                 Data = ((*(pSrc - Color_Num)) >> (8 -Diff)) + (*pSrc << Diff);
                 *pDst = ((*pDst) & ~Mask)  + (Data & Mask);

                 if(Color_Num > 1)
                 {
                     //pDst++;
                     //pSrc++;

                     Data = ((*(pSrc + 1 - Color_Num)) >> (8 -Diff)) + (*(pSrc + 1) << Diff);
                     *(pDst + 1) = ((*(pDst + 1)) & ~Mask)  + (Data & Mask);
                 }
               }

               for(j = 0; j < Len; j ++)
               {
                   pDst -= Color_Num;
                   pSrc -= Color_Num;

                   Data =((*(pSrc - Color_Num)) >> (8 - Diff)) + (*pSrc << Diff);
                   *pDst = Data;

                   if(Color_Num > 1)
                   {
                       //pDst++;
                       //pSrc++;

                      Data =((*(pSrc + 1 - Color_Num)) >> (8 - Diff)) + (*(pSrc + 1) << Diff);
                      *(pDst + 1) = Data;
                   }
               }

               if((X1 + X_Len - 1) /8 > X1 / 8)
               {
               pDst -= Color_Num;
               pSrc -= Color_Num;

               //��һ���ֽ����⴦��
               Mask = Bit_Mask[X1 & 0x07];
               if((X1 + X_Len - 1) /8 <= X1 / 8) //���Ŀ��������һ���ֽڿ���ڣ���Ӧ��
                 Mask = Bit_Mask[X1 & 0x07] + (Bit_Mask[7 - ((X1 + X_Len - 1) & 0x07)] << (((X1 + X_Len - 1) & 0x07) + 1));// Data = ((Data << (7 - ((X0 + X_Len -1) % 8))) >> (7 - ((X0 + X_Len -1) % 8))) >> Diff;

               Data = (*pSrc << Diff);
               *pDst = (*pDst & Mask)  + (Data & ~Mask);

               if(Color_Num > 1)
               {
                   //pDst++;
                   //pSrc++;

                   Data = (*(pSrc + 1) << Diff);
                   *(pDst + 1) = (*(pDst + 1) & Mask)  + (Data & ~Mask);
               }
           }
           }
       }
   }
   else if(X0 >= X1 && Y0 < Y1) //����ǲ�ͬ��ʾ����俽������ͬһ������Դ��Ŀ�����Ͻǣ���������ң��������¸���
   {
       if((X0 % 8) >= (X1 % 8)) //Դ������Ҫ����
       {
           for(i = 0; i < Y_Len; i ++)
           {
                       //STOP_SCAN_TIMER();

               Index0 = Get_Area_Point_Index(Area_No, pPoint0->X, pPoint0->Y + Y_Len - 1 - i); //Դ������
               Index1 = Get_Area_Point_Index(Area_No, pPoint1->X, pPoint1->Y + Y_Len - 1 - i); //Ŀ�������

               pSrc = pSrc_Buf->Color_Data + (Index0 >> 3) * Color_Num;
               pDst = pDst_Buf->Color_Data + (Index1 >> 3) * Color_Num;

               //��һ���ֽ����⴦��
               Mask = Bit_Mask[X1 & 0x07];
               if((X1 + X_Len - 1) /8 <= X1 / 8) //���Ŀ��������һ���ֽڿ���ڣ���Ӧ��
                 Mask = Bit_Mask[X1 & 0x07] + (Bit_Mask[7 - ((X1 + X_Len - 1) & 0x07)] << (((X1 + X_Len - 1) & 0x07) + 1));// Data = ((Data << (7 - ((X0 + X_Len -1) % 8))) >> (7 - ((X0 + X_Len -1) % 8))) >> Diff;

               Data = (*pSrc >> Diff) +  (*(pSrc + Color_Num) << (8 - Diff));
               *pDst = (*pDst & Mask)  + (Data & ~Mask); //����*pDst�ĵ�λ

               if(Color_Num > 1)
               {
                   pSrc++;
                   pDst++;

                   Data = (*pSrc >> Diff) +  (*(pSrc + Color_Num) << (8 - Diff));
                   *pDst = (*pDst & Mask)  + (Data & ~Mask); //����*pDst�ĵ�λ
               }

               for(j = 0; j < Len; j ++)
               {
                   pDst++;
                   pSrc++;

                   Data = (*pSrc >> Diff) + (*(pSrc + Color_Num) << (8 - Diff));
                   *pDst = Data;


                   if(Color_Num > 1)
                   {
                       pDst++;
                       pSrc++;

                       Data = (*pSrc >> Diff) + (*(pSrc + Color_Num) << (8 - Diff));
                       *pDst = Data;
                   }
               }

               //���һ���ֽ����⴦��
               if((X1 + X_Len - 1) /8 > X1 / 8)
               {
                   pDst++;
                   pSrc++;

                 //Data = (*pSrc) & Bit_Mask[((X0 + X_Len - 1) & 0x07) + 1];
                 Mask = Bit_Mask[((X1 + X_Len - 1) & 0x07) + 1];
                 Data = ((*pSrc) >> (Diff)) + (*(pSrc + Color_Num) << (8 - Diff));
                 *pDst = ((*pDst) & ~Mask)  + (Data & Mask);

                 if(Color_Num > 1)
                 {
                     pSrc++;
                     pDst++;

                     Data = ((*pSrc) >> (Diff)) + (*(pSrc + Color_Num) << (8 - Diff));
                     *pDst = ((*pDst) & ~Mask)  + (Data & Mask);
                 }
               }

                           //START_SCAN_TIMER();
           }

       }
       else
       {

           for(i = 0; i < Y_Len; i ++)
           {


               Index0 = Get_Area_Point_Index(Area_No, pPoint0->X, pPoint0->Y + i); //Դ������
               Index1 = Get_Area_Point_Index(Area_No, pPoint1->X, pPoint1->Y + i); //Ŀ�������

               pSrc = pSrc_Buf->Color_Data + (Index0 >> 3) * Color_Num;
               pDst = pDst_Buf->Color_Data + (Index1 >> 3) * Color_Num;

               //��һ���ֽ����⴦��
               Mask = Bit_Mask[X1 & 0x07];
               if((X1 + X_Len - 1) /8 <= X1 / 8) //���Ŀ��������һ���ֽڿ���ڣ���Ӧ��
                 Mask = Bit_Mask[X1 & 0x07] + (Bit_Mask[7 - ((X1 + X_Len - 1) & 0x07)] << (((X1 + X_Len - 1) & 0x07) + 1));// Data = ((Data << (7 - ((X0 + X_Len -1) % 8))) >> (7 - ((X0 + X_Len -1) % 8))) >> Diff;

               Data = (*pSrc << Diff);
               *pDst = (*pDst & Mask)  + (Data & ~Mask);

               if(Color_Num > 1)
               {
                   pDst++;
                   pSrc++;

                   Data = (*pSrc << Diff);
                   *pDst = (*pDst & Mask)  + (Data & ~Mask);
               }

               for(j = 0; j < Len; j ++)
               {
                   pDst++;
                   pSrc++;

                   Data =((*(pSrc - Color_Num)) >> (8 - Diff)) + (*pSrc << Diff);
                   *pDst = Data;

                   if(Color_Num > 1)
                   {
                       pDst++;
                       pSrc++;

                      Data =((*(pSrc - Color_Num)) >> (8 - Diff)) + (*pSrc << Diff);
                      *pDst = Data;
                   }
               }

               //���һ���ֽ����⴦��
               if((X1 + X_Len - 1) /8 > X1 / 8)
               {
                 pDst++;
                 pSrc++;

                 Mask = Bit_Mask[((X1 + X_Len - 1) & 0x07) + 1];

                 Data = ((*(pSrc - Color_Num)) >> (8 -Diff)) + (*pSrc << Diff);
                 *pDst = ((*pDst) & ~Mask)  + (Data & Mask);

                 if(Color_Num > 1)
                 {
                     pDst++;
                     pSrc++;

                     Data = ((*(pSrc - Color_Num)) >> (8 -Diff)) + (*pSrc << Diff);
                     *pDst = ((*pDst) & ~Mask)  + (Data & Mask);
                 }
               }


           }
       }
      }
   else if(X0 <= X1 && Y0 < Y1) //Դ��Ŀ�����ϣ�������������������¸���
    {
       if((X0 % 8) >= (X1 % 8)) //Դ������Ҫ����
       {
           for(i = 0; i < Y_Len; i ++)
           {
                       //STOP_SCAN_TIMER();

               Index0 = Get_Area_Point_Index(Area_No, pPoint0->X + X_Len - 1, pPoint0->Y + Y_Len - 1 - i); //Դ������
               Index1 = Get_Area_Point_Index(Area_No, pPoint1->X + X_Len - 1, pPoint1->Y + Y_Len - 1 - i); //Ŀ�������

               pSrc = pSrc_Buf->Color_Data + (Index0 >> 3) * Color_Num;
               pDst = pDst_Buf->Color_Data + (Index1 >> 3) * Color_Num;

               if(((X0 + X_Len - 1) % 8) < ((X1 + X_Len - 1) % 8))
                 pSrc -= Color_Num;

               //���һ���ֽ����⴦��
               //if((X1 + X_Len - 1) /8 > X1 / 8)
               {
                   //pDst++;
                   //pSrc++;

                 //Data = (*pSrc) & Bit_Mask[((X0 + X_Len - 1) & 0x07) + 1];
                 Mask = Bit_Mask[((X1 + X_Len - 1) & 0x07) + 1];
                 Data = ((*pSrc) >> (Diff)) + (*(pSrc + Color_Num) << (8 - Diff));
                 *pDst = ((*pDst) & ~Mask)  + (Data & Mask);

                 if(Color_Num > 1)
                 {
                     //pSrc++;
                     //pDst++;

                     Data = ((*(pSrc + 1)) >> (Diff)) + (*(pSrc + 1 + Color_Num) << (8 - Diff));
                     *(pDst + 1) = ((*(pDst + 1)) & ~Mask)  + (Data & Mask);
                 }
               }

               for(j = 0; j < Len; j ++)
               {
                   pDst -= Color_Num;
                   pSrc -= Color_Num;

                   Data = (*pSrc >> Diff) + (*(pSrc + Color_Num) << (8 - Diff));
                   *pDst = Data;


                   if(Color_Num > 1)
                   {
                       //pDst++;
                       //pSrc++;

                       Data = ((*(pSrc + 1)) >> (Diff)) + (*(pSrc + 1 + Color_Num) << (8 - Diff));
                       *(pDst + 1) = Data;
                   }
               }

               if((X1 + X_Len - 1) /8 > X1 / 8)
               {
               pDst -= Color_Num;
               pSrc -= Color_Num;

               //��һ���ֽ����⴦��
               Mask = Bit_Mask[X1 & 0x07];
               if((X1 + X_Len - 1) /8 <= X1 / 8) //���Ŀ��������һ���ֽڿ���ڣ���Ӧ��
                 Mask = Bit_Mask[X1 & 0x07] + (Bit_Mask[7 - ((X1 + X_Len - 1) & 0x07)] << (((X1 + X_Len - 1) & 0x07) + 1));// Data = ((Data << (7 - ((X0 + X_Len -1) % 8))) >> (7 - ((X0 + X_Len -1) % 8))) >> Diff;

               Data = (*pSrc >> Diff) +  (*(pSrc + Color_Num) << (8 - Diff));
               *pDst = (*pDst & Mask)  + (Data & ~Mask); //����*pDst�ĵ�λ

               if(Color_Num > 1)
               {
                   //pSrc++;
                   //pDst++;

                   Data = ((*(pSrc + 1)) >> (Diff)) + (*(pSrc + 1 + Color_Num) << (8 - Diff));
                   *(pDst + 1) = ((*(pDst + 1)) & ~Mask)  + (Data & Mask);
               }
           }
                           //START_SCAN_TIMER();
           }

       }
       else
       {

           for(i = 0; i < Y_Len; i ++)
           {


               Index0 = Get_Area_Point_Index(Area_No, pPoint0->X + X_Len - 1, pPoint0->Y + i); //Դ������
               Index1 = Get_Area_Point_Index(Area_No, pPoint1->X + X_Len - 1, pPoint1->Y + i); //Ŀ�������

               pSrc = pSrc_Buf->Color_Data + (Index0 >> 3) * Color_Num;
               pDst = pDst_Buf->Color_Data + (Index1 >> 3) * Color_Num;

               if(((X0 + X_Len - 1) % 8) > ((X1 + X_Len - 1) % 8))
                 pSrc += Color_Num;

               //���һ���ֽ����⴦��
               //if((X1 + X_Len - 1) /8 > X1 / 8)
               {
                 //pDst++;
                 //pSrc++;

                 Mask = Bit_Mask[((X1 + X_Len - 1) & 0x07) + 1];

                 Data = ((*(pSrc - Color_Num)) >> (8 -Diff)) + (*pSrc << Diff);
                 *pDst = ((*pDst) & ~Mask)  + (Data & Mask);

                 if(Color_Num > 1)
                 {
                     //pDst++;
                     //pSrc++;

                     Data = ((*(pSrc + 1 - Color_Num)) >> (8 -Diff)) + (*(pSrc + 1) << Diff);
                     *(pDst + 1) = ((*(pDst + 1)) & ~Mask)  + (Data & Mask);
                 }
               }

               for(j = 0; j < Len; j ++)
               {
                   pDst -= Color_Num;
                   pSrc -= Color_Num;

                   Data =((*(pSrc - Color_Num)) >> (8 - Diff)) + (*pSrc << Diff);
                   *pDst = Data;

                   if(Color_Num > 1)
                   {
                       //pDst++;
                       //pSrc++;

                      Data =((*(pSrc + 1 - Color_Num)) >> (8 - Diff)) + (*(pSrc + 1) << Diff);
                      *(pDst + 1) = Data;
                   }
               }

               if((X1 + X_Len - 1) /8 > X1 / 8)
               {
               pDst -= Color_Num;
               pSrc -= Color_Num;

               //��һ���ֽ����⴦��
               Mask = Bit_Mask[X1 & 0x07];
               if((X1 + X_Len - 1) /8 <= X1 / 8) //���Ŀ��������һ���ֽڿ���ڣ���Ӧ��
                 Mask = Bit_Mask[X1 & 0x07] + (Bit_Mask[7 - ((X1 + X_Len - 1) & 0x07)] << (((X1 + X_Len - 1) & 0x07) + 1));// Data = ((Data << (7 - ((X0 + X_Len -1) % 8))) >> (7 - ((X0 + X_Len -1) % 8))) >> Diff;

               Data = (*pSrc << Diff);
               *pDst = (*pDst & Mask)  + (Data & ~Mask);

               if(Color_Num > 1)
               {
                   //pDst++;
                   //pSrc++;

                   Data = (*(pSrc + 1) << Diff);
                   *(pDst + 1) = (*(pDst + 1) & Mask)  + (Data & ~Mask);
               }
           }
           }
       }
   }
	//LED_Scan_One_Row();
	//START_SCAN_TIMER();
     //GPIO_ResetBits(GPIOB,GPIO_Pin_9); //�������

}

//����ͼ������,�Ӷ�ȡ���Ļ��������Ƶ�Show_Data��
//pSrc��ʾ�Ӵ洢���ж�������ʾ����
//Off��ʾpSrc��ʼ��������һ����ʾ�����е�ƫ��
//SrcLen��ʾpSrc��ʼ�����ݳ���
//pDst��ʾĿ����ʾ������
//Area_No��ʾͼ���������ڷ�����
//X��Y��ʾĿ��ͼ����ʾ������
//Width,Height���Ƶ�ͼ�εĿ�Ⱥ͸߶�
INT16U Copy_Show_Data(INT8U *pSrc, INT32U Off, INT16U SrcLen,\
                     S_Show_Data *pDst, INT8U Area_No, INT16U X, INT16U Y, INT16U Width, INT16U Height)
{
  //INT16U Width,Height;
  INT16U X0,Y0,Row_Points, Data0,Data1, Mask;
  INT32U i,Len,Off0,Index;
  INT8U *pData, Bit;// Mask, Data;
  INT8U Screen_Color_Num;//,Re;
/*
  Area_Width = Get_Area_Width(Area_No);
  Area_Height = Get_Area_Height(Area_No);
  Dst_Off = X *
*/
  Screen_Color_Num = Get_Screen_Color_Num();
  Len = GET_TEXT_LEN(Width,Height);//(INT32U)Width * ((Height % 8) EQ 0 ? (Height / 8) : (Height / 8 + 1)); //ÿ����ʾ�����ݳ���
  Len = Len * Screen_Color_Num; //ÿһĻ��ʾ��Ҫ���ֽ���!

#if QT_EN && QT_SIM_EN
  if(Off + SrcLen > Len)
  {
    if(memcmp(pSrc, protoShowData.Color_Data + Off, Len - Off) != 0)
     ASSERT_FAILED();
  }
  else
  {
    if(memcmp(pSrc, protoShowData.Color_Data + Off, SrcLen) != 0)
      ASSERT_FAILED();
  }
#endif
  if((Off % Len) % Screen_Color_Num != 0)
      ASSERT_FAILED();

  Off0 = Off * 8 / Screen_Color_Num;
  Off = (Off % Len) * 8 / Screen_Color_Num; //Off��һ����ʾ�����е�ƫ��, Off/Len��ʾ�ǵڶ���Ļ

  //debug("copy show data, start x = %d, y = %d", (((Off)/8) % Width), (((Off)/8) / Width)*8 + (Off)%8);

  Row_Points = ((Width % 8) EQ 0)?Width:((Width / 8 + 1)*8);

  if(Row_Points EQ 0)
      return 0;
/*
  //���θ����ж��ٵ�����SrcLen*8/Screen_Color_Num
  for(i = 0; i <SrcLen*8/Screen_Color_Num && (i + Off0)<Len*8/Screen_Color_Num; i ++)
  {
    X0 = (Off + i) % Row_Points;
    Y0 = (Off + i) / Row_Points;

    if(X0 < Width && Y0 < Height) //X0,Y0������X_Len��Y_Len�ķ�Χ��
    {
        if(Screen_Color_Num EQ 1)  //��ɫ��
          Re = Get_Buf_Bit((INT8U *)pSrc, SrcLen, i);
        else if(Screen_Color_Num EQ 2) //˫ɫ��
          Re = Get_Buf_Bit((INT8U *)pSrc, SrcLen, ((i>>3)<<4) + (i & 0x07)) +\
            (Get_Buf_Bit((INT8U *)pSrc, SrcLen, ((i>>3)<<4) + 8 + (i & 0x07))<<1);
        else if(Screen_Color_Num EQ 3) //��ɫ��
          Re = Get_Buf_Bit((INT8U *)pSrc, SrcLen, (i>>3)*24 + (i & 0x07)) +\
            (Get_Buf_Bit((INT8U *)pSrc, SrcLen, (i>>3)*24 + 8 + (i & 0x07))<<1)+
            (Get_Buf_Bit((INT8U *)pSrc, SrcLen, (i>>3)*24 + 16 + (i & 0x07))<<2);

        Set_Area_Point_Data(pDst, Area_No, X + X0, Y + Y0, Re);
     }
  }

  return i*Screen_Color_Num/8;
*/
  //Diff = X % 8; //������ʾ��������8��һ��ƫ��
  //Mask = Bit_Mask(X % 8);

  for(i = 0; i < SrcLen*8/Screen_Color_Num && (i + Off0)<Len*8/Screen_Color_Num;)
  {
      X0 = (Off + i) % Row_Points;
      Y0 = (Off + i) / Row_Points;

      if(Y0 < Height)
      {
          Index = Get_Area_Point_Index(Area_No, X + X0, Y + Y0); //�ĵ���������Ļ������

          Bit = Index % 8; //�ֽ��ڵ�λƫ��
          pData = pDst->Color_Data + (Index >> 3)*Screen_Color_Num; //��Ӧ��Ŀ�껺�����е�λ��,���ֽ��ڵ�ƫ���� Index % 8;

          Mask = Bit_Mask[Bit] + (((INT16U)Bit_Mask[8 - Bit])<<(8 + Bit)); //�����������˹�8λ���ݣ��м����Data
          if(X0 + 8 > Width) //Խ��
          {
              Mask |= (INT16U)(~((INT16U)Bit_Mask[Width - X0]));// << (8 + Bit);
          }

          Data0 = pSrc[(i >> 3) * Screen_Color_Num]; //�����ݷ���pDataָ����ڴ��Bitλ��ʼ����8λ
          Data0 = Data0 << Bit; //16λ����

          *(INT8U *)&Data1 = *pData;
          *((INT8U *)&Data1 + 1) = *(pData + Screen_Color_Num);

          Data1 = (Data1 & Mask) + Data0;

          *pData = *(INT8U *)&Data1;
          *(pData + Screen_Color_Num) = *((INT8U *)&Data1 + 1);

          if(Screen_Color_Num > 1) //˫ɫ����ɫ��
          {
              Data0 = pSrc[(i >> 3) * Screen_Color_Num + 1]; //�����ݷ���pDataָ����ڴ��Bitλ��ʼ����8λ
              Data0 = Data0 << Bit; //16λ����

              pData ++;

              *(INT8U *)&Data1 = *pData;
              *((INT8U *)&Data1 + 1) = *(pData + Screen_Color_Num);

              Data1 = (Data1 & Mask) + Data0;

              *pData = *(INT8U *)&Data1;
              *(pData + Screen_Color_Num) = *((INT8U *)&Data1 + 1);

	           if(Screen_Color_Num > 2) //��ɫ��
	           {
	              Data0 = pSrc[(i >> 3) * Screen_Color_Num + 2]; //�����ݷ���pDataָ����ڴ��Bitλ��ʼ����8λ
	              Data0 = Data0 << Bit; //16λ����
	
	              pData ++;
	
	              *(INT8U *)&Data1 = *pData;
	              *((INT8U *)&Data1 + 1) = *(pData + Screen_Color_Num);
	
	              Data1 = (Data1 & Mask) + Data0;
	
	              *pData = *(INT8U *)&Data1;
	              *(pData + Screen_Color_Num) = *((INT8U *)&Data1 + 1);
	          }
          }
     }

      i+=8;

  }

  return i*Screen_Color_Num/8;
}

/*
//����һ������
void Copy_Filled_Rect(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len,\
  S_Show_Data *pDst_Buf, S_Point *pPoint1, INT8U Flag)
{
  INT16U i,j,X0,Y0,X1,Y1;
  INT8U Value;
  INT32U Index0, Index1;
  INT32U Temp;
  INT16U Area_Width, Area_Height;

  Area_Width = Get_Area_Width(Area_No);
  Area_Height = Get_Area_Height(Area_No);

  //Դ���ж�
  if(Area_No < MAX_AREA_NUM)
  {
     X0 = Prog_Para.Area[Area_No].X + pPoint0->X;
     Y0 = Prog_Para.Area[Area_No].Y + pPoint0->Y;
  }
  else if(Area_No EQ MAX_AREA_NUM)
  {
      X0 = pPoint0->X;
      Y0 = pPoint0->Y;
  }
  else
  {
      ASSERT_FAILED();
      return;
  }

  if(X0 >= Area_Width || Y0 >= Area_Height)
    return;

  if(X0 + X_Len >= Area_Width)
      X_Len = Area_Width - X0;
  if(Y0 + Y_Len >= Area_Height)
      Y_Len = Area_Height - Y0;

  //Ŀ����ж�
  if(Area_No < MAX_AREA_NUM)
  {
     X1 = Prog_Para.Area[Area_No].X + pPoint1->X;
     Y1 = Prog_Para.Area[Area_No].Y + pPoint1->Y;
  }
  else if(Area_No EQ MAX_AREA_NUM)
  {
      X1 = pPoint1->X;
      Y1 = pPoint1->Y;
  }
  else
  {
      ASSERT_FAILED();
      return;
  }


  if(X1 >= Area_Width || Y1 >= Area_Height)
    return;

  if(X1 + X_Len >= Area_Width)
      X_Len = Area_Width - X1;
  if(Y1 + Y_Len >= Area_Height)
      Y_Len = Area_Height - Y1;

  if(Screen_Status.Color_Num < 2)
  {
      for(i = 0; i < X_Len;  i++)
      {
       if((Flag & SCAN_DIS_FLAG) != 0)
         SCAN_INT_DISABLE(); //��ɨ���ж�

       for(j = 0; j < Y_Len; j++)
       {
         if((Flag & REV_FLAG) != 0)
         {
           Index0 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X0 + X_Len - 1 - i,Y0 + Y_Len - 1 - j);
           Index1 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X1 + X_Len - 1 - i,Y1 + Y_Len - 1 - j);
         }
         else
         {
           Index0 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X0 + i,Y0 + j);
           Index1 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X1 + i,Y1 + j);
         }

         Value = GET_BUF_BIT(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data),Index0);
         SET_BUF_BIT(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data),Index1, (Value & 0x01));
       }

       if((Flag & SCAN_DIS_FLAG) != 0)
         SCAN_INT_ENABLE();
      }
    }
    else if(Screen_Status.Color_Num EQ 2)
    {
        for(i = 0; i < X_Len;  i++)
        {
         if((Flag & SCAN_DIS_FLAG) != 0)
             SCAN_INT_DISABLE();

         for(j = 0; j < Y_Len; j++)
         {
             if((Flag & REV_FLAG) != 0)
             {
               Index0 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X0 + X_Len - 1 - i,Y0 + Y_Len - 1 - j);
               Index1 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X1 + X_Len - 1 - i,Y1 + Y_Len - 1 - j);
             }
             else
             {
               Index0 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X0 + i,Y0 + j);
               Index1 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X1 + i,Y1 + j);
             }

            Temp = ((Index0>>3)<<4);

            Value = GET_BUF_BIT(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), Temp + (Index0 & 0x07)) +\
                  (GET_BUF_BIT(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), Temp + 8 + (Index0 & 0x07))<<1);

            SET_BUF_BIT(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), Index1 , (Value & 0x01));
            SET_BUF_BIT(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), Index1 + 8, (Value & 0x02)>>1);
        }

       if((Flag & SCAN_DIS_FLAG) != 0)
            SCAN_INT_ENABLE();
       }
    }
    else if(Screen_Status.Color_Num EQ 3)
    {
        for(i = 0; i < X_Len;  i++)
        {
         if((Flag & SCAN_DIS_FLAG) != 0)
             SCAN_INT_DISABLE();

         for(j = 0; j < Y_Len; j++)
         {
             if((Flag & REV_FLAG) != 0)
             {
               Index0 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X0 + X_Len - 1 - i,Y0 + Y_Len - 1 - j);
               Index1 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X1 + X_Len - 1 - i,Y1 + Y_Len - 1 - j);
             }
             else
             {
               Index0 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X0 + i,Y0 + j);
               Index1 = GET_POINT_INDEX(Screen_Para.Base_Para.Width,X1 + i,Y1 + j);
             }
            Temp = (Index0>>3)*24;

            Value = GET_BUF_BIT(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), Temp + (Index0 & 0x07)) +\
             (GET_BUF_BIT(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), Temp + 8 + (Index0 & 0x07))<<1)+\
             (GET_BUF_BIT(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), Temp + 16 + (Index0 & 0x07))<<2);

            SET_BUF_BIT(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), Index1 , (Value & 0x01));
            SET_BUF_BIT(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), Index1 + 8, (Value & 0x02)>>1);
            SET_BUF_BIT(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), Index1 + 16, (Value & 0x04)>>2);
        }

       if((Flag & SCAN_DIS_FLAG) != 0)
            SCAN_INT_ENABLE();
       }
    }
    else
    {
        ASSERT_FAILED();
    }
}
*/
void Clear_Rect(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint, INT16U X_Len, INT16U Y_Len)
{
    //INT16U i,j;
    //INT8U Data;
/*
    for(i = 0; i < X_Len;  i++)
      for(j = 0; j < Y_Len; j++)
      {
        //Data = Get_Area_Point_Data(pSrc_Buf, Area_No, pPoint0->X + i, pPoint0->Y + j);
        Set_Area_Point_Data(pDst_Buf, Area_No, pPoint->X + i, pPoint->Y + j, 0);
      }
      */
    Fill_Rect(pDst_Buf, Area_No, pPoint, X_Len, Y_Len, 0);
}

//����һ������ľ��ο�Stretch_X_Len��ʾ���ƺ���Ŀ����ʾ�����п�ȣ�Stretch_Y_Len��ʾĿ�껺���еĸ߶�,Stretch_Direct��ʾ����ķ���,0��ʾ����1��ʾ����
//pPoint1��ʾ��Ŀ���е�
void Copy_Filled_Stretch_Rect(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len, INT8U Stretch_X_Fac, INT8U Stretch_Y_Fac,\
                              S_Show_Data *pDst_Buf, S_Point *pPoint1)
{
    INT16U i,j;//,m,n;
    INT8U Re;
	S_Point P0;

    for(i = 0; i < X_Len; i ++)
      for(j = 0; j < Y_Len; j ++)
      {
        Re = Get_Area_Point_Data(pSrc_Buf, Area_No, pPoint0->X + i, pPoint0->Y + j);
		
		P0.X = pPoint1->X + i*Stretch_X_Fac;
		P0.Y = pPoint1->Y + j*Stretch_Y_Fac;

		Fill_Rect(pDst_Buf, Area_No, &P0, Stretch_X_Fac, Stretch_Y_Fac, Re); 
		/*
        for(m = 0; m < Stretch_X_Fac; m ++)
        {
            for(n = 0; n < Stretch_Y_Fac; n ++)
            {
             Set_Area_Point_Data(pDst_Buf, Area_No, pPoint1->X + i*Stretch_X_Fac + m, pPoint1->Y + j*Stretch_Y_Fac + n, Re);
            }
        }
		*/
    }


}

//������һ������
void Rev_Copy_Filled_Rect0(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len,\
  S_Show_Data *pDst_Buf, S_Point *pPoint1)
{
  //INT16U i,j;
  INT32S i,j;
  INT8U Data;
  
  for(i = 0; i < X_Len;  i++)
  {
    SCAN_INT_DISABLE();
    for(j = 0; j < Y_Len; j++)
    {
      Data = Get_Area_Point_Data(pSrc_Buf, Area_No, pPoint0->X + (X_Len - 1 - i), pPoint0->Y + (Y_Len - 1 -j));
      Set_Area_Point_Data(pDst_Buf, Area_No, pPoint1->X + (X_Len - 1 - i), pPoint1->Y + (Y_Len - 1 -j), Data);
    }
    SCAN_INT_ENABLE();
  }
}

//������һ������
void Rev_Copy_Filled_Rect(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len,\
  S_Show_Data *pDst_Buf, S_Point *pPoint1)
{
  //INT16U i,j;
  INT32S i,j;
  INT8U Data;
  
  for(i = 0; i < X_Len;  i++)
    for(j = 0; j < Y_Len; j++)
    {
      Data = Get_Area_Point_Data(pSrc_Buf, Area_No, pPoint0->X + (X_Len - 1 - i), pPoint0->Y + (Y_Len - 1 -j));
      Set_Area_Point_Data(pDst_Buf, Area_No, pPoint1->X + (X_Len - 1 - i), pPoint1->Y + (Y_Len - 1 -j), Data);
    } 
}

//���һ������
void Fill_Rect(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len,INT8U Value)
{
/*
  INT16U i,j;
  //INT8U Data;
  
  for(i = 0; i < X_Len;  i++)
    for(j = 0; j < Y_Len; j++)
    {
      //Data = Get_Area_Point_Data(pSrc_Buf, Area_No, i, j); 
      Set_Area_Point_Data(pDst_Buf, Area_No, pPoint0->X + i, pPoint0->Y + j, Value);
    }
  */

    INT32U Index1;
    INT16U Len, i,j,Mask,X0,X1,Y0,Width,Height;//,Y1;
    INT8U *pDst;

    if(X_Len EQ 0 || Y_Len EQ 0)
        return;

        //GPIO_SetBits(GPIOB,GPIO_Pin_9); //�������
    ///-----------�жϲ�������ȷ��---------------
        X0 = pPoint0->X; //Դ������������Ļ�е���ʼλ��
        Y0 = pPoint0->Y; //Դ������������Ļ�е���ʼλ��

        if(Area_No < MAX_AREA_NUM)
        {
            Width = Prog_Para.Area[Area_No].X_Len;
            Height = Prog_Para.Area[Area_No].Y_Len;
        }
        else
        {
            Width = Screen_Para.Base_Para.Width;
            Height = Screen_Para.Base_Para.Height;
        }

        if(X0 >= Width || Y0 >= Height)
            return;

        if(X0 + X_Len >= Width)
            X_Len = Width - X0;

        if(Y0 + Y_Len >= Height)
            Y_Len = Height - Y0;

    ///---------------------------------------------

    if(Area_No < MAX_AREA_NUM)
      X1 = Prog_Para.Area[Area_No].X + pPoint0->X; //��������Ļ�е�λ��
    else
      X1 = pPoint0->X; //��������Ļ�е�λ��

    //Y1 = Prog_Para.Area[Area_No].Y + pPoint0->Y;

    //Diff = 0;

    if(X_Len > (8 - (X1 % 8)) + (((X1 + X_Len - 1) % 8) + 1))
      Len = (X_Len - (8 - (X1 % 8)) - (((X1 + X_Len - 1) % 8) + 1))/8; //ÿ�е��ֽ�������ȥͷ��β���ֽ�,ͷ��β��Ҫ���⴦��
    else
    {
      Len = 0;
      //return;
    }
    //Ŀ����Show_Data������Ҫ���⴦��
    Width = Screen_Status.Color_Num;//GET_COLOR_NUM(Screen_Para.Base_Para.Color);
    //qDebug("len = %d",Len);


    for(i = 0; i < Y_Len; i ++)
    {
        Index1 = Get_Area_Point_Index(Area_No, pPoint0->X, pPoint0->Y + i); //Դ������

        pDst = pDst_Buf->Color_Data + (Index1 >> 3)*Screen_Status.Color_Num;

        //��һ���ֽ����⴦��
        Mask = Bit_Mask[X1 & 0x07];

        if((X1 + X_Len - 1) /8 <= X1 / 8) //���Ŀ��������һ���ֽڿ���ڣ���Ӧ��
          Mask = Bit_Mask[X1 & 0x07] + (Bit_Mask[7 - ((X1 + X_Len - 1) & 0x07)] << (((X1 + X_Len - 1) & 0x07) + 1));// Data = ((Data << (7 - ((X0 + X_Len -1) % 8))) >> (7 - ((X0 + X_Len -1) % 8))) >> Diff;

        if(GET_BIT(Value, 0))
          *pDst = (*pDst & Mask)  + (0xFF & ~Mask); //����*pDst�ĵ�λ
        else
          *pDst = (*pDst & Mask);

        if(Screen_Status.Color_Num > 1)
        {
          if(GET_BIT(Value, 1))
            *(pDst + 1) = (*(pDst + 1) & Mask)  + (0xFF & ~Mask); //����*pDst�ĵ�λ
          else
            *(pDst + 1) = (*(pDst + 1) & Mask);
        }

        for(j = 0; j < Len; j ++)
        {
            pDst += Width;

            if(GET_BIT(Value, 0))
              *pDst = 0xFF;
            else
              *pDst = 0;


            if(Screen_Status.Color_Num > 1)
            {
                if(GET_BIT(Value, 1))
                  *(pDst + 1) = 0xFF;
                else
                  *(pDst + 1) = 0;
            }
        }

        //���һ���ֽ����⴦��
        if((X1 + X_Len - 1) /8 > X1 / 8)
        {
            pDst += Width;

            Mask = Bit_Mask[((X1 + X_Len - 1) & 0x07) + 1];

            if(GET_BIT(Value, 0))
              *pDst = ((*pDst) & ~Mask)  + (0xFF & Mask);
            else
              *pDst = (*pDst) & ~Mask;

           if(Screen_Status.Color_Num > 1)
            {
              if(GET_BIT(Value, 1))
                *(pDst + 1) = ((*(pDst + 1)) & ~Mask)  + (0xFF & Mask);
              else
                *(pDst + 1) = (*(pDst + 1)) & ~Mask;
            }
        }
    }
}


//���һ��Բ��
//pDst_Buf, Ŀ����ʾ����
//Area_No, ������
//pCenter,Բ���ĵ�
//Radius,�뾶
//Value,��ɫ
void Fill_Round(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pCenter, INT16U Radius, INT8U Value)
{
  S_Point Up, Down;
  INT16U Temp,X;
  INT32S Temp0;
  
  X = pCenter -> X - Radius + 1; //�����һ���X����
  
  for(; X < pCenter -> X + Radius; X ++)
  {
    Temp0 = ((INT32S)Radius * Radius - ((INT32S)X - (INT32S)pCenter->X)*((INT32S)X - (INT32S)pCenter->X));
    Temp = (INT16U)sqrt(Temp0);//Sqrt(Temp0);
    //����һ��
    Up.Y = pCenter->Y + Temp - 1;
    Up.X = X;
    //����һ��
    if(pCenter->Y >= Temp )
      Down.Y = pCenter->Y- Temp + 1;
    else
      Down.Y = 0;
    Down.X = X;
    Draw_Line(pDst_Buf, Area_No, &Down, &Up, Value);
  }
}

//����һ��ʵ��Բ
//pSrc_Buf,Դ��ʾ����
//Area_No,������
//pCenter0,Դ���ĵ�
//Radius,�뾶
//pDst_Buf,Ŀ�껺��
//pCenter,Ŀ�����ĵ�
void Copy_Filled_Round(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pCenter0, INT16U Radius, S_Show_Data *pDst_Buf, S_Point *pCenter1)
{
  S_Point Up, Down,Temp;
  INT16U X,Temp1;
  
  X = pCenter0 -> X - Radius + 1; //�����һ���X����
  
  for(; X < pCenter0 -> X + Radius; X ++)
  {
    Temp1 = (INT16U)sqrt((float)(Radius * Radius - (INT16U)((INT32S)X - (INT32S)pCenter0->X)*((INT32S)X - (INT32S)pCenter0->X)));
    //����һ��
    Up.Y = pCenter0->Y + Temp1 - 1;
    Up.X = X;
    //����һ��
    Down.Y = pCenter0->Y- Temp1 + 1;
    Down.X = X;
    
    Temp.X = (INT16U)((INT32S)Up.X + (INT32S)(pCenter1 -> X) - (INT32S)(pCenter0 -> X));
    Temp.Y = (INT16U)((INT32S)Up.Y + (INT32S)(pCenter1 -> Y) - (INT32S)(pCenter0 -> Y));
    
    Copy_Line(pSrc_Buf,Area_No, &Up, &Down, pDst_Buf, &Temp);
  }
}


//----------------------����ʵ�ָ�����ʾЧ��----------------------
//�ҵ���һ���㣬����Angle�Ƕ�����Len����һ����
//
void Get_Angle_Point(S_Point *pPoint0, INT16S Angle, INT16U Len, S_Point *pPoint1)
{
    INT16S Temp;
    double Re;

    if(Len >=1)
    {
      Re = (Len-1) * cos(2*PI*Angle/360);// + 0.5;
      Temp = (INT16S)((double)pPoint0->X + Re + 0.5);
      pPoint1->X = Temp>0?(INT16U)Temp:0;

      Re = (Len-1) * sin(2*PI*Angle/360);// + 0.5;
      Temp = (INT16S)((double)pPoint0->Y - Re + 0.5);
      pPoint1->Y = Temp>0?(INT16U)Temp:0;
    }
    else
    {
      pPoint1 -> X = pPoint0 -> X;
      pPoint1 -> Y = pPoint0 -> Y;
    }
}

//pDst_Buf,��ʾĿ�껺����
//Area_No, ��ʾ����
//pCenter,ʱ������
//Angle,�Ƕ�,-359->359
//Len,�����������ĵĳ���
//Radius,��İ뾶
//Value,���ֵҲ������ɫ
void Fill_Clock_Point(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pCenter, \
                      INT16S Angle, INT16U Len, INT16U Radius, INT8U Style, INT8U Value)
{
   S_Point Point[5];
   INT8U Hour;
   
   Get_Angle_Point(pCenter, Angle, Len, &Point[0]); //�ҵ�Բ�����ĵ�

   if(Style EQ 0) //Բ��
     Fill_Round(pDst_Buf, Area_No, &Point[0], Radius, Value); //����һ��Բ
   else if(Style EQ 1) //����
   {
     Point[0].X = Point[0].X - Radius + 1;
     Point[0].Y = Point[0].Y - Radius + 1;
     if(Radius > 0)
       Fill_Rect(pDst_Buf, Area_No, &Point[0], Radius*2-1, Radius*2-1, Value);
   }
   else if(Style EQ 2) //����
   {
    if(Radius > 0)
    {
        Get_Angle_Point(pCenter, Angle, Len * 8 / 10, &Point[0]); //ǰ�˵Ķ���
        Get_Angle_Point(&Point[0], Angle - 90, Radius, &Point[1]);
        Get_Angle_Point(&Point[0], Angle + 90, Radius, &Point[4]);

        Get_Angle_Point(pCenter, Angle, Len + Radius/2, &Point[0]); //ǰ�˵Ķ���
        Get_Angle_Point(&Point[0], Angle - 90, Radius, &Point[2]);
        Get_Angle_Point(&Point[0], Angle + 90, Radius, &Point[3]);

        Fill_Polygon(pDst_Buf, Area_No, &Point[1], 4, Value);
    }
   }
   else if(Style EQ 3) //����
   {
     Point[0].X = Point[0].X - Get_Font_Width(FONT0)/2;
     Point[0].Y = Point[0].Y - Get_Font_Height(FONT0)/2;;

     Hour = ((360 - Angle)/(360/12) + 3) % 12;
     if(Hour EQ 0)
         Hour = 12;

     if(Hour EQ 12)
       LED_Print(FONT0, Value, pDst_Buf, Area_No, Point[0].X - FONT0_WIDTH/2, Point[0].Y, "%d", Hour);
     else
       LED_Print(FONT0, Value, pDst_Buf, Area_No, Point[0].X, Point[0].Y, "%d", Hour);

   }
}

//����ʱ�ӵ�ʱ�ӡ�������
//pDst_Buf,Ŀ�껺����
//Area_No,������
//pCenterʱ������
//Angle ʱ���ߵĽǶ�0-359
//Len ʱ���ߵĳ���
//width ʱ���ߵĿ��
//Value ʱ���ߵ���ɫ
void Fill_Clock_Line(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pCenter, \
                     INT16S Angle, INT16U Len, INT16U Width, INT8U Value)
{
  S_Point Point0, Point1, Point2;

  if(Width EQ 0)
      return;

  Get_Angle_Point(pCenter, Angle, Len * 7 / 10, &Point0); //ǰ�˵Ķ���
  Get_Angle_Point(pCenter, Angle - 90, Width, &Point1);
  Get_Angle_Point(pCenter, Angle + 90, Width, &Point2);

  Fill_Triangle(pDst_Buf, Area_No, &Point1, &Point2, &Point0, Value);

  Get_Angle_Point(pCenter, Angle + 180, Len * 3 / 10, &Point0); //��˵Ķ���
  //Get_Angle_Point(pCenter, Angle + 180 - 90, Width, &Point1);
  //Get_Angle_Point(pCenter, Angle + 180 + 90, Width, &Point2);
  
  Fill_Triangle(pDst_Buf, Area_No, &Point1, &Point2, &Point0, Value);
}

//���ĳ����������ʾ
//pDst_Buf��ʾ������
void Clear_Area_Data(S_Show_Data *pDst_Buf, INT8U Area_No)
{
  INT16U X_Len,Y_Len;
  S_Point P0;

  X_Len = Get_Area_Width(Area_No);
  Y_Len = Get_Area_Height(Area_No);
/*
  for(X = 0; X < X_Len; X++)
    for(Y = 0; Y < Y_Len; Y++)
    {
      Set_Area_Point_Data(pDst_Buf, Area_No, X, Y, 0);
    }
 */
  P0.X = 0;
  P0.Y = 0;

  Fill_Rect(pDst_Buf, Area_No, &P0, X_Len, Y_Len, 0);
}

void Move_Up(INT8U Area_No)
{
  S_Point Temp;
  S_Point Temp1;
  
  Temp.X = 0;//Prog_Para.Area[Area_No].X;
  Temp.Y = 0;//Prog_Para.Area[Area_No].Y;
  
  Temp1.X = 0;//Prog_Para.Area[Area_No].X;// + Step +
  Temp1.Y = Prog_Para.Area[Area_No].Y_Len - Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
  //���������ݿ�������ʾ��
  Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step,\
    &Show_Data, &Temp1, SCAN_DIS_FLAG);
  
}

//��������
void Move_Up_Continuous(INT8U Area_No)//���ƶ�
{
  S_Point Temp;
  S_Point Temp1;
  
  INT16U Step_Len;


    Step_Len = Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step - (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;


    Temp.X = 0;
    Temp.Y = Step_Len;//MOVE_STEP * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;

    Temp1.X = 0;//Prog_Para.Area[Area_No].X;
    Temp1.Y = 0;//Prog_Para.Area[Area_No].Y;
    //��ʾ����������
    if(Prog_Status.Area_Status[Area_No].Step + MOVE_STEP <= Prog_Status.Area_Status[Area_No].Max_Step)
      Copy_Filled_Rect(&Show_Data, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len - (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step,\
                       &Show_Data, &Temp1, SCAN_DIS_FLAG);

    Move_Up(Area_No);
  //}
}

void Move_Down(INT8U Area_No)
{
  S_Point Temp;
  S_Point Temp1; 
  
  Temp.X = 0;//Prog_Para.Area[Area_No].X;// + Step +
  Temp.Y = Prog_Para.Area[Area_No].Y_Len - Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
  
  Temp1.X = 0;//Prog_Para.Area[Area_No].X;
  Temp1.Y = 0;//Prog_Para.Area[Area_No].Y;
  
  Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step,\
    &Show_Data, &Temp1, SCAN_DIS_FLAG);
  
}

//��������
void Move_Down_Continuous(INT8U Area_No)
{
  S_Point Temp;
  S_Point Temp1;

  //if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step) //�Ƿ��Ѿ��ƶ����Prog_Status.Area_Status[Area_No].Max_Step%
  {
    Temp.X = 0;
    Temp.Y = (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    
    Temp1.X = 0;
    Temp1.Y = Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
      
    //��ʾ����������
    if(Prog_Status.Area_Status[Area_No].Step + MOVE_STEP <= Prog_Status.Area_Status[Area_No].Max_Step)
      Copy_Filled_Rect(&Show_Data, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len - (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step,\
                       &Show_Data, &Temp1, REV_FLAG | SCAN_DIS_FLAG);
 
    Move_Down(Area_No);
  } 
}

//����
void Move_Left(INT8U Area_No)
{
  S_Point Temp;
  S_Point Temp1;
  INT16U Moved_Len;

  Temp.X = 0;//Prog_Para.Area[Area_No].X;
  Temp.Y = 0;//Prog_Para.Area[Area_No].Y;
  
  Moved_Len = Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;
  Temp1.X = Prog_Para.Area[Area_No].X_Len - Moved_Len;// + Step +
  Temp1.Y = 0;
  
  Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Moved_Len,Prog_Para.Area[Area_No].Y_Len, \
    &Show_Data, &Temp1, SCAN_DIS_FLAG);
   
}

void Move_Show_RightNow(INT8U Area_No)
{
    S_Point Temp;

    Temp.X = 0;
    Temp.Y = 0;
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len,\
                     &Show_Data, &Temp,0);

}

//��������
void Move_Left_Continuous(INT8U Area_No)
{
  S_Point Temp;
  S_Point Temp1;
  INT16U Step_Len;

  //GPIO_SetBits(GPIOB,GPIO_Pin_1); //�������
  Step_Len = Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step - (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;

  Temp.X = Step_Len;
  Temp.Y = 0; 

  Temp1.X = 0;//Prog_Para.Area[Area_No].X;
  Temp1.Y = 0;//Prog_Para.Area[Area_No].Y;   
  //��ʾ����������
  
  if(Prog_Status.Area_Status[Area_No].Step + MOVE_STEP <= Prog_Status.Area_Status[Area_No].Max_Step)
    Copy_Filled_Rect(&Show_Data, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len - (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step, Prog_Para.Area[Area_No].Y_Len,\
                     &Show_Data, &Temp1, SCAN_DIS_FLAG);
  
  Move_Left(Area_No);
}

//����
void Move_Right(INT8U Area_No)
{
  S_Point Temp;
  S_Point Temp1;
  INT16U Moved_Len;

  Moved_Len = Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;
  Temp.X = Prog_Para.Area[Area_No].X_Len - Moved_Len;//(Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step) * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;// + Step +
  Temp.Y = 0;
  
  Temp1.X = 0;//Prog_Para.Area[Area_No].X;
  Temp1.Y = 0;//Prog_Para.Area[Area_No].Y;
  
  Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp,  Moved_Len,Prog_Para.Area[Area_No].Y_Len,\
    &Show_Data, &Temp1, SCAN_DIS_FLAG);

}

//��������
void Move_Right_Continuous(INT8U Area_No)
{
  S_Point Temp;
  S_Point Temp1;
  INT16U Step_Len;

  Temp.X = (Prog_Status.Area_Status[Area_No].Step -MOVE_STEP) * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;
  Temp.Y = 0; 

  Step_Len = Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step - (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;
  Temp1.X = Temp.X + Step_Len;//(Prog_Status.Area_Status[Area_No].Step + MOVE_STEP) * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;;
  Temp1.Y = 0;  
   
  //��ʾ����������
  if(Prog_Status.Area_Status[Area_No].Step + MOVE_STEP <= Prog_Status.Area_Status[Area_No].Max_Step)
    Copy_Filled_Rect(&Show_Data, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len - Temp.X, Prog_Para.Area[Area_No].Y_Len,\
                     &Show_Data, &Temp1, REV_FLAG | SCAN_DIS_FLAG);

  Move_Right(Area_No);
}

//�ϸ���
void Move_Up_Cover(INT8U Area_No)
{
  S_Point Temp;
  
  //if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step) //�Ƿ��Ѿ��ƶ����Prog_Status.Area_Status[Area_No].Max_Step%
  {
    Temp.X = 0;// + (Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step) * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    Temp.Y = Prog_Para.Area[Area_No].Y_Len - Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, MOVE_STEP * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step,\
      &Show_Data, &Temp,0);
    //Prog_Status.Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//�¸���
void Move_Down_Cover(INT8U Area_No)
{
  S_Point Temp;
  
  //if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step) //�Ƿ��Ѿ��ƶ����Prog_Status.Area_Status[Area_No].Max_Step%
  {
    Temp.X = 0;// + Step +
    Temp.Y = (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;// + Step +
  
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, MOVE_STEP * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step,\
      &Show_Data, &Temp,0);
    //Prog_Status.Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//�󸲸�
void Move_Left_Cover(INT8U Area_No)
{
  S_Point Temp;
  
  //if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step) //�Ƿ��Ѿ��ƶ����Prog_Status.Area_Status[Area_No].Max_Step%
  {
    Temp.X = Prog_Para.Area[Area_No].X_Len - Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;// + Step +
    Temp.Y = 0;
    
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, MOVE_STEP * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step, Prog_Para.Area[Area_No].Y_Len,\
      &Show_Data, &Temp,0);
    //Prog_Status.Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//�Ҹ���
void Move_Right_Cover(INT8U Area_No)
{
  S_Point Temp;
  //S_Point Temp1;
  
  //if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step) //�Ƿ��Ѿ��ƶ����Prog_Status.Area_Status[Area_No].Max_Step%
  {
    Temp.X = (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;// + Step +
    Temp.Y = 0;
    
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, MOVE_STEP * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step, Prog_Para.Area[Area_No].Y_Len,\
      &Show_Data, &Temp,0);
    //Prog_Status.Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//���ϸ���
void Move_Left_Up_Cover(INT8U Area_No)
{
  S_Point Point[2];
  //INT8U i = 0;
  INT16U Area_Width, Area_Height,Step_Len,Len0, Len1;

  Area_Width = Get_Area_Width(Area_No);
  Area_Height = Get_Area_Height(Area_No);
  Len0 = (Area_Width + Area_Height) * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) / Prog_Status.Area_Status[Area_No].Max_Step;
  Len1 = (Area_Width + Area_Height) * Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step;

  //Step_Len = Area_Width + Area_Height;
/*
  if(Step_Len > Area_Height)
  {
    Point[i].X = Area_Width + Area_Height - Step_Len;
    Point[i].Y = 0;
    i ++;

    Point[i].X = Area_Width;
    Point[i].Y = 0;
    i ++;
  }
  else
  {
    Point[i].X = Area_Width;
    Point[i].Y = Area_Height - Step_Len;
    i ++;
  }

  Point[i].X = Area_Width;
  Point[i].Y = Area_Height;
  i++;

  if(Step_Len < Area_Width)
  {
    Point[i].X = Area_Width - Step_Len;
    Point[i].Y = Area_Height;
    i ++;
  }
  else
  {
    Point[i].X = 0;//Area_Width - Step_Len;
    Point[i].Y = Area_Height;
    i ++;

    Point[i].X = 0;//Area_Width - Step_Len;
    Point[i].Y = Area_Height + Area_Width - Step_Len;
    i ++;
  }

  //i = 3;
  Copy_Filled_Polygon(&Show_Data_Bak, Area_No, &Point[0], i, &Show_Data, &Point[0]);
*/
  for(Step_Len = Len0; Step_Len < Len1; Step_Len ++)
  {
      if(Step_Len > Area_Height)
      {
        Point[0].X = Area_Width + Area_Height - Step_Len;
        Point[0].Y = 0;
      }
      else
      {
        Point[0].X = Area_Width - 1;
        Point[0].Y = Area_Height - Step_Len;
      }

      if(Step_Len < Area_Width)
      {
        Point[1].X = Area_Width - Step_Len;
        Point[1].Y = Area_Height - 1;
      }
      else
      {
        Point[1].X = 0;//Area_Width - Step_Len;
        Point[1].Y = Area_Height + Area_Width - Step_Len;
      }

      Copy_Line(&Show_Data_Bak, Area_No, &Point[0], &Point[1], &Show_Data, &Point[0]);
  }
}

//���ϸ���
void Move_Right_Up_Cover(INT8U Area_No)
{
    S_Point Point[2];
    //INT8U i = 0;
    INT16U Area_Width, Area_Height,Step_Len, Len0, Len1;

    Area_Width = Get_Area_Width(Area_No);
    Area_Height = Get_Area_Height(Area_No);
    Len0 = (Area_Width + Area_Height) * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) / Prog_Status.Area_Status[Area_No].Max_Step;
    Len1 = (Area_Width + Area_Height) * Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step;
   /*
    //Step_Len = Area_Width + Area_Height;
    Point[i].X = 0;
    Point[i].Y = Area_Height;
    i ++;

    if(Step_Len < Area_Height)
    {
      Point[i].X = 0;
      Point[i].Y = Area_Height - Step_Len;
      i++;
    }
    else//if(Step_Len >= Area_Height)
    {
      Point[i].X = 0;
      Point[i].Y = 0;
      i++;

      Point[i].X = Step_Len - Area_Height;
      Point[i].Y = 0;
      i ++;
    }

    if(Step_Len >= Area_Width)
    {
        Point[i].X = Area_Width;
        Point[i].Y = Area_Width + Area_Height - Step_Len;
        i ++;

        Point[i].X = Area_Width;
        Point[i].Y = Area_Height;
        i ++;
    }
    else
    {
        Point[i].X = Step_Len;
        Point[i].Y = Area_Height;
        i ++;
    }

    //i = 3;
    Copy_Filled_Polygon(&Show_Data_Bak, Area_No, &Point[0], i, &Show_Data, &Point[0]);
   */
    for(Step_Len = Len0; Step_Len < Len1; Step_Len ++)
    {
        if(Step_Len < Area_Height)
        {
          Point[0].X = 0;
          Point[0].Y = Area_Height - Step_Len;
        }
        else//if(Step_Len >= Area_Height)
        {
          Point[0].X = Step_Len - Area_Height;
          Point[0].Y = 0;
        }

        if(Step_Len >= Area_Width)
        {
            Point[1].X = Area_Width - 1;
            Point[1].Y = Area_Width + Area_Height - Step_Len;
        }
        else
        {
            Point[1].X = Step_Len;
            Point[1].Y = Area_Height - 1;
        }

        Copy_Line(&Show_Data_Bak, Area_No, &Point[0], &Point[1], &Show_Data, &Point[0]);
    }
}

//���¸���
void Move_Left_Down_Cover(INT8U Area_No)
{
    S_Point Point[2];
    //INT8U i = 0;
    INT16U Area_Width, Area_Height,Step_Len, Len0, Len1;

    Area_Width = Get_Area_Width(Area_No);
    Area_Height = Get_Area_Height(Area_No);

    Len0 = (Area_Width + Area_Height) * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) / Prog_Status.Area_Status[Area_No].Max_Step;
    Len1 = (Area_Width + Area_Height) * Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step;
/*
    //Step_Len = (Area_Width + Area_Height) * 30 / Prog_Status.Area_Status[Area_No].Max_Step;
    Point[i].X = Area_Width;
    Point[i].Y = 0;
    i ++;

    if(Step_Len < Area_Height)
    {
      Point[i].X = Area_Width;
      Point[i].Y = Step_Len;
      i++;
    }
    else//if(Step_Len >= Area_Height)
    {
      Point[i].X = Area_Width;
      Point[i].Y = Area_Height;
      i++;

      Point[i].X = Area_Width + Area_Height - Step_Len;
      Point[i].Y = Area_Height;
      i ++;
    }

    if(Step_Len >= Area_Width)
    {
        Point[i].X = 0;//Area_Width - 1;
        Point[i].Y = Step_Len - Area_Width;
        i ++;

        Point[i].X = 0;//Area_Width - 1;
        Point[i].Y = 0;//Area_Height - 1;
        i ++;
    }
    else
    {
        Point[i].X = Area_Width - Step_Len;
        Point[i].Y = 0;//Area_Height - 1;
        i ++;
    }

    //i = 3;
    Copy_Filled_Polygon(&Show_Data_Bak, Area_No, &Point[0], i, &Show_Data, &Point[0]);
*/
    for(Step_Len = Len0; Step_Len < Len1; Step_Len ++)
    {
        if(Step_Len < Area_Height)
        {
          Point[0].X = Area_Width - 1;
          Point[0].Y = Step_Len;
        }
        else//if(Step_Len >= Area_Height)
        {
          Point[0].X = Area_Width + Area_Height - Step_Len;
          Point[0].Y = Area_Height - 1;
        }

        if(Step_Len >= Area_Width)
        {
            Point[1].X = 0;//Area_Width - 1;
            Point[1].Y = Step_Len - Area_Width;
        }
        else
        {
            Point[1].X = Area_Width - Step_Len;
            Point[1].Y = 0;//Area_Height - 1;
        }

        Copy_Line(&Show_Data_Bak, Area_No, &Point[0], &Point[1], &Show_Data, &Point[0]);
   }
}

//���¸���
void Move_Right_Down_Cover(INT8U Area_No)
{
    S_Point Point[2];
    //INT8U i = 0;
    INT16U Area_Width, Area_Height,Step_Len,Len0,Len1;

    Area_Width = Get_Area_Width(Area_No);
    Area_Height = Get_Area_Height(Area_No);

    Len0 = (Area_Width + Area_Height) * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) / Prog_Status.Area_Status[Area_No].Max_Step;
    Len1 = (Area_Width + Area_Height) * Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step;
/*
    //Step_Len = (Area_Width + Area_Height) * 30 / Prog_Status.Area_Status[Area_No].Max_Step;
    Point[i].X = 0;
    Point[i].Y = 0;
    i ++;

    if(Step_Len < Area_Width)
    {
      Point[i].X = Step_Len;
      Point[i].Y = 0;
      i++;
    }
    else//if(Step_Len >= Area_Height)
    {
      Point[i].X = Area_Width;
      Point[i].Y = 0;
      i ++;

      Point[i].X = Area_Width;
      Point[i].Y = Step_Len - Area_Width;
      i++;
    }

    if(Step_Len >= Area_Height)
    {
        Point[i].X = Step_Len - Area_Height;//Area_Width - 1;
        Point[i].Y = Area_Height;
        i ++;

        Point[i].X = 0;//Area_Width - 1;
        Point[i].Y = Area_Height;//Area_Height - 1;
        i ++;
    }
    else
    {
        Point[i].X = 0;
        Point[i].Y = Step_Len;//Area_Height - 1;
        i ++;
    }

    //i = 3;
    Copy_Filled_Polygon(&Show_Data_Bak, Area_No, &Point[0], i, &Show_Data, &Point[0]);
*/
    for(Step_Len = Len0; Step_Len < Len1; Step_Len ++)
    {
        if(Step_Len < Area_Width)
        {
          Point[0].X = Step_Len;
          Point[0].Y = 0;
        }
        else//if(Step_Len >= Area_Height)
        {
          Point[0].X = Area_Width - 1;
          Point[0].Y = Step_Len - Area_Width;
        }

        if(Step_Len >= Area_Height)
        {
            Point[1].X = Step_Len - Area_Height;//Area_Width - 1;
            Point[1].Y = Area_Height - 1;
        }
        else
        {
            Point[1].X = 0;
            Point[1].Y = Step_Len;//Area_Height - 1;
        }

         Copy_Line(&Show_Data_Bak, Area_No, &Point[0], &Point[1], &Show_Data, &Point[0]);
   }
}

//��������
void Move_Up_Down_Open(INT8U Area_No)
{
    /*
  S_Point Temp;
  
  //if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step)
  {
    Temp.X = 0;
    Temp.Y = (Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step)*Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*2);
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step, &Show_Data, &Temp);
    //Prog_Status.Area_Status[Area_No].Step += MOVE_STEP;
  }
  */

   S_Point Point[2];

   Point[0].X = 0;
   Point[0].Y = Prog_Para.Area[Area_No].Y_Len / 2;

   //Point[1].X = Prog_Para.Area[Area_No].X_Len - 1;
   //Point[1].Y = Prog_Para.Area[Area_No].Y_Len / 2;

   //Copy_Line(&Show_Data_Bak, Area_No, &Point[0], &Point[1], &Show_Data, &Point[0]);
   Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0], Prog_Para.Area[Area_No].X_Len, MOVE_STEP, &Show_Data, &Point[0],0);

   Point[0].X = 0;
   Point[0].Y = (Prog_Para.Area[Area_No].Y_Len/2  - Prog_Status.Area_Status[Area_No].Step/2);

   Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0], Prog_Para.Area[Area_No].X_Len, MOVE_STEP, &Show_Data, &Point[0],0);

   Point[0].X = 0;
   Point[0].Y = (Prog_Para.Area[Area_No].Y_Len/2  + Prog_Status.Area_Status[Area_No].Step/2);

   Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0], Prog_Para.Area[Area_No].X_Len, MOVE_STEP, &Show_Data, &Point[0],0);
}

//���º���
void Move_Up_Down_Close(INT8U Area_No)
{
  S_Point Temp;
  
  //if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step)
  {
    Temp.X = 0;
    Temp.Y = (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) /2 ;//* Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*2);
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, MOVE_STEP, &Show_Data, &Temp,0);
    
    Temp.X = 0;
    Temp.Y = Prog_Para.Area[Area_No].Y_Len - (Prog_Status.Area_Status[Area_No].Step  + MOVE_STEP) / 2;//* Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*2);
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, MOVE_STEP, &Show_Data, &Temp,0);
    //Prog_Status.Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//���ҿ���
void Move_Left_Right_Open(INT8U Area_No)
{
    S_Point Point[2];

    Point[0].X = Prog_Para.Area[Area_No].X_Len / 2;
    Point[0].Y = 0;

    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0],  MOVE_STEP, Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Point[0],0);

    Point[0].X = (Prog_Para.Area[Area_No].X_Len/2  - Prog_Status.Area_Status[Area_No].Step/2);
    Point[0].Y = 0;

    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0], MOVE_STEP, Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Point[0],0);

    Point[0].X = (Prog_Para.Area[Area_No].X_Len/2  + Prog_Status.Area_Status[Area_No].Step/2);
    Point[0].Y = 0;

    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0], MOVE_STEP, Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Point[0],0);
  
}

//���Һ���
void Move_Left_Right_Close(INT8U Area_No)
{
    S_Point Temp;

    //if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step)
    {
      Temp.X = (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) /2 ;
      Temp.Y = 0;//* Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*2);
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, MOVE_STEP, Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Temp,0);

      Temp.X = Prog_Para.Area[Area_No].X_Len - (Prog_Status.Area_Status[Area_No].Step  + MOVE_STEP) / 2;
      Temp.Y = 0;//* Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*2);
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp,  MOVE_STEP, Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Temp,0);
      //Prog_Status.Area_Status[Area_No].Step += MOVE_STEP;
    }
}

//���Ҿ����
void Move_Left_Right_Reel_Open(INT8U Area_No)
{
    S_Point Point[2];
    INT16U Len;

    Point[0].X = Prog_Para.Area[Area_No].X_Len / 2;
    Point[0].Y = 0;

    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0],  MOVE_STEP, Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Point[0],0);

    Point[0].X = (Prog_Para.Area[Area_No].X_Len/2  - Prog_Status.Area_Status[Area_No].Step/2);
    Point[0].Y = 0;

    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0], MOVE_STEP, Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Point[0],0);

    //-----������----
    if(Point[0].X > MOVE_STEP)
    {
        if(Point[0].X > REEL_WIDTH)
        {
          Point[1].X = Point[0].X - REEL_WIDTH;
          Len = REEL_WIDTH;
        }
        else
        {
          Point[1].X = 0;
          Len = Point[0].X;// - Point[1].X;
        }
        Point[1].Y = 0;
        Fill_Rect(&Show_Data, Area_No, &Point[1], Len, Prog_Para.Area[Area_No].Y_Len, 1);
    }
    //---------------------

    Point[0].X = (Prog_Para.Area[Area_No].X_Len/2  + Prog_Status.Area_Status[Area_No].Step/2);
    Point[0].Y = 0;

    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0], MOVE_STEP, Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Point[0],0);

    //-----������----
    if(Point[0].X + MOVE_STEP < Prog_Para.Area[Area_No].X_Len)
    {
        Point[1].X = Point[0].X + MOVE_STEP;
        if(Point[0].X + MOVE_STEP + REEL_WIDTH < Prog_Para.Area[Area_No].X_Len)
        {
          Len = REEL_WIDTH;
        }
        else
        {
          Len = Prog_Para.Area[Area_No].X_Len - Point[0].X;
        }
        Point[1].Y = 0;
        Fill_Rect(&Show_Data, Area_No, &Point[1], Len, Prog_Para.Area[Area_No].Y_Len, 1);
    }

    //---------------------
}

//���Ҿ���ر�
void Move_Left_Right_Reel_Close(INT8U Area_No)
{
    S_Point Temp[2];
    INT16U Len;

    //if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step)
    {
      Temp[0].X = Prog_Status.Area_Status[Area_No].Step / 2 ;
      Temp[0].Y = 0;//* Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*2);
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp[0], MOVE_STEP, Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Temp[0],0);

      //-----������----
      if(Temp[0].X + MOVE_STEP < Prog_Para.Area[Area_No].X_Len / 2)
      {
          Temp[1].X = Temp[0].X + MOVE_STEP;
          if(Temp[1].X + REEL_WIDTH > Prog_Para.Area[Area_No].X_Len / 2)
            Len = Prog_Para.Area[Area_No].X_Len / 2 - Temp[1].X;
          else
          {
            Len = REEL_WIDTH;
          }
          Temp[1].Y = 0;
          Fill_Rect(&Show_Data, Area_No, &Temp[1], Len, Prog_Para.Area[Area_No].Y_Len, 1);
      }
      //---------------------

      //if(Prog_Status.Area_Status[Area_No].Step  + MOVE_STEP < Prog_Para.Area[Area_No].X_Len)
      Temp[0].X = Prog_Para.Area[Area_No].X_Len - Prog_Status.Area_Status[Area_No].Step / 2;
      Temp[0].Y = 0;//* Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*2);
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp[0],  MOVE_STEP, Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Temp[0],0);
      //Prog_Status.Area_Status[Area_No].Step += MOVE_STEP;
      //-----������----
      if(Temp[0].X  > Prog_Para.Area[Area_No].X_Len / 2 + MOVE_STEP)
      {
          if(Temp[0].X >= Prog_Para.Area[Area_No].X_Len / 2 + REEL_WIDTH)
          {
              Temp[1].X = Temp[0].X - REEL_WIDTH;
              Len = REEL_WIDTH;
          }
          else
          {
              Temp[1].X = Prog_Para.Area[Area_No].X_Len / 2;
              Len = Temp[0].X - Temp[1].X;
          }
          Temp[1].Y = 0;
          Fill_Rect(&Show_Data, Area_No, &Temp[1], Len, Prog_Para.Area[Area_No].Y_Len, 1);
      }

      //---------------------

    }
}
//���¾����
void Move_Up_Down_Reel_Open(INT8U Area_No)
{
    /*
  S_Point Temp;

  //if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step)
  {
    Temp.X = 0;
    Temp.Y = (Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step)*Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*2);
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step, &Show_Data, &Temp);
    //Prog_Status.Area_Status[Area_No].Step += MOVE_STEP;
  }
  */

   S_Point Point[2];
   INT16U Len;

   Point[0].X = 0;
   Point[0].Y = Prog_Para.Area[Area_No].Y_Len / 2;

   //Point[1].X = Prog_Para.Area[Area_No].X_Len - 1;
   //Point[1].Y = Prog_Para.Area[Area_No].Y_Len / 2;

   //Copy_Line(&Show_Data_Bak, Area_No, &Point[0], &Point[1], &Show_Data, &Point[0]);
   Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0], Prog_Para.Area[Area_No].X_Len, MOVE_STEP, &Show_Data, &Point[0],0);

   Point[0].X = 0;
   Point[0].Y = (Prog_Para.Area[Area_No].Y_Len/2  - Prog_Status.Area_Status[Area_No].Step/2);

   Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0], Prog_Para.Area[Area_No].X_Len, MOVE_STEP, &Show_Data, &Point[0],0);
   if(Point[0].Y > MOVE_STEP)
   {
       //-----������----
       if(Point[0].Y > REEL_WIDTH)
       {
         Point[1].Y = Point[0].Y - REEL_WIDTH;
         Len = REEL_WIDTH;
       }
       else
       {
         Point[1].Y = 0;
         Len = Point[0].Y - Point[1].Y;
       }
       Point[1].X = 0;
       Fill_Rect(&Show_Data, Area_No, &Point[1], Prog_Para.Area[Area_No].X_Len, Len, 1);
  }
   //---------------------

   Point[0].X = 0;
   Point[0].Y = (Prog_Para.Area[Area_No].Y_Len/2  + Prog_Status.Area_Status[Area_No].Step/2);

   Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point[0], Prog_Para.Area[Area_No].X_Len, MOVE_STEP, &Show_Data, &Point[0],0);
   //-----������----
   if(Point[0].Y + MOVE_STEP < Prog_Para.Area[Area_No].Y_Len)
   {
       Point[1].Y = Point[0].Y + MOVE_STEP;
       if(Point[0].Y + MOVE_STEP + REEL_WIDTH < Prog_Para.Area[Area_No].Y_Len)
       {
         Len = REEL_WIDTH;
       }
       else
       {
         Len = Prog_Para.Area[Area_No].Y_Len - Point[0].Y;
       }
       Point[1].X = 0;
       Fill_Rect(&Show_Data, Area_No, &Point[1], Prog_Para.Area[Area_No].X_Len, Len, 1);
   }
   //---------------------
}

//���¾���ر�
void Move_Up_Down_Reel_Close(INT8U Area_No)
{
    S_Point Temp[2];
    INT16U Len;

    //if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step)
    {
      Temp[0].X = 0;
      Temp[0].Y = Prog_Status.Area_Status[Area_No].Step/2 ;//* Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*2);
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp[0], Prog_Para.Area[Area_No].X_Len, MOVE_STEP, &Show_Data, &Temp[0],0);
      //-----������----
      if(Temp[0].Y + MOVE_STEP < Prog_Para.Area[Area_No].Y_Len / 2)
      {
          Temp[1].Y = Temp[0].Y + MOVE_STEP;
          if(Temp[1].Y + REEL_WIDTH > Prog_Para.Area[Area_No].Y_Len / 2)
            Len = Prog_Para.Area[Area_No].Y_Len / 2 - Temp[1].Y;
          else
          {
            Len = REEL_WIDTH;
          }
          Temp[1].X = 0;
          Fill_Rect(&Show_Data, Area_No, &Temp[1], Prog_Para.Area[Area_No].X_Len, Len, 1);
      }
      //---------------------
      Temp[0].X = 0;
      Temp[0].Y = Prog_Para.Area[Area_No].Y_Len - Prog_Status.Area_Status[Area_No].Step / 2;//* Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*2);
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp[0], Prog_Para.Area[Area_No].X_Len, MOVE_STEP, &Show_Data, &Temp[0],0);
      //Prog_Status.Area_Status[Area_No].Step += MOVE_STEP;
      //-----������----
      if(Temp[0].Y > Prog_Para.Area[Area_No].Y_Len / 2 + MOVE_STEP)
      {
          if(Temp[0].Y >= Prog_Para.Area[Area_No].Y_Len / 2 + REEL_WIDTH)
          {
              Temp[1].Y = Temp[0].Y - REEL_WIDTH;
              Len = REEL_WIDTH;
          }
          else
          {
              Temp[1].Y = Prog_Para.Area[Area_No].Y_Len / 2;
              Len = Temp[0].Y - Temp[1].Y;
          }
          Temp[1].X = 0;
          Fill_Rect(&Show_Data, Area_No, &Temp[1], Prog_Para.Area[Area_No].X_Len, Len, 1);
      }

      //---------------------
    }
}

//�ж��������Ƿ���һ��ֱ���ϣ�ͬʱpPoint1��pPoint2��pPoint0��ͬһ��
INT8U Check_Point_One_Line(S_Point *pPoint0, S_Point *pPoint1, S_Point *pPoint2)
{
    if(pPoint0->X != pPoint1->X && pPoint0->X != pPoint2->X)
    {
      if(((float)pPoint0->Y - (float)pPoint1->Y)/((float)pPoint0->X - (float)pPoint1->X) <=\
         ((float)pPoint0->Y - (float)pPoint2->Y)/((float)pPoint0->X - (float)pPoint2->X)) //б�����
        {
          if(((INT16S)pPoint0->X - (INT16S)pPoint1->X)*((INT16S)pPoint0->X - (INT16S)pPoint2->X) > 0)
              return 1;
          else
              return 0;
        }
        else
            return 0;
    }
    else
    {
        if(pPoint0->X EQ pPoint1->X && pPoint0->X EQ pPoint2->X)
        {
            if(((INT16S)pPoint0->Y - (INT16S)pPoint1->Y)*((INT16S)pPoint0->Y - (INT16S)pPoint2->Y) > 0)
               return 1;
            else
               return 0;
        }
        else
            return 0;
    }
}

void Get_Spin_Step_Point(INT16U Area_Width, INT16U Area_Height, INT16U Len, S_Point *pPoint)
{
  //INT16U Len;

  //Len = Step;//(Area_Width + Area_Height)*2 * Prog_Status.Area_Status[Area_No].Step/Prog_Status.Area_Status[Area_No].Max_Step;

  pPoint->X = Area_Width / 2 + Len ;
  pPoint->Y = 0;

  if(Len > Area_Width / 2)
  {
    pPoint->X = Area_Width - 1;// + Area_Height / 2 -Len;
    pPoint->Y = Len - Area_Width / 2;
  }

  if(Len > Area_Width / 2 + Area_Height)
  {
    pPoint->X = Area_Width - (Len - Area_Width / 2 - Area_Height);
    pPoint->Y = Area_Height - 1;
  }

  if(Len > Area_Width / 2 + Area_Width + Area_Height)
  {
    pPoint->X = 0;
    pPoint->Y = Area_Height - (Len - (Area_Width / 2 + Area_Width + Area_Height));
  }

  if(Len > Area_Width / 2 + Area_Height + Area_Width + Area_Height)
  {
    pPoint->X = Len - (Area_Width / 2 + Area_Height + Area_Width + Area_Height);
    pPoint->Y = 0;
  }
}

//˳ʱ����ת
void Move_Spin_CW(INT8U Area_No)
{
   //INT16U X,Y;
   //INT16U Arg;
   INT16U Area_Width, Area_Height;
   S_Point Point[3];//,CPoint;
   //INT8U i = 0;
   //INT16U Len;
/*
   Area_Width = Get_Area_Width(Area_No);
   Area_Height = Get_Area_Height(Area_No);

   Len = (Area_Width + Area_Height)*2 * Prog_Status.Area_Status[Area_No].Step/Prog_Status.Area_Status[Area_No].Max_Step;

   Point[i].X = Area_Width / 2;
   Point[i].Y = Area_Height / 2;
   i++;

   Point[i].X = Area_Width ;
   Point[i].Y = Area_Height / 2;
   i++;

   Point[i].X = Area_Width ;
   Point[i].Y = Area_Height / 2 + Len;

   //Get_Angle_Point(&Point[0], 360 - Arg, (Area_Width>Area_Height?Area_Height:Area_Width)/2, &CPoint);

   if(Len > Area_Height / 2)
   {
     Point[i].X = Area_Width;
     Point[i].Y = Area_Height;
     i++;

     Point[i].X = Area_Width + Area_Height / 2 -Len;
     Point[i].Y = Area_Height;
   }

   if(Len > Area_Height / 2 + Area_Width)
   {
     Point[i].X = 0;
     Point[i].Y = Area_Height;
     i++;

     Point[i].X = 0;
     Point[i].Y = Area_Height / 2 + Area_Width + Area_Height - Len;
   }

   if(Len > Area_Height / 2 + Area_Width + Area_Height)
   {
     Point[i].X = 0;
     Point[i].Y = 0;
     i++;

     Point[i].X = Len - (Area_Height / 2 + Area_Width + Area_Height);
     Point[i].Y = 0;
   }

   if(Len > Area_Height / 2 + Area_Width + Area_Height + Area_Width)
   {
     Point[i].X = Area_Width;
     Point[i].Y = 0;
     i ++;

     Point[i].X = Area_Width;
     Point[i].Y = Len - (Area_Height / 2 + Area_Width + Area_Height + Area_Width);
   }

   i++;
   Copy_Filled_Polygon(&Show_Data_Bak, Area_No, &Point[0], i, &Show_Data, &Point[0]);

   return;
 */
   Area_Width = Get_Area_Width(Area_No);
   Area_Height = Get_Area_Height(Area_No);

   Point[0].X = Area_Width / 2;
   Point[0].Y = Area_Height / 2;

   Get_Spin_Step_Point(Area_Width, Area_Height, Prog_Status.Area_Status[Area_No].Step - MOVE_STEP, &Point[1]);
   Get_Spin_Step_Point(Area_Width, Area_Height, Prog_Status.Area_Status[Area_No].Step, &Point[2]);
   //Copy_Line(&Show_Data_Bak, Area_No, &Point[0], &Point[1], &Show_Data, &Point[0]);
   Copy_Filled_Polygon(&Show_Data_Bak, Area_No, &Point[0], 3, &Show_Data, &Point[0]);

   Get_Spin_Step_Point(Area_Width, Area_Height, Prog_Status.Area_Status[Area_No].Step - MOVE_STEP + Area_Width + Area_Height, &Point[1]);
   Get_Spin_Step_Point(Area_Width, Area_Height, Prog_Status.Area_Status[Area_No].Step + Area_Width + Area_Height, &Point[2]);
   //Copy_Line(&Show_Data_Bak, Area_No, &Point[0], &Point[1], &Show_Data, &Point[0]);
   Copy_Filled_Polygon(&Show_Data_Bak, Area_No, &Point[0], 3, &Show_Data, &Point[0]);
}

//��ʱ����ת
void Move_Spin_CCW(INT8U Area_No)
{
    //INT16U X;//,Y;
    //INT16U Arg;
    INT16U Area_Width, Area_Height;
    S_Point Point[3];//,CPoint;
    //INT8U i = 0;
    //INT16U Len;
/*
    Area_Width = Get_Area_Width(Area_No);
    Area_Height = Get_Area_Height(Area_No);

    Len = (Area_Width + Area_Height)*2 * Prog_Status.Area_Status[Area_No].Step/Prog_Status.Area_Status[Area_No].Max_Step;

    Point[i].X = Area_Width / 2;
    Point[i].Y = Area_Height / 2;
    i++;

    Point[i].X = Area_Width;
    Point[i].Y = Area_Height / 2;
    i++;

    Point[i].X = Area_Width;
    Point[i].Y = Area_Height / 2 - Len;

    //Get_Angle_Point(&Point[0], 360 - Arg, (Area_Width>Area_Height?Area_Height:Area_Width)/2, &CPoint);

    if(Len > Area_Height / 2)
    {
      Point[i].X = Area_Width;
      Point[i].Y = 0;
      i++;

      Point[i].X = Area_Width + Area_Height / 2 -Len;
      Point[i].Y = 0;
    }

    if(Len > Area_Height / 2 + Area_Width)
    {
      Point[i].X = 0;
      Point[i].Y = 0;
      i++;

      Point[i].X = 0;
      Point[i].Y = Len - (Area_Height / 2 + Area_Width);
    }

    if(Len > Area_Height / 2 + Area_Width + Area_Height)
    {
      Point[i].X = 0;
      Point[i].Y = Area_Height;
      i++;

      Point[i].X = Len - (Area_Height / 2 + Area_Width + Area_Height);
      Point[i].Y = Area_Height;
    }

    if(Len > Area_Height / 2 + Area_Width + Area_Height + Area_Width)
    {
      Point[i].X = Area_Width;
      Point[i].Y = Area_Height;
      i ++;

      Point[i].X = Area_Width;
      Point[i].Y = Area_Height -(Len - (Area_Height / 2 + Area_Width + Area_Height + Area_Width));
    }

    i++;
    Copy_Filled_Polygon(&Show_Data_Bak, Area_No, &Point[0], i, &Show_Data, &Point[0]);

    return;
 */
    Area_Width = Get_Area_Width(Area_No);
    Area_Height = Get_Area_Height(Area_No);

    Point[0].X = Area_Width / 2;
    Point[0].Y = Area_Height / 2;

    Get_Spin_Step_Point(Area_Width, Area_Height, Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step, &Point[1]);
    Get_Spin_Step_Point(Area_Width, Area_Height, Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step + MOVE_STEP, &Point[2]);
    Copy_Filled_Polygon(&Show_Data_Bak, Area_No, &Point[0], 3, &Show_Data, &Point[0]);

    Get_Spin_Step_Point(Area_Width, Area_Height, Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step + Area_Width + Area_Height, &Point[1]);
    Get_Spin_Step_Point(Area_Width, Area_Height, Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step + MOVE_STEP + Area_Width + Area_Height, &Point[2]);
    Copy_Filled_Polygon(&Show_Data_Bak, Area_No, &Point[0], 3, &Show_Data, &Point[0]);
}

void Copy_Snow_Rect(S_Show_Data *pSrc, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len, \
                    S_Show_Data *pDst, S_Point *pPoint1, INT16U Step)
{
  INT16U i,j;//,k;
  INT16U y;
  INT8U Re;

  for(i = 0;i < X_Len; i ++)
    for(j = 0; j < Y_Len; j++)
      {
        Re = Get_Area_Point_Data(pSrc, Area_No, pPoint0->X + i, pPoint0->Y + j);

        y = pPoint1->Y + j * SNOW_RATIO + (i + 0) % SNOW_RATIO;
        //x = pPoint0->X + i;

        //y += (x % SNOW_RATIO);

        Set_Area_Point_Data(pDst, Area_No, pPoint1->X + i, y,Re);

        //for(k = 1; k < SNOW_RATIO; k++)
          //Set_Area_Point_Data(pDst, Area_No, pPoint1->X + i, pPoint1->Y + j * SNOW_RATIO + k, 0);

  }
}

//����Ʈѩ
void Move_Up_Snow(INT8U Area_No)
{
    INT16U Step_Len,Y_Len;
    S_Point P0,P1;

    //�½���û�е��׵�ʱ���
    if(Prog_Status.Area_Status[Area_No].Step <= (Prog_Status.Area_Status[Area_No].Max_Step / SNOW_RATIO))
    {
        //y = (height - y0)
        Step_Len = Prog_Para.Area[Area_No].Y_Len * Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step;
        P0.X = 0;
        P0.Y = 0;//Prog_Para.Area[Area_No].Y_Len - Step_Len;

        P1.X = 0;
        P1.Y = Prog_Para.Area[Area_No].Y_Len - Step_Len * SNOW_RATIO;
        Copy_Snow_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Step_Len, &Show_Data,&P1, Prog_Status.Area_Status[Area_No].Step);
    }
    else
    {/*
        Step_Len = Prog_Para.Area[Area_No].Y_Len * ((Prog_Status.Area_Status[Area_No].Step - (Prog_Status.Area_Status[Area_No].Max_Step / SNOW_RATIO)))*SNOW_RATIO/(SNOW_RATIO - 1)/ Prog_Status.Area_Status[Area_No].Max_Step;
        P0.X = 0;
        P0.Y = 0;//Prog_Para.Area[Area_No].Y_Len - Step_Len;

        Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Step_Len, &Show_Data,&P0);

        //Step_Len = (Prog_Para.Area[Area_No].Y_Len - Step_Len)/ SNOW_RATIO;
        P0.Y = Step_Len;//P0.Y - P0.Y / SNOW_RATIO;

        Step_Len = (Prog_Para.Area[Area_No].Y_Len - Step_Len) / SNOW_RATIO;
        //P1.X = 0;
        //P1.Y = 0;
        Copy_Snow_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Step_Len, &Show_Data,&P0);
*/
//------------
        Step_Len = Prog_Para.Area[Area_No].Y_Len * ((Prog_Status.Area_Status[Area_No].Step - (Prog_Status.Area_Status[Area_No].Max_Step / SNOW_RATIO)))*SNOW_RATIO/(SNOW_RATIO - 1)/ Prog_Status.Area_Status[Area_No].Max_Step;

        P0.X = 0;
        P0.Y = Step_Len;//(Prog_Para.Area[Area_No].Y_Len - Step_Len) - (Prog_Para.Area[Area_No].Y_Len - Step_Len) / SNOW_RATIO;

        P1.X = 0;
        P1.Y = Step_Len;
        Y_Len = (Prog_Para.Area[Area_No].Y_Len - Step_Len) / SNOW_RATIO;
        Copy_Snow_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Y_Len, &Show_Data,&P1, Prog_Status.Area_Status[Area_No].Step);

        P0.X = 0;
        P0.Y = 0;
        Y_Len = Step_Len;// / SNOW_RATIO;

        Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Y_Len, &Show_Data,&P0,Prog_Status.Area_Status[Area_No].Step);


        //------------
    }

}

//����Ʈѩ
void Move_Down_Snow(INT8U Area_No)
{
    INT16U Step_Len,Y_Len;
    S_Point P0,P1;

    //�½���û�е��׵�ʱ���
    if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step / SNOW_RATIO)//(Prog_Status.Area_Status[Area_No].Max_Step / SNOW_RATIO))
    {
        //y = (height - y0)
        Step_Len = Prog_Status.Area_Status[Area_No].Step / SNOW_RATIO;//Prog_Para.Area[Area_No].Y_Len * Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step;
        P0.X = 0;
        P0.Y = Prog_Para.Area[Area_No].Y_Len - Step_Len;

        P1.X = 0;
        P1.Y = 0;
        Copy_Snow_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Step_Len, &Show_Data,&P1, Prog_Status.Area_Status[Area_No].Step);
    }
    else
    {
        Step_Len = Prog_Para.Area[Area_No].Y_Len * ((Prog_Status.Area_Status[Area_No].Step - (Prog_Status.Area_Status[Area_No].Max_Step / SNOW_RATIO)))*SNOW_RATIO/(SNOW_RATIO - 1)/ Prog_Status.Area_Status[Area_No].Max_Step;

        P0.X = 0;
        Y_Len = (Prog_Para.Area[Area_No].Y_Len - Step_Len) / SNOW_RATIO;
        P0.Y = (Prog_Para.Area[Area_No].Y_Len - Step_Len) - (Prog_Para.Area[Area_No].Y_Len - Step_Len) / SNOW_RATIO;

        P1.X = 0;
        P1.Y = 0;
        Copy_Snow_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Y_Len, &Show_Data,&P1, Prog_Status.Area_Status[Area_No].Step);

        P0.X = 0;
        P0.Y = Prog_Para.Area[Area_No].Y_Len - Step_Len;

        Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Step_Len, &Show_Data,&P0, Prog_Status.Area_Status[Area_No].Step);


    }

}

INT16U Get_TENSILE_STEP(INT16U Len)
{
  if(Len > 1000)
    return 200;
  else if(Len > 800)
    return 160;
  else if(Len > 600)
    return 120;
  else if(Len > 400)
    return 80;
  else if(Len > 200)
    return 40;
  else if(Len > 100)
    return 16;
  else
    return 8;

/*
    INT16U Re;

    if(Len > 100)
    {
    Re = Len / 10;
    if(Re < 5)
        Re = 5;
    }
    else
        Re = 10;
    return Re;
    */
}

//���ƺ����ѹ������
void Copy_Compresssion_H_Rect(S_Show_Data *pSrc, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len, \
                              S_Show_Data *pDst, S_Point *pPoint1, INT16U Ratio, INT8U Direct)
{

    INT16U i;//, j;
    S_Point P0, P1,P2;
    INT16U TENSILE_STEP;
    //INT16U Temp;

    if(Ratio EQ 0)
        return;

    TENSILE_STEP = Get_TENSILE_STEP(Prog_Para.Area[Area_No].X_Len);//Prog_Para.Area[Area_No].X_Len);

    Ratio = TENSILE_STEP * Ratio / Prog_Status.Area_Status[Area_No].Max_Step;//100;//ÿ10�����������;

    if(Direct EQ 0)
    {
        for(i = 0; i < X_Len; i ++)
        {
          if((i % TENSILE_STEP) < Ratio)
          {
              P0.X = pPoint0->X + i;
              P0.Y = pPoint0->Y;

              P1.X = pPoint0->X + i;
              P1.Y = pPoint0->Y + Y_Len - 1;

              P2.X = pPoint1->X + (i / TENSILE_STEP)*Ratio + (i % TENSILE_STEP);
              P2.Y = pPoint1->Y;
              Copy_Line(pSrc, Area_No, &P0, &P1, pDst, &P2);
           }
         }
    }
    else
    {
        //Clear_Area_Data(pDst, Area_No);
        for(i = 0; i < X_Len; i ++)
        {
          if(((X_Len - 1- i) % TENSILE_STEP) < Ratio)
          {
              P0.X = pPoint0->X + (X_Len - 1- i);
              P0.Y = pPoint0->Y;

              P1.X = pPoint0->X + (X_Len - 1- i);
              P1.Y = pPoint0->Y + Y_Len - 1;

              P2.X = pPoint1->X + X_Len - ((i / TENSILE_STEP)*Ratio + (i % TENSILE_STEP));
              P2.Y = pPoint1->Y;
              Copy_Line(pSrc, Area_No, &P0, &P1, pDst, &P2);
           }
         }
   }
}

//���������ѹ������
void Copy_Compresssion_V_Rect(S_Show_Data *pSrc, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len, \
                              S_Show_Data *pDst, S_Point *pPoint1, INT16U Ratio, INT8U Direct)
{
    INT16U i;
    S_Point P0, P1,P2;
    INT16U TENSILE_STEP;

    if(Ratio EQ 0)
        return;

    TENSILE_STEP = Get_TENSILE_STEP(Prog_Para.Area[Area_No].Y_Len);

    Ratio = Ratio * TENSILE_STEP / (Prog_Status.Area_Status[Area_No].Max_Step);//100;//ÿ10�����������;
    for(i = 0; i < Y_Len; i ++)
        //for(j = 0; j < Y_Len; j ++)
        {
        if((Direct EQ 0 && (i % TENSILE_STEP) < Ratio) ||\
           (Direct EQ 1 && (i % TENSILE_STEP) >= (TENSILE_STEP - Ratio)))
        {
              P0.X = pPoint0->X;// + i;
              P0.Y = pPoint0->Y + i;

              P1.X = pPoint0->X + X_Len - 1;
              P1.Y = pPoint0->Y + i;

              P2.X = pPoint1->X;
              P2.Y = pPoint1->Y + (i / TENSILE_STEP)*Ratio + (i % TENSILE_STEP);

              Copy_Line(pSrc, Area_No, &P0, &P1, pDst, &P2);
          }
    }
}

//������
void Move_Left_Tensile(INT8U Area_No)
{
    S_Point P0;

    P0.X = 0;
    P0.Y = 0;
    Copy_Compresssion_H_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len,\
                             &Show_Data, &P0, Prog_Status.Area_Status[Area_No].Step, 0);
}

//������
void Move_Right_Tensile(INT8U Area_No)
{
    S_Point P0,P1;

    P0.X = 0;
    P0.Y = 0;

    P1.X = Prog_Para.Area[Area_No].X_Len - Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    P1.Y = 0;
    Copy_Compresssion_H_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len,\
                             &Show_Data, &P1, Prog_Status.Area_Status[Area_No].Step, 1);

}

//������
void Move_Up_Tensile(INT8U Area_No)
{
    S_Point P0;

    P0.X = 0;
    P0.Y = 0;
    Copy_Compresssion_V_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len,\
                             &Show_Data, &P0, Prog_Status.Area_Status[Area_No].Step, 0);

}

//������
void Move_Down_Tensile(INT8U Area_No)
{
    S_Point P0,P1;

    P0.X = 0;
    P0.Y = 0;

    P1.X = 0;
    P1.Y = Prog_Para.Area[Area_No].Y_Len - Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    Copy_Compresssion_V_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len,\
                             &Show_Data, &P1, Prog_Status.Area_Status[Area_No].Step, 1);

}

//��ֱ����
void Move_Vertical_Tensile(INT8U Area_No)
{
    S_Point P0,P1;
    INT16U Step;
    INT16U TENSILE_STEP;

    TENSILE_STEP = Get_TENSILE_STEP(Prog_Para.Area[Area_No].Y_Len);

    if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step)
      Step = Prog_Status.Area_Status[Area_No].Step / (Prog_Status.Area_Status[Area_No].Max_Step / TENSILE_STEP) *(Prog_Status.Area_Status[Area_No].Max_Step / TENSILE_STEP);
    else
      Step = Prog_Status.Area_Status[Area_No].Step;

    P0.X = 0;
    P0.Y = 0;

    P1.X = 0;
    P1.Y = Prog_Para.Area[Area_No].Y_Len - Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    P1.Y = P1.Y / 2;
    Copy_Compresssion_V_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len / 2,\
                             &Show_Data, &P1, Step, 0);

    P0.X = 0;
    P0.Y = Prog_Para.Area[Area_No].Y_Len / 2;

    P1.X = 0;
    P1.Y = Prog_Para.Area[Area_No].Y_Len / 2;//Prog_Para.Area[Area_No].Y_Len - Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    //P1.Y = P1.Y / 2;
    Copy_Compresssion_V_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len / 2,\
                             &Show_Data, &P1, Step, 0);

}

//ˮƽ����
void Move_Horizontal_Tensile(INT8U Area_No)
{
    S_Point P0,P1;
    INT16U Step;
    INT16U TENSILE_STEP;

    TENSILE_STEP = Get_TENSILE_STEP(Prog_Para.Area[Area_No].X_Len);

    if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step)
      Step = Prog_Status.Area_Status[Area_No].Step / (Prog_Status.Area_Status[Area_No].Max_Step / TENSILE_STEP) *(Prog_Status.Area_Status[Area_No].Max_Step / TENSILE_STEP);
    else
      Step = Prog_Status.Area_Status[Area_No].Step;
    P0.X = 0;
    P0.Y = 0;

    P1.X = Prog_Para.Area[Area_No].X_Len - Step * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    P1.Y = 0;
    P1.X = P1.X / 2;
    Copy_Compresssion_H_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len / 2, Prog_Para.Area[Area_No].Y_Len,\
                             &Show_Data, &P1, Step, 0);

    P0.X = Prog_Para.Area[Area_No].X_Len / 2;
    P0.Y = 0;

    P1.X = Prog_Para.Area[Area_No].X_Len / 2;
    P1.Y = 0;//Prog_Para.Area[Area_No].Y_Len - Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    //P1.Y = P1.Y / 2;
    Copy_Compresssion_H_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len / 2, Prog_Para.Area[Area_No].Y_Len,\
                             &Show_Data, &P1, Step, 0);
}

//��˸
void Move_Flash(INT8U Area_No)
{
   S_Point P0;

   P0.X = 0;
   P0.Y = 0;

   if((Prog_Status.Area_Status[Area_No].Step / (Prog_Status.Area_Status[Area_No].Max_Step/10)) % 2 EQ 0)
    {
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len,\
                       &Show_Data, &P0,0);
   }
   else
       Clear_Area_Data(&Show_Data, Area_No);
}

//������
void Move_Up_Laser(INT8U Area_No)
{
    S_Point Temp,Temp1;
    INT8U Re;
    INT16U i;


    //Clear_Area_Data(&Show_Data, Area_No);
    Temp.X = 0;// + (Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step) * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    Temp.Y = Prog_Para.Area[Area_No].Y_Len - Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;

    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, MOVE_STEP,\
                     &Show_Data, &Temp,0);

    Temp1.X = 0;
    Temp1.Y = 0;
    Clear_Rect(&Show_Data, Area_No, &Temp1, Prog_Para.Area[Area_No].X_Len, Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step);

    for(i = 0; i < Prog_Para.Area[Area_No].X_Len; i ++)
    {
       Re = Get_Area_Point_Data(&Show_Data_Bak, Area_No, i, Temp.Y);
       if(Re)// && (i % 2))
       {
           Temp1.X = i;
           Temp1.Y = 0;

           Temp.X = i;
           Draw_Line(&Show_Data, Area_No, &Temp, &Temp1,Re);
       }
    }
}

//������
void Move_Down_Laser(INT8U Area_No)
{
    S_Point Temp,Temp1;
    INT8U Re;
    INT16U i;

    //Clear_Area_Data(&Show_Data, Area_No);

    Temp.X = 0;// + Step +
    Temp.Y = (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;

    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, MOVE_STEP,\
                     &Show_Data, &Temp,0);

    Temp1.X = 0;
    Temp1.Y = Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    Clear_Rect(&Show_Data, Area_No, &Temp1, Prog_Para.Area[Area_No].X_Len, Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step);

    Temp.Y = Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    for(i = 0; i < Prog_Para.Area[Area_No].X_Len; i ++)
    {
       //Temp.Y = i;
       Re = Get_Area_Point_Data(&Show_Data_Bak, Area_No, i, Temp.Y);
       if(Re)// && (i % 2))
       {
           Temp1.X = i;
           Temp1.Y = Prog_Para.Area[Area_No].Y_Len - 1;

           Temp.X = i;
           Draw_Line(&Show_Data, Area_No, &Temp, &Temp1,Re);
       }
    }

}

//������
void Move_Left_Laser(INT8U Area_No)
{
    INT8U Re;
    S_Point Temp,Temp1;
    INT16U i;

    //Clear_Area_Data(&Show_Data, Area_No);
    Temp.X = Prog_Para.Area[Area_No].X_Len - Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;// + Step +
    Temp.Y = 0;

    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, MOVE_STEP * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step, Prog_Para.Area[Area_No].Y_Len,\
      &Show_Data, &Temp,0);

    Temp1.X = 0;
    Temp1.Y = 0;
    Clear_Rect(&Show_Data, Area_No, &Temp1, (Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step) * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step, Prog_Para.Area[Area_No].Y_Len);

    for(i = 0; i < Prog_Para.Area[Area_No].Y_Len; i ++)
    {
       Re = Get_Area_Point_Data(&Show_Data_Bak, Area_No, Temp.X, i);
       if(Re)// && (i % 2))
       {
           Temp1.X = 0;
           Temp1.Y = i;

           Temp.Y = i;
           Draw_Line(&Show_Data, Area_No, &Temp, &Temp1,Re);
       }
    }
}

//������
void Move_Right_Laser(INT8U Area_No)
{
    S_Point Temp;
    INT8U Re;
    INT16U i;
    S_Point Temp1;


    //Clear_Area_Data(&Show_Data, Area_No);
    Temp.X = (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    Temp.Y = 0;

    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, MOVE_STEP * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step, Prog_Para.Area[Area_No].Y_Len,\
    &Show_Data, &Temp,0);

    Temp1.X = Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    Temp1.Y = 0;
    Clear_Rect(&Show_Data, Area_No, &Temp1, (Prog_Status.Area_Status[Area_No].Max_Step - Prog_Status.Area_Status[Area_No].Step)*Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step, Prog_Para.Area[Area_No].Y_Len);

    Temp.X = Prog_Status.Area_Status[Area_No].Step * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;
    for(i = 0; i < Prog_Para.Area[Area_No].Y_Len; i ++)
    {
       //Temp.Y = i;
       Re = Get_Area_Point_Data(&Show_Data_Bak, Area_No, Temp.X, i);
       if(Re)// && (i % 2))
       {
           Temp1.X = Prog_Para.Area[Area_No].X_Len - 1;
           Temp1.Y = i;

           Temp.Y = i;
           Draw_Line(&Show_Data, Area_No, &Temp, &Temp1,Re);
       }
    }
}

//���Ƶ���
void Move_Left_Stretch(INT8U Area_No)
{
    S_Point Temp;
    S_Point Temp1;
    INT16U Step;
    INT16U Moved_Len;

    if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step / 3)
    {
        Temp.X = 0;//Prog_Para.Area[Area_No].X;
        Temp.Y = 0;//Prog_Para.Area[Area_No].Y;

        Step = Prog_Status.Area_Status[Area_No].Step * 3;
        Moved_Len =  Step * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;
        Temp1.X = Prog_Para.Area[Area_No].X_Len - Moved_Len;// + Step +
        Temp1.Y = 0;

        Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Moved_Len,Prog_Para.Area[Area_No].Y_Len, \
          &Show_Data, &Temp1,0);
   }
   else if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step*2 / 3)
   {
       Clear_Area_Data(&Show_Data, Area_No);
       Temp.X = 0;
       Temp.Y = 0;
       Step = (Prog_Status.Area_Status[Area_No].Max_Step - (Prog_Status.Area_Status[Area_No].Step  * 3- Prog_Status.Area_Status[Area_No].Max_Step));
       Copy_Compresssion_H_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len,\
                                &Show_Data, &Temp, Step, 0);

   }
   else
   {
       Temp.X = 0;
       Temp.Y = 0;
       Step = (Prog_Status.Area_Status[Area_No].Step*3 - Prog_Status.Area_Status[Area_No].Max_Step * 2);
       Copy_Compresssion_H_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len,\
                                &Show_Data, &Temp, Step, 0);

   }
 }

//���Ƶ���
void Move_Right_Stretch(INT8U Area_No)
{

}

//���Ƶ���
void Move_Up_Stretch(INT8U Area_No)
{
    S_Point Temp;
    S_Point Temp1;
    INT16U Step;
    INT16U Moved_Len;

    if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step / 3)
    {
        Temp.X = 0;//Prog_Para.Area[Area_No].X;
        Temp.Y = 0;//Prog_Para.Area[Area_No].Y;

        Step = Prog_Status.Area_Status[Area_No].Step * 3;
        Moved_Len =  Step * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
        Temp1.X = 0;// + Step +
        Temp1.Y = Prog_Para.Area[Area_No].Y_Len - Moved_Len;;

        Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Moved_Len, \
          &Show_Data, &Temp1,0);
   }
   else if(Prog_Status.Area_Status[Area_No].Step < Prog_Status.Area_Status[Area_No].Max_Step*2 / 3)
   {
       Clear_Area_Data(&Show_Data, Area_No);
       Temp.X = 0;
       Temp.Y = 0;
       Step = (Prog_Status.Area_Status[Area_No].Max_Step - (Prog_Status.Area_Status[Area_No].Step*3 - Prog_Status.Area_Status[Area_No].Max_Step));
       Copy_Compresssion_V_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len,\
                                &Show_Data, &Temp, Step, 0);

   }
   else
   {
       Temp.X = 0;
       Temp.Y = 0;
       Step = (Prog_Status.Area_Status[Area_No].Step * 3 - Prog_Status.Area_Status[Area_No].Max_Step * 2) ;
       Copy_Compresssion_V_Rect(&Show_Data_Bak, Area_No, &Temp, Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len,\
                                &Show_Data, &Temp, Step, 0);

   }
}

void Move_Down_Stretch(INT8U Area_No)
{

}

void Move_Up_Left(INT8U Area_No)
{

}

//ˮƽ��Ҷ��
void Move_Horizontal_Window(INT8U Area_No)
{
  INT16U i;
  S_Point P0;
  INT16U Width,Num;
  //INT32U Step;

  Width = WIN_LEAF_WIDTH;
  if(Prog_Para.Area[Area_No].X_Len % Width EQ 0)
    Num = Prog_Para.Area[Area_No].X_Len / Width;
  else
    Num = Prog_Para.Area[Area_No].X_Len / Width + 1;

  if(Num EQ 0)
      Num = 1;

  for(i = 0; i < Num ; i++)
  {
     P0.X = (INT16U)i * Width;//Prog_Para.Area[Area_No].Y_Len / 20;
     P0.Y = 0;
     Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Width * Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step, Prog_Para.Area[Area_No].Y_Len, &Show_Data, &P0,0);
  }

}

//��ֱ��Ҷ��
void Move_Vertical_Window(INT8U Area_No)
{
    INT16U i;
    S_Point P0;
    INT16U Width,Num;
    //INT32U Step;

    Width = WIN_LEAF_WIDTH;
    if(Prog_Para.Area[Area_No].Y_Len % Width EQ 0)
      Num = Prog_Para.Area[Area_No].Y_Len / Width;
    else
      Num = Prog_Para.Area[Area_No].Y_Len / Width + 1;

    if(Num EQ 0)
        Num = 1;

    for(i = 0; i < Num ; i++)
    {
       P0.X = 0;//Prog_Para.Area[Area_No].Y_Len / 20;
       P0.Y = (INT16U)i * Width;
       Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Prog_Para.Area[Area_No].X_Len, Width * Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step, &Show_Data, &P0,0);
    }
}

//��ѹ��
void Move_Left_Compress(INT8U Area_No)
{
  INT16U i,j;
  S_Point P0,P1,P2;
  INT16U Step;

  Step = 10 - Prog_Status.Area_Status[Area_No].Step / (Prog_Status.Area_Status[Area_No].Max_Step / 10);
  Step++;
  if(Step EQ 0)
      return;

  //Clear_Area_Data(&Show_Data, Area_No);
  for(i = 0; i < Prog_Para.Area[Area_No].X_Len / Step; i ++)
  {
      P0.X = i;
      P0.Y = 0;

      P1.X = i;
      P1.Y = Prog_Para.Area[Area_No].Y_Len - 1;

      for(j = 0; j < Step; j++)
      {
          P2.X = i *Step + j;
          P2.Y = 0;
          Copy_Line(&Show_Data_Bak, Area_No, &P0, &P1, &Show_Data, &P2);

      }
  }
  /*
    INT16U i,j;
    S_Point P0,P1,P2;
    INT16U Step;

    Step = Prog_Status.Area_Status[Area_No].Step;
    if(Step EQ 0)
        Step = 1;

    //Clear_Area_Data(&Show_Data, Area_No);
    j = 0;
    i = 0;
    while(j < Prog_Para.Area[Area_No].X_Len)
    {
        P0.X = i;
        P0.Y = 0;

        P1.X = i;
        P1.Y = Prog_Para.Area[Area_No].Y_Len - 1;

        P2.X = j;
        P2.Y = Prog_Para.Area[Area_No].Y_Len - 1;

        Copy_Line(&Show_Data_Bak, Area_No, &P0, &P1, &Show_Data, &P2);

        if(i % Step EQ 0)
        {
            P2.X = j + 1;
            P2.Y = Prog_Para.Area[Area_No].Y_Len - 1;
            Copy_Line(&Show_Data_Bak, Area_No, &P0, &P1, &Show_Data, &P2);
            j++;
        }

        i++;
        j++;
    }*/
}

//��ѹ��
void Move_Right_Compress(INT8U Area_No)
{

}

//��ѹ��
void Move_Up_Compress(INT8U Area_No)
{
    INT16U i,j;
    S_Point P0,P1,P2;
    INT16U Step;

    Step = 10 - Prog_Status.Area_Status[Area_No].Step / (Prog_Status.Area_Status[Area_No].Max_Step / 10);
    Step++;
    if(Step EQ 0)
        return;

    //Clear_Area_Data(&Show_Data, Area_No);
    for(i = 0; i < Prog_Para.Area[Area_No].Y_Len / Step; i ++)
    {
        P0.X = 0;
        P0.Y = i;

        P1.X = Prog_Para.Area[Area_No].X_Len - 1;
        P1.Y = i;

        for(j = 0; j < Step; j++)
        {
            P2.X = 0;
            P2.Y = i *Step + j;
            Copy_Line(&Show_Data_Bak, Area_No, &P0, &P1, &Show_Data, &P2);

        }
    }
}

//��ѹ��
void Move_Down_Compress(INT8U Area_No)
{

}

//��ѹ��
void Move_Left_Compress_0(INT8U Area_No)
{
    S_Point Temp0,Temp1;
    INT16U Moved_Len, Last_Moved_Len;


   if((float)Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step <= (float)1/STRETCH_RATIO)
    {
       Temp0.X = 0;
       Temp0.Y = 0;

       Moved_Len = Prog_Status.Area_Status[Area_No].Step*STRETCH_RATIO * Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;
       Temp1.X = Prog_Para.Area[Area_No].X_Len - Moved_Len;// + Step +
       Temp1.Y = 0;

       Copy_Filled_Stretch_Rect(&Show_Data_Bak, Area_No, &Temp0, Moved_Len / STRETCH_RATIO, Prog_Para.Area[Area_No].Y_Len, STRETCH_RATIO, 1, &Show_Data, &Temp1);
   }
   else
   {
 	   if(Prog_Status.Area_Status[Area_No].Step - MOVE_STEP > Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO)
         Last_Moved_Len = ((Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) - Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO) * Prog_Para.Area[Area_No].X_Len / (Prog_Status.Area_Status[Area_No].Max_Step*(STRETCH_RATIO - 1)/(STRETCH_RATIO));
	   else
	     Last_Moved_Len = 0;

       Temp0.X = Last_Moved_Len;
       Temp0.Y = 0;

	   if(Prog_Status.Area_Status[Area_No].Step > Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO)
         Moved_Len = (Prog_Status.Area_Status[Area_No].Step - Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO) * Prog_Para.Area[Area_No].X_Len / (Prog_Status.Area_Status[Area_No].Max_Step*(STRETCH_RATIO - 1)/(STRETCH_RATIO));
	   else
	     Moved_Len = 0;

       Temp1.X = Moved_Len;// + Step +
       Temp1.Y = 0;

       Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp0, Moved_Len - Last_Moved_Len,Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Temp0,0);

	   if(Prog_Para.Area[Area_No].X_Len > Moved_Len)
         Copy_Filled_Stretch_Rect(&Show_Data_Bak, Area_No, &Temp1, (Prog_Para.Area[Area_No].X_Len - Moved_Len) / STRETCH_RATIO, Prog_Para.Area[Area_No].Y_Len, STRETCH_RATIO, 1, &Show_Data, &Temp1);
   }
}

//��ѹ��
void Move_Right_Compress_0(INT8U Area_No)
{
    S_Point Temp0,Temp1;
    INT16U Moved_Len, Last_Moved_Len;


   if((float)Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step <= (float)1/STRETCH_RATIO)
    {
       Moved_Len = Prog_Status.Area_Status[Area_No].Step* Prog_Para.Area[Area_No].X_Len / Prog_Status.Area_Status[Area_No].Max_Step;

       Temp0.X = Prog_Para.Area[Area_No].X_Len - Moved_Len;
       Temp0.Y = 0;


       Temp1.X = 0;//Prog_Para.Area[Area_No].X_Len - Moved_Len;// + Step +
       Temp1.Y = 0;

       Copy_Filled_Stretch_Rect(&Show_Data_Bak, Area_No, &Temp0, Moved_Len, Prog_Para.Area[Area_No].Y_Len, STRETCH_RATIO, 1, &Show_Data, &Temp1);
   }
   else
   {
       if(Prog_Status.Area_Status[Area_No].Step - MOVE_STEP > Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO)
         Last_Moved_Len = ((Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) - Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO) * Prog_Para.Area[Area_No].X_Len / (Prog_Status.Area_Status[Area_No].Max_Step*(STRETCH_RATIO - 1)/(STRETCH_RATIO));
           else
             Last_Moved_Len = 0;

       if(Prog_Status.Area_Status[Area_No].Step > Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO)
         Moved_Len = (Prog_Status.Area_Status[Area_No].Step - Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO) * Prog_Para.Area[Area_No].X_Len / (Prog_Status.Area_Status[Area_No].Max_Step*(STRETCH_RATIO - 1)/(STRETCH_RATIO));
	   else
	     Moved_Len = 0;

       Temp0.X = Prog_Para.Area[Area_No].X_Len - Moved_Len;
       Temp0.Y = 0;

       Temp1.X = Prog_Para.Area[Area_No].X_Len - Moved_Len - (Prog_Para.Area[Area_No].X_Len - Moved_Len) / STRETCH_RATIO;// + Step +
       Temp1.Y = 0;

       Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp0, Moved_Len - Last_Moved_Len,Prog_Para.Area[Area_No].Y_Len, &Show_Data, &Temp0,0);

       Temp0.X = 0;
       Temp0.Y = 0;

	   if(Prog_Para.Area[Area_No].X_Len > Moved_Len)
         Copy_Filled_Stretch_Rect(&Show_Data_Bak, Area_No, &Temp1, (Prog_Para.Area[Area_No].X_Len - Moved_Len) / STRETCH_RATIO, Prog_Para.Area[Area_No].Y_Len, STRETCH_RATIO, 1, &Show_Data, &Temp0);
   }
}

//��ѹ��
void Move_Up_Compress_0(INT8U Area_No)
{
    S_Point Temp0,Temp1;
    INT16U Moved_Len, Last_Moved_Len;


   if((float)Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step <= (float)1/STRETCH_RATIO)
    {
       Temp0.X = 0;
       Temp0.Y = 0;

       Moved_Len = Prog_Status.Area_Status[Area_No].Step*STRETCH_RATIO * Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;
       Temp1.X = 0;// + Step +
       Temp1.Y = Prog_Para.Area[Area_No].Y_Len - Moved_Len;;

       Copy_Filled_Stretch_Rect(&Show_Data_Bak, Area_No, &Temp0, Prog_Para.Area[Area_No].X_Len, Moved_Len / STRETCH_RATIO, 1, STRETCH_RATIO,  &Show_Data, &Temp1);
   }
   else
   {
       if(Prog_Status.Area_Status[Area_No].Step - MOVE_STEP > Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO)
      Last_Moved_Len = ((Prog_Status.Area_Status[Area_No].Step - MOVE_STEP) - Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO) * Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*(STRETCH_RATIO - 1)/(STRETCH_RATIO));
       else
         Last_Moved_Len = 0;

       Temp0.X = 0;
       Temp0.Y = Last_Moved_Len;

	   if(Prog_Status.Area_Status[Area_No].Step > Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO)
         Moved_Len = (Prog_Status.Area_Status[Area_No].Step - Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO) * Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*(STRETCH_RATIO - 1)/(STRETCH_RATIO));
	   else
	     Moved_Len = 0;
		  
       Temp1.X = 0;// + Step +
       Temp1.Y = Moved_Len;

       Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp0,Prog_Para.Area[Area_No].X_Len, Moved_Len - Last_Moved_Len, &Show_Data, &Temp0,0);
	   
	   if(Prog_Para.Area[Area_No].Y_Len > Moved_Len)
         Copy_Filled_Stretch_Rect(&Show_Data_Bak, Area_No, &Temp1, Prog_Para.Area[Area_No].X_Len, (Prog_Para.Area[Area_No].Y_Len - Moved_Len) / STRETCH_RATIO, 1, STRETCH_RATIO, &Show_Data, &Temp1);
   }
}

//��ѹ��
void Move_Down_Compress_0(INT8U Area_No)
{
    S_Point Temp0,Temp1;
    INT16U Moved_Len, Last_Moved_Len;


   if((float)Prog_Status.Area_Status[Area_No].Step / Prog_Status.Area_Status[Area_No].Max_Step <= (float)1/STRETCH_RATIO)
    {
       Moved_Len = Prog_Status.Area_Status[Area_No].Step* Prog_Para.Area[Area_No].Y_Len / Prog_Status.Area_Status[Area_No].Max_Step;

       Temp0.X = 0;//
       Temp0.Y = Prog_Para.Area[Area_No].Y_Len - Moved_Len;


       Temp1.X = 0;//Prog_Para.Area[Area_No].X_Len - Moved_Len;// + Step +
       Temp1.Y = 0;

       Copy_Filled_Stretch_Rect(&Show_Data_Bak, Area_No, &Temp0, Prog_Para.Area[Area_No].X_Len, Moved_Len,  1, STRETCH_RATIO, &Show_Data, &Temp1);
   }
   else
   {
       if(Prog_Status.Area_Status[Area_No].Step - MOVE_STEP  > Prog_Status.Area_Status[Area_No].Max_Step / STRETCH_RATIO)
             Last_Moved_Len = ((Prog_Status.Area_Status[Area_No].Step - MOVE_STEP)  - Prog_Status.Area_Status[Area_No].Max_Step / STRETCH_RATIO) * Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*(STRETCH_RATIO - 1)/(STRETCH_RATIO));
           else
             Last_Moved_Len = 0;

       //Moved_Len = (Prog_Status.Area_Status[Area_No].Step - Prog_Status.Area_Status[Area_No].Max_Step/STRETCH_RATIO) * Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*(STRETCH_RATIO - 1)/(STRETCH_RATIO));
       if(Prog_Status.Area_Status[Area_No].Step  > Prog_Status.Area_Status[Area_No].Max_Step / STRETCH_RATIO)
             Moved_Len = (Prog_Status.Area_Status[Area_No].Step  - Prog_Status.Area_Status[Area_No].Max_Step / STRETCH_RATIO) * Prog_Para.Area[Area_No].Y_Len / (Prog_Status.Area_Status[Area_No].Max_Step*(STRETCH_RATIO - 1)/(STRETCH_RATIO));
	   else
	     Moved_Len = 0;

       Temp0.X = 0;
       Temp0.Y = Prog_Para.Area[Area_No].Y_Len - Moved_Len;

       Temp1.X = 0;// + Step +
       Temp1.Y = Prog_Para.Area[Area_No].Y_Len - Moved_Len - (Prog_Para.Area[Area_No].Y_Len - Moved_Len) / STRETCH_RATIO;

       Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp0, Prog_Para.Area[Area_No].X_Len, Moved_Len - Last_Moved_Len, &Show_Data, &Temp0,0);

       Temp0.X = 0;
       Temp0.Y = 0;
	  
	   if(Prog_Para.Area[Area_No].Y_Len > Moved_Len)
         Copy_Filled_Stretch_Rect(&Show_Data_Bak, Area_No, &Temp1, Prog_Para.Area[Area_No].X_Len, (Prog_Para.Area[Area_No].Y_Len - Moved_Len) / STRETCH_RATIO,  1, STRETCH_RATIO, &Show_Data, &Temp0);
   }
}

//��㵭��
void Move_Fade_In(INT8U Area_No)
{
    INT8U Re;
    INT16U i,j;
    INT16U Step;
    //const INT8U data[20] = {1,17,3,9,19,0,15,10,7, 6,18, 2,12,4,8,14,11,13,16,5};

    Step =  Prog_Status.Area_Status[Area_No].Step *20/ Prog_Status.Area_Status[Area_No].Max_Step;
    Step = 20 - Step;
    if(Step == 0)
       Step = 1;

    for(i = 0; i < Prog_Para.Area[Area_No].X_Len; i ++)
        for(j = 0; j < Prog_Para.Area[Area_No].Y_Len; j++)
        {
          if(i % Step < 2 && j % Step < 2)
          //if(i % 20 EQ data[Step] && j %20 EQ 19 - data[Step])
          {
             Re = Get_Area_Point_Data(&Show_Data_Bak, Area_No, i, j);
             Set_Area_Point_Data(&Show_Data, Area_No, i, j, Re);
          }
    }
}

//��������
void Move_Left_Up_In(INT8U Area_No)
{
  S_Point Temp,Temp0;
  INT16U X_Off,Y_Off;
  INT16U OldX,OldY;

  OldX = (INT16U)((float)Prog_Para.Area[Area_No].X_Len * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP)/ Prog_Status.Area_Status[Area_No].Max_Step);
  OldY = (INT16U)((float)Prog_Para.Area[Area_No].Y_Len * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP)/ Prog_Status.Area_Status[Area_No].Max_Step);

  X_Off = (INT16U)((float)Prog_Para.Area[Area_No].X_Len * Prog_Status.Area_Status[Area_No].Step/ Prog_Status.Area_Status[Area_No].Max_Step);
  Y_Off = (INT16U)((float)Prog_Para.Area[Area_No].Y_Len * Prog_Status.Area_Status[Area_No].Step/ Prog_Status.Area_Status[Area_No].Max_Step);

  Temp.X = Prog_Para.Area[Area_No].X_Len - X_Off;
  Temp.Y = Prog_Para.Area[Area_No].Y_Len - Y_Off;

  Temp0.X = 0;
  Temp0.Y = 0;

  if(OldX != X_Off && OldY != Y_Off)
  {
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, X_Off, Y_Off, &Show_Data, &Temp0,0);
  }

}

//��������
void Move_Right_Up_In(INT8U Area_No)
{
    S_Point Temp,Temp0;
    INT16U X_Off,Y_Off;
    INT16U OldX, OldY;


    OldX = (INT16U)((float)Prog_Para.Area[Area_No].X_Len * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP)/ Prog_Status.Area_Status[Area_No].Max_Step);
    OldY = (INT16U)((float)Prog_Para.Area[Area_No].Y_Len * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP)/ Prog_Status.Area_Status[Area_No].Max_Step);

    X_Off = (INT16U)((float)Prog_Para.Area[Area_No].X_Len * Prog_Status.Area_Status[Area_No].Step/ Prog_Status.Area_Status[Area_No].Max_Step);
    Y_Off = (INT16U)((float)Prog_Para.Area[Area_No].Y_Len * Prog_Status.Area_Status[Area_No].Step/ Prog_Status.Area_Status[Area_No].Max_Step);

    Temp.X = 0;//Prog_Para.Area[Area_No].X_Len - 1;// X_Off;
    Temp.Y = Prog_Para.Area[Area_No].Y_Len - Y_Off;

    Temp0.X = Prog_Para.Area[Area_No].X_Len - X_Off;
    Temp0.Y = 0;//Prog_Para.Area[Area_No].Y_Len - Y_Off;

    if(OldX != X_Off && OldY != Y_Off)
    {
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, X_Off, Y_Off, &Show_Data, &Temp0,0);
    }

}

//��������
void Move_Left_Down_In(INT8U Area_No)
{
    S_Point Temp,Temp0;
    INT16U X_Off,Y_Off;
    INT16U OldX,OldY;

    //X�����ƶ��ľ���
    OldX = (INT16U)((float)Prog_Para.Area[Area_No].X_Len * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP)/ Prog_Status.Area_Status[Area_No].Max_Step);
    //Y�����ƶ��ľ���
    OldY = (INT16U)((float)Prog_Para.Area[Area_No].Y_Len * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP)/ Prog_Status.Area_Status[Area_No].Max_Step);

    //X�����ƶ��ľ���
    X_Off = (INT16U)((float)Prog_Para.Area[Area_No].X_Len * Prog_Status.Area_Status[Area_No].Step/ Prog_Status.Area_Status[Area_No].Max_Step);
    //Y�����ƶ��ľ���
    Y_Off = (INT16U)((float)Prog_Para.Area[Area_No].Y_Len * Prog_Status.Area_Status[Area_No].Step/ Prog_Status.Area_Status[Area_No].Max_Step);

    Temp.X = Prog_Para.Area[Area_No].X_Len - X_Off;
    Temp.Y = 0;//Prog_Para.Area[Area_No].Y_Len - Y_Off;

    Temp0.X = 0;
    Temp0.Y = Prog_Para.Area[Area_No].Y_Len - Y_Off;

    if(OldX != X_Off && OldY != Y_Off)
    {
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, X_Off, Y_Off, &Show_Data, &Temp0,0);
    }
}

//��������
void Mofe_Right_Down_In(INT8U Area_No)
{
    S_Point Temp,Temp0;
    INT16U X_Off,Y_Off;
    INT16U OldX, OldY;

    OldX = (INT16U)((float)Prog_Para.Area[Area_No].X_Len * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP)/ Prog_Status.Area_Status[Area_No].Max_Step);
    OldY = (INT16U)((float)Prog_Para.Area[Area_No].Y_Len * (Prog_Status.Area_Status[Area_No].Step - MOVE_STEP)/ Prog_Status.Area_Status[Area_No].Max_Step);

    X_Off = (INT16U)((float)Prog_Para.Area[Area_No].X_Len * Prog_Status.Area_Status[Area_No].Step/ Prog_Status.Area_Status[Area_No].Max_Step);
    Y_Off = (INT16U)((float)Prog_Para.Area[Area_No].Y_Len * Prog_Status.Area_Status[Area_No].Step/ Prog_Status.Area_Status[Area_No].Max_Step);

    Temp.X = 0;//Prog_Para.Area[Area_No].X_Len - 1;// X_Off;
    Temp.Y = 0;//Prog_Para.Area[Area_No].Y_Len - Y_Off;

    Temp0.X = Prog_Para.Area[Area_No].X_Len - X_Off;
    Temp0.Y = Prog_Para.Area[Area_No].Y_Len - Y_Off;

    if(OldX != X_Off && OldY != Y_Off)
    {
      Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, X_Off, Y_Off, &Show_Data, &Temp0,0);
    }
}


/*
    dateCombo->addItem(tr("2000��12��30��"));
    dateCombo->addItem(tr("00��12��30��"));
    dateCombo->addItem(tr("12/30/2000"));
    dateCombo->addItem(tr("2000/12/30"));
    dateCombo->addItem(tr("00-12-30"));
    dateCombo->addItem(tr("00.12.30"));
    dateCombo->addItem(tr("12��30"));
    dateCombo->addItem(tr("12.30.2000"));
    dateCombo->addItem(tr("2000-12-30"));
    dateCombo->addItem(tr("2000"));
    dateCombo->addItem(tr("12"));
    dateCombo->addItem(tr("30"));
 */
/*
//��ȡ�����ַ����Ŀ��
INT16U Get_DateStr_Width(INT8U Font, INT8U Type)
{
    INT8U chrNum;

    chrNum = 0;
    if(Type EQ 0)
        chrNum = 14;
    else if(Type EQ 1)
        chrNum = 12;
    else if(Type EQ 2)
        chrNum = 8;
    else if(Type EQ 3)
        chrNum = 8;
    else if(Type EQ 4)
        chrNum = 8;
    else if(Type EQ 5)
        chrNum = 8;
    else if(Type EQ 6)
        chrNum = 8;
    else if(Type EQ 7)
        chrNum = 10;
    else if(Type EQ 8)
        chrNum = 10;
    else if(Type EQ 9)
        chrNum = 4;
    else if(Type EQ 10)
        chrNum = 2;
    else if(Type EQ 11)
        chrNum = 2;
    else
        ASSERT_FAILED();

    return chrNum * Get_Font_Width(Font);
}

//��ʾ����
INT16U Get_WeekStr_Width(INT8U Font, INT8U Language, INT8U Week)
{
  return strlen(WeekStr[Language][Week])*Get_Font_Width(Font);
}
*/



//��ʾĳ����������--->ÿ10ms���øú�����ʵ�ֶ������ƶ���
//���ô˺���ǰ����ʾ�����Ѿ���ȡ��Show_Data_Bak�У�ͬʱProg_Status.Area_Status��Program_Para����Ϣ�Ѿ������

#define Put_Char(c) Buf[j++] = c
//����format��ap���������������Ϣ
void vsPrintf(char Buf[], CONST INT8S *format, va_list ap)
{

  INT8U j = 0;
  static const INT8S Chr[] = "0123456789ABCDEF";

  static const INT32U Oct[12]=
  {
    01,010,0100,01000,010000,0100000,01000000,010000000,
    0100000000,01000000000,010000000000,010000000000,
  }; //�˽���
  static const INT32U Dec[11]=
  {
    1,10,100,1000,10000,100000,1000000,
    10000000,100000000,1000000000,1000000000,
  }; //ʮ����
  static const INT32U Hex[8]=
  {
    0x1,0x10,0x100,0x1000,0x10000,
    0x100000,0x1000000,0x10000000,
  }; //ʮ������

  INT8U LintFlag;
  INT32U const *p;
  INT8S *pSrc;

  unsigned long int uParaValue;//�޷�����
  long int sParaValue;//�з�����

  INT8U c;
  INT8U i,Width,Len;

  for(;;)    //��������������
  {
    while((c=*format++)!='%')//%����֮ǰȫ���ַ���
    {
      if(!c)
        return;
      Put_Char(c);
    }

    c=*format++;
    //����ֵ���ʹ���
    switch(c)
    {
      case 'c':
        c = va_arg(ap, int);
        Put_Char(c);
        break;
      case 's':
        pSrc= va_arg(ap,INT8S *);
        while((c = *pSrc++)!=0)
          Put_Char(c);
        break;
    }

    //��ֵ���ʹ���
    if(c>='1' && c<='9')
    {
      Width=c-'0';
      c=*format++;
    }
    else
      Width=1;//���ٴ�ӡһ���ַ�

    if(c=='l' || c=='L')//�Ƿ���һ��������?
    {
      LintFlag=1;
      c=*format++;
    }
    else
      LintFlag=0;

    switch(c)//��ӡ��������
    {
      case 'o':
        p=Oct;
        Len=12;
        break;
      case 'd':
      case 'u':
        p=Dec;
        Len=11;
        break;
      case 'x':
        p=Hex;
        Len=8;
        break;

      default:
        continue;
    }

    //��ȡ������ֵ
    if(c=='d')//�з�����
    {
      if(LintFlag)//������
        sParaValue=va_arg(ap,long int);
      else
        sParaValue=va_arg(ap,int);

      if(sParaValue<0)
      {
        Put_Char('-');
        sParaValue=0-sParaValue;
      }
      uParaValue=(unsigned long int)sParaValue;//��ֵ��uParaValue,ͳһ����
    }
    else//�޷�����
    {
      if(LintFlag)//������
        uParaValue=va_arg(ap,unsigned long int);
      else
        uParaValue=va_arg(ap,int);
    }

    //�������ݱ���ĳ���
    for(i=0;i<Len;i++)
    {
       if(uParaValue<*(p+i))
         break;
    }

    if(Width<i)//i��ʾ���ݱ����ȣ�Width��ʾ��Ҫ��ӡ�ĳ���
      Width=i;

    //�ֱ��ӡÿ���ַ�
    i=0;//��ʾ�Ƿ��Ѿ��ҵ���һ����0λ
    for(;Width!=0;Width--)
    {
      c=(INT8U)(uParaValue/(*(p+Width-1)));
      uParaValue=uParaValue%(*(p+Width-1));
      //ǰ���0ȫ����ɿո�

      if(c==0 && i==0 && Width>1)//��λΪ0����֮ǰ��λҲ��Ϊ0,�Ҳ������һλ(��ֵ����Ϊ0)
        c='0';
      else
      {
        i=1;//��ʾ�Ѿ���һ����0λ��
        c=Chr[c];
      }
      Put_Char(c);
    }
  }
}

//Disp_Flag,1��ʾ���ԣ�0��ʾ����
  void Show_String(INT8U Str[], INT8U Font, INT8U Color, S_Show_Data *pData, INT8U Area_No, INT16U X,INT16U Y)
  {
    INT8U i;
    INT8U FontWidth;
    INT16U Unicode;
    //INT8U X_Bak;

    FontWidth = Get_Font_Width(Font)*2;


    i=0;
    //X_Bak = X;
    while(Str[i]!=0)
    {
      if(Str[i]>=0xA0)
      {
        Unicode=((INT16U)Str[i])*256+(INT16U)Str[i+1];
        Show_Char(Unicode, Font, Color, pData, Area_No, X, Y);
        X+=FontWidth;
        i=i+2;
      }
      else
      {
        if(Str[i]=='\r')
        {
          X=0;//X_Bak;
          i++;
        }
        else if(Str[i]=='\n')
        {
          Y+=FontWidth;
          i++;
        }
        else
        {
        Show_Char(Str[i], Font, Color, pData, Area_No, X, Y);
        X+=FontWidth / 2;
        i=i+1;
        }
      }
    }
  }

//����format��ap���������������Ϣ
INT16U LED_Print(INT8U Font, INT8U Color, S_Show_Data *pData, INT8U Area_No, INT16U X, INT16U Y, const INT8S *format,...)
{

	va_list ap;
	
	memset(Print_Buf, 0, sizeof(Print_Buf));
	va_start(ap,format);
        vsPrintf((char *)Print_Buf, format, ap);
	
	if(pData != (S_Show_Data *)0)
	  Show_String(Print_Buf, Font, Color, pData,  Area_No, X, Y);
	va_end(ap);
	
	return strlen((char *)Print_Buf)*Get_Font_Width(Font);
}

//ʵʱ��ʾĳ��������
INT16U RT_LED_Print(INT8U Font, INT8U Color, INT16U X, INT16U Y, INT16U Sec, const INT8S *format,...)
{
  va_list ap;

  Set_RT_Show_Area(0, 0, Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);
  RT_Play_Status_Enter(Sec);

  memset(Print_Buf, 0, sizeof(Print_Buf));

  va_start(ap,format);
  vsPrintf((char *)Print_Buf, format, ap);

  Show_String(Print_Buf, Font, Color, &Show_Data,  0, X, Y);
  
  va_end(ap);

  return strlen((char *)Print_Buf)*Get_Font_Width(Font);

}





