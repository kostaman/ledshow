#include "Includes.h"

int main(void)
{ 
  Hardware_Init();

#if UDISK_EN  
  UDisk_Init();
#endif

#if NET_EN
  Net_Init();
#endif
  Self_Test(); //�Լ����
  
  while(1)
  {
    Shell_Proc();
    Show_Main_Proc();

#if UDISK_EN
    UDisk_Proc(); //u�̴���
#endif
#if NET_EN
	Net_Proc();
#endif
  }
  
}
