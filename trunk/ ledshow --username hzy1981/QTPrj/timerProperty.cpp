#include "timerProperty.h"
#include "mainwindow.h"
#include <QSettings>

extern MainWindow *w;
extern QSettings settings;

//������ʱ�༭
CtimerProperty::CtimerProperty(QWidget *parent):QWidget(parent)
{

    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;
    QGridLayout *gridLayout;

    hLayout = new QHBoxLayout(this);
    //mainLayout = new QGridLayout(this);

    area = new Carea(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(area);
    hLayout->addLayout(vLayout);

    smLineEdit = new CsmLineEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(smLineEdit);
    hLayout->addLayout(vLayout);

    simpleTextEdit = new CsimpleTextEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(simpleTextEdit);
    hLayout->addLayout(vLayout);

    //--------------------
    dstTimeGroup = new QGroupBox(tr("Ŀ��ʱ��༭"), this);
    dstTimeLabel = new QLabel(tr("Ŀ��ʱ��"), this);
    styleLabel = new QLabel(tr("��ʽ"), this);
    colorLabel = new QLabel(tr("��ɫ"), this);
    fontSizeLabel = new QLabel(tr("��С"), this);
    dstDateTimeEdit = new QDateTimeEdit(this);
    colorCombo = new CcolorCombo(this);
    styleCombo = new QComboBox(this);
    fontSizeCombo = new CsizeCombo(this);

    styleCombo->addItem(tr("0000��00ʱ00��00��"));
    styleCombo->addItem(tr("000��00ʱ00��00��"));
    styleCombo->addItem(tr("00��00ʱ00��00��"));
    styleCombo->addItem(tr("0000��"));
    styleCombo->addItem(tr("000��"));
    styleCombo->addItem(tr("00��"));
    styleCombo->addItem(tr("00ʱ00��00��"));
    styleCombo->addItem(tr("00��00��"));
    styleCombo->addItem(tr("00��"));

    gridLayout = new QGridLayout(this);
    gridLayout -> addWidget(dstTimeLabel, 0, 0);
    gridLayout -> addWidget(dstDateTimeEdit, 0, 1);
    gridLayout -> addWidget(colorLabel, 0, 2);
    gridLayout -> addWidget(colorCombo, 0, 3);
    gridLayout -> addWidget(styleLabel, 1, 0);
    gridLayout -> addWidget(styleCombo, 1, 1);
    gridLayout -> addWidget(fontSizeLabel, 1, 2);
    gridLayout -> addWidget(fontSizeCombo, 1, 3);
    dstTimeGroup -> setLayout(gridLayout);

    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(dstTimeGroup);
    hLayout->addLayout(vLayout);

    hLayout->addStretch(10);
    setLayout(hLayout);
}

CtimerProperty::~CtimerProperty()
{

}

void CtimerProperty::getSettingsFromWidget(QString str)
{
  settings.beginGroup(str);
  settings.setValue("dstYear", dstDateTimeEdit->date().year());
  settings.setValue("dstMon", dstDateTimeEdit->date().month());
  settings.setValue("dstDay", dstDateTimeEdit->date().day());
  settings.setValue("dstHour", dstDateTimeEdit->time().hour());
  settings.setValue("dstMin", dstDateTimeEdit->time().minute());
  settings.setValue("dstSec", dstDateTimeEdit->time().second());

  settings.setValue("color",   fontSizeCombo->currentIndex());
  settings.setValue("size", styleCombo->currentIndex());
  settings.endGroup();

  simpleTextEdit->getSettingsFromWidget(str);
  smLineEdit->getSettingsFromWidget(str);
}

void CtimerProperty::setSettingsToWidget(QString str)
{
    int year,month,day,hour,min,sec;
    QDate date;
    QTime time;

    settings.beginGroup(str);

    year = settings.value("dstYear").toInt();
    month = settings.value("dstMon").toInt();
    day = settings.value("dstDay").toInt();
    date.setDate(year, month, day);
    dstDateTimeEdit->setDate(date);

    hour = settings.value("dstHour").toInt();
    min = settings.value("dstMin").toInt();
    sec = settings.value("dstSec").toInt();
    time.setHMS(hour, min, sec, 0);
    dstDateTimeEdit->setTime(time);

    settings.endGroup();

    simpleTextEdit->setSettingsToWidget(str);
    smLineEdit->setSettingsToWidget(str);
}
