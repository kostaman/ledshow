#define DS1302_C
#include "Includes.h"

/*
void Dataout_init(void) 
{ 
GPIO_InitTypeDef GPIO_InitStructure; 
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
//PB14  CE     PB12 SCLK 
GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13; 
GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP; 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
GPIO_Init(GPIOB, &GPIO_InitStructure); 
} 
void Datain_init(void) 
{ 
GPIO_InitTypeDef GPIO_InitStructure; 
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13; 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
GPIO_Init(GPIOB, &GPIO_InitStructure); 
} 

*/
void SPI_DS1302_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  SPI_Cmd(SPI1, ENABLE);
/* PA 4,6,Ϊ���*/
  GPIO_InitStructure.GPIO_Pin =  ds1302Clk | ds1302Rst | ds1302Data;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//��������io��Ϊ�����
void Set_DataIO_Input(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  GPIO_InitStructure.GPIO_Pin =  ds1302Data;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

//��������io��Ϊ�����
void Set_DataIO_Output(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  GPIO_InitStructure.GPIO_Pin =  ds1302Data;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void SendData_1302(u8 Data)
{ u8 i;
 u8 cTmp;

 Set_DataIO_Output();

 for(i=0;i<8;i++)
 { 
   cTmp= (Data& 0x01); //���ݶ˵���tmp���ݵ�ĩλֵ
  if(cTmp)    //1
      GPIO_SetBits(GPIOA,ds1302Data);
  else
   GPIO_ResetBits(GPIOA,ds1302Data); 
  Data>>=1;
  GPIO_SetBits(GPIOA,ds1302Clk);
  Delay_us(1);
  GPIO_ResetBits(GPIOA,ds1302Clk);
 }
}
/*д��1�����߶���ֽڣ���1���������������
#define WrMulti     0xbe //д�����ֽڵ�ָ�����
#define WrSingle    0x84 //д�뵥���ֽڵ�ָ�����
��2�������Ǵ�д���ֵ
��3�������Ǵ�д�������ָ��
*/ 
void WriteByte_1302(u8 CmdDat,u8 Num,u8 *pSend)
{ 
 u8 i=0;
 GPIO_ResetBits(GPIOA,ds1302Rst);
 Delay_us(1);
 GPIO_SetBits(GPIOA,ds1302Rst);
 SendData_1302(CmdDat);
 for(i=0;i<Num;i++)
 { SendData_1302(*(pSend+i));
 }
 GPIO_ResetBits(GPIOA,ds1302Rst);
}
/*�����ֽڣ���һ������������
 #define RdMulti  0xbf //��������ֽڵ�ָ�����
 ��2�������Ƕ������ֽ�������3����ָ����������ָ��
 */
void RecByte_1302(u8 CmdDat,u8 Num,u8 *pRec)
{ 
 u8 i,j,tmp,cTmp;
 GPIO_ResetBits(GPIOA,ds1302Rst);//��λ����Ϊ�͵�ƽ
 Delay_us(1);
 GPIO_ResetBits(GPIOA,ds1302Clk);
 Delay_us(1);
 GPIO_SetBits(GPIOA,ds1302Rst);
 SendData_1302(CmdDat); //��������

 Set_DataIO_Input();

 tmp = 0;
 //�˴�Ӧ�ø�Ϊ�����ݿ�
 for(i=0;i<Num;i++)
 { for(j=0;j<8;j++)
  { tmp>>=1;
   cTmp=GPIO_ReadInputDataBit(GPIOA,ds1302Data);
   if(cTmp)
    tmp|=0x80;
   GPIO_SetBits(GPIOA,ds1302Clk);
   Delay_us(1);
   GPIO_ResetBits(GPIOA,ds1302Clk);       
  }
  *(pRec+i)=tmp;
 }
 Delay_us(1);
 GPIO_ResetBits(GPIOA,ds1302Rst);//��λ����Ϊ�͵�ƽ
}
/*
��д�����Ĵ��������λΪ0ʱ,��������д��Ĵ�����
д�����Ĵ�������ͨ�������ֽ�8E��8F���涨��ֹд��/������д����λ�����ڶ��ֽڴ���ģʽ��д�롣
��д�����Ĵ��������λΪ1ʱ����ֹ����д��Ĵ�����

ʱ��ֹͣλ����:������Ĵ����ĵ�7λʱ��ֹͣλ����Ϊ0ʱ��ʱ�ӿ�ʼ
������Ĵ����ĵ�7λʱ��ֹͣλ����Ϊ1ʱ��ʱ������ֹͣ��
   
    ���ݴ���Ĳ�������������
 ��һ�������������֣���2��������д�������
 д�������8EH,00H
 д��ֹ���8EH,80H
 �����������80H,00H
 ������ֹ���80H,80H
*/
void WrCmd(u8 CmdDat,u8 CmdWord)
{ u8 CmdBuf[2];
 CmdBuf[0]=CmdWord;
 WriteByte_1302(CmdDat,1,CmdBuf);
}

void test_main()
{

 u8 Ds1302SendBuf[8]={0x30,0x32,0x01,0x10,0x01,0x01,0x08,33};  //�������ݻ�����	  00,02, 
 u8 Ds1302RecBuf[8];    //�������ݻ�����
 WrCmd(WrEnDisCmd,WrEnDat);  //д����
 WrCmd(OscEnDisCmd,OscEnDat); //��������
 WriteByte_1302(WrMulti,8,Ds1302SendBuf);//��ʱ��ֵ�͵�DS1302��
 RecByte_1302(RdMulti,8,Ds1302RecBuf); // ������������
 }

void DS1302_Init(void)
{
  INT8U Temp[8];
  Unselect_SPI_Device();
  SPI_DS1302_Init();

  RecByte_1302(RdMulti,8,Temp); //��ʱ������
  
  if((Temp[0] & 0x80 > 0))  //������
  { 
    WrCmd(WrEnDisCmd,WrEnDat);  //д����
    WrCmd(OscEnDisCmd,OscEnDat); //��������
	WrCmd(WrEnDisCmd,WrDisDat);  //д����ر�
  }
}
/*
#define T_YEAR  0 //--�����պ�����������0��ʼ�����մ�1�������1900�����
#define T_MONTH 1
#define T_DATE  2
#define T_HOUR  3
#define T_MIN   4
#define T_SEC   5
#define T_WEEK  6
*/
//��ȡ��ǰʱ��
INT8U Set_Cur_Time(INT8U Time[])//S_Time *pTime)
{
  INT8U Temp[8];

  Temp[0] = Hex2Bcd_Byte(Time[T_SEC]);
  Temp[1] = Hex2Bcd_Byte(Time[T_MIN]);
  Temp[2] = Hex2Bcd_Byte(Time[T_HOUR]);
  Temp[3] = Hex2Bcd_Byte(Time[T_DATE]);
  Temp[4] = Hex2Bcd_Byte(Time[T_MONTH]);
  Temp[5] = Hex2Bcd_Byte(Time[T_WEEK]);
  Temp[6] = Hex2Bcd_Byte(Time[T_YEAR]);
  Temp[7] = 0;

  Unselect_SPI_Device();
  SPI_DS1302_Init(); //���³�ʼ��SPI��

  WrCmd(WrEnDisCmd,WrEnDat);  //д����
  WriteByte_1302(WrMulti,8,Temp);//��ʱ��ֵ�͵�DS1302��
  WrCmd(WrEnDisCmd,WrDisDat);  //д����ر�
  return 1;
}

//���õ�ǰʱ��
INT8U _Get_Cur_Time(INT8U Time[])
{
  INT8U Temp[8];

  Unselect_SPI_Device();
  SPI_DS1302_Init();  //���³�ʼ��SPI��

  RecByte_1302(RdMulti,8,Temp); // ������������

  if((Temp[0] & 0x80)) //����û��ʹ��?
  {
    Temp[0] = Temp[0] & 0x7F;
    
	WrCmd(WrEnDisCmd,WrEnDat);  //д����
    WrCmd(OscEnDisCmd,OscEnDat); //��������
	WrCmd(WrEnDisCmd,WrDisDat);  //д����ر�
  }

  Time[T_SEC] = Bcd2Hex_Byte(Temp[0]);
  Time[T_MIN] = Bcd2Hex_Byte(Temp[1]);
  Time[T_HOUR] = Bcd2Hex_Byte(Temp[2]);
  Time[T_DATE] = Bcd2Hex_Byte(Temp[3]);
  Time[T_MONTH] = Bcd2Hex_Byte(Temp[4]);
  Time[T_WEEK] = Bcd2Hex_Byte(Temp[5]);
  Time[T_YEAR] = Bcd2Hex_Byte(Temp[6]);

  return 1;
}
