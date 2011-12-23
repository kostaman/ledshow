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
  INT16U i = 0;
  static INT8U Min = 0xFF;

  if(CHK_HT(Main_Stack) EQ 0)
  {
    ASSERT_FAILED();
  }

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

}

int main(void)
{
  __set_MSP((INT32U)(&Main_Stack.Stack[MAIN_STACK_SIZE - 1])); //�޸�Ϊ�˹���ջ��ʽ

  Ram_Init();
  Hardware_Init();



  RST_Periph();

  Para_Init(); //������ʼ��

  Com_Init(); //��ʼ������

#if UDISK_EN  
  UDisk_Init(); //U�̳�ʼ��
#endif

#if NET_EN
  Net_Init(); //�����ʼ��
#endif

  DS1302_Init(); //������1s�ٳ�ʼ��DS1302���ֲ�Ҫ��

  //Fac_Status_Self_Test(); //�Լ����
  
  Para_Show(); //�ϵ������ʾ

  SET_STATUS_LED_ON(); //��LED״̬��

  while(1)
  {
    Screen_Test(); //��Ļ���

	Self_Test(); //Ӳ���Լ�

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
  }
  
}
