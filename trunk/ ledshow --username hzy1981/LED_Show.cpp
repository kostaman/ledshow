#define LED_SHOW_C
#include "Includes.h"


const CNZK_Info CN_ZK[]=
{
  {0,{0},{0},{0}}
};

//ÿ���ٶȵ���ʱ,��λΪ����
const INT16U Step_Delay[]=
{
  10,
  20,
  30,
  40,
  50,
  60,
  70,
  80,
  90,
  100
};

//�������뷽ʽ
const S_Mode_Func Mode_Func[]=
{
  {&Move_Left},//0
  {&Move_Right},//1
  {&Move_Up},//2
  {&Move_Down},//3
  {&Move_Left_Cover},//4
  {&Move_Right_Cover},//5
  {&Move_Up_Cover},//6
  {&Move_Down_Cover},//7
  {&Move_Left_Up_Cover},//8
  {&Move_Right_Up_Cover},//9
  {&Move_Left_Down_Cover},//10
  {&Move_Right_Down_Cover},//11
  {&Move_Left_Right_Open},//12
  {&Move_Up_Down_Open},//13
  {&Move_Left_Right_Close},//14
  {&Move_Up_Down_Close},//15
  
};

//��ȡ����ɫ
INT8U Get_Color()
{
  if(!(Screen_Para.Color <=2))
    return 0;
  else
  {
    return Screen_Para.Color;
  } 
}  

//��ȡ�������е�Indexλ��ֵ
INT8U Get_Buf_Bit(INT8U Buf[], INT32U Buf_Size, INT32U Index)
{
  if(Index >= (INT32U)Buf_Size * 8)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  return (Buf[Index >>3] & (0x01 << (Index & 0x07)))>0?1:0;
}

//���û������е�Indexλ��ֵ
void Set_Buf_Bit(INT8U Buf[], INT32U Buf_Size, INT32U Index, INT8U Value)
{
  if(Index >= Buf_Size * 8)
  {
    ASSERT_FAILED();
    return;
  }
  
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
  
  Index = ((Y/8 * Width) + X)*8 + Y %8;
  return Get_Buf_Bit(Buf, Buf_Size, Index);//Index;
  
}

//����һ���������ݻ�������ĳ������ֵ 
//Buf_SizeΪ����������,WidthΪ����������
//X\YΪ�����е������
//ValueΪ�õ�ֵ
void Set_Rect_Buf_Bit(INT8U Buf[], INT16U Buf_Size, INT16U Width, INT16U X, INT16U Y, INT8U Value)
{
  INT16U Index;
  
  Index = ((Y/8 * Width) + X)*8 + Y %8;
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

  for(i = 0; i <Src_Len *8; i ++)
  {
    Re = Get_Buf_Bit(pSrc, Src_Len, i);
    X0 = (Src_Off*8 + i) % X_Len;
    Y0 = (Src_Off*8 + i) / X_Len;
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
  if(Area_No >= MAX_AREA_NUM)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  return Program_Para.Area[Area_No].X_Len;
}

//��ȡĳ�������ĸ߶�
//Area_No������
INT16U Get_Area_Height(INT8U Area_No)
{
  if(Area_No >= MAX_AREA_NUM)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  return Program_Para.Area[Area_No].Y_Len;  
}

//��ȡһ�����������ظ���,Area_No��ʾ������
INT32U Get_Area_Size(INT8U Area_No)
{
  if(Area_No >= MAX_AREA_NUM)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  return (INT32U)Program_Para.Area[Area_No].X_Len * Program_Para.Area[Area_No].Y_Len;  
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
  
  pPoint->X = Program_Para.Area[Area_No].X;
  pPoint->Y = Program_Para.Area[Area_No].Y;
  
  return 1;
}

//��ȡ������ĳ�������
//Area_No��ʾ������
//x,y��ʾ�ڷ����ڵ�����
INT32U Get_Area_Point_Index(INT8U Area_No, INT16U X, INT16U Y)
{
  INT32U Index;
  
  if(Area_No > MAX_AREA_NUM)
  {
    ASSERT_FAILED();
    return 0;	
  }
  
  if(X >= Program_Para.Area[Area_No].X_Len ||\
     Y >= Program_Para.Area[Area_No].Y_Len)
  {
    ASSERT_FAILED();
    return 0;
  }

  X += Program_Para.Area[Area_No].X;
  Y += Program_Para.Area[Area_No].Y;
 
  if(X >= Screen_Para.Width ||\
     Y >= Screen_Para.Height)
  {
    ASSERT_FAILED();
    return 0;
  }

  Index = (((Y>>3) * Screen_Para.Width) + X)*8 + (Y & 0x07);
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

//��ǰ��Ŀ��ĳ������,��0λ����2λ�ֱ�Ϊ������ɫ
//pSrc_Buf����ʾ����buf
//Area_No��������
//x,y��������
INT8U Get_Area_Point_Data(S_Show_Data *pSrc_Buf, INT8U Area_No, INT16U X, INT16U Y) //��ȡһ��������һ���������
{
  INT32U Index;

  Index = Get_Area_Point_Index(Area_No, X, Y);
  
  if(Screen_Para.Color EQ 0)  //��ɫ��
    return Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data),Index);
  else if(Screen_Para.Color EQ 1) //˫ɫ��
    return Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), ((Index>>3)<<4) + (Index & 0x07)) +\
      (Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), ((Index>>3)<<4) + 8 + (Index & 0x07))<<1);
  else if(Screen_Para.Color EQ 2) //��ɫ��
    return Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), (Index>>3)*24 + (Index & 0x07)) +\
      (Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), (Index>>3)*24 + 8 + (Index & 0x07))<<1)+
      (Get_Buf_Bit(pSrc_Buf->Color_Data, sizeof(pSrc_Buf->Color_Data), (Index>>3)*24 + 16 + (Index & 0x07))<<2);
  else
    return 0;
}
/*
INT8U Get_Area_Offset_Len(S_Show_Data *pBuf, INT8U Area_No, INT8U **pOff, INT16U *pLen)
{
  INT32U Index;
  
  Index = Get_Area_Point_Index(Area_No, X, Y);
 
  if(Screen_Para.Color EQ 0)  //��ɫ��
    return Get_Buf_Bit(pSrc_Buf->One_Color_Data.Color0, sizeof(pSrc_Buf->One_Color_Data.Color0),Index);
  else if(Screen_Para.Color EQ 1) //˫ɫ��
    return Get_Buf_Bit(pSrc_Buf->Two_Color_Data.Color0, sizeof(pSrc_Buf->Two_Color_Data.Color0), Index) +\
      (Get_Buf_Bit(pSrc_Buf->Two_Color_Data.Color1, sizeof(pSrc_Buf->Two_Color_Data.Color1), Index) << 1);
  else if(Screen_Para.Color EQ 2) //��ɫ��
    return Get_Buf_Bit(pSrc_Buf->Three_Color_Data.Color0, sizeof(pSrc_Buf->Two_Color_Data.Color0), Index) + \
      (Get_Buf_Bit(pSrc_Buf->Three_Color_Data.Color1, sizeof(pSrc_Buf->Three_Color_Data.Color1), Index) << 1) +\
        (Get_Buf_Bit(pSrc_Buf->Three_Color_Data.Color2, sizeof(pSrc_Buf->Three_Color_Data.Color2), Index) << 2);
  else
    return 0;  
  
}
*/
//����ĳ��Ŀ������ĳ�������,��0-2λ�ֱ��ʾ������ɫ
//pDst_Buf�����ø���ʾ�����еĵ�
//Area_No��ʾ������
//x,y����λ��
//Value��
void Set_Area_Point_Data(S_Show_Data *pDst_Buf, INT8U Area_No, INT16U X, INT16U Y, INT8U Value) //����һ������ĵ�   
{
  INT32U Index;
  
  Index = Get_Area_Point_Index(Area_No, X, Y);
  
  if(Screen_Para.Color EQ 0)  //��ɫ��
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data),Index, (Value & 0x01));
  else if(Screen_Para.Color EQ 1) //˫ɫ��
  {
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), ((Index>>3)<<4) + (Index & 0x07), (Value & 0x01));
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), ((Index>>3)<<4) + 8+ (Index & 0x07), (Value & 0x02)>>1);
  }
  else if(Screen_Para.Color EQ 2) //��ɫ��
  {
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), (Index>>3)*24 + (Index & 0x07), (Value & 0x01));
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), (Index>>3)*24 + 8 + (Index & 0x07), (Value & 0x02)>>1);
    Set_Buf_Bit(pDst_Buf->Color_Data, sizeof(pDst_Buf->Color_Data), (Index>>3)*24 + 16 + (Index & 0x07), (Value & 0x04)>>2);
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
  else
  {
    return pPoint1;
  }  
}

//��ȡ������֮�е��ұ�һ���㣬X����ϴ��һ��
S_Point * Get_Right_Point(S_Point *pPoint0, S_Point *pPoint1)
{
  if(pPoint0->X > pPoint1->X) //point0�������
  {
    return pPoint0;
  }
  else
  {
    return pPoint1;
  }  
}

S_Point * Get_Up_Point(S_Point *pPoint0, S_Point *pPoint1)
{
  if(pPoint0->Y < pPoint1->Y) //point0�����ϱ�
  {
    return pPoint0;
  }
  else
  {
    return pPoint1;
  }
}

//��ȡ������֮�е��±�һ���㣬Y����ϴ��һ��
S_Point * Get_Down_Point(S_Point *pPoint0, S_Point *pPoint1)
{
  if(pPoint0->Y > pPoint1->Y) //point0�����±�
  {
    return pPoint0;
  }
  else
  {
    return pPoint1;
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
{
  INT8U Data;
  S_Point *p0, *p1;
  INT32S i,j;
  
  p0 = Get_Left_Point(pPoint0, pPoint1);
  p1 = Get_Right_Point(pPoint0, pPoint1);
  
  if(p0 != p1) //�����ڴ�ֱ��һ������
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
  
  p0 = Get_Left_Point(pPoint0, pPoint1);
  p1 = Get_Right_Point(pPoint0, pPoint1);
  
  if(p0 != p1)
  {
      for(i = p0 -> X; i <= p1->X ; i ++)
      {
        j = GET_LINE_Y((INT32S)p0->X,(INT32S)p0->Y, (INT32S)p1->X, (INT32S)p1->Y, i);//(INT32S)pLeft->Y + (INT32S)(i - pLeft ->X)((INT32S)(pRgiht->Y) - (INT32S)(pLeft->Y))/(pRight -> X - pLeft->X) ;

        if(j < 0)
          ASSERT_FAILED();

        Set_Area_Point_Data(pDst_Buf, Area_No, (INT16U)i, (INT16U)j, Value);
      }
  }
  else
  {
      p0 = Get_Up_Point(pPoint0, pPoint1);
      p1 = Get_Down_Point(pPoint0, pPoint1);

      for(j = p0->Y; j <=p1->Y; j ++)
        Set_Area_Point_Data(pDst_Buf, Area_No, p0->X, j, Value);
  }

}

//����һ������������--��ֱ��������
//pSrc_Buf Դ��ʾbuf
//pPoint0, pPoint1, pPoint2 ��ʾԴ���ǵĵ����������
//pDst_Buf Ŀ����ʾbuf
//pPoint3 Ŀ������λ�ã���ӦpPoint0
void Copy_Filled_Triangle(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1,S_Point *pPoint2,\
  S_Show_Data *pDst_Buf, S_Point *pPoint3)  //����һ������������

{/*
  S_Point *pLeft;  //����ߵĵ�
  S_Point *pRight; //���ұߵĵ�
  S_Point Temp;
  S_Point Temp1;
  
  pLeft = Get_Left_Point(pPoint0, pPoint1);
  pRight = Get_Right_Point(pPoint0, pPoint1);
  
  Temp.X = pLeft -> X;  //�м��X
  
  while(Temp.X != pRight -> X)
  {
    Temp.Y = GET_LINE_Y((INT32S)pLeft ->X, (INT32S)pLeft->Y, (INT32S)pRight->X, (INT32S)pRight->Y, (INT32S)Temp.X);
    Temp1.X = (INT16U)((INT32S)Temp.X + (INT32S)(pPoint3 -> X) - (INT32S)(pPoint0 -> X));
    Temp1.Y = (INT16U)((INT32S)Temp.Y + (INT32S)(pPoint3 -> Y) - (INT32S)(pPoint0 -> Y));
    Copy_Line(pSrc_Buf, Area_No, &Temp, pPoint2, pDst_Buf, &Temp1);
    Temp.X ++;
  }
  */
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

  do
  {
    Temp0.Y = GET_LINE_Y((INT32S)pLeft ->X, (INT32S)pLeft->Y, (INT32S)pRight->X, (INT32S)pRight->Y, (INT32S)Temp0.X);
    Temp1.X = Temp0.X;
    if(Temp1.X < pMid->X)
      Temp1.Y = GET_LINE_Y((INT32S)pLeft ->X, (INT32S)pLeft->Y, (INT32S)pMid->X, (INT32S)pMid->Y, (INT32S)Temp1.X);
    else
      Temp1.Y = GET_LINE_Y((INT32S)pRight ->X, (INT32S)pRight->Y, (INT32S)pMid->X, (INT32S)pMid->Y, (INT32S)Temp1.X);
    //Draw_Line(pDst_Buf, Area_No, &Temp0, &Temp1, Value);
    Temp2.X = Temp0.X + pPoint3->X - pPoint0->X;
    Temp2.Y = Temp0.Y + pPoint3->Y - pPoint0->Y;

    Copy_Line(pSrc_Buf, 0, &Temp0, &Temp1, pDst_Buf, &Temp2);
    Temp0.X ++;
  }while(Temp0.X <= pRight -> X);
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
  S_Point Temp0, Temp1;
  
  pLeft = Get_Left_Point(pPoint0, pPoint1);
  pLeft = Get_Left_Point(pLeft, pPoint2);

  pRight = Get_Right_Point(pPoint0, pPoint1);
  pRight = Get_Right_Point(pRight, pPoint2);

  pMid = Get_X_Mid_Point(pPoint0, pPoint1, pPoint2);

  //Draw_Line(pDst_Buf, Area_No, pPoint0, pPoint1, Value);
  //Draw_Line(pDst_Buf, Area_No, pPoint1, pPoint2, Value);
  //Draw_Line(pDst_Buf, Area_No, pPoint2, pPoint0, Value);

  Temp0.X = pLeft -> X;  //�м��X
  
  do
  {
    Temp0.Y = GET_LINE_Y((INT32S)pLeft ->X, (INT32S)pLeft->Y, (INT32S)pRight->X, (INT32S)pRight->Y, (INT32S)Temp0.X);
    Temp1.X = Temp0.X;
    if(Temp1.X < pMid->X)
      Temp1.Y = GET_LINE_Y((INT32S)pLeft ->X, (INT32S)pLeft->Y, (INT32S)pMid->X, (INT32S)pMid->Y, (INT32S)Temp1.X);
    else
      Temp1.Y = GET_LINE_Y((INT32S)pRight ->X, (INT32S)pRight->Y, (INT32S)pMid->X, (INT32S)pMid->Y, (INT32S)Temp1.X);
    Draw_Line(pDst_Buf, Area_No, &Temp0, &Temp1, Value);
    Temp0.X ++;
  }while(Temp0.X <= pRight -> X);
}

//����һ�������
void Copy_Filled_Polygon(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1,S_Point *pPoint2, S_Point *pPoint3,\
  S_Show_Data *pDst_Buf, S_Point *pPoint4)
{
  Copy_Filled_Triangle(pSrc_Buf, Area_No, pPoint0, pPoint1, pPoint2, pDst_Buf, pPoint4);
  Copy_Filled_Triangle(pSrc_Buf, Area_No, pPoint0, pPoint2, pPoint3, pDst_Buf, pPoint4);
}

//���һ�������
void Fill_Polygon(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint0, S_Point *pPoint1,S_Point *pPoint2, S_Point *pPoint3, INT8U Value)
{
  Fill_Triangle(pDst_Buf, Area_No, pPoint0, pPoint3, pPoint2, Value);
  Fill_Triangle(pDst_Buf, Area_No, pPoint0, pPoint1, pPoint2, Value);

}

//����һ������
void Copy_Filled_Rect(S_Show_Data *pSrc_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len,\
  S_Show_Data *pDst_Buf, S_Point *pPoint1)
{
  INT16U i,j;
  INT8U Data;
  
  for(i = 0; i < X_Len;  i++)
    for(j = 0; j < Y_Len; j++)
    {
      Data = Get_Area_Point_Data(pSrc_Buf, Area_No, pPoint0->X + i, pPoint0->Y + j);
      Set_Area_Point_Data(pDst_Buf, Area_No, pPoint1->X + i, pPoint1->Y + j, Data);
    }  
}

//���һ������
void Fill_Rect(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pPoint0, INT16U X_Len, INT16U Y_Len,INT8U Value)
{
  INT16U i,j;
  //INT8U Data;
  
  for(i = 0; i < X_Len;  i++)
    for(j = 0; j < Y_Len; j++)
    {
      //Data = Get_Area_Point_Data(pSrc_Buf, Area_No, i, j); 
      Set_Area_Point_Data(pDst_Buf, Area_No, pPoint0->X + i, pPoint0->Y + j, Value);
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
  
  X = pCenter -> X - Radius; //�����һ���X����
  
  for(; X <= pCenter -> X + Radius; X ++)
  {
    Temp0 = ((INT32S)Radius * Radius - ((INT32S)X - (INT32S)pCenter->X)*((INT32S)X - (INT32S)pCenter->X));
    Temp = (INT16U)sqrt(Temp0);
    //����һ��
    Up.Y = pCenter->Y + Temp;
    Up.X = X;
    //����һ��
    if(pCenter->Y >= Temp)
      Down.Y = pCenter->Y- Temp;
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
  
  X = pCenter0 -> X - Radius; //�����һ���X����
  
  for(; X <= pCenter0 -> X + Radius; X ++)
  {
    Temp1 = (INT16U)sqrt((float)(Radius * Radius - (INT16U)((INT32S)X - (INT32S)pCenter0->X)*((INT32S)X - (INT32S)pCenter0->X)));
    //����һ��
    Up.Y = pCenter0->Y + Temp1;
    Up.X = X;
    //����һ��
    Down.Y = pCenter0->Y- Temp1;
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
  pPoint1 -> X = (INT16U)((INT16S)pPoint0->X + (INT16S)Len * cos(2*PI*Angle/360));
  pPoint1 -> Y = (INT16U)((INT16S)pPoint0->Y - (INT16S)Len * sin(2*PI*Angle/360));
}

//pDst_Buf,��ʾĿ�껺����
//Area_No, ��ʾ����
//pCenter,ʱ������
//Angle,�Ƕ�,-359->359
//Len,�����������ĵĳ���
//Radius,��İ뾶
//Value,���ֵҲ������ɫ
void Fill_Clock_Point(S_Show_Data *pDst_Buf, INT8U Area_No, S_Point *pCenter, \
                      INT16S Angle, INT16U Len, INT16U Radius, INT8U Value)
{
   S_Point Point;
   
   Get_Angle_Point(pCenter, Angle, Len, &Point); //�ҵ�Բ�����ĵ�
   Fill_Round(pDst_Buf, Area_No, &Point, Radius, Value); //����һ��Բ
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
  
  Get_Angle_Point(pCenter, Angle, Len * 7 / 10, &Point0); //ǰ�˵Ķ���
  Get_Angle_Point(pCenter, Angle - 90, Width/2, &Point1);
  Get_Angle_Point(pCenter, Angle + 90, Width/2, &Point2);
  
  Fill_Triangle(pDst_Buf, Area_No, &Point0, &Point1, &Point2, Value);
  
  Get_Angle_Point(pCenter, Angle + 180, Len * 3 / 10, &Point0); //��˵Ķ���
  Get_Angle_Point(pCenter, Angle + 180 - 90, Width/2, &Point1);
  Get_Angle_Point(pCenter, Angle + 180 + 90, Width/2, &Point2);
  
  Fill_Triangle(pDst_Buf, Area_No, &Point0, &Point1, &Point2, Value); 
}

//���ĳ����������ʾ
//pDst_Buf��ʾ������
void Clear_Area_Data(S_Show_Data *pDst_Buf, INT8U Area_No)
{
  INT16U X,Y,X_Len,Y_Len;
  
  X_Len = Get_Area_Width(Area_No);
  Y_Len = Get_Area_Height(Area_No);
  
  for(X = 0; X < X_Len; X++)
    for(Y = 0; Y < Y_Len; Y++)
    {
      Set_Area_Point_Data(pDst_Buf, Area_No, X, Y, 0);
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

//����
void Move_Up(INT8U Area_No)//���ƶ�
{
  S_Point Temp;
  S_Point Temp1;
  
  if(Area_Status[Area_No].Step < 100) //�Ƿ��Ѿ��ƶ����100%
  {
    Temp.X = 0;//Program_Para.Area[Area_No].X;
    Temp.Y = 0;//Program_Para.Area[Area_No].Y;
    
    Temp1.X = 0;//Program_Para.Area[Area_No].X;// + Step +
    Temp1.Y = (100 - Area_Status[Area_No].Step) * Program_Para.Area[Area_No].Y_Len / 100;
    
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Program_Para.Area[Area_No].X_Len, Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 100,\
      &Show_Data, &Temp1);
    Area_Status[Area_No].Step += MOVE_STEP;
  } 
}

//����
void Move_Down(INT8U Area_No)
{
  S_Point Temp;
  S_Point Temp1;
  
  if(Area_Status[Area_No].Step < 100) //�Ƿ��Ѿ��ƶ����100%
  {
    Temp.X = 0;//Program_Para.Area[Area_No].X;// + Step +
    Temp.Y = (100 - Area_Status[Area_No].Step) * Program_Para.Area[Area_No].Y_Len / 100;
    
    Temp1.X = 0;//Program_Para.Area[Area_No].X;
    Temp1.Y = 0;//Program_Para.Area[Area_No].Y;
    
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Program_Para.Area[Area_No].X_Len, Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 100,\
      &Show_Data, &Temp1);
    Area_Status[Area_No].Step += MOVE_STEP;
  } 
}

//����
void Move_Left(INT8U Area_No)
{
  S_Point Temp;
  S_Point Temp1;
  
  if(Area_Status[Area_No].Step < 100) //�Ƿ��Ѿ��ƶ����100%
  {
    Temp.X = 0;//Program_Para.Area[Area_No].X;
    Temp.Y = 0;//Program_Para.Area[Area_No].Y;
    
    Temp1.X = (100 - Area_Status[Area_No].Step) * Program_Para.Area[Area_No].X_Len / 100;// + Step +
    Temp1.Y = 0;
    
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Area_Status[Area_No].Step * Program_Para.Area[Area_No].X_Len / 100,Program_Para.Area[Area_No].Y_Len, \
      &Show_Data, &Temp1);
    Area_Status[Area_No].Step += MOVE_STEP;
  }   
}

//�ұ���
void Move_Right(INT8U Area_No)
{
  S_Point Temp;
  S_Point Temp1;
  
  if(Area_Status[Area_No].Step < 100) //�Ƿ��Ѿ��ƶ����100%
  {
    Temp.X = (100 - Area_Status[Area_No].Step) * Program_Para.Area[Area_No].Y_Len / 100;// + Step +
    Temp.Y = 0;
    
    Temp1.X = 0;//Program_Para.Area[Area_No].X;
    Temp1.Y = 0;//Program_Para.Area[Area_No].Y;
    
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp,  Area_Status[Area_No].Step * Program_Para.Area[Area_No].X_Len / 100,Program_Para.Area[Area_No].Y_Len,\
      &Show_Data, &Temp1);
    Area_Status[Area_No].Step += MOVE_STEP;
  } 
}

//�ϻ�
void Move_Up_Cover(INT8U Area_No)
{
  S_Point Temp;
  
  if(Area_Status[Area_No].Step < 100) //�Ƿ��Ѿ��ƶ����100%
  {
    Temp.X = 0;// + (100 - Area_Status[Area_No].Step) * Program_Para.Area[Area_No].Y_Len / 100;
    Temp.Y = (100 - Area_Status[Area_No].Step) * Program_Para.Area[Area_No].Y_Len / 100;
    
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Program_Para.Area[Area_No].X_Len, MOVE_STEP * Program_Para.Area[Area_No].Y_Len / 100,\
      &Show_Data, &Temp);
    Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//�»�
void Move_Down_Cover(INT8U Area_No)
{
  S_Point Temp;
  
  if(Area_Status[Area_No].Step < 100) //�Ƿ��Ѿ��ƶ����100%
  {
    Temp.X = 0;// + Step +
    Temp.Y = Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 100;
    
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Program_Para.Area[Area_No].X_Len, MOVE_STEP * Program_Para.Area[Area_No].Y_Len / 100,\
      &Show_Data, &Temp);
    Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//��
void Move_Left_Cover(INT8U Area_No)
{
  S_Point Temp;
  
  if(Area_Status[Area_No].Step < 100) //�Ƿ��Ѿ��ƶ����100%
  {
    Temp.X = (100 - Area_Status[Area_No].Step) * Program_Para.Area[Area_No].X_Len / 100;// + Step +
    Temp.Y = 0;
    
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, MOVE_STEP * Program_Para.Area[Area_No].X_Len / 100, Program_Para.Area[Area_No].Y_Len,\
      &Show_Data, &Temp);
    Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//�һ�
void Move_Right_Cover(INT8U Area_No)
{
  S_Point Temp;
  S_Point Temp1;
  
  if(Area_Status[Area_No].Step < 100) //�Ƿ��Ѿ��ƶ����100%
  {
    Temp.X = Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 100;// + Step +
    Temp.Y = 0;
    
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp,  MOVE_STEP * Program_Para.Area[Area_No].X_Len / 100,Program_Para.Area[Area_No].Y_Len,\
      &Show_Data, &Temp1);
    Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//���ϻ�
void Move_Left_Up_Cover(INT8U Area_No)
{
  S_Point Left,Up,Right;
  
  if(Area_Status[Area_No].Step < 100)
  {
    Left.X = (100 - Area_Status[Area_No].Step)*Program_Para.Area[Area_No].X_Len / 100;
    Left.Y = Program_Para.Area[Area_No].Y_Len;
    
    Up.X = Program_Para.Area[Area_No].X_Len;
    Up.Y = (100 - Area_Status[Area_No].Step)*Program_Para.Area[Area_No].Y_Len / 100;
    
    Right.X = Program_Para.Area[Area_No].X_Len;
    Right.Y = Program_Para.Area[Area_No].Y_Len;
    
    Copy_Filled_Triangle(&Show_Data_Bak, Area_No, &Left, &Up, &Right, &Show_Data, &Left);
    Area_Status[Area_No].Step += MOVE_STEP;
  }
}

//���ϻ�
void Move_Right_Up_Cover(INT8U Area_No)
{
  S_Point Left,Up,Right;
  
  if(Area_Status[Area_No].Step < 100)
  {
    Left.X = 0;//Program_Para.Area[Area_No].X;
    Left.Y = Program_Para.Area[Area_No].Y_Len;
    
    Right.X = Area_Status[Area_No].Step * Program_Para.Area[Area_No].X_Len / 100;
    Right.Y = Program_Para.Area[Area_No].Y_Len;
    
    Up.X = 0;//Program_Para.Area[Area_No].X;
    Up.Y = (100 - Area_Status[Area_No].Step)*Program_Para.Area[Area_No].Y_Len / 100;
    
    Copy_Filled_Triangle(&Show_Data_Bak, Area_No, &Left, &Up, &Right, &Show_Data, &Left);
    Area_Status[Area_No].Step += MOVE_STEP;
  }
  
}

//���»�
void Move_Left_Down_Cover(INT8U Area_No)
{
  S_Point Left,Up,Right;
  
  if(Area_Status[Area_No].Step < 100)
  {
    Left.X = (100 - Area_Status[Area_No].Step)*Program_Para.Area[Area_No].X_Len / 100; 
    Left.Y = 0;
    
    Right.X = Program_Para.Area[Area_No].X_Len;
    Right.Y = Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 100;
    
    Up.X = Program_Para.Area[Area_No].X_Len;
    Up.Y = 0;
    
    Copy_Filled_Triangle(&Show_Data_Bak, Area_No, &Left, &Up, &Right, &Show_Data, &Left);
    Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//���»�
void Move_Right_Down_Cover(INT8U Area_No)
{
  S_Point Left,Up,Right;
  
  if(Area_Status[Area_No].Step < 100)
  {
    Left.X = 0;// + (100 - Area_Status[Area_No].Step)*Program_Para.Area[Area_No].X_Len / 100; 
    Left.Y = Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 100;
    
    Right.X = Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 100;
    Right.Y = 0;// + Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 100;
    
    Up.X = 0;// + Program_Para.Area[Area_No].X_Len;
    Up.Y = 0;
    
    Copy_Filled_Triangle(&Show_Data_Bak, Area_No, &Left, &Up, &Right, &Show_Data, &Left);
    Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//��������
void Move_Up_Down_Open(INT8U Area_No)
{
  S_Point Temp;
  
  if(Area_Status[Area_No].Step < 100)
  {
    Temp.X = 0;
    Temp.Y = (100 - Area_Status[Area_No].Step)*Program_Para.Area[Area_No].Y_Len / 200; 
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Program_Para.Area[Area_No].X_Len, Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 100, &Show_Data, &Temp);
    Area_Status[Area_No].Step += MOVE_STEP;
  }
  
}

//���º���
void Move_Up_Down_Close(INT8U Area_No)
{
  S_Point Temp;
  
  if(Area_Status[Area_No].Step < 100)
  {
    Temp.X = 0;
    Temp.Y = 0;// + Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 200; 
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Program_Para.Area[Area_No].X_Len, Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 200, &Show_Data, &Temp);
    
    Temp.X = 0;
    Temp.Y = Program_Para.Area[Area_No].Y_Len - Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 200; 
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Program_Para.Area[Area_No].X_Len, Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 200, &Show_Data, &Temp);
    Area_Status[Area_No].Step += MOVE_STEP;
  }  
}

//���ҿ���
void Move_Left_Right_Open(INT8U Area_No)
{
  S_Point Temp;
  
  if(Area_Status[Area_No].Step < 100)
  {
    Temp.X = (100 - Area_Status[Area_No].Step)*Program_Para.Area[Area_No].X_Len / 200;
    Temp.Y = 0; 
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp,  Area_Status[Area_No].Step * Program_Para.Area[Area_No].X_Len / 100, Program_Para.Area[Area_No].Y_Len, &Show_Data, &Temp);
    Area_Status[Area_No].Step += MOVE_STEP;
  }
  
}

//���Һ���
void Move_Left_Right_Close(INT8U Area_No)
{
  S_Point Temp;
  
  if(Area_Status[Area_No].Step < 100)
  {
    Temp.X = 0;
    Temp.Y = 0;// + Area_Status[Area_No].Step * Program_Para.Area[Area_No].Y_Len / 200; 
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Area_Status[Area_No].Step * Program_Para.Area[Area_No].X_Len / 200, Program_Para.Area[Area_No].Y_Len,  &Show_Data, &Temp);
    
    Temp.X = Program_Para.Area[Area_No].X_Len - Area_Status[Area_No].Step * Program_Para.Area[Area_No].X_Len / 200;
    Temp.Y = 0; 
    Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Temp, Area_Status[Area_No].Step * Program_Para.Area[Area_No].X_Len / 200, Program_Para.Area[Area_No].Y_Len, &Show_Data, &Temp);
    Area_Status[Area_No].Step += MOVE_STEP;
  }  
}




//��ȡĳ����������ĳ��������ͣ��ʱ��
INT8U Get_Area_Step_Delay(INT8U Area_No)
{
  INT8U Step;
  
  if(Area_No >= MAX_AREA_NUM)
  {
    ASSERT_FAILED();
    return Step_Delay[0];
  }
  
  Step = File_Para[Area_No].Pic_Para.In_Speed; //�����ٶ�
  if(Step >= sizeof(Step_Delay)/sizeof(Step_Delay))
    Step = sizeof(Step_Delay)/sizeof(Step_Delay);
  
  return Step_Delay[Step];
}

//��ȡ�ļ���ͣ��ʱ��,��λΪms
//ԭ�������Ϊ��ʾ��λ��0Ϊs��1Ϊms
INT32U Get_File_Stay_Time(INT8U Area_No)
{
  if((File_Para[Area_No].Pic_Para.Stay_Time & 0x8000) > 0)
    return (INT32U)(File_Para[Area_No].Pic_Para.Stay_Time & 0x7FFF);
  else
    return (INT32U)File_Para[Area_No].Pic_Para.Stay_Time * 1000;
}

//�����ļ���ͣ��ʱ��
void Set_File_Stay_Time(INT8U Area_No, INT16U ms)
{
  File_Para[Area_No].Pic_Para.Stay_Time = ms;
  File_Para[Area_No].Pic_Para.Stay_Time = File_Para[Area_No].Pic_Para.Stay_Time | 0x80;
}

//��ʾĳ����������--->ÿ10ms���øú�����ʵ�ֶ������ƶ���
//���ô˺���ǰ����ʾ�����Ѿ���ȡ��Show_Data_Bak�У�ͬʱArea_Status��Program_Para����Ϣ�Ѿ������
void Update_Pic_Data(INT8U Area_No)
{
  INT8U In_Mode;
  //�����ƶ�״̬
  if(Area_Status[Area_No].Step < 100)
  {
    if(Area_Status[Area_No].Step_Timer < Get_Area_Step_Delay(Area_No))
      Area_Status[Area_No].Step_Timer += MOVE_STEP_TIMER;
    else
    {
      In_Mode = File_Para[Area_No].Pic_Para.In_Mode;
      (*(Mode_Func[In_Mode].Func))(Area_No);//ִ���ƶ�����
    }
  }
  else if(Area_Status[Area_No].Stay_Time <= Get_File_Stay_Time(Area_No)) //ͣ��ʱ��δ��
  {
    Area_Status[Area_No].Stay_Time += MOVE_STEP_TIMER;
  }
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
  Point.X = File_Para[Area_No].Clock_Para.Bk_X;
  Point.Y = File_Para[Area_No].Clock_Para.Bk_Y;
  X_Len = File_Para[Area_No].Clock_Para.Bk_Width;
  Y_Len = File_Para[Area_No].Clock_Para.Bk_Height;
  
  Copy_Filled_Rect(&Show_Data_Bak, Area_No, &Point, X_Len, Y_Len, &Show_Data, &Point);
}

//���¶�ʱ������
void Update_Timer_Data(INT8U Area_No)
{
  
  
}

//����ʱ������
void Update_Time_Data(INT8U Area_No)
{
  
  
}

//�����¶�����
void Update_Temp_Data(INT8U Area_No)
{
  
  
}

//ÿ��MOVE_STEP_TIMER ms���øú���,ʵ���ƶ���ʾ��Ч��
void Update_Show_Data()
{
  INT8U i;
  //static S_Int8U Ms10_Timer
  for(i = 0; i < Program_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
    if(File_Para[i].Pic_Para.Flag EQ SHOW_PIC)
      Update_Pic_Data(i);
    else if(File_Para[i].Pic_Para.Flag EQ SHOW_CLOCK)
      Update_Clock_Data(i);
    else if(File_Para[i].Pic_Para.Flag EQ SHOW_TIMER)
      Update_Timer_Data(i);
    else if(File_Para[i].Pic_Para.Flag EQ SHOW_TIME)
      Update_Time_Data(i);
    else if(File_Para[i].Pic_Para.Flag EQ SHOW_TEMP)
      Update_Temp_Data(i);
  }
}

//��ȡһ����ʾ����
//prog��Ŀ��
//area������
INT8S Update_Show_Data_Bak(INT8U Prog_No, INT8U Area_No)
{
  INT8S Re;
  INT8U Seq;
  char File_Name[MAX_FILE_NAME_SIZE];
  FILE_T File;
  INT16U Ctrl_Code;
  INT32S Len, Len0;
  INT32U Dst_Index, Size;
  INT16U X,Y,X_Len,Y_Len;

  Re = AREA_OK;
  //Read_Para();
  Get_Program_Data_File_Name(Prog_No, Area_No, File_Name); //��ȡ�÷�������ʾ�ļ�

  File = File_Open(File_Name, FILE_R); //Read_

  Len = File_Read_One_Frame(File, Area_Status[Area_No].File_Offset, &Seq, &Ctrl_Code, Pub_Buf, Pub_Buf, sizeof(Pub_Buf));
  if(Len EQ FILE_END) //�ļ�����--��ͷ��ʼ����
  {
    Area_Status[Area_No].File_Offset = 0;
    Area_Status[Area_No].File_Type = 0;
    Len = File_Read_One_Frame(File, Area_Status[Area_No].File_Offset, &Seq, &Ctrl_Code, Pub_Buf, Pub_Buf, sizeof(Pub_Buf));
  }

  if(Seq EQ 0)//---�����ǵ�һ֡,�Ƚ���ʾ��ز������Ƶ�File_Para�ṹ����
  {
    Area_Status[Area_No].File_Offset += Len;

    if(Len > (sizeof(S_Pic_Para) - 2)) //��һ֡
    {
      Len0 = 0;

      Dst_Index = Get_Area_Point_Index(Area_No, 0, 0);
      Size = 0;
      Area_Status[Area_No].File_Type = Pub_Buf[0];

      if(Pub_Buf[0] EQ SHOW_PIC) //ͼ��
      {
        Len0 =  sizeof(File_Para[Area_No].Pic_Para) - 2;
        mem_cpy(&File_Para[Area_No].Pic_Para.Flag, Pub_Buf, Len0, &File_Para[Area_No].Pic_Para, sizeof(File_Para[Area_No].Pic_Para));
        X = 0;
        Y = 0;
        X_Len = Program_Para.Area[Area_No].X_Len;
        Y_Len = Program_Para.Area[Area_No].Y_Len;
      }
      else if(Pub_Buf[0] EQ SHOW_CLOCK)//����
      {
        Len0 =  sizeof(File_Para[Area_No].Clock_Para) - 2;
        mem_cpy(&File_Para[Area_No].Clock_Para.Flag, Pub_Buf, Len0, &File_Para[Area_No].Clock_Para, sizeof(File_Para[Area_No].Clock_Para));

        X = File_Para[Area_No].Clock_Para.Bk_X;
        Y = File_Para[Area_No].Clock_Para.Bk_Y;
        X_Len = File_Para[Area_No].Clock_Para.Bk_Width;
        Y_Len = File_Para[Area_No].Clock_Para.Bk_Height;
      }
      else if(Pub_Buf[0] EQ SHOW_TIME)//ʱ��
      {
        Len0 =  sizeof(File_Para[Area_No].Time_Para) - 2;
        mem_cpy(&File_Para[Area_No].Time_Para.Flag, Pub_Buf, Len0, &File_Para[Area_No].Time_Para, sizeof(File_Para[Area_No].Time_Para));

        X = File_Para[Area_No].Clock_Para.Bk_X;
        Y = File_Para[Area_No].Clock_Para.Bk_Y;
        X_Len = File_Para[Area_No].Clock_Para.Bk_Width;
        Y_Len = File_Para[Area_No].Clock_Para.Bk_Height;
      }
      else if(Pub_Buf[0] EQ SHOW_TIMER)//��ʱ��
      {
        Len0 =  sizeof(File_Para[Area_No].Timer_Para) - 2;
        mem_cpy(&File_Para[Area_No].Timer_Para.Flag, Pub_Buf, Len0, &File_Para[Area_No].Timer_Para, sizeof(File_Para[Area_No].Timer_Para));

        X = File_Para[Area_No].Clock_Para.Bk_X;
        Y = File_Para[Area_No].Clock_Para.Bk_Y;
        X_Len = File_Para[Area_No].Clock_Para.Bk_Width;
        Y_Len = File_Para[Area_No].Clock_Para.Bk_Height;
      }
      else if(Pub_Buf[0] EQ SHOW_TEMP)//�¶�
      {
        Len0 =  sizeof(File_Para[Area_No].Temp_Para) - 2;
        mem_cpy(&File_Para[Area_No].Temp_Para.Flag, Pub_Buf, Len0, &File_Para[Area_No].Temp_Para, sizeof(File_Para[Area_No].Temp_Para));

        X = File_Para[Area_No].Clock_Para.Bk_X;
        Y = File_Para[Area_No].Clock_Para.Bk_Y;
        X_Len = File_Para[Area_No].Clock_Para.Bk_Width;
        Y_Len = File_Para[Area_No].Clock_Para.Bk_Height;
      }

      //Bits_Copy(Pub_Buf, sizeof(Pub_Buf), 0, (Len - Len0)* 8, Show_Data.Color_Data + Dst_Index, sizeof(Show_Data.Color_Data), Dst_Index);
      Copy_Buf_2_Area_Rect_0(Pub_Buf, Len - Len0, 0, &Show_Data_Bak, Area_No, X, Y, X_Len, Y_Len);
      Dst_Index += (Len - Len0)*8;
      Size += (Len - Len0);
    }
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }

  if((Ctrl_Code & 0x10) == 0x10) //�к���֡
  {
    STOP_SHOW_TIMER_INT; //�ر���ʾ�ж�

    do
    { //��������һ֡
      Len = File_Read_One_Frame(File, Area_Status[Area_No].File_Offset, &Seq, &Ctrl_Code, Pub_Buf, Pub_Buf, sizeof(Pub_Buf)); //��ȡһ֡

      if(Len > 0) //��������һ֡
      {
        if((Size + Len) * 8 > Get_Area_Size(Area_No)) //�����˷����ķ�Χ��
        {
          ASSERT_FAILED();
          break;
        }

        //λ����
        Copy_Buf_2_Area_Rect_0(Pub_Buf, Len - Len0, Size, &Show_Data_Bak, Area_No, X, Y, X_Len, Y_Len);
        //Bits_Copy(Pub_Buf, sizeof(Pub_Buf), 0, Len * 8, Show_Data.Color_Data + Dst_Index, sizeof(Show_Data.Color_Data), Dst_Index);
        Dst_Index += Len*8;
        Size += Len;
        //�޸Ķ��ļ�ƫ��
        Area_Status[Area_No].File_Offset += Len;

        if((Ctrl_Code & 0x10) != 0x10) //û�к���֡���˳�
          break;
      }
      else //������һ��������֡�����ˣ���Ϊ�÷����������ݽ�����
      {
        Area_Status[Area_No].File_Offset = 0;
        Re = AREA_END;
        break;
      }
    }while(1); //��ͬһ������,�к���֡��ʾ---һ����������������һ֡���䣬����̫�����֡

    START_SHOW_TIMER_INT; //����ʾ�ж�
  }

  File_Close(File); //�ر�

  return 1;
}


//��������ʾ����������
INT8S Check_Update_Show_Data_Bak()
{
  INT8U i, Re;
  INT32U Area_End_Flag = 0;
  INT8U All_End_Flag = 1; //��һ������û�н���������0
  
  for(i = 0; i < Program_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {
    //Ŀǰ��ʾ�Ĳ����Ѿ���100%����Ŀǰͣ��ʱ���Ѿ��ﵽ�ļ���ͣ��ʱ�䣬����Ϊ�����Ѿ���ʾ��ϣ��л�������
    if(Get_File_Stay_Time(i) < MIN_STAY_TIME)
      Set_File_Stay_Time(i, MIN_STAY_TIME);
    
    //Step>=100��ʾ�����ƶ�������ɣ�Stay_Time>=��ʾͣ��ʱ�䵽���������Ϊ��һ������
    if(Area_Status[i].Step >= 100 && Area_Status[i].Stay_Time >= Get_File_Stay_Time(i))
    {
      Re = Update_Show_Data_Bak(Program_Para.Program_No, i);// == FILE_END)
      if(Re EQ AREA_END) //�������
      {
        SET_BIT(Area_End_Flag, i); //��i������Ŀ�������
        if(i + 1 EQ Program_Para.Main_Area_No)
          return PROG_END;
      }
      else
        All_End_Flag = 0; //��һ������û�н���������ñ�־
    }
  }
  
  if(All_End_Flag EQ 1) //���з�����������
    return PROG_END;
  else
    return PROG_OK;
}

INT8U Get_Bit(INT8U *p,INT16U X_Size,INT16U X,INT16U Y)
{
  if((*(p+(Y/8)*(X_Size)+X))&(0x01<<(Y%8)))
    return 0x01;
  else
    return 0x00;
  
}

void Show_Char(INT16U Unicode,INT8U Area_No, INT16U X,INT16U Y,INT8U Size_Flag)
{
  INT16U i,j,k;
  INT8U Bit,X_Size,Y_Size;
  //S_Point Point;
  
  for(i=0;i<sizeof(CN_ZK)/sizeof(CN_ZK[0]);i++)
  {
    if(CN_ZK[i].Unicode==Unicode)
    {     
      if(Size_Flag EQ FONT_SIZE16)
      {
        X_Size=16;
        Y_Size=16;
      }
      else if(Size_Flag EQ FONT_SIZE24)
      {
        X_Size=24;
        Y_Size=24;          
      }
      else
      {
        X_Size=48;
        Y_Size=48;
      }
      
      if(Unicode < 0xA0A0) //Ӣ�Ŀ��-1
      {
        X_Size=X_Size / 2;           
      }//
      
      for(j=0;j<X_Size;j++)
        for(k=0;k<Y_Size;k++)
        {
          if(Size_Flag EQ 0)            
            Bit=Get_Bit((INT8U *)CN_ZK[i].CN16_Dot,X_Size,j,k);
          else if(Size_Flag EQ 1)
            Bit=Get_Bit((INT8U *)CN_ZK[i].CN24_Dot,X_Size,j,k);
          else
            Bit=Get_Bit((INT8U *)CN_ZK[i].CN36_Dot,X_Size,j,k);
          
          Set_Area_Point_Data(&Show_Data_Bak, Area_No, X + j, Y +k, Bit);          
        }
    }   
  }
}

//����format��ap���������������Ϣ
void LED_Printf(INT8U Area_No, INT16U X, INT16U Y, INT8U Size_Flag, const INT8S *format, va_list ap)
{
  
  static const INT8S Chr[]="0123456789ABCDEF";
  
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
      Show_Char(Area_No, X, Y,c,Size_Flag);
    }
    
    c=*format++;
    //����ֵ���ʹ���
    switch(c)
    {
    case 'c':
      c = va_arg(ap, int);
      Show_Char(Area_No, X, Y,c,Size_Flag);
      break;
    case 's':
      pSrc= va_arg(ap,INT8S *);
      while((c = *pSrc++)!=0)
        Show_Char(Area_No, X, Y,c,Size_Flag);
      break;
    default:
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
    
    if(c EQ 'l' || c EQ 'L')//�Ƿ���һ��������?
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
    if(c EQ 'd')//�з�����
    {
      if(LintFlag)//������
        sParaValue=va_arg(ap,long int);
      else
        sParaValue=va_arg(ap,int);
      
      if(sParaValue<0)
      {
        Show_Char(Area_No, X, Y, '-',Size_Flag);
        sParaValue=0-sParaValue;
      }
      uParaValue=(unsigned long int)sParaValue;//��ֵ��uParaValue,ͳһ����
    }
    else//�޷�����
    {
      if(LintFlag)//������
        uParaValue=va_arg(ap,unsigned long int);
      else
        uParaValue=va_arg(ap,INT16U);  
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
      
      if(c EQ 0 && i EQ 0 && Width>1)//��λΪ0����֮ǰ��λҲ��Ϊ0,�Ҳ������һλ(��ֵ����Ϊ0)
        c='0';//c=' ';----�޸�Ϊ��0
      else
      {
        i=1;//��ʾ�Ѿ���һ����0λ��
        c=Chr[c];
      }
      Show_Char(Area_No, X, Y,c,Size_Flag);
    }
  }
}

//ÿ��MOVE_STEP_TIMER ms ���øú�����ʵ���ƶ�Ч��
void Show_Timer_Proc()
{
  Update_Show_Data(); //������ʾ����
  
}

//��ʾ��ش���
void Show_Main_Proc()
{
  //Check_Update_Program_Para(); //����Ƿ���Ҫ���½�Ŀ
  Check_Update_Show_Data_Bak(); //����Ƿ���Ҫ������ʾ����������
  //Check_Update_Show_Data(); //����Ƿ������ʾ������
  
}

