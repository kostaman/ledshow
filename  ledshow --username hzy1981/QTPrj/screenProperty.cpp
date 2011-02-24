#include <QFileDialog>
#include <QSettings>
#include <QMovie>
#include <QInputDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "screenProperty.h"

extern MainWindow *w;
extern QSettings settings;
extern QSettings screenSettings;
extern QSettings cardSettings;

#define WIDTH_0 40
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
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;

    hLayout = new QHBoxLayout(this);

    vLayout = new QVBoxLayout(this);
    nameEdit = new CnameEdit(this);
    vLayout->addWidget(nameEdit);
    vLayout->addStretch(10);
    hLayout->addLayout(vLayout);

    tab = new QTabWidget(this);
    facProperty = new CfacScreenProperty(this);

    //QGroupBox *lightnessGroup = new QGroupBox(tr("���ȵ���"),this);
    //vLayout = new QVBoxLayout(this);
    lightnessProperty = new ClightnessProperty(this);
    openCloseProperty = new CopenCloseProperty(this);
    //vLayout->addWidget(lightnessProperty);
    //lightnessGroup->setLayout(vLayout);
    //facProperty->setEnabled(false);
    //facProperty->lockParaButton->setEnabled(true);
    tab->addTab(lightnessProperty, tr("���ȵ���"));
    tab->addTab(openCloseProperty, tr("��ʱ���ػ�"));

    tab->addTab(facProperty, tr("��������"));
    hLayout->addWidget(tab);
    hLayout->addStretch(10);

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
lightnessProperty->getSettingsFromWidget(str);
}

void CscreenProperty::setSettingsToWidget(QString str)
{
lightnessProperty->setSettingsToWidget(str);
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
ClightnessProperty::ClightnessProperty(QWidget *parent):QWidget(parent)
{
    INT8U i;

    QHBoxLayout *hLayout;
   QVBoxLayout *vLayout;
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
   vLayout = new QVBoxLayout(this);

   hLayout = new QHBoxLayout(this);
   manualSlider = new QSlider(Qt::Horizontal,this);
   hLayout->addWidget(manualSlider);
   vLayout->addLayout(hLayout);

   hLayout = new QHBoxLayout(this);
   autoLabel = new QLabel(tr("��ȷ���Ѱ�װ���մ�����"),this);
   hLayout->addWidget(autoLabel);
   vLayout->addLayout(hLayout);


   QVBoxLayout *timerVLayout = new QVBoxLayout(this);
   for(i = 0; i < MAX_LIGHTNESS_TIME; i ++)
   {
     hLayout = new QHBoxLayout(this);
     timerCheck[i] = new QCheckBox(tr("ʹ��"),this);
     timerEdit[i] = new QTimeEdit(this);
     timerSlider[i] = new QSlider(Qt::Horizontal,this);
     hLayout->addWidget(timerCheck[i]);
     hLayout->addWidget(timerEdit[i]);
     hLayout->addWidget(timerSlider[i]);

     timerVLayout->addLayout(hLayout);
   }

   vLayout->addLayout(timerVLayout);
   groupBox->setLayout(vLayout);
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

   connect(this,SIGNAL(adjModeEditSignal()),this,SLOT(adjModeEditSlot()));
   connect(this,SIGNAL(allEditSignal()),this,SLOT(allEditSlot()));
}

void ClightnessProperty::allEditSlot()
{

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
        }

        autoLabel->setVisible(false);

        manualSlider->setVisible(true);
    }
    else if(timerButton->isChecked())
    {
      for(int i=0; i < MAX_LIGHTNESS_TIME; i ++)
      {
          timerCheck[i]->setVisible(true);
          timerEdit[i]->setVisible(true);
          timerSlider[i]->setVisible(true);
      }

      autoLabel->setVisible(false);
      manualSlider->setVisible(false);
    }
    else if(autoButton->isChecked())
    {
        for(int i=0; i < MAX_LIGHTNESS_TIME; i ++)
        {
            timerCheck[i]->setVisible(false);
            timerEdit[i]->setVisible(false);
            timerSlider[i]->setVisible(false);
        }

        autoLabel->setVisible(true);

        manualSlider->setVisible(false);
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
     settings.setValue("timerLightness" + QString::number(i), timerSlider[i]->value());
  }

  settings.setValue("manualLightness", manualSlider->value());
  settings.endGroup();
  settings.endGroup();
}

void ClightnessProperty::setSettingsToWidget(QString str)
{
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
      timerSlider[i]->setValue(settings.value("timerLightness" + QString::number(i)).toInt());
     }

    manualSlider->setValue(settings.value("manualLightness").toInt());

    settings.endGroup();
    settings.endGroup();
}

ClightnessProperty::~ClightnessProperty()
{

}

CopenCloseProperty::CopenCloseProperty(QWidget *parent):QWidget(parent)
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
 QSpinBox *lineHideBox; //��������
 //------------------

 QPushButton *lockParaButton;
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
//���������༭
CfacScreenProperty::CfacScreenProperty(QWidget *parent):QWidget(parent)
{
    QTabWidget *tabWidget;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    QGridLayout *gridLayout;

    QHBoxLayout *mainLayout;

    mainLayout = new QHBoxLayout(this);
    hLayout = new QHBoxLayout(this);

    tabWidget= new QTabWidget(this);
    //setFixedWidth(400);

    //�������group
    cardGroup = new QWidget(this);//QGroupBox(tr("�������"), this);//CnameEdit(this);
    vLayout = new QVBoxLayout(this);
    cardCombo = new QComboBox(this);
    cardCombo->setFixedWidth(100);
    cardParaEdit = new QTextEdit(this);
    //cardParaEdit->setFixedWidth(150);
    cardParaEdit->setFixedHeight(60);


    vLayout->addWidget(cardCombo);
    vLayout->addWidget(cardParaEdit);
    cardGroup->setLayout(vLayout);
    tabWidget-> addTab(cardGroup, tr("�������"));

    comParaGroup = new QWidget(this);//QGroupBox(tr("ͨ�Ų���"),this);
    gridLayout = new QGridLayout(this);
    screenIDEdit = new QLineEdit(this);
    screenIDEdit->setFixedWidth(40);
    newScreenIDEdit = new QLineEdit(this);
    newScreenIDEdit->setFixedWidth(40);
    comModeCombo = new QComboBox(this);
    baudCombo = new QComboBox(this);
    ipModeCombo = new QComboBox(this);
    ipEdit = new QLineEdit(this);
    newIpEdit = new QLineEdit(this);
    maskEdit = new QLineEdit(this);
    gateEdit = new QLineEdit(this);
    //QRegExp rx("(2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})");
    //QRegExpValidator validatorIP(QRegExp("[0-9]{1,3}(.[0-9]{1,3}){3,3}"), this);
    //ipEdit->setValidator(&validatorIP);

    QLabel *screenIDLabel  = new QLabel(tr("��ǰ����"),this);
    QLabel *newScreenIDLabel = new QLabel(tr("������"),this);
    QLabel *screenIDInfoLabel = new QLabel(tr("(����Ļ����ʱÿ������Ӧ��Ψһ)"),this);
    QLabel *comModeLabel = new QLabel(tr("ͨ�ŷ�ʽ"),this);
    QLabel *baudComboLabel = new QLabel(tr("������"),this);
    QLabel *ipModeComboLabel = new QLabel(tr("IP��ʽ"));
    QLabel *ipEditLabel = new QLabel(tr("��ǰIP"),this);
    QLabel *newIpEditLabel = new QLabel(tr("��IP"),this);
    QLabel *maskEditLabel = new QLabel(tr("��������"),this);
    QLabel *gateEditLabel = new QLabel(tr("����"),this);

    //QLabel *ipPortLabel = new QLabel(tr("�˿�: 7788"));

    gridLayout->addWidget(screenIDLabel, 0, 0);
    gridLayout->addWidget(screenIDEdit, 0, 1);
    gridLayout->addWidget(newScreenIDLabel, 0, 2);
    gridLayout->addWidget(newScreenIDEdit, 0, 3);
    gridLayout->addWidget(screenIDInfoLabel,0, 4, 1, 3);

    gridLayout->addWidget(comModeLabel, 1, 0);
    gridLayout->addWidget(comModeCombo, 1, 1);
    gridLayout->addWidget(baudComboLabel, 1, 2);
    gridLayout->addWidget(baudCombo, 1, 3);
    gridLayout->addWidget(ipModeComboLabel, 1, 4);
    gridLayout->addWidget(ipModeCombo, 1, 5);

    gridLayout->addWidget(ipEditLabel, 2, 0);
    gridLayout->addWidget(ipEdit, 2, 1, 1, 3);
    gridLayout->addWidget(newIpEditLabel, 2, 4);
    gridLayout->addWidget(newIpEdit, 2, 5,1,3);
    gridLayout->addWidget(maskEditLabel, 3, 0);
    gridLayout->addWidget(maskEdit, 3, 1,1,3);
    gridLayout->addWidget(gateEditLabel, 3, 4);
    gridLayout->addWidget(gateEdit, 3, 5, 1, 3);

    //gridLayout->addWidget(ipEditLabel, 3, 0);
    //gridLayout->addWidget(ipEdit, 5, 0, 1, 2);
    //gridLayout->addWidget(ipPortLabel, 6, 0);

    comParaGroup->setLayout(gridLayout);
    tabWidget->addTab(comParaGroup, tr("ͨ�Ų���"));

    //-------------
    baseParaGroup = new QWidget(this);//QGroupBox(tr("��������"),this);
    //sscreenIDEdit= new QLineEdit(this);
    //screenIDEdit->setFixedWidth(WIDTH_0 * 2);

    dataPolarityCombo = new QComboBox(this);
    //dataPolarityCombo->setFixedWidth(WIDTH_0);

    oePolarityCombo = new QComboBox(this);
    //oePolarityCombo->setFixedWidth(WIDTH_0);

    colorCombo = new QComboBox(this);
    //colorCombo->setFixedWidth(WIDTH_0);

    widthEdit = new QLineEdit(this);
    //widthEdit->setFixedWidth(WIDTH_0);

    heightEdit = new QLineEdit(this);
    //heightEdit->setFixedWidth(WIDTH_0);

    _138Check = new QCheckBox(tr("ʹ��138������"),this);
    scanModeCombo = new QComboBox(this);


   QLabel *dataPolarityLabel = new QLabel(tr("���ݼ���"),this);
   QLabel *oePolarityLabel = new QLabel(tr("OE����"),this);
   QLabel *colorLabel = new QLabel(tr("��ɫ"),this);
   QLabel *widthLabel = new QLabel(tr("����"),this);
   QLabel *heightLabel = new QLabel(tr("����"),this);
   QLabel *scanModeLabel = new QLabel(tr("ɨ�跽ʽ"),this);

   gridLayout = new QGridLayout(this);
   //gridLayout->addWidget(screenIDLabel, 0, 0);
   //gridLayout->addWidget(screenIDEdit, 0, 1, 1, 2);

   gridLayout->addWidget(dataPolarityLabel, 0, 0);
   gridLayout->addWidget(dataPolarityCombo, 0, 1);
   gridLayout->addWidget(oePolarityLabel, 0, 2);
   gridLayout->addWidget(oePolarityCombo, 0, 3);

   gridLayout->addWidget(_138Check, 1, 0, 1, 2);
   gridLayout->addWidget(colorLabel, 1, 2);
   gridLayout->addWidget(colorCombo, 1, 3);

   gridLayout->addWidget(widthLabel, 2, 0);
   gridLayout->addWidget(widthEdit, 2, 1);
   gridLayout->addWidget(heightLabel, 2, 2);
   gridLayout->addWidget(heightEdit, 2, 3);



   gridLayout->addWidget(scanModeLabel, 3, 0);
   gridLayout->addWidget(scanModeCombo, 3, 1, 1, 3);

   baseParaGroup->setLayout(gridLayout);
   tabWidget->addTab(baseParaGroup, tr("��������"));

   advanceParaGroup = new QWidget(this);//QGroupBox(tr("�߼�����"),this);
   defParaCheck = new QCheckBox(tr("ʹ��Ĭ������"),this);
   freqCombo = new QComboBox(this);
   lineHideBox = new QSpinBox(this);
   dataMirrorCombo = new QComboBox(this);
   lineOrderCombo = new QComboBox(this);

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
   gridLayout->addWidget(lineHideBox,1,3);

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

   vLayout = new QVBoxLayout(this);
   lockParaButton = new QPushButton(tr("�༭����"), this);
   sendButton = new QPushButton(tr("���Ͳ���"), this);
   exportButton = new QPushButton(tr("���������ļ�"), this);
  // saveButton = new QPushButton(tr("�������"), this);
   //defButton = new QPushButton(tr("�ָ�Ĭ��"), this);
   vLayout->addWidget(lockParaButton);
   vLayout->addWidget(sendButton);
   vLayout->addWidget(exportButton);
   //vLayout->addStretch(10);
   //vLayout->addWidget(cancelButton);
   //hLayout->addStretch(10);

   mainLayout->addWidget(tabWidget);
   //mainLayout->addWidget(lockParaButton);
   mainLayout->addLayout(vLayout);
   //mainLayout->addStretch(10);
   setLayout(mainLayout);

  setEditEnable(false);
   //this->setEnabled(false);
   //this->setc

   connect(lockParaButton, SIGNAL(clicked()), this, SLOT(lockParaProc()));
    //connect(openButton, SIGNAL(clicked()), this, SLOT(openscreenFile()));
}

CfacScreenProperty::~CfacScreenProperty()
{

}

void CfacScreenProperty::setEditEnable(bool flag)
{
    if(flag EQ false)
    {
        cardGroup->setEnabled(false);
        comParaGroup->setEnabled(false);
        baseParaGroup->setEnabled(false);
        advanceParaGroup->setEnabled(false);
        readParaGroup->setEnabled(false);
        sendButton->setEnabled(false);
        exportButton->setEnabled(false);
    }
    else
    {
        cardGroup->setEnabled(true);
        comParaGroup->setEnabled(true);
        baseParaGroup->setEnabled(true);
        advanceParaGroup->setEnabled(true);
        readParaGroup->setEnabled(true);
        sendButton->setEnabled(true);
        exportButton->setEnabled(true);
    }
}

void CfacScreenProperty::lockParaProc()
{
    if(lockParaButton->text() EQ tr("�༭����"))
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("����������"),
                                             tr("����"), QLineEdit::Password,
                                             tr(""), &ok);
        if (ok && text EQ "168")
        {
            lockParaButton->setText(tr("���沢����"));
            setEditEnable(true);
            //w->property->setWindowModality(Qt::WindowModal);
            //w->property->show();
            //this->show();
       }
       else if(ok)
        {
           QMessageBox::information(0, tr(APP_NAME),
                                    tr("�������!"),tr("ȷ��"));

       }
    }
    else
    {
        lockParaButton->setText(tr("�༭����"));
        setEditEnable(false);
    }

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
