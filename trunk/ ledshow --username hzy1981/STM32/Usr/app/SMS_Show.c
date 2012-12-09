#define SMS_SHOW_C
#include "Includes.h"

#if SMS_EN
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
      memset(SMS_File_Flag.Flag, 0, sizeof(SMS_File_Flag.Flag));

      SMS_File_Flag.Flag[0] = 0x03; //������
    }

    SET_SUM(SMS_File_Flag);
    SET_HT(SMS_File_Flag);

    //��ȡ��Ч����
    Len = Read_Storage_Data(SDI_SMS_PHONE_NO, &SMS_Phone_No, &SMS_Phone_No, sizeof(SMS_Phone_No));
    if(Len EQ 0)
      memset(&SMS_Phone_No, 0, sizeof(SMS_Phone_No));

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

/*
1���򻯷��ͣ�
  ��ʽ��*#1A  nnn ����
  *#1A :  �̶�����
  nnn   :  ������ϢID����Ч��ΧΪ000 �C 999����3λ
  ����  :  Ҫ��ʾ�����ݣ��63���ַ�
//��ȡ��ǰ�����ļ���ת��ΪS_Txt_Para���Ͳ���

2����ͨ���ͣ�
��ʽ��*#1B  nnn  I  J   K   L  ����
*#1B ���̶�����
nnn  ����ϢID
I     �� ׷��������Ĭ����0
J    �� ��ʾ�ؼ��� 0 �C 9  �����ո�����
K    �� �ٶȣ�0-9����Խ��Խ��
L    ��ͣ��ʱ�䣬0-9
���� �� Ҫ��ʾ�����ݣ��58���ַ�

����*#1B0010821�����ǵ�001����Ϣ���ؼ�=���꣬�ٶ�=2��ͣ��ʱ��=1

����  ��ʽ��ϸ˵��
1����*#1������Ϊ�̶����ڣ�ÿ���Ϸ���ָ���������3����ĸ��ͷ�����򱻶���
2������ϢID��  ����Ч��Χ000-399�����ɴ�400����Ϣ������ʱ��С������������
3����׷����������0=��׷�ӡ�1-2������Ϣ��Ҫ׷��1��2�β�������A/B ����ʱ����Ϣ
4������ʾ�ؼ���  ����Ч��Χ:  ����0-9��Сд��ĸa-z����д��ĸA-I�����庬�������
����
5�����ٶȡ�  ��0-9-Z������Խ��Խ��
6����ͣ��ʱ�䡱  ��0-9-X��0-9 ����0-9 �룬A=10�룬B=15�룬C=20���Դ�����(��ĸ��10�뿪ʼ��ÿ������5��)�����ΪX��

����  ����ָ���ʽ
ɾ��һ����Ϣ��
*#1(�̶�3��) + GDEL(�̶�4��)  + ��ϢID(3��)

ɾ��ȫ����Ϣ��
*#1(�̶�3��) + HALL(�̶�4��)  + 999(�̶�3��)

Уʱ��
*#1(�̶�3��) + ITIM(�̶�4��)  + ������ʱ�������ڣ�15�֣�
-- �磺201107181301385 ����2011��7��18��13ʱ01��38��������

�������ã�
*#1(�̶�3��) + LSET(�̶�4��) + ��������(4��) + ��x��(Сд,�̶�����) + ��
�ߵ���(3��) + ��,��(�̶�����) + ��ɫ����(1��) + ���ݼ���(1��) + OE��
��(1��) + ɨ�跽ʽ(2��) + ��˳��(1��)

ɨ�跽ʽ���壺00=16ɨ(���ڳ���)��41=4ɨ(P10���쳣��)

����*#1LSET0128x016,101410  ����Ϊ8������(128��*16��)��P10����ɨ�跽ʽ(4.1)��
���ݼ���=0��OE����=1

  ����*#1LSET0128x016,200000 ����Ϊ8������������16ɨ�����ݺ�OE��Ϊ��

�ģ�  ָ���
1�� �������ݽ��涨��ָ��صĸ�ʽ�������յ�ָ����Ƿ�ظ����ţ�ȡ���ڻ���
�ȼ�����ע�⣺������ô��ڷ���ָ����һֱ���أ������Ի��Եȼ���
2�� ����յ��޷�ʶ��Ķ��ţ����Զ��������������κ����ݡ�
3�� ָ������ݴ����ĺ���μ��±�
��������  ���ܵ�ԭ��
OK  ָ��ִ�гɹ�

E002  �޷�ʶ�𣬻�֧�ֵ�ָ��
E004  ָ��������󣬼�ָ���ʽ��ȫ��ȷ�����ǲ�������Э��涨����ַ���
���������Ϣʱ�������ID ����400��
E005  ָ������޷�ʶ����ó������ֵĵط���������ĸ��
E007  ��������ʱ�����ȳ������Χ��
E008  ��������ʱ���߶ȳ������Χ��
E009  ��������ʱ���ܵ����������ƿ���֧�ֵ���������
E010  ָ����쳣���籾���ܳ���Ӧ����10���ַ���ȴ������9����11����
E110  ׷����Ϣʱ��˳����󣬻����û��ԭʼ��Ϣֱ��׷�ӵ������
*/
INT16U Read_Cur_SMS_File_Para(void *pDst, void *pDst_Start, INT16U DstLen)
{
  S_Txt_Para *pPara;
  INT8U subIndex, i, Num0 = 1, Num1;
  INT16U index;

  Find_Next_SMS_File_No();

  if(SMS_Cur_No.No EQ NULL_SMS_NO) //�Ѿ����ŵ����һ���ˣ�����ͷ��ʼ����
  {
      Find_Next_SMS_File_No();
      if(SMS_Cur_No.No EQ NULL_SMS_NO)
        return 0;
  }
/*
  if(Read_Storage_Data(SDI_SMS_FILE_PARA + SMS_Cur_No.No, Pub_Buf, Pub_Buf, sizeof(Pub_Buf)))
  {

  }
  */
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


  One_SMS_Proc((char *)"+P0002AB0901#ijk���Ǹ��󱿵�������ë���ɣ�������������,����");//, (S_Txt_Para *)pDst, (char *)SMS_Data.Data, &index, &subIndex);

  //------����Ӧ�����С---------
  if(((S_Txt_Para *)pDst)->SMS_Fix_Font_Flag EQ 0) //û�й̶������С
  {
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

    if(strstr(No, SMS_Phone_No.No[i]) != '\0')
        break;
  }

  if(num EQ 0 || i < S_NUM(SMS_Phone_No.No))
      return 1;
  else
      return 0;

}

//����һ����������
INT8U One_SMS_Proc(char *p)
{
  int index,temp,i;
  INT8U Rows,TxtOff;
  INT8U SubIndex;
  S_Scan_Para Scan_Para = {0};
  S_Screen_Base_Para Base_Para = {0};
  S_Time tempTime;
  INT16U scanMode;
  S_Txt_Para *pPara;


  pPara = (S_Txt_Para *)SMS_WR_Buf.Data;
  pPara->SMS_Fix_Font_Flag = 0;
  pPara->Color = Screen_Para.Base_Para.Color;

  if(p[0] EQ '+' || p[0] EQ '*') //'+'��ʾ����Ӧ��'*'��ʾ��ҪӦ��
  {
    if(p[1] EQ '#') //�򵥷�ʽ
      {
        if(Chk_Int_Str(&p[2], 3) EQ 0)
            return SMS_INDEX_ERR;

        index = Str_2_Int(&p[2], 3);

        if(index > MAX_SMS_NUM)
            return SMS_INDEX_ERR;

        //*pIndex = (INT16U)index;
        //*pSubIndex = 0;

        if(strlen(&p[5]) >= SMS_MAX_DATA_LEN)
            return SMS_LEN_ERR;

        pPara->In_Mode = 0x01;
        pPara->Out_Mode = 0x01;
        pPara->Play_Counts = 0x01;
        pPara->Stay_Time = 10;

        //strcpy(pUSC, &p[4]);
		memset(SMS_WR_Buf.Data, 0, sizeof(SMS_WR_Buf.Data));
		memcpy(SMS_WR_Buf.Data, pPara, sizeof(S_Txt_Para));
		
		
		mem_cpy(SMS_WR_Buf.Data + sizeof(S_Txt_Para), &p[5],strlen(&p[5]),\
		      SMS_WR_Buf.Data,sizeof(SMS_WR_Buf.Data));
		Write_Storage_Data(SDI_SMS_FILE_PARA + index, SMS_WR_Buf.Data, SMS_FILE_PARA_LEN);

		//�޸Ĳ�����SMS_File_Flag
		Set_Buf_Bit(SMS_File_Flag.Flag, sizeof(SMS_File_Flag.Flag), index, 1);
		SET_SUM(SMS_File_Flag);
        Write_SMS_File_Flag();

		return SMS_NO_ERR;
      }
      else if(p[1] EQ 'P') //+T0002AB09
      {
          if(Chk_Int_Str(&p[2], 3) EQ 0) //��Ŵ���
              return SMS_INDEX_ERR;

           index = Str_2_Int(&p[2], 3);

           if(index > MAX_SMS_NUM)
               return SMS_INDEX_ERR;

           //*pIndex = (INT16U)index;

           //---���Ŵ���------------
           if(!(p[5] >= '0' && p[5] <= '2'))
               return SMS_PLAY_COUNTS_ERR;

           SubIndex = (p[5] - '0'); //׷�Ӵ���
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
               else if(p[6] >= 'A' && p[6] <= 'Z')
                   temp = 10 + p[6] - 'A';
               else
                   temp = 10 + 26 + p[6] - 'a';

               pPara->In_Mode = (INT8U)temp;

               //----�˳���ʽ----
               if(!((p[7] >= '0' && p[7] <= '9') ||\
                    (p[7] >= 'A' && p[7] <= 'Z') ||\
                    (p[7] >= 'a' && p[7] <= 'z')))
                   return SMS_OUT_MODE_ERR;

               if(p[7] >= '0' && p[7] <= '9')
                   temp = p[7] - '0';
               else if(p[7] >= 'A' && p[7] <= 'Z')
                   temp = 10 + p[7] - 'A';
               else
                   temp = 10 + 26 + p[7] - 'a';

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

               if(p[10] != '#')
               {
                   //����
                   if(!(p[10] >= '0' && p[10] <= '2'))
                     return SMS_FONT_ERR;

                   pPara->Font_Size = p[10] - '0';

                   //��ɫ
                   if(!(p[11] >= '0' && p[11] <= '3'))
                     return SMS_COLOR_ERR;

                   pPara->Color = p[11] - '0';
                   if(pPara->Color EQ 0)
                       pPara->Color = 1;

                   if((pPara->Color & Screen_Para.Base_Para.Color) EQ 0)
                       return SMS_COLOR_ERR;

                   if(p[12] != '#')
                       return SMS_TXTHEAD_ERR;

                   pPara->SMS_Fix_Font_Flag = 1;

                   TxtOff = 13;
               }
               else
                 TxtOff = 11;

               pPara->Play_Counts = 1;

               SET_SUM(*pPara);
          }
          else
           {
              if(p[10] != '#')
                  return SMS_TXTHEAD_ERR;

              TxtOff = 11;
          }

          if(strlen(&p[TxtOff]) >= SMS_MAX_DATA_LEN)
            return SMS_LEN_ERR;

          if(SubIndex EQ 0)
		  {
            memset(SMS_WR_Buf.Data, 0, sizeof(SMS_WR_Buf.Data));
		    memcpy(SMS_WR_Buf.Data, pPara, sizeof(S_Txt_Para));
		  }
		  else
		  {
		    if(Read_Storage_Data(SDI_SMS_FILE_PARA + index, SMS_WR_Buf.Data, SMS_WR_Buf.Data, sizeof(SMS_WR_Buf.Data)) > 0)
			  return SMS_STORA_ERR;
		  }
		  
	      mem_cpy(SMS_WR_Buf.Data + sizeof(S_Txt_Para) + SubIndex * SMS_SUB_DATA_LEN,&p[TxtOff],strlen(&p[TxtOff]),\
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
        //��Ļ����
          if(Chk_Int_Str(&p[4], 4) EQ 0)
              return SMS_FORMAT_ERR;

           Base_Para.Width = Str_2_Int(&p[4], 4);

           if(p[8] EQ 'x' || p[8] EQ 'X')
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
           else if(p[12] EQ '3')
               Base_Para.Color = 0x03;
           else
               return SMS_COLOR_ERR;

           if(Check_Screen_Base_Para(&Base_Para) EQ 0)
             return SMS_SCN_BASE_ERR;

           //���ݼ���
           if(p[14] EQ 0)
               Scan_Para.Data_Polarity = 0x00;
           else if(p[14] EQ 1)
               Scan_Para.Data_Polarity = 0x01;
           else
               return SMS_SCN_DE_ERR;

           //OE����
           if(p[15] EQ 0)
               Scan_Para.OE_Polarity = 0x00;
           else if(p[15] EQ 1)
               Scan_Para.OE_Polarity = 0x01;
           else
               return SMS_SCN_OE_ERR;

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
      else if(p[1] EQ 'P' && p[2] EQ 'N')//���չ��˶��ź���
      {
          if(p[3] EQ 0) //������к���
          {
              memset(SMS_Phone_No.No, 0, sizeof(SMS_Phone_No));
              SET_SUM(SMS_Phone_No);

              Write_Storage_Data(SDI_SMS_PHONE_NO, &SMS_Phone_No, sizeof(SMS_Phone_No));
          }
          else
          {
             if(strlen(&p[3]) >= sizeof(SMS_Phone_No.No[0]))
                 return SMS_FORMAT_ERR;

             //Ѱ��һ������λ�ô洢����
             for(i = 0; i < (int)S_NUM(SMS_Phone_No.No); i ++)
             {
                 if(strlen(SMS_Phone_No.No[i]) EQ 0)
                 {
                     strcpy(SMS_Phone_No.No[i], &p[3]);
                     SET_SUM(SMS_Phone_No);

                     Write_Storage_Data(SDI_SMS_PHONE_NO, &SMS_Phone_No, sizeof(SMS_Phone_No));
                     break;
                 }
             }

             if(i EQ S_NUM(SMS_Phone_No.No))
                 return SMS_PN_FULL_ERR; //û�п���λ����
          }

          return SMS_NO_ERR;
      }
      else if(p[1] EQ 'D' && p[2] EQ 'E' && p[3] EQ 'L') //ɾ������
      {
          if(p[4] EQ '9' && p[5] EQ '9' && p[6] EQ '9') //ɾ�����ж���
          {
              memset(SMS_File_Flag.Flag, 0, sizeof(SMS_File_Flag.Flag));
              SET_SUM(SMS_File_Flag);

              Write_SMS_File_Flag();
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
      
	  return SMS_FORMAT_ERR;
  }
  else
    return SMS_UNAVAIL_ERR;


}

#if QT_EN == 0
//�յ���Ϣ����
void smsMessageProc(SM_PARAM* pMsg, INT8U Num)
{
  INT8U i;
  INT8U re;

  for(i = 0; i < 1; i ++)
  {
    re = One_SMS_Proc(pMsg[i].TP_UD);
	
	if(pMsg[i].TP_UD[0] EQ '*') //��ҪӦ��
	{
	   if(re EQ SMS_NO_ERR)
	   	 strcpy(SMS_WR_Buf.Data, "OK");//"OK,���óɹ�,ԭʼ��Ϣ:"); 											   
	   else
	   	 sprintf(SMS_WR_Buf.Data, "ERR %d", re);//"Err %d,����ʧ��,ԭʼ��Ϣ:", re);

	   //strcpy(SMS_WR_Buf.Data, "���");//"OK,���óɹ�,ԭʼ��Ϣ:");
	   /*
	   mem_cpy(SMS_WR_Buf.Data + strlen(SMS_WR_Buf.Data), pMsg[i].TP_UD, sizeof(pMsg[i].TP_UD),\
	           SMS_WR_Buf.Data, sizeof(SMS_WR_Buf.Data));
	*/		  
	   mem_cpy(pMsg[i].TP_UD, SMS_WR_Buf.Data, sizeof(pMsg[i].TP_UD),\
	           pMsg[i].TP_UD, sizeof(pMsg[i].TP_UD)); 
	   
	   gsmSendMessage(&(pMsg[i]));
	}
  }

}
#endif
#endif
