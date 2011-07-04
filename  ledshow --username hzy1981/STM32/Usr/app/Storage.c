#define STORAGE_C
#include "includes.h"
/*
typedef struct
{
  INT8U Head;
  INT8U Prog_No; //��Ŀ��
  
  INT8U Mode; //���ŷ�ʽ��0��ʾѭ�����ţ�1��ʾ��������
  INT16U Counts; //ѭ������
  INT32U Time; //ͣ������
  
  S_Program_Timing Timing[3];//[3]; //��Ŀ��ʱ����
  INT8U Area_Num; //������
  INT8U Main_Area_No; //��������
  INT8U Area_File_Num[MAX_AREA_NUM]; //ÿ�����ļ���
  S_Area Area[MAX_AREA_NUM]; //������
  
  INT8U Border_Check; //�Ƿ���ʾ�߿�
  INT16U Border_StayTime;
  //INT8U Border_Speed; //�߿������ٶ�
  INT8U Border_Mode;  //�߿�ģʽ
  INT8U Border_Width;   //�߿���
  INT8U Border_Height;  //�߿�߶�
  INT8U Temp;   //����
//#if BORDER_SHOW_EN > 0  
  INT8U Border_Data[3*MAX_BORDER_POINTS/8]; //�߿�����
//#endif  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Prog_Para;
*/

const S_Data_Para_Storage_Info Data_Para_Storage[] =
{
  //��Ļ�����Լ�����
  {SDI_SCREEN_PARA, SCREEN_PARA_LEN, 1},
#ifdef SDI_SCREEN_PARA_BK0 
  {SDI_SCREEN_PARA_BK0, SCREEN_PARA_LEN, 1},
#endif  
#ifdef SDI_SCREEN_PARA_BK1
  {SDI_SCREEN_PARA_BK1, SCREEN_PARA_LEN, 1},
#endif
#ifdef SDI_SCREEN_PARA_BK2
  {SDI_SCREEN_PARA_BK2, SCREEN_PARA_LEN, 1},  
#endif

  //��Ŀ����������
  {SDI_PROG_PARA, PROG_PARA_LEN, MAX_PROG_NUM},
#ifdef  SDI_PROG_PARA_BK0
  {SDI_PROG_PARA_BK0, PROG_PARA_LEN, MAX_PROG_NUM},
#endif
#ifdef SDI_PROG_PARA_BK1
  {SDI_PROG_PARA_BK1, PROG_PARA_LEN, MAX_PROG_NUM},
#endif  

 //�ļ�����������
  {SDI_FILE_PARA, FILE_PARA_LEN, MAX_PROG_NUM * MAX_AREA_NUM * MAX_FILE_NUM},
#ifdef  SDI_FILE_PARA_BK0
  {SDI_FILE_PARA_BK0,  FILE_PARA_LEN, MAX_PROG_NUM * MAX_AREA_NUM * MAX_FILE_NUM},
#endif  

 //��Ŀ��ʾ���ݵĴ洢����
  {SDI_PROG_BLOCK_INDEX, BLOCK_INDEX_LEN, MAX_PROG_NUM}, 
#ifdef SDI_PROG_BLOCK_INDEX_BK0  
  {SDI_PROG_BLOCK_INDEX_BK0, BLOCK_INDEX_LEN, MAX_PROG_NUM}, 
#endif  
#ifdef SDI_PROG_BLOCK_INDEX_BK1  
  {SDI_PROG_BLOCK_INDEX_BK1, BLOCK_INDEX_LEN, MAX_PROG_NUM}, 
#endif  

  {SDI_CUR_BLOCK_INDEX, sizeof(S_Cur_Block_Index), 1},
#ifdef SDI_CUR_BLOCK_INDEX_BK0  
  {SDI_CUR_BLOCK_INDEX_BK0, sizeof(S_Cur_Block_Index), 1},
#endif
#ifdef SDI_CUR_BLOCK_INDEX_BK1
  {SDI_CUR_BLOCK_INDEX_BK1, sizeof(S_Cur_Block_Index), 1},
#endif                                   
                                   
  //��Ŀ��ʾ����
  {SDI_SHOW_DATA, BLOCK_DATA_LEN, MAX_BLOCK_NUM},

  {SDI_TEST_DATA, TEST_DATA_LEN, 1}
};

//�Ӵ洢���ж�ȡĳ����Ҫ�ȼ�������
//Imp_Flag����ʾ���ݵ���Ҫ�ȼ���־
//Offset, ��ʾ�����ڴ洢���е�ƫ��
//pDst����ʾ���ݶ�ȡ���Ŀ��ָ��
//RD_Len����ʾ��Ҫ��ȡ�����ݵĳ���
//pDst_Start��DstLenyһ���pDst��RD_Len�ķ�Χ����Լ��
//����1��ʾ�ɹ�
INT8U Read_Data_Width_CS(INT32U Offset, void* pDst, INT16U RD_Len, void* pDst_Start, INT16U DstLen)
{
  //INT16U i;//, j;
  INT32U Sum;
  INT8U Re;

  TRACE();

  //�����߼��洢���е�����

      Re = Read_PHY_Mem(Offset, pDst, RD_Len, pDst_Start, DstLen);
      if(1!=Re)//ASSERT(1 EQ Re)) //ȷ��������ȷ
      {
        ASSERT_FAILED();
        return 0;
      }

      //��У���
      Re = Read_PHY_Mem(Offset + RD_Len, &Sum, ROM_CS_BYTES, &Sum, sizeof(Sum));
      if(1!=Re)//ASSERT(1 EQ Re))
      {
        ASSERT_FAILED();
        return 0;
      }
      //���У����Ƿ���ȷ
      if(Check_Sum(pDst, RD_Len, &Sum, ROM_CS_BYTES))//У�����ȷ��ֱ�ӷ���1�����������ȡ�¸�LOG_MEM
        return 1;
      else
        return 0;
  //ASSERT_FAILED();
  //return 0;
}

//��ĳ����Ҫ��־������д�뵽�洢����
//Imp_Flag����ʾ���ݵ���Ҫ�ȼ���־
//Offset, ��ʾ�����ڴ洢���е�ƫ��
//pSrc����ʾ���ݵ���ʼָ��
//SrcLen����ʾ���ݵĳ���
//����1��ʾд�ɹ�
//����WR_IMP_DATA_ERR��ʾд����ʧ��
INT8U Write_Data_With_CS(INT32U Offset, void* pSrc, INT16U SrcLen)
{
  //INT8U i;
  INT8U Re;
  INT32U Sum;

  TRACE();

    Set_Sum(pSrc, SrcLen, &Sum, ROM_CS_BYTES, &Sum, sizeof(Sum)); //����У���

    Re = Write_PHY_Mem(Offset, pSrc, SrcLen); //д����
    if(0 EQ Re)
    {
      ASSERT_FAILED();
      return 0;
    }

    Re = Write_PHY_Mem(Offset + SrcLen, &Sum, ROM_CS_BYTES); //дУ���
    if(0 EQ Re)
    {
      ASSERT_FAILED();
      return 0;
    }
    
    return 1;
}

//��ȡĳ���洢��������Ĵ洢ƫ�ƣ���ƫ�Ʊ�ʾ����������ͬImp_Flag�����еĴ洢Ʒƫ��
//Ҳ��ʾ���߼��洢���е�����ƫ��
INT32U Get_Storage_Data_Off(STORA_DI SDI)
{
  INT16U i; 
  INT32U Offset = 0; 
  //INT8U Re;

  for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
  {
    if(Data_Para_Storage[i].SDI EQ SDI)
    {
      return Offset;
    }
    else if(Data_Para_Storage[i].Num > 1 && Data_Para_Storage[i].SDI < SDI && SDI < Data_Para_Storage[i].SDI + Data_Para_Storage[i].Num)
    {
      Offset += (Data_Para_Storage[i].Len + ROM_CS_BYTES) * (SDI - Data_Para_Storage[i].SDI); 
      return Offset;
    }
    else
    {
      Offset += (Data_Para_Storage[i].Len + ROM_CS_BYTES) * Data_Para_Storage[i].Num;
    }
  }

  debug("get_storage_data_off error, data 0x%x not found\r\n", SDI);
  return NULL_4BYTES;
}

//��ȡĳ���洢��������ĳ���, DIֻ����Data_Para_Storage�ж��������
INT16U Get_Storage_Data_Len(STORA_DI SDI)
{
  INT16U i; 

  TRACE();

  for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
  {
    if((Data_Para_Storage[i].Num > 0 && Data_Para_Storage[i].SDI EQ SDI) || \
       (Data_Para_Storage[i].Num > 1 && \
	  Data_Para_Storage[i].SDI < SDI && \
	  Data_Para_Storage[i].SDI + Data_Para_Storage[i].Num> SDI))
    {
      return Data_Para_Storage[i].Len;
    }
  }
  debug("get_storage_data_len err, SDI = 0x%x",SDI);
  ASSERT_FAILED(); 
  return 0;
}

//��ȡĳ��SDI�ڵ����ݣ�������CSУ��
INT16U Read_Storage_Data_NoCS(STORA_DI SDI, INT16U Offset, INT16U Len, void* pDst, void* pDst_Start, INT16U DstLen)
{
    INT32U Off;
    INT8U Re;

    TRACE();

    Unselect_SPI_Device();
    ReInit_Mem_Port();//���³�ʼ���˿�

    Off = Get_Storage_Data_Off(SDI); //��ȡ����ƫ��
    if(NULL_4BYTES EQ Off)//ASSERT(NULL_4BYTES != Off))
    {
      ASSERT_FAILED();
      //*pErr = RD_STORAGE_DATA_DI_ERR;
      return 0;
    }

    debug("read data:ID = 0x%x, Addr = %d, Off = %d, Len = %d", SDI, Off, Offset, Len);

    Off += Offset; // + �ڲ�ƫ��

    //OS_Mutex_Pend(PUB_RW_ROM_ID); //����дROM���ź���ID
    //if(Check_Power_Status() EQ POWER_ON_STATUS)
    Re = Read_PHY_Mem(Off, pDst, Len, pDst_Start, DstLen);

    if(Re > 0)
        return Len;
    else
        return 0;

}

//��ȡ�洢���е�ĳ�����ݵĹ̶����ȣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI, ��Ҫ��ȡ���������ʶ
//Offset, ��ȡDI���ݵ���ʼƫ��
//Len, ��Ҫ��ȡ�����ݳ���
//pDst��ʾ��ȡ������ŵ��û�����
//pDst_Start��DstLenһ��綨Ŀ�껺�����ķ�Χ
//*pErr��ʾ��ȡʧ��ʱ��ԭ��, 1��ʾ��ȡ�ɹ�, ��������ԭ��μ�Pub_Err.h
//����ֵ����ȡ�����ݳ���, ��ȡʧ��ʱ����0
INT16U Read_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, INT16U Len, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT32U Off; 
  INT8U Re; 

  TRACE();

  Unselect_SPI_Device();
  ReInit_Mem_Port();//���³�ʼ���˿�

  Off = Get_Storage_Data_Off(SDI); //��ȡ����ƫ��
  if(NULL_4BYTES EQ Off)//ASSERT(NULL_4BYTES != Off))
  {
    ASSERT_FAILED();
    //*pErr = RD_STORAGE_DATA_DI_ERR; 
    return 0;
  }

  debug("read data:ID = 0x%x, Addr = %d, Off = %d, Len = %d", SDI, Off, Offset, Len);

  Off += Offset; // + �ڲ�ƫ��

  //OS_Mutex_Pend(PUB_RW_ROM_ID); //����дROM���ź���ID
  //if(Check_Power_Status() EQ POWER_ON_STATUS)
  Re = Read_Data_Width_CS(Off, pDst, Len, pDst_Start, DstLen);
  //else
  //*pErr = PD_Read_Imp_Data(Imp_Flag, Off, pDst, Len, pDst_Start, DstLen); 
  //OS_Mutex_Post(PUB_RW_ROM_ID); //�ͷ�дROM���ź���ID
  if(1 EQ Re)
  {
    return Len;
  }
  else//���洢ʧ�����ȡĬ�ϲ���
  {
    //*pErr = RD_FIX_DATA_ERR; 
    return 0;
  }
  //return 0;   

}

//д�洢���е�ĳ�����ݵĹ̶����ȣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI, ��Ҫд���������ʶ
//Offset, дDI���ݵ���ʼƫ��
//SrcLen, ��Ҫд�����ݳ���
//pSrc��ʾд��Դ���ݻ�����
//SrcLen��ʾԴ���ݵĳ���
//����1��ʾ�ɹ���������ʾʧ��
INT8U Write_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, void* pSrc, INT16U SrcLen)
{
  INT32U Off; 
  INT8U Re; 

  TRACE();

  Unselect_SPI_Device();
  ReInit_Mem_Port();//���³�ʼ���˿�

  Off = Get_Storage_Data_Off(SDI); //��ȡ����ƫ��
  if(NULL_4BYTES EQ Off)
  {
    ASSERT_FAILED();
    return 0;
  }

  debug("write data:ID = 0x%x, Addr = %d, Off = %d, Len = %d", SDI, Off, Offset, SrcLen);

  Off += Offset; // + �ڲ�ƫ��
  //OS_Mutex_Pend(PUB_RW_ROM_ID);
  //if(Check_Power_Status() EQ POWER_ON_STATUS)
  Re = Write_Data_With_CS(Off, pSrc, SrcLen);
  //else
  //Re = PD_Write_Imp_Data(Imp_Flag, Off, pSrc, SrcLen);     
  //OS_Mutex_Post(PUB_RW_ROM_ID);

  //OS_TimeDly_Ms(20); //��ʱ20ms

  if(1 EQ Re)
  {
    return 1;
  }
  else//���洢ʧ�����ȡĬ�ϲ���
  {
    return 0;
  }
}


//��ȡ�洢���е�ĳ�����ݣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI, ��Ҫ��ȡ���������ʶ
//pPara���ڶ�ȡĳЩ����������ʱ��Ҫ�Ĳ���������HIS_ENERGY, HIS_DEMAND, HIS_DEMAND_TIMEʱ��Ҫ����ʱ�����
//ʱ������ĸ�ʽ��������pPara[0]-pPara[4]�ֱ��Ƿ֡�ʱ���ա��¡���, ��������¸ò���������
//pDst��ʾ��ȡ������ŵ��û�����
//pDst_Start��DstLenһ��綨Ŀ�껺�����ķ�Χ
//*pErr��ʾ��ȡʧ��ʱ��ԭ��, 1��ʾ��ȡ�ɹ�, ��������ԭ��μ�Pub_Err.h
//����ֵ����ȡ�����ݳ���, ��ȡʧ��ʱ����0
INT16U Read_Storage_Data(STORA_DI SDI, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len, Len1; 

  TRACE();

  //Clear_CPU_Dog();     //��CPU�ڲ����Ź�
  //Clear_Ext_Dog();     //��CPU�ⲿ���Ź�
  //Cur_Task_ID = Get_Cur_Task_ID(); 
  //debug("Read Storage Data:0x%x", DI, Tcb[Cur_Task_ID].Name);
  Len = Get_Storage_Data_Len(SDI); 
  if(Len > 0)
  {
    //OS_TimeDly_Ms(20); //��ʱ���������񣬷�ֹĳ�����������������ռ��CPU
    Len1 = Read_Storage_Data_Fix_Len(SDI, 0, Len, pDst, pDst_Start, DstLen); 
    if(Len != Len1)
    {
      return 0;
    }
    else
      return Len;
  }
  else
  {
    ASSERT_FAILED(); 
    return 0;
  }
}

//��ȡ����DI�Ķ����洢����
INT16U Read_Multi_Storage_Data(STORA_DI SDI, INT16U Num, void *pDst, void *pDst_Start, INT16U DstLen)
{
  INT16U i;
  INT16U Len;
  
  Len = 0;
  for(i = 0; i < Num; i ++)
  {
    Len += Read_Storage_Data(SDI + i, (INT8U *)pDst + Len, (INT8U *)pDst_Start, DstLen); 
  }
  
  return Len;
}

//��洢����дĳ�����ݣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI, ��Ҫд���������ʶ
//pPara����дĳЩ����������ʱ��Ҫ�Ĳ���������HIS_ENERGY, HIS_DEMAND, HIS_DEMAND_TIMEʱ��Ҫ����ʱ�����
//ʱ������ĸ�ʽ��������pPara[0]-pPara[4]�ֱ��Ƿ֡�ʱ���ա��¡���, ��������¸ò���������
//pSrc��ʾд���ݵ�Դ������
//����ֵ��1��ʾ�ɹ���������ʾʧ��
INT8U Write_Storage_Data(STORA_DI SDI, void* pSrc, INT16U SrcLen)
{
  INT16U Len; 
  INT8U Re; 

  TRACE();

  //Unselect_SPI_Device();
  //Cur_Task_ID = Get_Cur_Task_ID(); 
  //debug("Write Storage Data:0x%x", DI, Tcb[Cur_Task_ID].Name);
  //��ȡ���Ƚ����ݳ���
  Len = Get_Storage_Data_Len(SDI); 
  if(Len != SrcLen)//ASSERT(Len EQ SrcLen))
  {
    ASSERT_FAILED();
    debug("wr_len err, SDI = 0x%x len = %d, srclen = %d", SDI, Len, SrcLen);
    return 0;
  } 

  //дImp����
  //OS_Mutex_Pend(PUB_RW_ROM_ID); //����дROM���ź���ID
  Re = Write_Storage_Data_Fix_Len(SDI, 0, pSrc, SrcLen); 
  //OS_Mutex_Post(PUB_RW_ROM_ID); //�ͷŸ��ź���
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    return 0;
  } 
  return 1;
}


#undef STORAGE_C

