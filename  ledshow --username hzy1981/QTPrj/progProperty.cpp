#include "progProperty.h"
#include <QSettings>
#include <QDate>

extern QSettings settings;
//��Ŀ���Ա༭
CprogProperty::CprogProperty(QWidget *parent):QWidget(parent)
{
    QGridLayout *gridLayout,*timerGroupLayout;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;

    hLayout = new QHBoxLayout(this);

    nameGroup = new QGroupBox(tr("��Ŀ����"),this);
    //nameLabel = new QLabel(tr("����"), this);

    nameEdit = new QLineEdit(this);
    vLayout = new QVBoxLayout(this);
    //vLayout->addWidget(nameLabel);
    vLayout->addWidget(nameEdit);
    //vLayout->addStretch();
    nameGroup->setLayout(vLayout);

    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(nameGroup);
    hLayout->addLayout(vLayout);

    //mainLayout = new QGridLayout(this); //������
    //mainLayout -> addWidget(nameLabel, 0, 0);
    //mainLayout -> addWidget(nameEdit, 0, 1);

    timerGroupLayout = new QGridLayout(this); //��ʱ���Ų���
    gridLayout = new QGridLayout(this); //�����򲼾�

    timerGroup = new QGroupBox(tr("��ʱ����"), this);

    //�����ڶ�ʱ
    dateGroup = new QGroupBox(this);
    dateTimerCheck = new QCheckBox(tr("�����ڶ�ʱ"), this);
    startDateLabel = new QLabel(tr("��ʼ����"), this);
    endDateLabel = new QLabel(tr("����������"), this);
    startDateEdit = new QDateEdit(this);
    endDateEdit = new QDateEdit(this);
    gridLayout -> addWidget(dateTimerCheck, 0, 0);
    gridLayout -> addWidget(startDateLabel, 1, 0);
    gridLayout -> addWidget(startDateEdit, 1, 1);
    gridLayout -> addWidget(endDateLabel, 2, 0);
    gridLayout -> addWidget(endDateEdit, 2, 1);
    dateGroup -> setLayout(gridLayout);
    timerGroupLayout -> addWidget(dateGroup, 0, 0);

    //�����ڶ�ʱ
    gridLayout = new QGridLayout(this);
    weekGroup = new QGroupBox( this);
    weekTimerCheck = new QCheckBox(tr("�����ڶ�ʱ"), this);
    weekCheck[0] = new QCheckBox(tr("����һ"), this);
    weekCheck[1] = new QCheckBox(tr("���ڶ�"), this);
    weekCheck[2] = new QCheckBox(tr("������"), this);
    weekCheck[3] = new QCheckBox(tr("������"), this);
    weekCheck[4] = new QCheckBox(tr("������"), this);
    weekCheck[5] = new QCheckBox(tr("������"), this);
    weekCheck[6] = new QCheckBox(tr("������"), this);
    //weekCheck[7] = new QCheckBox(tr("ȫѡ"), this);
    gridLayout -> addWidget(weekTimerCheck, 0, 0);
    gridLayout -> addWidget(weekCheck[0], 1, 0);
    gridLayout -> addWidget(weekCheck[1], 1, 1);
    gridLayout -> addWidget(weekCheck[2], 1, 2);
    gridLayout -> addWidget(weekCheck[3], 2, 0);
    gridLayout -> addWidget(weekCheck[4], 2, 1);
    gridLayout -> addWidget(weekCheck[5], 2, 2);
    gridLayout -> addWidget(weekCheck[6], 3, 0);
    //gridLayout -> addWidget(weekCheck[7], 3, 1);
    weekGroup -> setLayout(gridLayout);
    timerGroupLayout -> addWidget(weekGroup, 0, 1);

    //��ʱ�䶨ʱ
    gridLayout = new QGridLayout(this);
    timeGroup = new QGroupBox(this);
    timeCheck = new QCheckBox(tr("��ʱ�䶨ʱ"), this);
    startTimeLabel = new QLabel(tr("��ʼʱ��"), this);
    endTimeLabel = new QLabel(tr("����ʱ��"), this);
    startTimeEdit = new QTimeEdit(this);
    endTimeEdit = new QTimeEdit(this);
    gridLayout -> addWidget(timeCheck, 0, 0);
    gridLayout -> addWidget(startTimeLabel, 1, 0);
    gridLayout -> addWidget(startTimeEdit, 1, 1);
    gridLayout -> addWidget(endTimeLabel, 2, 0);
    gridLayout -> addWidget(endTimeEdit, 2, 1);
    timeGroup -> setLayout(gridLayout);
    timerGroupLayout -> addWidget(timeGroup, 0, 2);
    timerGroup -> setLayout(timerGroupLayout);//addWidget(timerGroupLayout, 1, 0);

    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(timerGroup);
    hLayout->addLayout(vLayout);

    //mainLayout -> addWidget(timerGroup, 1, 0);
    //���ų���
    gridLayout = new QGridLayout(this);
    playTimeGroup = new QGroupBox(tr("���ų���"), this);
    playTimeCheck = new QCheckBox(tr("��������"), this);
    playTimeEdit = new QLineEdit(this);
    playTimeLabel = new QLabel(tr("��"));
    gridLayout -> addWidget(playTimeCheck, 0, 0);
    gridLayout -> addWidget(playTimeEdit, 1, 0);
    gridLayout -> addWidget(playTimeLabel, 1, 1);
    playTimeGroup -> setLayout(gridLayout);

    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(playTimeGroup);
    hLayout->addLayout(vLayout);
    //mainLayout -> addWidget(playTimeGroup, 1, 1);


    //��ˮ�߿�ѡ��
    gridLayout = new QGridLayout(this);
    borderGroup = new QGroupBox(tr("��ˮ�߿�ѡ��"), this);
    borderCheck = new QCheckBox(tr("������ˮ�߿�"), this);
    widthLabel = new QLabel(tr("���"), this);
    pointsLabel = new QLabel(tr("����"), this);
    styleLabel = new QLabel(tr("��ʽ"), this);
    colorLabel = new QLabel(tr("��ɫ"), this);
    speedLabel = new QLabel(tr("�ٶ�"), this);
    usLabel = new QLabel(tr("΢��"), this);
    widthEdit = new QLineEdit(this);
    speedEdit = new QLineEdit(this);
    styleCombo = new QComboBox(this);
    colorCombo = new CcolorCombo(this);
    gridLayout -> addWidget(borderCheck, 0, 0);
    gridLayout -> addWidget(widthLabel, 1, 0);
    gridLayout -> addWidget(widthEdit, 1, 1);
    gridLayout -> addWidget(pointsLabel, 1, 2);
    gridLayout -> addWidget(styleLabel, 2, 0);
    gridLayout -> addWidget(styleCombo, 2, 1);
    gridLayout -> addWidget(colorLabel, 3, 0);
    gridLayout -> addWidget(colorCombo, 3, 1);
    gridLayout -> addWidget(speedLabel, 4, 0);
    gridLayout -> addWidget(speedEdit, 4, 1);
    gridLayout -> addWidget(usLabel, 4, 2);
    borderGroup -> setLayout(gridLayout);
    //mainLayout -> addWidget(borderGroup, 1, 2);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(borderGroup);
    hLayout->addLayout(vLayout);

    hLayout->addStretch();
    setLayout(hLayout);

  //-----------------------------------------------------
   styleCombo->addItem(tr("1��˳ʱ��"));
   styleCombo->addItem(tr("2��˳ʱ��"));
   styleCombo->addItem(tr("3��˳ʱ��"));
   styleCombo->addItem(tr("4��˳ʱ��"));
   styleCombo->addItem(tr("5��˳ʱ��"));
   styleCombo->addItem(tr("6��˳ʱ��"));
   styleCombo->addItem(tr("7��˳ʱ��"));
   styleCombo->addItem(tr("8��˳ʱ��"));

   styleCombo->addItem(tr("1����ʱ��"));
   styleCombo->addItem(tr("2����ʱ��"));
   styleCombo->addItem(tr("3����ʱ��"));
   styleCombo->addItem(tr("4����ʱ��"));
   styleCombo->addItem(tr("5����ʱ��"));
   styleCombo->addItem(tr("6����ʱ��"));
   styleCombo->addItem(tr("7����ʱ��"));
   styleCombo->addItem(tr("8����ʱ��"));

   //colorCombo->addItem(tr("��ɫ"));
   //colorCombo->addItem(tr("��ɫ"));
   //colorCombo->addItem(tr("��ɫ"));

   //�����ڶ�ʱѡ��
   dateTimerCheckProc((int)dateTimerCheck->checkState());
   //�����ڶ�ʱѡ��
   weekTimerCheckProc((int)weekTimerCheck->checkState());
   //��ʱ�䶨ʱѡ��
   timeCheckProc((int)timeCheck->checkState());
   //��������ѡ��
   playTimeCheckProc((int)timeCheck->checkState());
   //�߿�ѡ��
   borderCheckProc((int)borderCheck->checkState());

   //connect(weekCheck[7], SIGNAL(stateChanged(int)),this,SLOT(allWeekDayCheckProc(int)));
   connect(dateTimerCheck, SIGNAL(stateChanged(int)),this,SLOT(dateTimerCheckProc(int)));
   connect(weekTimerCheck, SIGNAL(stateChanged(int)),this,SLOT(weekTimerCheckProc(int)));
   connect(timeCheck, SIGNAL(stateChanged(int)),this,SLOT(timeCheckProc(int)));
   connect(playTimeCheck, SIGNAL(stateChanged(int)),this,SLOT(playTimeCheckProc(int)));
   connect(borderCheck, SIGNAL(stateChanged(int)),this,SLOT(borderCheckProc(int)));
}



CprogProperty::~CprogProperty()
{

}

/*
    //-----------����-------------
    QLabel *nameLabel;  //����
    QLineEdit *nameEdit; //���������

    //--------  �����ڶ�ʱ---------
    QGroupBox *dateGroup;
    QCheckBox *dateTimerCheck; //�����ڶ�ʱ
    QLabel *startDateLabel, *endDateLabel;
    QDateEdit *startDateEdit; //��ʼ����
    QDateEdit *endDateEdit; //��������

    //----------�����ڶ�ʱ-----------
    QGroupBox *weekGroup;
    QCheckBox *weekTimerCheck; //�����ڶ�ʱ
    QCheckBox *weekCheck[8]; //����ѡ��

    //----------��ʱ�䶨ʱ----------
    QGroupBox *timeGroup;
    QCheckBox *timeCheck; //��ʱ�䶨ʱ
    QLabel *startTimeLabel,*endTimeLabel;
    QTimeEdit *startTimeEdit; //��ʼʱ��
    QTimeEdit *endTimeEdit; //����ʱ��

    //------------��������----------
    QGroupBox *playTimeGroup; //����ʱ��
    QCheckBox *playTimeCheck; //��������
    QLineEdit *playTimeEdit; //ʱ��
    QLabel *playTimeLabel;

    //-------------�߿�ѡ��----------
    QGroupBox *borderGroup; //�߿�
    QCheckBox *borderCheck;

    QLabel *widthLabel,*styleLabel,*colorLabel,*speedLabel;
    QLabel *pointsLabel,*usLabel;
    QLineEdit *widthEdit, *speedEdit;
    QComboBox *styleCombo, *colorCombo;
 */
//��settings���õ�widget��
void CprogProperty::setSettingsToWidget(QString str)
{
    QStringList keys;
    int year,month,day,hour,min;
    QDate date;
    QTime time;

    disconnect(dateTimerCheck, SIGNAL(stateChanged(int)),this,SLOT(dateTimerCheckProc(int)));
    disconnect(weekTimerCheck, SIGNAL(stateChanged(int)),this,SLOT(weekTimerCheckProc(int)));
    disconnect(timeCheck, SIGNAL(stateChanged(int)),this,SLOT(timeCheckProc(int)));
    disconnect(playTimeCheck, SIGNAL(stateChanged(int)),this,SLOT(playTimeCheckProc(int)));
    disconnect(borderCheck, SIGNAL(stateChanged(int)),this,SLOT(borderCheckProc(int)));

    settings.beginGroup(str);
    keys = settings.allKeys();
    if(keys.isEmpty() == false)
    {
      //����
      nameEdit->setText(settings.value("name").toString());

      //�����ڶ�ʱ
      dateTimerCheck->setChecked(settings.value("dateTimerCheck").toBool());
      //startDateEdit->setDate(QDate::fromString(settings.value("startDate").toString(),"yyyyMd"));
      //endDateEdit->setDate(QDate::fromString(settings.value("endDate").toString(),"yyyyMd"));
      //��ʼ������
      year = settings.value("startYear").toInt();
      month = settings.value("startMonth").toInt();
      day = settings.value("startDay").toInt();
      date.setDate(year, month, day);
      startDateEdit->setDate(date);
      //����������
      year = settings.value("endYear").toInt();
      month = settings.value("endMonth").toInt();
      day = settings.value("endDay").toInt();
      date.setDate(year, month, day);
      endDateEdit->setDate(date);

      //�����ڶ�ʱ
      weekTimerCheck->setChecked(settings.value("weekTimerCheck").toBool());
      weekCheck[0]->setChecked(settings.value("w0").toBool());
      weekCheck[1]->setChecked(settings.value("w1").toBool());
      weekCheck[2]->setChecked(settings.value("w2").toBool());
      weekCheck[3]->setChecked(settings.value("w3").toBool());
      weekCheck[4]->setChecked(settings.value("w4").toBool());
      weekCheck[5]->setChecked(settings.value("w5").toBool());
      weekCheck[6]->setChecked(settings.value("w6").toBool());
      //weekCheck[7]->setChecked(settings.value("w7").toBool());

      //��ʱ�䶨ʱ
      timeCheck->setChecked(settings.value("timeCheck").toBool());
      //startTimeEdit->setTime(QTime::fromString(settings.value("startTime").toString(),"m.s"));
      //endTimeEdit->setTime(QTime::fromString(settings.value("endTime").toString(),"m.s"));
      hour = settings.value("startHour").toInt();
      min = settings.value("startMin").toInt();
      time.setHMS(hour, min, 0, 0);
      startTimeEdit->setTime(time);

      hour = settings.value("endHour").toInt();
      min = settings.value("endMin").toInt();
      time.setHMS(hour, min, 0, 0);
      endTimeEdit->setTime(time);

      //��������
      playTimeCheck->setChecked(settings.value("playTimeCheck").toBool());
      playTimeEdit->setText(QString::number(settings.value("playTime").toInt()));

      //�߿�ѡ��
      borderCheck->setChecked(settings.value("borderCheck").toBool());
      widthEdit->setText(QString::number(settings.value("width").toInt()));
      speedEdit->setText(QString::number(settings.value("speed").toInt()));
      styleCombo->setCurrentIndex(settings.value("style").toInt());
      colorCombo->setCurrentIndex(settings.value("color").toInt());
    }

    settings.endGroup();

    connect(dateTimerCheck, SIGNAL(stateChanged(int)),this,SLOT(dateTimerCheckProc(int)));
    connect(weekTimerCheck, SIGNAL(stateChanged(int)),this,SLOT(weekTimerCheckProc(int)));
    connect(timeCheck, SIGNAL(stateChanged(int)),this,SLOT(timeCheckProc(int)));
    connect(playTimeCheck, SIGNAL(stateChanged(int)),this,SLOT(playTimeCheckProc(int)));
    connect(borderCheck, SIGNAL(stateChanged(int)),this,SLOT(borderCheckProc(int)));
}

//��Widget��ȡ���õ�settings��,strΪSettings��group
void CprogProperty::getSettingsFromWidget(QString str)
{
    QStringList keys;

    settings.beginGroup(str);
    //keys = settings.allKeys();
    //if(keys.isEmpty() == false)
    {
      //����
      //nameEdit->setText(settings.value("name").toString());
    settings.setValue("name",QVariant(nameEdit->text()));
      //�����ڶ�ʱ
    settings.setValue("dateTimerCheck", QVariant((bool)(dateTimerCheck->checkState())));
    //settings.setValue("startDate", QVariant(startDateEdit->date().toString()));
    //endDateEdit->setDate(QDate::fromString(settings.value("endDate").toString(),"yyyyMd"));
    //settings.setValue("endDate", QVariant(endDateEdit->date().toString()));

    settings.setValue("startYear", startDateEdit->date().year());
    settings.setValue("startMonth", startDateEdit->date().month());
    settings.setValue("startDay", startDateEdit->date().day());

    settings.setValue("endYear", endDateEdit->date().year());
    settings.setValue("endMonth", endDateEdit->date().month());
    settings.setValue("endDay", endDateEdit->date().day());

    //�����ڶ�ʱ
     // weekTimerCheck->setChecked(settings.value("weekTimerCheck").toBool());
    settings.setValue("weekTimerCheck", QVariant(weekTimerCheck->checkState()));
    //weekCheck[0]->setChecked(settings.value("w0").toBool());
    settings.setValue("w0", QVariant(weekCheck[0]->checkState()));
    settings.setValue("w1", QVariant(weekCheck[1]->checkState()));
    settings.setValue("w2", QVariant(weekCheck[2]->checkState()));
    settings.setValue("w3", QVariant(weekCheck[3]->checkState()));
    settings.setValue("w4", QVariant(weekCheck[4]->checkState()));
    settings.setValue("w5", QVariant(weekCheck[5]->checkState()));
    settings.setValue("w6", QVariant(weekCheck[6]->checkState()));
    //settings.setValue("w7", QVariant(weekCheck[7]->checkState()));

      //��ʱ�䶨ʱ
    //timeCheck->setChecked(settings.value("timeCheck").toBool());
    settings.setValue("timeCheck", QVariant(timeCheck->checkState()));
    //startTimeEdit->setTime(QTime::fromString(settings.value("startTime").toString(),"m.s"));
    //settings.setValue("startTime", QVariant(startTimeEdit->time().toString()));
    //endTimeEdit->setTime(QTime::fromString(settings.value("endTime").toString(),"m.s"));
    //settings.setValue("endTime", QVariant(endTimeEdit->time().toString()));
    settings.setValue("startHour", startTimeEdit->time().hour());
    settings.setValue("startMin", startTimeEdit->time().minute());
    settings.setValue("endHour", endTimeEdit->time().hour());
    settings.setValue("endMin", endTimeEdit->time().minute());

    //��������
      //playTimeCheck->setChecked(settings.value("playTimeCheck").toBool());
    settings.setValue("playTimeCheck", QVariant(playTimeCheck->checkState()));
    //playTimeEdit->setText(settings.value("playTime").toString());
    settings.setValue("playTime", QVariant(playTimeEdit->text().toInt()));
      //�߿�ѡ��
      //borderCheck->setChecked(settings.value("boderCheck").toBool());
    settings.setValue("borderCheck", QVariant(borderCheck->checkState()));
    //widthEdit->setText(settings.value("width").toString());
    settings.setValue("width", QVariant(widthEdit->text().toInt()));
    //speedEdit->setText(settings.value("speed").toString());
    settings.setValue("speed", QVariant(speedEdit->text().toInt()));
    //styleCombo->setCurrentIndex(settings.value("style").toInt());
    settings.setValue("style", QVariant(styleCombo->currentIndex()));
    //colorCombo->setCurrentIndex(settings.value("color").toInt());
    settings.setValue("color", QVariant(colorCombo->currentIndex()));
   }

    settings.endGroup();

}

void CprogProperty::allWeekDayCheckProc(int state)
{
    bool flag;

    flag = (state==Qt::Checked)?true:false;
    if(flag == true)
    {
        for(int i = 0; i < 7; i ++)
        weekCheck[i]->setChecked(flag);
    }
}

void CprogProperty::dateTimerCheckProc(int state)
{
    bool flag;

    flag = (state==Qt::Unchecked)?false:true;

    startDateEdit->setEnabled(flag);
    endDateEdit->setEnabled(flag);
 }

void CprogProperty::weekTimerCheckProc(int state)
{
    bool flag;

    flag = (state==Qt::Unchecked)?false:true;

    weekCheck[0]->setEnabled(flag);
    weekCheck[1]->setEnabled(flag);
    weekCheck[2]->setEnabled(flag);
    weekCheck[3]->setEnabled(flag);
    weekCheck[4]->setEnabled(flag);
    weekCheck[5]->setEnabled(flag);
    weekCheck[6]->setEnabled(flag);
    //weekCheck[7]->setEnabled(flag);

}

void CprogProperty::timeCheckProc(int state)
{
    bool flag;

    flag = (state==Qt::Unchecked)?false:true;

    startTimeEdit->setEnabled(flag);
    endTimeEdit->setEnabled(flag);
}

void CprogProperty::playTimeCheckProc(int state)
{
    bool flag;

    flag = (state==Qt::Unchecked)?false:true;
    playTimeEdit->setEnabled(flag);
}

void CprogProperty::borderCheckProc(int state)
{
    bool flag;

    flag = (state==Qt::Unchecked)?false:true;

    widthEdit->setEnabled(flag);
    speedEdit->setEnabled(flag);
    styleCombo->setEnabled(flag);
    colorCombo->setEnabled(flag);
}


