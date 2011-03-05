#include <QFileDialog>
#include <QSettings>
#include <QMovie>
#include <QInputDialog>
#include <QMessageBox>
#include <QextSerialPort>
#include <QextSerialEnumerator>
#include <QList>
#include <QObject>
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
//��ȡ��Ļ����
//����>0��ʾ��ȡ��������==0��ʾû�ж�ȡ������
INT8U getScreenParaFromSettings(QString screenStr, S_Screen_Para &screenPara)
{
    //��
  settings.beginGroup(screenStr);
  QString indexStr = settings.value("screenIndex").toString(); //�����Ļ
  settings.endGroup();

  //����Ļ���������ļ��ж�ȡ��Ļ����
  screenSettings.beginGroup(QString("screen/") + indexStr);
  if(settings.childKeys().size() EQ 0) //�����������Ļ??
  {
      screenSettings.endGroup();
      return 0;
  }

  screenPara.Base_Para.Addr = screenSettings.value("addr").toString().toInt();
  screenPara.Base_Para.Baud = screenSettings.value("Baud").toString().toInt();
  screenPara.Base_Para.Color = screenSettings.value("color").toString().toInt();
  screenPara.Base_Para.Width = 256;//screenSettings.value("width").toString().toInt();
  screenPara.Base_Para.Height = 256;//screenSettings.value("height").toString().toInt();
  screenPara.Base_Para.IP = screenSettings.value("ip").toString().toInt();
  screenSettings.endGroup();

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
    facProperty = new CfacScreenProperty(this);

    facProperty->setEditEnable(false);
    facProperty->comTest->setVisible(false);
    facProperty->endButton->setVisible(false);
    facProperty->loadButton->setVisible(false);
    facProperty->tabWidget->removeTab(facProperty->tabWidget->indexOf(facProperty->readParaGroup));
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
      settings.setValue("adjMode", 1);
  else if(autoButton->isChecked())
      settings.setValue("adjMode", 2);
  else
      settings.setValue("adjMode", 0);

  for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
  {
     settings.setValue("timeCheck" + QString::number(i), timerCheck[i]->isChecked());
     settings.setValue("startHour" + QString::number(i),timerEdit[i]->time().hour());
     settings.setValue("startMin" + QString::number(i), timerEdit[i]->time().minute());
     settings.setValue("startSec" + QString::number(i),timerEdit[i]->time().second());
     settings.setValue("timerLightness" + QString::number(i), timerSlider[i]->value()/10);
  }

  settings.setValue("manualLightness", manualSlider->value()/10);
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
    if(adjMode EQ 0)
       manualButton->setChecked(1);
    else
       manualButton->setChecked(0);

    if(adjMode EQ 1)
       timerButton->setChecked(1);
    else
       timerButton->setChecked(0);

    if(adjMode EQ 2)
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
      timerSlider[i]->setValue(settings.value("timerLightness" + QString::number(i)).toInt()*10);
      timerLabel[i]->setText(QString::number(timerSlider[i]->value()/10));
    }

    manualSlider->setValue(settings.value("manualLightness").toInt()*10);
    manualLabel->setText(QString::number(manualSlider->value()/10));

    settings.endGroup();
    settings.endGroup();

    adjModeEditSlot();
    sliderEditProc();

    setTitle(tr("���Ȳ���"));

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

   setTitle(tr("���ػ�����"));
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

  QextSerialEnumerator enumer;
  QList<QextPortInfo> ports = enumer.getPorts();
  QStringList strlist;

  strlist.clear();
  for( int i = 0; i < ports.count(); ++i)
      strlist << QObject::tr(ports.at(i).portName.toLocal8Bit());
  comPortEdit->addItems(strlist);

  QLabel *comBaudLabel = new QLabel(tr("������"),this);
  comBaudCombo = new QComboBox(this);
  comBaudCombo->addItem("9600");
  comBaudCombo->addItem("57600");
  QLabel *ipEditLabel = new QLabel(tr("IP��ַ"),this);
  ipEdit = new CipInput(this);

  connectButton = new QPushButton(tr("��������"),this);

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

  setLayout(gridLayout);

  //------------��ʱ����----
  ipEditLabel->setVisible(false);
  ipEdit->setVisible(false);
}

void CcomTest::getSettingsFromWidget(QString str)
{

}

void CcomTest::setSettingsToWidget(QString str)
{

}

CcomTest::~CcomTest()
{

}

//���������༭
CfacScreenProperty::CfacScreenProperty(QWidget *parent):QGroupBox(parent)
{

    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    QGridLayout *gridLayout;

    QHBoxLayout *mainLayout;
    QVBoxLayout *mainVLayout;

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
    //cardParaEdit->setFixedWidth(150);
    cardParaEdit->setFixedHeight(60);


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

    heightEdit = new QSpinBox(this);
    heightEdit->setFixedWidth(WIDTH_0);
    heightEdit->setSingleStep(8);
    heightEdit->setMinimum(8);
    heightEdit->setMaximum(4096);
    heightEdit->setFocusPolicy(Qt::NoFocus); //��ֹ��������


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
   //readParaEdit->setFixedWidth(150);
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
   comTest = new CcomTest(this);
   //hLayout->addWidget(comTest);
   //comTestGroup->setLayout(hLayout);

   mainLayout->addWidget(tabWidget);
   //mainLayout->addWidget(endButton);
   mainLayout->addWidget(comTest);
   //mainLayout->addLayout(vLayout);
   mainVLayout->addLayout(mainLayout);
   mainVLayout->addLayout(hLayout);

   //endButton->setVisible(false);
   //loadButton->setVisible(false);

   //mainLayout->addStretch(10);
   setLayout(mainVLayout);


   //this->setEnabled(false);
   //this->setc

  setTitle(tr("��װ����"));
   connect(loadButton, SIGNAL(clicked()), this, SLOT(loadParaProc()));
   connect(endButton, SIGNAL(clicked()), this, SLOT(endProc()));

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
  settings.beginGroup(str);
  settings.beginGroup("facPara");

  ipEdit->getSettingsFromWidget(str);
  maskEdit->getSettingsFromWidget(str);
  gateEdit->getSettingsFromWidget(str);
  macEdit->getSettingsFromWidget(str);

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

  settings.endGroup();
  settings.endGroup();


}

void CfacScreenProperty::setSettingsToWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("facPara");

    ipEdit->setSettingsToWidget(str);
    maskEdit->setSettingsToWidget(str);
    gateEdit->setSettingsToWidget(str);
    macEdit->setSettingsToWidget(str);

    screenIDEdit->setValue(settings.value("screenID").toInt());
    baudCombo->setCurrentIndex(settings.value("baud").toInt());
    redGreenRevCheck->setChecked(settings.value("redGreenRev").toBool());
    dataPolarityCombo->setCurrentIndex(settings.value("dataPolarity").toInt());
    oePolarityCombo->setCurrentIndex(settings.value("oePolarity").toInt());
    colorCombo->setCurrentIndex(settings.value("color").toInt());
    widthEdit->setValue(settings.value("width").toInt());
    heightEdit->setValue(settings.value("height").toInt());
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
    getSettingsFromWidget(str);
}

void CfacScreenProperty::endProc()
{

}

CsetFacPara::CsetFacPara(QWidget *parent):QMainWindow(parent)
{
    facScreenProperty = new CfacScreenProperty(this);
    this->setCentralWidget(facScreenProperty);
    this->setWindowTitle(tr("������Ļ����"));

}

CsetFacPara::~CsetFacPara()
{

}
