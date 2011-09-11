#define LED_SCAN_C
#include "Includes.h"

volatile INT32U test_temp = 0, test_x=0, test_y=0;
//���㷨�൱ţ�ƣ���i�����е�8��
void transpose8(unsigned char i[8], unsigned char o[8]) { 
        unsigned long x, y, t; 

        //x = (i[0] << 24) | (i[1] << 16) | (i[2] << 8) | i[3]; 
        //y = (i[4] << 24) | (i[5] << 16) | (i[6] << 8) | i[7]; 
        x = (i[7] << 24) | (i[6] << 16) | (i[5] << 8) | i[4]; 
        y = (i[3] << 24) | (i[2] << 16) | (i[1] << 8) | i[0];

        t = (x & 0xf0f0f0f0) | ((y >> 4) & 0x0f0f0f0f); 
        y = ((x << 4) & 0xf0f0f0f0) | (y & 0x0f0f0f0f); 
        x = t; 

        t = (x ^ (x >> 14)) & 0x0000cccc; 
        x = x ^ t ^ (t << 14); 
        t = (y ^ (y >> 14)) & 0x0000cccc; 
        y = y ^ t ^ (t << 14); 

        t = (x ^ (x >> 7)) & 0x00aa00aa; 
        x = x ^ t ^ (t << 7); 
        t = (y ^ (y >> 7)) & 0x00aa00aa; 
        y = y ^ t ^ (t << 7); 

        o[7] = x >> 24; o[6] = x >> 16; o[5] = x >> 8; o[4] = x; 
        o[3] = y >> 24; o[2] = y >> 16; o[1] = y >> 8; o[0] = y; 
}

/*
//��λ������
#include  "intrinsics.h" 
unsigned int __rbit(unsigned int val) 
*/
//-------------------------
/*
void Set_Clock_Hight_Speed(void)
{
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE); //�����ⲿʱ��ΪHSE
	//_RCC_HCLKConfig(RCC_SYSCLK_Div1);   //����AHBʱ��=AHB_FREQ MHz
	RCC_PCLK1Config(H_PCLK1_DIV);   //����APB1ʱ��=36 MHz(APB1ʱ�����ֵ)
	RCC_PCLK2Config(H_PCLK2_DIV);   //����APB2ʱ��=72 MHz
	RCC_PLLCmd(DISABLE); //�ر�PLL
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, H_HCLK_MUL); //PLL�������伤��ǰ������ã�����PLLʱ��Դ����Ƶϵ����
	RCC_PLLCmd(ENABLE);
	// Wait till PLL is ready 
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	{
	}
	// Select PLL as system clock source 
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	// Wait till PLL is used as system clock source 
	while(RCC_GetSYSCLKSource() != 0x08)
	{
	}
}
 */
void Set_Clock_Normal_Speed(void)
{
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE); //�����ⲿʱ��ΪHSE
	//_RCC_HCLKConfig(RCC_SYSCLK_Div1);   //����AHBʱ��=AHB_FREQ MHz
	RCC_PCLK1Config(PCLK1_DIV);   //����APB1ʱ��=36 MHz(APB1ʱ�����ֵ)
	RCC_PCLK2Config(PCLK2_DIV);   //����APB2ʱ��=72 MHz
	RCC_PLLCmd(DISABLE); //�ر�PLL
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, HCLK_MUL); //PLL�������伤��ǰ������ã�����PLLʱ��Դ����Ƶϵ����
	RCC_PLLCmd(ENABLE);
	// Wait till PLL is ready 
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	{
	}
	// Select PLL as system clock source 
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	// Wait till PLL is used as system clock source 
	while(RCC_GetSYSCLKSource() != 0x08)
	{
	}

}

#if BUILD_SCAN_DATA_INDEX_EN
typedef struct
{
  INT8U Head;
  INT16U Index[MAX_POINTS*2/(8*16)]; //��¼��0ɨ�赥Ԫ�ڵ�һ��ɨ���ߵ���������ƫ��

  INT16U Block_Off[MAX_SCAN_BLOCK_NUM][16];
  INT8U Block_Num;
  INT8U Tail;
}S_Scan_Data_Index;

S_Scan_Data_Index Scan_Data_Index;
#endif

 //����ɨ�赥Ԫ0������ɨ�����ݵ����������ֽ�Ϊ��λ
void Build_Scan_Data_Index(void)
{
#if BUILD_SCAN_DATA_INDEX_EN
  INT16U Cols, i,j,Index;
  INT8U Color_Num;

  if(Screen_Para.Scan_Para.Rows EQ 0)
  {
	Screen_Para.Scan_Para.Rows = 16;
	SET_SUM(Screen_Para);
  }

  Color_Num = Get_Screen_Color_Num();
  //Block����������Ϊ��Ԫ������ĸ���
  Scan_Data_Index.Block_Num = Screen_Para.Base_Para.Height / (Screen_Para.Scan_Para.Rows * (Screen_Para.Scan_Para.Rows_Fold + 1)); //1.2.4.8.16ɨ��
 
  if(Scan_Data_Index.Block_Num > MAX_SCAN_BLOCK_NUM)
	 Scan_Data_Index.Block_Num = MAX_SCAN_BLOCK_NUM;

  Cols = Screen_Para.Base_Para.Width / 8;
  //��ÿ��Blocks����ɨ��
  //ÿһ��ɨ������ҪScreen_Para.Base_Para.Width / 8 * Screen_Para.Scan_Para.Rows_Fold���ֽ�
  for(i = 0; i < Cols * (Screen_Para.Scan_Para.Rows_Fold + 1); i ++)
  {
      Index = Get_Scan_Data_Index(0, i);

	   if(Index < sizeof(Scan_Data_Index.Index))
		  Scan_Data_Index.Index[i] = Index;
	   else
		  ASSERT_FAILED();

   }

   for(i = 0; i < MAX_SCAN_BLOCK_NUM; i ++)
   {
      for(j = 0; j < Screen_Para.Scan_Para.Rows && j < S_NUM(Scan_Data_Index.Block_Off[0]); j ++)
	  {
	      Index = Get_Scan_Data_Index(i, \
		              Screen_Para.Scan_Para.Rows, \
		              j,\
		              Cols, \
		              0, \
		              Screen_Para.Scan_Para.Direct, \
		              Screen_Para.Scan_Para.Rows_Fold, \
		              Screen_Para.Scan_Para.Cols_Fold);
	
		   //if(Index < sizeof(Scan_Data_Index.Index))
			  Scan_Data_Index.Block_Off[i][j] = Index - Scan_Data_Index.Index[0];
     }
   }
 #endif
}

void Set_OE_Duty_Polarity(INT8U Duty, INT8U Polarity)
{
  if(Duty > 100)
  {
    Duty = 100;
    ASSERT_FAILED();
  }

  if(Polarity EQ 0)
    TIM4->CCR3 = TIM4->ARR * Duty / 100;
  else
    TIM4->CCR3 = TIM4->ARR * (100 - Duty) / 100;
}
//��ȡ��Rows�е�Index���ֽڵ��ƶ����ݶ�Ӧ������Ļ�����е�����
//Block��ʾɨ���Ŀ��
//Rows��ʾ�кţ����кŶ�Ӧ�ӿ��е�ABCD���к�,����֮��ɨ?
//BRow��ʾ�ÿ���ڵĵڼ���ɨ����
//Cols��ʾ���ȣ�595����,ʵ��Ϊ��Ļ����/8
//Index��ʾ��ɨ�����еĵ�Index���ֽ�
//*pX��*pY��������
//Direct��ʾ���ݽ��뷽��,Rows_Fold��ʾ���۵�����Cols_Fold��ʾ������
INT16U Get_Scan_Data_Index(INT16U Block, INT16U Index)
{
  INT32U Fold_Size,X,Y;
  //INT8U  *p;
  INT32U Temp;
  INT8U Rows_Fold, Cols_Fold,Rows;
  INT16U Cols;
  INT8U Direct;

  //X = Y = 0; 
  if(Screen_Para.Scan_Para.Direct < 2) //����߽��룬������Ӧ��ת��
    Index = Screen_Status.Block_Cols - 1 - Index; //Index��0��ʼ����
		  
  if(Screen_Para.Scan_Para.Rows_Fold EQ 0 ||\
     Screen_Para.Scan_Para.Cols_Fold EQ 0) //û�д��۵�����
  {
      //return ((Block * Screen_Status.Block_Cols + Screen_Status.Scan_Row) * Screen_Status.Block_Cols + Index)*Screen_Status.Color_Num;
      X = Index;
	   //ÿ��Block��Ӧ����Ļ�ϵ������� Rows*Rows_Fold
	   //BRow��ʾ�ڼ���ɨ����,ÿ��ɨ���߶�Ӧ����Ļ�ϵ���Rows_Fold��
	  Y = Block*Screen_Status.Rows_X_RowsFold + Screen_Status.BRow_X_RowsFold;//(Block * Rows + BRow) * Rows_Fold;//Block * Rows* Rows_Fold + BRow * Rows_Fold;//
      return (Y*Screen_Status.Block_Cols + X)*Screen_Status.Color_Num;//ReIndex;
  }
  else
  {
	  Cols = Screen_Status.Block_Cols;
	
	  Rows = Screen_Para.Scan_Para.Rows;
	  Rows_Fold = Screen_Para.Scan_Para.Rows_Fold + 1;
	  Cols_Fold = Screen_Para.Scan_Para.Cols_Fold;
	  Direct = Screen_Para.Scan_Para.Direct;
     
	  Fold_Size = Screen_Status.Fold_Size;//Rows_Fold*Cols_Fold;  
	  if(Direct EQ 0x00 || Direct EQ 0x02)//���Ͻ��롢���Ͻ���
	  {

	    Temp = Index % Fold_Size; 
	    X = Index / Fold_Size * Cols_Fold + Temp % Cols_Fold;
	    //ÿ��Block��Ӧ����Ļ�ϵ������� Rows*Rows_Fold
	    //BRow��ʾ�ڼ���ɨ����,ÿ��ɨ���߶�Ӧ����Ļ�ϵ���Rows_Fold��
	    Y = Block*Screen_Status.Rows_X_RowsFold + Screen_Status.BRow_X_RowsFold + Temp / Cols_Fold; //(Block * Rows + BRow) * Rows_Fold + Temp / Cols_Fold;//Block * Rows* Rows_Fold + BRow * Rows_Fold + (Index % Fold_Size) / Cols_Fold;
/*	  
		if(Screen_Para.Scan_Para.Direct EQ 0 && Screen_Para.Scan_Para.Rows_Fold EQ 0x01 && Screen_Para.Scan_Para.Cols_Fold EQ 0x01)
		{
		   test_x = X;
		   test_y = Y;

		   test_x = Index;
		   test_y = Fold_Size;

		   test_temp = Index;// = test_temp;
		}	*/  
	  }
	  else if(Direct EQ 0x01 || Direct EQ 0x03) //���½��롢���½���
	  {
	    Temp = Index % Fold_Size; 
	    X = Index / Fold_Size * Cols_Fold + Temp % Cols_Fold;
	    //ÿ��Block��Ӧ����Ļ�ϵ������� Rows*Rows_Fold
	    //BRow��ʾ�ڼ���ɨ����,ÿ��ɨ���߶�Ӧ����Ļ�ϵ���Rows_Fold��
	    Y = Block*Screen_Status.Rows_X_RowsFold + Screen_Status.BRow_X_RowsFold + Temp / Cols_Fold + Rows_Fold - Temp / Cols_Fold - 1; 
	  }
	  else
	  {
	    ASSERT_FAILED();
        return 0;
	  }

	  //Screen_Color_Num = Screen_Status.Color_Num;//Get_Screen_Color_Num();  
	
	  return (Y*Cols + X)*Screen_Status.Color_Num;//ReIndex;
   }

}

#if BUILD_SCAN_DATA_INDEX_EN
 //��ȡɨ������
void Get_Scan_Data(INT16U Blocks, INT8U Row, INT16U Col)
{

  INT16U i;
  INT8U *p;
  INT32U Temp;

  p = (INT8U *)Show_Data.Color_Data;
  for(i = 0; i < Scan_Data_Index.Block_Num && i < MAX_SCAN_BLOCK_NUM; i ++)
  {
    if(GET_BIT(Screen_Para.Base_Para.Color, 0))
      Scan_Data[0][i] = 0xFF - *(p + Scan_Data_Index.Index[Col] +  Scan_Data_Index.Block_Off[i][Row]);
	else
	  Scan_Data[0][i] = 0xFF;
   
    if(GET_BIT(Screen_Para.Base_Para.Color, 1))
	  Scan_Data[1][i] = 0xFF - *(p + Scan_Data_Index.Index[Col] +  Scan_Data_Index.Block_Off[i][Row] + 1);
	else
	  Scan_Data[1][i] = 0xFF;
    
	if(GET_BIT(Screen_Para.Base_Para.Color, 2))
	  Scan_Data[2][i] = 0xFF - *(p + Scan_Data_Index.Index[Col] +  Scan_Data_Index.Block_Off[i][Row] + 2);
    else
	  Scan_Data[2][i] = 0xFF;

	if(Screen_Para.Scan_Para.Direct EQ 0x00 || Screen_Para.Scan_Para.Direct EQ 0x01)//��߽���λ��Ӧ�÷�
	{
		Temp = __RBIT(Scan_Data[0][i]);
		Scan_Data[0][i] = *((INT8U *)&Temp + 3);
		Temp = __RBIT(Scan_Data[1][i]);
		Scan_Data[1][i] = *((INT8U *)&Temp + 3);
		Temp = __RBIT(Scan_Data[2][i]);
		Scan_Data[2][i] = *((INT8U *)&Temp + 3);
	}
  }	

}
#else
void Get_Scan_Data(INT16U Blocks, INT16U Col)
{
    INT16U Index,Off,i;
	INT32U Temp;
	INT16U Cols;
	INT8U *p;
	
    //Cols = Screen_Para.Base_Para.Width / 8;
    for(i = 0; i < Blocks && i < MAX_SCAN_BLOCK_NUM; i ++)
    {
        //��ȡ��ɨ�����ϵ������ֽڲ����
        Index = Get_Scan_Data_Index(i, Col);

	   //test_temp = Index;
	    p = Show_Data.Color_Data + Index;
	  
		Off = 0;
		//��ȡ��ɫ����
		//��
		if(GET_BIT(Screen_Para.Base_Para.Color, 0))
		  Scan_Data[0][i] = 0xFF - *(p + Off++);//Show_Data.Color_Data[Data_Index];
		else 
		  Scan_Data[0][i] = 0xFF;
		
		//��
		if(GET_BIT(Screen_Para.Base_Para.Color, 1))
		  Scan_Data[1][i] = 0xFF - *(p + Off ++);//Show_Data.Color_Data[Data_Index];
		else 
		  Scan_Data[1][i] = 0xFF;
/*		
		//��
		if(GET_BIT(Screen_Para.Base_Para.Color, 2))
		  Scan_Data[2][i] = 0xFF - *(p + Off ++);//Show_Data.Color_Data[Data_Index];
		else 
		  Scan_Data[2][i] = 0xFF; 
*/		
		
		if(Screen_Para.Scan_Para.Direct < 0x02)// EQ 0x00 || Screen_Para.Scan_Para.Direct EQ 0x01)//��߽���λ��Ӧ�÷�
		{
			Temp = __RBIT(Scan_Data[0][i]);
			Scan_Data[0][i] = *((INT8U *)&Temp + 3);
			Temp = __RBIT(Scan_Data[1][i]);
			Scan_Data[1][i] = *((INT8U *)&Temp + 3);
			//Temp = __RBIT(Scan_Data[2][i]);
			//Scan_Data[2][i] = *((INT8U *)&Temp + 3);
		}
    }

}
#endif
  
 //���ÿ��к�
void Set_Block_Row(INT8U Row)
{
  //Row = Screen_Status.Scan_Row;
  if(Screen_Para.Scan_Para.Rows EQ 0)
  {
    Screen_Para.Scan_Para.Rows = 16;
	SET_SUM(Screen_Para);
  }

  Row = (INT8U)(((INT8S)Screen_Status.Scan_Row + Screen_Para.Scan_Para.Line_Order) % Screen_Para.Scan_Para.Rows);
    
  SET_A((Row & 0x01));
  SET_B(((Row & 0x02) >> 1));
  SET_C(((Row & 0x04) >> 2));
  SET_D(((Row & 0x08) >> 3));
}

                       
//���øú���ÿ��ɨ��һ��
//ÿ�ж�һ�ε���һ�θú���
void LED_Scan_One_Row(void)
{
  INT16U i,j,Cols;
  INT16U Blocks;
  INT16U Temp;
//  INT8U Color_Num;
  
  //Delay_us(500);
  //return;

  if(Screen_Status.Time_OC_Flag EQ CLOSE_FLAG ||\
     Screen_Status.Manual_OC_Flag EQ CLOSE_FLAG ||\
	 Screen_Status.Com_Time > 0 ||\
	 Chk_UDisk_Processing()) //�ػ�״̬������ʾ,��ǰ��ͨ��״̬Ҳ����ʾ
    return;
 

  Prog_Status.Play_Status.Effect_Counts++;
  if(Prog_Status.Play_Status.Effect_Counts >= Prog_Status.Play_Status.Max_Effect_Counts)
  {
    //Prog_Status.Play_Status.Effect_Counts = 0;
	Prog_Status.Play_Status.Effect_Flag = 1;
  }
  //Set_Clock_Hight_Speed(); //����Ϊ��������ģʽ
  if(Screen_Para.Scan_Para.Rows EQ 0)
  {
	Screen_Para.Scan_Para.Rows = 16;
	SET_SUM(Screen_Para);
  }

  Screen_Status.Color_Num = Get_Screen_Color_Num();
  Screen_Status.Block_Cols = (Screen_Para.Base_Para.Width / 8)* (Screen_Para.Scan_Para.Rows_Fold + 1);//Screen_Para.Base_Para.Width / 8;	//һ��ɨ���ߵĳ��ȣ��˴����޸�
  Screen_Status.Fold_Size = Screen_Para.Scan_Para.Cols_Fold * (Screen_Para.Scan_Para.Rows_Fold + 1);
  Screen_Status.BRow_X_RowsFold = Screen_Status.Scan_Row * (Screen_Para.Scan_Para.Rows_Fold + 1);
  Screen_Status.Rows_X_RowsFold = Screen_Para.Scan_Para.Rows * (Screen_Para.Scan_Para.Rows_Fold + 1); 
  //Block����������Ϊ��Ԫ������ĸ���

  Blocks = Screen_Para.Base_Para.Height / (Screen_Para.Scan_Para.Rows * (Screen_Para.Scan_Para.Rows_Fold + 1)); //1.2.4.8.16ɨ��
	
  if(Blocks > MAX_SCAN_BLOCK_NUM)
	Blocks = MAX_SCAN_BLOCK_NUM;

  Cols = Screen_Status.Block_Cols;
  //��ÿ��Blocks����ɨ��
  //ÿһ��ɨ������ҪScreen_Para.Base_Para.Width / 8 * Screen_Para.Scan_Para.Rows_Fold���ֽ�
  for(i = 0; i < Cols ; i ++)
  {
      Get_Scan_Data(Blocks, i);


#if SCAN_DATA_MODE EQ 0

#if MAX_SCAN_BLOCK_NUM EQ 4
      transpose8(Scan_Data[0], Scan_Data0[0]);
	  for(j = 0; j < 8; j ++)
	  {
	    nop();
	    nop();
	    SET_CLK_LOW();
        GPIOB->ODR = (GPIOB->ODR & 0xFF00) | Scan_Data0[0][j]; //���R1
		nop();
		SET_CLK_HIGH();
	   }
#elif MAX_SCAN_BLOCK_NUM EQ 8
;
#elif MAX_SCAN_BLOCK_NUM EQ 16
;
#elif MAX_SCAN_BLOCK_NUM EQ 32
;
#else
#error "MAX_SCAN_BLOCK_NUM error"
#endif

#endif

   }
	 //�˴���Ӳ��ɨ�跽ʽ����

  //return;	 
	//�ر�OEʹ��
	Set_OE_Duty_Polarity(0, Screen_Para.Scan_Para.OE_Polarity);

	if(Screen_Para.Scan_Para.Line_Hide > 0)
	  Delay_us(Screen_Para.Scan_Para.Line_Hide*10); //������ʱ��
    Delay_us(20);

    SET_LAT(0); //�����ź����
	nop();
	nop();
    SET_LAT(1); //�����ź����
    
    Set_Block_Row(Screen_Status.Scan_Row);
    Screen_Status.Scan_Row++;
    if(Screen_Status.Scan_Row >= Screen_Para.Scan_Para.Rows)
      Screen_Status.Scan_Row = 0;
	
	//���´�OE
	Set_OE_Duty_Polarity(50, Screen_Para.Scan_Para.OE_Polarity);
	//_USART_Cmd(USART1, DISABLE);
    //Set_Clock_Normal_Speed();
	//_USART_Cmd(USART1, ENABLE); 
	//USART_Clar
   
}