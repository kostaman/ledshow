#include <QFileDialog>
#include <QSettings>
#include <QMovie>
#include <QInputDialog>
#include <QMessageBox>
#include <QextSerialPort>
#include <QextSerialEnumerator>
#include <QList>
#include <QObject>
#include "makeProto.h"
#include "mainwindow.h"
#include "screenProperty.h"

extern MainWindow *w;
extern QSettings settings;

//��Ļ�����ļ�
QSettings screenSettings(SCREEN_INI_FILE,QSettings::IniFormat,0);
//���ƿ������ļ�
QSettings cardSettings(CARD_INI_FILE,QSettings::IniFormat,0);

#define WIDTH_0 80
/*
CipInput::CipInput(QWidget *parent):QGroupBox(parent)
{
    QHBoxLayout *hLayout;
    QLabel *pointLabel[4];

    hLayout = new QHBoxLayout(this);

    for(int i = 0; i < 4; i ++)
    {
        inputEdit[i] = new QLineEdit(this);
        inputEdit[i]->setFixedWidth(30);
        //inputEdit[i]->setmi
        //inputEdit[i]->setmax
        pointLabel[i] = new QLabel(tr("."),this);
        hLayout->addWidget(inputEdit[i]);
        hLayout->addWidget(pointLabel[i]);
    }

   setLayout(hLayout);
}

CipInput::~CipInput()
{

}

INT332U CipInput::getInputIP()
{

}
*/
/*
//screen���Դ�
class CscreenProperty:public QWidget
{
    Q_OBJECT
private:
    QLabel *screenSourceLabel; //screenԴ��־
    QLineEdit *screenSourceEdit; //screenԴ�༭��
    QPushButton *openButton; //�򿪰�ť

    QLabel *frameNumLabel; //֡����־
    QLineEdit *frameNumEdit; //֡���༭
    QLabel *runSpeedLabel; //�����ٶȱ�־
    QLineEdit *runSpeedCheck; //�����ٶȱ༭
    QLabel *speedUnitLabel; //�ٶȵ�λ

    QLabel *totalFrameNumLabel; //��֡��


public:
    CscreenProperty(QWidget *parent=0);
    ~CscreenProperty();
};
*/
INT8U getCardParaFromSettings(QString cardName, S_Card_Para &cardPara)
{
    cardSettings.beginGroup(cardName);
    cardPara.Font_Num = cardSettings.value("FontNum").toInt();
    cardPara.InMode_Num = cardSettings.value("inModeNum").toInt();
    cardPara.OutMode_Num = cardSettings.value("outModeNum").toInt();
    cardPara.File_En_Word = cardSettings.value("fileEnWord").toInt();
    cardPara.Max_Points = cardSettings.value("maxPoints").toInt();
    Card_Para.Max_Height = cardSettings.value("maxHeight").toInt();
    cardPara.Flag = cardSettings.value("flag").toInt();
    cardPara.ROM_Size = cardSettings.value("romSize").toInt();
    cardPara.Com_Mode = cardSettings.value("comMode").toInt();
    cardSettings.endGroup();

    return 1;
}

//��ȡ��Ļ����
//����>0��ʾ��ȡ��������==0��ʾû�ж�ȡ������
INT8U getScreenCardParaFromSettings(QString screenStr, S_Screen_Para &screenPara, S_Card_Para &cardPara)
{
    QString cardName;

    qDebug("getScreenCardParaFromSettings:%s", (const char *)screenStr.toLocal8Bit());

    settings.beginGroup(screenStr);
    settings.beginGroup("facPara");

    int index = settings.value("cardType").toInt();

    screenPara.Base_Para.Width = settings.value("width").toInt();
    screenPara.Base_Para.Height = settings.value("height").toInt();

    INT8U color = settings.value("color").toInt();
    if(color EQ 0) //��ɫ��
        screenPara.Base_Para.Color = 0x01;
    else if(color EQ 1) //˫ɫ��
        screenPara.Base_Para.Color = 0x03;
    else
        screenPara.Base_Para.Color = 0x07;

    screenPara.COM_Para.Addr = (INT16U)settings.value("screenID").toInt();
    screenPara.COM_Para.Baud = settings.value("comBaud").toInt();

    screenPara.ETH_Para.IP = settings.value("ip").toInt();
    screenPara.ETH_Para.Mac = settings.value("mac").toInt();
    screenPara.ETH_Para.Mask = settings.value("mask").toInt();

    screenPara.Scan_Para.Data_Polarity = settings.value("dataPolarity").toInt(); //���ݼ���
    screenPara.Scan_Para.OE_Polarity = settings.value("oePolarity").toInt();
    screenPara.Scan_Para.RG_Reverse = settings.value("redGreenRev").toInt();
    screenPara.Scan_Para.Line_Order = settings.value("lineOrder").toInt();
    screenPara.Scan_Para.Line_Hide = settings.value("lineHide").toInt();
    screenPara.Scan_Para.Clk_Freq = settings.value("freq").toInt(); //��λƵ��

    screenPara.Scan_Para.Direct = 0;
    screenPara.Scan_Para.Cols_Fold = 0;
    screenPara.Scan_Para.Rows_Fold = 0;
    screenPara.Scan_Para.Rows = 0;
    screenPara.Scan_Para.Screen_Freq = 0; //��Ƶ

    //���ȵ���
    settings.beginGroup("lightness");
    screenPara.Lightness.Mode = settings.value("adjMode").toInt();
    screenPara.Lightness.Manual_Lightness = settings.value("manualLightness").toInt(); //�ֶ�������

    for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
    {
      screenPara.Lightness.Time_Lightness[i].Flag = settings.value("timeCheck" + QString::number(i)).toBool();
      screenPara.Lightness.Time_Lightness[i].Start_Hour = settings.value("startHour" + QString::number(i)).toInt();
      screenPara.Lightness.Time_Lightness[i].Start_Min = settings.value("startMin" + QString::number(i)).toInt();
    }
    settings.endGroup();

    //��ʱ���ػ�
    settings.beginGroup("openCloseTime");

    for(int i =0; i < MAX_OPEN_CLOSE_TIME;i ++)
    {
        screenPara.OC_Time.Time[i].Flag = settings.value("timeCheck"+QString::number(i)).toBool();
        screenPara.OC_Time.Time[i].Open_Hour = settings.value("openHour" + QString::number(i)).toInt();
        screenPara.OC_Time.Time[i].Open_Min = settings.value("openMin" + QString::number(i)).toInt();
        screenPara.OC_Time.Time[i].Close_Hour = settings.value("closeHour" + QString::number(i)).toInt();
        screenPara.OC_Time.Time[i].Close_Min = settings.value("closeSec" + QString::number(i)).toInt();
    }

    settings.endGroup();

    settings.endGroup();
    settings.endGroup();

   cardSettings.beginGroup("");
   cardName = cardSettings.childGroups().at(index);
   cardSettings.endGroup();

   getCardParaFromSettings(cardName, cardPara);
  return 1;
}

//screen���Ա༭
CscreenProperty::CscreenProperty(QWidget *parent):QWidget(parent)
{

    QTabWidget *tab;
    QHBoxLayout *hLayout,*mainLayout;
    QVBoxLayout *vLayout;
    //QGroupBox *lightnessGroup;
    //QGroupBox *openCloseTimeGroup;
    //QGroupBox *facParaGroup;

    //lightnessGroup = new QGroupBox(tr("��������"),this);
    //openCloseTimeGroup = new QGroupBox(tr("���ػ�����"),this);
    //facParaGroup = new QGroupBox(tr("��װ����"),this);

    mainLayout = new QHBoxLayout(this);

    vLayout = new QVBoxLayout(this);
    nameEdit = new CnameEdit(this);
    vLayout->addWidget(nameEdit);
    vLayout->addStretch(10);
    mainLayout->addLayout(vLayout);

    //tab = new QTabWidget(this);
     //hLayout = new QHBoxLayout(this);
    facProperty = new CfacScreenProperty(SHOW_SCN,this);

     //hLayout->addWidget(facProperty);
    //facParaGroup->setLayout(hLayout);

    //hLayout = new QHBoxLayout(this);
    lightnessProperty = new ClightnessProperty(this);
    //hLayout->addWidget(lightnessProperty);
    //lightnessGroup->setLayout(hLayout);

    //hLayout = new QHBoxLayout(this);
    openCloseProperty = new CopenCloseProperty(this);
    //hLayout->addWidget(openCloseProperty,0,Qt::AlignTop);
    //openCloseTimeGroup->setLayout(hLayout);
    //lightnessGroup->setLayout(vLayout);
    //facProperty->setEnabled(false);
    //facProperty->endButton->setEnabled(true);
    //tab->addTab(lightnessProperty, tr("���ȵ���"));
    //tab->addTab(openCloseProperty, tr("��ʱ���ػ�"));

   // tab->addTab(facProperty, tr("��������"));
    //hLayout->addWidget(tab);
    mainLayout->addWidget(lightnessProperty);
    mainLayout->addWidget(openCloseProperty);
    mainLayout->addWidget(facProperty);
    mainLayout->addStretch(10);

    //setLayout(hLayout);
     //hLayout->addLayout(vLayout);

    //connect(nameEdit, SIGNAL(edited()), this, SIGNAL(edited()));
    //connect(openButton, SIGNAL(clicked()), this, SLOT(openscreenFile()));
}


CscreenProperty::~CscreenProperty()
{

}

void CscreenProperty::getSettingsFromWidget(QString str)
{
    nameEdit->getSettingsFromWidget(str);
    lightnessProperty->getSettingsFromWidget(str);
    openCloseProperty->getSettingsFromWidget(str);

}

void CscreenProperty::setSettingsToWidget(QString str)
{
    nameEdit->setSettingsToWidget(str);
    lightnessProperty->setSettingsToWidget(str);
    openCloseProperty->setSettingsToWidget(str);
    facProperty->setSettingsToWidget(str);
}
/*
class ClightnessProperty:public QWidget
{
    Q_OBJECT
    QRadioButton *manualButton;
    QRadioButton *timerButton;

public:
    QCheckBox *timerCheck[MAX_LIGHTNESS_TIME];
    QTimeEdit *timerEdit[MAX_LIGHTNESS_TIME];
    QSlider *timerSlider[MAX_LIGHTNESS_TIME];

    QSlider *manualSlider;
    //void getSettingsFromWidget(QString str);
   //void setSettingsToWidget(QString str);
    ClightnessProperty(QWidget *parent=0);
    ~ClightnessProperty();
};
*/
ClightnessProperty::ClightnessProperty(QWidget *parent):QGroupBox(parent)
{
    INT8U i;

    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
   QHBoxLayout *gHLayout;
   QGroupBox *groupBox;

   QHBoxLayout *mainLayout = new QHBoxLayout(this);

   groupBox = new QGroupBox(this);
   vLayout = new QVBoxLayout(this);
   manualButton = new QRadioButton(tr("�ֶ�����"),this);
   timerButton = new QRadioButton(tr("��ʱ����"),this);
   autoButton = new QRadioButton(tr("�Զ�����"),this);

   vLayout->addWidget(manualButton);
   vLayout->addWidget(timerButton);
   vLayout->addWidget(autoButton);
   groupBox->setLayout(vLayout);

   mainLayout->addWidget(groupBox);//addLayout(hLayout);

   groupBox = new QGroupBox(this);
   gHLayout = new QHBoxLayout(this);

   hLayout = new QHBoxLayout(this);
   manualSlider = new QSlider(Qt::Horizontal,this);
   manualSlider->setRange(10,MAX_LIGHTNESS_LEVEL*10);
   manualSlider->setTickInterval(10);
   //manualSlider->setFocusPolicy(Qt::StrongFocus);
   //manualSlider->setTickPosition(QSlider::TicksAbove);
   manualLabel = new QLabel(this);
   manualLabel->setFixedWidth(15);
   hLayout->addWidget(manualSlider);
   hLayout->addWidget(manualLabel);
   gHLayout->addLayout(hLayout);

   hLayout = new QHBoxLayout(this);
   autoLabel = new QLabel(tr("��ȷ���Ѱ�װ���մ�����"),this);
   hLayout->addWidget(autoLabel);
   gHLayout->addLayout(hLayout);


   QVBoxLayout *timerVLayout = new QVBoxLayout(this);
   for(i = 0; i < MAX_LIGHTNESS_TIME; i ++)
   {
     hLayout = new QHBoxLayout(this);
     timerCheck[i] = new QCheckBox(tr("ʹ��"),this);
     timerEdit[i] = new QTimeEdit(this);

     timerSlider[i] = new QSlider(Qt::Horizontal,this);
     timerSlider[i]->setRange(10,MAX_LIGHTNESS_LEVEL*10);
     timerSlider[i]->setTickInterval(10);
     //timerSlider[i]->setFocusPolicy(Qt::StrongFocus);
     //timerSlider[i]->setTickPosition(QSlider::TicksAbove);

     timerLabel[i] = new QLabel(this);
     timerLabel[i]->setFixedWidth(15);

     hLayout->addWidget(timerCheck[i]);
     hLayout->addWidget(timerEdit[i]);
     hLayout->addWidget(timerSlider[i]);
     hLayout->addWidget(timerLabel[i]);

     timerVLayout->addLayout(hLayout);
   }

   gHLayout->addLayout(timerVLayout);
   groupBox->setLayout(gHLayout);
   mainLayout->addWidget(groupBox);
   mainLayout->addStretch(10);

   this->setLayout(mainLayout);

   setTitle(tr("���Ȳ���"));

   connect(manualButton, SIGNAL(clicked()),this,SIGNAL(adjModeEditSignal()));
   connect(timerButton, SIGNAL(clicked()),this,SIGNAL(adjModeEditSignal()));
   connect(autoButton, SIGNAL(clicked()),this,SIGNAL(adjModeEditSignal()));

   connect(manualButton, SIGNAL(clicked()),this,SIGNAL(allEditSignal()));
   connect(timerButton, SIGNAL(clicked()),this,SIGNAL(allEditSignal()));
   connect(autoButton, SIGNAL(clicked()),this,SIGNAL(allEditSignal()));

   for(int i =0;i < MAX_LIGHTNESS_TIME; i ++)
   {
     connect(timerCheck[i],SIGNAL(clicked()),this,SIGNAL(allEditSignal()));
     connect(timerEdit[i],SIGNAL(timeChanged(QTime)),this,SIGNAL(allEditSignal()));
     connect(timerSlider[i],SIGNAL(valueChanged(int)),this,SIGNAL(allEditSignal()));
   }
   connect(manualSlider,SIGNAL(valueChanged(int)),this,SIGNAL(allEditSignal()));

   connect(this,SIGNAL(adjModeEditSignal()),this,SLOT(adjModeEditSlot()));
   connect(this,SIGNAL(allEditSignal()),this,SLOT(allEditSlot()));
}

void ClightnessProperty::allEditSlot()
{
    QString str = w->screenArea->getCurrentScreenStr();//getCurrentStr
    getSettingsFromWidget(str);

    for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
      timerLabel[i]->setText(QString::number(timerSlider[i]->value()/10));
    manualLabel->setText(QString::number(manualSlider->value()/10));

    sliderEditProc();
}

void ClightnessProperty::adjModeEditSlot()
{
    if(manualButton->isChecked())
    {
        for(int i=0; i < MAX_LIGHTNESS_TIME; i ++)
        {
            timerCheck[i]->setVisible(false);
            timerEdit[i]->setVisible(false);
            timerSlider[i]->setVisible(false);
            timerLabel[i]->setVisible(false);
        }

        autoLabel->setVisible(false);

        manualSlider->setVisible(true);
        manualLabel->setVisible(true);
    }
    else if(timerButton->isChecked())
    {
      for(int i=0; i < MAX_LIGHTNESS_TIME; i ++)
      {
          timerCheck[i]->setVisible(true);
          timerEdit[i]->setVisible(true);
          timerSlider[i]->setVisible(true);
          timerLabel[i]->setVisible(true);
      }

      autoLabel->setVisible(false);
      manualSlider->setVisible(false);
      manualLabel->setVisible(false);
    }
    else if(autoButton->isChecked())
    {
        for(int i=0; i < MAX_LIGHTNESS_TIME; i ++)
        {
            timerCheck[i]->setVisible(false);
            timerEdit[i]->setVisible(false);
            timerSlider[i]->setVisible(false);
            timerLabel[i]->setVisible(false);
        }

        autoLabel->setVisible(true);

        manualSlider->setVisible(false);
        manualLabel->setVisible(false);
    }

    sliderEditProc();
}

void ClightnessProperty::sliderEditProc()
{
    for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
    {
      if(timerCheck[i]->isChecked())
      {
          timerEdit[i]->setEnabled(true);//setTime(time);
          timerSlider[i]->setEnabled(true);//setValue(settings.value("timerLightness" + QString::number(i)).toInt()*10);
          timerLabel[i]->setEnabled(true);//setText(QString::number(timerSlider[i]->value()/10));
      }
      else
      {
          timerEdit[i]->setEnabled(false);//setTime(time);
          timerSlider[i]->setEnabled(false);//setValue(settings.value("timerLightness" + QString::number(i)).toInt()*10);
          timerLabel[i]->setEnabled(false);//setText(QString::number(timerSlider[i]->value()/10));
      }
    }
}

void ClightnessProperty::getSettingsFromWidget(QString str)
{
    settings.beginGroup(str);
  settings.beginGroup("lightness");
  //���ȵ��ڷ�ʽ
  if(timerButton->isChecked())
      settings.setValue("adjMode", TIME_ADJ);
  else if(autoButton->isChecked())
      settings.setValue("adjMode", AUTO_ADJ);
  else
      settings.setValue("adjMode", MANUAL_ADJ);

  for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
  {
     settings.setValue("timeCheck" + QString::number(i), timerCheck[i]->isChecked());
     settings.setValue("startHour" + QString::number(i),timerEdit[i]->time().hour());
     settings.setValue("startMin" + QString::number(i), timerEdit[i]->time().minute());
     settings.setValue("startSec" + QString::number(i),timerEdit[i]->time().second());
     settings.setValue("timerLightness" + QString::number(i), timerSlider[i]->value()/10 - 1);
  }

  settings.setValue("manualLightness", manualSlider->value()/10 - 1);
  settings.endGroup();
  settings.endGroup();
}

void ClightnessProperty::setSettingsToWidget(QString str)
{
    disconnect(this,SIGNAL(adjModeEditSignal()),this,SLOT(adjModeEditSlot()));
    disconnect(this,SIGNAL(allEditSignal()),this,SLOT(allEditSlot()));

    settings.beginGroup(str);
    settings.beginGroup("lightness");
    //���ȵ��ڷ�ʽ
    int adjMode = settings.value("adjMode").toInt();
    if(adjMode EQ MANUAL_ADJ)
       manualButton->setChecked(1);
    else
       manualButton->setChecked(0);

    if(adjMode EQ TIME_ADJ)
       timerButton->setChecked(1);
    else
       timerButton->setChecked(0);

    if(adjMode EQ AUTO_ADJ)
       autoButton->setChecked(1);
    else
       autoButton->setChecked(0);

    for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
    {
      timerCheck[i]->setChecked(settings.value("timeCheck" + QString::number(i)).toBool());
      QTime time;
      time.setHMS(settings.value("startHour" + QString::number(i)).toInt(), \
                  settings.value("startMin" + QString::number(i)).toInt(),\
                  settings.value("startSec" + QString::number(i)).toInt());
      timerEdit[i]->setTime(time);
      timerSlider[i]->setValue((settings.value("timerLightness" + QString::number(i)).toInt() + 1)*10);
      timerLabel[i]->setText(QString::number(timerSlider[i]->value()/10));
    }

    manualSlider->setValue((settings.value("manualLightness").toInt() + 1)*10);
    manualLabel->setText(QString::number(manualSlider->value()/10));

    settings.endGroup();
    settings.endGroup();

    adjModeEditSlot();
    sliderEditProc();

    connect(this,SIGNAL(adjModeEditSignal()),this,SLOT(adjModeEditSlot()));
    connect(this,SIGNAL(allEditSignal()),this,SLOT(allEditSlot()));
}

ClightnessProperty::~ClightnessProperty()
{

}

CopenCloseProperty::CopenCloseProperty(QWidget *parent):QGroupBox(parent)
{
    INT8U i;

    QHBoxLayout *hLayout;
   QVBoxLayout *vLayout;
   QLabel *openTimeLabel, *closeTimeLabel;

   hLayout = new QHBoxLayout(this);
   QGridLayout *mainLayout = new QGridLayout(this);
   closeTimeLabel = new QLabel(tr("�ر�ʱ��"),this);
   openTimeLabel = new QLabel(tr("����ʱ��"),this);
   mainLayout->addWidget(closeTimeLabel,0,1,1,1,Qt::AlignVCenter|Qt::AlignHCenter);
   mainLayout->addWidget(openTimeLabel,0,3,1,1,Qt::AlignVCenter|Qt::AlignHCenter);

   for(i = 0; i < MAX_OPEN_CLOSE_TIME; i ++)
   {
     timeCheck[i] = new QCheckBox(tr("ʹ��"),this);
     openTimeEdit[i] = new QTimeEdit(this);
     closeTimeEdit[i] = new QTimeEdit(this);

     mainLayout->addWidget(timeCheck[i], 1 + i, 0, 1, 1,Qt::AlignTop);
     mainLayout->addWidget(openTimeEdit[i], 1 + i, 1, 1, 2,Qt::AlignTop);
     mainLayout->addWidget(closeTimeEdit[i], 1 + i, 3, 1, 2,Qt::AlignTop);
   }

   hLayout->addLayout(mainLayout);
   hLayout->addStretch(10);
   setLayout(hLayout);

   for(i =0;i < MAX_LIGHTNESS_TIME; i ++)
   {
     connect(timeCheck[i], SIGNAL(clicked()),this,SIGNAL(TimeEditSignal()));
     connect(openTimeEdit[i],SIGNAL(timeChanged(QTime)),this,SIGNAL(TimeEditSignal()));
     connect(closeTimeEdit[i],SIGNAL(timeChanged(QTime)),this,SIGNAL(TimeEditSignal()));
   }

   connect(this, SIGNAL(TimeEditSignal()), this, SLOT(allEditSlot()));

   setTitle(tr("��ʱ���ػ�����"));
   timeCheckProc();
}

void CopenCloseProperty::timeCheckProc()
{
   for(int i = 0; i < MAX_OPEN_CLOSE_TIME; i ++)
    {
     openTimeEdit[i]->setEnabled(timeCheck[i]->isChecked());
     closeTimeEdit[i]->setEnabled(timeCheck[i]->isChecked());
   }
}

void CopenCloseProperty::allEditSlot()
{
    QString str = w->screenArea->getCurrentScreenStr();//getCurrentStr
    getSettingsFromWidget(str);

    timeCheckProc();
}

void CopenCloseProperty::getSettingsFromWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("openCloseTime");

    for(int i =0; i < MAX_OPEN_CLOSE_TIME;i ++)
    {
        settings.setValue("timeCheck"+QString::number(i), timeCheck[i]->isChecked());
        settings.setValue("openHour"+QString::number(i), openTimeEdit[i]->time().hour());
        settings.setValue("openMin"+QString::number(i),openTimeEdit[i]->time().minute());
        settings.setValue("openSec"+QString::number(i), openTimeEdit[i]->time().second());
        settings.setValue("closeHour"+QString::number(i), closeTimeEdit[i]->time().hour());
        settings.setValue("closeMin"+QString::number(i), closeTimeEdit[i]->time().minute());
        settings.setValue("closeSec"+QString::number(i), closeTimeEdit[i]->time().second());
    }

    settings.endGroup();
    settings.endGroup();
}
//���ػ�ʱ������
void CopenCloseProperty::setSettingsToWidget(QString str)
{
    disconnect(this, SIGNAL(TimeEditSignal()), this, SLOT(allEditSlot()));

    settings.beginGroup(str);
    settings.beginGroup("openCloseTime");

    for(int i =0; i < MAX_OPEN_CLOSE_TIME;i ++)
    {
        timeCheck[i]->setChecked(settings.value("timeCheck"+QString::number(i)).toBool());
        QTime time;
        time.setHMS(settings.value("openHour" + QString::number(i)).toInt(), \
                    settings.value("openMin" + QString::number(i)).toInt(),\
                    settings.value("openSec" + QString::number(i)).toInt());
        openTimeEdit[i]->setTime(time);

        time.setHMS(settings.value("closeHour" + QString::number(i)).toInt(), \
                    settings.value("closeMin" + QString::number(i)).toInt(),\
                    settings.value("closeSec" + QString::number(i)).toInt());
        closeTimeEdit[i]->setTime(time);
    }

    settings.endGroup();
    settings.endGroup();


    timeCheckProc();
    connect(this, SIGNAL(TimeEditSignal()), this, SLOT(allEditSlot()));
}


CopenCloseProperty::~CopenCloseProperty()
{

}

ClightnessDialog::ClightnessDialog(QWidget *parent):QDialog(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *vLayout = new QVBoxLayout(this);
   QHBoxLayout *hLayout = new QHBoxLayout(this);

   lightnessProperty = new ClightnessProperty(this);
   //lightnessProperty->setFixedWidth(370);
   //lightnessProperty->setFixedHeight(160);
   //lightnessProperty->setFixedWidth(lightnessProperty->sizeHint().width());

  sendButton = new QPushButton(tr("���Ͳ���"), this);
  udiskButton = new QPushButton(tr("����U���ļ�"),this);
  cancelButton = new QPushButton(tr("ȡ��"),this);


  hLayout ->addWidget(sendButton);
  hLayout ->addWidget(udiskButton);
  hLayout ->addWidget(cancelButton);

  vLayout->addWidget(lightnessProperty);
  vLayout->addLayout(hLayout);

  mainLayout  ->addLayout(vLayout);
  mainLayout ->addStretch(10);
  mainLayout->setSizeConstraint(QLayout::SetFixedSize);
  setLayout(mainLayout);

  this->setWindowTitle(tr("��������"));
  setAttribute(Qt::WA_DeleteOnClose);

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(sendButton, SIGNAL(clicked()), this, SLOT(sendPara()));
  connect(udiskButton, SIGNAL(clicked()), this, SLOT(udiskPara()));
}


//���Ͳ���
void sendLightnessPara()//S_COM_Status &COM_Status)
{
    //char frameBuf[BLOCK_DATA_LEN + 20];
    S_Screen_Para screenPara;
    S_Card_Para cardPara;
    //int len;

    QString str = w->screenArea->getCurrentScreenStr();

    //getScreenCardParaFromSettings(str, screenPara, cardPara); //
    //����
    /*
    len = Make_Frame((INT8U *)&screenPara.Lightness, sizeof(screenPara.Lightness),\
               (INT8U *)&screenPara.COM_Para.Addr, C_SCREEN_LIGNTNESS, 0, 0, 0, frameBuf);
    if(QT_SIM_EN)
      sendProtoData(frameBuf, len); //����ģʽ
    else
      sendProtoData(frameBuf, len);
*/

    int flag = 0;
    SET_BIT(flag, C_SCREEN_LIGNTNESS);
    if(QT_SIM_EN)
      makeProtoData(str, SIM_MODE, flag);
    else
      makeProtoData(str, COM_MODE, flag);

}


void ClightnessDialog::sendPara()
{
    S_Screen_Para screenPara;
    S_Card_Para cardPara;
    QString str = w->screenArea->getCurrentScreenStr();

    //getScreenCardParaFromSettings(str, screenPara, cardPara); //

    //initComStatus(screenPara);
    //connectScreen();
    sendLightnessPara();
    //disconnectScreen();

}

//
void ClightnessDialog::udiskPara()
{

}

void ClightnessDialog::getSettingsFromWidget(QString str)
{
  lightnessProperty->getSettingsFromWidget(str);
}

void ClightnessDialog::setSettingsToWidget(QString str)
{
  lightnessProperty->setSettingsToWidget(str);
}

ClightnessDialog::~ClightnessDialog()
{

}

CopenCloseDialog::CopenCloseDialog(QWidget *parent):QDialog(parent)
{
        QVBoxLayout *vLayout = new QVBoxLayout(this);
    QHBoxLayout *hLayout = new QHBoxLayout(this);


  openCloseProperty = new CopenCloseProperty(this);
  sendButton = new QPushButton(tr("���Ͳ���"), this);
  udiskButton = new QPushButton(tr("����U���ļ�"),this);
  cancelButton = new QPushButton(tr("ȡ��"),this);

  hLayout ->addWidget(sendButton);
  hLayout ->addWidget(udiskButton);
  hLayout ->addWidget(cancelButton);

  vLayout->addWidget(openCloseProperty);
  vLayout->addLayout(hLayout);

  setLayout(vLayout);

  this->setWindowTitle(tr("���ö�ʱ���ػ�"));
  setAttribute(Qt::WA_DeleteOnClose);

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(sendButton, SIGNAL(clicked()), this, SLOT(sendPara()));
  connect(udiskButton, SIGNAL(clicked()), this, SLOT(udiskPara()));
}

//���Ͳ���
void sendOpenClosePara()
{
    char frameBuf[BLOCK_DATA_LEN + 20];
   S_Screen_Para screenPara;
   S_Card_Para cardPara;
   int len;

   QString str = w->screenArea->getCurrentScreenStr();

   getScreenCardParaFromSettings(str, screenPara, cardPara); //

   //��ʱ���ػ�ʱ��
   /*
   len = makeFrame((char *)&screenPara.OC_Time, sizeof(screenPara.OC_Time),\
              C_SCREEN_OC_TIME, 0, frameBuf);*/

   int flag = 0;
   SET_BIT(flag, C_SCREEN_OC_TIME);
   if(QT_SIM_EN)
     makeProtoData(str, SIM_MODE, flag);
   else
     makeProtoData(str, COM_MODE, flag);
}

void CopenCloseDialog::sendPara()
{
    S_Screen_Para screenPara;
    S_Card_Para cardPara;
    QString str = w->screenArea->getCurrentScreenStr();

    //getScreenCardParaFromSettings(str, screenPara, cardPara); //

    //initComStatus(screenPara);
    //connectScreen();
    sendOpenClosePara();
    //disconnectScreen();
}

//
void CopenCloseDialog::udiskPara()
{

}

void CopenCloseDialog::getSettingsFromWidget(QString str)
{
  openCloseProperty->getSettingsFromWidget(str);
}

void CopenCloseDialog::setSettingsToWidget(QString str)
{
  openCloseProperty->setSettingsToWidget(str);
}

CopenCloseDialog::~CopenCloseDialog()
{

}

//У׼ʱ��
CadjTimeProperty::CadjTimeProperty(QWidget *parent):QGroupBox(parent)
{
    QGridLayout *mainLayout = new QGridLayout(this);

    sysTimeButton = new QRadioButton(tr("ϵͳʱ��"),parent); //ϵͳʱ��
    selfTimeButton = new QRadioButton(tr("�Զ���ʱ��"),parent); //�Զ����¼�
    dateTimeEdit = new QDateTimeEdit(parent);

    mainLayout->addWidget(sysTimeButton, 0, 0);
    mainLayout->addWidget(selfTimeButton, 1, 0);
    mainLayout->addWidget(dateTimeEdit, 1, 2);
    sysTimeButton->setChecked(true);

    QDateTime temp;
    temp =  QDateTime::currentDateTime();
    dateTimeEdit->setDateTime(temp);
    dateTimeEdit->setEnabled(false);

    setLayout(mainLayout);
    setTitle(tr("У׼ʱ��"));

    connect(sysTimeButton, SIGNAL(clicked()), this, SLOT(adjTimeModeCheck()));
    connect(selfTimeButton, SIGNAL(clicked()), this, SLOT(adjTimeModeCheck()));
}

void CadjTimeProperty::adjTimeModeCheck()
{
    if(sysTimeButton->isChecked())
    {
        dateTimeEdit->setEnabled(false);
    }
    else
    {
        QDateTime temp;
        temp =  QDateTime::currentDateTime();
        dateTimeEdit->setDateTime(temp);
        dateTimeEdit->setEnabled(true);
    }
}

CadjTimeProperty::~CadjTimeProperty()
{

}

void CadjTimeProperty::getSettingsFromWidget(QString str)
{

}

void CadjTimeProperty::setSettingsToWidget(QString str)
{

}

//У׼ʱ��Ի���
CadjTimeDialog::CadjTimeDialog(QWidget *parent):QDialog(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    QHBoxLayout *hLayout = new QHBoxLayout(this);

  adjTimeProperty = new CadjTimeProperty(this);

  sendButton = new QPushButton(tr("����"),this);
  udiskButton = new QPushButton(tr("����U���ļ�"),this);
  cancelButton = new QPushButton(tr("ȡ��"), this);

  hLayout->addWidget(sendButton);
  hLayout->addWidget(udiskButton);
  hLayout->addWidget(cancelButton);
  vLayout->addWidget(adjTimeProperty);
  vLayout->addLayout(hLayout);

  setLayout(vLayout);

  this->setWindowTitle(tr("Уʱ"));
  setAttribute(Qt::WA_DeleteOnClose);
}

CadjTimeDialog::~CadjTimeDialog()
{

}

void CadjTimeDialog::getSettingsFromWidget(QString str)
{

}

void CadjTimeDialog::setSettingsToWidget(QString str)
{

}

CsendDataDialog::CsendDataDialog(int flag, QWidget *parent):QDialog(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);


  QString str;

  lightnessCheck = new QCheckBox(tr("��������"),this);
  openCloseCheck = new QCheckBox(tr("���ö�ʱ���ػ�"),this);
  adjTimeCheck = new QCheckBox(tr("Уʱ"),this);
  QCheckBox *progCheck = new QCheckBox(tr("��Ŀ����"),this);
  progCheck->setChecked(true);
  progCheck->setEnabled(false);

  str = w->screenArea->getCurrentScreenStr();

  lightnessProperty = new ClightnessProperty(this);
  openCloseProperty = new CopenCloseProperty(this);
  adjTimeProperty = new CadjTimeProperty(this);

  lightnessProperty->setSettingsToWidget(str);
  openCloseProperty->setSettingsToWidget(str);
  adjTimeProperty->setSettingsToWidget(str);

  //lightnessProperty->setFixedWidth(370);
  //lightnessProperty->setFixedHeight(160);

  lightnessProperty->setSettingsToWidget(str);
  openCloseProperty->setSettingsToWidget(str);
  adjTimeProperty->setSettingsToWidget(str);

  sendButton = new QPushButton(tr("����"),this);
  udiskButton = new QPushButton(tr("����U���ļ�"),this);
  cancelButton = new QPushButton(tr("ȡ��"),this);

  vLayout->addWidget(lightnessCheck);

  QHBoxLayout *hLayout = new QHBoxLayout(this);
  hLayout->addWidget(lightnessProperty);
  hLayout->addStretch(10);
  vLayout->addLayout(hLayout);

  vLayout->addWidget(openCloseCheck);

  hLayout = new QHBoxLayout(this);
  hLayout->addWidget(openCloseProperty);
  hLayout->addStretch(10);
  vLayout->addLayout(hLayout);

  vLayout->addWidget(adjTimeCheck);

  hLayout = new QHBoxLayout(this);
  hLayout->addWidget(adjTimeProperty);
  hLayout->addStretch(10);
  vLayout->addLayout(hLayout);
  vLayout->addWidget(progCheck);

  hLayout = new QHBoxLayout(this);
  hLayout->addWidget(sendButton);
  hLayout->addWidget(udiskButton);
  hLayout->addWidget(cancelButton);
  vLayout->addLayout(hLayout);
  vLayout->addStretch(10);

  lightnessProperty->hide();
  openCloseProperty->hide();
  adjTimeProperty->hide();

  vLayout->setSizeConstraint(QLayout::SetFixedSize);
  setLayout(vLayout);

  if(flag EQ 0)
  {
    this->setWindowTitle(tr("��������"));
    adjTimeProperty->sysTimeButton->setChecked(true);
    udiskButton->hide();
  }
  else
  {
    this->setWindowTitle(tr("����U���ļ�"));
    adjTimeProperty->selfTimeButton->setChecked(true);
    sendButton->hide();
  }

  adjTimeProperty->adjTimeModeCheck();

  connect(lightnessCheck, SIGNAL(clicked()), this, SLOT(propertyCheckProc()));
  connect(openCloseCheck, SIGNAL(clicked()), this, SLOT(propertyCheckProc()));
  connect(adjTimeCheck, SIGNAL(clicked()), this, SLOT(propertyCheckProc()));

  connect(sendButton, SIGNAL(clicked()), this, SLOT(sendData()));
  connect(udiskButton, SIGNAL(clicked()), this, SLOT(uDiskData()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  setAttribute(Qt::WA_DeleteOnClose);
}

void CsendDataDialog::sendData()
{
    int flag = 0;
    QString str = w->screenArea->getCurrentScreenStr();

    if(lightnessCheck->isChecked())
        SET_BIT(flag, C_SCREEN_LIGNTNESS);
    if(openCloseCheck->isChecked())
        SET_BIT(flag, C_SCREEN_OC_TIME);
    if(adjTimeCheck->isChecked())
        SET_BIT(flag, C_SCREEN_TIME);

    SET_BIT(flag, C_PROG_NUM);
    SET_BIT(flag, C_PROG_PARA);
    SET_BIT(flag, C_PROG_DATA);

    if(QT_SIM_EN)
      makeProtoData(str, SIM_MODE, flag);
    else
      makeProtoData(str, COM_MODE, flag);

}

void CsendDataDialog::uDiskData()
{
    int flag = 0;
    QString str = w->screenArea->getCurrentScreenStr();

    if(lightnessCheck->isChecked())
        SET_BIT(flag, C_SCREEN_LIGNTNESS);
    if(openCloseCheck->isChecked())
        SET_BIT(flag, C_SCREEN_OC_TIME);
    if(adjTimeCheck->isChecked())
        SET_BIT(flag, C_SCREEN_TIME);

    SET_BIT(flag, C_PROG_NUM);
    SET_BIT(flag, C_PROG_PARA);
    SET_BIT(flag, C_PROG_DATA);

    if(QT_SIM_EN)
      makeProtoData(str, SIM_MODE, flag);
    else
      makeProtoData(str, UDISK_MODE, flag);
}

void CsendDataDialog::propertyCheckProc()
{
  if(lightnessCheck->isChecked())
      lightnessProperty->show();
  else
      lightnessProperty->hide();

  if(openCloseCheck->isChecked())
      openCloseProperty->show();
  else
      openCloseProperty->hide();

  if(adjTimeCheck->isChecked())
      adjTimeProperty->show();
  else
      adjTimeProperty->hide();

  this->resize(this->sizeHint());;
}

CsendDataDialog::~CsendDataDialog()
{

}

/*
//screen���Դ�
class CfacScreenProperty:public QWidget
{
    Q_OBJECT
 QGroupBox *cardGroup;
 QGroupBox *baseParaGroup;
 QGroupBox *advanceParaGroup;

 QComboBox *cardCombo; //ѡ������
 QTextEdit *cardPara; //������

 //��������
 QLineEdit *screenIDEdit; // ��ĻID
 QComboBox *dataPolarityCombo; //���ݼ���
 QComboBox *oePolarityCombo; //OE����
 QComboBox *colorCombo; //��ɫ
 QLineEdit *widthEdit; //����
 QLineEdit *heightEdit; //����
 QCheckBox *138Check;     //�Ƿ���138������
 QComboBox *scanModeCombo; //ɨ�跽ʽ

 //�߼�����
 QCheckBox *defParaCheck; //ʹ��Ĭ�ϲ���
 QComboBox *freqCombo; //ɨ��Ƶ��
 QSpinBox *lineHideCombo; //��������
 //------------------

 QPushButton *endButton;
 QPushButton *readParaButton;
 QPushButton *cancelButton;
 QPushButton *okButton;
public:
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CfacScreenProperty(QWidget *parent=0);
    ~CfacScreenProperty();
};
*/

CipInput::CipInput(QWidget *parent):QWidget(parent)
{/*
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    for(int i = 0; i < 4; i++)
    {

      edit[i] = new QLineEdit(this);
      //edit[i]->setFixedWidth(25);


      QRegExp rx("(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-4]|[01]?\\d\\d?") ;

         //ipLabel = new QLabel(tr("IP Address:"));
        // ipLineEdit = new QLineEdit;
         //ipLabel->setBuddy(ipLineEdit);

         QValidator *validator = new QRegExpValidator(rx, this);
         edit[i]->setValidator(validator);
         edit[i]->setInputMask("000.000.000.000;");


      hLayout->addWidget(edit[i],10);
      if(i!=3)
      {
        QLabel *label = new QLabel(".",this);
        label->setFixedWidth(2);
        hLayout->addWidget(label,1);
      }
    }

    hLayout->addStretch(10);
    setLayout(hLayout);
    */

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QRegExp rx("(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-4]|[01]?\\d\\d?") ;

    //ipLabel = new QLabel(tr("IP Address:"));
    // ipLineEdit = new QLineEdit;
    //ipLabel->setBuddy(ipLineEdit);

    edit = new QLineEdit(this);
    QValidator *validator = new QRegExpValidator(rx, this);
    edit->setValidator(validator);
    edit->setInputMask("000.000.000.000;");

    hLayout->addWidget(edit);
    setLayout(hLayout);
}

void CipInput::getSettingsFromWidget(QString str)
{

}

void CipInput::setSettingsToWidget(QString str)
{

}

void CipInput::setIP(int ip)
{

}

int CipInput::getIP()
{
  return 0xFFFFFFFF;
}

CipInput::~CipInput()
{

}

CcomTest::CcomTest(QWidget *parent):QGroupBox(parent)
{
  //QVBoxLayout *vLayout = new QVBoxLayout(this);
  QGridLayout *gridLayout = new QGridLayout(this);

  QLabel *comModeLabel = new QLabel(tr("ͨ�ŷ�ʽ"),this);
  comModeCombo = new QComboBox(this);
  comModeCombo->addItem(tr("����"));
  QLabel *screenIDLabel = new QLabel(tr("Ӳ����ַ"),this);
  screenIDEdit = new QSpinBox(this);
  QLabel *comPortLabel = new QLabel(tr("���ں�"),this);
  comPortEdit = new QComboBox(this);

  //QextSerialPort *comm = new QextSerialPort();
  //comm->setQueryMode(QextSerialPort::EventDriven);
/*
  QextSerialEnumerator enumer;
  QList<QextPortInfo> ports = enumer.getPorts();
  QStringList strlist;

  strlist.clear();
  for( int i = 0; i < ports.count(); ++i)
      strlist << QObject::tr(ports.at(i).portName.toLocal8Bit());
*/
  QStringList strlist = getComPortList();
  comPortEdit->addItems(strlist);

  QLabel *comBaudLabel = new QLabel(tr("������"),this);
  comBaudCombo = new QComboBox(this);
  comBaudCombo->addItem("9600");
  comBaudCombo->addItem("57600");
  QLabel *ipEditLabel = new QLabel(tr("IP��ַ"),this);
  ipEdit = new CipInput(this);

  connectButton = new QPushButton(tr("�ֶ�����"),this);
  autoTestButton = new QPushButton(tr("�Զ�����"),this);

  gridLayout->addWidget(comModeLabel, 0, 0,1,1);
  gridLayout->addWidget(comModeCombo,  0, 1,1,2);
  gridLayout->addWidget(screenIDLabel, 1, 0,1,1);
  gridLayout->addWidget(screenIDEdit, 1,1,1,2);
  gridLayout->addWidget(comPortLabel, 2, 0,1,1);
  gridLayout->addWidget(comPortEdit, 2, 1,1,2);
  gridLayout->addWidget(comBaudLabel, 3, 0,1,1);
  gridLayout->addWidget(comBaudCombo, 3, 1,1,2);
  gridLayout->addWidget(ipEditLabel, 4, 0,1,1);
  gridLayout->addWidget(ipEdit, 4,1,1,2);
  gridLayout->addWidget(connectButton, 5,0,1,3);
  gridLayout->addWidget(autoTestButton, 6,0,1,3);

  setLayout(gridLayout);
  setTitle(tr("ͨ�Ų���"));

  connect(comModeCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(editSignal()));
  connect(comPortEdit, SIGNAL(currentIndexChanged(int)), this, SIGNAL(editSignal()));
  connect(screenIDEdit, SIGNAL(valueChanged(int)), this, SIGNAL(editSignal()));
  connect(comBaudCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(editSignal()));
  connect(ipEdit, SIGNAL(editSignal()), this, SIGNAL(editSignal()));

  connect(this, SIGNAL(editSignal()), this, SLOT(editSlot()));

  //------------��ʱ����----
  ipEditLabel->setVisible(false);
  ipEdit->setVisible(false);


}
/*
    QComboBox *comModeCombo; //ͨ�ŷ�ʽ
    QSpinBox *screenIDEdit; //��ĻID��Ӳ����ַ
    QComboBox *comPortEdit; //���ں�
    QComboBox *comBaudCombo; //������
    CipInput *ipEdit; //IP��ַ
    QPushButton *connectButton; //���Ӱ�ť
 */

void CcomTest::editSlot()
{
  QString screenStr;

  screenStr = w->screenArea->getCurrentScreenStr();

  getSettingsFromWidget(screenStr);
}

void CcomTest::getSettingsFromWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("comTest");

    settings.setValue("comMode", comModeCombo->currentIndex());
    settings.setValue("screenID", screenIDEdit->value());
    settings.setValue("comPort", comPortEdit->currentIndex());
    settings.setValue("comBaud", comBaudCombo->currentIndex());
    settings.setValue("ip", ipEdit->getIP());

    settings.endGroup();
    settings.endGroup();
}

void getComTestParaFromSettings(QString str, S_Screen_Para &screenPara)
{
    settings.beginGroup(str);
    settings.beginGroup("comTest");

    screenPara.Com_Mode = settings.value("comMode").toInt();
    screenPara.Com_Port = settings.value("comPort").toInt();

    screenPara.COM_Para.Addr = settings.value("screenID").toInt();
    screenPara.COM_Para.Baud = settings.value("comBaud").toInt();

    screenPara.ETH_Para.IP = settings.value("ip").toInt();

    settings.endGroup();
    settings.endGroup();

    SET_SUM(screenPara);
}

void CcomTest::setSettingsToWidget(QString str)
{
    disconnect(this, SIGNAL(editSignal()), this, SLOT(editSlot()));

    settings.beginGroup(str);
    settings.beginGroup("comTest");

    comModeCombo->setCurrentIndex(settings.value("comMode").toInt());
    screenIDEdit->setValue(settings.value("screenID").toInt());
    comPortEdit->setCurrentIndex(settings.value("comPort").toInt());
    comBaudCombo->setCurrentIndex(settings.value("comBaud").toInt());
    ipEdit->setIP(settings.value("ip").toInt());

    settings.endGroup();
    settings.endGroup();

    connect(this, SIGNAL(editSignal()), this, SLOT(editSlot()));
}

CcomTest::~CcomTest()
{

}

//���������༭
//flag NEW_SCN��ʾ�½���Ļ����,MODI_SCN��ʾ�޸�������Ļ����,SHOW_SCN��ʾ��ʾ����
CfacScreenProperty::CfacScreenProperty(int flag, QWidget *parent):QGroupBox(parent)
{

    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    QGridLayout *gridLayout;

    QHBoxLayout *mainLayout;
    QVBoxLayout *mainVLayout;

    paraFlag = flag;

    mainVLayout = new QVBoxLayout(this);
    mainLayout = new QHBoxLayout(this);
    hLayout = new QHBoxLayout(this);

    tabWidget= new QTabWidget(this);
    //setFixedWidth(400);

    //�������group
    cardGroup = new QWidget(this);//QGroupBox(tr("�������"), this);//CnameEdit(this);
    vLayout = new QVBoxLayout(this);
    cardCombo = new QComboBox(this);
    cardCombo->setFixedWidth(100);

    //��ȡ���п����б�
    cardSettings.beginGroup("");
    QStringList cardList = cardSettings.childGroups();
    cardSettings.endGroup();

    cardCombo->addItems(cardList);

    cardParaEdit = new QTextEdit(this);
    cardParaEdit->setFocusPolicy(Qt::NoFocus); //��ֹ��������(false);
    cardParaEdit->setFixedHeight(80);


    vLayout->addWidget(cardCombo);
    vLayout->addWidget(cardParaEdit);
    cardGroup->setLayout(vLayout);
    tabWidget-> addTab(cardGroup, tr("�������"));



    //-------------
    baseParaGroup = new QWidget(this);//QGroupBox(tr("��������"),this);
    screenIDEdit = new QSpinBox(this);
    screenIDEdit->setFixedWidth(WIDTH_0);

    baudCombo = new QComboBox(this);
    baudCombo->addItem("9600");
    baudCombo->addItem("57600");
    baudCombo->setFixedWidth(WIDTH_0);

    redGreenRevCheck = new QCheckBox(tr("����ȡ��"),this);

    dataPolarityCombo = new QComboBox(this);
    dataPolarityCombo->addItem(tr("������"));
    dataPolarityCombo->addItem(tr("������"));
    dataPolarityCombo->setFixedWidth(WIDTH_0);

    oePolarityCombo = new QComboBox(this);
    oePolarityCombo->addItem(tr("����Ч"));
    oePolarityCombo->addItem(tr("����Ч"));
    oePolarityCombo->setFixedWidth(WIDTH_0);

    colorCombo = new QComboBox(this);
    colorCombo->addItem(tr("��ɫ"));
    colorCombo->addItem(tr("˫ɫ"));
    colorCombo->addItem(tr("ȫ��"));

    colorCombo->setFixedWidth(WIDTH_0);

    widthEdit = new QSpinBox(this);
    widthEdit->setFixedWidth(WIDTH_0);
    widthEdit->setSingleStep(8);
    widthEdit->setMinimum(8);
    widthEdit->setMaximum(4096);
    widthEdit->setFocusPolicy(Qt::NoFocus); //��ֹ��������
    widthEdit->setValue(256); //��ʼĬ��ֵ

    heightEdit = new QSpinBox(this);
    heightEdit->setFixedWidth(WIDTH_0);
    heightEdit->setSingleStep(8);
    heightEdit->setMinimum(8);
    heightEdit->setMaximum(4096);
    heightEdit->setFocusPolicy(Qt::NoFocus); //��ֹ��������
    heightEdit->setValue(256); //��ʼĬ��ֵ

    _138Check = new QCheckBox(tr("ʹ��138������"),this);
    scanModeCombo = new QComboBox(this);

    QLabel *screenIDLabel  = new QLabel(tr("Ӳ����ַ"),this);
    //QLabel *screenIDInfoLabel = new QLabel(tr("(����Ļ����ʱÿ������Ӧ��Ψһ)"),this);
    QLabel *baudComboLabel = new QLabel(tr("������"),this);
   QLabel *dataPolarityLabel = new QLabel(tr("���ݼ���"),this);
   QLabel *oePolarityLabel = new QLabel(tr("OE����"),this);
   QLabel *colorLabel = new QLabel(tr("��ɫ"),this);
   QLabel *widthLabel = new QLabel(tr("����"),this);
   QLabel *heightLabel = new QLabel(tr("����"),this);
   QLabel *scanModeLabel = new QLabel(tr("ɨ�跽ʽ"),this);

   gridLayout = new QGridLayout(this);

   gridLayout->addWidget(screenIDLabel, 0, 0);
   gridLayout->addWidget(screenIDEdit, 0, 1);
   gridLayout->addWidget(baudComboLabel, 0, 2);
   gridLayout->addWidget(baudCombo, 0, 3);
   gridLayout->addWidget(redGreenRevCheck,0,4,1,2);

   gridLayout->addWidget(dataPolarityLabel, 1, 0);
   gridLayout->addWidget(dataPolarityCombo, 1, 1);
   gridLayout->addWidget(oePolarityLabel, 1, 2);
   gridLayout->addWidget(oePolarityCombo, 1, 3);
   gridLayout->addWidget(_138Check, 1, 4, 1, 2);

   gridLayout->addWidget(widthLabel, 2, 0);
   gridLayout->addWidget(widthEdit, 2, 1);
   gridLayout->addWidget(heightLabel, 2, 2);
   gridLayout->addWidget(heightEdit, 2, 3);

   gridLayout->addWidget(colorLabel, 2, 4);
   gridLayout->addWidget(colorCombo, 2, 5);

   gridLayout->addWidget(scanModeLabel, 3, 0);
   gridLayout->addWidget(scanModeCombo, 3, 1, 1, 5);

   baseParaGroup->setLayout(gridLayout);
   tabWidget->addTab(baseParaGroup, tr("��������"));

   //---------------�������-------------
   netParaGroup = new QWidget(this);
   gridLayout = new QGridLayout(this);
   //newScreenIDEdit = new QLineEdit(this);
   //newScreenIDEdit->setFixedWidth(40);
   //comModeCombo = new QComboBox(this);

   //ipModeCombo = new QComboBox(this);
   ipEdit = new CipInput(this);
   //newIpEdit = new QLineEdit(this);
   maskEdit = new CipInput(this);
   gateEdit = new CipInput(this);
   macEdit = new CipInput(this);
   //QRegExp rx("(2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})");
   //QRegExpValidator validatorIP(QRegExp("[0-9]{1,3}(.[0-9]{1,3}){3,3}"), this);
   //ipEdit->setValidator(&validatorIP);


   //QLabel *ipModeComboLabel = new QLabel(tr("IP��ʽ"));
   QLabel *ipEditLabel = new QLabel(tr("��ĻIP"),this);
   //QLabel *newIpEditLabel = new QLabel(tr("��IP"),this);
   QLabel *maskEditLabel = new QLabel(tr("��������"),this);
   QLabel *gateEditLabel = new QLabel(tr("����"),this);
   QLabel *macEditLabel = new QLabel(tr("MAC��ַ"));


   //QLabel *ipPortLabel = new QLabel(tr("�˿�: 7788"));



   //gridLayout->addWidget(ipModeComboLabel, 0, 0);
   //gridLayout->addWidget(ipModeCombo, 0, 1);

   gridLayout->addWidget(ipEditLabel, 1, 0);
   gridLayout->addWidget(ipEdit, 1, 1, 1, 3);
   gridLayout->addWidget(maskEditLabel, 1, 4);
   gridLayout->addWidget(maskEdit, 1, 5,1,3);

   gridLayout->addWidget(gateEditLabel, 2, 0);
   gridLayout->addWidget(gateEdit, 2, 1, 1, 3);
   gridLayout->addWidget(macEditLabel, 2, 4);
   gridLayout->addWidget(macEdit, 2, 5, 1, 3);
   //gridLayout->addWidget(ipEditLabel, 3, 0);
   //gridLayout->addWidget(ipEdit, 5, 0, 1, 2);
   //gridLayout->addWidget(ipPortLabel, 6, 0);

   netParaGroup->setLayout(gridLayout);
   tabWidget->addTab(netParaGroup, tr("�������"));

   //tabWidget->setTabEnabled(0,false);
   //netParaGroup->setVisible(false);
   //-----------------------------------


   advanceParaGroup = new QWidget(this);//QGroupBox(tr("�߼�����"),this);
   defParaCheck = new QCheckBox(tr("ʹ��Ĭ������"),this);
   defParaCheck->setChecked(true);

   freqCombo = new QComboBox(this);

   freqCombo ->addItem(tr("1���"));
   freqCombo ->addItem(tr("2"));
   freqCombo ->addItem(tr("3"));
   freqCombo ->addItem(tr("4"));
   freqCombo ->addItem(tr("5����"));

   lineHideCombo = new QComboBox(this);

   lineHideCombo->addItem(tr("1���"));
   lineHideCombo->addItem(tr("2"));
   lineHideCombo->addItem(tr("3"));
   lineHideCombo->addItem(tr("4"));
   lineHideCombo->addItem(tr("5"));
   lineHideCombo->addItem(tr("6"));
   lineHideCombo->addItem(tr("7"));
   lineHideCombo->addItem(tr("8"));
   lineHideCombo->addItem(tr("9"));
   lineHideCombo->addItem(tr("10�"));

   dataMirrorCombo = new QComboBox(this);
   dataMirrorCombo->addItem(tr("����"));
   dataMirrorCombo->addItem(tr("����"));

   lineOrderCombo = new QComboBox(this);

   lineOrderCombo->addItem(tr("����"));
   lineOrderCombo->addItem(("+1"));
   lineOrderCombo->addItem(("-1"));

   vLayout = new QVBoxLayout(this);

   gridLayout = new QGridLayout(this);
   QLabel *freqLabel = new QLabel(tr("ʱ��Ƶ��"),this);
   QLabel *lineHideLabel = new QLabel(tr("������"),this);
   QLabel *dataMirrorLabel = new QLabel(tr("���ݾ���"),this);
   QLabel *lineOrderLabel = new QLabel(tr("��˳��"),this);

   gridLayout->addWidget(defParaCheck,0,0,1,2);

   gridLayout->addWidget(freqLabel, 1, 0);
   gridLayout->addWidget(freqCombo, 1, 1);

   gridLayout->addWidget(lineHideLabel, 1, 2);
   gridLayout->addWidget(lineHideCombo,1,3);

   gridLayout->addWidget(dataMirrorLabel, 2, 0);
   gridLayout->addWidget(dataMirrorCombo, 2, 1);

   gridLayout->addWidget(lineOrderLabel, 2, 2);
   gridLayout->addWidget(lineOrderCombo,2,3);

   advanceParaGroup->setLayout(gridLayout);
   tabWidget->addTab(advanceParaGroup, tr("�߼�����"));

   //�����ض�
   vLayout = new QVBoxLayout(this);
   hLayout = new QHBoxLayout(this);
   readParaGroup = new QWidget(this);//QGroupBox(tr("�����ش�"),this);
   readParaEdit = new QTextEdit(tr("--��ʾ���ز���--"),this);
   readParaEdit->setFocusPolicy(Qt::NoFocus); //��ֹ��������(false);
   readParaEdit->setFixedHeight(60);
   readParaButton = new QPushButton(tr("�ض�����"),this);
   importParaButton = new QPushButton(tr("�������"),this);
   vLayout->addWidget(readParaEdit);
   //hLayout->addStretch();
   hLayout->addWidget(readParaButton);
   hLayout->addWidget(importParaButton);
   vLayout->addLayout(hLayout);
   readParaGroup->setLayout(vLayout);
   tabWidget->addTab(readParaGroup, tr("�ض�����"));

   hLayout = new QHBoxLayout(this);
   endButton = new QPushButton(tr("�ر�"), this);
   loadButton = new QPushButton(tr("���ز���"), this);
   //exportButton = new QPushButton(tr("���������ļ�"), this);
  // saveButton = new QPushButton(tr("�������"), this);
   //defButton = new QPushButton(tr("�ָ�Ĭ��"), this);

   hLayout->addStretch();
   hLayout->addWidget(loadButton);
   hLayout->addStretch();
   hLayout->addWidget(endButton);
   hLayout->addStretch();
   //vLayout->addWidget(exportButton);
   //vLayout->addStretch(10);
   //vLayout->addWidget(cancelButton);
   //hLayout->addStretch(10);
   //hLayout = new QHBoxLayout(this);
   //QGroupBox *comTestGroup = new QGroupBox(this);
   //comTest = new CcomTest(this);
   //hLayout->addWidget(comTest);
   //comTestGroup->setLayout(hLayout);

   mainLayout->addWidget(tabWidget);
   //mainLayout->addWidget(endButton);
   //mainLayout->addWidget(comTest);
   //mainLayout->addLayout(vLayout);
   mainVLayout->addLayout(mainLayout);
   mainVLayout->addLayout(hLayout);

   //endButton->setVisible(false);
   //loadButton->setVisible(false);

   //mainLayout->addStretch(10);
   setLayout(mainVLayout);


   if(paraFlag EQ SHOW_SCN) //��ʾ����
   {
       setEditEnable(false);
       //comTest->setVisible(false);
       endButton->setVisible(false);
       loadButton->setVisible(false);
       tabWidget->removeTab(tabWidget->indexOf(readParaGroup));
   }
     //this->setc

  setTitle(tr("��Ļ����"));

  connect(defParaCheck, SIGNAL(stateChanged(int)), this, SLOT(defParaCheckProc()));
  connect(cardCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(cardChangeProc()));
   connect(loadButton, SIGNAL(clicked()), this, SLOT(loadParaProc()));
   connect(endButton, SIGNAL(clicked()), this, SLOT(endProc()));

   defParaCheckProc();
   cardChangeProc();
  //----��ʱ���������ɾ����
   tabWidget->removeTab(tabWidget->indexOf(netParaGroup));
}

/*
 //QComboBox *ipModeCombo; //IP��ȡ��ʽ
 //QLineEdit *ipEdit; //IP��ַ
 CipInput *ipEdit;
 //QLineEdit *newIpEdit; //��IP��ַ
 CipInput *maskEdit; //��������
 CipInput *gateEdit; //��������
 CipInput *macEdit; //mac��ַ
 //��������
 QSpinBox *screenIDEdit; // ��ĻID
 QComboBox *baudCombo; //������
 QCheckBox *redGreenRevCheck; //����
 QComboBox *dataPolarityCombo; //���ݼ���
 QComboBox *oePolarityCombo; //OE����

 QComboBox *colorCombo; //��ɫ
 QSpinBox *widthEdit; //����
 QSpinBox *heightEdit; //����
 QCheckBox *_138Check;     //�Ƿ���138������
 QComboBox *scanModeCombo; //ɨ�跽ʽ

 //�߼�����
 QCheckBox *defParaCheck; //ʹ��Ĭ�ϲ���
 QComboBox *freqCombo; //ɨ��Ƶ��
 QSpinBox *lineHideCombo; //��������
 QComboBox *dataMirrorCombo; //���ݾ���
 QComboBox *lineOrderCombo; //��˳��
 //------------------

 CcomTest *comTest;
 */

void CfacScreenProperty::getSettingsFromWidget(QString str)
{
    ipEdit->getSettingsFromWidget(str+"/facPara");
    maskEdit->getSettingsFromWidget(str+"/facPara");
    gateEdit->getSettingsFromWidget(str+"/facPara");
    macEdit->getSettingsFromWidget(str+"/facPara");
    //comTest->getSettingsFromWidget(str+"/facPara");

  settings.beginGroup(str);
  settings.beginGroup("facPara");

  settings.setValue("cardType", cardCombo->currentIndex());
  settings.setValue("screenID", screenIDEdit->value()); //Ӳ����ַ
  settings.setValue("baud", baudCombo->currentIndex());
  settings.setValue("redGreenRev", redGreenRevCheck->isChecked());
  settings.setValue("dataPolarity", dataPolarityCombo->currentIndex());
  settings.setValue("oePolarity", oePolarityCombo->currentIndex());
  settings.setValue("color", colorCombo->currentIndex());
  settings.setValue("width", widthEdit->value());
  settings.setValue("height", heightEdit->value());
  settings.setValue("_138Check", _138Check->isChecked());
  settings.setValue("scanMode", scanModeCombo->currentIndex());

  settings.setValue("advDefPara", defParaCheck->isChecked());
  settings.setValue("freq", freqCombo->currentIndex());
  settings.setValue("lineHide", lineHideCombo->currentIndex());
  settings.setValue("dataMirror", dataMirrorCombo->currentIndex());
  settings.setValue("lineOrder", lineOrderCombo->currentIndex());

  settings.setValue("setFlag", 1);
  settings.endGroup();
  settings.endGroup();


}

void CfacScreenProperty::setSettingsToWidget(QString str)
{

    ipEdit->setSettingsToWidget(str+"/facPara");
    maskEdit->setSettingsToWidget(str+"/facPara");
    gateEdit->setSettingsToWidget(str+"/facPara");
    macEdit->setSettingsToWidget(str+"/facPara");
    //comTest->setSettingsToWidget(str+"/facPara");

    settings.beginGroup(str);
    settings.beginGroup("facPara");

    cardCombo->setCurrentIndex(settings.value("cardType").toInt());
    screenIDEdit->setValue(settings.value("screenID").toInt());
    baudCombo->setCurrentIndex(settings.value("baud").toInt());
    redGreenRevCheck->setChecked(settings.value("redGreenRev").toBool());
    dataPolarityCombo->setCurrentIndex(settings.value("dataPolarity").toInt());
    oePolarityCombo->setCurrentIndex(settings.value("oePolarity").toInt());
    colorCombo->setCurrentIndex(settings.value("color").toInt());


    if(settings.value("setFlag").toInt() > 0)
    {
      widthEdit->setValue(settings.value("width").toInt());
      heightEdit->setValue(settings.value("height").toInt());
    }
    else
    {
        widthEdit->setValue(DEF_SCN_WIDTH);
        heightEdit->setValue(DEF_SCN_HEIGHT);
    }
    _138Check->setChecked(settings.value("_138Check").toBool());
    scanModeCombo->setCurrentIndex(settings.value("scanMode").toInt());

    defParaCheck->setChecked(settings.value("advDefPara").toBool());
    freqCombo->setCurrentIndex(settings.value("freq").toInt());
    lineHideCombo->setCurrentIndex(settings.value("lineHide").toInt());
    dataMirrorCombo->setCurrentIndex(settings.value("dataMirror").toInt());
    lineOrderCombo->setCurrentIndex(settings.value("lineOrder").toInt());

    settings.endGroup();
    settings.endGroup();

}

CfacScreenProperty::~CfacScreenProperty()
{

}

void CfacScreenProperty::setEditEnable(bool flag)
{
    if(flag EQ false)
    {
        cardGroup->setEnabled(false);
        netParaGroup->setEnabled(false);
        baseParaGroup->setEnabled(false);
        advanceParaGroup->setEnabled(false);
        readParaGroup->setEnabled(false);
        loadButton->setEnabled(false);
        //exportButton->setEnabled(false);
        //comTest->setEnabled(false);
    }
    else
    {
        cardGroup->setEnabled(true);
        netParaGroup->setEnabled(true);
        baseParaGroup->setEnabled(true);
        advanceParaGroup->setEnabled(true);
        readParaGroup->setEnabled(true);
        loadButton->setEnabled(true);
        //exportButton->setEnabled(true);
        //comTest->setEnabled(true);
    }
}

//���ز���
void CfacScreenProperty::loadParaProc()
{
    QString str;

    str = w->screenArea->getCurrentScreenStr(); //��ǰ��Ļstr
    qDebug("loadpara:%s",(const char *)str.toLocal8Bit());

    settings.beginGroup(str);
    settings.beginGroup("facPara");

    int width = settings.value("width").toInt();
    int height = settings.value("height").toInt();
    int color = settings.value("color").toInt();
    settings.endGroup();
    settings.endGroup();


    //if(paraFlag EQ MODI_SCN)
    {
        //��ȡ��߶ȡ���ɫ�������޸�����Ҫ������еĽ�Ŀ
        if(width != widthEdit->value() ||\
           height != heightEdit->value() ||\
           color != colorCombo->currentIndex())
        {
            if(paraFlag EQ MODI_SCN)
              QMessageBox::information(w, tr("��ʾ"),
                                     tr("���˴��޸�����Ļ�Ŀ�ȡ��߶ȡ���ɫ֮�е�һ��⽫���¸���Ļ�µ����н�Ŀ�����ã�"),tr("ȷ��"));


            //�����޸���ʾ���ڴ�С
            QMdiSubWindow * subWin =w->mdiArea->currentSubWindow();
            subWin->setFixedSize(widthEdit->value() + 8, heightEdit->value() + 34); //��ǰ��Ļ������С
            w->screenArea->setFixedSize(widthEdit->value(), heightEdit->value());

            //�����������
            QTreeWidgetItem *screenItem = w->screenArea->screenItem;
            int count = screenItem->childCount();
            for(int i = 0; i < count; i ++)
            {
                w->progManage->clickItem(screenItem->child(0),0);
                w->progManage->treeWidget->setCurrentItem(screenItem->child(0));
                w->progManage->deleteItem();
            }
            //w->screenArea->screenItem->removeChild(w->screenArea->screenItem->child(i));
            //w->progManage->settingsInit();
        }
    }

    getSettingsFromWidget(str);

    int flag = 0;
    SET_BIT(flag, C_SCREEN_BASE_PARA);
    SET_BIT(flag, C_SCREEN_COM_PARA);
    SET_BIT(flag, C_SCREEN_ETH_PARA);
    SET_BIT(flag, C_SCREEN_GPRS_PARA);
    SET_BIT(flag, C_SCAN_PARA);
    //SET_BIT(flag, C_SCREEN_OC_TIME);

    if(QT_SIM_EN)
      makeProtoData(str, SIM_MODE, flag);
    else
      makeProtoData(str, COM_MODE, flag);

  QMessageBox::information(w, tr("��ʾ"),
                         tr("�������سɹ���"),tr("ȷ��"));



}
/*
//���Ͳ���
int CfacScreenProperty::sendPara()
{
    char frameBuf[BLOCK_DATA_LEN + 20];
    S_Screen_Para screenPara;
    S_Card_Para cardPara;
    int len;

    QString str = w->screenArea->getCurrentScreenStr();

    getScreenCardParaFromSettings(str, screenPara, cardPara); //
    //��������
    len = Make_Frame((INT8U *)&screenPara.Base_Para, sizeof(screenPara.Base_Para),\
               (INT8U *)&screenPara.COM_Para.Addr, C_SCREEN_BASE_PARA, 0, 0, 0, frameBuf);

    if(QT_SIM_EN)
      sendProtoData(frameBuf, len, SIM_MODE); //����ģʽ
    else
      sendProtoData(frameBuf, len, COM_MODE);

    //ɨ�����
    len = Make_Frame((INT8U *)&screenPara.Scan_Para, sizeof(screenPara.Scan_Para),\
               (INT8U *)&screenPara.COM_Para.Addr, C_SCAN_PARA, 0, 0, 0, frameBuf);

    if(QT_SIM_EN)
      sendProtoData(frameBuf, len, SIM_MODE); //����ģʽ
    else
      sendProtoData(frameBuf, len, COM_MODE);
}
*/
void CfacScreenProperty::defParaCheckProc()
{
  if(defParaCheck->checkState()) //ѡ��
  {
    freqCombo->setCurrentIndex(0);
    lineHideCombo->setCurrentIndex(0);
    dataMirrorCombo->setCurrentIndex(0);
    lineOrderCombo->setCurrentIndex(0);

    freqCombo->setEnabled(false);
    lineHideCombo->setEnabled(false);
    dataMirrorCombo->setEnabled(false);
    lineOrderCombo->setEnabled(false);
  }
  else
  {
      freqCombo->setEnabled(true);
      lineHideCombo->setEnabled(true);
      dataMirrorCombo->setEnabled(true);
      lineOrderCombo->setEnabled(true);
  }
}

void CfacScreenProperty::cardChangeProc()
{
    S_Card_Para cardPara;
    S_Card_Para cardPara_Bak;

    memcpy(&cardPara_Bak, &Card_Para, sizeof(Card_Para));

    getCardParaFromSettings(cardCombo->currentText(), Card_Para);
    QString pointsStr = tr("����������ɫ") + QString::number(Card_Para.Max_Points) +\
                          tr("��˫ɫ") + QString::number(Card_Para.Max_Points/2);

    if(Card_Para.Flag & 0x01) //֧��ȫ��
      pointsStr += tr("��ȫ��") + QString::number(Card_Para.Max_Points/3);

    pointsStr += tr("�����߶ȣ�") + QString::number(Card_Para.Max_Height);
    cardParaEdit->setText(pointsStr);

    QString fileStr = tr("֧�֣�") +\
    ((Get_Border_Show_En()>0)?tr("�߿�"):tr("")) +\
    ((Get_Clock_Show_En()>0)?tr("������"):tr("")) +\
    ((Get_Pic_Show_En()>0)?tr("����Ļ���ı������ͼƬ������"):tr("")) +\
    ((Get_Lun_Show_En()>0)?tr("��ũ��"):tr(""))+\
    ((Get_Temp_Show_En()>0)?tr("���¶�"):tr(""))+\
    ((Get_Time_Show_En()>0)?tr("��ʱ��"):tr(""))+\
    ((Get_Timer_Show_En()>0)?tr("����ʱ"):tr(""))+\
    ((Get_Humidity_Show_En()>0)?tr("��ʪ��"):tr(""))+\
    ((Get_Noise_Show_En()>0)?tr("������"):tr(""));

    cardParaEdit->append(fileStr);

    QString modeStr = tr("������Ч��") + QString::number(Card_Para.InMode_Num) +\
                      tr("��������Ч��") + QString::number(Card_Para.OutMode_Num);
    cardParaEdit->append(modeStr);

    QString comStr = tr("ͨ�ŷ�ʽ��") +\
                     (((Card_Para.Com_Mode & COM_RS232)>0)?tr("RS232"):tr("")) +\
                     (((Card_Para.Com_Mode & COM_RS485)>0)?tr("��R485"):tr("")) +\
                     (((Card_Para.Com_Mode & COM_UDISK)>0)?tr("��U��"):tr("")) +\
                     (((Card_Para.Com_Mode & COM_ETH)>0)?tr("����̫��"):tr("")) +\
                     (((Card_Para.Com_Mode & COM_GPRS)>0)?tr("��GSM/GPRS"):tr(""));

    cardParaEdit->append(comStr);
    memcpy(&Card_Para, &cardPara_Bak, sizeof(Card_Para));
}

void CfacScreenProperty::endProc()
{

}

CsetFacPara::CsetFacPara(QWidget *parent):QMainWindow(parent)
{
    facScreenProperty = new CfacScreenProperty(MODI_SCN,this);
    this->setCentralWidget(facScreenProperty);
    this->setWindowTitle(tr("������Ļ����"));

}

CsetFacPara::~CsetFacPara()
{

}


