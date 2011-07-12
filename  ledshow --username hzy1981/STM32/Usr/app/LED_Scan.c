#define LED_SCAN_C
#include "Includes.h"

//���㷨�൱ţ�ƣ���i�����е�8��
void transpose8(unsigned char i[8], unsigned char o[8]) { 
        unsigned long x, y, t; 

        x = (i[0] << 24) | (i[1] << 16) | (i[2] << 8) | i[3]; 
        y = (i[4] << 24) | (i[5] << 16) | (i[6] << 8) | i[7]; 

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

#pragma pack(1)
INT8U Scan_Data[MAX_SCAN_BLOCK_NUM][3] __attribute__((at(SCAN_DATA_ADDR)));
#pragma pack()

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
  //Block���������Ϊ��Ԫ������ĸ���
  Scan_Data_Index.Block_Num = Screen_Para.Base_Para.Height / (Screen_Para.Scan_Para.Rows * (Screen_Para.Scan_Para.Rows_Fold + 1)); //1.2.4.8.16ɨ��
 
  if(Scan_Data_Index.Block_Num > MAX_SCAN_BLOCK_NUM)
	 Scan_Data_Index.Block_Num = MAX_SCAN_BLOCK_NUM;

  Cols = Screen_Para.Base_Para.Width / 8;
  //��ÿ��Blocks����ɨ��
  //ÿһ��ɨ������ҪScreen_Para.Base_Para.Width / 8 * Screen_Para.Scan_Para.Rows_Fold���ֽ�
  for(i = 0; i < Cols * (Screen_Para.Scan_Para.Rows_Fold + 1); i ++)
  {
      Index = Get_Scan_Data(0, \
	              Screen_Para.Scan_Para.Rows, \
	              0,\
	              Cols, \
	              i, \
	              Screen_Para.Scan_Para.Direct, \
	              Screen_Para.Scan_Para.Rows_Fold, \
	              Screen_Para.Scan_Para.Cols_Fold,\
	              Scan_Data[0]);

	   if(Index < sizeof(Scan_Data_Index.Index))
		  Scan_Data_Index.Index[i] = Index;
	   else
		  ASSERT_FAILED();

   }

   for(i = 0; i < MAX_SCAN_BLOCK_NUM; i ++)
   {
      for(j = 0; j < Screen_Para.Scan_Para.Rows && j < S_NUM(Scan_Data_Index.Block_Off[0]); j ++)
	  {
	      Index = Get_Scan_Data(i, \
		              Screen_Para.Scan_Para.Rows, \
		              j,\
		              Cols, \
		              0, \
		              Screen_Para.Scan_Para.Direct, \
		              Screen_Para.Scan_Para.Rows_Fold, \
		              Screen_Para.Scan_Para.Cols_Fold,\
		              Scan_Data[0]);
	
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
    TIM3->CCR3 = TIM3->ARR * Duty / 100;
  else
    TIM3->CCR3 = TIM3->ARR * (100 - Duty) / 100;
}
//��ȡ��Rows�е�Index���ֽڵ��ƶ����ݶ�Ӧ������Ļ�����е�����
//Block��ʾɨ���Ŀ��
//Rows��ʾ�кţ����кŶ�Ӧ�ӿ��е�ABCD���к�,����֮��ɨ?
//BRow��ʾ�ÿ���ڵĵڼ���ɨ����
//Cols��ʾ��ȣ�595����,ʵ��Ϊ��Ļ���/8
//Index��ʾ��ɨ�����еĵ�Index���ֽ�
//*pX��*pY��������
//Direct��ʾ���ݽ��뷽��,Rows_Fold��ʾ���۵�����Cols_Fold��ʾ������
INT16U Get_Scan_Data(INT16U Block, INT16U Rows, INT16U BRow, INT16U Cols, INT16U Index,\
                          INT8U Direct, INT8U Rows_Fold, INT8U Cols_Fold, INT8U *pDst)
{
  INT16U Fold_Size,X,Y;
  INT8U Screen_Color_Num, *p;
  INT8U Off;
  //INT16U Cols;
  
  X = Y = 0; 

  Rows_Fold ++;

  if(Direct EQ 0x00 || Direct EQ 0x01) //����߽��룬������Ӧ��ת��
    Index = Cols - 1 - Index; //Index��0��ʼ����
		  
  if(Rows_Fold EQ 0 || Cols_Fold EQ 0) //û�д��۵�����
  {
      X = Index;
	   //ÿ��Block��Ӧ����Ļ�ϵ������� Rows*Rows_Fold
	   //BRow��ʾ�ڼ���ɨ����,ÿ��ɨ���߶�Ӧ����Ļ�ϵ���Rows_Fold��
	  Y = Block * Rows* Rows_Fold + BRow * Rows_Fold;// + (Index % Fold_Size) / Cols_Fold;
  }
  else
  { 
	  Fold_Size = Rows_Fold*Cols_Fold;  
	  if(Direct EQ 0x00 || Direct EQ 0x02)//���Ͻ��롢���Ͻ���
	  {
	    X = Index / Fold_Size * Cols_Fold + (Index % Fold_Size) % Cols_Fold;
	    //ÿ��Block��Ӧ����Ļ�ϵ������� Rows*Rows_Fold
	    //BRow��ʾ�ڼ���ɨ����,ÿ��ɨ���߶�Ӧ����Ļ�ϵ���Rows_Fold��
	    Y = Block * Rows* Rows_Fold + BRow * Rows_Fold + (Index % Fold_Size) / Cols_Fold;
	  }
	  else if(Direct EQ 0x01 || Direct EQ 0x03) //���½��롢���½���
	  {
	    X = Index / Fold_Size * Cols_Fold + (Index % Fold_Size) % Cols_Fold;
	    //ÿ��Block��Ӧ����Ļ�ϵ������� Rows*Rows_Fold
	    //BRow��ʾ�ڼ���ɨ����,ÿ��ɨ���߶�Ӧ����Ļ�ϵ���Rows_Fold��
	    Y = Block * Rows* Rows_Fold + (BRow + 1) * Rows_Fold - (Index % Fold_Size) / Cols_Fold - 1;//Y = (Block  + 1)*  Rows * Rows_Fold - BRow * Rows_Fold - (Index % Rows_Fold);//(Index % Fold_Size) / Cols_Fold;    
	  }
	  else
	    ASSERT_FAILED();
   }
  Screen_Color_Num = Get_Screen_Color_Num();  

  p = Show_Data.Color_Data + (Y*Cols + X)*Screen_Color_Num;
  
  Off = 0;
  
  //��ȡ��ɫ����
  //��
  if(GET_BIT(Screen_Para.Base_Para.Color, 0))
    *pDst = 0xFF - *(p + Off++);//Show_Data.Color_Data[Data_Index];
  else 
    *pDst = 0xFF;
  
  //��
  if(GET_BIT(Screen_Para.Base_Para.Color, 1))
    *(pDst + 1) = 0xFF - *(p + Off ++);//Show_Data.Color_Data[Data_Index];
  else 
    *(pDst + 1) = 0xFF;
  
  //��
  if(GET_BIT(Screen_Para.Base_Para.Color, 2))
    *(pDst + 2) = 0xFF - *(p + Off ++);//Show_Data.Color_Data[Data_Index];
  else 
    *(pDst + 2) = 0xFF;  
  //memcpy(pDst, Show_Data.Color_Data + Data_Index*Screen_Color_Num, Screen_Color_Num);
  return (Y*Cols + X)*Screen_Color_Num;//ReIndex;
}
 //��ȡɨ������
void Get_Scan_Data0(INT8U Row, INT16U Col)
{
#if BUILD_SCAN_DATA_INDEX_EN
  INT16U i;
  INT8U *p;

  p = (INT8U *)Show_Data.Color_Data;
  for(i = 0; i < Scan_Data_Index.Block_Num && i < MAX_SCAN_BLOCK_NUM; i ++)
  {
    Scan_Data[i][0] = 0xFF - *(p + Scan_Data_Index.Index[Col] +  Scan_Data_Index.Block_Off[i][Row]);
	Scan_Data[i][1] = 0xFF - *(p + Scan_Data_Index.Index[Col] +  Scan_Data_Index.Block_Off[i][Row] + 1);
	Scan_Data[i][2] = 0xFF - *(p + Scan_Data_Index.Index[Col] +  Scan_Data_Index.Block_Off[i][Row] + 2);
  }
#endif
}

  
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
  INT8U Color_Num;
  
  if(Screen_Status.Time_OC_Flag EQ CLOSE_FLAG ||\
     Screen_Status.Manual_OC_Flag EQ CLOSE_FLAG ||\
	 Screen_Status.Com_Time > 0 ||\
	 Chk_UDisk_Processing()) //�ػ�״̬������ʾ,��ǰ��ͨ��״̬Ҳ����ʾ
    return;
 

  //Set_Clock_Hight_Speed(); //����Ϊ��������ģʽ
  if(Screen_Para.Scan_Para.Rows EQ 0)
  {
	Screen_Para.Scan_Para.Rows = 16;
	SET_SUM(Screen_Para);
  }

  Color_Num = Get_Screen_Color_Num();
  //Block���������Ϊ��Ԫ������ĸ���
  Blocks = Screen_Para.Base_Para.Height / (Screen_Para.Scan_Para.Rows * (Screen_Para.Scan_Para.Rows_Fold + 1)); //1.2.4.8.16ɨ��
 
  if(Blocks > MAX_SCAN_BLOCK_NUM)
	 Blocks = MAX_SCAN_BLOCK_NUM;

  Cols = Screen_Para.Base_Para.Width / 8;
  //��ÿ��Blocks����ɨ��
  //ÿһ��ɨ������ҪScreen_Para.Base_Para.Width / 8 * Screen_Para.Scan_Para.Rows_Fold���ֽ�
  for(i = 0; i < Cols * (Screen_Para.Scan_Para.Rows_Fold + 1); i ++)
  {
#if BUILD_SCAN_DATA_INDEX_EN
  	Get_Scan_Data0(Screen_Status.Scan_Row, i);	
#else
    //��ÿ��Block��ÿ��ɨ����ͬʱ���һ���ֽ�
    for(j = 0; j < Blocks; j++)
    {
    //��ȡ��ɨ�����ϵ������ֽڲ����
      Get_Scan_Data(j, \
              Screen_Para.Scan_Para.Rows, \
              Screen_Status.Scan_Row,\
              Cols, \
              i, \
              Screen_Para.Scan_Para.Direct, \
              Screen_Para.Scan_Para.Rows_Fold, \
              Screen_Para.Scan_Para.Cols_Fold,\
              Scan_Data[j]);
    }
#endif	

#if SCAN_DATA_MODE EQ 0    
    //�����е�block���һ���ֽ�
    //����Ǵ������ң�Ӧ���������λ�������λ
    if(Screen_Para.Scan_Para.Direct EQ 0x00 || Screen_Para.Scan_Para.Direct EQ 0x01)
    {
	 if(Color_Num EQ 1)
	 {  
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,7); 
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,6);
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,5);
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,4);
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,3);
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,2);
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,1); 
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,0);
	  }
	  else if(Color_Num EQ 2)
	  {
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,7); 
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,6);
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,5);
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,4);
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,3);
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,2);
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,1); 
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,0);
	  }	
	  else
	  {
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,7); 
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,6);
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,5);
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,4);
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,3);
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,2);
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,1); 
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,0);	  
	  }   
     }
     else //��������������Ӧ���������λ
     {
	 
	 if(Color_Num EQ 1)
	 {  
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,0); 
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,1);
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,2);
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,3);
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,4);
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,5);
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,6); 
	   SET_SHIFT_BIT_1(Blocks, Scan_Data,7);
	  }
	  else if(Color_Num EQ 2)
	  {
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,0); 
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,1);
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,2);
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,3);
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,4);
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,5);
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,6); 
	   SET_SHIFT_BIT_2(Blocks, Scan_Data,7);
	  }
	  else
	  {
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,0); 
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,1);
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,2);
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,3);
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,4);
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,5);
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,6); 
	   SET_SHIFT_BIT_3(Blocks, Scan_Data,7);
	  }
	       
     }
	}
#else
	 //�˴���Ӳ��ɨ�跽ʽ����
#endif	 
	//�ر�OEʹ��
	Set_OE_Duty_Polarity(0, Screen_Para.Scan_Para.OE_Polarity);

	if(Screen_Para.Scan_Para.Line_Hide > 0)
	  Delay_us(Screen_Para.Scan_Para.Line_Hide*10); //������ʱ��
    Delay_us(20);
    SET_LAT(0); //�����ź����
    SET_LAT(1); //�����ź����
    
    Set_Block_Row(Screen_Status.Scan_Row);
    Screen_Status.Scan_Row++;
    if(Screen_Status.Scan_Row >= Screen_Para.Scan_Para.Rows)
      Screen_Status.Scan_Row = 0;
	
	//���´�OE
	Set_OE_Duty_Polarity(100, Screen_Para.Scan_Para.OE_Polarity);
	//_USART_Cmd(USART1, DISABLE);
    //Set_Clock_Normal_Speed();
	//_USART_Cmd(USART1, ENABLE); 
	//USART_Clar
   
}
