#include "Includes.h"

#define MAIN_STACK_SIZE 300
 
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
}S_Stack;


S_Stack Main_Stack = {CHK_BYTE, {0}, 0, CHK_BYTE};

//���ϵͳ��ջʣ�����
void Chk_Main_Stack(void)
{
#if CLOCK_EN
  INT16U i = 0;
  static INT8U Min = 0xFF;

  //ÿ���Ӵ�ӡһ�ζ�ջ��С
  if(Min != Cur_Time.Time[T_MIN])
  {
    Min = Cur_Time.Time[T_MIN]; 
	  
	while(Main_Stack.Stack[i] EQ 0)
	{ 
	i ++;
	}
	
	Main_Stack.Left = i*4;

    debug("stack left %d", Main_Stack.Left);
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

int main(void)
{
  __set_MSP((INT32U)(&Main_Stack.Stack[MAIN_STACK_SIZE - 1])); //�޸�Ϊ�˹���ջ��ʽ

  Ram_Init();

#if WDG_EN
  IWDG_Init();
#endif

  Hardware_Init();

  OS_Debug_Print("----------system start----------");
  OS_Debug_Print("----------version: %s----------", version);

  Check_Storage_Size();
  
  RST_Periph();

  Para_Init(); //������ʼ��

  Com_Init(); //��ʼ������

#if UDISK_EN  
  UDisk_Init(); //U�̳�ʼ��
#endif

#if NET_EN
  Net_Init(); //�����ʼ��
#endif

#if CLOCK_EN
  DS1302_Init(); //������1s�ٳ�ʼ��DS1302���ֲ�Ҫ��
#endif
  //Fac_Status_Self_Test(); //�Լ����
  
  Para_Show(); //�ϵ������ʾ

  SET_STATUS_LED_ON(); //��LED״̬��


  while(1)
  {
    Screen_Test(); //��Ļ���

	Fac_Status_Self_Test(); //Ӳ���Լ�

#if SHELL_EN
    Shell_Proc();
#endif
	
#if UDISK_EN
    UDisk_Proc(); //u�̴���
#endif

    Show_Main_Proc();


#if NET_EN
	Net_Proc();
#endif

    Chk_Main_Stack();

    Clr_Watch_Dog();
  }
  
}
