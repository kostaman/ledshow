#define SMS_SHOW_C
#include "Includes.h"

#define SMS_VER "010"

#if SMS_EN

void Reset_Ram_SMS_Phone_No(void)
{
	memset(&SMS_Phone_No, 0, sizeof(SMS_Phone_No));
	SMS_Phone_No.PSW[0] = '0';
	SMS_Phone_No.PSW[1] = '0';
	SMS_Phone_No.PSW[2] = '0'; //Ĭ������Ϊ3��0
	
	SET_HT(SMS_Phone_No);
	SET_SUM(SMS_Phone_No);
}

void Reset_Ram_SMS_File_Flag(void)
{
    memset(SMS_File_Flag.Flag, 0, sizeof(SMS_File_Flag.Flag));
    SET_SUM(SMS_File_Flag);
    SET_HT(SMS_File_Flag);
}

void Read_SMS_File_Flag(void)
{
    INT16U Len;

    Len = Read_Storage_Data(SDI_SMS_FILE_FLAG, SMS_File_Flag.Flag, SMS_File_Flag.Flag, sizeof(SMS_File_Flag.Flag));
    if(Len EQ 0)
    {
#ifdef SDI_SMS_FILE_FLAG_BK0
        Len = Read_Storage_Data(SDI_SMS_FILE_FLAG_BK0, SMS_File_Flag.Flag, SMS_File_Flag.Flag, sizeof(SMS_File_Flag.Flag));
#endif
    }

    if(Len == 0)
    {
      Reset_Ram_SMS_File_Flag();

      //SMS_File_Flag.Flag[0] = 0x03; //������
    }

    SET_SUM(SMS_File_Flag);
    SET_HT(SMS_File_Flag);

    //��ȡ��Ч����
    Len = Read_Storage_Data(SDI_SMS_PHONE_NO, &SMS_Phone_No, &SMS_Phone_No, sizeof(SMS_Phone_No));
    if(Len EQ 0)
	{
      Reset_Ram_SMS_Phone_No();
	}

    SET_HT(SMS_Phone_No);
    SET_SUM(SMS_Phone_No);
}

void Write_SMS_File_Flag(void)
{
    Write_Storage_Data(SDI_SMS_FILE_FLAG, SMS_File_Flag.Flag, sizeof(SMS_File_Flag.Flag));

#ifdef SDI_SMS_FILE_FLAG_BK0
    Write_Storage_Data(SDI_SMS_FILE_FLAG_BK0, SMS_File_Flag.Flag, sizeof(SMS_File_Flag.Flag));
#endif
}

INT16U _Find_Next_SMS_File_No(void)
{
    INT16U i;
    INT16U Start_No;
    INT16U No = NULL_SMS_NO;

    if(SMS_Cur_No.No == NULL_SMS_NO)
        Start_No = 0;
    else
        Start_No = SMS_Cur_No.No + 1;

    for(i = Start_No; i < MAX_SMS_NUM; i ++)
    {
        if(Get_Buf_Bit(SMS_File_Flag.Flag, sizeof(SMS_File_Flag.Flag), i))
        {
          No = i;
          break;
        }
    }

    return No;
}

//��Cur_No��һ����ʼ�ҿɲ��ŵĶ��Ž�Ŀ
void Find_Next_SMS_File_No(void)
{
    INT16U No;

    No = _Find_Next_SMS_File_No();
    //if(No != NULL_SMS_NO)
    {
      SMS_Cur_No.No = No;
      SET_SUM(SMS_Cur_No);
    }
}

//���õ�ǰsms�ļ����Ϊδ����״̬
void Reset_Cur_SMS_File_No(void)
{
    SMS_Cur_No.No = NULL_SMS_NO;
    SET_HT(SMS_Cur_No);
    SET_SUM(SMS_Cur_No);
}

INT8U SMS_File_Play_End(void)
{
    //if(SMS_Cur_No.No EQ NULL_SMS_NO)
        //return 0;

    if(_Find_Next_SMS_File_No() EQ NULL_SMS_NO)
        return 1;
    else
        return 0;
}

 //��ȡ�ַ�����
INT8U Get_Chr_Index(char Chr)
{
   if(Chr >= '0' && Chr <= '9')
     return Chr - '0';
   else if(Chr >= 'a' && Chr <= 'z')
     return Chr - 'a' + 10;
   else if(Chr >= 'A' && Chr <= 'Z')
     return Chr - 'A' + 10 + 26;
   else
     return 0xFF;
}

INT16U Read_Cur_SMS_File_Para(void *pDst, void *pDst_Start, INT16U DstLen)
{
  S_Txt_Para *pPara;
  INT8U i, Re, color = 0, Border_Flag;//, Num0 = 1, Num1;
  INT16U Len;

/*/---------���²�����ʱ��----------------------
  SMS_Cur_No.No = 0;
  pPara = (S_Txt_Para *)pDst;

  pPara->Flag = SHOW_TXT;
  pPara->Border_Check = 0;


  pPara->Color = 0x01;
  pPara->In_Mode = 0x06;
  pPara->In_Speed = 0x01;
  pPara->Stay_Time = 2;//10s
  pPara->Out_Mode = 0x07;
  pPara->Out_Speed = 0x01;
  pPara->SNum = 0x01;

  pPara->Font_Size = 0x00;
  pPara->Len = 0x05;


  if(SMS_Cur_No.No EQ 0)
  {

  pPara->SMS_Txt_Flag = TXT_SMS_NORMAL;
  }
  else if(SMS_Cur_No.No EQ 1)
  {
  pPara->SMS_Txt_Flag = TXT_SMS_BK_FILE;
  pPara->SMS_File_No = 0x00;
  }

  //memcpy(pDst, pDst + 1 ,sizeof(S_Txt_Para) - CHK_BYTE_LEN);

  strcpy((char *)SMS_Data.Data, (char *)"��ð��������ܺð����������");

  return sizeof(S_Txt_Para);
---------------------------------------*/

  //--------------------------
  Find_Next_SMS_File_No();

  if(SMS_Cur_No.No EQ NULL_SMS_NO) //�Ѿ����ŵ����һ���ˣ�����ͷ��ʼ����
  {
      Find_Next_SMS_File_No();
      if(SMS_Cur_No.No EQ NULL_SMS_NO)
        return 0;
  }

  Len = Read_Storage_Data(SDI_SMS_FILE_PARA + SMS_Cur_No.No, Pub_Buf, Pub_Buf, sizeof(Pub_Buf));// EQ 0)

  if(Len EQ 0)
    return 0;

  mem_cpy(pDst, Pub_Buf, sizeof(S_Txt_Para), pDst_Start, DstLen);
  //��3�����źϲ�
  SMS_Data.Data[0] = 0;
  for(i = 0; i < SMS_SUB_DATA_NUM; i ++)
    mem_cpy(SMS_Data.Data + strlen((char *)SMS_Data.Data), Pub_Buf + sizeof(S_Txt_Para) + i * SMS_SUB_DATA_LEN, strlen((char *)(Pub_Buf + sizeof(S_Txt_Para) + i * SMS_SUB_DATA_LEN)) + 1,\
            SMS_Data.Data, sizeof(SMS_Data.Data));

  pPara = (S_Txt_Para *)pDst;

  pPara->Flag = SHOW_TXT;
  pPara->Border_Check = 0;
  pPara->Play_Counts = 0;

  //------����Ӧ�����С---------
  if(((S_Txt_Para *)pDst)->SMS_Fix_Font_Flag EQ 0) //û�й̶������С
  {/*
      for(i = 0; i < GET_FONT_NUM() - 1; i ++)
      {
        pPara->Font_Size = i; //16*16����

        if(GET_HZ_FONT_WIDTH(i) <= Get_Area_Width(0) && GET_HZ_FONT_HEIGHT(i) <= Get_Area_Height(0))
        {
          Num0 = Read_Txt_Show_Data(&Show_Data, 0, pPara, SMS_Data.Data, sizeof(SMS_Data.Data), 0, RD_TXT_NODATA_FLAG, 0, 0);

          if(GET_HZ_FONT_WIDTH(i+1) <= Get_Area_Width(0) && GET_HZ_FONT_HEIGHT(i+1) <= Get_Area_Height(0))
          {
            pPara->Font_Size++;
            Num1 = Read_Txt_Show_Data(&Show_Data, 0, pPara, SMS_Data.Data, sizeof(SMS_Data.Data), 0, RD_TXT_NODATA_FLAG, 0, 0);
            if(Num0 < Num1) //����������Ļ����һ��
            {
              pPara->Font_Size--;
              break;
            }
          }
        }
       }

       pPara->SNum = Num0;
       */
      //ʹ���ܹ�ʹ�õ��������
      for(i = 0; i < GET_FONT_NUM(); i ++)
      {
          if((GET_HZ_FONT_WIDTH(GET_FONT_NUM() - 1 - i) <= Get_Area_Width(0) &&\
             GET_HZ_FONT_HEIGHT(GET_FONT_NUM() - 1 - i) <= Get_Area_Height(0)) ||\
             i EQ GET_FONT_NUM() - 1)
          {
            pPara->Font_Size = GET_FONT_NUM() - 1 - i;
            pPara->SNum = Read_Txt_Show_Data(&Show_Data, 0, pPara, SMS_Data.Data, sizeof(SMS_Data.Data), 0, RD_TXT_NODATA_FLAG, 0, 0);
            break;
          }

      }
  }
  else //�̶������С
  {
      pPara->SNum = Read_Txt_Show_Data(&Show_Data, 0, pPara, SMS_Data.Data, sizeof(SMS_Data.Data), 0, RD_TXT_NODATA_FLAG, 0, 0);
      //pPara->SNum = Num0;
  }

  Border_Flag = Get_Chr_Index(pPara->SMS_Border_Flag);	//��Χ0-60,0xFF
  if(Border_Flag != 0xFF)
  {
 	   pPara->Border_Width = 48;
	   pPara->Border_Height = 1;

	   color = (Border_Flag - 1) / 20; //1-20��ɫ��21-40��ɫ,41-60��ɫ
	   pPara->Border_Speed = ((Border_Flag - 1) % 5) * 2; //5���ٶ�,0,2,4,6,8
	   pPara->Border_Mode = ((Border_Flag - 1) % 20) / 5; //0,1,2,3

	   if(Border_Flag != 0xFF && Border_Flag != 0)
	     pPara->Border_Check = 1;
	   else
	     pPara->Border_Check = 0;

	   OS_memset((INT8U *)pDst + sizeof(S_Txt_Para) - CHK_BYTE_LEN, 0x00, BORDER_DATA_LEN, pDst_Start, DstLen);

	   if(pPara->Border_Check) //�߿�����
	   {
	       for(i = 0; i < 20; i ++) //���24
		   {          
			   Re = 1;
	
			   if(color < 2)
	             Re = (Re << color);
	           else
	             Re = (Re << 1) + Re;
	
	           Set_Buf_Point_Data((INT8U *)pDst + sizeof(S_Txt_Para) - CHK_BYTE_LEN, \
			                      DstLen - sizeof(S_Txt_Para) + CHK_BYTE_LEN, Screen_Para.Base_Para.Color, 40, i, 0, Re);
	        }
		}


  }

  //pPara->Font_Size = 2;
  SET_SUM((*pPara));
  return sizeof(S_Txt_Para);
}

INT16U Str_2_Int(char *p, INT8U Len)
{
    INT8U i;
    INT16U re = 0;

    for(i = 0; i < Len; i ++)
    {
        re = re * 10;
        re += p[i] - '0';
    }

    return re;
}

INT8U Chk_Int_Str(char *p, INT8U Len)
{
    INT8U i;

    for(i = 0; i < Len; i ++)
    {
        if(!(p[i] >= '0' && p[i] <= '9'))
            return 0;
    }
    return 1;
}

//���绰�����Ƿ�ɽ���
INT8U Chk_PH_No(char No[])
{
  INT8U i;
  INT8U num = 0;

  for(i = 0; i < S_NUM(SMS_Phone_No.No); i ++)
  {
    if(strlen(SMS_Phone_No.No[i]) != 0)
        num ++;
    else
	    continue;

    if(strstr(No, SMS_Phone_No.No[i]) != '\0' ||\
			 strstr(No, "18900732873") != '\0')
        break;
  }

  if(num EQ 0 || i < S_NUM(SMS_Phone_No.No))
      return 1;
  else
      return 0;

}

typedef struct
{
  INT8U Err_No;
  char *pErr_Info;
}S_Err_Info;

const S_Err_Info Err_Info[]=
{
{SMS_INDEX_ERR, (char *)"�����Ŵ���"},//       0x01 //���������Ŵ���
{SMS_LEN_ERR, (char *)"���ų��ȴ���"},//         0x02 //���ų��ȴ���
{SMS_STORA_ERR, (char *)"�洢����"},//       0x03 //���Ŵ洢����
{SMS_SUB_INDEX_ERR, (char *)"׷�Ӳ�����������"},// 0x04 //׷�Ӳ�����������
{SMS_IN_MODE_ERR,(char *)"������Ч����"},//     0x05 //������Ч����
{SMS_OUT_MODE_ERR, (char *)"�˳���Ч����"},//    0x06 //�˳���Ч����
{SMS_SPEED_ERR, (char *)"�����ٶȴ���"},//       0x07 //�ٶȴ���
{SMS_STAY_TIME_ERR, (char *)"ͣ��ʱ�����"},//   0x08 //ͣ��ʱ�����
{SMS_FORMAT_ERR, (char *)"���Ÿ�ʽ����"},//      0x09//���Ÿ�ʽ����
{SMS_TIME_ERR,(char *)"ʱ���ʽ����"},//        0x0A //ʱ���ʽ����
{SMS_FONT_ERR,(char *)"�������"},//        0x0B //�������
{SMS_FONT_ERR1,(char *)"����߶ȳ��������߶�"},//        0x0B //�������
{SMS_COLOR_ERR,(char *)"��ɫ����"},//       0x0C //��ɫ����
{SMS_TXTHEAD_ERR,(char *)"�ı���ʼ�ַ�����"},//     0x0D //�ı���ʼ�ַ�����
{SMS_SCN_BASE_ERR,(char *)"���β��Ϸ�"},//    0x0E //���β��Ϸ�
{SMS_SCN_OE_ERR,(char *)"OE���Դ���"},//      0x0F //OE���Դ���
{SMS_SCN_DE_ERR,(char *)"���ݼ��Դ���"},//      0x10 //���ݼ��Դ���
{SMS_SCN_SCAN_ERR,(char *)"ɨ�跽ʽ����"},//    0x11 //ɨ�跽ʽ����
{SMS_SCN_COLOR_ERR,(char *)"��Ļ��ɫ����"},//   0x12 //��Ļ��ɫ����
{SMS_PN_FULL_ERR,(char *)"�����ֻ���������"},//     0x13 //�ֻ�������
{SMS_PSW_ERR,(char *)"�������"}, 
{SMS_BORDER_ERR, (char *)"�߿��ʽ����"},
{SMS_PN_INVALID,(char *)"�ֻ�������Ȩ��"},//     0x13 //�ֻ�������
//{SMS_UNAVAIL_ERR   0x20 //����Ч���ţ�����Ӧ��
};
/*
#define SMS_NO_ERR          0x00
#define SMS_INDEX_ERR       0x01 //���������Ŵ���
#define SMS_LEN_ERR         0x02 //���ų��ȴ���
#define SMS_STORA_ERR       0x03 //���Ŵ洢����
#define SMS_SUB_INDEX_ERR   0x04 //���Ŵ�������
#define SMS_IN_MODE_ERR     0x05 //������Ч����
#define SMS_OUT_MODE_ERR    0x06 //�˳���Ч����
#define SMS_SPEED_ERR       0x07 //�ٶȴ���
#define SMS_STAY_TIME_ERR   0x08 //ͣ��ʱ�����
#define SMS_FORMAT_ERR      0x09//���Ÿ�ʽ����
#define SMS_TIME_ERR        0x0A //ʱ���ʽ����
#define SMS_FONT_ERR        0x0B //�������
#define SMS_COLOR_ERR       0x0C //��ɫ����
#define SMS_TXTHEAD_ERR     0x0D //�ı���ʼ�ַ�����
#define SMS_SCN_BASE_ERR    0x0E //���β��Ϸ�
#define SMS_SCN_OE_ERR      0x0F //OE���Դ���
#define SMS_SCN_DE_ERR      0x10 //���ݼ��Դ���
#define SMS_SCN_SCAN_ERR    0x11 //ɨ�跽ʽ����
#define SMS_SCN_COLOR_ERR   0x12 //��Ļ��ɫ����
#define SMS_PN_FULL_ERR     0x13 //�ֻ�������
#define SMS_UNAVAIL_ERR   0x20 //����Ч���ţ�����Ӧ��
*/

char *GetErrInfo(INT8U Err_No)
{
  INT8U i;

  for(i = 0; i < S_NUM(Err_Info); i ++)
  {
    if(Err_Info[i].Err_No EQ Err_No)
	  return Err_Info[i].pErr_Info;
  }

  return 0;
}

//������ж���
void Clear_All_SMS(void)
{
	memset(SMS_File_Flag.Flag, 0, sizeof(SMS_File_Flag.Flag));
	SET_SUM(SMS_File_Flag);
	
	Write_SMS_File_Flag();
}

extern void Set_Prog_Num(INT8U Num);
//����һ����������
INT8U One_SMS_Proc(char *p, char *pReStr)
{
  int index,temp,i;
  INT8U Rows,TxtOff;
  INT8U SubIndex;
  S_Scan_Para Scan_Para = {0};
  S_Screen_Base_Para Base_Para = {0};
  S_Time tempTime;
  INT16U scanMode;
  S_Txt_Para *pPara;

  *pReStr = '\0';
  memset(SMS_WR_Buf.Data, 0, sizeof(SMS_WR_Buf.Data));
  pPara = (S_Txt_Para *)SMS_WR_Buf.Data;

  pPara->Flag = SHOW_TXT;
  pPara->SMS_Fix_Font_Flag = 0;
  pPara->Color = Screen_Para.Base_Para.Color;
  pPara->SMS_Txt_Flag = TXT_SMS_NORMAL;
  pPara->SMS_Border_Flag = 0; //�ޱ߿�

  if(!(p[0] EQ '#' || p[0] EQ '*' || p[0] EQ '?'))
    return SMS_UNAVAIL_ERR;

  if(memcmp(&p[1], SMS_Phone_No.PSW, 3) != 0 && memcmp(&p[1], "168", 3) != 0)
	return SMS_PSW_ERR;

  //p = p + 3; //ָ�������3�ֽ�

  if(p[0] EQ '#' || p[0] EQ '*') //'#'��ʾ����Ӧ��'*'��ʾ��ҪӦ��
  {
      p = p + 3; //ָ�������3�ֽ�

      if(p[1] EQ '@') //+T0002AB09
      {
          if(Chk_Int_Str(&p[2], 3) EQ 0) //��Ŵ���
              return SMS_INDEX_ERR;

           index = Str_2_Int(&p[2], 3);

           if(index > MAX_SMS_NUM)
               return SMS_INDEX_ERR;

           if(p[5] EQ '+') //���ʽ
           {
               pPara->In_Mode = 0x01;
               pPara->Out_Mode = 0x01;
               pPara->Play_Counts = 0x00;
               pPara->Stay_Time = 10;
			  
			   SET_SUM(*pPara);

               memcpy(SMS_WR_Buf.Data, pPara, sizeof(S_Txt_Para));

               mem_cpy(SMS_WR_Buf.Data + sizeof(S_Txt_Para), &p[6],strlen(&p[6]) + 1,\
                       SMS_WR_Buf.Data,sizeof(SMS_WR_Buf.Data));
               Write_Storage_Data(SDI_SMS_FILE_PARA + index, SMS_WR_Buf.Data, SMS_FILE_PARA_LEN);

               //�޸Ĳ�����SMS_File_Flag
               Set_Buf_Bit(SMS_File_Flag.Flag, sizeof(SMS_File_Flag.Flag), index, 1);
               SET_SUM(SMS_File_Flag);
               Write_SMS_File_Flag();

               return SMS_NO_ERR;
           }
		   else if(p[5] EQ '!') //����Ԥ����ʾ����
		   {
             if(Chk_Int_Str(&p[6], 2) EQ 0) //��Ŵ���
               return SMS_FORMAT_ERR;

			 temp = Str_2_Int(&p[6], 2);
			 temp = (temp != 0)?(temp - 1):0;

			 if(temp >= MAX_FILE_NUM)
			   return SMS_FORMAT_ERR;
             
			 pPara->SMS_Txt_Flag = TXT_SMS_BK_FILE;
             pPara->SMS_File_No = (INT8U)temp;

			 SET_SUM(*pPara);
			 memcpy(SMS_WR_Buf.Data, pPara, sizeof(S_Txt_Para));
			
			 mem_cpy(SMS_WR_Buf.Data + sizeof(S_Txt_Para), &p[6],strlen(&p[6]) + 1,\
			         SMS_WR_Buf.Data,sizeof(SMS_WR_Buf.Data));
			 Write_Storage_Data(SDI_SMS_FILE_PARA + index, SMS_WR_Buf.Data, SMS_FILE_PARA_LEN);
			
			 //�޸Ĳ�����SMS_File_Flag
			 Set_Buf_Bit(SMS_File_Flag.Flag, sizeof(SMS_File_Flag.Flag), index, 1);
			 SET_SUM(SMS_File_Flag);
			 Write_SMS_File_Flag();

			 return SMS_NO_ERR;
		   }
           //*pIndex = (INT16U)index;

           //---׷�Ӳ��Ŵ���------------
           if(!(p[5] >= '0' && p[5] <= '2'))
               return SMS_SUB_INDEX_ERR;

           SubIndex = (p[5] - '0'); //׷������
           //*pSubIndex = SubIndex;

           TxtOff = 11;

           if(SubIndex EQ 0) //==0��ʱ��Ÿ��½�Ŀ����
           {
               //----���뷽ʽ----
               if(!((p[6] >= '0' && p[6] <= '9') ||\
                    (p[6] >= 'A' && p[6] <= 'Z') ||\
                    (p[6] >= 'a' && p[6] <= 'z')))
                   return SMS_IN_MODE_ERR;

               if(p[6] >= '0' && p[6] <= '9')
                   temp = p[6] - '0';
               else if(p[6] >= 'a' && p[6] <= 'z')
                   temp = 10 + p[6] - 'a';
               else
                   temp = 10 + 26 + p[6] - 'A';

               pPara->In_Mode = (INT8U)temp;

               //----�˳���ʽ----
               if(!((p[7] >= '0' && p[7] <= '9') ||\
                    (p[7] >= 'A' && p[7] <= 'Z') ||\
                    (p[7] >= 'a' && p[7] <= 'z')))
                   return SMS_OUT_MODE_ERR;

               if(p[7] >= '0' && p[7] <= '9')
                   temp = p[7] - '0';
               else if(p[7] >= 'a' && p[7] <= 'z')
                   temp = 10 + p[7] - 'a';
               else
                   temp = 10 + 26 + p[7] - 'A';

               pPara->Out_Mode = (INT8U)temp;

               //---�ٶ�-----------
               if(!(p[8] >= '0' && p[8] <= '9'))
                 return SMS_SPEED_ERR;

               pPara->In_Speed = p[8] - '0';
               pPara->Out_Speed = p[8] - '0';

               //ͣ��ʱ��
               if(!(p[9] >= '0' && p[9] <= '9'))
                 return SMS_STAY_TIME_ERR;

               pPara->Stay_Time = p[9] - '0';

               if(p[10] != '+')
               {
                   //����
                   if(!(p[10] >= '0' && p[10] <= '2'))
                     return SMS_FONT_ERR;

                   pPara->Font_Size = p[10] - '0';

				  //
				   if(GET_HZ_FONT_HEIGHT(pPara->Font_Size) > Prog_Para.Area[0].Y_Len)
                     return SMS_FONT_ERR1;

                   //��ɫ
                   if(!(p[11] >= '0' && p[11] <= '3'))
                     return SMS_COLOR_ERR;

                   pPara->Color = p[11] - '0';
                   if(pPara->Color EQ 0)
                       pPara->Color = 1;

                   if((pPara->Color & Screen_Para.Base_Para.Color) EQ 0)
                       return SMS_COLOR_ERR;

				   //p[12]������Ϊ�߿�ѡ��---Ԥ������
				   if(Get_Chr_Index(p[12]) EQ 0xFF)
				       return SMS_BORDER_ERR;

				   pPara->SMS_Border_Flag = p[12];// - '0';

                   if(p[13] != '+')
                       return SMS_TXTHEAD_ERR;

                   pPara->SMS_Fix_Font_Flag = 1;

                   TxtOff = 14;
               }
               else
                 TxtOff = 11;

               pPara->Play_Counts = 1;

               SET_SUM(*pPara);
          }
          else
           {
              if(p[10] != '+')
              {
                  if(p[13] != '+')
                      return SMS_TXTHEAD_ERR;

                   TxtOff = 14;
              }
              else
                TxtOff = 11;
          }

          if(strlen(&p[TxtOff]) >= SMS_MAX_DATA_LEN)
            return SMS_LEN_ERR;

          if(SubIndex EQ 0)
		  {
		    //���֮ǰ����ʾ����
            OS_memset(SMS_WR_Buf.Data + sizeof(S_Txt_Para), 0, SMS_SUB_DATA_LEN * SMS_SUB_DATA_NUM,\
			          SMS_WR_Buf.Data,sizeof(SMS_WR_Buf.Data));
            //memcpy(SMS_WR_Buf.Data, pPara, sizeof(S_Txt_Para));
		  }
		  else
		  {
		    //��û����ʾ���ݣ�ֱ��׷�ӣ����ش���
		    if(Get_Buf_Bit(SMS_File_Flag.Flag, sizeof(SMS_File_Flag.Flag), index) EQ 0)
			  return SMS_SUB_INDEX_ERR;

            if(Read_Storage_Data(SDI_SMS_FILE_PARA + index, SMS_WR_Buf.Data, SMS_WR_Buf.Data, sizeof(SMS_WR_Buf.Data)) EQ 0)
		      return SMS_STORA_ERR;
		  }
			 	  
          mem_cpy(SMS_WR_Buf.Data + sizeof(S_Txt_Para) + SubIndex * SMS_SUB_DATA_LEN,&p[TxtOff],strlen(&p[TxtOff]) + 1,\
		          SMS_WR_Buf.Data,sizeof(SMS_WR_Buf.Data));
		  Write_Storage_Data(SDI_SMS_FILE_PARA + index, SMS_WR_Buf.Data, SMS_FILE_PARA_LEN);
 
	 	  //�޸Ĳ�����SMS_File_Flag
		  Set_Buf_Bit(SMS_File_Flag.Flag, sizeof(SMS_File_Flag.Flag), index, 1);
		  SET_SUM(SMS_File_Flag);
	      Write_SMS_File_Flag();
		           
		  return SMS_NO_ERR;
      }
      else if(p[1] EQ 'T' && p[2] EQ 'I' && p[3] EQ 'M') //Уʱ
      {
          if(Chk_Int_Str(&p[4], 15) EQ 0)
              return SMS_TIME_ERR;

          tempTime.Time[T_YEAR] = (INT8U)Str_2_Int(&p[4], 2); //��
          tempTime.Time[T_MONTH] = (INT8U)Str_2_Int(&p[6], 2);//��
          tempTime.Time[T_DATE] = (INT8U)Str_2_Int(&p[8], 2); //��
          tempTime.Time[T_HOUR] = (INT8U)Str_2_Int(&p[10], 2); //ʱ
          tempTime.Time[T_MIN] = (INT8U)Str_2_Int(&p[12], 2); //��
          tempTime.Time[T_SEC] = (INT8U)Str_2_Int(&p[14], 2); //��
          tempTime.Time[T_WEEK] = (INT8U)Str_2_Int(&p[16], 1); //����

          SET_HT(tempTime);
          SET_SUM(tempTime);

          if(Chk_Time(&tempTime) EQ 0)
              return SMS_TIME_ERR;

          Set_Cur_Time(tempTime.Time);
          return SMS_NO_ERR;
      }
      else if(p[1] EQ 'S' && p[2] EQ 'C' && p[3] EQ 'N') //������Ļ����
      {
        //��Ļ���
          if(Chk_Int_Str(&p[4], 4) EQ 0)
              return SMS_FORMAT_ERR;

           Base_Para.Width = Str_2_Int(&p[4], 4);

           if(!(p[8] EQ 'x' || p[8] EQ 'X' || p[8] EQ '*'))
             return SMS_FORMAT_ERR;

           //�߶�
           if(Chk_Int_Str(&p[9], 3) EQ 0)
             return SMS_FORMAT_ERR;

           Base_Para.Height = Str_2_Int(&p[9], 3); //�߶�

           if(p[12] != ',')
               return SMS_FORMAT_ERR;

           //��ɫ
           if(p[13] EQ '0' || p[13] EQ '1')
               Base_Para.Color = 0x01;
           else if(p[13] EQ '2')
               Base_Para.Color = 0x02;
           else if(p[13] EQ '3')
               Base_Para.Color = 0x03;
           else
               return SMS_COLOR_ERR;

           if(Check_Screen_Base_Para(&Base_Para) EQ 0)
             return SMS_SCN_BASE_ERR;

           //���ݼ���
           if(p[14] EQ '0')
               Scan_Para.Data_Polarity = 0x00;
           else if(p[14] EQ '1')
               Scan_Para.Data_Polarity = 0x01;
           else
               return SMS_SCN_DE_ERR;

           //OE����
           if(p[15] EQ '0')
               Scan_Para.OE_Polarity = 0x00;
           else if(p[15] EQ '1')
               Scan_Para.OE_Polarity = 0x01;
           else
               return SMS_SCN_OE_ERR;

           if(p[16] != ',')
               return SMS_FORMAT_ERR;

           //ɨ�跽ʽ
           if(Chk_Int_Str(&p[17], 4) > 0)
               scanMode = Str_2_Int(&p[17], 4);
		   else
		      return SMS_SCN_SCAN_ERR;

           Scan_Para.Direct = (scanMode%1000) / 100;
           Scan_Para.Cols_Fold = (scanMode %100) / 10;
           Scan_Para.Rows_Fold = (scanMode %10);
           Rows = (scanMode % 10000) / 1000;

           if(Rows EQ 0)
             Scan_Para.Rows = 16;
           else if(Rows EQ 1)
             Scan_Para.Rows = 8;
           else if(Rows EQ 2)
             Scan_Para.Rows = 4;
           else if(Rows EQ 3)
             Scan_Para.Rows = 2;
           else if(Rows EQ 4)
             Scan_Para.Rows = 1;
           else
             Scan_Para.Rows = 16;
		   
		   //���� 
		   //if(memcmp((INT8U *)&Screen_Para.Base_Para, (INT8U *)&Base_Para, sizeof(Screen_Para.Base_Para)) != 0)
		   {
		   //Ĭ������Ϊֻ��һ����Ŀ����ֻ��һ������
		     Prog_Para.Area_Num = 1;
			 Prog_Para.Border_Check = 0;
			 Prog_Para.Area[0].X = 0;
			 Prog_Para.Area[0].Y = 0;
			 Prog_Para.Area[0].X_Len = Base_Para.Width;
			 Prog_Para.Area[0].Y_Len = Base_Para.Height;
			 SET_SUM(Prog_Para);
			 Write_Prog_Para(0, (INT8U *)&Prog_Para.Head + 1, PROG_PARA_LEN);

		     Set_Screen_Replay_Flag(); //�ز���Ŀ��־
		     Set_Prog_Num(1);	//���ý�Ŀ����Ϊ1  
		   }

           memcpy(&Screen_Para.Base_Para, &Base_Para, sizeof(Base_Para));
           //memcpy(&Screen_Para.Scan_Para, &Scan_Para, sizeof(Scan_Para));
		   Screen_Para.Scan_Para.Data_Polarity = Scan_Para.Data_Polarity;
		   Screen_Para.Scan_Para.OE_Polarity = Scan_Para.OE_Polarity;
		   Screen_Para.Scan_Para.Direct = Scan_Para.Direct;
           Screen_Para.Scan_Para.Cols_Fold = Scan_Para.Cols_Fold;
           Screen_Para.Scan_Para.Rows_Fold = Scan_Para.Rows_Fold;
		   Screen_Para.Scan_Para.Rows = Scan_Para.Rows;
           SET_SUM(Screen_Para);

           Write_Screen_Para();

           return SMS_NO_ERR;

      }
      else if(p[1] EQ 'M' && p[2] EQ 'P' && p[3] EQ 'N')//���չ��˶��ź���
      {
          if(p[4] EQ '0' && (p[5] >= '0' && p[5] <= '9') && p[6] EQ '\0') //�������
					{
						if(p[5] EQ '0')
              memset(SMS_Phone_No.No, 0, sizeof(SMS_Phone_No.No));
						else
						{
							SubIndex = p[5] - '0' - 1;
							SMS_Phone_No.No[SubIndex][0] = 0;
            }
						
						SET_SUM(SMS_Phone_No);
						Write_Storage_Data(SDI_SMS_PHONE_NO, &SMS_Phone_No, sizeof(SMS_Phone_No));
						
						return SMS_NO_ERR;
          }
          else
          {
						 if(!(p[4] >= '1' && p[4] <= '9')) 
						     return SMS_FORMAT_ERR;
						 
             if(strlen(&p[5]) >= sizeof(SMS_Phone_No.No[0]))
                 return SMS_FORMAT_ERR;

						 SubIndex = p[4] - '1';
						 
						 mem_cpy(SMS_Phone_No.No[SubIndex], &p[5], strlen(&p[5]) + 1,\
         						 SMS_Phone_No.No[SubIndex], sizeof(SMS_Phone_No.No[SubIndex]));
						 SET_SUM(SMS_Phone_No);
						 Write_Storage_Data(SDI_SMS_PHONE_NO, &SMS_Phone_No, sizeof(SMS_Phone_No));
						 
             return SMS_NO_ERR;
					 }
      }
      else if(p[1] EQ 'D' && p[2] EQ 'E' && p[3] EQ 'L') //ɾ������
      {
          if(p[4] EQ '9' && p[5] EQ '9' && p[6] EQ '9') //ɾ�����ж���
          {
              Clear_All_SMS();
			  
			  //ɾ����ʾ���� 
			  Clear_Area_Data(&Show_Data_Bak, 0);
			  Clear_Area_Data(&Show_Data, 0);
              return SMS_NO_ERR;
          }
          else if(Chk_Int_Str(&p[4], 3))
          {
              index = Str_2_Int(&p[4], 3);
              if(index > MAX_SMS_NUM)
                  return SMS_INDEX_ERR;

              Set_Buf_Bit(SMS_File_Flag.Flag, sizeof(SMS_File_Flag.Flag), index, 0);
              SET_SUM(SMS_File_Flag);

              Write_SMS_File_Flag();
              return SMS_NO_ERR;
         }
         else
             return SMS_FORMAT_ERR;
      }
	  else if(p[1] EQ 'P' && p[2] EQ 'S' && p[3] EQ 'W')
	  {
	    if(p[4] != 0 && p[5] != 0 && p[6] != 0)
			{
				SMS_Phone_No.PSW[0] = p[4];
				SMS_Phone_No.PSW[1] = p[5];
				SMS_Phone_No.PSW[2] = p[6];

				SET_SUM(SMS_Phone_No);	
				Write_Storage_Data(SDI_SMS_PHONE_NO, &SMS_Phone_No, sizeof(SMS_Phone_No));

				return SMS_NO_ERR;
			}
			else
			{
				return SMS_FORMAT_ERR;
			}
	  }
      
	  return SMS_FORMAT_ERR;
  }
  else //��ѯ���ţ�
  {
    p = p + 3; //ָ�������3�ֽ�
    
	if(p[1] EQ 'V' && p[2] EQ 'E' && p[3] EQ 'R') //��ѯ�汾��
	{
	  pReStr[0] = 'V';
	  pReStr[1] = 'E';
	  pReStr[2] = 'R';

	  strcpy(&pReStr[3], SMS_VER);
	  return SMS_NO_ERR;
	}
	else if(p[1] EQ 'M' && p[2] EQ 'P' && p[3] EQ 'N') //��ѯ�绰����
	{
		pReStr[0] = 'M';
		pReStr[1] = 'P';
		pReStr[2] = 'N';	
		SubIndex = 3;
		
		for(i = 0; i < S_NUM(SMS_Phone_No.No); i ++)
		{
			pReStr[SubIndex ++] = ',';
			
			if(SubIndex + strlen(SMS_Phone_No.No[i]) >= 130)
				break;
			
		  strcpy(&pReStr[SubIndex], SMS_Phone_No.No[i]);
		  SubIndex += strlen(SMS_Phone_No.No[i]);
			
			//if(SubIndex + 1 >= 130)
				//break;
		}
		
		return SMS_NO_ERR;
	}

	 //��ѯ�汾�ţ�����
	return SMS_UNAVAIL_ERR;
  }
}

#if QT_EN == 0
//�յ���Ϣ����
void smsMessageProc(SM_PARAM* pMsg, INT8U Num)
{
  INT8U i;
  INT8U re;
  static char reStr[150];

  for(i = 0; i < 1; i ++)
  {
    if(Chk_PH_No(pMsg[i].TPA) EQ 0 &&\
	   memcmp(pMsg[i].TP_UD + 1, "168", 3) != 0) //�ֻ�������Ȩ��
	  continue;

    re = One_SMS_Proc(pMsg[i].TP_UD, reStr);

	if(re EQ SMS_UNAVAIL_ERR) //��Ч����ֱ�ӷ���
	  return;

	if(pMsg[i].TP_UD[0] EQ '*') //��ҪӦ��
	{
	   if(re EQ SMS_NO_ERR)
	   	 strcpy(SMS_WR_Buf.Data, "���óɹ�");//"OK,���óɹ�,ԭʼ��Ϣ:");								   
	   else
	   	 sprintf(SMS_WR_Buf.Data, "����ʧ��:%s", GetErrInfo(re));//"Err %d,����ʧ��,ԭʼ��Ϣ:", re);

	   //strcpy(SMS_WR_Buf.Data, "���");//"OK,���óɹ�,ԭʼ��Ϣ:");
	   /*
	   mem_cpy(SMS_WR_Buf.Data + strlen(SMS_WR_Buf.Data), pMsg[i].TP_UD, sizeof(pMsg[i].TP_UD),\
	           SMS_WR_Buf.Data, sizeof(SMS_WR_Buf.Data));
	*/
	}
	else if(pMsg[i].TP_UD[0] EQ '?') //��ѯ����
	{
	   if(re EQ SMS_NO_ERR)
		 strcpy(SMS_WR_Buf.Data, reStr);
	   else
	     sprintf(SMS_WR_Buf.Data, "��ѯʧ��");//"Err %d,����ʧ��,ԭʼ��Ϣ:", re);
	}

	if(re != SMS_UNAVAIL_ERR)
	{/*		  
		mem_cpy(pMsg[i].TP_UD, SMS_WR_Buf.Data, sizeof(pMsg[i].TP_UD),\
		       pMsg[i].TP_UD, sizeof(pMsg[i].TP_UD)); 
		*/
		strcpy(pMsg[i].TP_UD, SMS_WR_Buf.Data); 
		gsmSendMessage(&(pMsg[i]));
	}
  }

}
#endif
#endif

