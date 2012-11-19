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
J    �� ��ʾ�ؼ��� 0 �C 9  �����ո���
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
*#1(�̶�3��) + LSET(�̶�4��) + �������(4��) + ��x��(Сд,�̶�����) + ��
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
3�� ָ������ݴ���ĺ���μ��±�
��������  ���ܵ�ԭ��
OK  ָ��ִ�гɹ�

E002  �޷�ʶ�𣬻�֧�ֵ�ָ��
E004  ָ��������󣬼�ָ���ʽ��ȫ��ȷ�����ǲ�������Э��涨����ַ���
���������Ϣʱ�������ID ����400��
E005  ָ������޷�ʶ����ó������ֵĵط���������ĸ��
E007  ��������ʱ����ȳ������Χ��
E008  ��������ʱ���߶ȳ������Χ��
E009  ��������ʱ���ܵ����������ƿ���֧�ֵ���������
E010  ָ����쳣���籾���ܳ���Ӧ����10���ַ���ȴ������9����11����
E110  ׷����Ϣʱ��˳����󣬻����û��ԭʼ��Ϣֱ��׷�ӵ������
*/
INT16U Read_Cur_SMS_File_Para(void *pDst, void *pDst_Start, INT16U DstLen)
{
  S_Txt_Para *pPara;

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

  pPara->Txt_Flag = TXT_SMS_NORMAL;
  }
  else if(SMS_Cur_No.No EQ 1)
  {
  pPara->Txt_Flag = TXT_SMS_BK_FILE;
  pPara->File_No = 0x00;
  }

  //memcpy(pDst, pDst + 1 ,sizeof(S_Txt_Para) - CHK_BYTE_LEN);

  strcpy((char *)SMS_Data.Data, (char *)"��ð��������ܺð����������");

  return sizeof(S_Txt_Para);
  //pPara->
}

#endif

