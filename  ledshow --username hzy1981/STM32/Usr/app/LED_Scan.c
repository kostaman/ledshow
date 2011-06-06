#define LED_SCAN_C
#include "Includes.h"

//��ȡ��Rows�е�Index���ֽڵ��ƶ����ݶ�Ӧ������Ļ�����е�����
//Rows��ʾ�кţ����кŶ�Ӧ�ӿ��е�ABCD���к�
//Cols��ʾ��ȣ�595����
//Index��ʾ��ɨ�����еĵ�Index���ֽ�
//*pX��*pY��������
//Direct��ʾ���ݽ��뷽��,Rows_Fold��ʾ���۵�����Cols_Fold��ʾ������
void Get_Shift_Data(INT16U Block, INT16U Rows, INT16U BRow, INT16U Cols, INT16U Index,\
                          INT8U Direct, INT8U Rows_Fold, INT8U Cols_Fold, INT8U *pDst)
{
  INT16U Fold_Size,X,Y;
  INT8U Screen_Color_Num, *p;
  INT8U Off;

  X = Y = 0;  
  if(Direct EQ 0x01 || Direct EQ 0x03)
    Index = Cols * Rows_Fold - Index;
  
  Fold_Size = Rows_Fold*Cols_Fold;  
  if(Direct EQ 0x00 || Direct EQ 0x03)//���Ͻ��롢���½���
  {
    X = Index / Rows_Fold  + (Index % Fold_Size) % Cols_Fold;
    Y = Block * Rows* Rows_Fold + BRow * Rows_Fold + (Index % Fold_Size) / Cols_Fold;
  }
  else if(Direct EQ 0x01 || Direct EQ 0x02) //���½��롢���Ͻ���
  {
    X = Index / Rows_Fold + (Index % Fold_Size) % Cols_Fold;
    Y = (Block  + 1)*  Rows * Rows_Fold - BRow * Rows_Fold - (Index % Fold_Size) / Cols_Fold;    
  }
  else
    ASSERT_FAILED();
 
  Screen_Color_Num = Get_Screen_Color_Num();  

  p = Show_Data.Color_Data + (Y*Cols + X)*Screen_Color_Num;
  
  Off = 0;
  
  //��ȡ��ɫ����
  //��
  if(GET_BIT(Screen_Para.Base_Para.Color, 0))
    *pDst = *(p + Off++);//Show_Data.Color_Data[Data_Index];
  else 
    *pDst = 0;
  
  //��
  if(GET_BIT(Screen_Para.Base_Para.Color, 1))
    *(pDst + 1) = *(p + Off ++);//Show_Data.Color_Data[Data_Index];
  else 
    *(pDst + 1) = 0;
  
  //��
  if(GET_BIT(Screen_Para.Base_Para.Color, 2))
    *(pDst + 2) = *(p + Off ++);//Show_Data.Color_Data[Data_Index];
  else 
    *(pDst + 2) = 0;  
  //memcpy(pDst, Show_Data.Color_Data + Data_Index*Screen_Color_Num, Screen_Color_Num);
  return ;//ReIndex;
}


INT8U Get_Next_Byte_Posi(INT16U X, INT16U Y, INT16U *pX, INT16U *pY,\
                         INT8U Direct, INT8U Rows_Fold, INT8U Cols_Fold)
{
  if(Direct EQ 0x00)//���Ͻ���
  {
    if(X % Cols_Fold EQ 0 && Y % Rows_Fold EQ 0)
    {
      *pX = X - 1;
      *pY = Y + Rows_Fold - 1;
    }
    else if(X % Cols_Fold EQ 0)
    {
      *pX = X + Cols_Fold - 1;
      *pY = Y - 1;
    }
    else
    {
       *pX = X - 1; 
       *pY = Y;
    }
  }
  else if(Direct EQ 0x01) //���Ͻ���
  {
    if(X % Cols_Fold EQ (Cols_Fold - 1) && Y % Rows_Fold EQ 0)
    {
      *pX = X + 1;
      *pY = Y + Rows_Fold - 1;
    }
    else if(X % Cols_Fold EQ (Cols_Fold - 1))
    {
      *pX = X - (Cols_Fold - 1);
      *pY = Y - 1;
    }
    else
    {
       *pX = X + 1; 
       *pY = Y;
    }    
  }
  else if(Direct EQ 0x02) //���½���
  {
    if(X % Cols_Fold EQ 0 && Y % Rows_Fold EQ (Rows_Fold - 1))
    {
      *pX = X - 1;
      *pY = Y - (Rows_Fold - 1);
    }
    else if(X % Cols_Fold EQ 0)
    {
      *pX = X + (Cols_Fold - 1);
      *pY = Y + 1;
    }
    else
    {
       *pX = X - 1; 
       *pY = Y;
    }     
  }
  else if(Direct EQ 0x03) //���½���
  {
    if(X % Cols_Fold EQ (Cols_Fold - 1) && Y % Rows_Fold EQ (Rows_Fold - 1))
    {
      *pX = X + 1;
      *pY = Y - (Rows_Fold - 1);
    }
    else if(X % Cols_Fold EQ (Cols_Fold - 1))
    {
      *pX = X - (Cols_Fold - 1);
      *pY = Y + 1;
    }
    else
    {
       *pX = X + 1; 
       *pY = Y;
    }     
  }
  else
  {
    ASSERT_FAILED();
    *pX = 0;
    *pY = 0;
  }
  
  return 1;
}
                         
//���øú���ÿ��ɨ��һ��
//ÿ�ж�һ�ε���һ�θú���
void LED_Scan_One_Row(void)
{
  INT16U i,j,k,m;
  INT16U Blocks;
  INT32U Row_Freq;
  
  if(Screen_Status.Open_Flag EQ 0) //�ػ�״̬������ʾ
    return;

  if(Screen_Para.Scan_Para.Rows EQ 0)
  {
	Screen_Para.Scan_Para.Rows = 1;
	SET_SUM(Screen_Para);
  }

  if(Screen_Para.Scan_Para.Rows_Fold EQ 0)
  {
	Screen_Para.Scan_Para.Rows_Fold = 1;
	SET_SUM(Screen_Para);
  }

  //Block���������Ϊ��Ԫ������ĸ���
  Blocks = Screen_Para.Base_Para.Height / (Screen_Para.Scan_Para.Rows * Screen_Para.Scan_Para.Rows_Fold); //1.2.4.8.16ɨ��
 
  if(Blocks > MAX_SCAN_BLOCK_NUM)
	 Blocks = MAX_SCAN_BLOCK_NUM;

  //��ÿ��Blocks����ɨ��
  //ÿһ��ɨ������ҪScreen_Para.Base_Para.Width / 8 * Screen_Para.Scan_Para.Rows_Fold���ֽ�
  for(i = 0; i < Screen_Para.Base_Para.Width / 8 * Screen_Para.Scan_Para.Rows_Fold; i ++)
  {
    //��ÿ��Block��ÿ��ɨ����ͬʱ���һ���ֽ�
    for(j = 0; j < Blocks; j++)
    {
    //��ȡ��ɨ�����ϵ������ֽڲ����
      Get_Shift_Data(j, \
              Screen_Para.Scan_Para.Rows, \
              Screen_Status.Scan_Row,\
              Screen_Para.Base_Para.Width, \
              i, \
              Screen_Para.Scan_Para.Direct, \
              Screen_Para.Scan_Para.Rows_Fold, \
              Screen_Para.Scan_Para.Cols_Fold,\
              Screen_Status.Scan_Data[j]);
    }
    
    //�����е�block���һ���ֽ�
    //����Ǵ������ң�Ӧ���������λ�������λ
    if(Screen_Para.Scan_Para.Direct EQ 0x00 || Screen_Para.Scan_Para.Direct EQ 0x01)
    {
      for(j = 0; j < 8 ; j++)
      {
	    m = 7 - j;
        //Set_Shift_Bit_Clk(0); //��λ����ʱ��Ϊ0
        SET_CLK(0);

        for(k = 0; k < Blocks; k++)
        {/*
          Set_Shift_Bit(k, 0, GET_BIT(Screen_Status.Scan_Data[k][0], 7-j));//��ɫ Rk
          Set_Shift_Bit(k, 1, GET_BIT(Screen_Status.Scan_Data[k][1], 7-j));//��ɫ Gk
          Set_Shift_Bit(k, 2, GET_BIT(Screen_Status.Scan_Data[k][2], 7-j));//��ɫ Bk
		*/
		 SET_SHIFT_BIT(k, Screen_Status.Scan_Data[k], m); 
		}
        
        //Set_Shift_Bit_Clk(1); //��λʱ����1
		SET_CLK(1);
      } 
    }
    else //��������������Ӧ���������λ
    {
      for(j = 0; j < 8 ; j++)
      {
        //Set_Shift_Bit_Clk(0); //��λ����ʱ��Ϊ0
		SET_CLK(0);
        
        for(k = 0; k < Blocks; k++)
        {/*
          Set_Shift_Bit(k, 0, GET_BIT(Screen_Status.Scan_Data[k][0], j));//��ɫ
          Set_Shift_Bit(k, 1, GET_BIT(Screen_Status.Scan_Data[k][1], j));//��ɫ
          Set_Shift_Bit(k, 2, GET_BIT(Screen_Status.Scan_Data[k][2], j));//��ɫ
          */
		  SET_SHIFT_BIT(k, Screen_Status.Scan_Data[k], j);
		}
        
        //Set_Shift_Bit_Clk(1); //��λʱ����1
		SET_CLK(1);
      }      
    }
    
    //������ʱ��
    Set_Block_OE_En(0); //�ر�ʹ��
    Delay_us(Screen_Para.Scan_Para.Line_Hide); //������ʱ��
    
    SET_LAT(0); //�����ź����
    SET_LAT(1); //�����ź����
    
    Set_Block_Row(Screen_Status.Scan_Row);
    Screen_Status.Scan_Row++;
    if(Screen_Status.Scan_Row >= Screen_Para.Scan_Para.Rows)
      Screen_Status.Scan_Row = 0;
  
    Set_Block_OE_En(1); //���´�ʹ��
    
    //��ɨ���Ƶ�ʵ�����ɨ��Ƶ��*ɨ������
    //Row_Freq = (INT32U)Screen_Para.Scan_Para.Screen_Freq*Screen_Para.Scan_Para.Rows; //��ɨ���Ƶ��
    //Reset_Scan_Timer(Row_Freq);
  }
  

/*  
  Shift_Bytes = (INT16U)Screen_Para.Scan_Para.Rows_Fold*Screen_Para.Base_Para.Width/8;
  Block_Num = (INT16U)Scan_Para.Base_Para.Height/Screen_Para.Scan_Para.Rows_Fold;
  
  for(i = 0; i < Shift_Bytes; i ++)
  {
   SHIFT_CLK_0;
   
   SHIFT_CLK_1;
  }
  
*/  
  
  
  
}
