#define STM32_C
#include "Includes.h"

#if QT_EN == 0

void Put_Char(char c)
{
  
}

//��ȡ��ǰʱ��
INT8U Get_Cur_Time(INT8U Time[])//S_Time *pTime)
{
  
}

//���õ�ǰʱ��
INT8U Set_Cur_Time(INT8U Time[])
{
  
}
//�ļ���
//File_Name��ʾ�ļ���
//WR_Flag��ʾ��д��־--���ļ�������ʱ���������ļ�
FILE_T File_Open(char File_Name[], INT8U WR_Flag)
{
  
}

//�ļ���
//File_Name�ļ���
//Offset�ļ�ƫ��
//Len��ȡ����
//����-1��ʾʧ�ܣ�0��ʾ�ļ�������1��ʾ�ɹ�
//FILE_ERR,FILL_END,FILE_OK
INT8S File_Read(FILE_T file, INT32U Offset, INT16U Len, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  
}

//�ļ�д
//File_Name�ļ���
//offsetƫ��
//Bufд����
//д����
//0��ʾʧ�ܣ�>0 ��ʾ�ɹ�
//FILE_ERR,FILE_OK
INT8S File_Write(FILE_T file, INT32U Offset, INT8U Buf[], INT16U Len)
{
  
}

INT8S File_Close(FILE_T file)
{
  
}

//ɾ���ļ�
INT8S File_Delete(char File_Name[])
{
  
}

INT8S File_Size(char File_Name[])
{

}

INT8U Read_PHY_Mem(INT32U Offset, void *pDst, INT16U RD_Len, void *pDst_Start, INT16U DstLen)
{
  return 1;
}

INT8U Write_PHY_Mem(INT32U Offset, void *pSrc, INT16U SrcLen)
{
  return 1;
}

#endif
