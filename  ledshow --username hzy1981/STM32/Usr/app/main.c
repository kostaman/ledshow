#include "Includes.h"

#if NET_EN
#define MAIN_STACK_SIZE 500
#else
#define MAIN_STACK_SIZE 400
#endif

#define SMS_GPRS_STACK_SIZE 400
 
 void test()
 {
        int i; 
        unsigned char t1[18]={0x24,0x21,0xf0,0x7f,0x80,0x37,0xff,0x1f}; 
        unsigned char t2[18];//0xEA,0xE8,0xE9,0xC8,0xEC,0x6F,0x4C,0x54 

	    transpose8(t1, t2/*, 1*/);
        transpose4(t1, t2/*, 1*/);  
		//juzhen(t1, t2, 0);
		for(i = 0; i < 8; i	++)
		  printf("%d = %x", i, t2[i]);

 }

typedef struct
{
  INT8U Head;

  INT32U Stack[MAIN_STACK_SIZE];	//�˹���ջ
  INT16U Left;

  INT8U Tail;
}S_Main_Stack;

typedef struct
{
  INT8U Head;

  INT32U Stack[SMS_GPRS_STACK_SIZE];
  INT16U Left;

  INT8U Tail;
}S_SMS_GPRS_Stack;

S_Main_Stack Main_Stack = {CHK_BYTE, {0}, 0, CHK_BYTE};	 //������stack
S_SMS_GPRS_Stack SMS_GPRS_Stack = {CHK_BYTE, {0}, 0, CHK_BYTE};	 //���š�GRPSͨ��ά������

//���ϵͳ��ջʣ�����
void Chk_Main_Stack(void)
{
#if CLOCK_EN
  INT16U i = 0;
  INT8U *p;
  static INT8U Min = 0xFF;

  //ÿ���Ӵ�ӡһ�ζ�ջ��С
  if(Min != Cur_Time.Time[T_MIN])
  {
    Min = Cur_Time.Time[T_MIN]; 
	
	p =  (INT8U *)&Main_Stack.Stack[0]; 
	while(*p EQ 0)
	{
	  p ++;
	  i ++;
	}

	Main_Stack.Left = i;

    debug("main stack remain %d", Main_Stack.Left);

#if SMS_EN || GPRS_EN
    i = 0;

	p =  (INT8U *)&SMS_GPRS_Stack.Stack[0];
	while(*p EQ 0)
	{
	  p ++;
	  i ++;
	}

	SMS_GPRS_Stack.Left = i;
	debug("smsGprs stack remain %d", SMS_GPRS_Stack.Left);
#endif
  }
#else
  INT16U i = 0;
  static INT32U Sec = 0;
  static INT8U Sec_Counts = 0;

  //ÿ���Ӵ�ӡһ�ζ�ջ��С
  if(Sec != Pub_Timer.Sec)
  {
    Sec = Pub_Timer.Sec;
    Sec_Counts ++;
	  
    if(Sec_Counts >= 60)
	{
	    Sec_Counts = 0;

		while(Main_Stack.Stack[i] EQ 0)
		{ 
		i ++;
		}
		
		Main_Stack.Left = i*4;
	
	    debug("stack left %d", Main_Stack.Left);
	}
  }
#endif
  
  if(CHK_HT(Main_Stack) EQ 0)
  {
    ASSERT_FAILED();
  }


}

extern const char version[];

void mainInit(void)
{
  Ram_Init();

#if WDG_EN
  IWDG_Init();
#endif

  Hardware_Init();

  OS_Debug_Print("----------system start----------");
  //OS_Debug_Print("----------version: %s----------", version);

  Check_Storage_Size();
  
  RST_Periph();

  Para_Init(); //������ʼ��

  Com_Init(); //��ʼ������

#if UDISK_EN  
  UDisk_Init(); //U�̳�ʼ��
#endif

#if CLOCK_EN
  DS1302_Init(); //������1s�ٳ�ʼ��DS1302���ֲ�Ҫ��
#endif
  //Fac_Status_Self_Test(); //�Լ����

#if NET_EN
  Net_Init();
#endif

#if TEMP_SHOW_EN || HUMIDITY_SHOW_EN
  SHT1X_Init(); 
#endif
   
  Para_Show(); //�ϵ������ʾ

  SET_STATUS_LED_ON(); //��LED״̬��

  //Encrypt_Chk();
  //Read_Storage_Data_NoCS(SDI_ZK_DATA, 0x8030, 16, (INT8U *)Pub_Buf,  (INT8U *)Pub_Buf, sizeof(Pub_Buf));

}

void mainProc(void)
{
    Screen_Test(); //��Ļ���

	//Fac_Status_Self_Test(); //Ӳ���Լ�

#if SHELL_EN
    Shell_Proc();
#endif
	
#if UDISK_EN
    UDisk_Proc(); //u�̴���
#endif

    Show_Main_Proc();

/*
#if NET_EN
	Net_Proc();
#endif
*/
    Chk_Main_Stack();

    Clr_Watch_Dog();
}

//ע���޸�����ʼ��ַ��Ҫ�ĺ�APP_ADDRESS_OFF,��������ܲ�����������
#if SMS_EN == 0 && GPRS_EN == 0
int main(void)
{
  __set_MSP((INT32U)(&Main_Stack.Stack[MAIN_STACK_SIZE - 1])); //�޸�Ϊ�˹���ջ��ʽ

  mainInit();

  while(1)
  {
	mainProc();
  } 
}
#else

//SMS��GRPSͨ������
void smsGPRSTask(void)
{
  ModuleInit();
  while(1)
  {
    Chk_Module_Status();
    SmsProc();
  }
}

//������
void mainTask(void)
{
  mainInit();

  OS_Create_Task(&smsGPRSTask,(OS_STK *)(&SMS_GPRS_Stack.Stack[SMS_GPRS_STACK_SIZE - 1]),sizeof(SMS_GPRS_Stack.Stack),"smsGPRSTask");

  while(1)
  {
	mainProc();
	OS_TimeDly_Ms(10);
  }
}


int main(void)
{ 
  OS_Init();
  
  OS_Create_Task(&mainTask,(OS_STK *)(&Main_Stack.Stack[MAIN_STACK_SIZE - 1]),sizeof(Main_Stack.Stack),"mainTask");
  OS_Start();
}

#endif
