#include "Includes.h"

int main(void)
{ 
  Hardware_Init();

  Para_Init(); //������ʼ��

  Com_Init(); //��ʼ������

#if UDISK_EN  
  UDisk_Init(); //U�̳�ʼ��
#endif

#if NET_EN
  Net_Init(); //�����ʼ��
#endif

  Self_Test(); //�Լ����
  
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
