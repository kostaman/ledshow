#include <QSettings>
#include "timeProperty.h"
#include "mainwindow.h"

extern MainWindow *w;
extern QSettings settings;


//������ʱ�༭
CtimeProperty::CtimeProperty(QWidget *parent):QWidget(parent)
{
    //QGridLayout *gridLayout,*mainLayout;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;


    hLayout = new QHBoxLayout(this);
    //mainLayout = new QGridLayout(this);

    area = new Carea(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(area);
    //vLayout->addStretch();
    hLayout->addLayout(vLayout);

    smLineEdit = new CsmLineEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(smLineEdit);
    //vLayout->addStretch();
    hLayout->addLayout(vLayout);

    //textGroup = new QGroupBox(tr("�̶��ı�"), this);
    simpleTextEdit = new CsimpleTextEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(simpleTextEdit);
    //vLayout->addStretch();
    hLayout->addLayout(vLayout);

    dateTimeEdit = new CdateTimeEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(dateTimeEdit);
    //vLayout->addStretch();
    hLayout->addLayout(vLayout);
/*
    vLayout = new QVBoxLayout(this);
    vLayout ->addWidget(simpleTextEdit);

    gridLayout -> addLayout(vLayout, 0, 0);

    vLayout = new QVBoxLayout(this);
    vLayout -> addWidget(dateTimeEdit);
*/
    //hLayout ->addWidget(area);
    //hLayout ->addWidget(smLineEdit);
    //hLayout ->addWidget(simpleTextEdit);
    //hLayout ->addWidget(dateTimeEdit);
    hLayout->addStretch(10);
    //textGroup -> setLayout(gridLayout);
    //mainLayout->addWidget(textGroup, 0, 0);
    setLayout(hLayout);
}

//���Ա༭��SLOT
void CtimeProperty::edited()
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
            updateTimeShowArea(area, item);
        }
    }
}

//ˢ����ʾ����
void updateTimeShowArea(CshowArea *area, QTreeWidgetItem *item)
{
    //CshowArea *area;
    QString str;


    if(area != (CshowArea *)0) //
    {
        str = item->data(0,Qt::UserRole).toString();

        getTimeParaFromSettings(str,area->File_Para);
        area->imageBk = getLineTextImage(str);

        //qDebug("file_para flag = %d", area->File_Para.Temp_Para.Flag);
        area->update(); //ˢ����ʾ

    }
    else
    {
        ASSERT_FAILED();
    }

}

//��settings�л�ȡ����
void getTimeParaFromSettings(QString str, U_File_Para &para)
{
    int tmp;
   // QString str;

    para.Clock_Para.Flag = SHOW_TIME;
    settings.beginGroup(str);


    settings.endGroup();
}


CtimeProperty::~CtimeProperty()
{

}

void CtimeProperty::getSettingsFromWidget(QString str)
{
    settings.beginGroup(str);

    int type = settings.value("type").toInt();
    if(type == TIME_PROPERTY)
    {
        simpleTextEdit->getSettingsFromWidget(str);
        smLineEdit->getSettingsFromWidget(str);
        dateTimeEdit->getSettingsFromWidget(str);
    }
    else
        ASSERT_FAILED();

    settings.endGroup();
}

void CtimeProperty::setSettingsToWidget(QString str)
{
    settings.beginGroup(str);

    int type = settings.value("type").toInt();
    if(type == TIME_PROPERTY)
    {
        simpleTextEdit->setSettingsToWidget(str);
        smLineEdit->setSettingsToWidget(str);
        dateTimeEdit->setSettingsToWidget(str);
    }
    else
        ASSERT_FAILED();

    settings.endGroup();
}
