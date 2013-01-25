//=========================DS18b20.c================================//
/*
#include "stm32f10x_lib.h"
#include "DS18b20.h"
#include "SysTick_Delay.h"
*/
#include "Includes.h"

#define NO_18B20_FLAG 0x56789123
#define EXIST_18B20_FLAG 0x13452389

INT32U DS18B20_In_Flag; 

#define Delay_Nus Delay_us 
#define Delay_Nms Delay_ms

#define DIS_INT() __disable_irq()
#define EN_INT() __enable_irq()
/******************************************
�������ƣ�GPIO_DQ_Out_Mode
��    �ܣ�����DQ����Ϊ��©���ģʽ
��    ������
����ֵ  ����
*******************************************/
void GPIO_DQ_Out_Mode(void)
{
    GPIO_InitTypeDef GPIO_InitStructure ;
    
    GPIO_InitStructure.GPIO_Pin = DQ_GPIO_Pin ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ; //�������
    GPIO_Init(DQ_GPIO ,&GPIO_InitStructure) ;
}
/******************************************
�������ƣ�GPIO_DQ_Input_Mode
��    �ܣ�����DQ����Ϊ��������ģʽ
��    ������
����ֵ  ����
*******************************************/
void GPIO_DQ_Input_Mode(void)
{
    GPIO_InitTypeDef GPIO_InitStructure ;
    
    GPIO_InitStructure.GPIO_Pin = DQ_GPIO_Pin ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; //��������
    GPIO_Init(DQ_GPIO ,&GPIO_InitStructure) ;
}
/******************************************
�������ƣ�Tx_ResetPulse
��    �ܣ����͸�λ����
��    ������
����ֵ  ����
*******************************************/
void Tx_ResetPulse(void)
{
    GPIO_DQ_Out_Mode() ;
    DQ_Write_0() ;  //��λ����
    Delay_Nus(500) ; //���ٱ���480us
    DQ_Write_1() ;  //�����������ٶ�
    Delay_Nus(1) ;
}
/******************************************
�������ƣ�Rx_PresencePulse
��    �ܣ�����Ӧ���ź�
��    ������
����ֵ  ����
*******************************************/
INT8U Rx_PresencePulse(void)
{
    INT16U i;

    GPIO_DQ_Input_Mode() ;

	for(i = 0; i < 50; i ++)
	{
      if( DQ_ReadBit() EQ 0)   //�ȴ�DS18b20Ӧ��
	    break;
	  Delay_Nus(1);
    }

	if(i EQ 50)
	  return 0;

	for(i = 0; i < 250; i ++)
	{
	  if( DQ_ReadBit())  //DS18b20����������60~240us ,Ȼ��������������������
	    break;
	  Delay_Nus(1);
	}

	if(i EQ 250)
	  return 0;

    Delay_Nus(10) ;
    GPIO_DQ_Out_Mode() ;    //������ɣ��������¿�������

	return 1;
}
/******************************************
�������ƣ�Write_OneByte_ToDS18b20
��    �ܣ�дһ���ֽڵ�DS18b20
��    ������
����ֵ  ����
*******************************************/
void Write_OneByte_ToDS18b20(unsigned char data)
{
    unsigned char i ;
    GPIO_DQ_Out_Mode() ;
    for(i=0 ;i<8 ;i++)
    {
        if(data&0x01)    //��λ��ǰ
        {
            //д1
            DQ_Write_0() ; //дʱ���϶���Ǵ����ߵĵ͵�ƽ��ʼ
            Delay_Nus(8) ;  //15us������
            DQ_Write_1() ;
            Delay_Nus(80) ; //����д1ʱ϶������60us
        }
        else
        {
            //д0
            DQ_Write_0() ;
            Delay_Nus(80) ; //������60us��120us֮��
            DQ_Write_1() ;
            Delay_Nus(5) ;
        }
        data >>= 1 ;
    }
}

void DS18B20_StartConvert(void)
{
    DIS_INT();
    DS18B20_Reset();
    Write_OneByte_ToDS18b20(ROM_Skip_Cmd);//���������кŲ���
    Write_OneByte_ToDS18b20(Convert_T); //�����¶�ת��
	EN_INT();
    //Delay_Nms(780);//�ȴ�DS18b20ת�����
}

/******************************************
�������ƣ�Read_OneByte_FromDS18b20
��    �ܣ���DS18b20��һ���ֽ�
��    ������
����ֵ  ������������
*******************************************/
unsigned char Read_OneByte_FromDS18b20(void)
{
    unsigned char i ,data = 0 ;
    
    for(i=0 ;i<8 ;i++)
    {
        GPIO_DQ_Out_Mode() ;
        data >>= 1 ;
        DQ_Write_0() ;
        Delay_Nus(2) ;
        GPIO_DQ_Input_Mode() ;
        Delay_Nus(1) ;
        if(DQ_ReadBit())
        {
            data |= 0x80 ;
        }
        Delay_Nus(70) ;   //�ȴ���һλ������ɴ���
    }
    GPIO_DQ_Out_Mode() ;
    return data ;
}
/******************************************
�������ƣ�Read_Temperature
��    �ܣ���ȡ�¶���Ϣ
��    ����*sign - ������ţ����ϻ����£�
          *integer - ������������
          *decimal - ����С������
����ֵ  ����
*******************************************/
INT16S Read_Temperature(unsigned char *sign ,
                      unsigned char *interger ,
                      unsigned int *decimal)
{
    unsigned char a=0;
    unsigned char b=0;
    //volatile unsigned char c=0;
    //volatile unsigned char d=0;
    //volatile unsigned char e=0;
    
    INT16U tmp ;
/*    
    DS18B20_Reset();
    Write_OneByte_ToDS18b20(ROM_Read_Cmd);
  
    DS18B20_Reset();
    Write_OneByte_ToDS18b20(ROM_Skip_Cmd);//���������кŲ���
    Write_OneByte_ToDS18b20(Convert_T); //�����¶�ת��
    Delay_Nms(780);//�ȴ�DS18b20ת�����
*/ 
    DIS_INT();
	   
    DS18B20_Reset();
    Write_OneByte_ToDS18b20(ROM_Skip_Cmd);
    Write_OneByte_ToDS18b20(Read_Scratchpad); //��ȡ�Ĵ������ݣ����ԴӼĴ���0�����Ĵ���8��
    
    a= Read_OneByte_FromDS18b20();     //�¶ȵ�8λ0x90;//
    b= Read_OneByte_FromDS18b20();     //�¶ȸ�8λ0xFC;//--�ò�������Ϊ����55

	EN_INT();
    //c= Read_OneByte_FromDS18B20();   //TH
    //d= Read_OneByte_FromDS18B20();   //TL
    //e= Read_OneByte_FromDS18B20();   //Configuration Register
    
    //Tx_ResetPulse();  //�ж����ݶ�ȡ
    tmp = (b<<8) | a ;
    if(b & 0xFC)
    {
    *sign = 1 ;              //���Ų���
    tmp = ~tmp+1 ;
    }
    else 
    {
    *sign = 0 ;
    }
    *interger = (tmp>>4) & 0x00FF;  //��������
    *decimal = (tmp & 0x000F) * 625 ; //С������ 

    return (INT16S)((float)tmp * 0.0625 * 10);
}

void DS18B20_Init(void)
{
    INT8U Re;

	DIS_INT();
	Re = DS18B20_Reset();
	EN_INT();

	if(Re EQ 0) //�������μ��18B20�Ƿ����
	{
	  Delay_ms(100);

	  DIS_INT();
	  Re = DS18B20_Reset();
	  EN_INT();
	}

    if(Re)
	{
	  DS18B20_In_Flag = EXIST_18B20_FLAG;	//18B20����
	  DS18B20_StartConvert();
	  Delay_ms(900);
	  Screen_Status.Temperature = Get_DS18B20_Temp();
	} 
	else
	{
	  DS18B20_In_Flag = NO_18B20_FLAG;
	}
}
/******************************************
�������ƣ�DS18B20_Reset
��    �ܣ���ʼ��DS18b20
��    ������
����ֵ  ����
*******************************************/
INT8U DS18B20_Reset(void)
{
    Tx_ResetPulse();
	return 	Rx_PresencePulse();
}

//��ȡ�¶�
INT16S Get_DS18B20_Temp(void)
{
  unsigned char sign, integer;
  unsigned int dec;
  INT16S Temp;
    
  Temp = Read_Temperature(&sign, &integer, &dec);

  if(sign)
    Temp = 0 - Temp;

  DS18B20_StartConvert();
  return Temp;//integer;
}

INT8U Chk_DS18B20_Sensor(void)
{
  if(DS18B20_In_Flag EQ EXIST_18B20_FLAG)
    return 1;
  else 
    return 0;
}
