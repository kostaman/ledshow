#include "mainwindow.h"
#include "showArea.h"
#include "clockProperty.h"
#include "colorCombo.h"
#include <QSettings>

extern MainWindow *w;
extern QSettings settings;
//ʱ�����Ա༭
CclockProperty::CclockProperty(QWidget *parent):QWidget(parent)
{
    QGridLayout *gridLayout;

    gridLayout = new QGridLayout(this);

    editGroup = new QGroupBox(this);
    pointRadiusLabel = new QLabel(tr("����뾶"), this);
    point369RadiusLabel = new QLabel(tr("369��뾶"), this);
    hourWidthLabel = new QLabel(tr("Сʱ���"), this);
    minWidthLabel = new QLabel(tr("���ӿ��"), this);
    secWidthLabel = new QLabel(tr("���ӿ��"), this);

    pointColorLabel = new QLabel(tr("������ɫ"), this);
    point369ColorLabel = new QLabel(tr("369����ɫ"), this);
    hourColorLabel = new QLabel(tr("Сʱ��ɫ"), this);
    minColorLabel = new QLabel(tr("������ɫ"), this);
    secColorLabel = new QLabel(tr("������ɫ"), this);

    pointRadiusEdit = new QLineEdit(this);
    point369RadiusEdit = new QLineEdit(this);
    hourWidthEdit = new QLineEdit(this);
    minWidthEdit= new QLineEdit(this);
    secWidthEdit = new QLineEdit(this);

    pointColorCombo = new CcolorCombo(this);
    point369ColorCombo = new CcolorCombo(this);
    hourColorCombo = new CcolorCombo(this);
    minColorCombo = new CcolorCombo(this);
    secColorCombo = new CcolorCombo(this);

    gridLayout -> addWidget(pointRadiusLabel, 0, 0);
    gridLayout -> addWidget(pointRadiusEdit, 0, 1);
    gridLayout -> addWidget(pointColorLabel, 0, 2);
    gridLayout -> addWidget(pointColorCombo, 0, 3);

    gridLayout -> addWidget(point369RadiusLabel, 1, 0);
    gridLayout -> addWidget(point369RadiusEdit, 1, 1);
    gridLayout -> addWidget(point369ColorLabel, 1, 2);
    gridLayout -> addWidget(point369ColorCombo, 1, 3);

    gridLayout -> addWidget(hourWidthLabel, 2, 0);
    gridLayout -> addWidget(hourWidthEdit, 2, 1);
    gridLayout -> addWidget(hourColorLabel, 2, 2);
    gridLayout -> addWidget(hourColorCombo, 2, 3);

    gridLayout -> addWidget(minWidthLabel, 3, 0);
    gridLayout -> addWidget(minWidthEdit, 3, 1);
    gridLayout -> addWidget(minColorLabel, 3, 2);
    gridLayout -> addWidget(minColorCombo, 3, 3);

    gridLayout -> addWidget(secWidthLabel, 4, 0);
    gridLayout -> addWidget(secWidthEdit, 4, 1);
    gridLayout -> addWidget(secColorLabel, 4, 2);
    gridLayout -> addWidget(secColorCombo, 4, 3);
    editGroup -> setLayout(gridLayout);


    textGroup = new QGroupBox(tr("�ı��༭"), this);
    simpleTextEdit = new CsimpleTextEdit(textGroup);
    gridLayout = new QGridLayout(this);
    gridLayout ->addWidget(simpleTextEdit, 0, 0);
    textGroup ->setLayout(gridLayout);

    gridLayout = new QGridLayout(this);
    gridLayout -> addWidget(editGroup, 0, 0);
    gridLayout -> addWidget(textGroup, 0, 1);
    setLayout(gridLayout);

    connect(pointRadiusEdit, SIGNAL(editingFinished()), this, SLOT(propertyEdited()));
    connect(point369RadiusEdit, SIGNAL(editingFinished()), this, SLOT(propertyEdited()));
    connect(hourWidthEdit, SIGNAL(editingFinished()), this, SLOT(propertyEdited()));
    connect(minWidthEdit, SIGNAL(editingFinished()), this, SLOT(propertyEdited()));
    connect(secWidthEdit, SIGNAL(editingFinished()), this, SLOT(propertyEdited()));

    connect(pointColorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(propertyEdited()));
    connect(point369ColorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(propertyEdited()));
    connect(hourColorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(propertyEdited()));
    connect(minColorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(propertyEdited()));
    connect(secColorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(propertyEdited()));

    connect(secColorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(propertyEdited()));

    connect(simpleTextEdit, SIGNAL(edited()), this, SLOT(propertyEdited()));
}

CclockProperty::~CclockProperty()
{

}

void CclockProperty::getSettingsFromWidget(QString str)
{
    settings.beginGroup(str);

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

    settings.endGroup();

    simpleTextEdit->getSettingsFromWidget(str);
}

//ˢ����ʾ����
void updateClockShowArea(CshowArea *area)
{
    //CshowArea *area;
    QString str;


    if(area != (CshowArea *)0) //
    {
        str = area->treeItem->data(0,Qt::UserRole).toString();
        //qDebug("item str:%s",str);
        getClockParaFromSettings(str,area->File_Para);

        //memset(area->showDataBak.Color_Data, 0, sizeof(area->showDataBak.Color_Data));
        area->imageBk = getTextImage(str);
        //QSize size = getTextShowData(image, &area->showDataBak, 0, 0);
        //area->File_Para.Clock_Para.Bk_Width = size.width();
        //area->File_Para.Clock_Para.Bk_Height = size.height();

        qDebug("file_para flag = %d", area->File_Para.Temp_Para.Flag);
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

    qDebug("propertyEdited");
    area = w->screenArea->getFocusArea(); //��ǰ�������

    if(area != (CshowArea *)0) //
    {
        QString str = area->treeItem->data(0,Qt::UserRole).toString();
        getSettingsFromWidget(str);
    }
    updateClockShowArea(area);
}

//��settings�л�ȡ����
void getClockParaFromSettings(QString str, U_File_Para &para)
{
    int tmp;

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
    qDebug("point369color = %d", para.Clock_Para.Hour369_Point_Color);

    tmp = settings.value("pointColor").toInt(); //������ɫ
    para.Clock_Para.Hour_Point_Color = 0;
    SET_BIT(para.Clock_Para.Hour_Point_Color, tmp);
    qDebug("pointColor = %d", para.Clock_Para.Hour_Point_Color);

    tmp = settings.value("hourColor").toInt(); //Сʱ��ɫ
    para.Clock_Para.Hour_Line_Color = 0;
    SET_BIT(para.Clock_Para.Hour_Line_Color, tmp);
    qDebug("hourColor = %d", para.Clock_Para.Hour_Line_Color);

    tmp = settings.value("minColor").toInt(); //������ɫ
    para.Clock_Para.Min_Line_Color = 0;
    SET_BIT(para.Clock_Para.Min_Line_Color, tmp);
    qDebug("minColor = %d", para.Clock_Para.Min_Line_Color);

    tmp = settings.value("secColor").toInt(); //������ɫ
    para.Clock_Para.Sec_Line_Color = 0;
    SET_BIT(para.Clock_Para.Sec_Line_Color, tmp);
    qDebug("secColor = %d", para.Clock_Para.Sec_Line_Color);

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

    settings.beginGroup(str);
    keys = settings.allKeys();
    if(keys.size() <10)
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

    simpleTextEdit->setSettingsToWidget(str);
}
