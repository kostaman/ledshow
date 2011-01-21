#include <QHBoxLayout>
#include <QSettings>
#include "tempProperty.h"
#include "simpleTextEdit.h"
#include "showArea.h"
#include "mainwindow.h"


extern MainWindow *w;

extern QSettings settings;
Ctemp::Ctemp(QWidget *parent):QGroupBox(parent)
{
    QHBoxLayout *hLayout;
    QLabel *label;

    tempCombo = new QComboBox(this);
    colorCombo = new CcolorCombo(this);
    sizeCombo = new CsizeCombo(this);
    label = new QLabel(tr("��ʽ"),this);
    /*
    {"�¶� %2d.%d��", 11},
    {"�¶� %2d��", 9},
    {" %2d.%d��", 7},
    {" %2d��",5}
    */
    tempCombo->addItem(tr("�¶� 25.0��"));
    tempCombo->addItem(tr("�¶� 25��"));
    tempCombo->addItem(tr(" 25.0��"));
    tempCombo->addItem(tr(" 25��"));

    hLayout = new QHBoxLayout(this);
    hLayout ->addWidget(label);
    hLayout->addWidget(tempCombo);

    hLayout->addWidget(sizeCombo);
    hLayout->addWidget(colorCombo);

    setLayout(hLayout);
    setTitle(tr("�¶�����"));

    connect(tempCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
    connect(colorCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
    connect(sizeCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
}

void Ctemp::getSettingsFromWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("tempStyle");
    settings.setValue("tempCombo", tempCombo->currentIndex());
    settings.setValue("color", colorCombo->currentIndex());
    settings.setValue("size", sizeCombo->currentIndex());
    settings.endGroup();
    settings.endGroup();

    //colorCombo->getSettingsFromWidget(str);
    //sizeCombo->getSettingsFromWidget(str);

}

void Ctemp::setSettingsToWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("tempStyle");
    //settings.setValue("tempCombo", tempCombo->currentIndex());
    tempCombo->setCurrentIndex(settings.value("tempCombo").toInt());
    colorCombo->setCurrentIndex(settings.value("color").toInt());
    sizeCombo->setCurrentIndex(settings.value("size").toInt());
    settings.endGroup();
    settings.endGroup();

    //colorCombo->setSettingsTomWidget(str);
    //sizeCombo->setSettingsToWidget(str);
}


Ctemp::~Ctemp()
{

}
//������ʱ�༭
CtempProperty::CtempProperty(QWidget *parent):QWidget(parent)
{
    //QGridLayout *gridLayout,*mainLayout;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;

    hLayout = new QHBoxLayout(this);
    vLayout = new QVBoxLayout(this);

    nameEdit = new CnameEdit(this);
    area = new Carea(this);
    vLayout->addWidget(nameEdit);
    vLayout->addWidget(area);
    hLayout->addLayout(vLayout);
    //textGroup = new QGroupBox(tr("�̶��ı�"), this);
    simpleTextEdit = new CsimpleTextEdit(this);
    tempStyle = new Ctemp(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(simpleTextEdit);
    vLayout->addWidget(tempStyle);

    showModeEdit = new CshowModeEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout ->addWidget(showModeEdit);

    hLayout->addLayout(vLayout);
    hLayout->addStretch(10);
    setLayout(hLayout);

    connectSignal();

}

CtempProperty::~CtempProperty()
{

}

//��settings�л�ȡ����
void getTempParaFromSettings(QString str, U_File_Para &para)
{
    int tmp;

    para.Temp_Para.Flag = SHOW_TEMP;
    settings.beginGroup(str);
    settings.beginGroup("tempStyle");

    para.Temp_Para.Temp_Type = settings.value("tempCombo").toInt();
    tmp = settings.value("color").toInt();
    para.Temp_Para.Temp_Color = 0;
    SET_BIT(para.Temp_Para.Temp_Color, tmp);
    para.Temp_Para.Temp_Font = settings.value("size").toInt();

    settings.endGroup();
    settings.endGroup();

    getShowModeParaFromSettings(str, para);

}
//ˢ����ʾ����
void updateTempShowArea(CshowArea *area)
{
    //CshowArea *area;
    QString str;
    QTreeWidgetItem *item;

    if(area != (CshowArea *)0) //
    {
        item = area->fileItem;

        str = item->data(0,Qt::UserRole).toString();

        getTempParaFromSettings(str,area->filePara);
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


//���Ա༭��SLOT
void CtempProperty::edited()
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
            updateTempShowArea(area);
        }
    }
}

void CtempProperty::connectSignal()
{
    //connect(timeDiffEdit, SIGNAL(edited()), this, SLOT(edited()));
    connect(simpleTextEdit, SIGNAL(edited()), this, SLOT(edited()));
    connect(tempStyle, SIGNAL(edited()), this, SLOT(edited()));
    connect(showModeEdit, SIGNAL(edited()), this, SLOT(edited()));
    //connect(smLineEdit, SIGNAL(edited()), this, SLOT(edited()));
}

void CtempProperty::disconnectSignal()
{
    //connect(timeDiffEdit, SIGNAL(edited()), this, SLOT(edited()));
    disconnect(simpleTextEdit, SIGNAL(edited()), this, SLOT(edited()));
    disconnect(tempStyle, SIGNAL(edited()), this, SLOT(edited()));
    disconnect(showModeEdit, SIGNAL(edited()), this, SLOT(edited()));
    //connect(smLineEdit, SIGNAL(edited()), this, SLOT(edited()));
}

void CtempProperty::getSettingsFromWidget(QString str)
{
  simpleTextEdit->getSettingsFromWidget(str);
  tempStyle->getSettingsFromWidget(str);
  nameEdit->getSettingsFromWidget(str);

}

void CtempProperty::setSettingsToWidget(QString str)
{
    disconnectSignal();
    simpleTextEdit->setSettingsToWidget(str);
    tempStyle->setSettingsToWidget(str);
    nameEdit->setSettingsToWidget(str);
    connectSignal();
}
