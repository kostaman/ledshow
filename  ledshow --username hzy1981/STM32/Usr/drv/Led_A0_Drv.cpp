#define LED_A0_DRV_C
#include "Includes.h"

#if CARD_TYPE == CARD_A0
/*
//GPIO初始化
void GPIO_Init()
{
  
}

//SPI初始化
void SPI_Init()
{
  
}

//UART初始化
void UART_Init()
{
  
}
*/

//CPU
void Hardware_Init()
{

}

void OS_Put_Char(char Chr)
{
  //qDebug("%c", Chr);
}

void Put_Char(char c)
{
  
}

//获取当前时间
INT8U Get_Cur_Time()//S_Time *pTime)
{
  return 1;
}

//设置当前时间
INT8U Set_Cur_Time(INT8U Time[])
{
  return 1;
}

//存储器初始化
void Mem_Init()
{

}

//获取当前温度
INT16S Get_Cur_Temp()
{
  return -215; 
}

//获取当前湿度
INT16U Get_Cur_Humidity()
{
  return 60; 
}

//获取当前噪音
INT16U Get_Cur_Noise()
{
  return 60;
}
//设置移位数据
//Block表示块号
//RGB表示颜色0-R，1-G，2-B
//Bit表示位
void Set_Shift_Bit(INT16U Block, INT8U RGB, INT8U Bit)
{
  
}

//设置移位时钟
void Set_Shift_Bit_Clk(INT8U Value)
{
  
}

//设置块使能信号
void Set_Block_OE(INT8U Value)
{
  
}


//设置块锁存信号
void Set_Block_Latch(INT8U Value)
{
  
}

//设置块行号
void Set_Block_Row(INT16U Row)
{
  
}

//重置扫描定时器,Freq表示扫描频率
void Reset_Scan_Timer(INT32U Freq)
{
  
}

//延时us
void Delay_us(INT32U Value)
{
  
}


#endif
