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

int CcomThread::waitComRcv(int sec)
{
    int rcvBytes,j = 0;

    //return 1;
    for(int i = 0; i < sec*10; i ++)
    {
        this->msleep(100); //��ʱ100ms
        rcvBytes = comReceive();

        if(Rcv_Flag EQ FRAME_FLAG) //�յ�Ӧ��֡
            return 1;
        else if(rcvBytes > 0)//�յ������������¼�ʱ
        {
            i = 0;
        }

        j ++;
        if(j >= 50) //��󲻳���5s
            return 0;

    }

    return 0;
}

bool CcomThread::comRun()
{
    FILE *file;
    int re;
    bool Re = true;
    INT16U len, len0 = 0;
    bool flag = false;
    char frameBuf[BLOCK_DATA_LEN + 20];

    file = fopen(protoFileName.toLocal8Bit(), "rb");
    if(file EQ 0)
    {
        ASSERT_FAILED();
        emit this->comStatusChanged(tr("�Ҳ���Э�������ļ���"));
        return false;
    }

    fseek(file, 0, SEEK_SET);

    //dialog->show();

    if(this->connect() EQ 0)
        return false;

    while((re = fread(frameBuf, FLEN + 2, 1, file)) > 0)
    {
      memcpy(&len, frameBuf + FLEN, 2);
      if(len <= sizeof(frameBuf) && len > FLEN + 2)
      {
          re = fread(frameBuf + FLEN + 2,  len - (FLEN + 2), 1, file);

          if(re > 0 && Check_Frame_Format((INT8U *)frameBuf, len))
          {
              flag = true;
            if(sendFrame(frameBuf, len) EQ 0)
              {
                Re = false;
                break;
            }

            len0 += len;
          }
          else
          {
            Re = false;
            break;
          }
      }
      else
      {
          Re = false;
          break;
      }
    }

    fclose(file);

    this->disConnect();

    if(checkComMode(this->COM_Mode))
    {
        if(flag EQ false)
          emit this->comStatusChanged(tr("�����ݷ���"));
        else
          emit this->comEnd(Re);
     }
    return Re;
}

void CcomThread::run()
{
  comRun();
}

CcomThread::CcomThread(QObject * parent):QThread(parent)
{
    QVBoxLayout *vLayout;

    port = new QextSerialPort("COM1", QextSerialPort::EventDriven);

    memset(Rcv_Buf, 0, sizeof(Rcv_Buf));
    Rcv_Posi = 0;

        //QObject::connect(port, SIGNAL(readyRead()), this, SLOT(receive()));
}

//�Ͽ�ͨ������
bool CcomThread::disConnect()
{
    memset(Rcv_Buf, 0, sizeof(Rcv_Buf));
    Rcv_Posi = 0;

    if(COM_Mode EQ COM_MODE)
      port->close();

    return true;
}

//��ͨ�Ŷ˿ڣ�����������
bool CcomThread::connect()
{
    QStringList comPortList;
    comPortList = getComPortList();

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

        port->setPortName(COM_Port);

        if(port->open(QIODevice::ReadWrite) EQ false)
        {

            comReStr = tr("�򿪴���ʧ�ܣ�����ô����Ƿ��ѱ�ռ��");
            emit comStatusChanged(comReStr);
            return false;
        }
        else
        {
          comReStr = tr("�򿪴��ڳɹ�");
          emit comStatusChanged(comReStr);
          return true;
        }

    }
    else //����ͨ�ŷ�ʽ
    {
       return true;

    }
}

int CcomThread::sendFrame(char *data, int len)
{
    int i,re;
  INT8U mode = COM_Mode;

  if(mode EQ PREVIEW_MODE)//Ԥ��ģʽ
  {
    Rcv_Frame_Proc(CH_SIM, (INT8U *)data, (INT16U)len); //���պ��������ڷ�������£�������д����Ӳ���ļ���ģ��д��EEROM
  }
  else if(mode EQ SIM_MODE) //����ģʽ
  {
    for(i = 0; i < len; i ++)
        Com_Rcv_Byte(CH_SIM, *(data + i));
  }
  else if(mode EQ COM_MODE)//����ͨ��ģʽ
  {
    for(i = 0; i < 3; i ++)
    {
      port->write(data, len);
      emit this->comStatusChanged(tr("���͵�") + QString::number(frameCounts + 1)+"/"+QString::number(totalFrameCounts)+tr("֡,�ȴ�Ӧ��"));
      re = waitComRcv(2); //�ȴ�Ӧ��
      if(re > 0)
      {
          frameCounts++;
          emit this->comStatusChanged(tr("�յ�Ӧ��"));
          emit comProgressChanged(100*frameCounts/totalFrameCounts);
          return 1;
      }
    }
    emit this->comStatusChanged(tr("�ȴ�Ӧ��ʱ"));
    return 0;
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

//���ڽ�������
int CcomThread::comReceive()
{

    int bytesRead;

    bytesRead = port->read((char *)Rcv_Buf + Rcv_Posi, sizeof(Rcv_Buf)- Rcv_Posi);//(char *)(Rcv_Buf + Rcv_Posi), sizeof(Rcv_ Buf) - Rcv_Posi);
    if(bytesRead EQ 0)
        return 0;

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
           return bytesRead;
        }
    }

    return bytesRead;
}

CcomStatus::CcomStatus(QWidget * parent):QDockWidget(tr("ͨ��״̬"), parent)
{
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;
    QWidget *widget;
    QLabel *progressLabel;
    QLabel *paraLabel, *statusLabel;
    QLabel *nameLabel;

    widget = new QWidget(this);
    vLayout = new QVBoxLayout(widget);
    hLayout = new QHBoxLayout(widget);

    nameLabel = new QLabel(tr("ͨ����Ļ:"));
    screenNameEdit = new QLineEdit(widget);
    screenNameEdit->setFocusPolicy(Qt::NoFocus);

    hLayout->addWidget(nameLabel);
    hLayout->addWidget(screenNameEdit);
    vLayout->addLayout(hLayout);

    paraLabel = new QLabel(tr("ͨ�Ų���:"),widget);
    paraEdit = new QTextEdit(widget);
    paraEdit->setFixedHeight(50);
    paraEdit->setFocusPolicy(Qt::NoFocus);

    statusLabel = new QLabel(tr("ͨ��״̬:"),widget);

    statusEdit = new QTextEdit(widget);
    statusEdit->setFixedHeight(150); //ͨ��״̬
    statusEdit->setFocusPolicy(Qt::NoFocus);

    progressLabel = new QLabel(tr("����"),widget);
    progressBar = new QProgressBar(widget);//QProgressDialog()
    progressBar->setMaximum(100);
    progressBar->setValue(0);

    hLayout = new QHBoxLayout(widget);
    hLayout->addWidget(progressLabel);
    hLayout->addWidget(progressBar);

    progressList = new QListView(widget);
    //progressList->setFixedSize(100,100);
    progressList->setFixedHeight(100);
    comThread = new CcomThread(this);

    vLayout->addWidget(paraLabel);
    vLayout->addWidget(paraEdit);
    vLayout->addWidget(statusLabel);
    vLayout->addWidget(statusEdit);
    vLayout->addWidget(progressList);
    vLayout->addLayout(hLayout);
    //vLayout->addWidget(statusEdit);
    //vLayout->addWidget(progressBar);
    vLayout->addStretch(10);
    widget->setLayout(vLayout);

    widget->setFixedWidth(200);
    setWidget(widget);
    connect(this->comThread, SIGNAL(comProgressChanged(int)), this, SLOT(progressChange(int)));
    connect(this->comThread, SIGNAL(comStatusChanged(QString)), this, SLOT(statusChange(QString)));
    connect(this->comThread, SIGNAL(comEnd(bool)), this, SLOT(comEnd(bool)));
    //connect(this, SIGNAL(comStart()), this->comth)
    //connect(this, SIGNAL(Start()), this, SLOT(comStart()));
    //QObject::connect(port, SIGNAL(readyRead()), this, SLOT(receive()));
    progressList->setVisible(false);
}

bool checkComMode(INT8U COM_Mode)
{
    if(COM_Mode EQ COM_MODE ||\
       COM_Mode EQ GPRS_MODE ||\
       COM_Mode EQ ETH_MODE)
        return true;
    else
        return false;
}

//����һ���ļ���Э�����ݵ�Ŀ�꣬�������̵߳���ʽ����
void CcomStatus::sendProtoFile(QString fileName)
{

   this->comThread->protoFileName = fileName;

   //���ڡ�GPRS����̫����ʽ�����߳���ʽ,��������һ�㺯����ʽ��������ܵ���Ԥ��ʧ��
   if(checkComMode(this->comThread->COM_Mode))
   {
     this->show();
     this->comThread->start();
   }
   else
     this->comThread->comRun();
   //emit this->start();
  // this->exec();
}

//��ȡͨ�Ų���,strΪ��Ļ��settings str
void CcomStatus::getCOMParaFromSettings(QString str)
{
    QString str1;
    QStringList screenGroups;
    int screenSize;

    settings.beginGroup(str);
    settings.beginGroup("comTest");

    comThread->COM_Mode = settings.value("comMode").toInt();
    comThread->COM_Port = settings.value("comPort").toString();

    comThread->COM_Para.Addr = settings.value("screenID").toInt();
    comThread->COM_Para.Baud = settings.value("comBaud").toInt();

    comThread->ETH_Para.IP = settings.value("ip").toInt();

    settings.endGroup();
    settings.endGroup();

    screenNameEdit->clear();
    paraEdit->clear();
    statusEdit->clear();
    progressBar->setValue(0);

    //------�����ǵڼ�����Ļ
    int index = getScreenIndex(str);
    screenNameEdit->setText(QString::number(index) + tr("����Ļ"));
    //-------------
    if(comThread->COM_Mode EQ COM_MODE)
    {
      str1 = tr("����ͨ�ŷ�ʽ, ");
      str1 += comThread->COM_Port + tr(" ������:");
      if(comThread->COM_Para.Baud EQ 0)
          str1 += tr("9600");
      else
          str1 += tr("57600");

      paraEdit->append(str1);
    }
}

void CcomStatus::setComMode(int mode)
{
    comThread->COM_Mode = mode;

}


void CcomStatus::setTotalFrameCounts(int counts)
{
  comThread->frameCounts = 0;
  comThread->totalFrameCounts = counts;
}

//���ȸı�
void CcomStatus::progressChange(int progress)
{
    progressBar->setValue(progress);
}

//ͨ��״̬�ı�
void CcomStatus::statusChange(QString str)
{
    statusEdit->append(str);
}

//ͨ�Ž���
void CcomStatus::comEnd(bool flag)
{
    if(flag EQ false)
        statusEdit->append(tr("��������ʧ��!"));
    else
        statusEdit->append(tr("�������ݳɹ�!"));
}

void CcomStatus::comStart()
{
    show();
    comThread->start();
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



