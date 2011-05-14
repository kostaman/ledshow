#include <QTextStream>
#include "Communication.h"
#include <Qstringlist.h>
#include <QSettings>
#include <QTime>
#include <QCoreApplication>
#include <QProgressDialog>
#include <QVBoxLayout>
#include "mainwindow.h"
#include "makeProto.h"

extern QSettings settings;
extern MainWindow *w;
/*
==============
<CONSTRUCTORS>
==============
*/
QStringList getComPortList()
{
    QextSerialEnumerator enumer;
    QList<QextPortInfo> ports = enumer.getPorts();
    QStringList strlist;

    strlist.clear();
    for( int i = 0; i < ports.count(); ++i)
        strlist << QObject::tr(ports.at(i).portName.toLocal8Bit());
    //comPortEdit->addItems(strlist);
    return strlist;
}

void comSleep(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

int CcomStatus::waitComRcv(int sec)
{
  for(int i = 0; i < sec*10; i ++)
  {
    comSleep(100); //��ʱ100ms
    comReceive();
    if(Rcv_Flag EQ FRAME_FLAG) //�յ�Ӧ��֡
        return 1;
  }

  return 0;
}

CcomStatus::CcomStatus(QWidget * parent):QWidget(parent)
{
    QVBoxLayout *vLayout;

    vLayout = new QVBoxLayout(this);
    port = new QextSerialPort("COM1", QextSerialPort::EventDriven);
    progressDialog = new QProgressDialog(w);//QProgressDialog()
    vLayout->addWidget(progressDialog);
    setLayout(vLayout);

    memset(Rcv_Buf, 0, sizeof(Rcv_Buf));
    Rcv_Posi = 0;

        //QObject::connect(port, SIGNAL(readyRead()), this, SLOT(receive()));
}

//�Ͽ�ͨ������
int CcomStatus::disConnect()
{
    memset(Rcv_Buf, 0, sizeof(Rcv_Buf));
    Rcv_Posi = 0;

    if(COM_Mode EQ COM_MODE)
      port->close();
}

//��ͨ�Ŷ˿ڣ�����������
int CcomStatus::connect(QString str)
{
    QStringList comPortList;
    comPortList = getComPortList();

    getCOMParaFromSettings(str);//��ȡͨ�Ų���

    if(COM_Mode EQ COM_MODE)
    {
        if(COM_Para.Baud EQ 0)
          port->setBaudRate(BAUD9600);
        else
          port->setBaudRate(BAUD57600);

        //���عء�żУ�顢����λ8λ��ֹͣλ1λ
        port->setFlowControl(FLOW_OFF);
        port->setParity(PAR_EVEN); //żУ��
        port->setDataBits(DATA_8);
        port->setStopBits(STOP_1);

        if(port->open(QIODevice::ReadWrite) EQ false)
        {

            comReStr = tr("�򿪴���ʧ�ܣ�����ô����Ƿ��ѱ�ռ��");
            emit comStatusChanged(comReStr);
            return 0;
        }
        else
        {
          comReStr = tr("�򿪴��ڳɹ�");
          emit comStatusChanged(comReStr);
          return 1;
        }

    }
    else //����ͨ�ŷ�ʽ
    {
       return 0;

    }
}

void CcomStatus::setComMode(int mode)
{
    COM_Mode = mode;

}

int CcomStatus::sendFrame(char *data, int len)
{
  INT8U mode = COM_Mode;

  if(mode EQ PREVIEW_MODE)//Ԥ��ģʽ
  {
    Rcv_Frame_Proc(CH_SIM, (INT8U *)data, (INT16U)len); //���պ��������ڷ�������£�������д����Ӳ���ļ���ģ��д��EEROM
  }
  else if(mode EQ SIM_MODE) //����ģʽ
  {
    for(int i = 0; i < len; i ++)
        Com_Rcv_Byte(CH_SIM, *(data + i));
  }
  else if(mode EQ COM_MODE)//����ͨ��ģʽ
  {
      port->write(data, len);
      waitComRcv(3); //�ȴ�Ӧ��
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

//����һ���ļ���Э�����ݵ�Ŀ�꣬�������̵߳���ʽ����
int CcomStatus::sendProtoFile(QString fileName)
{
    FILE *file;
    int re,Re = 1;
    INT16U len, len0 = 0;
    char frameBuf[BLOCK_DATA_LEN + 20];

    file = fopen(fileName.toLocal8Bit(), "rb");
    if(file EQ 0)
    {
        ASSERT_FAILED();
        return 0;
    }

    fseek(file, 0, SEEK_SET);

    while((re = fread(frameBuf, FLEN + 2, 1, file)) > 0)
    {
      memcpy(&len, frameBuf + FLEN, 2);
      if(len <= sizeof(frameBuf) && len > FLEN + 2)
      {
          re = fread(frameBuf + FLEN + 2,  len - (FLEN + 2), 1, file);

          if(re > 0 && Check_Frame_Format((INT8U *)frameBuf, len))
          {
            if(sendFrame(frameBuf, len) EQ 0)
              {
                Re = 0;
                break;
            }

            len0 += len;
          }
          else
          {
            Re = 0;
            break;
          }
      }
      else
      {
          Re = 0;
          break;
      }
    }

    fclose(file);

    return Re;
}

//��ȡͨ�Ų���,strΪ��Ļ��settings str
void CcomStatus::getCOMParaFromSettings(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("comTest");

    COM_Mode = settings.value("comMode").toInt();
    COM_Port = settings.value("comPort").toInt();

    COM_Para.Addr = settings.value("screenID").toInt();
    COM_Para.Baud = settings.value("comBaud").toInt();

    ETH_Para.IP = settings.value("ip").toInt();

    settings.endGroup();
    settings.endGroup();

    //SET_SUM(screenPara);
}

//���ڽ�������
void CcomStatus::comReceive()
{

    int bytesRead;

    bytesRead = port->read((char *)Rcv_Buf + Rcv_Posi, sizeof(Rcv_Buf)- Rcv_Posi);//(char *)(Rcv_Buf + Rcv_Posi), sizeof(Rcv_ Buf) - Rcv_Posi);
    if(bytesRead EQ 0)
        return;

    if(sizeof(Rcv_Buf) >= Rcv_Posi + bytesRead)
    {
        Rcv_Posi += bytesRead;
        Rcv_Buf[Rcv_Posi] = '\0';
    }
    else
    {
        ASSERT_FAILED();
        Rcv_Posi = 0;
    }

    for(int i = 0; i < Rcv_Posi; i ++)
    {
        //if(Screen_Status.Rcv_Data[i] EQ FRAME_HEAD && \
        if(Check_Frame_Format(Rcv_Buf + i, Rcv_Posi - i))
        {
           if(i != 0) //�����ݸ��Ƶ���ʼ
               memcpy(Rcv_Buf, Rcv_Buf + i, Rcv_Posi - i);
           Rcv_Flag = FRAME_FLAG;
           Rcv_Ch = CH_COM;
           return;
        }
    }
}
/*
==============
<DESTRUCTOR>
==============
*/


/*
==============
<STATIC>
==============
*/


/*
==============
<SLOTS>
==============
*/



