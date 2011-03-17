#define OS_SHELL_C
#include "OS_Includes.h"

#if OS_SHELL_EN > 0

#define OS_SHELL_MAX_PARA_NUM 5 //���֧��5���������
//��ڲ�����ʾ�Ƿ��
void OS_Shell_Init(OS_INT8U Bg_Print_Flag)
{
  if(Bg_Print_Flag != 0)
    OS_Shell_Status.Bg_Print_Flag = BG_PRINT_ON; //��̨���̴�ӡ����
  else
    OS_Shell_Status.Bg_Print_Flag = BG_PRINT_OFF;
  
  OS_Shell_Status.Shell_Flag = SHELL_OUT; //��ʼ״̬����Shell��
  OS_Shell_Status.Shell_Task_ID = 0; //shell���е�����ID
  OS_SET_STRUCT_HT(OS_Shell_Status);
}

//��鵱ǰ�Ƿ��ں�̨״̬���У�����1��ʾ�ǣ�0��ʾ����
//�ú����ڲ������п���������ԵĻ���ֱ�ӵ�������ĺ���,�������Ƕ��
OS_INT8U OS_Check_Bg_Status(void)
{
  OS_INT8U Task_ID;
  
  Task_ID = Task_Info.Cur_Task_ID;//OS_Get_Cur_Task_ID();
  
  if(OS_Shell_Status.Shell_Flag EQ SHELL_IN &&\
     OS_Shell_Status.Shell_Task_ID EQ Task_ID)
    return 0;
  else
    return 1;
}

//����̨��ӡ�Ƿ���������0��ʾ�رգ�1��ʾ��
//�ú����ڲ������п���������ԵĻ���ֱ�ӵ�������ĺ���,�������Ƕ��
OS_INT8U OS_Check_Bg_Print_En(void)
{
  if(OS_Shell_Status.Bg_Print_Flag EQ BG_PRINT_OFF)
    return 0;
  else
    return 1;
}

//���ú�̨��ӡ��־��0��ʾ�رպ�̨��ӡ��ֻ����shell�Ĵ�ӡ��1��ʾ�򿪺�̨��ӡ
void OS_Set_Bg_Print_Flag(OS_INT8U Flag)
{
  if(Flag EQ 0)
    OS_Shell_Status.Bg_Print_Flag = BG_PRINT_OFF;
  else
    OS_Shell_Status.Bg_Print_Flag = BG_PRINT_ON;
}

//�������
OS_INT8U OS_Cmd_Analys(CONST S_OS_Shell_Cmd Shell_Cmd[], OS_INT8U Num, OS_INT8S Cmd[], OS_INT8U Len)
{
  OS_INT8U i, j, Re;
  OS_INT8S *(Argv[OS_SHELL_MAX_PARA_NUM]);
  OS_INT8U Argc, Cmd_Len;
  
  Cmd_Len = 0;
  for(i = 0; i < Len; i ++)
  {
    if(Cmd[i] EQ '\r')//�ҵ��س���,˵���Ѿ�������һ����������
    {
      Cmd[i] = '\0';
      Cmd_Len = i; //��¼�����
      break;
    }
    else if(Cmd[i] EQ ' ') //�ո�ȫ���滻��'\0'
      Cmd[i] = '\0';
  }
  
  if(i EQ Len) //û���ҵ�����
    return 0;

  OS_Shell_Status.Shell_Flag = SHELL_IN; //����shell״̬
  OS_Shell_Status.Shell_Task_ID = OS_Get_Cur_Task_ID(); //��ǰ����shell�����ID
  
  if(Cmd_Len EQ 0) //ȫ��������ǿո���߻س�
  {
    OS_Debug_Print("\nOS_Shell:"); //��ʾ�����µ�����
    OS_Shell_Status.Shell_Flag = SHELL_OUT; //�˳�shell״̬
    return 1;
  }
  
  Re = OS_CHECK_STRUCT_HT(OS_Shell_Status); //����״̬��ͷβ��Ϣ
  if(Re EQ 0)
    OS_ASSERT_FAILED();
  
  for(i = 0; i < Num; i ++)
  {
    if(strcmp(Shell_Cmd[i].pName, Cmd) != 0)
      continue;
    
    j = (OS_INT8U)strlen(Cmd);
    Argc = 0;
    while(j < Cmd_Len)
    {
      if(Cmd[j] EQ '\0' && Cmd[j + 1] != '\0') //ǰһ���ǿո񣬺�һ���ǿո�˵����һ���²���
      {
        if(Argc < OS_SHELL_MAX_PARA_NUM)
        {
          Argv[Argc] = &Cmd[j + 1];
          Argc++;
        }
        else
        {
          OS_ASSERT_FAILED();
          break;
        }
      }
      
      j++;
    }

    OS_Debug_Print("\n");    
    (*Shell_Cmd[i].pCmdFunc)(Argc,Argv); 
    OS_Debug_Print("\r\n");    
    break;  
  }
  
  if(i EQ Num)
    OS_Debug_Print("\r\nCmd Error!\r\n");
  
  OS_Debug_Print("\r\nOS_Shell:"); //��ʾ�����µ�����
  OS_Shell_Status.Shell_Flag = SHELL_OUT; //�˳�shell״̬ 
  return 1;
}
#endif

#undef OS_SHELL_C
