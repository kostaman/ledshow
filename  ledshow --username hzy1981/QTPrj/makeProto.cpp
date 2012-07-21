#define MAKE_PROTO_C
#include "..\Stm32\usr\app\includes.h"
#include "makeProto.h"
#include <QString>
#include <QObject>
#include <QSettings>
#include <QMessageBox>
#include <QImage>
#include "screenProperty.h"
#include "mainwindow.h"

extern MainWindow *w;
extern QSettings settings;

extern int linePosi[MAX_LINE_NUM];
extern int pagePosi[MAX_LINE_NUM];
S_Show_Data protoShowData;

S_Screen_Para comScreenPara; //ͨ�Ų���

#define PROTO_DATA_BUF_LEN (2000*1000)
/*
    if(height % 8 EQ 0)
       tmpLen = width * height/ 8;
    else
       tmpLen = width * (height / 8 + 1);
*/
//#define BLOCK_SHOW_DATA_LEN (BLOCK_DATA_LEN - 20)

/*
#define FLEN   0x01
#define FADDR  0x03
#define FSEQ   0x05
#define FSEQ0  0x06
#define FCMD  0x07
#define FDATA  0x09

1	0x5A	֡ͷ���ֽ�
2	Len0	֡���ȵ��ֽ�(��֡ͷ��֡β)
3	Len1	֡���ȸ��ֽ�
4	Addr0	��ַ���ֽ�,
5	Addr1	��ַ���ֽ�
6	Seq	֡���, 0-255 ѭ������,�ط���������Ų���
7	Seq0	֡�����,0-255 ѭ������
8	Cmd0	��������ֽ�
9	Cmd1	��������ֽ�
10	��	֡����������
        ��
        CS0	У������ֽ�,��֡ͷ��CS0ǰһ���ֽڵĺ�
        CS1	У������ֽ�
        0xAA	֡β

      Cmd0����:
0x01 ����������ɫ���ɶ���д
0x02 ����ַ���ɶ���д
0x03 ��IP�������ɶ���д
0x04 ͨ�����ʣ��ɶ���д
0x05 ��ʱ���ػ����ɶ���д
0x06 ��ǰʱ�䣬�ɶ���д
0x07 �������ã��ɶ���д
0x08 ��Ŀ�����ã��ɶ���д
0x09 ��Ŀ�������ã��ɶ���д
0x0A �����������ã��ɶ���д
0x0B ����Ϣ(ֻ��)
0x0C �̼�����

  Cmd1����:
Bit0->Bit7 �������λ�����λ
Bit2: 0 ��ʾ��վ����������֡��1��ʾ��վ������Ӧ��֡
Bit1: 0 ��ʾ����Ӧ��֡��1��ʾ�쳣Ӧ��֡
Bit0:0 ��ʾ�޺���֡��1��ʾ�к���֡
Bit3->Bit7 ����

 */

//����һ��֡��ԭʼ����
int _makeFrame(char *data, int dataLen, INT16U addr, char cmd0, char cmd1, char seq, INT16U seq0, char *pDst)
{
  pDst[0] = FRAME_HEAD;//֡ͷ
  memcpy(pDst + FADDR, &addr, 2); //��ַ

  memcpy(pDst + FDATA, data, dataLen);

  //������+33
  //for(int i = 0; i < dataLen; i ++)
      //pDst[FDATA + i] += 0x33;

  pDst[FSEQ] = seq;
  memcpy(pDst + FSEQ0, &seq0, sizeof(seq0));

  pDst[FCMD] = cmd0; //�����ֽڵĿ�����
  pDst[FCMD + 1] = cmd1;

  dataLen += F_NDATA_LEN; //������ + �������� = ����֡��
  memcpy(pDst + FLEN, &dataLen, 2);

  INT16U sum = Sum_2Bytes((INT8U *)pDst, dataLen - 3); //��3���ֽ���У��ͺ�֡β
  memcpy((char *)pDst + dataLen - 3, (char *)&sum, 2);
  pDst[dataLen - 1] = FRAME_TAIL;

  return dataLen;
}

//����һ��֡
//dataΪ������,dataLen�����򳤶�
//cmd������
//seq���к�
//pDstΪĿ�껺����
int makeFrame(char *data, int dataLen, char cmd, char seq, char *pDst)
{
  int len;
  INT16U seq0;
  char type,cmd1 = 0;

  pDst[0] = FRAME_HEAD;//֡ͷ

  memcpy(pDst + FADDR, &Screen_Para.COM_Para.Addr, 2); //��ַ

  if(seq != frameInfo.seq) //һ���µ�֡��
  {
      frameInfo.seq = seq;
      frameInfo.seq0 = 0;
      frameInfo.off = 0;
  }

  if(dataLen >  0 && frameInfo.off >= dataLen)//>
      return 0;

  seq0 = frameInfo.seq0;
  if(cmd EQ (C_PROG_DATA | WR_CMD)) //����������ʾ�����������Ҫ��֡
  {
    if(frameInfo.seq0 EQ 0) //��һ֡ȫ������ʾ����!!
    {
        frameInfo.len = 0;
        type = data[0];
        len = Get_Show_Para_Len(type); //��һ֡����
        len += BORDER_DATA_LEN;

        frameInfo.off = 0;
        if(dataLen > len)
        {
            cmd1 |= 0x01;
            frameInfo.seq0 ++;//�к���֡
        }
    }
    else
    {
        if(frameInfo.off + BLOCK_SHOW_DATA_LEN >= dataLen)
        {
          len = dataLen - frameInfo.off; //����֡����
          frameInfo.seq0 = 0; //û�к���֡��
        }
        else
        {
          len = BLOCK_SHOW_DATA_LEN;
          cmd1 |= 0x01;
          frameInfo.seq0 ++; // �к���֡
        }
    }
  }
  else
      len = dataLen;

  memcpy(pDst + FDATA, data + frameInfo.off, len);

  //������+33
  for(int i = 0; i < len; i ++)
      pDst[FDATA + i] += 0x33;

  frameInfo.off += len;

  pDst[FSEQ] = frameInfo.seq;
  memcpy(pDst + FSEQ0, &seq0, sizeof(seq0));
  //pDst[FSEQ0] = frameInfo.seq0;
  pDst[FCMD] = cmd; //�����ֽڵĿ�����
  pDst[FCMD + 1] = cmd1;

  len += F_NDATA_LEN; //������ + �������� = ����֡��
  memcpy(pDst + FLEN, &len, 2);

  INT16U sum = Sum_2Bytes((INT8U *)pDst, len - 3); //��3���ֽ���У��ͺ�֡β
  memcpy((char *)pDst + len - 3, (char *)&sum, 2);
  pDst[len - 1] = FRAME_TAIL;

  return len;
}

#if 0
//����Э������
//pFrame��len��ʾ֡��ʼ��֡��
//mode��ʾ���͵�ģʽ��0��ʾ���ڣ�1��ʾu�̣�2��ʾ��̫��
INT8U sendProtoData(char *pFrame, int len)
{
    int i = 0;

    INT8U mode = comScreenPara.Com_Mode;

    if(mode EQ PREVIEW_MODE)//Ԥ��ģʽ
    {
      Rcv_Frame_Proc(CH_SIM, (INT8U *)pFrame, (INT16U)len); //���պ��������ڷ�������£�������д����Ӳ���ļ���ģ��д��EEROM
    }
    else if(mode EQ SIM_MODE) //����ģʽ
    {
      for(i = 0; i < len; i ++)
          Com_Rcv_Byte(CH_SIM, *(pFrame + i));
/*
      QTimer t;
      t.start();
      while(t.elapsed() < 250)
      {
          QCoreApplication::processEvents();
          usleep(10000);//sleep��usleep���Ѿ�obsolete������ʹ��nanosleep���� }

      }*/
    }
    else if(mode EQ COM_MODE)//����ͨ��ģʽ
    {

    }
    else if(mode EQ ETH_MODE)//��̫��ģʽ
    {

    }
    else if(mode EQ GPRS_MODE)
    {

    }
    else if(mode EQ UDISK_MODE)
    {

    }

    return 1;
}
#endif

//��ȡ�ļ�����
//width,height������ʾ�����Ŀ�Ⱥ͸߶�
//fileStr�ļ����ַ���
//bufĿ�����ݻ�����
int getFileParaFromSettings(INT8U Prog_No, INT8U Area_No, INT8U File_No, INT16U width, INT16U height, QString fileStr, char *buf, int bufLen)
{
    int type, tmpLen;
    U_File_Para filePara;
    S_Screen_Para screenParaBak;
    S_Prog_Para progParaBak;
    int len = 0;
    int borderHeight = 0;

    type = checkStrType(fileStr);

    saveScreenPara(screenParaBak);
    saveProgPara(progParaBak);

    memset(&filePara, 0, sizeof(filePara));
    memset(protoShowData.Color_Data, 0, sizeof(protoShowData.Color_Data));

    //���ò���--
    resetShowPara(width, height, Screen_Para.Base_Para.Color);

    filePara.Pic_Para.Prog_No = Prog_No;
    filePara.Pic_Para.Area_No = Area_No;
    filePara.Pic_Para.File_No = File_No;


    getBorderParaFromeSettings(fileStr, filePara);

    if(filePara.Pic_Para.Border_Check > 0)
    {
        //INT8U Type = filePara.Pic_Para.Border_Type;
        borderHeight = filePara.Pic_Para.Border_Height;//Get_Simple_Border_Height(filePara.Pic_Para.Border_Type);//Simple_Border_Data[Type].Height;//Get_Area_Border_Height(Area_No);

        width = width - borderHeight*2;
        height = height - borderHeight*2;
    }

    //getBorderParaFromeSettings(fileStr, filePara);// ��ȡ�߿����

    if(type EQ PIC_STEXT_PROPERTY || type EQ PIC_MTEXT_PROPERTY || type EQ PIC_TABLE_PROPERTY)
    {
      len = sizeof(S_Pic_Para) - CHK_BYTE_LEN; //�����Ĳ������ȣ�������ͷβУ��

      settings.beginGroup(fileStr);
      settings.beginGroup("textEdit");
      QString picStr = settings.value("text").toString();
      settings.endGroup();

      bool smLineFlag;
      if(type EQ PIC_MTEXT_PROPERTY)
      {
          settings.beginGroup("smLine");
          smLineFlag = settings.value("smLineCheck").toBool();
          settings.endGroup();
      }
      else
          smLineFlag = false; //����
      settings.endGroup();

      int moveFlag = checkSLineMoveLeftContinuous(fileStr);
      int lineNum,pageNum;
      QImage image;
      //�����ı���ͼ��
      if(type EQ PIC_TABLE_PROPERTY)
      {
        image = getTableImage(width, height, picStr, &pageNum);
      }
      else
      {
          if(moveFlag != MOVE_LEFT_CONTINUOUS)
          {
              image = getTextImage(width, picStr, &lineNum, linePosi);
              //���������
              pageNum = getTextPageNum(smLineFlag, moveFlag, image.height(), width, height, lineNum, linePosi, pagePosi);
          }
          else
          {
              pageNum = getSLineTextPageNum(picStr, width);
              //image = getSLineTextImage(picStr, width,height,page);
          }
      }

      getPicParaFromSettings(fileStr, filePara);
      filePara.Pic_Para.SNum = pageNum;
      memcpy(buf, (char *)&filePara.Pic_Para.Head + 1, sizeof(S_Pic_Para)); //ǰһ���ֽ���ͷ��������

      getBorderData(fileStr, (INT8U *)buf + len, bufLen); //�߿�����
      len += BORDER_DATA_LEN;

      QImage imageBk;
      for(int i = 0; i < pageNum; i ++)
      {
          //��ȡÿҳ��ͼ��
          if(type EQ PIC_TABLE_PROPERTY)
          {
             imageBk = getTablePageImage(image, width, height, i);
          }
          else
          {
              if(moveFlag != MOVE_LEFT_CONTINUOUS)
                imageBk = getTextPageImage(smLineFlag, image, width, height, i, pagePosi);
              else
                imageBk = getSLineTextImage(picStr, width,height,i);
          }

          //��ȡ��ͼ�εĿ�Ⱥ͸߶�Ӧ�úͷ����Ŀ�Ⱥ͸߶�һ��
          if(imageBk.width() != width || imageBk.height() != height)
          {
              ASSERT_FAILED();
          }

           //ת��ͼ�����ݵ�protoShowData��
          //memset(protoShowData.Color_Data, 0, sizeof(protoShowData.Color_Data));
          //Set_Area_Border_Out(0);

          //Screen_Para.Base_Para.Width -=  2*borderHeight; //getTextShowData������Ҫʹ�õ���Ļ��ȣ��߶ȵȣ������Ҫ���øĲ���
          //Screen_Para.Base_Para.Height -= 2*borderHeight;

          resetShowPara(width, height, Screen_Para.Base_Para.Color);
          //imageBk.save("d:\\mkprotoimag.png");
          getTextShowData(imageBk, &protoShowData, 0, 0);

          //Screen_Para.Base_Para.Width +=  2*borderHeight;
          //Screen_Para.Base_Para.Height += 2*borderHeight;
/*
          if(height % 8 EQ 0)
             tmpLen = width * height/ 8;
          else
             tmpLen = width * (height / 8 + 1);
*/
          tmpLen = GET_TEXT_LEN(width, height);
          tmpLen = tmpLen * Get_Screen_Color_Num();
          if(len + tmpLen >= bufLen)
          {
              ASSERT_FAILED();
              return len;
          }

          memcpy(buf + len, protoShowData.Color_Data, tmpLen);
          len += tmpLen;
      }
    }
    else if(type EQ CLOCK_PROPERTY) //ʱ��
    {
        getClockParaFromSettings(fileStr, filePara);
        QImage image = getLineTextImage(fileStr);

        filePara.Clock_Para.Text_Width = image.size().width();
        filePara.Clock_Para.Text_Height = image.size().height();
        filePara.Clock_Para.SNum = 1;

        mem_cpy((INT8U *)&Prog_Status.File_Para[0], &filePara, sizeof(filePara), (INT8U *)&Prog_Status.File_Para[0], sizeof(Prog_Status.File_Para[0]));

        S_Point Point;
        Get_Clock_Text_Point(width, height, &filePara.Clock_Para, &Point);
        filePara.Clock_Para.Text_X = Point.X + borderHeight;
        filePara.Clock_Para.Text_Y = Point.Y + borderHeight;

        memcpy(buf, (char *)&filePara.Clock_Para.Head + 1, sizeof(S_Clock_Para)); //ǰһ���ֽ���ͷ��������
        len = sizeof(S_Clock_Para) - CHK_BYTE_LEN;

        getBorderData(fileStr, (INT8U *)buf + len, bufLen); //�߿�����
        len += BORDER_DATA_LEN;

        resetShowPara(image.size().width(), image.size().height(), Screen_Para.Base_Para.Color);
        getTextShowData(image, &protoShowData, 0, 0);

        tmpLen = GET_TEXT_LEN(image.size().width(),image.size().height());
        tmpLen = tmpLen * Get_Screen_Color_Num();
        memcpy(buf + len, protoShowData.Color_Data, tmpLen);
        len +=tmpLen;
    }
    else if(type EQ LUN_PROPERTY) //ũ��
    {
        getLunParaFromSettings(fileStr, filePara);
        QImage image = getLineTextImage(fileStr);

        //image.save("d:\\time.png");
        QSize size = image.size();

        filePara.Lun_Para.Text_Width = size.width();
        filePara.Lun_Para.Text_Height = size.height();
        filePara.Lun_Para.SNum = 1;

        mem_cpy((INT8U *)&Prog_Status.File_Para[0], &filePara, sizeof(filePara), (INT8U *)&Prog_Status.File_Para[0], sizeof(Prog_Status.File_Para[0]));

        S_Point P0;
        Get_Lun_Text_Point(0, width, height, P0);
        filePara.Lun_Para.Text_X = P0.X + borderHeight;
        filePara.Lun_Para.Text_Y = P0.Y + borderHeight;

        memcpy(buf, (char *)&filePara.Lun_Para.Head + 1, sizeof(S_Lun_Para)); //ǰһ���ֽ���ͷ��������
        len = sizeof(S_Lun_Para) - CHK_BYTE_LEN;

        getBorderData(fileStr, (INT8U *)buf + len, bufLen); //�߿�����
        len += BORDER_DATA_LEN;

        resetShowPara(image.size().width(), image.size().height(), Screen_Para.Base_Para.Color);
        getTextShowData(image, &protoShowData, 0, 0);

        tmpLen = GET_TEXT_LEN(image.size().width(),image.size().height());
        tmpLen = tmpLen * Get_Screen_Color_Num();
        memcpy(buf + len, protoShowData.Color_Data, tmpLen);
        len +=tmpLen;

    }
    else if(type EQ TIME_PROPERTY) //ʱ��
    {
        getTimeParaFromSettings(fileStr, filePara);
        QImage image = getLineTextImage(fileStr);
        QSize size = image.size();

        filePara.Time_Para.Text_Width = size.width();
        filePara.Time_Para.Text_Height = size.height();
        filePara.Time_Para.SNum = 1;

        mem_cpy((INT8U *)&Prog_Status.File_Para[0], &filePara, sizeof(filePara), (INT8U *)&Prog_Status.File_Para[0], sizeof(Prog_Status.File_Para[0]));

        S_Point P0;
        Get_Time_Text_Point(0, width, height, P0);
        filePara.Time_Para.Text_X = P0.X + borderHeight;
        filePara.Time_Para.Text_Y = P0.Y + borderHeight;
        memcpy(buf, (char *)&filePara.Time_Para.Head + 1, sizeof(S_Time_Para)); //ǰһ���ֽ���ͷ��������
        len = sizeof(S_Time_Para) - CHK_BYTE_LEN;

        getBorderData(fileStr, (INT8U *)buf + len, bufLen); //�߿�����
        len += BORDER_DATA_LEN;

        resetShowPara(image.size().width(), image.size().height(), Screen_Para.Base_Para.Color);
        getTextShowData(image, &protoShowData, 0, 0);

        tmpLen = GET_TEXT_LEN(image.size().width(),image.size().height());
        tmpLen = tmpLen * Get_Screen_Color_Num();
        memcpy(buf + len, protoShowData.Color_Data, tmpLen);
        len +=tmpLen;
    }
    else if(type EQ TEMP_PROPERTY) //�¶�
    {
        getTempParaFromSettings(fileStr, filePara);
        QImage image = getLineTextImage(fileStr);
        QSize size = image.size();

        filePara.Temp_Para.Text_Width = size.width();
        filePara.Temp_Para.Text_Height = size.height();
        filePara.Temp_Para.SNum = 1;

        mem_cpy((INT8U *)&Prog_Status.File_Para[0], &filePara, sizeof(filePara), (INT8U *)&Prog_Status.File_Para[0], sizeof(Prog_Status.File_Para[0]));

        S_Point P0;
        Get_Temp_Text_Point(0, width, height, P0);
        filePara.Temp_Para.Text_X = P0.X + borderHeight;
        filePara.Temp_Para.Text_Y = P0.Y + borderHeight;
        memcpy(buf, (char *)&filePara.Temp_Para.Head + 1, sizeof(S_Temp_Para)); //ǰһ���ֽ���ͷ��������
        len = sizeof(S_Temp_Para) - CHK_BYTE_LEN;

        getBorderData(fileStr, (INT8U *)buf + len, bufLen); //�߿�����
        len += BORDER_DATA_LEN;

        resetShowPara(image.size().width(), image.size().height(), Screen_Para.Base_Para.Color);
        getTextShowData(image, &protoShowData, 0, 0);

        tmpLen = GET_TEXT_LEN(image.size().width(),image.size().height());
        tmpLen = tmpLen * Get_Screen_Color_Num();
        memcpy(buf + len, protoShowData.Color_Data, tmpLen);
        len +=tmpLen;

    }
    else if(type EQ HUMIDITY_PROPERTY) //ʪ��
    {
        getHumidityParaFromSettings(fileStr, filePara);
        QImage image = getLineTextImage(fileStr);
        QSize size = image.size();

        filePara.Humidity_Para.Text_Width = size.width();
        filePara.Humidity_Para.Text_Height = size.height();
        filePara.Humidity_Para.SNum = 1;

        mem_cpy((INT8U *)&Prog_Status.File_Para[0], &filePara, sizeof(filePara), (INT8U *)&Prog_Status.File_Para[0], sizeof(Prog_Status.File_Para[0]));

        S_Point P0;
        Get_Humidity_Text_Point(0, width, height, P0);
        filePara.Humidity_Para.Text_X = P0.X + borderHeight;
        filePara.Humidity_Para.Text_Y = P0.Y + borderHeight;
        memcpy(buf, (char *)&filePara.Humidity_Para.Head + 1, sizeof(S_Humidity_Para)); //ǰһ���ֽ���ͷ��������
        len = sizeof(S_Humidity_Para) - CHK_BYTE_LEN;

        getBorderData(fileStr, (INT8U *)buf + len, bufLen); //�߿�����
        len += BORDER_DATA_LEN;

        resetShowPara(image.size().width(), image.size().height(), Screen_Para.Base_Para.Color);
        getTextShowData(image, &protoShowData, 0, 0);

        tmpLen = GET_TEXT_LEN(image.size().width(),image.size().height());
        tmpLen = tmpLen * Get_Screen_Color_Num();
        memcpy(buf + len, protoShowData.Color_Data, tmpLen);
        len +=tmpLen;

    }
    else if(type EQ NOISE_PROPERTY) //����
    {
        getNoiseParaFromSettings(fileStr, filePara);
        QImage image = getLineTextImage(fileStr);
        QSize size = image.size();

        filePara.Noise_Para.Text_Width = size.width();
        filePara.Noise_Para.Text_Height = size.height();
        filePara.Noise_Para.SNum = 1;

        mem_cpy((INT8U *)&Prog_Status.File_Para[0], &filePara, sizeof(filePara), (INT8U *)&Prog_Status.File_Para[0], sizeof(Prog_Status.File_Para[0]));

        S_Point P0;
        Get_Noise_Text_Point(0, width, height, P0);
        filePara.Noise_Para.Text_X = P0.X + borderHeight;
        filePara.Noise_Para.Text_Y = P0.Y + borderHeight;
        memcpy(buf, (char *)&filePara.Noise_Para.Head + 1, sizeof(S_Noise_Para)); //ǰһ���ֽ���ͷ��������
        len = sizeof(S_Noise_Para) - CHK_BYTE_LEN;

        getBorderData(fileStr,(INT8U *)buf + len, bufLen); //�߿�����
        len += BORDER_DATA_LEN;

        resetShowPara(image.size().width(), image.size().height(), Screen_Para.Base_Para.Color);
        getTextShowData(image, &protoShowData, 0, 0);

        tmpLen = GET_TEXT_LEN(image.size().width(),image.size().height());
        tmpLen = tmpLen * Get_Screen_Color_Num();
        memcpy(buf + len, protoShowData.Color_Data, tmpLen);
        len +=tmpLen;

    }
    else if(type EQ TIMER_PROPERTY) //��ʱ
    {
        getTimerParaFromSettings(fileStr, filePara);
        QImage image = getLineTextImage(fileStr);
        QSize size = image.size();

        filePara.Timer_Para.Text_Width = size.width();
        filePara.Timer_Para.Text_Height = size.height();
        filePara.Timer_Para.SNum = 1;

        mem_cpy((INT8U *)&Prog_Status.File_Para[0], &filePara, sizeof(filePara), (INT8U *)&Prog_Status.File_Para[0], sizeof(Prog_Status.File_Para[0]));

        S_Point P0;
        Get_Timer_Text_Point(0, width, height, P0);
        filePara.Timer_Para.Text_X = P0.X + borderHeight;
        filePara.Timer_Para.Text_Y = P0.Y + borderHeight;
        memcpy(buf, (char *)&filePara.Timer_Para.Head + 1, sizeof(S_Timer_Para)); //ǰһ���ֽ���ͷ��������
        len = sizeof(S_Timer_Para) - CHK_BYTE_LEN;

        getBorderData(fileStr, (INT8U *)buf + len, bufLen); //�߿�����
        len += BORDER_DATA_LEN;

        resetShowPara(image.size().width(), image.size().height(), Screen_Para.Base_Para.Color);
        getTextShowData(image, &protoShowData, 0, 0);

        tmpLen = GET_TEXT_LEN(image.size().width(),image.size().height());
        tmpLen = tmpLen * Get_Screen_Color_Num();
        memcpy(buf + len, protoShowData.Color_Data, tmpLen);
        len +=tmpLen;
    }
    else if(type EQ PIC_FLASH_PROPERTY)//����
    {
        getFlashParaFromSettings(fileStr, filePara);
        filePara.Pic_Para.Flag = SHOW_PIC;

        len = sizeof(S_Pic_Para) - CHK_BYTE_LEN;

        getBorderData(fileStr, (INT8U *)buf + len, bufLen); //�߿�����
        len += BORDER_DATA_LEN;

        int count = getFlashFrameCount(fileStr);
        //filePara.Pic_Para.SNum = count;

        //memset(protoShowData.Color_Data, 0, sizeof(protoShowData.Color_Data));


        INT16U num = 0;

        if(filePara.Pic_Para.SNum > 0)
        {
            for(int i = 0; i < count; i += count / filePara.Pic_Para.SNum)
            {
            //Screen_Para.Base_Para.Width -=  2*borderHeight; //getTextShowData������Ҫʹ�õ���Ļ��ȣ��߶ȵȣ������Ҫ���øĲ���
            //Screen_Para.Base_Para.Height -= 2*borderHeight;

            resetShowPara(width, height, Screen_Para.Base_Para.Color);
            getFlashPageShowData(fileStr, i, &protoShowData, 0, borderHeight, borderHeight, width, height);

              //Screen_Para.Base_Para.Width +=  2*borderHeight; //getTextShowData������Ҫʹ�õ���Ļ��ȣ��߶ȵȣ������Ҫ���øĲ���
              //Screen_Para.Base_Para.Height += 2*borderHeight;
              tmpLen = GET_TEXT_LEN(width, height);
              tmpLen = tmpLen * Get_Screen_Color_Num();
              if(len + tmpLen >= bufLen)
              {
                  filePara.Pic_Para.SNum = num;
                  memcpy(buf, (char *)&filePara.Pic_Para.Head + 1, sizeof(S_Pic_Para) - CHK_BYTE_LEN); //ǰһ���ֽ���ͷ��������

                  ASSERT_FAILED();
                  return len;
              }
              num ++;

              memcpy(buf + len, protoShowData.Color_Data, tmpLen);
              len += tmpLen;

              if(num>=filePara.Pic_Para.SNum)
                  break;
            }
        }

        filePara.Pic_Para.SNum = num;
        memcpy(buf, (char *)&filePara.Pic_Para.Head + 1, sizeof(S_Pic_Para) - CHK_BYTE_LEN); //ǰһ���ֽ���ͷ��������


    }
  else if(type EQ PIC_IMAGE_PROPERTY) //ͼƬ
    {
      getImageParaFromSettings(fileStr, filePara);
      filePara.Pic_Para.Flag = SHOW_PIC;

      //int count = getFlashFrameCount(fileStr);
      //filePara.Pic_Para.SNum = count;

      len = sizeof(S_Pic_Para) - CHK_BYTE_LEN;

      filePara.Pic_Para.SNum = 1;
      memcpy(buf, (char *)&filePara.Pic_Para.Head + 1, sizeof(S_Pic_Para) - CHK_BYTE_LEN); //ǰһ���ֽ���ͷ��������

      getBorderData(fileStr, (INT8U *)buf + len, bufLen); //�߿�����
      len += BORDER_DATA_LEN;

      //memset(protoShowData.Color_Data, 0, sizeof(protoShowData.Color_Data));

      //Screen_Para.Base_Para.Width -=  2*borderHeight; //getTextShowData������Ҫʹ�õ���Ļ��ȣ��߶ȵȣ������Ҫ���øĲ���
      //Screen_Para.Base_Para.Height -= 2*borderHeight;

    resetShowPara(width, height, Screen_Para.Base_Para.Color);
    getImagePageShowData(fileStr, 0, &protoShowData, 0, 0, 0, width, height);

    //Screen_Para.Base_Para.Width +=  2*borderHeight;
    //Screen_Para.Base_Para.Height += 2*borderHeight;
    tmpLen = GET_TEXT_LEN(width, height);
    tmpLen = tmpLen * Get_Screen_Color_Num();

    memcpy(buf + len, protoShowData.Color_Data, tmpLen);
    len += tmpLen;

  }

    restoreScreenPara(screenParaBak);
    restoreProgPara(progParaBak);

    return len;
}

//�ж����������Ƿ����ཻ
bool  clashed(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
//�ж����������Ƿ���ײ
    if((x1   <   x2)   &&   ((x2   -   x1)   >=   w1))
                return   false;
    if((x1   >   x2)   &&   ((x1   -   x2)   >=   w2))
                return   false;
    if((y1   <   y2)   &&   ((y2   -   y1)   >=   h1))
                return   false;
    if((y1   >   y2)   &&   ((y1   -   y2) >=   h2))
              return   false;
  return   true;
}


QString Chk_Prog_Border_Para(int progNo, S_Prog_Para &progPara, S_Screen_Para &screenPara)
{
    int i,j;
    INT8U Re = 1;
    QString reStr;
    reStr = QString(QObject::tr("��Ŀ")) + QString::number(progNo + 1);

    if(progPara.Border_Check > 0)
    {
      for(i = 0; i < progPara.Area_Num; i ++)
          if(progPara.Area[i].X < progPara.Border_Height ||\
             progPara.Area[i].Y < progPara.Border_Height ||\
             progPara.Area[i].X + progPara.Area[i].X_Len + progPara.Border_Height >= screenPara.Base_Para.Width  ||\
             progPara.Area[i].Y + progPara.Area[i].Y_Len + progPara.Border_Height >= screenPara.Base_Para.Height)
          {
              reStr += QString(QObject::tr("��")) + QString::number(i + 1) + QString(QObject::tr("����")) + QString(QObject::tr("���Ŀ�߿����ص���"));
              Re = 0;
          }
  }

    for(i = 0; i < progPara.Area_Num; i ++)
    {
        for(j = i + 1; j < progPara.Area_Num; j ++)
        {
          //if(i EQ j)
             // continue;

          if(clashed(progPara.Area[i].X, progPara.Area[i].Y, progPara.Area[i].X_Len, progPara.Area[i].Y_Len,\
                     progPara.Area[j].X, progPara.Area[j].Y, progPara.Area[j].X_Len, progPara.Area[j].Y_Len))
          {
              reStr += QString(QObject::tr("��")) + QString::number(i + 1) + QString(QObject::tr("�������")) +\
                      QString::number(j + 1) + QString(QObject::tr("������ʾ�������ص���"));
              Re = 0;
          }
              /*
          if((progPara.Area[i].X >= progPara.Area[j].X && \
              progPara.Area[i].X < progPara.Area[j].X + progPara.Area[j].X_Len) &&\
             (progPara.Area[i].Y >= progPara.Area[j].Y && \
              progPara.Area[i].Y < progPara.Area[j].Y + progPara.Area[j].Y_Len))
              return QString(QObject::tr("��Ŀ")) + QString::number(progNo + 1) +\
                      QString(QObject::tr("��")) + QString::number(i + 1) + QString(QObject::tr("�������")) +\
                      QString::number(j + 1) + QString(QObject::tr("������ʾ�������ص������ܵ�����ʾ����ȷ��"));
*/
         // if(abs(2*progPara.Area[i].X + progPara.Area[i].X_Len-2*progPara.Area[j].X - progPara.Area[j].X_Len)
        }
    }

    if(Re)
        return "";
    else
    {
        reStr += QString(QObject::tr("���ܵ�����ʾ����ȷ��"));
        return reStr;
    }
}

//����Э�����ݵ�fileName
INT16U _makeProtoData(QString fileName, QString screenStr, int flag, char buf[], int bufLen)
{
    FILE *file;
    INT16U counts = 0;
    S_Prog_Para progPara;
    int len;
    INT16U areaWidth, areaHeight;
    INT8U seq = 0, progNum, areaNum, fileNum;
    char frameBuf[MAX_COM_BUF_LEN + 20], *dataBuf;
    S_Screen_Para screenParaBak;
    S_Prog_Para progParaBak;
    S_Card_Para cardParaBak;
    INT8U data[500];

    seq = frameInfo.seq + 1;//= 0xFF;

    file = fopen(fileName.toLocal8Bit(), "wb+");
    if(file EQ (FILE *)0)
    {
        ASSERT_FAILED();
        return 0;
    }

    fseek(file, 0, SEEK_SET);

    //ֱ�ӷ�������,���������ļ��л�ȡ
    if(flag EQ 0)
    {
        counts++;
        fwrite(buf, bufLen, 1, file);

        fclose(file);

        return counts;
    }

    saveScreenPara(screenParaBak);
    saveProgPara(progParaBak);
    saveCardPara(cardParaBak);

    //��ȡ��Ļ�����Ϳ��ƿ�����
    //û�ж�ȡ����ȷ����Ļ�����򷵻�0
    if(getScreenCardParaFromSettings(screenStr, Screen_Para, Card_Para) EQ 0)
    {
        ASSERT_FAILED();

        restoreScreenPara(screenParaBak);
        restoreProgPara(progParaBak);
        restoreCardPara(cardParaBak);

        fclose(file);

        return counts;
    }

    Calc_Screen_Color_Num();
    dataBuf = (char *)malloc(PROTO_DATA_BUF_LEN);
    //��ȡ��Ļ����
    //Ԥ��ģʽ���߷���ģʽ��Ҫд��Ļ�����������ļ�
    //if(mode EQ PREVIEW_MODE || mode EQ SIM_MODE)
    {
        //������Ļ����
        if(GET_BIT(flag, C_SCREEN_PARA))
        {
            len = makeFrame((char *)&Screen_Para.Base_Para, sizeof(Screen_Para) - CHK_BYTE_LEN,\
                       C_SCREEN_PARA | WR_CMD, seq++, frameBuf);
            counts++;
            fwrite(frameBuf, len, 1, file);
        }

        //����ͨ�Ų���
        if(GET_BIT(flag, C_SCREEN_COM_PARA))
        {
            len = makeFrame((char *)&Screen_Para.COM_Para, sizeof(Screen_Para.COM_Para),\
                       C_SCREEN_COM_PARA | WR_CMD, seq++, frameBuf);
            counts++;
            fwrite(frameBuf, len, 1, file);
        }

        //������Ļ��������
        if(GET_BIT(flag, C_SCREEN_BASE_PARA))
        {
            len = makeFrame((char *)&Screen_Para.Base_Para, sizeof(Screen_Para.Base_Para),\
                       C_SCREEN_BASE_PARA | WR_CMD, seq++, frameBuf);
            counts++;
            fwrite(frameBuf, len, 1, file);
        }
        //ɨ�����
        if(GET_BIT(flag, C_SCAN_PARA))
        {
            len = makeFrame((char *)&Screen_Para.Scan_Para, sizeof(Screen_Para.Scan_Para),\
                       C_SCAN_PARA | WR_CMD, seq++, frameBuf);
            counts++;
            fwrite(frameBuf, len, 1, file);
       }
    }


    //��ʱ���ػ�ʱ��
    if(GET_BIT(flag, C_SCREEN_OC_TIME))
    {
        len = makeFrame((char *)&Screen_Para.OC_Time, sizeof(Screen_Para.OC_Time),\
                   C_SCREEN_OC_TIME | WR_CMD, seq++, frameBuf);
        counts++;
        fwrite(frameBuf, len, 1, file);
    }

    //����
    if(GET_BIT(flag, C_SCREEN_LIGNTNESS))
    {
        len = makeFrame((char *)&Screen_Para.Lightness, sizeof(Screen_Para.Lightness),\
                   C_SCREEN_LIGNTNESS | WR_CMD, seq++, frameBuf);
        counts++;
        fwrite(frameBuf, len, 1, file);
    }

    //��Ŀ��

    //settings.beginGroup(screenStr + "/program/");
    //QStringList progList = getSettingsCheckedSubList();//settings.childGroups();
    //settings.endGroup();

    QStringList progList = getSettingsCheckedSubList(screenStr + "/program/");

    progNum = progList.size();
    debug("prog num = %d", progNum);


    //��Ŀ����
    if(GET_BIT(flag, C_PROG_DATA))
    {
        QString progStr,areaStr, fileStr;

        for(int i = 0; i < progNum; i ++)
        {
            //��Ŀ�ַ���
            progStr = screenStr + "/program/" + progList.at(i);
            //��ȡ��Ŀ����
            getProgParaFromSettings(progStr, progPara);
            progPara.Prog_No = i;

            QString reStr = Chk_Prog_Border_Para(i, progPara, Screen_Para);
            if(reStr != "")
            {
                int re = QMessageBox::warning(w, QObject::tr("��ʾ"),
                                         reStr ,QObject::tr("���±༭"), QObject::tr("����"));
                if(re EQ 0)
                    return 0;
            }

            //��Ŀ����֡
            len = sizeof(progPara) - CHK_BYTE_LEN;
            memcpy(data, (char *)&progPara.Head + 1, len);
            getBorderData(progStr, data + len, sizeof(data) - len);
            len = makeFrame((char *)data, len + BORDER_DATA_LEN,C_PROG_PARA | WR_CMD, seq++, frameBuf);
            counts++;
            fwrite(frameBuf, len, 1, file);
            //��Ŀ�߿�����
            /*
            borderData[0] = i;//��Ŀ��
            len = getBorderData(progStr, borderData + 1, sizeof(borderData));
            len = makeFrame((char *)&progPara.Head + 1, sizeof(progPara) - CHK_BYTE_LEN,C_PROG_PARA | WR_CMD, seq++, frameBuf);
            counts++;
            fwrite(frameBuf, len, 1, file);
*/
            //settings.beginGroup(progStr + "/area/");
            QStringList areaList = getSettingsCheckedSubList(progStr + "/area/");//settings.childGroups();
            //settings.endGroup();

            areaNum = areaList.size();
            for(int j = 0; j < areaNum; j ++)
            {
                areaStr = progStr + "/area/" + areaList.at(j);

                //������Ⱥ͸߶�
                settings.beginGroup(areaStr);
                areaWidth = settings.value("width").toInt();
                areaHeight = settings.value("height").toInt();
                settings.endGroup();

                //�ļ��б�
                //settings.beginGroup(areaStr + "/file/");
                QStringList fileList = getSettingsCheckedSubList(areaStr + "/file/");//settings.childGroups();
                //settings.endGroup();

                fileNum = fileList.size();
                for(int k = 0; k < fileNum; k ++)
                {
                    fileStr = areaStr + "/file/" + fileList.at(k);
                    len = getFileParaFromSettings(i,j,k,areaWidth, areaHeight, fileStr, dataBuf, PROTO_DATA_BUF_LEN);

                    while(1)
                    {
                      //��Ŀ��ʾ����֡
                      int tmpLen = makeFrame(dataBuf, len, C_PROG_DATA | WR_CMD, seq, frameBuf);
                      if(tmpLen > 0)
                      {
                          counts++;
                          fwrite(frameBuf, tmpLen, 1, file);
                      }
                      else
                      {
                          seq ++;
                          break;
                      }
                    }
                }
              }
        }
    }

    if(GET_BIT(flag, C_PROG_DATA))
    {
      len = makeFrame((char *)&progNum, sizeof(progNum),\
               C_PROG_NUM | WR_CMD, seq++, frameBuf);
      counts++;
      fwrite(frameBuf, len, 1, file);
    }

    free(dataBuf);

    fclose(file);

    restoreScreenPara(screenParaBak);
    restoreProgPara(progParaBak);
    restoreCardPara(cardParaBak);

    return counts;

}

//����Э������,����Դ����settings��ȡ������ֱ�Ӵ�buf�л��
INT8U makeProtoBufData(QString screenStr, int mode, INT8U cmd , char buf[], int bufLen)
{
    int len, counts;
    //INT8U seq = 0;
    char frameBuf[MAX_COM_BUF_LEN + 20];


    len = makeFrame(buf, bufLen,\
               cmd, frameInfo.seq+1, frameBuf);

    if(mode EQ PREVIEW_MODE || mode EQ SIM_MODE)
    {
       counts = _makeProtoData(PREVIEW_PROTO_FILE, screenStr, 0, frameBuf, len); //����Э�����ݵ�

       if(counts > 0)
       {
           w->comStatus->setTotalFrameCounts(counts);
           w->comStatus->setComMode(mode);
           w->comStatus->sendProtoFile(PREVIEW_PROTO_FILE);
       }
    }
    else if(mode EQ UDISK_MODE)
    {
       //ֱ�����ɵ�U�����ļ���Ϊ ��ĻAddr.dat
        counts = _makeProtoData(UDISK_PROTO_FILE, screenStr, 0, frameBuf, len); //����Э�����ݵ�
        if(counts > 0)
        {
          w->comStatus->setComMode(mode);
          w->comStatus->getUDiskParaFromSettings(screenStr); //��ȡ��Ļ��ַ--�����ļ�ʱ��Ҫ
          w->comStatus->sendProtoFile(UDISK_PROTO_FILE);
        }
    }
    else //if(mode EQ COM_MODE) //���ڷ�ʽ
    {
        counts = _makeProtoData(COM_PROTO_FILE, screenStr, 0, frameBuf, len);  //����Э�����ݵ�
        if(counts)
        {
          w->comStatus->setTotalFrameCounts(counts);
          w->comStatus->getCOMParaFromSettings(screenStr); //��ȡͨ�Ų���--�����ͨ�ŷ�ʽ��ͨ�Ų����ж���
          w->comStatus->sendProtoFile(COM_PROTO_FILE);
        }
    }

    return 1;
}

//INT8U makeProtoBufData(INT8U Cmd, )
INT8U makeProtoFileData(QString screenStr, int mode, int flag)
{
    INT16U counts = 0; //�ܵ�֡��

    if(mode EQ PREVIEW_MODE)
    {
       counts = _makeProtoData(PREVIEW_PROTO_FILE, screenStr, flag, (char *)0, 0); //����Э�����ݵ�

       if(counts > 0)
       {
         w->comStatus->setTotalFrameCounts(counts);
         w->comStatus->setComMode(mode);
         w->comStatus->sendProtoFile(PREVIEW_PROTO_FILE);
       }
    }
    else  if(mode EQ SIM_MODE)
    {
        counts = _makeProtoData(SIM_PROTO_FILE, screenStr, flag, (char *)0, 0); //����Э�����ݵ�

        if(counts > 0)
        {
          w->comStatus->setTotalFrameCounts(counts);
          w->comStatus->setComMode(mode);
          w->comStatus->sendProtoFile(SIM_PROTO_FILE);
        }
    }
    else if(mode EQ UDISK_MODE)
    {
        //ֱ�����ɵ�U�����ļ���Ϊ ��ĻAddr.dat
         counts = _makeProtoData(UDISK_PROTO_FILE, screenStr, flag, (char *)0, 0); //����Э�����ݵ�
         if(counts > 0)
         {
           w->comStatus->setComMode(mode);
           w->comStatus->getUDiskParaFromSettings(screenStr); //��ȡ��Ļ��ַ--�����ļ�ʱ��Ҫ
           w->comStatus->sendProtoFile(UDISK_PROTO_FILE);
         }
     }
    else //if(mode EQ COM_MODE) //���ڷ�ʽ
    {
        counts = _makeProtoData(COM_PROTO_FILE, screenStr, flag, (char *)0, 0);  //����Э�����ݵ�
        if(counts > 0)
        {
          w->comStatus->setTotalFrameCounts(counts);
          w->comStatus->getCOMParaFromSettings(screenStr); //��ȡͨ�Ų���
          w->comStatus->sendProtoFile(COM_PROTO_FILE);
        }
    }

    return counts > 0?1:0;

}
