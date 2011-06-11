#define SHELL_C
#include "Includes.h"

//#define MAX_RD_MEM_LEN 300
//#define MAX_CMD_LEN  50

//#define SHELL_DATA_BUF_LEN 100  

//��ȡ����洢������
//extern INT8U Read_PHY_Mem_Drv(INT8U MemNo,INT32U Offset,INT8U *pDst,INT16U RD_Len, INT8U *pDst_Start, INT16U DstLen);

CONST S_OS_Shell_Cmd Shell_Cmd[] =
{
  {/*.pName = */"echo", /*.pCmdFunc = */&Shell_Bg_Print_Switch},
  {/*.pName = */"ps", /*.pCmdFunc = */&Shell_Print_Prog_Status},
  {/*.pName = */"ss", /*.pCmdFunc = */&Shell_Print_Screen_Status},
  //{.pName = "mem", .pCmdFunc = &Shell_Read_Mem},
  //{.pName = "osinfo", .pCmdFunc = &Shell_OS_Info}
};

//��̨��ӡ����echo 0��ʾ�غ�̨��ӡ,echo 1��ʾ�򿪺�̨��ӡ��echo ?��ʾ��̨��ӡ����״̬
INT8U Shell_Bg_Print_Switch(INT8U argc, INT8S **argv)
{
  if(*(argv[0]) EQ '0')
     OS_Set_Bg_Print_Flag(0);
  else if(*(argv[0]) EQ '1')
     OS_Set_Bg_Print_Flag(1);
  else if(*(argv[0]) EQ '?')
  {
    debug("echo status %s",\
      (OS_Check_Bg_Print_En() > 0)?"On":"Off"); 
  }
  else
  {
    debug("Cmd format error!"); 
  }
  return 1;
}
/*
//��ӡ����ϵͳ��Ϣ
INT8U Shell_OS_Info(INT8U argc, INT8S **argv)
{
  OS_Info_Print();
  return 1;
}
*/
//��ӡ����
/*
void Shell_Print_Data(INT32U Addr, INT8U *p, INT16U Len)
{
  INT16U i;
  
  for(i = 0; i < Len && i < MAX_RD_MEM_LEN; i ++)
  {
    if((i % 16) EQ 0)
      OS_Debug_Print("\r\n%8lx:", Addr + i);
    
    if(*p < 0x10)
      OS_Debug_Print("0");
    OS_Debug_Print("%x ",*p);
    p ++;
  }  
  
}

//ͨ��shell��ȡ�ڴ��rom����,argv[0]��ʾ�ڴ�ID��0��ʾram��0���ϱ�ʾrom
//argv[1]��ʾ��ַ
//argv[2]��ʾ����
INT8U Shell_Read_Mem(INT8U argc, INT8S **argv)
{
  INT32U Mem_No, Addr, Len;
  INT8U *p, Re;
  
  if(argc != 3)
  {
    OS_Debug_Print("Cmd format error!");
    return 0;
  }
  
  Mem_No = atoi(argv[0]);
  Addr = atol(argv[1]);
  Len = atol(argv[2]);
  
  OS_Debug_Print("\r\nMem_No:%lu, Addr:%lu, Len:%lu\r\n", Mem_No, Addr, Len);

  if(Len > MAX_RD_MEM_LEN)
    Len = MAX_RD_MEM_LEN;
    
  if(Mem_No EQ 0)
    p = (INT8U *)Addr;
  else
  {
    Re = Read_PHY_Mem_Drv(Mem_No - 1, Addr, (INT8U *)Shell_Data_Buf, Len, (INT8U *)Shell_Data_Buf, SHELL_DATA_BUF_LEN);
    if(Re EQ 0)
      Len = 0;
    
    p = (INT8U *)Shell_Data_Buf;
  }
  
  Shell_Print_Data(Addr, p, Len);
  
  return 1;
}
*/
/*
//�����Ŀ״̬
typedef struct
{
  INT8U Head;
  
  INT8U Prog_No; //��ǰ��Ŀ��
  INT32U Time; //�Ѿ�����ʱ��
  INT16U Counts; //�Ѿ����Ŵ���

  INT8U Play_Flag; //�Ƿ񲥷ű�־--��Ҫ�������ж���ʾͬ��
  
  S_Border_Status Border_Status;
  U_File_Para File_Para[MAX_AREA_NUM]; //ÿ�������ĵ�ǰ�ļ�����
  S_Area_Status Area_Status[MAX_AREA_NUM]; //ÿ��������״̬ 
  S_Prog_Block_Index Block_Index; //��ǰ��Ŀ������

  INT8U CS[CS_BYTES];
  INT8U Tail;
}S_Prog_Status;

typedef struct
{
  INT8U Head;
  INT8U Lightness;
  INT8U Open_Flag;
  INT8U CS[CS_BYTES];
  INT8U Tail;  
}S_Screen_Status;
*/
INT8U Shell_Print_Screen_Status(INT8U argc, INT8S **argv)
{
 
  debug("screen status, lightness = %d, oc_flag = %d",\
        Screen_Status.Lightness, Screen_Status.Open_Flag);
  
  return 1;
}
/*
  INT8U Flag; //��־
  INT8U Prog_No; //��Ŀ��
  INT8U Area_No; //������
  INT8U File_No; //�ļ���
  INT8U In_Mode; //���뷽ʽ
  INT8U In_Speed; //�����ٶ�
  INT8U Add_Mode; //׷�ӷ�ʽ
  INT16U Stay_Time; //ͣ��ʱ�䣬���λΪ��λ��0��ʾs��1��ʾms
  INT8U Out_Mode; //������ʽ	
  INT8U Color; //��ɫ
  INT16U SNum; //��������
*/
INT8U Shell_Print_Prog_Status(INT8U argc, INT8S **argv)
{
  INT8U i;
  
  debug("cur prog %d, play time = %d, counts = %d, play_flag = %d",\
         Prog_Status.Play_Status.Prog_No, Prog_Status.Play_Status.Time, Prog_Status.Play_Status.Counts);
  
  debug("prog border step = %d, timer = %d", \
         Prog_Status.Border_Status[0].Step, Prog_Status.Border_Status[0].Timer);
  
  debug("area num = %d", Prog_Para.Area_Num);

  for(i = 0; i < Prog_Para.Area_Num; i ++)
  {
    debug("area_no = %d, file para:", i);
    debug("flag = %d, prog_no = %d, area_no = %d, file_no = %d", \
          Prog_Status.File_Para[i].Pic_Para.Flag,\
          Prog_Status.File_Para[i].Pic_Para.Prog_No,\
          Prog_Status.File_Para[i].Pic_Para.Area_No,\
          Prog_Status.File_Para[i].Pic_Para.File_No);
    debug("in_mode = %d, In_Speed = %d, add_mode = %d, stay_time = %d, out_mode = %d, Out_Speed = %d, snum = %d",
          Prog_Status.File_Para[i].Pic_Para.In_Mode,\
          Prog_Status.File_Para[i].Pic_Para.In_Speed,\
          Prog_Status.File_Para[i].Pic_Para.Add_Mode,\
          Prog_Status.File_Para[i].Pic_Para.Stay_Time,\
          Prog_Status.File_Para[i].Pic_Para.Out_Mode,\
          Prog_Status.File_Para[i].Pic_Para.Out_Speed,\
          Prog_Status.File_Para[i].Pic_Para.SNum);  
  }
  
  return 1;
}

void Shell_Rcv_Byte(INT8U Byte)
{
  if(_Shell_Cmd_Buf.Posi >= SHELL_CMD_BUF_LEN)
    _Shell_Cmd_Buf.Posi = 0;

  _Shell_Cmd_Buf.Buf[_Shell_Cmd_Buf.Posi] = Byte;
}

void Shell_Proc(void)
{
  INT8U Re;
  
  Re = OS_Cmd_Analys(Shell_Cmd, S_NUM(Shell_Cmd), (INT8S *)Shell_Cmd_Buf, SHELL_CMD_BUF_LEN);
  if(Re EQ 1)
  {
    _Shell_Cmd_Buf.Posi = 0;
    mem_set((INT8S *)Shell_Cmd_Buf, 0, SHELL_CMD_BUF_LEN, (INT8S *)Shell_Cmd_Buf, SHELL_CMD_BUF_LEN);
  }
}
#undef APP_SHELL_C
