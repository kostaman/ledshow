#include "picProperty.h"
#include "mainwindow.h"
#include <QSettings>

extern MainWindow *w;
extern QSettings settings;

//��ȡ������PicPara��
void getPicParaFromSettings(QString str, U_File_Para &para)
{
   para.Clock_Para.Flag = SHOW_PIC;

   getShowModeParaFromSettings(str, para);
}

//ˢ����ʾ����
void updatePicShowArea(CshowArea *area)
{
    //CshowArea *area;
    QString str;
    QTreeWidgetItem *item;

    if(area != (CshowArea *)0) //
    {
        item = area->fileItem;
        str = item->data(0,Qt::UserRole).toString();

        getPicParaFromSettings(str,area->filePara);

        settings.beginGroup(str);
        settings.beginGroup("textEdit");
        area->picStr = settings.value("text").toString();
        area->page = settings.value("page").toInt();
        settings.endGroup();

        settings.beginGroup("smLine");
        area->smLineFlag = settings.value("smLineCheck").toBool();
        settings.endGroup();
/*
        settings.beginGroup("showMode"); //�Ƿ�����������ģʽ?
        area->moveLeftFlag = (settings.value("inMode").toInt() EQ MOVE_LEFT_CONTINUOUS_INDEX)?true:false;
        settings.endGroup();
*/
        settings.endGroup();

        //�Ƿ���������
        area->moveLeftFlag = checkSLineMoveLeftContinuous(str);
        area->updateFlag = true;
        //area->imageBk = getTextEditImage(MLINE_MODE, area->width(), area->height(), str, 0);

        //qDebug("file_para flag = %d", area->File_Para.Temp_Para.Flag);
        area->update(); //ˢ����ʾ

        //getSLineTextImage(area->picStr, area->width(), area->height(), 1);

    }
    else
    {
        ASSERT_FAILED();
    }

}

//���Ա༭��SLOT
void CpicProperty::showModeEdited()
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
            showModeEdit->getSettingsFromWidget(str);

            bool flag = checkSLineMoveLeftContinuous(str);
            if(flag != area->moveLeftFlag)
            {
              area->moveLeftFlag = flag;
              area->updateFlag = true;
              area->update();
            }
            //getSettingsFromWidget(str);
            //updatePicShowArea(area);
        }
    }
}

//ͼ�����Ա༭
CpicProperty::CpicProperty(QWidget *parent):QWidget(parent)
{
    QGridLayout *gridLayout;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;


    hLayout = new QHBoxLayout(this);

    area = new Carea(this);
    nameEdit = new CnameEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(nameEdit);
    vLayout ->addWidget(area);
    hLayout->addLayout(vLayout);

    textGroup = new QGroupBox(tr("�ı�����"), this);
    editButton = new QPushButton(tr("�༭��"), this);

    vLayout = new QVBoxLayout(this);
    vLayout ->addWidget(editButton);
    textGroup -> setLayout(vLayout);

    vLayout = new QVBoxLayout(this);
    vLayout ->addWidget(textGroup);
    hLayout->addLayout(vLayout);

    showModeEdit = new CshowModeEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout ->addWidget(showModeEdit);
    hLayout->addLayout(vLayout);

    hLayout->addStretch(10);
    setLayout(hLayout);

    edit = new TextEdit(this);
    //edit->getEdit()->clear();
    connectSignal();
    //connect(editButton, SIGNAL(clicked()), this, SLOT(propertyEdited()));
}

CpicProperty::~CpicProperty()
{

}

void CpicProperty::connectSignal()
{
    connect(editButton, SIGNAL(clicked()), edit, SLOT(showInit()));
    connect(showModeEdit, SIGNAL(edited()), this, SLOT(showModeEdited()));
}

void CpicProperty::disconnectSignal()
{
    disconnect(editButton, SIGNAL(clicked()), edit, SLOT(showInit()));
    disconnect(showModeEdit, SIGNAL(edited()), this, SLOT(showModeEdited()));
}

void CpicProperty::screenCardParaChangeProc()
{
  edit->screenCardParaChangeProc();
}

//��ȡsettings��
void CpicProperty::getSettingsFromWidget(QString str)
{
    nameEdit->getSettingsFromWidget(str);
    showModeEdit->getSettingsFromWidget(str);
    edit->getSettingsFromWidget(str);
}

void CpicProperty::setSettingsToWidget(QString str)
{
    disconnectSignal();

    nameEdit->setSettingsToWidget(str);
    showModeEdit->setSettingsToWidget(str);
    edit->setSettingsToWidget(str);

    connectSignal();
}

bool checkSLineMoveLeftContinuous(QString str)//Check_SLine_Move_Left_Continuous(QString str)
{
    int inMode;
    bool smLineFlag;

    settings.beginGroup(str);
    settings.beginGroup("showMode"); //�Ƿ�����������ģʽ?
    inMode = settings.value("inMode").toInt();// EQ MOVE_LEFT_CONTINUOUS_INDEX)?true:false;
    settings.endGroup();

    settings.beginGroup("smLine");
    smLineFlag = settings.value("smLineCheck").toBool();
    settings.endGroup();
    settings.endGroup();

    if(inMode EQ MOVE_LEFT_CONTINUOUS_INDEX && smLineFlag EQ 0)
        return true;
    else
        return false;
}
