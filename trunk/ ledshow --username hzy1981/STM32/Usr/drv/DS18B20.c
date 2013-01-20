#include "Includes.h"

#if TEMP_SHOW_EN

#define NO_18B20_FLAG 0x56789123
#define EXIST_18B20_FLAG 0x13452389

INT32U DS18B20_In_Flag; 

#define EnableINT()  __disable_irq()
#define DisableINT() __enable_irq()

#define DS_PORT   SHT1X_SDA_PORT
#define DS_DQIO   SHT1X_SDA_PIN
//#define DS_RCC_PORT  RCC_APB2Periph_GPIOA
#define DS_PRECISION 0x7f   //�������üĴ��� 1f=9λ; 3f=10λ; 5f=11λ; 7f=12λ;
#define DS_AlarmTH  0x64
#define DS_AlarmTL  0x8a
#define DS_CONVERT_TICK 1000

#define ResetDQ() GPIO_ResetBits(DS_PORT,DS_DQIO)
#define SetDQ()  GPIO_SetBits(DS_PORT,DS_DQIO)

#define GetDQ()  GPIO_ReadInputDataBit(DS_PORT,DS_DQIO)
 
 
static unsigned char TempX_TAB[16]={0x00,0x01,0x01,0x02,0x03,0x03,0x04,0x04,0x05,0x06,0x06,0x07,0x08,0x08,0x09,0x09};

void Set_IO_Input(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  GPIO_InitStructure.GPIO_Pin =  SHT1X_SDA_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DS_PORT, &GPIO_InitStructure);

}

//��������io��Ϊ�����
void Set_IO_Output(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  GPIO_InitStructure.GPIO_Pin =  SHT1X_SDA_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DS_PORT, &GPIO_InitStructure);

}
/*
void Delay_us(u32 Nus) 
{  
 SysTick->LOAD=Nus*9;          //ʱ�����       
 SysTick->CTRL|=0x01;             //��ʼ����     
 while(!(SysTick->CTRL&(1<<16))); //�ȴ�ʱ�䵽��  
 SysTick->CTRL=0X00000000;        //�رռ����� 
 SysTick->VAL=0X00000000;         //��ռ�����      
}
*/  

 

unsigned char ResetDS18B20(void)
{
 long int i;
 unsigned char resport = 0;
 SetDQ();
 Delay_us(50);
 
 ResetDQ();
 Delay_us(500);  //500us ����ʱ���ʱ�䷶Χ���Դ�480��960΢�룩
 SetDQ();
 Delay_us(40);  //40us
 //resport = GetDQ();
 Set_IO_Input();
 for(i = 0; i < 1000; i ++)
 {
   if(GetDQ() EQ 0) //�ȴ����ص͵�ƽ
   {
     resport = 1;
     break;
   }
   Delay_us(1);
 }
 //while(GetDQ());
 Delay_us(500);  //500us
 Set_IO_Output();
 SetDQ();
 return resport;
}

void DS18B20WriteByte(unsigned char Dat)
{
 unsigned char i;
 for(i=8;i>0;i--)
 {
   ResetDQ();     //��15u���������������ϣ�DS18B20��15-60u����
  Delay_us(5);    //5us
  if(Dat & 0x01)
   SetDQ();
  else
   ResetDQ();
  Delay_us(65);    //65us
  SetDQ();
  Delay_us(2);    //������λ��Ӧ����1us
  Dat >>= 1; 
 } 
}


unsigned char DS18B20ReadByte(void)
{
 unsigned char i,Dat = 0;
 SetDQ();
 Delay_us(5);
 for(i=8;i>0;i--)
 {
   Dat >>= 1;
    ResetDQ();     //�Ӷ�ʱ��ʼ�������ź��߱�����15u�ڣ��Ҳ�������������15u�����
  Delay_us(5);   //5us
  SetDQ();
  Delay_us(5);   //5us
  
  Set_IO_Input();
  if(GetDQ())
    Dat|=0x80;
  else
   Dat&=0x7f;  
  Delay_us(65);   //65us

  Set_IO_Output();
  SetDQ();
 }
 return Dat;
}


void ReadRom(unsigned char *Read_Addr)
{
 unsigned char i;

 DS18B20WriteByte(ReadROM);
  
 for(i=8;i>0;i--)
 {
  *Read_Addr=DS18B20ReadByte();
  Read_Addr++;
 }
}

//��ʼ��18B20
void DS18B20Init(unsigned char Precision,unsigned char AlarmTH,unsigned char AlarmTL)
{
 INT32U i;

 DisableINT();
 
 if(ResetDS18B20())
 {
    DS18B20_In_Flag = EXIST_18B20_FLAG;	//18B20����
	DS18B20WriteByte(SkipROM); 
	DS18B20WriteByte(WriteScratchpad);
	DS18B20WriteByte(AlarmTL);
	DS18B20WriteByte(AlarmTH);
	DS18B20WriteByte(Precision);
	
	ResetDS18B20();
	DS18B20WriteByte(SkipROM); 
	DS18B20WriteByte(CopyScratchpad);
 }
 else
    DS18B20_In_Flag = NO_18B20_FLAG;

 EnableINT();

 if(DS18B20_In_Flag EQ EXIST_18B20_FLAG)
 {
   Set_IO_Input();
   for(i = 0; i < 1000; i ++)
   {
     Delay_us(1);
	 if(GetDQ())
	   break;
     //while(!GetDQ());  //�ȴ�������� ///////////
   }
   Set_IO_Output();
 }
}


void DS18B20StartConvert(void)
{
 if(DS18B20_In_Flag EQ NO_18B20_FLAG)
   return;

 DisableINT();
 ResetDS18B20();
 DS18B20WriteByte(SkipROM); 
 DS18B20WriteByte(StartConvert); 
 EnableINT();
}

void DS18B20_Configuration(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;
 
 //RCC_APB2PeriphClockCmd(DS_RCC_PORT, ENABLE);

 GPIO_InitStructure.GPIO_Pin = DS_DQIO;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //2Mʱ���ٶ�
 GPIO_Init(DS_PORT, &GPIO_InitStructure);
}


void DS18B20_Start(void)
{
 DS18B20_Configuration();
 DS18B20Init(DS_PRECISION, DS_AlarmTH, DS_AlarmTL);
 DS18B20StartConvert();
}


unsigned short DS18B20_Read(void)
{
 unsigned char TemperatureL,TemperatureH;
 unsigned int  Temperature;

 if(DS18B20_In_Flag EQ NO_18B20_FLAG)
   return 0;

 DisableINT();
 ResetDS18B20();
 DS18B20WriteByte(SkipROM); 
 DS18B20WriteByte(ReadScratchpad);
 TemperatureL=DS18B20ReadByte();
 TemperatureH=DS18B20ReadByte(); 
 ResetDS18B20();
 EnableINT();

 if(TemperatureH & 0x80)
  {
  TemperatureH=(~TemperatureH) | 0x08;
  TemperatureL=~TemperatureL+1;
  if(TemperatureL==0)
   TemperatureH+=1;
  }

 TemperatureH=(TemperatureH<<4)+((TemperatureL&0xf0)>>4);
 TemperatureL=TempX_TAB[TemperatureL&0x0f];

 //bit0-bit7ΪС��λ��bit8-bit14Ϊ����λ��bit15Ϊ����λ
 Temperature=TemperatureH;
 Temperature=(Temperature<<8) | TemperatureL; 

 DS18B20StartConvert();

 return  Temperature;
}

//��ȡ�¶�
INT16S Get_DS18B20_Temp(void)
{
  return DS18B20_Read();
}

INT8U Chk_DS18B20_Sensor(void)
{
  if(DS18B20_In_Flag EQ EXIST_18B20_FLAG)
    return 1;
  else 
    return 0;
}
#endif

 

 

