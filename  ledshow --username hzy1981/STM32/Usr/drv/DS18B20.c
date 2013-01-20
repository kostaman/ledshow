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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ; //��©���
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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ; //��������
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
void Rx_PresencePulse(void)
{
    GPIO_DQ_Input_Mode() ;
    while( DQ_ReadBit()) ;  //�ȴ�DS18b20Ӧ��
    while( DQ_ReadBit() == 0) ; //DS18b20����������60~240us ,Ȼ��������������������
    Delay_Nus(300) ;
    GPIO_DQ_Out_Mode() ;    //������ɣ��������¿�������
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
            Delay_Nus(110) ; //������60us��120us֮��
            DQ_Write_1() ;
            Delay_Nus(5) ;
        }
        data >>= 1 ;
    }
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
void Read_Temperature(unsigned char *sign ,
                      unsigned char *interger ,
                      unsigned int *decimal)
{
    unsigned char a=0;
    unsigned char b=0;
    //volatile unsigned char c=0;
    //volatile unsigned char d=0;
    //volatile unsigned char e=0;
    
    unsigned int tmp ;
    
    DS18B20_Init();
    Write_OneByte_ToDS18b20(ROM_Read_Cmd);
  
    DS18B20_Init();
    Write_OneByte_ToDS18b20(ROM_Skip_Cmd);//���������кŲ���
    Write_OneByte_ToDS18b20(Convert_T); //�����¶�ת��
    Delay_Nms(780);//�ȴ�DS18b20ת�����
    
    DS18B20_Init();
    Write_OneByte_ToDS18b20(ROM_Skip_Cmd);
    Write_OneByte_ToDS18b20(Read_Scratchpad); //��ȡ�Ĵ������ݣ����ԴӼĴ���0�����Ĵ���8��
    
    a= Read_OneByte_FromDS18b20();     //�¶ȵ�8λ
    b= Read_OneByte_FromDS18b20();     //�¶ȸ�8λ
    //c= Read_OneByte_FromDS18B20();   //TH
    //d= Read_OneByte_FromDS18B20();   //TL
    //e= Read_OneByte_FromDS18B20();   //Configuration Register
    
    Tx_ResetPulse();  //�ж����ݶ�ȡ
    tmp = (b<<8) | a ;
    if(b & 0xF0)
    {
    *sign = 1 ;              //���Ų���
    tmp = ~tmp+1 ;
    }
    else 
    {
    sign = 0 ;
    }
    *interger = (tmp>>4) & 0x00FF;  //��������
    *decimal = (tmp & 0x000F) * 625 ; //С������ 
}

/******************************************
�������ƣ�DS18B20_Init
��    �ܣ���ʼ��DS18b20
��    ������
����ֵ  ����
*******************************************/
void DS18B20_Init(void)
{
    Tx_ResetPulse();
    Rx_PresencePulse(); 
}

//��ȡ�¶�
INT16S Get_DS18B20_Temp(void)
{
  unsigned char sign, integer;
  unsigned int dec;
    
  Read_Temperature(&sign, &integer, &dec);
  return integer;
}

INT8U Chk_DS18B20_Sensor(void)
{
  if(DS18B20_In_Flag EQ EXIST_18B20_FLAG)
    return 1;
  else 
    return 0;
}
