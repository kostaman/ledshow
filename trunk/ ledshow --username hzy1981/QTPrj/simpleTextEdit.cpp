#include <QApplication>
#include "simpleTextEdit.h"
#include <QGridLayout>
#include <QFontDatabase>
#include <QFontComboBox>
#include <QFontMetrics>
#include <QPainter>
#include <QSize>
#include <QRectF>
#include <QTextEdit>
#include <QSettings>
#include "..\led_show.h"

extern QSettings settings;

/*
const S_Mode_Func Mode_Func[]=
{
  {&Move_Left},
  {&Move_Right},
  {&Move_Up},
  {&Move_Down},
  {&Move_Left_Cover},
  {&Move_Right_Cover},
  {&Move_Up_Cover},
  {&Move_Down_Cover},
  {&Move_Left_Up_Cover},
  {&Move_Right_Up_Cover},
  {&Move_Left_Down_Cover},
  {&Move_Right_Down_Cover},
  {&Move_Left_Right_Open},
  {&Move_Up_Down_Open},
  {&Move_Left_Right_Close},
  {&Move_Up_Down_Close},

};
*/
CshowModeCombo::CshowModeCombo(QWidget *parent):QComboBox(parent)
{
    addItem(tr("����"));
    addItem(tr("����"));
    addItem(tr("����"));
    addItem(tr("����"));
    addItem(tr("��"));
    addItem(tr("�һ�"));
    addItem(tr("�ϻ�"));
    addItem(tr("�»�"));
    addItem(tr("���ϻ�"));
    addItem(tr("���ϻ�"));
    addItem(tr("���»�"));
    addItem(tr("���»�"));
    addItem(tr("���ҿ���"));
    addItem(tr("���¿���"));
    addItem(tr("���Һ���"));
    addItem(tr("���º���"));
 }

CshowModeCombo::~CshowModeCombo()
{

}

CshowSpeedCombo::CshowSpeedCombo(QWidget *parent):QComboBox(parent)
{
    addItem(tr("0"));
    addItem(tr("1"));
    addItem(tr("2"));
    addItem(tr("3"));
    addItem(tr("4"));
    addItem(tr("5"));
    addItem(tr("6"));
    addItem(tr("7"));
    addItem(tr("8"));
    addItem(tr("9"));
 }

CshowSpeedCombo::~CshowSpeedCombo()
{

}

CshowModeEdit::CshowModeEdit(QWidget *parent):QGroupBox(parent)
{
    QGridLayout *gridLayout;

    gridLayout = new QGridLayout(this);

    setTitle(tr("��ʾ��Ч"));
    showModeLabel = new QLabel(tr("��ʾģʽ"), this);
    speedLabel = new QLabel(tr("�����ٶ�"), this);
    stayTimeLabel = new QLabel(tr("ͣ��ʱ��"), this);

    showModeCombo = new CshowModeCombo(this);
    speedCombo = new CshowSpeedCombo(this);
    stayTimeEdit = new QLineEdit(this);
    gridLayout -> addWidget(showModeLabel, 0, 0);
    gridLayout -> addWidget(showModeCombo, 0, 1);
    gridLayout -> addWidget(speedLabel, 1, 0);
    gridLayout -> addWidget(speedCombo, 1, 1);
    gridLayout -> addWidget(stayTimeLabel, 2, 0);
    gridLayout -> addWidget(stayTimeEdit, 2, 1);
    setLayout(gridLayout);

}

void CshowModeEdit::getSettingsFromWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("showMode");
    settings.setValue("Mode", showModeCombo->currentIndex());
    settings.setValue("speed", speedCombo->currentIndex());
    settings.setValue("stayTime", stayTimeEdit->text().toInt());
    //settings.setValue("text", edit->getEdit()->toPlainText());
    settings.endGroup();
    settings.endGroup();

}

void CshowModeEdit::setSettingsToWidget(QString str)
{
    QStringList keys;
    QString text;

    settings.beginGroup(str);
    settings.beginGroup("showMode");
    keys = settings.allKeys();
    if(keys.isEmpty() == true)
    {
      //����
      settings.setValue("type", PIC_PROPERTY);
      settings.setValue("showMode", 0);
      settings.setValue("speed", 1);
      settings.setValue("stayTime", 5);
      settings.setValue("text", QString(tr("ͼ����ʾ")));
    }

    showModeCombo->setCurrentIndex(settings.value("showMode").toInt());
    speedCombo->setCurrentIndex(settings.value("speed").toInt());
    stayTimeEdit->setText(QString::number(settings.value("stayTime").toInt()));
    /*
    text = settings.value("text").toString();
    if(text == "")
        text == QString(tr("ͼ����ʾ"));
    //textEdit->clear();
    edit->getEdit()->setPlainText(text);*/
    settings.endGroup();
    settings.endGroup();
}

CshowModeEdit::~CshowModeEdit()
{

}


CsmLineEdit::CsmLineEdit(QWidget *parent):QGroupBox(parent)
{
    QHBoxLayout *hLayout;

    //editGroup = new QGroupBox(this);
    smLineCombo = new QComboBox(this);

    smLineCombo->addItem(tr("����"));
    smLineCombo->addItem(tr("����"));

    hLayout = new QHBoxLayout(this);
    hLayout->addWidget(smLineCombo);

    setTitle(tr("��/����"));
    setLayout(hLayout);

    connect(smLineCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
}

//��Widget�ϻ�ȡ����
void CsmLineEdit::getSettingsFromWidget(QString str)
{
   settings.beginGroup(str);
   settings.beginGroup("smLine");
   settings.setValue("smLineCheck", smLineCombo->currentIndex());
   settings.endGroup();
   settings.endGroup();
}

void CsmLineEdit::setSettingsToWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("smLine");
    int setFlag = settings.value("setFlag").toBool();
    if(setFlag == 0)
    {
       settings.setValue("smLineCheck", 0);
       settings.setValue("setFlag", 1);
    }
    smLineCombo->setCurrentIndex(settings.value("smLineCheck").toInt());
    settings.endGroup();
    settings.endGroup();
}

CsmLineEdit::~CsmLineEdit()
{

}

CdateEdit::CdateEdit(QWidget *parent):QWidget(parent)
{
    QHBoxLayout *hLayout;

    dateCheck = new QCheckBox(tr("����"),this);
    dateCombo = new QComboBox(this);
    dateCombo->addItem(tr("2000��12��30��"));
    dateCombo->addItem(tr("00��12��30��"));
    dateCombo->addItem(tr("12/30/2000"));
    dateCombo->addItem(tr("2000/12/30"));
    dateCombo->addItem(tr("00-12-30"));
    dateCombo->addItem(tr("00.12.30"));
    dateCombo->addItem(tr("12��30"));
    dateCombo->addItem(tr("12.30.2000"));
    dateCombo->addItem(tr("2000-12-30"));
    dateCombo->addItem(tr("2000"));
    dateCombo->addItem(tr("12"));
    dateCombo->addItem(tr("30"));

    colorCombo = new CcolorCombo(this);
    sizeCombo = new CsizeCombo(this);

    hLayout = new QHBoxLayout(this);
    hLayout->addWidget(dateCheck);
    hLayout->addWidget(dateCombo);
    hLayout->addWidget(colorCombo);
    hLayout->addWidget(sizeCombo);

    setLayout(hLayout);

    connect(dateCheck, SIGNAL(stateChanged(int)),this,SIGNAL(edited()));
    connect(dateCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
    connect(colorCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
    connect(sizeCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
}

//��Widget�ϻ�ȡ����
void CdateEdit::getSettingsFromWidget(QString str)
{
   settings.beginGroup(str);
   settings.beginGroup("dateEdit");
   settings.setValue("checked", dateCheck->isChecked());
   settings.setValue("type", dateCombo->currentIndex());
   settings.setValue("color", colorCombo->currentIndex());
   settings.setValue("size", sizeCombo->currentIndex());
   settings.endGroup();
   settings.endGroup();
}

void CdateEdit::setSettingsToWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("dateEdit");
    int setFlag = settings.value("setFlag").toBool();
    {
       settings.setValue("checked", 0);
       settings.setValue("type", 0);
       settings.setValue("color", 0);
       settings.setValue("size", 0);

       settings.setValue("setFlag", 1);
    }
    dateCheck->setChecked(settings.value("checked").toBool());
    dateCombo->setCurrentIndex(settings.value("type").toInt());
    colorCombo->setCurrentIndex(settings.value("color").toInt());
    sizeCombo->setCurrentIndex(settings.value("size").toInt());
    settings.endGroup();
    settings.endGroup();
}

CdateEdit::~CdateEdit()
{

}

CweekEdit::CweekEdit(QWidget *parent):QWidget(parent)
{
    QHBoxLayout *hLayout;

    weekCheck = new QCheckBox(tr("����"),this);
    weekCombo = new QComboBox(this);
    weekCombo->addItem(tr("����һ"));
    weekCombo->addItem(tr("Monday"));
    weekCombo->addItem(tr("Mon"));
    weekCombo->addItem(tr("Lunedi"));
    weekCombo->addItem(tr("Montag"));
    weekCombo->addItem(tr("Lundi"));


    colorCombo = new CcolorCombo(this);
    sizeCombo = new CsizeCombo(this);

    hLayout = new QHBoxLayout(this);
    hLayout->addWidget(weekCheck);
    hLayout->addWidget(weekCombo);
    hLayout->addWidget(colorCombo);
    hLayout->addWidget(sizeCombo);

    setLayout(hLayout);

    connect(weekCheck, SIGNAL(stateChanged(int)),this,SIGNAL(edited()));
    connect(weekCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
    connect(colorCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
    connect(sizeCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
}

//��Widget�ϻ�ȡ����
void CweekEdit::getSettingsFromWidget(QString str)
{
   settings.beginGroup(str);
   settings.beginGroup("weekEdit");
   settings.setValue("checked", weekCheck->isChecked());
   settings.setValue("type", weekCombo->currentIndex());
   settings.setValue("color", colorCombo->currentIndex());
   settings.setValue("size", sizeCombo->currentIndex());
   settings.endGroup();
   settings.endGroup();
}

void CweekEdit::setSettingsToWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("weekEdit");
    int setFlag = settings.value("setFlag").toBool();
    if(setFlag EQ 0)
    {
       settings.setValue("checked", 0);
       settings.setValue("type", 0);
       settings.setValue("color", 0);
       settings.setValue("size", 0);

       settings.setValue("setFlag", 1);
    }
    weekCheck->setChecked(settings.value("checked").toBool());
    weekCombo->setCurrentIndex(settings.value("type").toInt());
    colorCombo->setCurrentIndex(settings.value("color").toInt());
    sizeCombo->setCurrentIndex(settings.value("size").toInt());
    settings.endGroup();
    settings.endGroup();
}

CweekEdit::~CweekEdit()
{

}

CtimeEdit::CtimeEdit(QWidget *parent):QWidget(parent)
{
    QHBoxLayout *hLayout;

    timeCheck = new QCheckBox(tr("ʱ��"),this);
    timeCombo = new QComboBox(this);
    timeCombo->addItem(tr("2000��12��30��"));
    timeCombo->addItem(tr("00��12��30��"));
    timeCombo->addItem(tr("12/30/2000"));
    timeCombo->addItem(tr("2000/12/30"));
    timeCombo->addItem(tr("00-12-30"));
    timeCombo->addItem(tr("00.12.30"));
    timeCombo->addItem(tr("12��30"));
    timeCombo->addItem(tr("00.12.30"));

    colorCombo = new CcolorCombo(this);
    sizeCombo = new CsizeCombo(this);

    hLayout = new QHBoxLayout(this);
    hLayout ->addWidget(timeCheck);
    hLayout->addWidget(timeCombo);
    hLayout->addWidget(colorCombo);
    hLayout->addWidget(sizeCombo);

    setLayout(hLayout);

    connect(timeCheck, SIGNAL(stateChanged(int)),this,SIGNAL(edited()));
    connect(timeCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
    connect(colorCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
    connect(sizeCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
}

//��Widget�ϻ�ȡ����
void CtimeEdit::getSettingsFromWidget(QString str)
{
   settings.beginGroup(str);
   settings.beginGroup("timeEdit");
   settings.setValue("checked", timeCheck->isChecked());
   settings.setValue("type", timeCombo->currentIndex());
   settings.setValue("color", colorCombo->currentIndex());
   settings.setValue("size", sizeCombo->currentIndex());
   settings.endGroup();
   settings.endGroup();
}

void CtimeEdit::setSettingsToWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("timeEdit");
    timeCheck->setChecked(settings.value("checked").toBool());
    timeCombo->setCurrentIndex(settings.value("type").toInt());
    colorCombo->setCurrentIndex(settings.value("color").toInt());
    sizeCombo->setCurrentIndex(settings.value("size").toInt());
    settings.endGroup();
    settings.endGroup();
}

CtimeEdit::~CtimeEdit()
{

}

CdateTimeEdit::CdateTimeEdit(QWidget *parent):QGroupBox(parent)
{
    QVBoxLayout *vLayout;
    QGridLayout *gridLayout;

    vLayout = new QVBoxLayout(this);

    //editGroup = new QGroupBox(tr("ʱ��"),this);
    dateEdit = new CdateEdit(this);
    timeEdit = new CtimeEdit(this);
    weekEdit = new CweekEdit(this);

    vLayout->addWidget(dateEdit);
    vLayout->addWidget(timeEdit);
    vLayout->addWidget(weekEdit);
    //editGroup->setLayout(vLayout);

    //gridLayout = new QGridLayout(this);
    //gridLayout->addWidget(editGroup, 0, 0);
    setTitle(tr("ʱ��"));
    setLayout(vLayout);

    connect(dateEdit, SIGNAL(edited(int)),this,SIGNAL(edited()));
    connect(timeEdit, SIGNAL(edited(int)),this,SIGNAL(edited()));
    connect(weekEdit, SIGNAL(edited(int)),this,SIGNAL(edited()));
}

//��Widget�ϻ�ȡ����
void CdateTimeEdit::getSettingsFromWidget(QString str)
{
    dateEdit->getSettingsFromWidget(str);
    timeEdit->getSettingsFromWidget(str);
    weekEdit->getSettingsFromWidget(str);
}

void CdateTimeEdit::setSettingsToWidget(QString str)
{
    dateEdit->setSettingsToWidget(str);
    timeEdit->setSettingsToWidget(str);
    weekEdit->setSettingsToWidget(str);
}

CdateTimeEdit::~CdateTimeEdit()
{

}

//���ı��༭��
CsimpleTextEdit::CsimpleTextEdit(QWidget *parent):QGroupBox(parent)
{
    QHBoxLayout *hLayout;
    //QVBoxLayout *vLayout;
  QGridLayout *gridLayout, *mainLayout;
  QFontDatabase db;


  //vLayout = new QVBoxLayout(this);
  gridLayout = new QGridLayout(this);
  mainLayout = new QGridLayout(this);

  fontLabel = new QLabel(tr("����"), this);
  fontSizeLabel = new QLabel(tr("��С"), this);
  colorLabel = new QLabel(tr("��ɫ"), this);

  fontCombo = new QFontComboBox(this);
  fontCombo->setFixedWidth(100);

  fontSizeCombo = new QComboBox(this);
  //fontSizeCombo->setobjectName("comboSize");
  fontSizeCombo->setEditable(true);

  foreach(int size, db.standardSizes())
    fontSizeCombo->addItem(QString::number(size));
    //connect(comboSize, SIGNAL(activated(const QString &)),
    //this, SLOT(textSize(const QString &)));
  fontSizeCombo->setCurrentIndex(fontSizeCombo->findText(QString::number(QApplication::font().pointSize())));

  colorCombo = new CcolorCombo(this);
//-------------


  //---------------
  bButton = new QPushButton(tr("����"),this);
  iButton = new QPushButton(tr("б��"),this);
  uButton = new QPushButton(tr("�»�"), this);
  //oButton = new QPushButton(tr("��"),this);

  bButton->setCheckable(true);
  iButton->setCheckable(true);
  uButton->setCheckable(true);
  //oButton->setCheckable(true);

  lineEdit = new QLineEdit(this);

  hLayout = new QHBoxLayout(this);
  hLayout -> addWidget(fontLabel);
  hLayout -> addWidget(fontCombo);
  hLayout -> addWidget(fontSizeLabel);
  hLayout -> addWidget(fontSizeCombo);
  hLayout -> addWidget(colorLabel);
  hLayout -> addWidget(colorCombo);
  gridLayout->addLayout(hLayout, 0, 0);

  hLayout = new QHBoxLayout(this);
  hLayout -> addWidget(bButton);
  hLayout -> addWidget(iButton);
  hLayout -> addWidget(uButton);
  hLayout->addStretch();
  //hLayout -> addWidget(oButton);
  gridLayout->addLayout(hLayout, 1, 0);

  //lineEdit->setSizePolicy();
  hLayout = new QHBoxLayout(this);

  hLayout -> addWidget(lineEdit);
  hLayout->addStretch();
  gridLayout->addLayout(hLayout, 2, 0);

  //textGroup = new QGroupBox(tr("�̶��ı�"), this);
  //textGroup -> setLayout(gridLayout);
  //mainLayout->addWidget(textGroup, 0, 0);
  setTitle(tr("�̶��ı�"));
  setLayout(gridLayout);

  //���е���Ϣͳһ��һ����Ϣ
  connect(fontCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
  connect(fontSizeCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
  connect(colorCombo, SIGNAL(currentIndexChanged(int)),this,SIGNAL(edited()));
  connect(bButton, SIGNAL(clicked(bool)),this,SIGNAL(edited()));
  connect(iButton, SIGNAL(clicked(bool)),this,SIGNAL(edited()));
  connect(uButton, SIGNAL(clicked(bool)),this,SIGNAL(edited()));
  connect(lineEdit, SIGNAL(editingFinished()),this,SIGNAL(edited()));
}

/*
QFont font("times", 24);
QFontMetrics fm(font);
int pixelsWide = fm.width("What's the width of this text?");
int pixelsHigh = fm.height();
 */
//��ȡ�ı�������
QImage getTextImage(QString str)
{
    bool uText, bText, iText;
    QString text;
    QPainter painter;
    //QFontComboBox fontComboBox;
    //QComboBox fontSizeComboBox;

    settings.beginGroup(str);
    settings.beginGroup("simpleTextEdit");
    text = settings.value("text").toString();
    uText = settings.value("uText").toBool();
    bText = settings.value("bText").toBool();
    iText = settings.value("iText").toBool();
    QString fontName = settings.value("fontName").toString();
    //fontComboBox.setCurrentIndex(i);
    int fontSize = settings.value("fontSize").toInt();
    //fontSizeComboBox.setCurrentIndex(i);

    //QFont font(fontComboBox.currentText(), fontSizeComboBox.currentText().toInt());

    QFont font(fontName, fontSize);

    font.setStyleStrategy(QFont::NoAntialias);//�رտ����

    font.setUnderline(uText);
    font.setBold(bText);
    font.setItalic(iText);

    QFontMetrics fm(font);
    int width = fm.width(text);
    int height = fm.height();

    QImage image(width, height, QImage::Format_RGB32);

    painter.begin(&image);
    painter.fillRect(0,0,width,height,Qt::black);

    int color = settings.value("color").toInt();
    if(color == 0x00)
        painter.setPen(QColor(Qt::red));
    else if(color == 0x01)
        painter.setPen(QColor(Qt::green));
    else
        painter.setPen(QColor(Qt::yellow));

    painter.setFont(font);

    //QString str = lineEdit->text();//edit.document()->toPlainText();//lineEdit->text();//document()->toPlainText ();
    painter.drawText(0,0,width,height,Qt::AlignLeft, text);
    painter.end();
/*
    if(image.save("c:\\a.png")== false)
    {
      qDebug("save image failed");
    }
*/
    settings.endGroup();
    settings.endGroup();
    return image;

}

//
QSize getTextShowData(QImage image, S_Show_Data *pDst, INT16U x, INT16U y)
{
  //QImage image;
  QSize size;
  QColor red(Qt::red);
  QColor green(Qt::green);
  QColor yellow(Qt::yellow);
  QColor black(Qt::black);
  QRgb rgb;
  int i,j;

  //image = getTextImage(str);
  for(i = 0; i < image.width(); i ++)
      for(j = 0; j < image.height(); j ++)
      {
        rgb = image.pixel(i,j);
        if(rgb == red.rgb())
            Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x01);
        else if(rgb == green.rgb())
            Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x02);
        else if(rgb == yellow.rgb())
            Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x04);
        else if(rgb == black.rgb())
            Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x00);
        else
            ASSERT_FAILED();
      }
  size.setWidth(image.width());
  size.setHeight(image.height());
  return size;
}

//��Widget�ϻ�ȡ����
void CsimpleTextEdit::getSettingsFromWidget(QString str)
{
   settings.beginGroup(str);
   settings.beginGroup("simpleTextEdit");
   settings.setValue("fontIndex", fontCombo->currentIndex());
   settings.setValue("fontSizeIndex", fontSizeCombo->currentIndex());
   settings.setValue("fontName", fontCombo->currentText());
   settings.setValue("fontSize", fontSizeCombo->currentText().toInt());

   settings.setValue("color", colorCombo->currentIndex());
   settings.setValue("bText", bButton->isChecked());
   settings.setValue("uText", uButton->isChecked());
   settings.setValue("iText", iButton->isChecked());
   settings.setValue("text", lineEdit->text());
   settings.endGroup();
   settings.endGroup();
}

void CsimpleTextEdit::setSettingsToWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("simpleTextEdit");
    int setFlag = settings.value("setFlag").toBool();
    if(setFlag EQ 0)
    {
       settings.setValue("fontIndex", 0);
       settings.setValue("fontSizeIndex", 0);
       settings.setValue("color", 0);
       settings.setValue("bText", 0);
       settings.setValue("uText", 0);
       settings.setValue("iText", 0);
       settings.setValue("text", QString(""));

       settings.setValue("setFlag", 1);
    }

    fontCombo->setCurrentIndex(settings.value("fontIndex").toInt());
    fontSizeCombo->setCurrentIndex(settings.value("fontSizeIndex").toInt());

    colorCombo->setCurrentIndex(settings.value("color").toInt());
    bButton->setChecked(settings.value("bText").toBool());
    uButton->setChecked(settings.value("uText").toBool());
    iButton->setChecked(settings.value("iText").toBool());
    lineEdit->setText(settings.value("text").toString());
    settings.endGroup();
    settings.endGroup();
}
/*
 bool QObject::connect ( const QObject * sender, const char * signal, const QObject * receiver, const char * method, Qt::ConnectionType type = Qt::AutoConnection )   [static]

void CsimpleTextEdit::edited()
{
  qDebug("simpleText edited!");
}
*/
CsimpleTextEdit::~CsimpleTextEdit()
{

}
