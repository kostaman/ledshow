#define LED_PARA_C
#include "Includes.h"
/*
//�û������ļ���С����
const S_File_Para_Info Usr_Para_File_Info[] =
{
  //{C_SCREEN_WH, 0}  0x01
  {C_SCREEN_ADDR, 1 + 11},//0x02
  {C_SCREEN_IP,   4 + 11}, //0x03
  {C_SCREEN_BAUD, 1 + 11}, //0x04
  {C_SCREEN_OC_TIME, 16 + 11},//0x05 //��ʱ���ػ�ʱ��
  {C_SCREEN_LIGNTNESS, 8 + 11},//0x06 //����
  //{C_SCREEN_TIME, 0x07}, //ʱ��
  
};

//���������ļ���С����
const S_File_Para_Info Fac_Para_File_Info[] =
{
  {C_SCREEN_WH, 5 + 11},//0x02
  
};
*/
/*
�ļ����֣�
fac_para.cfg //��������--����ǰ����
��Ļ��С
user_para.cfg //�û�����--�û����Լ�����
��ַ
IP��ַ
������
���ػ�ʱ��
����
��Ŀ��

prog_property00.cfg //��Ŀ0����
...
prog_propertyAA.cfg //��ĿN����

show-00-00-00.dat //�ļ�������: show-��Ŀ��-������-�ļ���
......
show-AA-BB-CC.dat    

fac_para�ļ���ʽ:
cmd=01 ����������ɫ֡

use_para.cfg �ļ���ʽ
cmd=0x02 ����ַ���ɶ���д
cmd=0x03 ��IP�������ɶ���д
cmd=0x04 ͨ�����ʣ��ɶ���д
cmd=0x05 ��ʱ���ػ����ɶ���д
cmd=0x07 �������ã��ɶ���д
cmd=0x08 ��Ŀ��
prog_property00.cfg �ļ���ʽ

*/
/*
//��ȡ��Ŀ����
//��ȡ��ʾ�����ļ���
char * Get_Program_Data_File_Name(INT8U Prog_No, INT8U Area_No, char File_Name[])
{
  INT8U i;
  
  strcpy(File_Name, "show-");
  i = 5;
  
  File_Name[i++] = '0' + Prog_No / 10;
  File_Name[i++] = '0' + Prog_No % 10;
  
  File_Name[i++] = '-';
  File_Name[i++] = '0' + Area_No / 10;
  File_Name[i++] = '0' + Area_No % 10;
 
  File_Name[i] = '\0';
  strcat(File_Name, ".dat");
  
  return File_Name;
}

//��ȡ��Ŀ�����ļ���
char * Get_Program_Property_File_Name(INT8U Prog_No, char File_Name[])
{
  INT8U i;
  
  strcpy(File_Name, "program_property-");
  i = 17;
  
  File_Name[i++] = '0' + Prog_No / 10;
  File_Name[i++] = '0' + Prog_No % 10;
  File_Name[i] = '\0';
  strcat(File_Name, ".pro");
  
  return File_Name;
}

//��ȡ���������ļ���
char * Get_Fac_Para_File_Name(char File_Name[])
{
  strcpy(File_Name, "fac_para.cfg");  
  return File_Name;
}

//��ȡ�û������ļ���
char * Get_Usr_Para_File_Name(char File_Name[])
{
  strcpy(File_Name, "usr_para.cfg");
  return File_Name;
}



//���ļ��ж�ȡһ֡
//Offset ƫ��
//pDst Ŀ�껺����
//����-1��ȡ����,�޷�������0��ʾ�ļ�������β��>0������֡��
INT32S File_Read_One_Frame(FILE_T File, INT32U Offset, INT8U *pSeq, INT16U *pCtrl, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  INT8S Re;
  //INT8U Temp[10];
  INT16U Len;
  
  //��ȡOffsetƫ�ƴ���һ֡
  Re = File_Read(File, Offset, 4, pDst, pDst_Start, DstLen); //sizeof(Temp), Temp, Temp, sizeof(Temp));
  if(Re <= 0)
    return Re;
  
  //֡ͷ�Ƿ���ȷ
  if(!(pDst[0] EQ FRAME_HEAD0 && pDst[1] EQ FRAME_HEAD1))
  {
    ASSERT_FAILED();
    return FILE_FRAME_ERR;
  }
  
  Len = pDst[2] + (INT16U)pDst[3] * 256; //֡��
  Re = File_Read(File, Offset + 4, Len - 4, pDst + 4, pDst_Start, DstLen);
  if(Re <= 0)
    return Re;
  
  if(Check_Frame_Format(pDst, Len) EQ 0)//֡��ʽ�Ƿ���ȷ
  {
    ASSERT_FAILED();
    return FILE_FRAME_ERR;
  }
  else
    return Len;
}



//��ȡĳһ����֡�ڲ����ļ��еĴ洢λ�ú�ƫ���Լ��洢���ĸ��ļ���
INT8U Get_Para_Frame_File_Off_Size(INT16U Ctrl_Code, char File_Name[], INT16U *pOffset, INT16U *pLen)
{
  INT8U i;
  INT16U Off = 0;//Len = 0;
  
  if(Ctrl_Code EQ C_SCREEN_WH) //��Ļ���
  {
    for(i = 0; i < S_NUM(Fac_Para_File_Info); i ++)
    {
      if(Ctrl_Code EQ Fac_Para_File_Info[i].Ctrl_Code)
      {
        *pOffset = Off;
        *pLen = Fac_Para_File_Info[i].Len;
        Get_Fac_Para_File_Name(File_Name);
        return 1;
      }
      else
        Off += Fac_Para_File_Info[i].Len;
    }
  }
  else //�����������洢���û������ļ�
  {
    for(i = 0; i < S_NUM(Usr_Para_File_Info); i ++)
    {
      if(Ctrl_Code EQ Usr_Para_File_Info[i].Ctrl_Code)
      {
        *pOffset = Off;
        *pLen = Usr_Para_File_Info[i].Len;
        Get_Usr_Para_File_Name(File_Name);
        return 1;
      }
      else
        Off += Usr_Para_File_Info[i].Len;
    }    
  }
  
  return 0;
}
*/

INT8U Get_Show_Para_Len(INT8U Type)
{
  if(Type EQ SHOW_PIC)
    return sizeof(S_Pic_Para) - CHK_BYTE_LEN;
  else if(Type EQ SHOW_CLOCK)
    return sizeof(S_Clock_Para) - CHK_BYTE_LEN;
  else if(Type EQ SHOW_TIME)
    return sizeof(S_Time_Para) - CHK_BYTE_LEN;
  else if(Type EQ SHOW_TIMER)
    return sizeof(S_Timer_Para) - CHK_BYTE_LEN;
  else if(Type EQ SHOW_TEMP)
    return sizeof(S_Temp_Para) - CHK_BYTE_LEN;
  else if(Type EQ SHOW_LUN)
    return sizeof(S_Lun_Para) - CHK_BYTE_LEN;
  else
  {
    ASSERT_FAILED();
    return 0;
  }
  
}

//�������֡����
INT8U Save_Para_Frame_Proc(INT8U Frame[], INT16U FrameLen)
{
  //INT8U Prog_No = Prog_Para.Prog_No;
  Write_Storage_Data(SDI_SCREEN_PARA , (INT8U *)&Screen_Para + CHK_HEAD_LEN, SCREEN_PARA_LEN);
  
#ifdef SDI_SCREEN_PARA_BK0 
  Write_Storage_Data(SDI_SCREEN_PARA_BK0, (INT8U *)&Screen_Para + CHK_HEAD_LEN, SCREEN_PARA_LEN);
#endif

#ifdef SDI_SCREEN_PARA_BK1 
  Write_Storage_Data(SDI_SCREEN_PARA_BK1, (INT8U *)&Screen_Para + CHK_HEAD_LEN, SCREEN_PARA_LEN);
#endif  
  
  
#ifdef SDI_SCREEN_PARA_BK2 
  Write_Storage_Data(SDI_SCREEN_PARA_BK2, (INT8U *)&Screen_Para + CHK_HEAD_LEN, SCREEN_PARA_LEN);
#endif 
  
  return 1;
}

//�����Ŀ����֡
INT8U Save_Prog_Property_Frame_Proc(INT8U Frame[],INT16U FrameLen)
{
  INT8U Prog_No;

  Prog_No = *(Frame + 8); //��Ŀ��
  Write_Storage_Data(SDI_PROG_PARA + Prog_No , (INT8U *)&Prog_Para + CHK_HEAD_LEN, PROG_PARA_LEN);
  
#ifdef SDI_PROG_PARA_BK0 
  Write_Storage_Data(SDI_PROG_PARA_BK0 + Prog_No, (INT8U *)&Prog_Para + CHK_HEAD_LEN, PROG_PARA_LEN);
#endif

#ifdef SDI_PROG_PARA_BK1 
  Write_Storage_Data(SDI_PROG_PARA_BK1 + Prog_No, (INT8U *)&Prog_Para + CHK_HEAD_LEN, PROG_PARA_LEN);
#endif  
  
  
#ifdef SDI_PROG_PARA_BK2 
  Write_Storage_Data(SDI_PROG_PARA_BK2 + Prog_No, (INT8U *)&Prog_Para + CHK_HEAD_LEN, PROG_PARA_LEN);
#endif     
 
  return 1;
}

//��ȡ��Ŀprog_no����Area_No�ĵ�File_No���ļ��Ĳ����Ĵ洢����
STORA_DI Get_Show_Para_Stora_DI(INT8U Prog_No, INT8U Area_No, INT8U File_No)
{
  if(Prog_No >= MAX_PROG_NUM || Area_No >= MAX_AREA_NUM || File_No >= MAX_FILE_NUM)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  return SDI_FILE_PARA + (INT16U)Prog_No * MAX_AREA_NUM * MAX_FILE_NUM + (INT16U)Area_No * MAX_FILE_NUM + File_No; 
    
}

//��Ŀ���ݿ������
INT8U Read_Prog_Block_Index(INT8U Prog_No, void *pDst, void *pDst_Start, INT16U DstLen)
{
  INT16U Len;
  
  Len = Read_Storage_Data(SDI_PROG_BLOCK_INDEX + Prog_No,  pDst, pDst_Start, DstLen);
#ifdef SDI_PROG_BLOCK_INDEX_BK0
  if(Len EQ 0)
    Len = Read_Storage_Data(SDI_PROG_BLOCK_INDEX_BK0 + Prog_No,  pDst, pDst_Start, DstLen);
#endif     
  
#ifdef SDI_PROG_BLOCK_INDEX_BK1
  if(Len EQ 0)
    Len = Read_Storage_Data(SDI_PROG_BLOCK_INDEX_BK1 + Prog_No,  pDst, pDst_Start, DstLen);
#endif 
  
  return 0;
  
}


INT8U Write_Prog_Block_Index(INT8U Prog_No, void *pSrc, INT16U SrcLen)
{
  INT8U Re = 1;
  
  Re &= Write_Storage_Data(SDI_PROG_BLOCK_INDEX + Prog_No, pSrc, SrcLen);
  
#ifdef SDI_PROG_BLOCK_INDEX_BK0
  Re &= Write_Storage_Data(SDI_PROG_BLOCK_INDEX_BK0 + Prog_No, pSrc, SrcLen);
#endif

#ifdef SDI_PROG_BLOCK_INDEX_BK1
  Re &= Write_Storage_Data(SDI_PROG_BLOCK_INDEX_BK1 + Prog_No, pSrc, SrcLen);
#endif
  
  return Re;
  
}

//��ȡ�ļ�����
INT16U Read_File_Para(INT8U Prog_No, INT8U Area_No, INT8U File_No, void *pDst, void *pDst_Start, INT16U DstLen)
{
  STORA_DI SDI;
  INT16U Len;
  
  SDI = SDI_FILE_PARA + (INT16U)Prog_No * MAX_AREA_NUM * MAX_FILE_NUM + (INT16U)Area_No * MAX_FILE_NUM + File_No;   
  Len = Read_Storage_Data(SDI, pDst, pDst_Start, DstLen); 
  
#ifdef SDI_FILE_PARA_BK0
  if(Len EQ 0)
  {
    SDI = SDI_FILE_PARA_BK0 + (INT16U)Prog_No * MAX_AREA_NUM * MAX_FILE_NUM + (INT16U)Area_No * MAX_FILE_NUM + File_No;   
    Len = Read_Storage_Data(SDI, pDst, pDst_Start, DstLen); 
  }
#endif
  
#ifdef SDI_FILE_PARA_BK1
  if(Len EQ 0)
  {
    SDI = SDI_FILE_PARA_BK1 + (INT16U)Prog_No * MAX_AREA_NUM * MAX_FILE_NUM + (INT16U)Area_No * MAX_FILE_NUM + File_No;   
    Len = Read_Storage_Data(SDI, pDst, pDst_Start, DstLen); 
  }
#endif 
  
  return Len;

}

//д�ļ�����
INT8U Write_File_Para(INT8U Prog_No, INT8U Area_No, INT8U File_No, void *pSrc, INT16U SrcLen)
{
  STORA_DI SDI;
  INT8U Re = 1;
  
  SDI = SDI_FILE_PARA + (INT16U)Prog_No * MAX_AREA_NUM * MAX_FILE_NUM + (INT16U)Area_No * MAX_FILE_NUM + File_No;   
  Re &=  Write_Storage_Data(SDI, pSrc, FILE_PARA_LEN); 
  
#ifdef SDI_FILE_PARA_BK0
  SDI = SDI_FILE_PARA_BK0 + (INT16U)Prog_No * MAX_AREA_NUM * MAX_FILE_NUM + (INT16U)Area_No * MAX_FILE_NUM + File_No;   
  Re &=  Write_Storage_Data(SDI, pSrc, FILE_PARA_LEN);   
#endif
  
#ifdef SDI_FILE_PARA_BK1
  SDI = SDI_FILE_PARA_BK1 + (INT16U)Prog_No * MAX_AREA_NUM * MAX_FILE_NUM + (INT16U)Area_No * MAX_FILE_NUM + File_No;   
  Re &=  Write_Storage_Data(SDI, pSrc, FILE_PARA_LEN);   
#endif 
  
  return Re;
}

//��ȡ��ǰ��ʾ���ݴ洢����
INT16U Read_Cur_Block_Index(void *pDst, void *pDst_Start, INT16U DstLen)
{
  STORA_DI SDI;
  INT16U Len;
  
  Len = Read_Storage_Data(SDI_CUR_BLOCK_INDEX, pDst, pDst_Start, DstLen); 
  
#ifdef SDI_CUR_BLOCK_INDEX_BK0
  if(Len EQ 0)
    Len = Read_Storage_Data(SDI_CUR_BLOCK_INDEX_BK0, pDst, pDst_Start, DstLen); 
#endif
  
#ifdef SDI_CUR_BLOCK_INDEX_BK1
  if(Len EQ 0)
     Len = Read_Storage_Data(SDI_CUR_BLOCK_INDEX_BK1, pDst, pDst_Start, DstLen); 
#endif 
  
  return Len;

}

INT8U Check_Prog_Show_Data(INT8U Prog_No, INT8U Area_No, INT8U File_No, void *pData)
{
  S_File_Para_Info *p = (S_File_Para_Info *)pData;

  if(p->Prog_No EQ Prog_Para.Prog_No &&\
     p->Area_No EQ Area_No &&\
     p->File_No EQ File_No)
    return 1;
  else
    return 0;
  
}

INT16U Copy_Show_Pic_Data(INT8U Area_No, void *pSrc, INT16U Off, INT16U SrcLen, S_Show_Data *pDst)
{
  INT16U Width,Height;
  INT32U X,Y;
  INT32U i,Len;
  INT8U Re;
  //INT16U Index;

  
  Width = Get_Area_Width(Area_No);
  Height = Get_Area_Height(Area_No);
  
  Len = (INT32U)Width * ((Height % 8) EQ 0 ? (Height / 8) : (Height / 8 + 1)); //ÿ����ʾ�����ݳ���

  Off = Off % Len; //Off��һ����ʾ�����е�ƫ�� 

  for(i = 0; i <SrcLen*8 && i<Len*8; i ++)
  {
    Re = Get_Buf_Bit((INT8U *)pSrc, SrcLen, i);
    X = (Off*8 + i) % Width;
    Y = (Off*8 + i) / Width;
    if(X < Width && Y < Height) //X0,Y0������X_Len��Y_Len�ķ�Χ��
      Set_Area_Point_Data(pDst, Area_No, X, Y, Re);
    else
      break;
  }
  
  return i/8;
}

//��ȡ��ǰ��Ŀ�ķ���Area_No�ĵ�File_No�ļ��ĵ�SIndex������ʾ����
INT16U Read_Prog_Show_Data(INT8U Area_No, INT8U File_No, INT16U SIndex, S_Show_Data *pShow_Data)
{
  INT16U Width,Height;
  INT32U Len,Len0,Offset;
  INT16U Index;

  Width = Get_Area_Width(Area_No);
  Height = Get_Area_Height(Area_No);
  
  Len = (INT32U)Width * ((Height % 8) EQ 0 ? (Height / 8) : (Height / 8 + 1));//ÿ�����ֽ���
  //SLen = Len;
  Len = Len * SIndex; //��������ʾ�����е���ʼλ��

  Index = Len / BLOCK_SHOW_DATA_LEN;//��ƫ��
  Index += Prog_Status.Block_Index.Index[Area_No][File_No]; //��ʼ���
    
  Offset = Len % BLOCK_SHOW_DATA_LEN; //�ڸÿ��е�����

  Len0 = 0;
  while(Len0 < Len)
  {
    if(Read_Storage_Data(SDI_SHOW_DATA + Index, Pub_Buf, Pub_Buf, sizeof(Pub_Buf)) EQ 0)
      break;
    
    if(Check_Prog_Show_Data(Prog_Para.Prog_No, Area_No, File_No, Pub_Buf) EQ 0)
      break;
       
    //��������
    //Len0 = 0;
    mem_cpy(Pub_Buf, Pub_Buf + BLOCK_HEAD_DATA_LEN + Offset, BLOCK_DATA_LEN - (BLOCK_HEAD_DATA_LEN + Offset), Pub_Buf, sizeof(Pub_Buf));   
    //�����������ݸ��Ƶ���ʾ������
    
    Len0 += Copy_Show_Pic_Data(Area_No, Pub_Buf, Len0, BLOCK_DATA_LEN - (BLOCK_HEAD_DATA_LEN + Offset), pShow_Data);
    Index++;
    Offset = 0;
  }
  
  return Len0;
  
}

//д��ǰ��ʾ���ݴ洢����
INT8U Write_Cur_Block_Index(void *pSrc, INT16U SrcLen)
{
  //STORA_DI SDI;
  INT8U Re = 1;
  
  //SDI = SDI_FILE_PARA + (INT16U)Prog_No * MAX_AREA_NUM * MAX_FILE_NUM + (INT16U)Area_No * MAX_FILE_NUM + File_No;   
  Re &=  Write_Storage_Data(SDI_CUR_BLOCK_INDEX, pSrc, sizeof(S_Cur_Block_Index)); 
  
#ifdef SDI_CUR_BLOCK_INDEX_BK0
  //SDI = SDI_FILE_PARA_BK0 + (INT16U)Prog_No * MAX_AREA_NUM * MAX_FILE_NUM + (INT16U)Area_No * MAX_FILE_NUM + File_No;   
  Re &=  Write_Storage_Data(SDI_CUR_BLOCK_INDEX, pSrc, sizeof(S_Cur_Block_Index));   
#endif
  
#ifdef SDI_CUR_BLOCK_INDEX_BK1
  //SDI = SDI_FILE_PARA_BK1 + (INT16U)Prog_No * MAX_AREA_NUM * MAX_FILE_NUM + (INT16U)Area_No * MAX_FILE_NUM + File_No;   
  Re &=  Write_Storage_Data(SDI_CUR_BLOCK_INDEX, pSrc, sizeof(S_Cur_Block_Index));   
#endif 
  
  return Re;
}

/*
typedef struct
{
  INT8U Prog_No;  //��Ŀ��
  INT8U Area_No:4; //������
  INT8U File_No:4; //�ļ���
  INT16U Len;     //֡����
  INT8U Buf[ONE_BLOCK_SIZE];
  
}S_Prog_Show_Data;
*/
//�����Ŀ����֡
INT8U Save_Prog_Data_Frame_Proc(INT8U Frame[],INT16U FrameLen)
{
  static S_File_Para_Info File_Para_Info;
  INT8U Prog_No, Area_No, File_No, Type;
  INT16U Para_Len,Len;
  INT8U Seq,Seq0,Re;
  STORA_DI SDI;
  S_Prog_Show_Data *pShow_Data;

  memcpy(&Len, &Frame[FLEN], sizeof(Len)); //֡��
  //���������򳤶�
  if(Len > F_NDATA_LEN)
    Len = Len - F_NDATA_LEN;
  else
  {
    ASSERT_FAILED();
    return 0;
  }
  
  Seq0 = Frame[FSEQ0];
  if(Seq0 EQ 0) //����֡--��֡�еĵ�һ֡
  {
      Type = Frame[FDATA];//*(Frame + 8); //��������?
      Prog_No = Frame[FDATA + 1];//*(Frame + 9); //��Ŀ��
      Area_No = Frame[FDATA + 2];//*(Frame + 10); //������
      File_No = Frame[FDATA + 3];//*(Frame + 11); //�ļ���
      //File_Para_Info.Seq0 = Seq0;

      Para_Len = Get_Show_Para_Len(File_Para_Info.Type); //��������
      if(Para_Len EQ Len)// ��������
      {     
        Re =  Write_File_Para(Prog_No, Area_No, File_No, &Frame[FDATA], FILE_PARA_LEN);//д���ļ�����
        if(Re > 0)
        {
          File_Para_Info.Type = Type;
          File_Para_Info.Prog_No = Prog_No;
          File_Para_Info.Area_No = Area_No;
          File_Para_Info.File_No = File_No;
          //File_Para_Info.Block_Index = 
          File_Para_Info.Seq0 = Seq0;
          
          //���������Ŀ�Ĵ洢����
          Read_Prog_Block_Index(Prog_No, Prog_Status.Block_Index.Index, &Prog_Status.Block_Index, sizeof(Prog_Status.Block_Index));
          //Read_Storage_Data(Prog_Block_Index
        }
        
        return Re;
      }
      else
      {
        
        ASSERT_FAILED();
        return 0;
      }
  }
  else if(Seq0 EQ File_Para_Info.Seq0 + 1) //��һ֡
  {
    if(Seq0 EQ 1) //��һ������֡
      Prog_Status.Block_Index.Index[File_Para_Info.Area_No][File_Para_Info.File_No] = Cur_Block_Index.Index;
    
    memset(Pub_Buf, 0, sizeof(Pub_Buf));
    
    Pub_Buf[0] = File_Para_Info.Prog_No;
    Pub_Buf[1] = (File_Para_Info.Area_No <<4) + File_Para_Info.File_No;
    Pub_Buf[2] = File_Para_Info.Type;   
    Pub_Buf[3] = Seq0 - 1;
    Pub_Buf[4] = Len % 256;
    Pub_Buf[5] = Len / 256;
    Pub_Buf[6] = 0; //��һ֡�Ĵ洢����--���� 
    Pub_Buf[7] = 0;
    mem_cpy(Pub_Buf + 8, &Frame[FDATA], Len, Pub_Buf, sizeof(Pub_Buf));
    
    //��ǰ�ֿ�����
    Write_Storage_Data(SDI_SHOW_DATA + Cur_Block_Index.Index, Pub_Buf, BLOCK_DATA_LEN);
    
    //���浱ǰ����
    Cur_Block_Index.Index ++;
    SET_SUM(Cur_Block_Index);
    Write_Cur_Block_Index(&Cur_Block_Index, sizeof(Cur_Block_Index));
    
    //д��ǰ��Ŀ������
    Prog_Status.Block_Index.Index[File_Para_Info.Area_No][File_Para_Info.File_No + 1] = Cur_Block_Index.Index;
    SET_SUM(Prog_Status.Block_Index);
    Write_Prog_Block_Index(File_Para_Info.Prog_No, Prog_Status.Block_Index.Index, sizeof(Prog_Status.Block_Index.Index));
    
    return 1;
  }
    
    
  return 0;

}

//ɾ����Ŀ����
INT8U Del_Prog_Data(INT8U Frame[], INT16U FrameLen)
{

}




//��ȡ��Ŀ����
//Prog��Ŀ��
//����ֵ1 ��ʾ��ȡ�ɹ���0��ʾû�������Ŀ���߶�ȡ���ɹ�
INT8U Read_Prog_Para(INT8U Prog_No)
{/*
  char File_Name[MAX_FILE_NAME_SIZE];
  FILE_T File;
  INT16U Ctrl, Len;
  INT8U Seq;
  
  Get_Program_Property_File_Name(Prog_No, File_Name);
  File = File_Open(File_Name, FILE_R);
  Len = File_Read_One_Frame(File, 0, &Seq, &Ctrl, (INT8U *)&Prog_Para, (INT8U *)&Prog_Para, sizeof(Prog_Para));
  File_Close(File);
  if(Len > 0)
    return 1;
  else
  {
    ASSERT_FAILED();
    return 0;
  }*/
}

//��ʱ��Ϣ�У����ڵĵ�0λ��ʾ����1����6λ��ʾ������
INT8U Check_Program_Time()
{
  //INT8U i;//Re = 1;
  INT8U Temp[20];
  memset(Temp, 0xFF, sizeof(Temp));
  
  if(Prog_Para.Timing[0].Week != 0xFF)  //�����ڶ�ʱ
  {
    if(GET_BIT(Prog_Para.Timing[0].Week, Cur_Time.Time[T_WEEK]) EQ 0)
      return 0;
  }      
  
  
  //�����ڶ�ʱ
  if(memcmp(Prog_Para.Timing[0].Start_Date, Temp, 3) != 0 &&\
    memcmp(Prog_Para.Timing[0].End_Date, Temp, 3) != 0)
  {
    if(!(Cur_Time.Time[T_YEAR] >= Prog_Para.Timing[0].Start_Date[0] &&\
      Cur_Time.Time[T_YEAR] <= Prog_Para.Timing[0].End_Date[0] &&\
        Cur_Time.Time[T_MONTH] >= Prog_Para.Timing[0].Start_Date[1] &&\
          Cur_Time.Time[T_MONTH] <= Prog_Para.Timing[0].End_Date[1] &&\
            Cur_Time.Time[T_DATE] >= Prog_Para.Timing[0].Start_Date[2] &&\
              Cur_Time.Time[T_DATE] <= Prog_Para.Timing[0].End_Date[2]))
      return 0;
    
  } 
  
  //��ʱ�䶨ʱ
  if(memcmp(Prog_Para.Timing[0].Start_Time, Temp, 2) != 0 &&\
    memcmp(Prog_Para.Timing[0].End_Time, Temp, 2) != 0)
  {
    if(!(Cur_Time.Time[T_HOUR] >= Prog_Para.Timing[0].Start_Time[0] &&\
      Cur_Time.Time[T_HOUR] <= Prog_Para.Timing[0].End_Time[0] &&\
        Cur_Time.Time[T_MIN] >= Prog_Para.Timing[0].Start_Time[1] &&\
          Cur_Time.Time[T_MIN] <= Prog_Para.Timing[0].End_Time[1]))
      return 0;
    
  }         
  
  return 1;
}

//��ȡ��ʾ����--����Read_Prog_Para
INT8U Update_Prog_Para()
{
  INT8U i;
  
  for(i = 0; i < MAX_PROG_NUM; i ++)
  {
    if(Read_Prog_Para(i)) //��ȡ�ɹ�
    {
      if(Check_Program_Time())//��ǰʱ���Ƿ�Ϊ��Ŀ����ʱ��?
        return 1;
    }
  }
  
  return 0;
  
}

//����Ƿ���Ҫ���½�Ŀ����
INT8U Check_Update_Prog_Para()
{
  static S_Int8U Min_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  
  if(Min_Bak.Var EQ Cur_Time.Time[T_MIN])
    return 0;
  
  Min_Bak.Var = Cur_Time.Time[T_HOUR];  
  Debug_Print("Min check update program para");
 	
  if(Check_Program_Time() EQ 0) //��ǰʱ���Ƿ��ڽ�Ŀ����ʱ����?
  {	
    if(Update_Prog_Para())
    {
      Debug_Print("update program para ok!");
      return 1;
    }
    else
      Debug_Print("no program run");
  }
  
  return 0;
}

//��ȡ����
void Read_Para()
{/*
  FILE_T File;
  INT16U Ctrl_Code;
  char File_Name[20];
  INT32U Offset = 0;
  INT32S Len = 0;
  INT8U Counts = 0;
  INT8U Seq;
  
  //��ȡ��������
  Get_Fac_Para_File_Name(File_Name); //���������ļ�����
  File = File_Open(File_Name, FILE_R); //ֻ����
  
  Len = File_Read_One_Frame(File, Offset, &Seq, &Ctrl_Code, Pub_Buf, Pub_Buf, sizeof(Pub_Buf));
  if(Len > 0)
    Para_Frame_Proc(Ctrl_Code, Pub_Buf, Len);
  else
    ASSERT_FAILED();
  
  //��ȡ�û�����
  Get_Usr_Para_File_Name(File_Name); //���������ļ�����
  File = File_Open(File_Name, FILE_R); //ֻ����
  //ÿ�ζ�һ֡��������,���ļ�����10֡

  while(1)
  {
    Len = File_Read_One_Frame(File, Offset, &Seq, &Ctrl_Code, Pub_Buf, Pub_Buf, sizeof(Pub_Buf));
    if(Len > 0)
    {
      Counts ++;
      Para_Frame_Proc(Ctrl_Code, Pub_Buf, Len);
    }
    else
    {
      if(Len != FILE_END)
        ASSERT_FAILED();
      break;
    }
  }
  
  //��ȡ��Ŀ����
  Update_Prog_Para();
  */
}
