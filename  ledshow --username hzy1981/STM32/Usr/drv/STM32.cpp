#define STM32_C
#include "Includes.h"

//���е������������ڴ��ļ��ж���
//������洢��
#ifndef DEF_WR_PHY_MEM
INT8U Read_PHY_Mem(INT32U Offset, void *pDst, INT16U RD_Len, void *pDst_Start, INT16U DstLen)
{
  return 1;
}

//д����洢��
INT8U Write_PHY_Mem(INT32U Offset, void *pSrc, INT16U SrcLen)
{
  return 1;
}
#endif
