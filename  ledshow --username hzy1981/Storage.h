#ifndef STORAGE_H
#define STORAGE_H

#define STORA_DI INT32U

#define NULL_1BYTE  0xFF
#define NULL_2BYTES 0xFFFF
#define NULL_4BYTES 0xFFFFFFFF

#define MEM_WR_NUM 3

typedef struct
{
    INT8U MemID;
    //INT8U Stora_Property;//�洢����,0��ʾ��ʶ�����Զ���ģ�1��ʾ��ʶ����Э�����
    STORA_DI SDI; 
    //������ʶ,��DLT645���ݣ�ͬʱ�����䡣
    //INT8U RW_Flag;
    //������д��־����READ��ʾ�ɶ�����WRITE ��ʾ��д,READ|WRITE��ʾ�ɶ���д
    //INT8U PSW_Flag;
    //��������ȼ���־,PSW_N��ʾ��N���������ϲſ��޸ĸò���(N=0,1,2)
    //INT8U Imp_Flag;
    //��Ҫ�ȼ���־ ��IMP_FACTORY_PARA��ʾ����Ҫ IMP_CUR_DATA->IMP5��Ҫ�����εݼ�
    INT16U Len; //���ݻ��������
    //�ɷ��ǼӶ�д��������������ɼ�ǿIMP��ͬ�Ĳ������ݴ�������
    INT32U Num;
    //�����ڴ���ĸ���
}S_Data_Para_Storage_Info;



//EXT INT8U Check_SuperPSW_Jump();
//EXT INT8U Check_Imp_Flag(INT8U Imp_Flag);
//EXT INT8U Get_Storage_Data_ImpFlag(STORA_DI SDI);
EXT INT32U Get_Storage_Data_Off(STORA_DI SDI);
EXT INT16U Get_Storage_Data_Len(STORA_DI SDI);
//EXT INT32U Get_Imp_Data_Size(INT8U Imp_Flag);
//EXT INT32U Get_Imp_Mem_Size(INT8U Imp_Flag);
//EXT INT8U Read_Imp_Data(INT8U Imp_Flag, INT32U Offset, void* pDst, INT16U RD_Len, void* pDst_Start, INT16U DstLen);
//EXT INT8U Write_Imp_Data(INT8U Imp_Flag, INT32U Offset, void* pSrc, INT16U SrcLen);

EXT INT16U Read_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, INT16U Len, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT8U Write_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, void* pSrc, INT16U SrcLen);

EXT INT16U Read_Storage_Data(STORA_DI SDI, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT8U Write_Storage_Data(STORA_DI SDI, void* pSrc, INT16U SrcLen);

EXT INT16U Read_Multi_Storage_Data(STORA_DI SDI, INT16U Num, void *pDst, void *pDst_Start, INT16U DstLen);

#endif
