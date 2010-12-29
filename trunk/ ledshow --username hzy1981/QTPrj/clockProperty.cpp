 #include "mainwindow.h"
#include "showArea.h"
#include "clockProperty.h"
#include "colorCombo.h"
#include <QSettings>

#define POSI_STEP 1

extern MainWindow *w;
extern QSettings settings;

CposiEdit::CposiEdit(QWidget *parent):QGroupBox(parent)
{
    setTitle(tr("����λ�õ���"));
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;

    //vLayout = new QVBoxLayout(this);
    hLayout = new QHBoxLayout(this);

    item = new QComboBox(this);
    item->addItem(tr("�̶��ı�"));
    item->addItem(tr("����"));
    item->addItem(tr("����"));

    left = new QPushButton(tr("��"));
    right = new QPushButton(tr("��"));
    up = new QPushButton(tr("��"));
    down = new QPushButton(tr("��"));
    def = new QPushButton(tr("Ĭ��"));

    int width = 30;
    left->setFixedWidth(width);
    right->setFixedWidth(width);
    up->setFixedWidth(width);
    down->setFixedWidth(width);
    def->setFixedWidth(width);

    hLayout->addWidget(item);
    hLayout->addWidget(left);
    hLayout->addWidget(right);
    hLayout->addWidget(up);
    hLayout->addWidget(down);
    hLayout->addWidget(def);
    hLayout->addStretch();
    setLayout(hLayout);
}


CposiEdit::~CposiEdit()
{

}

//ʱ�����Ա༭
CclockProperty::CclockProperty(QWidget *parent):QWidget(parent)
{
    QGridLayout *gridLayout;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;


    hLayout = new QHBoxLayout(this);
    vLayout = new QVBoxLayout(this);

    area = new Carea(this);
    nameEdit = new CnameEdit(this);

    vLayout->addWidget(nameEdit);
    vLayout ->addWidget(area);
    hLayout->addLayout(vLayout);

    editGroup = new QGroupBox(tr("��������"),this);
    pointRadiusLabel = new QLabel(tr("����"), this);
    point369RadiusLabel = new QLabel(tr("369��"), this);
    hourWidthLabel = new QLabel(tr("Сʱ"), this);
    minWidthLabel = new QLabel(tr("����"), this);
    secWidthLabel = new QLabel(tr("����"), this);
/*
    pointColorLabel = new QLabel(tr("������ɫ"), this);
    point369ColorLabel = new QLabel(tr("369����ɫ"), this);
    hourColorLabel = new QLabel(tr("Сʱ��ɫ"), this);
    minColorLabel = new QLabel(tr("������ɫ"), this);
    secColorLabel = new QLabel(tr("������ɫ"), this);
*/
    int width = 20;
    pointRadiusEdit = new QLineEdit(this);
    pointRadiusEdit->setFixedWidth(width);
    point369RadiusEdit = new QLineEdit(this);
    point369RadiusEdit->setFixedWidth(width);
    hourWidthEdit = new QLineEdit(this);
    hourWidthEdit->setFixedWidth(width);
    minWidthEdit= new QLineEdit(this);
    minWidthEdit->setFixedWidth(width);
    secWidthEdit = new QLineEdit(this);
    secWidthEdit->setFixedWidth(width);

    pointColorCombo = new CcolorCombo(this);
    point369ColorCombo = new CcolorCombo(this);
    hourColorCombo = new CcolorCombo(this);
    minColorCombo = new CcolorCombo(this);
    secColorCombo = new CcolorCombo(this);

    gridLayout = new QGridLayout(this);
    gridLayout -> addWidget(pointRadiusLabel, 0, 0);
    gridLayout -> addWidget(pointRadiusEdit, 0, 1);
    //gridLayout -> addWidget(pointColorLabel, 0, 2);
    gridLayout -> addWidget(pointColorCombo, 0, 2);

    gridLayout -> addWidget(point369RadiusLabel, 1, 0);
    gridLayout -> addWidget(point369RadiusEdit, 1, 1);
    //gridLayout -> addWidget(point369ColorLabel, 1, 2);
    gridLayout -> addWidget(point369ColorCombo, 1, 2);

    gridLayout -> addWidget(hourWidthLabel, 2, 0);
    gridLayout -> addWidget(hourWidthEdit, 2, 1);
    //gridLayout -> addWidget(hourColorLabel, 2, 2);
    gridLayout -> addWidget(hourColorCombo, 2, 2);

    gridLayout -> addWidget(minWidthLabel, 3, 0);
    gridLayout -> addWidget(minWidthEdit, 3, 1);
    //gridLayout -> addWidget(minColorLabel, 3, 2);
    gridLayout -> addWidget(minColorCombo, 3, 2);

    gridLayout -> addWidget(secWidthLabel, 4, 0);
    gridLayout -> addWidget(secWidthEdit, 4, 1);
    //gridLayout -> addWidget(secColorLabel, 4, 2);
    gridLayout -> addWidget(secColorCombo, 4, 2);
    editGroup -> setLayout(gridLayout);

    vLayout = new QVBoxLayout(this);
    vLayout ->addWidget(editGroup);
    hLayout->addLayout(vLayout);

    timeDiffEdit = new CtimeDiffEdit(this);
    simpleTextEdit = new CsimpleTextEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout ->addWidget(timeDiffEdit);
    vLayout ->addWidget(simpleTextEdit);
    //vLayout->addStretch();
    hLayout->addLayout(vLayout);



    //vLayout = new QVBoxLayout(this);
    //vLayout ->addWidget(timeGroup);
    //hLayout->addLayout(vLayout);
    timeGroup = new QGroupBox(tr("��������"),this);
    dateEdit = new CdateEdit(this);
    weekEdit = new CweekEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(dateEdit);
    vLayout->addWidget(weekEdit);
    vLayout->addStretch();
    timeGroup->setLayout(vLayout);

    posiEdit = new CposiEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout ->addWidget(timeGroup);
    vLayout ->addWidget(posiEdit);
    hLayout->addLayout(vLayout);
    //vLayout->addStretch();

    showModeEdit = new CshowModeEdit(this);

    vLayout = new QVBoxLayout(this);
    vLayout ->addWidget(showModeEdit);
    //vLayout->addStretch();
    hLayout->addLayout(vLayout);

    hLayout ->addStretch(10);
    setLayout(hLayout);

    connect(pointRadiusEdit, SIGNAL(editingFinished()), this, SIGNAL(edited()));
    connect(point369RadiusEdit, SIGNAL(editingFinished()), this, SIGNAL(edited()));
    connect(hourWidthEdit, SIGNAL(editingFinished()), this, SIGNAL(edited()));
    connect(minWidthEdit, SIGNAL(editingFinished()), this, SIGNAL(edited()));
    connect(secWidthEdit, SIGNAL(editingFinished()), this, SIGNAL(edited()));

    connect(pointColorCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(edited()));
    connect(point369ColorCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(edited()));
    connect(hourColorCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(edited()));
    connect(minColorCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(edited()));
    connect(secColorCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(edited()));

    //connect(secColorCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(edited()));

    //connect(nameEdit, SIGNAL(edited()), this, SIGNAL(edited()));
    connect(timeDiffEdit, SIGNAL(edited()), this, SIGNAL(edited()));
    connect(simpleTextEdit, SIGNAL(edited()), this, SIGNAL(edited()));
    connect(dateEdit, SIGNAL(edited()), this, SIGNAL(edited()));
    connect(weekEdit, SIGNAL(edited()), this, SIGNAL(edited()));
    connect(this, SIGNAL(edited()), this, SLOT(propertyEdited()));

    connect(posiEdit->left, SIGNAL(clicked()), this, SLOT(leftEdit()));
    connect(posiEdit->right, SIGNAL(clicked()), this, SLOT(rightEdit()));
    connect(posiEdit->up, SIGNAL(clicked()), this, SLOT(upEdit()));
    connect(posiEdit->down, SIGNAL(clicked()), this, SLOT(downEdit()));
    connect(posiEdit->def, SIGNAL(clicked()), this, SLOT(defEdit()));
}

CclockProperty::~CclockProperty()
{

}

void CclockProperty::getSettingsFromWidget(QString str)
{
    int type;
    int tmp;

    settings.beginGroup(str);

    type = settings.value("type").toInt();
    if(type == CLOCK_PROPERTY)
    {
        tmp = pointRadiusEdit->text().toInt();
        //qDebug("get pointRadius = %d", tmp);

        settings.setValue("pointRadius", pointRadiusEdit->text().toInt());   //����뾶
        settings.setValue("point369Radius", point369RadiusEdit->text().toInt()); //369��뾶
        settings.setValue("hourWidth", hourWidthEdit->text().toInt());//ʱ�ӿ��
        settings.setValue("minWidth", minWidthEdit->text().toInt()); //���ӿ��
        settings.setValue("secWidth", secWidthEdit->text().toInt()); //���ӿ��

        settings.setValue("pointColor", pointColorCombo->currentIndex()); //������ɫ
        settings.setValue("point369Color", point369ColorCombo->currentIndex()); //369����ɫ
        settings.setValue("hourColor", hourColorCombo->currentIndex()); //ʱ����ɫ
        settings.setValue("minColor", minColorCombo->currentIndex()); //������ɫ
        settings.setValue("secColor", secColorCombo->currentIndex()); //������ɫ
    }
    else
        ASSERT_FAILED();

    settings.endGroup();

    if(type == CLOCK_PROPERTY)
    {
      nameEdit->getSettingsFromWidget(str);
      timeDiffEdit->getSettingsFromWidget(str);
      simpleTextEdit->getSettingsFromWidget(str);
      dateEdit->getSettingsFromWidget(str);
      weekEdit->getSettingsFromWidget(str);
    }
}

//ˢ����ʾ����
void updateClockShowArea(CshowArea *area)
{
    //CshowArea *area;
    QString str;
    QTreeWidgetItem *item;

    if(area != (CshowArea *)0) //
    {
        item = area->fileItem;
        str = item->data(0,Qt::UserRole).toString();

        getClockParaFromSettings(str,area->filePara);
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
void CclockProperty::propertyEdited()
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
            updateClockShowArea(area);

        }
    }
}

//��settings�л�ȡ����
void getClockParaFromSettings(QString str, U_File_Para &para)
{
    int tmp;
   // QString str;

    para.Clock_Para.Flag = SHOW_CLOCK;
    settings.beginGroup(str);

    tmp = settings.value("pointRadius").toInt(); //����뾶
    para.Clock_Para.Hour_Point_Radius = (unsigned char)tmp;

    tmp = settings.value("point369Radius").toInt(); //369��뾶
    para.Clock_Para.Hour369_Point_Radius = (unsigned char)tmp;

    tmp = settings.value("hourWidth").toInt(); //ʱ�ӿ��
    para.Clock_Para.Hour_Line_Width = (unsigned char)tmp;

    tmp = settings.value("minWidth").toInt(); //���ӿ��
    para.Clock_Para.Min_Line_Width = (unsigned char)tmp;

    tmp = settings.value("secWidth").toInt(); //���ӿ��
    para.Clock_Para.Sec_Line_Width = (unsigned char)tmp;

    tmp = settings.value("point369Color").toInt(); //369����ɫ
    para.Clock_Para.Hour369_Point_Color = 0;
    SET_BIT(para.Clock_Para.Hour369_Point_Color, tmp);
    //qDebug("point369color = %d", para.Clock_Para.Hour369_Point_Color);

    tmp = settings.value("pointColor").toInt(); //������ɫ
    para.Clock_Para.Hour_Point_Color = 0;
    SET_BIT(para.Clock_Para.Hour_Point_Color, tmp);
    //qDebug("pointColor = %d", para.Clock_Para.Hour_Point_Color);

    tmp = settings.value("hourColor").toInt(); //Сʱ��ɫ
    para.Clock_Para.Hour_Line_Color = 0;
    SET_BIT(para.Clock_Para.Hour_Line_Color, tmp);
    //qDebug("hourColor = %d", para.Clock_Para.Hour_Line_Color);

    tmp = settings.value("minColor").toInt(); //������ɫ
    para.Clock_Para.Min_Line_Color = 0;
    SET_BIT(para.Clock_Para.Min_Line_Color, tmp);
    //qDebug("minColor = %d", para.Clock_Para.Min_Line_Color);

    tmp = settings.value("secColor").toInt(); //������ɫ
    para.Clock_Para.Sec_Line_Color = 0;
    SET_BIT(para.Clock_Para.Sec_Line_Color, tmp);
    //qDebug("secColor = %d", para.Clock_Para.Sec_Line_Color);

    settings.beginGroup("dateEdit");
    tmp = settings.value("checked").toBool();
    if(tmp EQ 0)
        para.Clock_Para.Date_Type = 0;
    else
    {
        tmp = settings.value("type").toInt();
        para.Clock_Para.Date_Type = tmp + 1;
    }

    tmp = settings.value("size").toInt();
    para.Clock_Para.Date_Font = tmp;
    tmp = settings.value("color").toInt();
    para.Clock_Para.Date_Color = 0;
    SET_BIT(para.Clock_Para.Date_Color, tmp);
    settings.endGroup();

    settings.beginGroup("weekEdit");
    tmp = settings.value("checked").toBool();
    if(tmp EQ 0)
        para.Clock_Para.Week_Type = 0;
    else
    {
        tmp = settings.value("type").toInt();
        para.Clock_Para.Week_Type = tmp + 1;
    }
    tmp = settings.value("size").toInt();
    para.Clock_Para.Week_Font = tmp;
    tmp = settings.value("color").toInt();
    para.Clock_Para.Week_Color = 0;
    SET_BIT(para.Clock_Para.Week_Color, tmp);
    settings.endGroup();

    tmp = settings.value("textX").toInt();
    para.Clock_Para.Text_X = tmp;

    tmp = settings.value("textY").toInt();
    para.Clock_Para.Text_Y = tmp;

    tmp = settings.value("dateX").toInt();
    para.Clock_Para.Date_X = tmp;

    tmp = settings.value("dateY").toInt();
    para.Clock_Para.Date_Y = tmp;

    tmp = settings.value("weekX").toInt();
    para.Clock_Para.Week_X = tmp;

    tmp = settings.value("weekY").toInt();
    para.Clock_Para.Week_Y = tmp;

/*
    settings.setValue("fontIndex", fontCombo->currentIndex());
    settings.setValue("fontSizeIndex", fontSizeCombo->currentIndex());
    settings.setValue("fontName", fontCombo->currentText());
    settings.setValue("fontSize", fontSizeCombo->currentText().toInt());

    settings.setValue("color", colorCombo->currentIndex());
    settings.setValue("bText", bButton->isChecked());
    settings.setValue("uText", uButton->isChecked());
    settings.setValue("iText", iButton->isChecked());
    settings.setValue("text", lineEdit->text());

    para.Clock_Para.Text_Color = settings.value("color").toInt();
    para.Clock_Para.Text_Color = settings.value("color").toInt();

    tmp = settings.value("fontSizeIndex").toInt();
    tmp = settings.value("fontName").toString();
    */
    //settings.beginGroup(str);
    settings.beginGroup("timeDiff");
    para.Clock_Para.Diff_Flag = settings.value("diffFlag").toInt();
    para.Clock_Para.Hour_Diff = settings.value("hour").toInt();
    para.Clock_Para.Min_Diff = settings.value("min").toInt();
    settings.endGroup();
    settings.endGroup();
}

/*
    QLineEdit *pointRadiusEdit; //����뾶
    QLineEdit *point369RadiusEdit; //
    QLineEdit *hourWidthEdit;
    QLineEdit *minWidthEdit;

    CcolorCombo *pointColorCombo;
    CcolorCombo *point369ColorCombo;
    CcolorCombo *hourColorCombo;
    CcolorCombo *minColorCombo;
    CcolorCombo *secColorCombo;

    QGroupBox *textGroup;
    CsimpleTextEdit *simpleTextEdit;
 */
//void CclockProperty::
void CclockProperty::setSettingsToWidget(QString str)
{
    QStringList keys;
    QString text;

    disconnect(this, SIGNAL(edited()), this, SLOT(propertyEdited()));
    settings.beginGroup(str);
    int setFlag = settings.value("setFlag").toBool();
    if(setFlag EQ 0)
    {
      settings.setValue("pointRadius", 3);   //����뾶
      settings.setValue("point369Radius", 3); //369��뾶
      settings.setValue("hourWidth", 8);//ʱ�ӿ��
      settings.setValue("minWidth", 5); //���ӿ��
      settings.setValue("secWidth", 3); //���ӿ��

      settings.setValue("pointColor", RED_INDEX); //������ɫ
      settings.setValue("point369Color", RED_INDEX); //369����ɫ
      settings.setValue("hourColor", RED_INDEX); //ʱ����ɫ
      settings.setValue("minColor", RED_INDEX); //������ɫ
      settings.setValue("secColor", RED_INDEX); //������ɫ

      settings.setValue("textX", 50); //�̶��ı�������X�ϵ�λ��
      settings.setValue("textY", 30); //�̶��ı�������Y�ϵ�λ��
      settings.setValue("dateX", 50);
      settings.setValue("dateY", 70);
      settings.setValue("weekX", 50);
      settings.setValue("weekY", 85);

      settings.setValue("setFlag", 1);
   }

    pointRadiusEdit->setText(QString::number(settings.value("pointRadius").toInt()));
    point369RadiusEdit->setText(QString::number(settings.value("point369Radius").toInt()));
    hourWidthEdit->setText(QString::number(settings.value("hourWidth").toInt()));
    minWidthEdit->setText(QString::number(settings.value("minWidth").toInt()));
    secWidthEdit->setText(QString::number(settings.value("secWidth").toInt()));

    pointColorCombo->setCurrentIndex(settings.value("pointColor").toInt());
    point369ColorCombo->setCurrentIndex(settings.value("point369Color").toInt());
    hourColorCombo->setCurrentIndex(settings.value("hourColor").toInt());
    minColorCombo->setCurrentIndex(settings.value("minColor").toInt());
    secColorCombo->setCurrentIndex(settings.value("secColor").toInt());

    settings.endGroup();

    nameEdit->setSettingsToWidget(str);
    timeDiffEdit->setSettingsToWidget(str);
    simpleTextEdit->setSettingsToWidget(str);
    dateEdit->setSettingsToWidget(str);
    weekEdit->setSettingsToWidget(str);

    connect(this, SIGNAL(edited()), this, SLOT(propertyEdited()));
}

void CclockProperty::leftEdit()
{
    QString str,str1;
    int index,posi;

    index = posiEdit->item->currentIndex();
    if(index EQ 0) //�̶��ı�����
      str = QString("textX");//left = settings.value("textX").toInt();
    else if(index EQ 1)
      str = QString("dateX");//left = settings.value("dateX").toInt();
    else
      str = QString("weekX");
      //

    QTreeWidgetItem *item = w->progManage->treeWidget->currentItem();
    if(item != (QTreeWidgetItem *)0)
    {
        str1 = item->data(0,Qt::UserRole).toString();
        //qDebug("left : %s", (const char *)str1.toLocal8Bit());
        settings.beginGroup(str1);

        posi = settings.value(str).toInt();
        if(posi >= POSI_STEP)
            posi = posi - POSI_STEP;
        else
            posi = 0;

        settings.setValue(str,posi);
        settings.endGroup();

        propertyEdited();
   }
}

void CclockProperty::rightEdit()
{
    QString str,str1;
    int index,posi;

    index = posiEdit->item->currentIndex();
    if(index EQ 0) //�̶��ı�����
      str = QString("textX");//left = settings.value("textX").toInt();
    else if(index EQ 1)
      str = QString("dateX");//left = settings.value("dateX").toInt();
    else
      str = QString("weekX");
      //

    QTreeWidgetItem *item = w->progManage->treeWidget->currentItem();
    if(item != (QTreeWidgetItem *)0)
    {
        str1 = item->data(0,Qt::UserRole).toString();
        //qDebug("left : %s", (const char *)str1.toLocal8Bit());
        settings.beginGroup(str1);

        posi = settings.value(str).toInt();
        if(posi  + POSI_STEP <= 100)
            posi = posi + POSI_STEP;
        else
            posi = 100;

        settings.setValue(str,posi);
        settings.endGroup();

        propertyEdited();
   }
}

void CclockProperty::upEdit()
{
    QString str,str1;
    int index,posi;

    index = posiEdit->item->currentIndex();
    if(index EQ 0) //�̶��ı�����
      str = QString("textY");//left = settings.value("textX").toInt();
    else if(index EQ 1)
      str = QString("dateY");//left = settings.value("dateX").toInt();
    else
      str = QString("weekY");
      //

    QTreeWidgetItem *item = w->progManage->treeWidget->currentItem();
    if(item != (QTreeWidgetItem *)0)
    {
        str1 = item->data(0,Qt::UserRole).toString();
        //qDebug("left : %s", (const char *)str1.toLocal8Bit());
        settings.beginGroup(str1);

        posi = settings.value(str).toInt();
        if(posi >= POSI_STEP)
            posi = posi - POSI_STEP;
        else
            posi = 0;

        settings.setValue(str,posi);
        settings.endGroup();

        propertyEdited();
   }
}

void CclockProperty::downEdit()
{
    QString str,str1;
    int index,posi;

    index = posiEdit->item->currentIndex();
    if(index EQ 0) //�̶��ı�����
      str = QString("textY");//left = settings.value("textX").toInt();
    else if(index EQ 1)
      str = QString("dateY");//left = settings.value("dateX").toInt();
    else
      str = QString("weekY");
      //

    QTreeWidgetItem *item = w->progManage->treeWidget->currentItem();
    if(item != (QTreeWidgetItem *)0)
    {
        str1 = item->data(0,Qt::UserRole).toString();
        //qDebug("left : %s", (const char *)str1.toLocal8Bit());
        settings.beginGroup(str1);

        posi = settings.value(str).toInt();
        if(posi  + POSI_STEP <= 100)
            posi = posi + POSI_STEP;
        else
            posi = 100;

        settings.setValue(str,posi);
        settings.endGroup();

        propertyEdited();
   }
}

void CclockProperty::defEdit()
{
    QTreeWidgetItem *item = w->progManage->treeWidget->currentItem();
    if(item != (QTreeWidgetItem *)0)
    {
        QString str = item->data(0,Qt::UserRole).toString();
        //qDebug("left : %s", (const char *)str1.toLocal8Bit());
        settings.beginGroup(str);
        settings.setValue("textX", 50); //�̶��ı�������X�ϵ�λ��
        settings.setValue("textY", 30); //�̶��ı�������Y�ϵ�λ��
        settings.setValue("dateX", 50);
        settings.setValue("dateY", 70);
        settings.setValue("weekX", 50);
        settings.setValue("weekY", 85);
        settings.endGroup();

        propertyEdited();
    }
}
