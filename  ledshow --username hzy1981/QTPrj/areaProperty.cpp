#include "areaProperty.h"
#include <QSettings>
#include "mainwindow.h"
#include "simpleTextEdit.h"

extern MainWindow *w;
extern QSettings settings;
//分区属性编辑
//////////////////////////////
Carea::Carea(QWidget *parent):QGroupBox(parent)
{
    //QHBoxLayout *hBoxLayout;
    QGridLayout *gridLayout;
    //int screenWidth, screenHeight;

    //screenWidth = Screen_Para.Base_Para.Width;
    //screenHeight = Screen_Para.Base_Para.Height;
    /*
    settings.beginGroup("screen");
    screenWidth = settings.value("width").toInt();//w->screenArea->width();
    screenHeight = settings.value("height").toInt();//w->screenArea->height();
    settings.endGroup();
*/
    //QValidator *xValidator = new QIntValidator(0,screenWidth,this);
    //QValidator *yValidator = new QIntValidator(0,screenHeight,this);

    //groupBox = new QGroupBox(tr("分区属性"), this);

    //nameLabel = new QLabel(tr("名字"), this);
    xLabel = new QLabel(tr("x起点"), this);
    yLabel = new QLabel(tr("y起点"), this);
    widthLabel = new QLabel(tr("宽度"), this);
    heightLabel = new QLabel(tr("高度"), this);

    int width = 50;
    //nameEdit = new QLineEdit(this);
    xEdit = new QSpinBox(this);
    yEdit = new QSpinBox(this);
    widthEdit = new QSpinBox(this);
    heightEdit = new QSpinBox(this);

    //nameEdit->setFixedWidth(width);
    xEdit->setFixedWidth(width);
    yEdit->setFixedWidth(width);
    widthEdit->setFixedWidth(width);
    heightEdit->setFixedWidth(width);

    xEdit->setMinimum(0);
    yEdit->setMinimum(0);
    widthEdit->setMinimum(MIN_AREA);
    heightEdit->setMinimum(MIN_AREA);

    xEdit->setMaximum(9999);
    yEdit->setMaximum(9999);
    widthEdit->setMaximum(9999);
    heightEdit->setMaximum(9999);

    connect(xEdit, SIGNAL(valueChanged(int)), this, SLOT(xEdited()));
    connect(yEdit, SIGNAL(valueChanged(int)), this, SLOT(yEdited()));
    connect(widthEdit, SIGNAL(valueChanged(int)), this, SLOT(xLenEdited()));
    connect(heightEdit, SIGNAL(valueChanged(int)), this, SLOT(yLenEdited()));

    //xEdit->setValidator(xValidator);
    //yEdit->setValidator(yValidator);
    //widthEdit->setValidator(xValidator);
    //heightEdit->setValidator(yValidator);
/*
    nameEdit->setMaxLength(4);
    xEdit->setMaxLength(4);
    yEdit->setMaxLength(4);
    widthEdit->setMaxLength(4);
    heightEdit->setMaxLength(4);
*/
    setTitle(tr("分区属性"));
    //setFixedWidth(150);
    gridLayout = new QGridLayout(this);

    //gridLayout -> addWidget(nameLabel,0,0);
    //gridLayout -> addWidget(nameEdit,0,1);

    gridLayout -> addWidget(xLabel, 0, 0);
    gridLayout -> addWidget(xEdit, 0, 1);
    gridLayout -> addWidget(yLabel, 1, 0);
    gridLayout -> addWidget(yEdit, 1, 1);
    gridLayout -> addWidget(widthLabel, 2, 0);
    gridLayout -> addWidget(widthEdit, 2, 1);
    gridLayout -> addWidget(heightLabel, 3, 0);
    gridLayout -> addWidget(heightEdit, 3, 1);
    //gridLayout -> setColumnStretch(1, 10);

    setLayout(gridLayout);
    //resize(200,200);

    //hBoxLayout = new QHBoxLayout(this);
    //hBoxLayout->addWidget(groupBox);

    //setLayout(hBoxLayout);

    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    //resize(sizeHint().width(),sizeHint().height());
}

void Carea::setEditMax()
{
   xEdit->setMaximum(Screen_Para.Base_Para.Width);
   yEdit->setMaximum(Screen_Para.Base_Para.Height);
   widthEdit->setMaximum(Screen_Para.Base_Para.Width);
   heightEdit->setMaximum(Screen_Para.Base_Para.Height);
}

void Carea::updateRect(QRect &rect, int sdWidth)
{
    disconnect(xEdit, SIGNAL(valueChanged(int)), this, SLOT(xEdited()));
    disconnect(yEdit, SIGNAL(valueChanged(int)), this, SLOT(yEdited()));
    disconnect(widthEdit, SIGNAL(valueChanged(int)), this, SLOT(xLenEdited()));
    disconnect(heightEdit, SIGNAL(valueChanged(int)), this, SLOT(yLenEdited()));

    xEdit->setValue((rect.x() / sdWidth));
    yEdit->setValue((rect.y()) / sdWidth);
    widthEdit->setValue((rect.width()) / sdWidth);
    heightEdit->setValue((rect.height()) / sdWidth);

    connect(xEdit, SIGNAL(valueChanged(int)), this, SLOT(xEdited()));
    connect(yEdit, SIGNAL(valueChanged(int)), this, SLOT(yEdited()));
    connect(widthEdit, SIGNAL(valueChanged(int)), this, SLOT(xLenEdited()));
    connect(heightEdit, SIGNAL(valueChanged(int)), this, SLOT(yLenEdited()));


}

void Carea::xEdited()
{
    int x;//xLen;
    CshowArea *area;
    QTreeWidgetItem *item;
    QString str;

    int sdWidth;
    sdWidth = w->screenArea->spaceWidth + w->screenArea->dotWidth;

    if(sdWidth == 0)
        sdWidth = 1;

    if(xEdit->value() + widthEdit->value() > w->screenArea->width() / sdWidth)
    {
        x = w->screenArea->width() / sdWidth - widthEdit->value();
        xEdit->setValue((x));
    }
    else
        x = xEdit->value();

    item = w->progManage->treeWidget->currentItem();//setCurrentItem(this->treeItem);
    if(checkItemType(item) != AREA_PROPERTY)
        item = item->parent();

    str = item->data(0, Qt::UserRole).toString();

    settings.beginGroup(str);
    settings.setValue("x", x);
    settings.endGroup();

    area = w->screenArea->getFocusArea(); //当前点中的分区

    //int sdWidth = w->screenArea->spaceWidth + w->screenArea->dotWidth;
    area->move(x * sdWidth, yEdit->value() * sdWidth);
}

void Carea::yEdited()
{
    int y;//yLen;
    CshowArea *area;
    QTreeWidgetItem *item;
    QString str;

    int sdWidth;
    sdWidth = w->screenArea->spaceWidth + w->screenArea->dotWidth;

    if(sdWidth == 0)
        sdWidth = 1;

    if(yEdit->value() + heightEdit->value() > w->screenArea->height() / sdWidth)
    {
        y = w->screenArea->height() / sdWidth - heightEdit->value();
        yEdit->setValue((y));
    }
    else
        y = yEdit->value();

    item = w->progManage->treeWidget->currentItem();//setCurrentItem(this->treeItem);
    if(checkItemType(item) != AREA_PROPERTY)
        item = item->parent();

    str = item->data(0, Qt::UserRole).toString();

    settings.beginGroup(str);
    settings.setValue("y", y);
    settings.endGroup();

    area = w->screenArea->getFocusArea(); //当前点中的分区
    //int sdWidth = w->screenArea->spaceWidth + w->screenArea->dotWidth;
    area->move(xEdit->value()* sdWidth, y* sdWidth);
}

void Carea::xLenEdited()
{
    int width;
    CshowArea *area;
    QTreeWidgetItem *item;
    QString str;

    int sdWidth;
    sdWidth = w->screenArea->spaceWidth + w->screenArea->dotWidth;

    if(sdWidth == 0)
        sdWidth = 1;

    if(xEdit->value() + widthEdit->value() > w->screenArea->width() / sdWidth)
    {
        width = w->screenArea->width() / sdWidth - xEdit->value();
        widthEdit->setValue((width));
    }
    else
        width = widthEdit->value();

    item = w->progManage->treeWidget->currentItem();//setCurrentItem(this->treeItem);
    if(checkItemType(item) != AREA_PROPERTY)
        item = item->parent();

    str = item->data(0, Qt::UserRole).toString();

    settings.beginGroup(str);
    settings.setValue("width", width);
    settings.endGroup();

    area = w->screenArea->getFocusArea(); //当前点中的分区
    //area->move(xEdit, yEdit->value());
    area->updateFlag = 1;
    //int sdWidth = w->screenArea->spaceWidth + w->screenArea->dotWidth;
    area->resize(width *sdWidth, heightEdit->value()* sdWidth);
}

void Carea::yLenEdited()
{
    int height;
    CshowArea *area;
    QTreeWidgetItem *item;
    QString str;

    int sdWidth;
    sdWidth = w->screenArea->spaceWidth + w->screenArea->dotWidth;

    if(sdWidth == 0)
        sdWidth = 1;


    if(yEdit->value() + heightEdit->value() > w->screenArea->height() / sdWidth)
    {
        height = w->screenArea->height() / sdWidth - yEdit->value();
        heightEdit->setValue((height));
    }
    else
        height = heightEdit->value();

    item = w->progManage->treeWidget->currentItem();//setCurrentItem(this->treeItem);
    if(checkItemType(item) != AREA_PROPERTY)
        item = item->parent();

    str = item->data(0, Qt::UserRole).toString();

    settings.beginGroup(str);
    settings.setValue("height", height);
    settings.endGroup();

    area = w->screenArea->getFocusArea(); //当前点中的分区
    area->updateFlag = 1;

    //int sdWidth = w->screenArea->spaceWidth + w->screenArea->dotWidth;

    area->resize(widthEdit->value()*sdWidth , height* sdWidth);
}

Carea::~Carea()
{


}

void Carea::getSettingsFromWidget(QString str)
{
    settings.beginGroup(str);
    //settings.setValue("name", nameEdit->value());
    settings.setValue("x", xEdit->value());
    settings.setValue("y", yEdit->value());
    settings.setValue("width", widthEdit->value());
    settings.setValue("height", heightEdit->value());
    settings.endGroup();

}

void Carea::setSettingsToWidget(QString str)
{
    QStringList keys;

    //设置前端开信号
    disconnect(xEdit, SIGNAL(valueChanged(int)), this, SLOT(xEdited()));
    disconnect(yEdit, SIGNAL(valueChanged(int)), this, SLOT(yEdited()));
    disconnect(widthEdit, SIGNAL(valueChanged(int)), this, SLOT(xLenEdited()));
    disconnect(heightEdit, SIGNAL(valueChanged(int)), this, SLOT(yLenEdited()));

    settings.beginGroup(str);
    int setFlag = settings.value("setFlag").toBool();
    if(setFlag EQ 0)
    {

       settings.setValue("setFlag", 1);
    }

    //名字
    //nameEdit->setText(settings.value("name").toString());
    xEdit->setValue((settings.value("x").toInt()));
    yEdit->setValue((settings.value("y").toInt()));
    widthEdit->setValue((settings.value("width").toInt()));
    heightEdit->setValue((settings.value("height").toInt()));


    settings.endGroup();

    //重新连接信号
    connect(xEdit, SIGNAL(valueChanged(int)), this, SLOT(xEdited()));
    connect(yEdit, SIGNAL(valueChanged(int)), this, SLOT(yEdited()));
    connect(widthEdit, SIGNAL(valueChanged(int)), this, SLOT(xLenEdited()));
    connect(heightEdit, SIGNAL(valueChanged(int)), this, SLOT(yLenEdited()));
}

CareaProperty::CareaProperty(QWidget *parent):QWidget(parent)
{/*
   QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;

    vLayout = new QVBoxLayout(this);
    hLayout = new QHBoxLayout(this);

    nameEdit = new CnameEdit(this);
    area = new Carea(this);

    vLayout->addWidget(nameEdit);
    vLayout->addWidget(area);

    hLayout->addLayout(vLayout);

    hLayout->addStretch(10);
    //vLayout->addStretch(10);

    setLayout(hLayout);
*/

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

    hLayout->addStretch(10);
    setLayout(hLayout);

    //connect(nameEdit, SIGNAL(edited()), this, SLOT(edited()));
}

void CareaProperty::edited()
{
    CshowArea *area;
    QTreeWidgetItem *item;

    //qDebug("propertyEdited");
    area = w->screenArea->getFocusArea(); //当前焦点分区

    if(area != (CshowArea *)0) //
    {
        //当前选中的item
        item = area->areaItem;//w->progManage->treeWidget->currentItem();////// //w->progManage->treeWidget->currentItem();
        if(item != (QTreeWidgetItem *)0)
        {
            QString str = item->data(0,Qt::UserRole).toString();
            getSettingsFromWidget(str);
            //updateClockShowArea(area);
        }
    }
}

void CareaProperty::getSettingsFromWidget(QString str)
{
   nameEdit->getSettingsFromWidget(str);
}

void CareaProperty::setSettingsToWidget(QString str)
{
   nameEdit->setSettingsToWidget(str);
}

CareaProperty::~CareaProperty()
{

}
