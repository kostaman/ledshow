#include "Includes.h"

int main(void)
{ 
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

  Fac_Status_Self_Test(); //�Լ����
  
  Para_Show(); //�ϵ������ʾ

  while(1)
  {
#if SHELL_EN
    Shell_Proc();
#endif

    Show_Main_Proc();

#if UDISK_EN
    UDisk_Proc(); //u�̴���
#endif
#if NET_EN
	Net_Proc();
#endif
  }
  
}
