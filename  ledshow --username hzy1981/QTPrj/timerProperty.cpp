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
    nameEdit = new CnameEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(nameEdit);
    vLayout->addWidget(area);
    hLayout->addLayout(vLayout);

    smLineEdit = new CsmLineEdit(this);
    //hLayout->addLayout(vLayout);

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
    styleCombo->addItem(tr("0000��00ʱ00��"));
    styleCombo->addItem(tr("000��00ʱ00��"));
    styleCombo->addItem(tr("00��00ʱ00��"));
    styleCombo->addItem(tr("0000��00ʱ"));
    styleCombo->addItem(tr("000��00ʱ"));
    styleCombo->addItem(tr("00��00ʱ"));
    styleCombo->addItem(tr("0000��"));
    styleCombo->addItem(tr("000��"));
    styleCombo->addItem(tr("00��"));
    styleCombo->addItem(tr("00ʱ00��00��"));
    styleCombo->addItem(tr("00ʱ00��"));
    styleCombo->addItem(tr("00ʱ"));
    styleCombo->addItem(tr("00��00��"));
    styleCombo->addItem(tr("00��"));
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
    vLayout->addWidget(smLineEdit,1);
    vLayout->addWidget(dstTimeGroup,2);
    hLayout->addLayout(vLayout);

    simpleTextEdit = new CsimpleTextEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(simpleTextEdit);
    hLayout->addLayout(vLayout);

    showModeEdit = new CshowModeEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout ->addWidget(showModeEdit);
    hLayout->addLayout(vLayout);

    borderEdit = new CborderEdit(this);
    hLayout->addWidget(borderEdit);
    hLayout->addStretch(10);
    setLayout(hLayout);

    connectSignal();
}

//���Ա༭��SLOT
void CtimerProperty::edited()
{
    CshowArea *area;
    QTreeWidgetItem *item;

    //qDebug("propertyEdited");
    area = w->screenArea->getFocusArea(); //��ǰ�������

    if(area != (CshowArea *)0) //
    {
        //��ǰѡ�е�item
        item = area->fileItem;//w->progManage->treeWidget->currentItem();////// //w->progManage->treeWidget->currentItem();
        if(item != (QTreeWidgetItem *)0)
        {
            QString str = item->data(0,Qt::UserRole).toString();
            getSettingsFromWidget(str);
            updateTimerShowArea(area);
        }
    }
}

//ˢ����ʾ����
void updateTimerShowArea(CshowArea *area)
{
    //CshowArea *area;
    QString str;
    QTreeWidgetItem *item;

    if(area != (CshowArea *)0) //
    {
        item = area->fileItem;

        str = item->data(0,Qt::UserRole).toString();

        getTimerParaFromSettings(str,area->filePara);
        area->imageBk = getLineTextImage(str);
        area->updateFlag = true;
        //qDebug("file_para flag = %d", area->filePara.Temp_Para.Flag);
        area->update(); //ˢ����ʾ

    }
    else
    {
        ASSERT_FAILED();
    }

}

void CtimerProperty::screenCardParaChangeProc()
{
  colorCombo->setItems();
  fontSizeCombo->setItems();
}

/*
  INT8U Dst_Year; //Ŀ����
  INT8U Dst_Month; //Ŀ����
  INT8U Dst_Date; //Ŀ����
  INT8U Dst_Hour; //Ŀ��ʱ
  INT8U Dst_Min; //Ŀ���
  INT8U Dst_Sec; //Ŀ����

  INT8U Show_Mode;  //��ʾ��ʽ
  INT8U Show_Color; //��ʾ��ɫ
  INT8U Show_Font; //��ʾ�ֺ�
  INT8U Show_Posi; //��ʾλ��

  INT8U Temp; //����

  INT8U Text_Color; //������ɫ
  INT16U Text_X; //����X
  INT16U Text_Y; //����Y
  INT16U Text_Width; //�������
  INT16U Text_Height; //�����߶�
 */
//��settings�л�ȡ����
void getTimerParaFromSettings(QString str, U_File_Para &para)
{
    int tmp;
    //bool checked;
    // QString str;
    getBorderParaFromeSettings(str, para);
    para.Timer_Para.Flag = SHOW_TIMER;
    settings.beginGroup(str);

    if(settings.value("dstYear").toInt() > 2000)
      para.Timer_Para.Dst_Year = (INT8U)(settings.value("dstYear").toInt() - 2000);
    else
      para.Timer_Para.Dst_Year = 0;

    para.Timer_Para.Dst_Month = (INT8U)settings.value("dstMon").toInt();
    para.Timer_Para.Dst_Date = (INT8U)settings.value("dstDay").toInt();
    para.Timer_Para.Dst_Hour = (INT8U)settings.value("dstHour").toInt();
    para.Timer_Para.Dst_Min = (INT8U)settings.value("dstMin").toInt();
    para.Timer_Para.Dst_Sec = (INT8U)settings.value("dstSec").toInt();

    tmp = (INT8U)settings.value("color").toInt();
    para.Timer_Para.Timer_Color = getColorDataFromIndex(tmp);
    //SET_BIT(para.Timer_Para.Timer_Color, tmp);

    para.Timer_Para.Timer_Font = (INT8U)settings.value("size").toInt();
    para.Timer_Para.Timer_Type = (INT8U)settings.value("style").toInt();

    settings.beginGroup("smLine");
    para.Timer_Para.SmLineFlag = settings.value("smLineCheck").toBool();
    para.Timer_Para.LineSpace = (INT8U)settings.value("lineSpace").toInt();
    settings.endGroup();
    settings.endGroup();

    getShowModeParaFromSettings(str, para);
}

CtimerProperty::~CtimerProperty()
{

}

void CtimerProperty::connectSignal()
{
    connect(simpleTextEdit, SIGNAL(edited()), this, SLOT(edited()));
    //connect(dstDateTimeEdit, SIGNAL(edited()), this, SLOT(edited()));
    connect(smLineEdit, SIGNAL(edited()), this, SLOT(edited()));

    connect(dstDateTimeEdit, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(edited()));
    connect(colorCombo, SIGNAL(indexChangeSignal()), this, SLOT(edited()));
    connect(styleCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(edited()));
    connect(fontSizeCombo, SIGNAL(indexChangeSignal()), this, SLOT(edited()));

    connect(showModeEdit, SIGNAL(edited()), this, SLOT(edited()));
    connect(borderEdit, SIGNAL(editSignal()), this, SLOT(edited()));
}

void CtimerProperty::disconnectSignal()
{
    disconnect(simpleTextEdit, SIGNAL(edited()), this, SLOT(edited()));
    //connect(dstDateTimeEdit, SIGNAL(edited()), this, SLOT(edited()));
    disconnect(smLineEdit, SIGNAL(edited()), this, SLOT(edited()));

    disconnect(dstDateTimeEdit, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(edited()));
    disconnect(colorCombo, SIGNAL(indexChangeSignal()), this, SLOT(edited()));
    disconnect(styleCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(edited()));
    disconnect(fontSizeCombo, SIGNAL(indexChangeSignal()), this, SLOT(edited()));

    disconnect(showModeEdit, SIGNAL(edited()), this, SLOT(edited()));
    disconnect(borderEdit, SIGNAL(editSignal()), this, SLOT(edited()));
}

void CtimerProperty::getSettingsFromWidget(QString str)
{
  settings.beginGroup(str);
  int type = settings.value("type").toInt();
  if(type EQ TIMER_PROPERTY)
  {
      settings.setValue("dstYear", dstDateTimeEdit->date().year());
      settings.setValue("dstMon", dstDateTimeEdit->date().month());
      settings.setValue("dstDay", dstDateTimeEdit->date().day());
      settings.setValue("dstHour", dstDateTimeEdit->time().hour());
      settings.setValue("dstMin", dstDateTimeEdit->time().minute());
      settings.setValue("dstSec", dstDateTimeEdit->time().second());

      settings.setValue("color",   colorCombo->currentIndex());
      settings.setValue("style", styleCombo->currentIndex());
      settings.setValue("size", fontSizeCombo->currentIndex());
  }
  else
      ASSERT_FAILED();
  settings.endGroup();

  if(type EQ TIMER_PROPERTY)
  {
      nameEdit->getSettingsFromWidget(str);
      simpleTextEdit->getSettingsFromWidget(str);
      smLineEdit->getSettingsFromWidget(str);
      showModeEdit->getSettingsFromWidget(str);
      borderEdit->getSettingsFromWidget(str);
  }
}

void CtimerProperty::setSettingsToWidget(QString str)
{
    int year,month,day,hour,min,sec;
    QDate date;
    QTime time;

    disconnectSignal();

    settings.beginGroup(str);
    int type = settings.value("type").toInt();
    if(type EQ TIMER_PROPERTY)
    {
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

        colorCombo->setCurrentIndex(settings.value("color").toInt());
        styleCombo->setCurrentIndex(settings.value("style").toInt());
        fontSizeCombo->setCurrentIndex(settings.value("size").toInt());
    }
    else
        ASSERT_FAILED();
    settings.endGroup();

    if(type EQ TIMER_PROPERTY)
    {
        nameEdit->setSettingsToWidget(str);
        simpleTextEdit->setSettingsToWidget(str);
        smLineEdit->setSettingsToWidget(str);
        showModeEdit->setSettingsToWidget(str);
        borderEdit->setSettingsToWidget(str);
    }
    else
        ASSERT_FAILED();

    connectSignal();
}

void Get_Timer_Text_Point(INT8U Area_No, INT16U Width, INT16U Height, S_Point &P0)
{
    INT16U Min_Width,Min_Height;

    Min_Width = Get_Timer_Min_Width(Area_No);
    Min_Height = Get_Timer_Min_Height(Area_No);

    if(Prog_Status.File_Para[Area_No].Timer_Para.SmLineFlag == SLINE_MODE)//����
    {
      if(Width > Min_Width)
        P0.X = (Width - Min_Width) / 2;
      else
        P0.X = 0;

      if(Height > Prog_Status.File_Para[Area_No].Timer_Para.Text_Height)
        P0.Y = (Height - Prog_Status.File_Para[Area_No].Timer_Para.Text_Height)/2;
      else
        P0.Y = 0;//(Height - Prog_Status.File_Para[Area_No].Timer_Para.Text_Height)/2;
    }
    else
    {
        if(Height > Min_Height)
          P0.Y = (Height - Min_Height) / 2;
        else
          P0.Y = 0;

        if(Width > Prog_Status.File_Para[Area_No].Timer_Para.Text_Width)
          P0.X = (Width - Prog_Status.File_Para[Area_No].Timer_Para.Text_Width)/2;
        else
          P0.X = 0;//(Height - Prog_Status.File_Para[Area_No].Timer_Para.Text_Height)/2;
    }

}
