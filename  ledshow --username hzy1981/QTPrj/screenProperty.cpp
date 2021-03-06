#include <QFileDialog>
#include <QSettings>
#include <QMovie>
#include <QInputDialog>
#include <QMessageBox>
#include <QextSerialPort>
#include <QextSerialEnumerator>
#include <QList>
#include <QObject>
#include <QDesktopServices>
#include "makeProto.h"
#include "mainwindow.h"
#include "screenProperty.h"

#define VERSION_OFF 1000 //原来二进制文件中版本号所在偏移
#define FIRMWARE_FRAME_DATA_LEN 500 //固件升级帧数据域中升级数据长度
#define VERSION_FRAME_DATA_LEN 50  //固件升级帧第一帧，版本信息帧数据域长度
#define VERSION_FRAME_SUM_OFF 30   //版本信息帧中所有帧校验偏移,2字节
#define VERSION_FRAME_FCOUNTS_OFF 34  //版本信息帧中帧个数偏移,2字节
#define VERSION_FRAME_BINSIZE_OFF 36  //整个bin文件大小

#define DEF_ETH_DST_IP 0xFB01A8C0 //192.168.1.251

extern MainWindow *w;
extern QSettings settings;

//屏幕配置文件
//QSettings screenSettings(SCREEN_INI_FILE,QSettings::IniFormat,0);
//控制卡配置文件
QSettings cardSettings(CARD_INI_FILE,QSettings::IniFormat,0);

#define WIDTH_0 80
/*
  INT8U Direct; //进入方向
  INT8U Rows; //扫描1，2，4，8，16扫
  INT8U Rows_Fold; //每驱行折数
  INT8U Cols_Fold; //每驱列折数
 */
typedef struct
{
    INT16U code;
    const char *info;
}S_Scan_Mode;
//扫描模式定义
//第0字节表示扫描方式 00表示1/16扫,01表示1/8扫,02表示1/4扫, 03表示1/2扫,04表示静态
//第1字节表示进入方式,00表示左上,01表示左下, 10表示右上,11表示右下
//第2字节表示列折数,每X*8打折
//第3字节表示行折数,打折X次

const S_Scan_Mode scanMode[] =
{
    {200, "1/16扫,右入直行一路带16行数据(室内屏常规)"},
    {2213, "1/4扫,右入每8点向下打折,打折3次(P10模组常规)"},
    {1200, "1/8扫,右入直行一路带8行数据(P6模组常规)"},

    {0, "1/16扫,左入直行一路带16行数据"},
    {281, "1/16扫,右入直行每64点向下打折一次"},
//----------1/8扫-------
    {1000, "1/8扫,左入直行一路带8行数据"},
    {1011, "1/8扫,左入每8点向下打折,打折1次"},
    {1012, "1/8扫,左入每8点向下打折,打折2次"},
  //{1013, "1/8扫,左入每8点向下打折,打折3次"},
    {1021, "1/8扫,左入每16点向下打折,打折1次"},
    {1022, "1/8扫,左入每16点向下打折,打折2次"},
  //{1023, "1/8扫,左入每16点向下打折,打折3次"},
    {1111, "1/8扫,左入每8点向上打折,打折1次"},
    {1112, "1/8扫,左入每8点向上打折,打折2次"},
  //{1113, "1/8扫,左入每8点向上打折,打折3次"},
    {1121, "1/8扫,左入每16点向上打折,打折1次"},
    {1122, "1/8扫,左入每16点向上打折,打折2次"},
  //{1123, "1/8扫,左入每16点向上打折,打折3次"},
    //1-----
    {1211, "1/8扫,右入每8点向下打折,打折1次"},
    {1212, "1/8扫,右入每8点向下打折,打折2次"},
  //{1213, "1/8扫,右入每8点向下打折,打折3次"},
    {1221, "1/8扫,右入每16点向下打折,打折1次"},
    {1222, "1/8扫,右入每16点向下打折,打折2次"},
  //{1223, "1/8扫,右入每16点向下打折,打折3次"},
    {1311, "1/8扫,右入每8点向上打折,打折1次"},
    {1312, "1/8扫,右入每8点向上打折,打折2次"},
  //{1313, "1/8扫,右入每8点向上打折,打折3次"},
    {1321, "1/8扫,右入每16点向上打折,打折1次"},
    {1322, "1/8扫,右入每16点向上打折,打折2次"},
  //{1323, "1/8扫,右入每16点向上打折,打折3次"},
//---1/4扫描------------
    {2000, "1/4扫,左入直行一路带4行数据"},
    {2011, "1/4扫,左入每8点向下打折,打折1次"},
    {2012, "1/4扫,左入每8点向下打折,打折2次"},
    {2013, "1/4扫,左入每8点向下打折,打折3次"},
    {2021, "1/4扫,左入每16点向下打折,打折1次"},
    {2022, "1/4扫,左入每16点向下打折,打折2次"},
    {2023, "1/4扫,左入每16点向下打折,打折3次"},
    {2111, "1/4扫,左入每8点向上打折,打折1次"},
    {2112, "1/4扫,左入每8点向上打折,打折2次"},
    {2113, "1/4扫,左入每8点向上打折,打折3次"},
    {2121, "1/4扫,左入每16点向上打折,打折1次"},
    {2122, "1/4扫,左入每16点向上打折,打折2次"},
    {2123, "1/4扫,左入每16点向上打折,打折3次"},
    //1-----
    {2200, "1/4扫,右入直行一路带4行数据"},
    {2211, "1/4扫,右入每8点向下打折,打折1次"},
    {2212, "1/4扫,右入每8点向下打折,打折2次"},
    {2221, "1/4扫,右入每16点向下打折,打折1次"},
    {2222, "1/4扫,右入每16点向下打折,打折2次"},
    {2223, "1/4扫,右入每16点向下打折,打折3次"},
    {2311, "1/4扫,右入每8点向上打折,打折1次"},
    {2312, "1/4扫,右入每8点向上打折,打折2次"},
    {2313, "1/4扫,右入每8点向上打折,打折3次"},
    {2321, "1/4扫,右入每16点向上打折,打折1次"},
    {2322, "1/4扫,右入每16点向上打折,打折2次"},
    {2323, "1/4扫,右入每16点向上打折,打折3次"}
};

//获取某个扫描code在扫描方式数组中的Index
int getScanModeIndex(INT16U code)
{
    for(unsigned int i = 0; i < S_NUM(scanMode); i ++)
    {
       if(scanMode[i].code EQ code)
           return i;
    }

    return 0;
 }

//获取某个扫描方式对应的字符串
QString getScanCodeString(INT16U code)
{
    int index = getScanModeIndex(code);
/*
    if(code EQ 0)
      return "0000 " + QString(QObject::tr((const char *)scanMode[index].info));
    else
      return QString::number(code) + " " +  QString(QObject::tr((const char *)scanMode[index].info));
*/

    return  QString::number(code / 1000) + QString::number((code % 1000) /100) +\
            QString::number((code % 100) / 10) + QString::number(code % 10) + QString(",") + QString(QObject::tr((const char *)scanMode[index].info));

}

INT16U getScanCodeFromScreenPara(S_Screen_Para &screenPara)
{
  INT16U code = 0;
  INT16U Rows;

  if(screenPara.Scan_Para.Rows EQ 16)
    Rows = 0;
  else if(screenPara.Scan_Para.Rows EQ 8)
    Rows = 1;
  else if(screenPara.Scan_Para.Rows EQ 4)
    Rows = 2;
  else if(screenPara.Scan_Para.Rows EQ 2)
    Rows = 3;
  else
    Rows = 4;

  code += Rows * 1000;
  code += screenPara.Scan_Para.Direct * 100;
  code += screenPara.Scan_Para.Cols_Fold * 10;
  code += screenPara.Scan_Para.Rows_Fold;

  return code;
}

/*
CipInput::CipInput(QWidget *parent):QGroupBox(parent)
{
    QHBoxLayout *hLayout;
    QLabel *pointLabel[4];

    hLayout = new QHBoxLayout(this);

    for(int i = 0; i < 4; i ++)
    {
        inputEdit[i] = new QLineEdit(this);
        inputEdit[i]->setFixedWidth(30);
        //inputEdit[i]->setmi
        //inputEdit[i]->setmax
        pointLabel[i] = new QLabel(tr("."),this);
        hLayout->addWidget(inputEdit[i]);
        hLayout->addWidget(pointLabel[i]);
    }

   setLayout(hLayout);
}

CipInput::~CipInput()
{

}

INT332U CipInput::getInputIP()
{

}
*/
/*
//screen属性窗
class CscreenProperty:public QWidget
{
    Q_OBJECT
private:
    QLabel *screenSourceLabel; //screen源标志
    QLineEdit *screenSourceEdit; //screen源编辑框
    QPushButton *openButton; //打开按钮

    QLabel *frameNumLabel; //帧数标志
    QLineEdit *frameNumEdit; //帧数编辑
    QLabel *runSpeedLabel; //运行速度标志
    QLineEdit *runSpeedCheck; //运行速度编辑
    QLabel *speedUnitLabel; //速度单位

    QLabel *totalFrameNumLabel; //总帧数


public:
    CscreenProperty(QWidget *parent=0);
    ~CscreenProperty();
};
*/

/*
#define COM_MODE   0x00 //串口
#define ETH_MODE   0x01 //以太网模式
#define GPRS_MODE  0x02 //GPRS模式
#define UDISK_MODE 0x03 //u盘
#define WIFI_MODE  0x04 //Wifi
*/
QString index2ComTxt(int index)
{
  if(index EQ COM_MODE)
      return QObject::tr(COM_MODE_STR);
  else if(index EQ ETH_MODE)
      return QObject::tr(ETH_MODE_STR);
  else if(index EQ GPRS_MODE)
      return QObject::tr(GPRS_MODE_STR);
  else if(index EQ WIFI_MODE)
      return QObject::tr(WIFI_MODE_STR);
  else
  {
      ASSERT_FAILED();
      return QObject::tr(COM_MODE_STR);
  }
}

int comTxt2Index(QString comTxt)
{
    if(comTxt EQ QObject::tr(COM_MODE_STR))
        return COM_MODE;
    else if(comTxt EQ QObject::tr(ETH_MODE_STR))
        return ETH_MODE;
    else if(comTxt EQ QObject::tr(GPRS_MODE_STR))
        return GPRS_MODE;
    else if(comTxt EQ QObject::tr(WIFI_MODE_STR))
        return WIFI_MODE;
    else //if(comTxt EQ "U盘")
    {
        ASSERT_FAILED();
        return COM_MODE;
    }
}

INT8U getCardParaFromSettings(QString cardName, S_Card_Para &cardPara)
{
    cardSettings.beginGroup(cardName);
    cardPara.Font_Num = cardSettings.value("FontNum").toInt();
    cardPara.InMode_Num = cardSettings.value("inModeNum").toInt();
    cardPara.OutMode_Num = cardSettings.value("outModeNum").toInt();
    cardPara.File_En_Word = cardSettings.value("fileEnWord").toInt();
    cardPara.Max_Points = cardSettings.value("maxPoints").toInt();
    cardPara.Max_Height = cardSettings.value("maxHeight").toInt();
    cardPara.Max_Area_Num = cardSettings.value("maxAreaNum").toInt();
    cardPara.Flag = cardSettings.value("flag").toInt();
    cardPara.ROM_Size = cardSettings.value("romSize").toInt();
    cardPara.Com_Mode = cardSettings.value("comMode").toInt();
    cardSettings.endGroup();

    return 1;
}

//设置屏幕参数到settings文件中
INT8U setScreenParaToSettings(QString screenStr, S_Screen_Para &screenPara)
{
   settings.beginGroup(screenStr);
   settings.beginGroup("facPara");

   settings.setValue("width", screenPara.Base_Para.Width);
   settings.setValue("height", screenPara.Base_Para.Height);

   if(screenPara.Base_Para.Color EQ 0x01 || screenPara.Base_Para.Color EQ 0)
       settings.setValue("color", 0);
   else if(screenPara.Base_Para.Color EQ 0x03)
       settings.setValue("color", 1);
   else if(screenPara.Base_Para.Color EQ 0x07)
       settings.setValue("color", 2);
   else
   {
       ASSERT_FAILED();
       settings.setValue("color", 0);
   }

   settings.setValue("screenID", screenPara.COM_Para.Addr);
   settings.setValue("baud", screenPara.COM_Para.Baud);

   settings.setValue("ip", screenPara.Net_Para.IP);
   //settings.setValue("mac0", screenPara.Net_Para.Mac0);
   //settings.setValue("mac1", screenPara.Net_Para.Mac1);
   settings.setValue("mask", screenPara.Net_Para.Mask);
   settings.setValue("gate", screenPara.Net_Para.Gate);

   settings.setValue("dataPolarity", screenPara.Scan_Para.Data_Polarity);
   settings.setValue("oePolarity", screenPara.Scan_Para.OE_Polarity);
   settings.setValue("redGreenRev", screenPara.Scan_Para.RG_Reverse);
   settings.setValue("lineOrder", screenPara.Scan_Para.Line_Order);
   settings.setValue("lineHide", screenPara.Scan_Para.Line_Hide);
   settings.setValue("freq", screenPara.Scan_Para.Screen_Freq);
   //settings.setValue("");
   settings.setValue("scanMode", getScanCodeFromScreenPara(screenPara));

   settings.endGroup();
   //亮度调节
   settings.beginGroup("lightness");
   settings.setValue("adjMode", screenPara.Lightness.Mode);
   settings.setValue("manualLightness", screenPara.Lightness.Manual_Lightness);
   //screenPara.Lightness.Mode = settings.value("adjMode").toInt();
   //screenPara.Lightness.Manual_Lightness = settings.value("manualLightness").toInt(); //手动调亮度

   for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
   {
     settings.setValue("timeCheck" + QString::number(i), screenPara.Lightness.Time_Lightness[i].Flag);
     settings.setValue("lightness" + QString::number(i), screenPara.Lightness.Time_Lightness[i].Value);
     settings.setValue("startHour" + QString::number(i), screenPara.Lightness.Time_Lightness[i].Start_Hour);
     settings.setValue("startMin" + QString::number(i), screenPara.Lightness.Time_Lightness[i].Start_Min);
   }
   settings.endGroup();

   //定时开关机
   settings.beginGroup("openCloseTime");

   for(int i =0; i < MAX_OPEN_CLOSE_TIME;i ++)
   {
       settings.setValue("timeCheck"+QString::number(i), screenPara.OC_Time.Time[i].Flag);
       settings.setValue("openHour" + QString::number(i), screenPara.OC_Time.Time[i].Open_Hour);
       settings.setValue("openMin" + QString::number(i), screenPara.OC_Time.Time[i].Open_Min);
       settings.setValue("closeHour" + QString::number(i), screenPara.OC_Time.Time[i].Close_Hour);
       settings.setValue("closeMin" + QString::number(i), screenPara.OC_Time.Time[i].Close_Min);
   }

   settings.endGroup();


   settings.endGroup();

   return 1;
}

//通信失败时的处理，重连接等
void comFailedProc()
{
    CcomTest comTest;

    if(w->comStatus->comThread->COM_Mode EQ COM_MODE && w->comStatus->comThread->timeOutFlag EQ 1)
    {
      //串口通信超时
      int Re =  QMessageBox::warning(w, QObject::tr("提示"),
                                 QObject::tr(SEND_PARA_FAIL_RECONNECT_STR),QObject::tr("确定"),QObject::tr("取消"));
      if(0 == Re)
        comTest.autoConnect();

    }
    else if(w->comStatus->comThread->deniedFlag EQ 1)
    {
        QMessageBox::warning(w, QObject::tr("提示"),
                                 QObject::tr(SEND_PARA_DENIED_STR),QObject::tr("确定"));
    }
    else
    {
        QMessageBox::warning(w, QObject::tr("提示"),
                                 QObject::tr(SEND_PARA_FAIL_STR),QObject::tr("确定"));

    }

}

//读取屏幕参数
//返回>0表示读取到参数，==0表示没有读取到参数
INT8U getScreenCardParaFromSettings(QString screenStr, S_Screen_Para &screenPara, S_Card_Para &cardPara)
{
    QString cardName;

    debug("getScreenCardParaFromSettings:%s", (const char *)screenStr.toLocal8Bit());

    settings.beginGroup(screenStr);
    settings.beginGroup("facPara");

    int index = settings.value("cardType").toInt();

    screenPara.Base_Para.Width = settings.value("width").toInt();
    screenPara.Base_Para.Height = settings.value("height").toInt();

    INT8U color = settings.value("color").toInt();
    if(color EQ 0) //单色屏
        screenPara.Base_Para.Color = 0x01;
    else if(color EQ 1) //双色屏
        screenPara.Base_Para.Color = 0x03;
    else
        screenPara.Base_Para.Color = 0x07;

    screenPara.COM_Para.Addr = (INT16U)settings.value("screenID").toInt();
    screenPara.COM_Para.Baud = (INT8U)settings.value("baud").toInt();

    screenPara.Net_Para.IP = settings.value("ip").toInt();
    //screenPara.Net_Para.Mac0 = settings.value("mac0").toInt();
    //screenPara.Net_Para.Mac1 = settings.value("mac1").toInt();
    screenPara.Net_Para.Mask = settings.value("mask").toInt();
    screenPara.Net_Para.Gate = settings.value("gate").toInt();

    screenPara.Net_Para.Serv_En = 0;
    screenPara.Net_Para.Serv_IP = 0;//screenPara.Net_Para.Gate;
    screenPara.Net_Para.Serv_Port = 0;//4001;
    screenPara.Net_Para.Heart_Period = 0;//10;

    screenPara.Scan_Para.Data_Polarity = settings.value("dataPolarity").toInt(); //数据级性
    screenPara.Scan_Para.OE_Polarity = settings.value("oePolarity").toInt();
    screenPara.Scan_Para.RG_Reverse = settings.value("redGreenRev").toInt();
    screenPara.Scan_Para.Line_Order = settings.value("lineOrder").toInt();
    screenPara.Scan_Para.Line_Hide = settings.value("lineHide").toInt();
    screenPara.Scan_Para.Screen_Freq = settings.value("freq").toInt(); //刷新频率
    screenPara.Scan_Para._138Check = settings.value("138Check").toInt();

    //扫描方式
    int scanMode = settings.value("scanMode").toInt();
    screenPara.Scan_Para.Direct = (scanMode%1000) / 100;
    screenPara.Scan_Para.Cols_Fold = (scanMode %100) / 10;
    screenPara.Scan_Para.Rows_Fold = (scanMode %10);
    INT8U Rows = (scanMode % 10000) / 1000;

    if(Rows EQ 0)
      screenPara.Scan_Para.Rows = 16;
    else if(Rows EQ 1)
      screenPara.Scan_Para.Rows = 8;
    else if(Rows EQ 2)
      screenPara.Scan_Para.Rows = 4;
    else if(Rows EQ 3)
      screenPara.Scan_Para.Rows = 2;
    else if(Rows EQ 4)
      screenPara.Scan_Para.Rows = 1;
    else
      screenPara.Scan_Para.Rows = 16;

    //----------------------
    //screenPara.Scan_Para.Screen_Freq = 0; //屏频
    screenPara.Scan_Para.Clk_Freq = 0;
    //
    settings.endGroup();
    //亮度调节
    settings.beginGroup("lightness");
    screenPara.Lightness.Mode = settings.value("adjMode").toInt();
    screenPara.Lightness.Manual_Lightness = settings.value("manualLightness").toInt(); //手动调亮度

    for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
    {
      screenPara.Lightness.Time_Lightness[i].Flag = settings.value("timeCheck" + QString::number(i)).toInt();
      screenPara.Lightness.Time_Lightness[i].Value = settings.value("lightness" + QString::number(i)).toInt();
      screenPara.Lightness.Time_Lightness[i].Start_Hour = settings.value("startHour" + QString::number(i)).toInt();
      screenPara.Lightness.Time_Lightness[i].Start_Min = settings.value("startMin" + QString::number(i)).toInt();
    }
    settings.endGroup();

    //定时开关机
    settings.beginGroup("openCloseTime");

    for(int i =0; i < MAX_OPEN_CLOSE_TIME;i ++)
    {
        screenPara.OC_Time.Time[i].Flag = settings.value("timeCheck"+QString::number(i)).toInt();
        screenPara.OC_Time.Time[i].Open_Hour = settings.value("openHour" + QString::number(i)).toInt();
        screenPara.OC_Time.Time[i].Open_Min = settings.value("openMin" + QString::number(i)).toInt();
        screenPara.OC_Time.Time[i].Close_Hour = settings.value("closeHour" + QString::number(i)).toInt();
        screenPara.OC_Time.Time[i].Close_Min = settings.value("closeMin" + QString::number(i)).toInt();
    }

    settings.endGroup();

    //锁定时间
    settings.beginGroup("validTime");

    if(settings.value("validTimeFlag").toBool())
        screenPara.Lock_Date.Lock_Date_Flag = LOCK_DATE_FLAG;
    else
        screenPara.Lock_Date.Lock_Date_Flag = 0;

    screenPara.Lock_Date.Time[0] = (INT8U)settings.value("date").toInt();
    screenPara.Lock_Date.Time[1] = (INT8U)settings.value("month").toInt();
    screenPara.Lock_Date.Time[2] = (INT8U)(settings.value("year").toInt() % 100);

    settings.endGroup();


    settings.endGroup();

   cardSettings.beginGroup("");
   cardName = cardSettings.childGroups().at(index);
   cardSettings.endGroup();

   getCardParaFromSettings(cardName, cardPara);

  return 1;
}

//screen属性编辑
CscreenProperty::CscreenProperty(QWidget *parent):QWidget(parent)
{

    //QTabWidget *tab;
    QHBoxLayout /**hLayout,*/*mainLayout;
    QVBoxLayout *vLayout;
    //QGroupBox *lightnessGroup;
    //QGroupBox *openCloseTimeGroup;
    //QGroupBox *facParaGroup;

    //lightnessGroup = new QGroupBox(tr("亮度设置"),this);
    //openCloseTimeGroup = new QGroupBox(tr("开关机设置"),this);
    //facParaGroup = new QGroupBox(tr("安装参数"),this);

    mainLayout = new QHBoxLayout(this);

    vLayout = new QVBoxLayout(this);
    nameEdit = new CnameEdit(this);
    vLayout->addWidget(nameEdit);
    vLayout->addStretch(10);
    mainLayout->addLayout(vLayout);

    //tab = new QTabWidget(this);
     //hLayout = new QHBoxLayout(this);
    facProperty = new CfacScreenProperty(SHOW_SCN, 0, this);
     //hLayout->addWidget(facProperty);
    //facParaGroup->setLayout(hLayout);

    //hLayout = new QHBoxLayout(this);
    //lightnessProperty = new ClightnessProperty(this);
    //hLayout->addWidget(lightnessProperty);
    //lightnessGroup->setLayout(hLayout);

    //hLayout = new QHBoxLayout(this);
    //openCloseProperty = new CopenCloseProperty(this);
    //hLayout->addWidget(openCloseProperty,0,Qt::AlignTop);
    //openCloseTimeGroup->setLayout(hLayout);
    //lightnessGroup->setLayout(vLayout);
    //facProperty->setEnabled(false);
    //facProperty->endButton->setEnabled(true);
    //tab->addTab(lightnessProperty, tr("亮度调节"));
    //tab->addTab(openCloseProperty, tr("定时开关机"));

   // tab->addTab(facProperty, tr("工厂参数"));
    //hLayout->addWidget(tab);
    //mainLayout->addWidget(lightnessProperty);
    //mainLayout->addWidget(openCloseProperty);
    mainLayout->addWidget(facProperty);
    mainLayout->addStretch(10);

    //setLayout(hLayout);
     //hLayout->addLayout(vLayout);

    //connect(nameEdit, SIGNAL(edited()), this, SIGNAL(edited()));
    //connect(openButton, SIGNAL(clicked()), this, SLOT(openscreenFile()));
}


CscreenProperty::~CscreenProperty()
{

}

void CscreenProperty::getSettingsFromWidget(QString str)
{
    nameEdit->getSettingsFromWidget(str);
    //lightnessProperty->getSettingsFromWidget(str);
    //openCloseProperty->getSettingsFromWidget(str);

}

void CscreenProperty::setSettingsToWidget(QString str)
{
    nameEdit->setSettingsToWidget(str);
    //lightnessProperty->setSettingsToWidget(str);
    //openCloseProperty->setSettingsToWidget(str);
    facProperty->setSettingsToWidget(str);
}
/*
class ClightnessProperty:public QWidget
{
    Q_OBJECT
    QRadioButton *manualButton;
    QRadioButton *timerButton;

public:
    QCheckBox *timerCheck[MAX_LIGHTNESS_TIME];
    QTimeEdit *timerEdit[MAX_LIGHTNESS_TIME];
    QSlider *timerSlider[MAX_LIGHTNESS_TIME];

    QSlider *manualSlider;
    //void getSettingsFromWidget(QString str);
   //void setSettingsToWidget(QString str);
    ClightnessProperty(QWidget *parent=0);
    ~ClightnessProperty();
};
*/
ClightnessProperty::ClightnessProperty(QWidget *parent):QGroupBox(parent)
{
    INT8U i;

    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
   QHBoxLayout *gHLayout;
   QGroupBox *groupBox;

   QHBoxLayout *mainLayout = new QHBoxLayout(this);

   groupBox = new QGroupBox(this);
   vLayout = new QVBoxLayout(this);
   manualButton = new QRadioButton(tr("手动调亮"),this);
   timerButton = new QRadioButton(tr("定时调亮"),this);
   autoButton = new QRadioButton(tr("自动调亮"),this);

   vLayout->addWidget(manualButton);
   vLayout->addWidget(timerButton);
   vLayout->addWidget(autoButton);
   groupBox->setLayout(vLayout);

   mainLayout->addWidget(groupBox);//addLayout(hLayout);

   groupBox = new QGroupBox(this);
   gHLayout = new QHBoxLayout(this);

   hLayout = new QHBoxLayout(this);
   manualSlider = new QSlider(Qt::Horizontal,this);
   manualSlider->setRange(10,MAX_LIGHTNESS_LEVEL*10);
   manualSlider->setTickInterval(10);
   //manualSlider->setFocusPolicy(Qt::StrongFocus);
   //manualSlider->setTickPosition(QSlider::TicksAbove);
   manualLabel = new QLabel(this);
   manualLabel->setFixedWidth(15);
   hLayout->addWidget(manualSlider);
   hLayout->addWidget(manualLabel);
   gHLayout->addLayout(hLayout);

   hLayout = new QHBoxLayout(this);
   autoLabel = new QLabel(tr("请确认已安装光照传感器"),this);
   hLayout->addWidget(autoLabel);
   gHLayout->addLayout(hLayout);


   QVBoxLayout *timerVLayout = new QVBoxLayout(this);
   for(i = 0; i < MAX_LIGHTNESS_TIME; i ++)
   {
     hLayout = new QHBoxLayout(this);
     timerCheck[i] = new QCheckBox(tr("启用"),this);
     timerEdit[i] = new QTimeEdit(this);

     timerSlider[i] = new QSlider(Qt::Horizontal,this);
     timerSlider[i]->setRange(10,MAX_LIGHTNESS_LEVEL*10);
     timerSlider[i]->setTickInterval(10);
     //timerSlider[i]->setFocusPolicy(Qt::StrongFocus);
     //timerSlider[i]->setTickPosition(QSlider::TicksAbove);

     timerLabel[i] = new QLabel(this);
     timerLabel[i]->setFixedWidth(15);

     hLayout->addWidget(timerCheck[i]);
     hLayout->addWidget(timerEdit[i]);
     hLayout->addWidget(timerSlider[i]);
     hLayout->addWidget(timerLabel[i]);

     timerVLayout->addLayout(hLayout);
   }

   gHLayout->addLayout(timerVLayout);
   groupBox->setLayout(gHLayout);
   mainLayout->addWidget(groupBox);
   mainLayout->addStretch(10);

   this->setLayout(mainLayout);

   setTitle(tr("亮度参数(1级最暗,16级最亮)"));

   connect(manualButton, SIGNAL(clicked()),this,SIGNAL(adjModeEditSignal()));
   connect(timerButton, SIGNAL(clicked()),this,SIGNAL(adjModeEditSignal()));
   connect(autoButton, SIGNAL(clicked()),this,SIGNAL(adjModeEditSignal()));

   connect(manualButton, SIGNAL(clicked()),this,SIGNAL(allEditSignal()));
   connect(timerButton, SIGNAL(clicked()),this,SIGNAL(allEditSignal()));
   connect(autoButton, SIGNAL(clicked()),this,SIGNAL(allEditSignal()));

   for(int i =0;i < MAX_LIGHTNESS_TIME; i ++)
   {
     connect(timerCheck[i],SIGNAL(clicked()),this,SIGNAL(allEditSignal()));
     connect(timerEdit[i],SIGNAL(timeChanged(QTime)),this,SIGNAL(allEditSignal()));
     connect(timerSlider[i],SIGNAL(valueChanged(int)),this,SIGNAL(allEditSignal()));
   }
   connect(manualSlider,SIGNAL(valueChanged(int)),this,SIGNAL(allEditSignal()));

   connect(this,SIGNAL(adjModeEditSignal()),this,SLOT(adjModeEditSlot()));
   connect(this,SIGNAL(allEditSignal()),this,SLOT(allEditSlot()));
}

void ClightnessProperty::allEditSlot()
{
    QString str = w->screenArea->getCurrentScreenStr();//getCurrentStr
    getSettingsFromWidget(str);

    for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
      timerLabel[i]->setText(QString::number(timerSlider[i]->value()/10));
    manualLabel->setText(QString::number(manualSlider->value()/10));

    sliderEditProc();
}

void ClightnessProperty::adjModeEditSlot()
{
    if(manualButton->isChecked())
    {
        for(int i=0; i < MAX_LIGHTNESS_TIME; i ++)
        {
            timerCheck[i]->setVisible(false);
            timerEdit[i]->setVisible(false);
            timerSlider[i]->setVisible(false);
            timerLabel[i]->setVisible(false);
        }

        autoLabel->setVisible(false);

        manualSlider->setVisible(true);
        manualLabel->setVisible(true);
    }
    else if(timerButton->isChecked())
    {
      for(int i=0; i < MAX_LIGHTNESS_TIME; i ++)
      {
          timerCheck[i]->setVisible(true);
          timerEdit[i]->setVisible(true);
          timerSlider[i]->setVisible(true);
          timerLabel[i]->setVisible(true);
      }

      autoLabel->setVisible(false);
      manualSlider->setVisible(false);
      manualLabel->setVisible(false);
    }
    else if(autoButton->isChecked())
    {
        for(int i=0; i < MAX_LIGHTNESS_TIME; i ++)
        {
            timerCheck[i]->setVisible(false);
            timerEdit[i]->setVisible(false);
            timerSlider[i]->setVisible(false);
            timerLabel[i]->setVisible(false);
        }

        autoLabel->setVisible(true);

        manualSlider->setVisible(false);
        manualLabel->setVisible(false);
    }

    sliderEditProc();
}

void ClightnessProperty::sliderEditProc()
{
    for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
    {
      if(timerCheck[i]->isChecked())
      {
          timerEdit[i]->setEnabled(true);//setTime(time);
          timerSlider[i]->setEnabled(true);//setValue(settings.value("timerLightness" + QString::number(i)).toInt()*10);
          timerLabel[i]->setEnabled(true);//setText(QString::number(timerSlider[i]->value()/10));
      }
      else
      {
          timerEdit[i]->setEnabled(false);//setTime(time);
          timerSlider[i]->setEnabled(false);//setValue(settings.value("timerLightness" + QString::number(i)).toInt()*10);
          timerLabel[i]->setEnabled(false);//setText(QString::number(timerSlider[i]->value()/10));
      }
    }
}

void ClightnessProperty::getSettingsFromWidget(QString str)
{
    settings.beginGroup(str);
  settings.beginGroup("lightness");
  //亮度调节方式
  if(timerButton->isChecked())
      settings.setValue("adjMode", TIME_ADJ);
  else if(autoButton->isChecked())
      settings.setValue("adjMode", AUTO_ADJ);
  else
      settings.setValue("adjMode", MANUAL_ADJ);

  for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
  {
     settings.setValue("timeCheck" + QString::number(i), timerCheck[i]->isChecked());
     settings.setValue("startHour" + QString::number(i),timerEdit[i]->time().hour());
     settings.setValue("startMin" + QString::number(i), timerEdit[i]->time().minute());
     settings.setValue("startSec" + QString::number(i),timerEdit[i]->time().second());
     settings.setValue("lightness" + QString::number(i), timerSlider[i]->value()/10 - 1);
  }

  settings.setValue("manualLightness", manualSlider->value()/10 - 1);
  settings.endGroup();
  settings.endGroup();
}

void ClightnessProperty::setSettingsToWidget(QString str)
{
    disconnect(this,SIGNAL(adjModeEditSignal()),this,SLOT(adjModeEditSlot()));
    disconnect(this,SIGNAL(allEditSignal()),this,SLOT(allEditSlot()));

    settings.beginGroup(str);
    settings.beginGroup("lightness");
    //亮度调节方式
    int adjMode = settings.value("adjMode").toInt();
    if(adjMode EQ MANUAL_ADJ)
       manualButton->setChecked(1);
    else
       manualButton->setChecked(0);

    if(adjMode EQ TIME_ADJ)
       timerButton->setChecked(1);
    else
       timerButton->setChecked(0);

    if(adjMode EQ AUTO_ADJ)
       autoButton->setChecked(1);
    else
       autoButton->setChecked(0);

    for(int i=0; i < MAX_LIGHTNESS_TIME; i++)
    {
      timerCheck[i]->setChecked(settings.value("timeCheck" + QString::number(i)).toBool());
      QTime time;
      time.setHMS(settings.value("startHour" + QString::number(i)).toInt(), \
                  settings.value("startMin" + QString::number(i)).toInt(),\
                  settings.value("startSec" + QString::number(i)).toInt());
      timerEdit[i]->setTime(time);
      timerSlider[i]->setValue((settings.value("lightness" + QString::number(i)).toInt() + 1)*10);
      timerLabel[i]->setText(QString::number(timerSlider[i]->value()/10));
    }

    manualSlider->setValue((settings.value("manualLightness").toInt() + 1)*10);
    manualLabel->setText(QString::number(manualSlider->value()/10));

    settings.endGroup();
    settings.endGroup();

    adjModeEditSlot();
    sliderEditProc();

    connect(this,SIGNAL(adjModeEditSignal()),this,SLOT(adjModeEditSlot()));
    connect(this,SIGNAL(allEditSignal()),this,SLOT(allEditSlot()));
}

ClightnessProperty::~ClightnessProperty()
{

}

CopenCloseProperty::CopenCloseProperty(QWidget *parent):QGroupBox(parent)
{
    INT8U i;

    QHBoxLayout *hLayout;
   //QVBoxLayout *vLayout;
   QLabel *openTimeLabel, *closeTimeLabel;

   hLayout = new QHBoxLayout(this);
   QGridLayout *mainLayout = new QGridLayout(this);
   closeTimeLabel = new QLabel(tr("关闭时间"),this);
   openTimeLabel = new QLabel(tr("开启时间"),this);
   mainLayout->addWidget(openTimeLabel,0,1,1,1,Qt::AlignVCenter|Qt::AlignHCenter);
   mainLayout->addWidget(closeTimeLabel,0,3,1,1,Qt::AlignVCenter|Qt::AlignHCenter);

   for(i = 0; i < MAX_OPEN_CLOSE_TIME; i ++)
   {
     timeCheck[i] = new QCheckBox(tr("启用"),this);
     openTimeEdit[i] = new QTimeEdit(this);
     closeTimeEdit[i] = new QTimeEdit(this);

     mainLayout->addWidget(timeCheck[i], 1 + i, 0, 1, 1,Qt::AlignTop);
     mainLayout->addWidget(openTimeEdit[i], 1 + i, 1, 1, 2,Qt::AlignTop);
     mainLayout->addWidget(closeTimeEdit[i], 1 + i, 3, 1, 2,Qt::AlignTop);
   }

   hLayout->addLayout(mainLayout);
   hLayout->addStretch(10);
   setLayout(hLayout);

   for(i =0;i < MAX_LIGHTNESS_TIME; i ++)
   {
     connect(timeCheck[i], SIGNAL(clicked()),this,SIGNAL(TimeEditSignal()));
     connect(openTimeEdit[i],SIGNAL(timeChanged(QTime)),this,SIGNAL(TimeEditSignal()));
     connect(closeTimeEdit[i],SIGNAL(timeChanged(QTime)),this,SIGNAL(TimeEditSignal()));
   }

   connect(this, SIGNAL(TimeEditSignal()), this, SLOT(allEditSlot()));

   setTitle(tr("定时开关机参数"));
   timeCheckProc();
}

void CopenCloseProperty::timeCheckProc()
{
   for(int i = 0; i < MAX_OPEN_CLOSE_TIME; i ++)
    {
     openTimeEdit[i]->setEnabled(timeCheck[i]->isChecked());
     closeTimeEdit[i]->setEnabled(timeCheck[i]->isChecked());
   }
}

void CopenCloseProperty::allEditSlot()
{
    QString str = w->screenArea->getCurrentScreenStr();//getCurrentStr
    getSettingsFromWidget(str);

    timeCheckProc();
}

void CopenCloseProperty::getSettingsFromWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("openCloseTime");

    for(int i =0; i < MAX_OPEN_CLOSE_TIME;i ++)
    {
        settings.setValue("timeCheck"+QString::number(i), timeCheck[i]->isChecked());
        settings.setValue("openHour"+QString::number(i), openTimeEdit[i]->time().hour());
        settings.setValue("openMin"+QString::number(i),openTimeEdit[i]->time().minute());
        settings.setValue("openSec"+QString::number(i), openTimeEdit[i]->time().second());
        settings.setValue("closeHour"+QString::number(i), closeTimeEdit[i]->time().hour());
        settings.setValue("closeMin"+QString::number(i), closeTimeEdit[i]->time().minute());
        settings.setValue("closeSec"+QString::number(i), closeTimeEdit[i]->time().second());
    }

    settings.endGroup();
    settings.endGroup();
}
//开关机时段属性
void CopenCloseProperty::setSettingsToWidget(QString str)
{
    disconnect(this, SIGNAL(TimeEditSignal()), this, SLOT(allEditSlot()));

    settings.beginGroup(str);
    settings.beginGroup("openCloseTime");

    for(int i =0; i < MAX_OPEN_CLOSE_TIME;i ++)
    {
        timeCheck[i]->setChecked(settings.value("timeCheck"+QString::number(i)).toBool());
        QTime time;
        time.setHMS(settings.value("openHour" + QString::number(i)).toInt(), \
                    settings.value("openMin" + QString::number(i)).toInt(),\
                    settings.value("openSec" + QString::number(i)).toInt());
        openTimeEdit[i]->setTime(time);

        time.setHMS(settings.value("closeHour" + QString::number(i)).toInt(), \
                    settings.value("closeMin" + QString::number(i)).toInt(),\
                    settings.value("closeSec" + QString::number(i)).toInt());
        closeTimeEdit[i]->setTime(time);
    }

    settings.endGroup();
    settings.endGroup();


    timeCheckProc();
    connect(this, SIGNAL(TimeEditSignal()), this, SLOT(allEditSlot()));
}


CopenCloseProperty::~CopenCloseProperty()
{

}

ClightnessDialog::ClightnessDialog(QWidget *parent):QDialog(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *vLayout = new QVBoxLayout(this);
   QHBoxLayout *hLayout = new QHBoxLayout(this);

   lightnessProperty = new ClightnessProperty(this);
   //lightnessProperty->setFixedWidth(370);
   //lightnessProperty->setFixedHeight(160);
   //lightnessProperty->setFixedWidth(lightnessProperty->sizeHint().width());

  sendButton = new QPushButton(tr("发送参数"), this);
  udiskButton = new QPushButton(tr("导出U盘文件"),this);
  cancelButton = new QPushButton(tr("关闭"),this);


  hLayout ->addWidget(sendButton);
  hLayout ->addWidget(udiskButton);
  hLayout ->addWidget(cancelButton);

  vLayout->addWidget(lightnessProperty);
  vLayout->addLayout(hLayout);

  mainLayout  ->addLayout(vLayout);
  mainLayout ->addStretch(10);
  mainLayout->setSizeConstraint(QLayout::SetFixedSize);
  setLayout(mainLayout);

  this->setWindowTitle(tr("设置亮度"));
  setAttribute(Qt::WA_DeleteOnClose);

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(sendButton, SIGNAL(clicked()), this, SLOT(sendPara()));
  connect(udiskButton, SIGNAL(clicked()), this, SLOT(udiskPara()));
}


//发送参数
void sendLightnessPara()//S_COM_Status &COM_Status)
{
    INT8U Temp[100];
    int len;
    //char frameBuf[BLOCK_DATA_LEN + 20];
    //S_Screen_Para screenPara;
    //S_Card_Para cardPara;
    //int len;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    QString str = w->screenArea->getCurrentScreenStr();

    int flag = 0;
    SET_BIT(flag, C_SCREEN_LIGNTNESS);
    if(QT_SIM_EN)
      makeProtoFileData(str, SIM_MODE, flag);
    else
      makeProtoFileData(str, COM_MODE, flag);


    bool re = w->comStatus->waitComEnd(Temp, sizeof(Temp), &len);
    if(re EQ true)
    {
        QMessageBox::information(w,QObject::tr("提示"),
                               QObject::tr(SEND_PARA_OK_STR),QObject::tr("确定"));

    }
    else
    {
        comFailedProc();
    }
}


void ClightnessDialog::sendPara()
{
    //char frameBuf[BLOCK_DATA_LEN + 20];
    //S_Screen_Para screenPara;
    //S_Card_Para cardPara;
    INT8U temp[100];
    int len;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    QString str = w->screenArea->getCurrentScreenStr();

    this->sendButton->setEnabled(false);

    int flag = 0;
    SET_BIT(flag, C_SCREEN_LIGNTNESS);
    if(QT_SIM_EN)
      makeProtoFileData(str, SIM_MODE, flag);
    else
      makeProtoFileData(str, COM_MODE, flag);

    if(w->comStatus->waitComEnd(temp, sizeof(temp), &len))
    {
        QMessageBox::information(w, tr("提示"),
                               tr(SEND_PARA_OK_STR),tr("确定"));
        close(); //校时成功则关闭
    }
    else
    {
        comFailedProc();
    }

    this->sendButton->setEnabled(true);
}

//
void ClightnessDialog::udiskPara()
{
    //S_Screen_Para screenPara;
    //S_Card_Para cardPara;
    //INT8U temp[100];
    //int len;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    QString str = w->screenArea->getCurrentScreenStr();

    this->udiskButton->setEnabled(false);

    int flag = 0;
    SET_BIT(flag, C_SCREEN_LIGNTNESS);

    makeProtoFileData(str, UDISK_MODE, flag);

    //U盘模式下不需要等待waitComEnd，因为没有通信返回数据需要等待
    if(w->comStatus->getComStatus() == COM_OK) //通信成功的情况下关闭
    {
        QMessageBox::information(w, QObject::tr("提示"),
                                w->comStatus->getComReStr(),QObject::tr("确定"));
        close();
    }
    else
    {
        comFailedProc();
    }

    this->udiskButton->setEnabled(true);
}

void ClightnessDialog::getSettingsFromWidget(QString str)
{
  lightnessProperty->getSettingsFromWidget(str);
}

void ClightnessDialog::setSettingsToWidget(QString str)
{
  lightnessProperty->setSettingsToWidget(str);
}

ClightnessDialog::~ClightnessDialog()
{

}

CopenCloseDialog::CopenCloseDialog(QWidget *parent):QDialog(parent)
{
        QVBoxLayout *vLayout = new QVBoxLayout(this);
    QHBoxLayout *hLayout = new QHBoxLayout(this);


  openCloseProperty = new CopenCloseProperty(this);
  sendButton = new QPushButton(tr("发送参数"), this);
  udiskButton = new QPushButton(tr("导出U盘文件"),this);
  cancelButton = new QPushButton(tr("关闭"),this);

  hLayout ->addWidget(sendButton);
  hLayout ->addWidget(udiskButton);
  hLayout ->addWidget(cancelButton);

  vLayout->addWidget(openCloseProperty);
  vLayout->addLayout(hLayout);

  setLayout(vLayout);

  this->setWindowTitle(tr("设置定时开关机"));
  setAttribute(Qt::WA_DeleteOnClose);

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(sendButton, SIGNAL(clicked()), this, SLOT(sendPara()));
  connect(udiskButton, SIGNAL(clicked()), this, SLOT(udiskPara()));
}

//发送参数
void sendOpenClosePara()
{
   //char frameBuf[BLOCK_DATA_LEN + 20];
   S_Screen_Para screenPara;
   S_Card_Para cardPara;
   //int len;


   if(w->comStatus->comThread->isRunning())//当前线程还在运行
       return;

   QString str = w->screenArea->getCurrentScreenStr();

   getScreenCardParaFromSettings(str, screenPara, cardPara); //

   //定时开关机时间
   /*
   len = makeFrame((char *)&screenPara.OC_Time, sizeof(screenPara.OC_Time),\
              C_SCREEN_OC_TIME, 0, frameBuf);*/
   int flag = 0;
   SET_BIT(flag, C_SCREEN_OC_TIME);
   if(QT_SIM_EN)
     makeProtoFileData(str, SIM_MODE, flag);
   else
     makeProtoFileData(str, COM_MODE, flag);
}

void CopenCloseDialog::sendPara()
{
    //char frameBuf[BLOCK_DATA_LEN + 20];
    S_Screen_Para screenPara;
    S_Card_Para cardPara;
    int len;
    INT8U temp[100];


    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    QString str = w->screenArea->getCurrentScreenStr();

    this->sendButton->setEnabled(false);

    getScreenCardParaFromSettings(str, screenPara, cardPara); //

    //定时开关机时间
    /*
    len = makeFrame((char *)&screenPara.OC_Time, sizeof(screenPara.OC_Time),\
               C_SCREEN_OC_TIME, 0, frameBuf);*/

    int flag = 0;
    SET_BIT(flag, C_SCREEN_OC_TIME);
    if(QT_SIM_EN)
      makeProtoFileData(str, SIM_MODE, flag);
    else
      makeProtoFileData(str, COM_MODE, flag);

    if(w->comStatus->waitComEnd(temp, sizeof(temp), &len))
    {
        QMessageBox::information(w, tr("提示"),
                               tr(SEND_PARA_OK_STR),tr("确定"));
        close(); //校时成功则关闭
    }
    else
    {
        comFailedProc();
    }

    this->sendButton->setEnabled(true);
}

//
void CopenCloseDialog::udiskPara()
{
    S_Screen_Para screenPara;
    S_Card_Para cardPara;
    //int len;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    QString str = w->screenArea->getCurrentScreenStr();

    this->udiskButton->setEnabled(false);

    getScreenCardParaFromSettings(str, screenPara, cardPara); //

    //定时开关机时间
    /*
    len = makeFrame((char *)&screenPara.OC_Time, sizeof(screenPara.OC_Time),\
               C_SCREEN_OC_TIME, 0, frameBuf);*/

    int flag = 0;
    SET_BIT(flag, C_SCREEN_OC_TIME);

    makeProtoFileData(str, UDISK_MODE, flag);

    //U盘模式下不需要等待waitComEnd，因为没有通信返回数据需要等待
    if(w->comStatus->getComStatus() == COM_OK) //通信成功的情况下关闭
    {
        QMessageBox::information(w, QObject::tr("提示"),
                                w->comStatus->getComReStr(),QObject::tr("确定"));
        close();
    }
    else
    {
        QMessageBox::warning(w, QObject::tr("提示"),
                                w->comStatus->getComReStr(),QObject::tr("确定"));
    }

    this->udiskButton->setEnabled(true);

}

void CopenCloseDialog::getSettingsFromWidget(QString str)
{
  openCloseProperty->getSettingsFromWidget(str);
}

void CopenCloseDialog::setSettingsToWidget(QString str)
{
  openCloseProperty->setSettingsToWidget(str);
}

CopenCloseDialog::~CopenCloseDialog()
{

}

//校准时间
CadjTimeProperty::CadjTimeProperty(QWidget *parent):QGroupBox(parent)
{
    QGridLayout *mainLayout = new QGridLayout(this);

    sysTimeButton = new QRadioButton(tr("系统时间"),parent); //系统时间
    selfTimeButton = new QRadioButton(tr("自定义时间"),parent); //自定义事件
    dateTimeEdit = new QDateTimeEdit(parent);

    mainLayout->addWidget(sysTimeButton, 0, 0);
    mainLayout->addWidget(selfTimeButton, 1, 0);
    mainLayout->addWidget(dateTimeEdit, 1, 2);
    sysTimeButton->setChecked(true);

    QDateTime temp;
    temp =  QDateTime::currentDateTime();
    dateTimeEdit->setDateTime(temp);
    dateTimeEdit->setEnabled(false);

    setLayout(mainLayout);
    setTitle(tr("校准时间"));

    connect(sysTimeButton, SIGNAL(clicked()), this, SLOT(adjTimeModeCheck()));
    connect(selfTimeButton, SIGNAL(clicked()), this, SLOT(adjTimeModeCheck()));
}

void CadjTimeProperty::adjTimeModeCheck()
{
    if(sysTimeButton->isChecked())
    {
        dateTimeEdit->setEnabled(false);
    }
    else
    {
        QDateTime temp;
        temp =  QDateTime::currentDateTime();
        dateTimeEdit->setDateTime(temp);
        dateTimeEdit->setEnabled(true);
    }
}

CadjTimeProperty::~CadjTimeProperty()
{

}

void CadjTimeProperty::getSettingsFromWidget(QString str)
{

}

void CadjTimeProperty::setSettingsToWidget(QString str)
{

}

//获取日期时间
QDateTime CadjTimeProperty::getDateTime()
{
  if(this->sysTimeButton->isChecked())
    {
      return QDateTime::currentDateTime();
  }
  else
  {
      return this->dateTimeEdit->dateTime();
  }
}

//发送校时数据
void CadjTimeDialog::sendData()
{
    QDateTime dateTime;
    INT8U TimeBuf[10];
    INT8U Temp[20];
    int len;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    this->sendButton->setEnabled(false);

    dateTime = adjTimeProperty->getDateTime();

    TimeBuf[T_YEAR] = dateTime.date().year() - 2000;
    TimeBuf[T_MONTH] = dateTime.date().month();
    TimeBuf[T_DATE] = dateTime.date().day();
    TimeBuf[T_WEEK] = dateTime.date().dayOfWeek();
    if(TimeBuf[T_WEEK] EQ 7)
        TimeBuf[T_WEEK] = 0;
    TimeBuf[T_HOUR] = dateTime.time().hour();
    TimeBuf[T_MIN] = dateTime.time().minute();
    TimeBuf[T_SEC] = dateTime.time().second();

    QString screenStr = w->screenArea->getCurrentScreenStr();

#if QT_SIM_EN
    makeProtoBufData(screenStr, SIM_MODE, C_SCREEN_TIME | WR_CMD, (char *)TimeBuf, 7);
#else
    makeProtoBufData(screenStr, COM_MODE, C_SCREEN_TIME | WR_CMD, (char *)TimeBuf, 7);
#endif


    bool re = w->comStatus->waitComEnd(Temp, sizeof(Temp), &len);
    if(re EQ true)
    {
        QMessageBox::information(w, tr("提示"),
                               tr(SEND_PARA_OK_STR),tr("确定"));
        close(); //校时成功则关闭

    }
    else
    {
        comFailedProc();
    }

    this->sendButton->setEnabled(true);
}

//导出校时数据到U盘
void CadjTimeDialog::udiskData()
{
    QDateTime dateTime = adjTimeProperty->getDateTime();
    INT8U TimeBuf[10];
    //INT8U Temp[20];
    //int len;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    this->udiskButton->setEnabled(false);

    TimeBuf[T_YEAR] = dateTime.date().year() - 2000;
    TimeBuf[T_MONTH] = dateTime.date().month();
    TimeBuf[T_DATE] = dateTime.date().day();
    TimeBuf[T_WEEK] = dateTime.date().dayOfWeek();
    if(TimeBuf[T_WEEK] EQ 7)
        TimeBuf[T_WEEK] = 0;
    TimeBuf[T_HOUR] = dateTime.time().hour();
    TimeBuf[T_MIN] = dateTime.time().minute();
    TimeBuf[T_SEC] = dateTime.time().second();

    QString screenStr = w->screenArea->getCurrentScreenStr();

    makeProtoBufData(screenStr, UDISK_MODE, C_SCREEN_TIME | WR_CMD, (char *)TimeBuf, 7);

    //U盘模式下不需要等待waitComEnd，因为没有通信返回数据需要等待
    if(w->comStatus->getComStatus() == COM_OK) //通信成功的情况下关闭
    {
        QMessageBox::information(w, QObject::tr("提示"),
                                w->comStatus->getComReStr(),QObject::tr("确定"));
        close();
    }
    else
    {
        QMessageBox::warning(w, QObject::tr("提示"),
                                w->comStatus->getComReStr(),QObject::tr("确定"));
    }

    this->udiskButton->setEnabled(true);

}

//校准时间对话框
CadjTimeDialog::CadjTimeDialog(QWidget *parent):QDialog(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    QHBoxLayout *hLayout = new QHBoxLayout(this);

  adjTimeProperty = new CadjTimeProperty(this);

  sendButton = new QPushButton(tr("发送"),this);
  udiskButton = new QPushButton(tr("导出U盘文件"),this);
  cancelButton = new QPushButton(tr("关闭"), this);

  hLayout->addWidget(sendButton);
  hLayout->addWidget(udiskButton);
  hLayout->addWidget(cancelButton);
  vLayout->addWidget(adjTimeProperty);
  vLayout->addLayout(hLayout);

  setLayout(vLayout);

  this->setWindowTitle(tr("校时"));
  setAttribute(Qt::WA_DeleteOnClose);

  connect(sendButton, SIGNAL(clicked()), this, SLOT(sendData()));
  connect(udiskButton, SIGNAL(clicked()), this, SLOT(udiskData()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

CadjTimeDialog::~CadjTimeDialog()
{

}

void CadjTimeDialog::getSettingsFromWidget(QString str)
{

}

void CadjTimeDialog::setSettingsToWidget(QString str)
{

}

QStringList getUDiskList()
{
    char temp[10];
    UINT type;
    QStringList path;
    //const wchar_t *path;

    temp[0] = 'a';
    temp[1] = ':';
    temp[2] = '\\';
    temp[3] = 0;

    for(char c = 'A'; c < 'Z'; c++)
    {
      temp[0] = c;


      sprintf(temp, "%c:\\", c);
      QString udiskString = QString(temp);

      type = GetDriveType((wchar_t *)udiskString.utf16());

      if(type == DRIVE_REMOVABLE)
      {
          path << udiskString;
          //memcpy(pDst, temp, 4);
          //return path;
      }
    }

    return path;
}

CudiskListDialog::CudiskListDialog(QWidget *parent):QDialog(parent)
{
  QVBoxLayout *vLayout = new QVBoxLayout(this);

  udiskCombo = new QComboBox(this);
  okButton = new QPushButton(tr("确定"),this);
  udiskCombo->addItems(getUDiskList());

  vLayout->addWidget(udiskCombo);
  vLayout->addWidget(okButton);
  setWindowTitle(tr("选择存储的U盘"));
  setLayout(vLayout);

  connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonSlot()));
}

void CudiskListDialog::okButtonSlot()
{
  this->udiskName = udiskCombo->currentText();
  close();
}

void CudiskListDialog::updateUdiskList()
{
    udiskCombo->clear();
    udiskList = getUDiskList();
  udiskCombo->addItems(udiskList);
}

CudiskListDialog::~CudiskListDialog()
{

}

CsendDataDialog::CsendDataDialog(int flag, QWidget *parent):QDialog(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);


  QString str;

  lightnessCheck = new QCheckBox(tr("设置亮度"),this);
  openCloseCheck = new QCheckBox(tr("设置定时开关机"),this);
  adjTimeCheck = new QCheckBox(tr("校时"),this);
  QCheckBox *progCheck = new QCheckBox(tr("节目数据"),this);
  progCheck->setChecked(true);
  progCheck->setEnabled(false);

  str = w->screenArea->getCurrentScreenStr();

  lightnessProperty = new ClightnessProperty(this);
  openCloseProperty = new CopenCloseProperty(this);
  adjTimeProperty = new CadjTimeProperty(this);

  lightnessProperty->setSettingsToWidget(str);
  openCloseProperty->setSettingsToWidget(str);
  adjTimeProperty->setSettingsToWidget(str);

  //lightnessProperty->setFixedWidth(370);
  //lightnessProperty->setFixedHeight(160);

  lightnessProperty->setSettingsToWidget(str);
  openCloseProperty->setSettingsToWidget(str);
  adjTimeProperty->setSettingsToWidget(str);

  sendButton = new QPushButton(tr("发送"),this);
  udiskButton = new QPushButton(tr("导出U盘文件"),this);
  cancelButton = new QPushButton(tr("关闭"),this);

  vLayout->addWidget(lightnessCheck);

  QHBoxLayout *hLayout = new QHBoxLayout(this);
  hLayout->addWidget(lightnessProperty);
  hLayout->addStretch(10);
  vLayout->addLayout(hLayout);

  vLayout->addWidget(openCloseCheck);

  hLayout = new QHBoxLayout(this);
  hLayout->addWidget(openCloseProperty);
  hLayout->addStretch(10);
  vLayout->addLayout(hLayout);

  vLayout->addWidget(adjTimeCheck);

  hLayout = new QHBoxLayout(this);
  hLayout->addWidget(adjTimeProperty);
  hLayout->addStretch(10);
  vLayout->addLayout(hLayout);
  vLayout->addWidget(progCheck);

  hLayout = new QHBoxLayout(this);
  hLayout->addWidget(sendButton);
  hLayout->addWidget(udiskButton);
  hLayout->addWidget(cancelButton);
  vLayout->addLayout(hLayout);
  vLayout->addStretch(10);

  lightnessProperty->hide();
  openCloseProperty->hide();
  adjTimeProperty->hide();

  vLayout->setSizeConstraint(QLayout::SetFixedSize);
  setLayout(vLayout);

  if(flag EQ 0)
  {
    this->setWindowTitle(tr("发送数据"));
    adjTimeProperty->sysTimeButton->setChecked(true);
    udiskButton->hide();
  }
  else
  {
    this->setWindowTitle(tr("导出U盘文件"));
    adjTimeProperty->selfTimeButton->setChecked(true);
    sendButton->hide();
  }

  adjTimeProperty->adjTimeModeCheck();

  connect(lightnessCheck, SIGNAL(clicked()), this, SLOT(propertyCheckProc()));
  connect(openCloseCheck, SIGNAL(clicked()), this, SLOT(propertyCheckProc()));
  connect(adjTimeCheck, SIGNAL(clicked()), this, SLOT(propertyCheckProc()));

  connect(sendButton, SIGNAL(clicked()), this, SLOT(sendData()));
  connect(udiskButton, SIGNAL(clicked()), this, SLOT(uDiskData()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

  connect(this, SIGNAL(closeSignal()), this, SLOT(close()));
  setAttribute(Qt::WA_DeleteOnClose);
}

void CsendDataDialog::sendData()
{
    INT8U temp[100];
    int len;
    int flag = 0;
    INT8U Re;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    QString str = w->screenArea->getCurrentScreenStr();

    if(lightnessCheck->isChecked())
        SET_BIT(flag, C_SCREEN_LIGNTNESS);
    if(openCloseCheck->isChecked())
        SET_BIT(flag, C_SCREEN_OC_TIME);
    if(adjTimeCheck->isChecked())
        SET_BIT(flag, C_SCREEN_TIME);

    SET_BIT(flag, C_PROG_NUM);
    SET_BIT(flag, C_PROG_PARA);
    SET_BIT(flag, C_PROG_DATA);

    this->sendButton->setEnabled(false);

    if(QT_SIM_EN)
      Re = makeProtoFileData(str, SIM_MODE, flag);
    else
      Re = makeProtoFileData(str, COM_MODE, flag);

    if(Re)
    {
        bool re = w->comStatus->waitComEnd(temp, sizeof(temp), &len);
        if(re EQ true)
        {
            QMessageBox::information(w, tr("提示"),
                                   tr(SEND_PARA_OK_STR),tr("确定"));
            close(); //发送成功则关闭

        }
        else
        {
            comFailedProc();
        }

        this->sendButton->setEnabled(true);
    }
    else
    {
         this->sendButton->setEnabled(true);
         close(); //生成数据没有成功，关闭，一般是节目分区重叠造成
    }


}

void CsendDataDialog::uDiskData()
{
    INT8U Re;

    int flag = 0;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    this->udiskButton->setEnabled(false);

    QString str = w->screenArea->getCurrentScreenStr();

    if(lightnessCheck->isChecked())
        SET_BIT(flag, C_SCREEN_LIGNTNESS);
    if(openCloseCheck->isChecked())
        SET_BIT(flag, C_SCREEN_OC_TIME);
    if(adjTimeCheck->isChecked())
        SET_BIT(flag, C_SCREEN_TIME);

    SET_BIT(flag, C_PROG_NUM);
    SET_BIT(flag, C_PROG_PARA);
    SET_BIT(flag, C_PROG_DATA);

    Re = makeProtoFileData(str, UDISK_MODE, flag);

    if(Re)
    {
        //U盘模式下不需要等待waitComEnd，因为没有通信返回数据需要等待
        if(w->comStatus->getComStatus() == COM_OK) //通信成功的情况下关闭
        {
            QMessageBox::information(w, QObject::tr("提示"),
                                    w->comStatus->getComReStr(),QObject::tr("确定"));
            close();
        }
        else
        {
            QMessageBox::warning(w, QObject::tr("提示"),
                                    w->comStatus->getComReStr(),QObject::tr("确定"));
        }

        this->udiskButton->setEnabled(true);
    }
    else
    {
        this->udiskButton->setEnabled(true);
        close();
    }

}

void CsendDataDialog::propertyCheckProc()
{
  if(lightnessCheck->isChecked())
      lightnessProperty->show();
  else
      lightnessProperty->hide();

  if(openCloseCheck->isChecked())
      openCloseProperty->show();
  else
      openCloseProperty->hide();

  if(adjTimeCheck->isChecked())
      adjTimeProperty->show();
  else
      adjTimeProperty->hide();

  this->resize(this->sizeHint());;
}

CsendDataDialog::~CsendDataDialog()
{

}

/*
//screen属性窗
class CfacScreenProperty:public QWidget
{
    Q_OBJECT
 QGroupBox *cardGroup;
 QGroupBox *baseParaGroup;
 QGroupBox *advanceParaGroup;

 QComboBox *cardCombo; //选择卡类型
 QTextEdit *cardPara; //卡参数

 //基本参数
 QLineEdit *screenIDEdit; // 屏幕ID
 QComboBox *dataPolarityCombo; //数据极性
 QComboBox *oePolarityCombo; //OE极性
 QComboBox *colorCombo; //颜色
 QLineEdit *widthEdit; //屏宽
 QLineEdit *heightEdit; //屏高
 QCheckBox *138Check;     //是否有138译码器
 QComboBox *scanModeCombo; //扫描方式

 //高级设置
 QCheckBox *defParaCheck; //使用默认参数
 QComboBox *freqCombo; //扫描频率
 QSpinBox *lineHideCombo; //行消隐藏
 //------------------

 QPushButton *endButton;
 QPushButton *readParaButton;
 QPushButton *cancelButton;
 QPushButton *okButton;
public:
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CfacScreenProperty(QWidget *parent=0);
    ~CfacScreenProperty();
};
*/

CipInput::CipInput(QWidget *parent):QLineEdit(parent)
{/*
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    for(int i = 0; i < 4; i++)
    {

      edit[i] = new QLineEdit(this);
      //edit[i]->setFixedWidth(25);


      QRegExp rx("(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-4]|[01]?\\d\\d?") ;

         //ipLabel = new QLabel(tr("IP Address:"));
        // ipLineEdit = new QLineEdit;
         //ipLabel->setBuddy(ipLineEdit);

         QValidator *validator = new QRegExpValidator(rx, this);
         edit[i]->setValidator(validator);
         edit[i]->setInputMask("000.000.000.000;");


      hLayout->addWidget(edit[i],10);
      if(i!=3)
      {
        QLabel *label = new QLabel(".",this);
        label->setFixedWidth(2);
        hLayout->addWidget(label,1);
      }
    }

    hLayout->addStretch(10);
    setLayout(hLayout);
    */

    //QHBoxLayout *hLayout = new QHBoxLayout(this);
    QRegExp rx("(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-4]|[01]?\\d\\d?") ;

    //ipLabel = new QLabel(tr("IP Address:"));
    // ipLineEdit = new QLineEdit;
    //ipLabel->setBuddy(ipLineEdit);

    //edit = new QLineEdit(this);
    QValidator *validator = new QRegExpValidator(rx, this);
    this->setValidator(validator);
    this->setInputMask("000.000.000.000;_");

    this->setFixedWidth(100);
    //hLayout->addWidget(edit);
    //setLayout(hLayout);
}

void CipInput::getSettingsFromWidget(QString str)
{

}

void CipInput::setSettingsToWidget(QString str)
{

}

QString ipToStr(INT8U ip)
{
  char str[4];
  //QString ipStr ="";

  str[3] = 0;
  str[2] = (ip % 10) + 0x30;
  ip = ip / 10;
  str[1] = (ip % 10) + 0x30;
  ip = ip / 10;
  str[0] = (ip % 10) + 0x30;

  return QString((char *)str);
}

void CipInput::setIP(INT32U IP)
{
  INT8U ip[4];
  QString ipStr;

  ip[3] = IP % 256;
  IP = IP >> 8;
  ip[2] = IP % 256;
  IP = IP >> 8;
  ip[1] = IP % 256;
  IP = IP >> 8;
  ip[0] = IP % 256;

  ipStr = ipToStr(ip[3]) + "." + ipToStr(ip[2]) + "." + \
          ipToStr(ip[1]) + "." + ipToStr(ip[0]);

  this->setText(ipStr);
}

INT32U CipInput::getIP()
{
  INT8U ipBytes[4];
  QString ipStr = this->text();

  ipStr.replace(" ","0");
  ipStr.remove(".");

  long long int ip = ipStr.toLongLong();
  ipBytes[3] = ip % 1000;
  ip = ip / 1000;
  ipBytes[2] = ip % 1000;
  ip = ip / 1000;
  ipBytes[1] = ip % 1000;
  ip = ip / 1000;
  ipBytes[0] = ip % 1000;

  return (INT32U)(ipBytes[0] + ipBytes[1] * 256 + ipBytes[2] * 256 *256 + ipBytes[3] * 256 * 256 *256);
}

CipInput::~CipInput()
{

}

CcomTest::CcomTest(QWidget *parent):QGroupBox(parent)
{
  //QVBoxLayout *vLayout = new QVBoxLayout(this);
  QGridLayout *gridLayout = new QGridLayout(this);
  QVBoxLayout *vLayout = new QVBoxLayout(this);

  QLabel *comModeLabel = new QLabel(tr("通信方式"),this);
  comModeCombo = new QComboBox(this);
  comModeCombo->addItem(tr(COM_MODE_STR));
  //comModeCombo->addItem(tr(WIFI_MODE_STR));
  QLabel *screenIDLabel = new QLabel(tr("屏幕地址"),this);
  screenIDEdit = new QSpinBox(this);
  comPortLabel = new QLabel(tr("串口号"),this);
  comPortEdit = new QComboBox(this);

  //QextSerialPort *comm = new QextSerialPort();
  //comm->setQueryMode(QextSerialPort::EventDriven);
/*
  QextSerialEnumerator enumer;
  QList<QextPortInfo> ports = enumer.getPorts();
  QStringList strlist;

  strlist.clear();
  for( int i = 0; i < ports.count(); ++i)
      strlist << QObject::tr(ports.at(i).portName.toLocal8Bit());
*/
  QStringList strlist = getComPortList();
  comPortEdit->addItems(strlist);

  comBaudLabel = new QLabel(tr("波特率"),this);
  comBaudCombo = new QComboBox(this);
  comBaudCombo->addItem("57600");
  comBaudCombo->addItem("9600");
  ipEditLabel = new QLabel(tr("屏幕IP"),this);
  ipEdit = new CipInput(this);

  ipEdit->setIP(DEF_ETH_DST_IP);//默认ip 192.168.1.251

  manualConnectButton = new QPushButton(tr("手动连接"),this);
  autoConnectButton = new QPushButton(tr("自动连接"),this);
  comPortInfoLabel = new QLabel(tr("使用直通串口线"));

  gridLayout->addWidget(comModeLabel, 0, 0,1,1);
  gridLayout->addWidget(comModeCombo,  0, 1,1,2);
  gridLayout->addWidget(screenIDLabel, 1, 0,1,1);
  gridLayout->addWidget(screenIDEdit, 1,1,1,2);
  gridLayout->addWidget(comPortLabel, 2, 0,1,1);
  gridLayout->addWidget(comPortEdit, 2, 1,1,2);
  gridLayout->addWidget(comBaudLabel, 3, 0,1,1);
  gridLayout->addWidget(comBaudCombo, 3, 1,1,2);
  gridLayout->addWidget(ipEditLabel, 4, 0,1,1);
  gridLayout->addWidget(ipEdit, 4,1,1,3);
  gridLayout->addWidget(comPortInfoLabel, 5,0,1,3);
  gridLayout->addWidget(manualConnectButton, 6,0,1,3);
  gridLayout->addWidget(autoConnectButton, 7,0,1,3);

  vLayout->addLayout(gridLayout);
  vLayout->addStretch(100);

  setLayout(vLayout);
  setTitle(tr("通信参数"));

  comPortEdit->setEditable(true);
  comPortEdit->setFocusPolicy(Qt::NoFocus);

  connect(comModeCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(editSignal()));
  connect(comPortEdit, SIGNAL(currentIndexChanged(int)), this, SIGNAL(editSignal()));
  connect(screenIDEdit, SIGNAL(valueChanged(int)), this, SIGNAL(editSignal()));
  connect(comBaudCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(editSignal()));
  connect(ipEdit, SIGNAL(editSignal()), this, SIGNAL(editSignal()));
  connect(this->manualConnectButton, SIGNAL(clicked()), this, SLOT(manualConnect()));
  connect(this->autoConnectButton, SIGNAL(clicked()), this, SLOT(autoConnect()));

  connect(this, SIGNAL(editSignal()), this, SLOT(editSlot()));

  //------------暂时屏蔽----
  //ipEditLabel->setVisible(false);
  //ipEdit->setVisible(false);


}

//自动连接
void CcomTest::autoConnect()
{
    INT8U temp[100];
    int len;
    QString oldComPortStr;
    int oldComMode;
    int oldComBaud;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    QStringList portList = getComPortList();

    QString screenStr = w->screenArea->getCurrentScreenStr();

    this->autoConnectButton->setEnabled(false);

    settings.beginGroup(screenStr);
    settings.beginGroup("comTest");

    oldComMode = settings.value("comMode").toInt(); //老的通信模式
    oldComBaud = settings.value("baud").toInt(); //老的波特率
    oldComPortStr = settings.value("comPort").toString(); //保存老的端口

    settings.setValue("comMode", 0); //串口通信方式
    settings.endGroup();
    settings.endGroup();

    for(int i = 0; i < portList.size(); i ++)
    {
        for(int j = 0; j < 2; j ++)
        {
            settings.beginGroup(screenStr);
            settings.beginGroup("comTest");

            settings.setValue("comPort", portList.at(i)); //设置端口
            settings.setValue("baud", j); //设置波特率

            settings.endGroup();
            settings.endGroup();

            w->comStatus->comThread->setComTimeOutSec(SEARCH_COM_TIME_OUT);

            makeProtoBufData(screenStr, COM_MODE, C_SOFT_VERSION | RD_CMD, (char *)0, 0);
            bool re = w->comStatus->waitComEnd(temp, sizeof(temp), &len);

            if(re EQ true)
            {
                QMessageBox::information(w, tr("提示"),
                                       tr("连接成功！") + portList.at(i) + tr("将被设置为当前显示屏通信串口。"),tr("确定"));

                setSettingsToWidget(screenStr);

                this->autoConnectButton->setEnabled(true);

                w->comStatus->comThread->setComTimeOutSec(DEF_COM_TIME_OUT);

                return;

            }
        }

    }

    //恢复之前的通信参数
    settings.beginGroup(screenStr);
    settings.beginGroup("comTest");

    settings.setValue("comPort", oldComPortStr);
    settings.setValue("baud", oldComBaud);
    settings.setValue("comMode", oldComMode);

    settings.endGroup();
    settings.endGroup();

    QMessageBox::warning(w, tr("提示"),
                               tr("连接失败，没有找到连接成功的串口！"),tr("确定"));

    this->autoConnectButton->setEnabled(true);

    w->comStatus->comThread->setComTimeOutSec(DEF_COM_TIME_OUT);

}

//自动连接
void CcomTest::manualConnect()
{
    INT8U temp[100];
    int len;
    QString oldComPortStr;
    int oldComMode;
    int oldComBaud;

    //QStringList portList = getComPortList();

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    QString screenStr = w->screenArea->getCurrentScreenStr();

    this->manualConnectButton->setEnabled(false);

    settings.beginGroup(screenStr);
    settings.beginGroup("comTest");

    oldComMode = settings.value("comMode").toInt(); //老的通信模式
    oldComBaud = settings.value("baud").toInt(); //老的波特率
    oldComPortStr = settings.value("comPort").toString(); //保存老的端口

    settings.setValue("comMode", 0); //串口通信方式
    settings.endGroup();
    settings.endGroup();

    getSettingsFromWidget(screenStr);

    makeProtoBufData(screenStr, COM_MODE, C_SOFT_VERSION | RD_CMD, (char *)0, 0);

    bool re = w->comStatus->waitComEnd(temp, sizeof(temp), &len);
    if(re EQ true)
    {
        QMessageBox::information(w, tr("提示"),
                               tr("连接成功！") + comPortEdit->currentText() + tr("将被设置为当前显示屏通信串口。"),tr("确定"));

    }
    else
    {
        //恢复之前的通信参数
        settings.beginGroup(screenStr);
        settings.beginGroup("comTest");

        settings.setValue("comPort", oldComPortStr);
        settings.setValue("baud", oldComBaud);
        settings.setValue("comMode", oldComMode);

        settings.endGroup();
        settings.endGroup();

        QMessageBox::warning(w, tr("提示"),
                                   tr("连接失败！"),tr("确定"));
    }
    this->manualConnectButton->setEnabled(true);
/*
    INT8U temp[100];
    int len;

    QString screenStr = w->screenArea->getCurrentScreenStr();

    this->manualConnectButton->setEnabled(false);

    makeProtoBufData(screenStr, COM_MODE, C_SOFT_VERSION | RD_CMD, (char *)temp, 0);

    bool re = w->comStatus->waitComEnd(temp, sizeof(temp), &len);
    if(re EQ true)
    {
        QMessageBox::information(w, tr("提示"),
                               tr("连接成功！"),tr("确定"));

    }
    else
    {
        QMessageBox::warning(w, tr("提示"),
                               tr("连接失败！"),tr("确定"));
    }

    this->manualConnectButton->setEnabled(true);
    */
}

/*
    QComboBox *comModeCombo; //通信方式
    QSpinBox *screenIDEdit; //屏幕ID，硬件地址
    QComboBox *comPortEdit; //串口号
    QComboBox *comBaudCombo; //波特率
    CipInput *ipEdit; //IP地址
    QPushButton *connectButton; //链接按钮
 */

void CcomTest::editSlot()
{
  QString screenStr;

  screenStr = w->screenArea->getCurrentScreenStr();

  comModeChangedProc();
  getSettingsFromWidget(screenStr);
}

void CcomTest::getSettingsFromWidget(QString str)
{
    settings.beginGroup(str);
    settings.beginGroup("comTest");

    int index = comTxt2Index(comModeCombo->currentText());
    settings.setValue("comMode", index);//comModeCombo->currentIndex());
    debug("get commode = %d", index);

    settings.setValue("screenID", screenIDEdit->value());
    settings.setValue("comPort", comPortEdit->currentText());
    //settings.setValue("comPort", comPortEdit->currentIndex());

    settings.setValue("baud", comBaudCombo->currentIndex());
    settings.setValue("ip", ipEdit->getIP());

    settings.setValue("setFlag", 1);
    settings.endGroup();
    settings.endGroup();
}

void CcomTest::comModeChangedProc()
{
    QString comStr;

    comStr = comModeCombo->currentText();
    if(comStr == tr(COM_MODE_STR))
    {
        comPortLabel->setVisible(true);
        comPortEdit->setVisible(true); //串口号
        comBaudCombo->setVisible(true); //波特率
        comBaudLabel->setVisible(true);
        comPortInfoLabel->setVisible(true);

        ipEdit->setVisible(false);; //IP地址
        ipEditLabel->setVisible(false);

        manualConnectButton->setVisible(true);; //手动连接
        autoConnectButton->setVisible(true);; //自动连连接
    }
    else //if(comStr == tr("网口"))
    {
        comPortLabel->setVisible(false);
        comPortEdit->setVisible(false); //串口号
        comBaudCombo->setVisible(false); //波特率
        comBaudLabel->setVisible(false);
        comPortInfoLabel->setVisible(false);

        ipEdit->setVisible(true);; //IP地址
        ipEditLabel->setVisible(true);

        manualConnectButton->setVisible(true);; //手动连接
        autoConnectButton->setVisible(false);; //自动连连接

        if(comStr == tr(WIFI_MODE_STR))
        {
          ipEdit->setVisible(false);
          ipEditLabel->setVisible(false);
        }
        else
        {
          ipEdit->setVisible(true);
          ipEditLabel->setVisible(true);
        }
    }
}

void CcomTest::cardChangedProc(QString cardName)
{
  S_Card_Para Card_Para;
  //int index;

  disconnect(this, SIGNAL(editSignal()), this, SLOT(editSlot()));

  getCardParaFromSettings(cardName, Card_Para);
  if(Card_Para.Com_Mode & COM_ETH) //支持以太网
  {
    if(this->comModeCombo->findText(tr(ETH_MODE_STR)) < 0)
      this->comModeCombo->addItem(tr(ETH_MODE_STR));

  }
  else
  {
      int index = this->comModeCombo->findText(tr(ETH_MODE_STR));
      if(index >= 0)
        this->comModeCombo->removeItem(index);
  }

  connect(this, SIGNAL(editSignal()), this, SLOT(editSlot()));

  comModeChangedProc();
}

/*
void getComTestParaFromSettings(QString str, S_Screen_Para &screenPara)
{
    settings.beginGroup(str);
    settings.beginGroup("comTest");

    screenPara.Com_Mode = settings.value("comMode").toInt();
    screenPara.Com_Port = settings.value("comPort").toInt();

    screenPara.COM_Para.Addr = settings.value("screenID").toInt();
    screenPara.COM_Para.Baud = settings.value("baud").toInt();

    screenPara.Net_Para.IP = settings.value("ip").toInt();

    settings.endGroup();
    settings.endGroup();

    SET_SUM(screenPara);
}
*/
void CcomTest::setSettingsToWidget(QString str)
{
    QString comPort;

    disconnect(this, SIGNAL(editSignal()), this, SLOT(editSlot()));

    settings.beginGroup(str);
    settings.beginGroup("comTest");

    //comModeCombo->setCurrentIndex(settings.value("comMode").toInt());
    QString comTxt = index2ComTxt(settings.value("comMode").toInt());
    comModeCombo->setCurrentIndex(comModeCombo->findText(comTxt));

    debug("set commode = %d", settings.value("comMode").toInt());
    screenIDEdit->setValue(settings.value("screenID").toInt());
    comPort = settings.value("comPort").toString();
    if(comPort EQ "")
     {
        if(getComPortList().count() > 0)
          comPort = getComPortList().at(0);
     }
    comPortEdit->setEditText(comPort);

    comBaudCombo->setCurrentIndex(settings.value("baud").toInt());

    if(settings.value("setFlag").toInt())
      ipEdit->setIP(settings.value("ip").toInt());
    else
      ipEdit->setIP(DEF_ETH_DST_IP);

    settings.endGroup();
    settings.endGroup();

    connect(this, SIGNAL(editSignal()), this, SLOT(editSlot()));

    comModeChangedProc();
}

CcomTest::~CcomTest()
{

}

//工厂参数编辑
//flag NEW_SCN表示新建屏幕参数,MODI_SCN表示修改现有屏幕参数,SHOW_SCN表示显示参数
CfacScreenProperty::CfacScreenProperty(int flag, CcomTest *com,  QWidget *parent):QGroupBox(parent)
{

    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    QGridLayout *gridLayout;

    QHBoxLayout *mainLayout;
    QVBoxLayout *mainVLayout;

    paraFlag = flag;

    this->comTest = com;

    mainVLayout = new QVBoxLayout(this);
    mainLayout = new QHBoxLayout(this);
    hLayout = new QHBoxLayout(this);

    tabWidget= new QTabWidget(this);
    //setFixedWidth(400);

    //控制组件group
    cardGroup = new QWidget(this);//QGroupBox(tr("控制组件"), this);//CnameEdit(this);
    vLayout = new QVBoxLayout(this);
    cardCombo = new QComboBox(this);
    readCardTypeButton = new QPushButton(tr("读取卡类型"), this);
    cardCombo->setFixedWidth(100);

    //获取所有卡的列表
    cardSettings.beginGroup("");
    QStringList cardList = cardSettings.childGroups();
    cardSettings.endGroup();

    cardCombo->addItems(cardList);

    cardParaEdit = new QTextEdit(this);
    cardParaEdit->setFocusPolicy(Qt::NoFocus); //禁止键盘输入(false);
    cardParaEdit->setFixedHeight(80);

    hLayout =new QHBoxLayout(this);
    hLayout ->addWidget(cardCombo);
    hLayout ->addWidget(readCardTypeButton);
    hLayout ->addStretch();

    vLayout->addLayout(hLayout);//addWidget(cardCombo);
    vLayout->addWidget(cardParaEdit);
    cardGroup->setLayout(vLayout);
    tabWidget-> addTab(cardGroup, tr("控制组件"));



    //-------------
    baseParaGroup = new QWidget(this);//QGroupBox(tr("基本参数"),this);
    screenIDEdit = new QSpinBox(this);
    screenIDEdit->setFixedWidth(WIDTH_0);

    baudCombo = new QComboBox(this);
    baudCombo->addItem("57600");
    baudCombo->addItem("9600");
    baudCombo->setFixedWidth(WIDTH_0);

    redGreenRevCheck = new QCheckBox(tr("红绿取反"),this);

    dataPolarityCombo = new QComboBox(this);
    dataPolarityCombo->addItem(tr("负极性"));
    dataPolarityCombo->addItem(tr("正极性"));
    dataPolarityCombo->setFixedWidth(WIDTH_0);

    oePolarityCombo = new QComboBox(this);
    oePolarityCombo->addItem(tr("低有效"));
    oePolarityCombo->addItem(tr("高有效"));
    oePolarityCombo->setFixedWidth(WIDTH_0);

    lineHideLabel = new QLabel(tr("行消隐"),this);
    lineHideCombo = new QComboBox(this);

    lineHideCombo->addItem(tr("1最短"));
    lineHideCombo->addItem(tr("2"));
    lineHideCombo->addItem(tr("3"));
    lineHideCombo->addItem(tr("4"));
    lineHideCombo->addItem(tr("5"));
    lineHideCombo->addItem(tr("6"));
    lineHideCombo->addItem(tr("7"));
    lineHideCombo->addItem(tr("8"));
    lineHideCombo->addItem(tr("9"));
    lineHideCombo->addItem(tr("10最长"));

    colorCombo = new QComboBox(this);
    colorCombo->addItem(tr("红色"));
    colorCombo->addItem(tr("红+绿"));
    //colorCombo->addItem(tr("全彩"));

    colorCombo->setFixedWidth(WIDTH_0);

    widthEdit = new QSpinBox(this);
    widthEdit->setFixedWidth(WIDTH_0);
    widthEdit->setSingleStep(8);
    widthEdit->setMinimum(8);
    widthEdit->setMaximum(8192);
    //widthEdit->setFocusPolicy(Qt::NoFocus); //禁止键盘输入
    widthEdit->setValue(DEF_SCN_WIDTH); //初始默认值

    heightEdit = new QSpinBox(this);
    heightEdit->setFixedWidth(WIDTH_0);
    heightEdit->setSingleStep(8);
    heightEdit->setMinimum(8);
    heightEdit->setMaximum(4096);
    //heightEdit->setFocusPolicy(Qt::NoFocus); //禁止键盘输入
    heightEdit->setValue(DEF_SCN_HEIGHT); //初始默认值

    _138Combo = new QComboBox(this);//new QCheckBox(tr("使用138译码器"),this);
    _138Combo->addItem(tr("有"));
    _138Combo->addItem(tr("无"));

    //----------------------------------------------------------------


    QLabel *screenIDLabel  = new QLabel(tr("屏幕地址"),this);
    //QLabel *screenIDInfoLabel = new QLabel(tr("(多屏幕组网时每个屏号应该唯一)"),this);
    QLabel *baudComboLabel = new QLabel(tr("波特率"),this);
   QLabel *dataPolarityLabel = new QLabel(tr("数据极性"),this);
   QLabel *oePolarityLabel = new QLabel(tr("OE极性"),this);
   QLabel *colorLabel = new QLabel(tr("颜色"),this);
   QLabel *widthLabel = new QLabel(tr("屏宽"),this);
   QLabel *heightLabel = new QLabel(tr("屏高"),this);


   gridLayout = new QGridLayout(this);

   gridLayout->addWidget(screenIDLabel, 0, 0);
   gridLayout->addWidget(screenIDEdit, 0, 1);
   gridLayout->addWidget(baudComboLabel, 0, 2);
   gridLayout->addWidget(baudCombo, 0, 3);


   gridLayout->addWidget(widthLabel, 1, 0);
   gridLayout->addWidget(widthEdit, 1, 1);
   gridLayout->addWidget(heightLabel, 1, 2);
   gridLayout->addWidget(heightEdit, 1, 3);

   gridLayout->addWidget(colorLabel, 1, 4);
   gridLayout->addWidget(colorCombo, 1, 5);


   gridLayout->addWidget(dataPolarityLabel, 2, 0);
   gridLayout->addWidget(dataPolarityCombo, 2, 1);
   /*-----------不需要软件设置OE，直接硬件跳线选择--------*/
   gridLayout->addWidget(oePolarityLabel, 2, 2);
   gridLayout->addWidget(oePolarityCombo, 2, 3);


   //gridLayout->addWidget(lineHideLabel, 2, 4);
   //gridLayout->addWidget(lineHideCombo,2,5);

   gridLayout->addWidget(redGreenRevCheck,2,4,1,2);




   //--------------------------------



   //---------------------------------

   baseParaGroup->setLayout(gridLayout);
   tabWidget->addTab(baseParaGroup, tr("基本参数"));

   //---------------扫描参数---------------
   //QLabel *scanModeLabel = new QLabel(tr("扫描方式"),this);
   scanParaGroup = new QWidget(this);//QGroupBox(tr("基本参数"),this);
   scanModeCombo = new QComboBox(this);
   selfTestButton = new QPushButton(tr("自动检测"), this);
   QLabel *scanModeInfo = new QLabel(tr("选择框内前4位数字为扫描方式的特征码，自动检测时显示在屏幕左上角"), this);
   scanPicWidget = new QWidget(this);

   gridLayout = new QGridLayout(this);

   //---------------------------------------------------------------
   QString modeString;
   //int direct, scanLine, rowsFold, colsFold, lines;

   for(unsigned int i = 0; i < S_NUM(scanMode); i ++)
   {
       modeString.clear();
       modeString = getScanCodeString(scanMode[i].code);
       scanModeCombo->addItem(modeString);
   }
   gridLayout->addWidget(scanModeInfo, 0, 0, 1, 6);
   gridLayout->addWidget(scanModeCombo, 1, 0, 1, 5);
   gridLayout->addWidget(selfTestButton, 1, 5, 1, 1);
   gridLayout->addWidget(scanPicWidget, 2, 0, 3, 6);

   scanParaGroup->setLayout(gridLayout);
   tabWidget->addTab(scanParaGroup, tr("扫描参数"));

   //---------------网络参数-------------
   netParaGroup = new QWidget(this);
   gridLayout = new QGridLayout(this);
   //newScreenIDEdit = new QLineEdit(this);
   //newScreenIDEdit->setFixedWidth(40);
   //comModeCombo = new QComboBox(this);

   //ipModeCombo = new QComboBox(this);
   ipEdit = new CipInput(this);
   //newIpEdit = new QLineEdit(this);
   maskEdit = new CipInput(this);
   gateEdit = new CipInput(this);
   macEdit = new CipInput(this);

   ipEdit->setIP(DEF_ETH_DST_IP);//192.168.1.251
   maskEdit->setIP(0x00FFFFFF);//255.255.255.0
   gateEdit->setIP(0x0101A8C0);//192.168.1.1
   //QRegExp rx("(2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})");
   //QRegExpValidator validatorIP(QRegExp("[0-9]{1,3}(.[0-9]{1,3}){3,3}"), this);
   //ipEdit->setValidator(&validatorIP);


   //QLabel *ipModeComboLabel = new QLabel(tr("IP方式"));
   QLabel *ipEditLabel = new QLabel(tr("屏幕IP"),this);
   //QLabel *newIpEditLabel = new QLabel(tr("新IP"),this);
   QLabel *maskEditLabel = new QLabel(tr("子网掩码"),this);
   QLabel *gateEditLabel = new QLabel(tr("网关"),this);
   QLabel *macEditLabel = new QLabel(tr("MAC地址"));

   macEdit->setVisible(false); //mac地址不允许用户设置
   macEditLabel->setVisible(false);

   //QLabel *ipPortLabel = new QLabel(tr("端口: 7788"));



   //gridLayout->addWidget(ipModeComboLabel, 0, 0);
   //gridLayout->addWidget(ipModeCombo, 0, 1);

   gridLayout->addWidget(ipEditLabel, 1, 0);
   gridLayout->addWidget(ipEdit, 1, 1, 1, 3);
   gridLayout->addWidget(maskEditLabel, 1, 4);
   gridLayout->addWidget(maskEdit, 1, 5,1,3);

   gridLayout->addWidget(gateEditLabel, 2, 0);
   gridLayout->addWidget(gateEdit, 2, 1, 1, 3);
   gridLayout->addWidget(macEditLabel, 2, 4);
   gridLayout->addWidget(macEdit, 2, 5, 1, 3);
   //gridLayout->addWidget(ipEditLabel, 3, 0);
   //gridLayout->addWidget(ipEdit, 5, 0, 1, 2);
   //gridLayout->addWidget(ipPortLabel, 6, 0);

   netParaGroup->setLayout(gridLayout);
   tabWidget->addTab(netParaGroup, tr("网络参数"));

   //tabWidget->setTabEnabled(0,false);
   //netParaGroup->setVisible(false);
   //-----------------------------------


   advanceParaGroup = new QWidget(this);//QGroupBox(tr("高级配置"),this);
   defParaCheck = new QCheckBox(tr("使用默认设置"),this);
   defParaCheck->setChecked(true);

   freqCombo = new QComboBox(this);

   freqCombo ->addItem(tr("1最快"));
   freqCombo ->addItem(tr("2"));
   freqCombo ->addItem(tr("3"));
   freqCombo ->addItem(tr("4"));
   freqCombo ->addItem(tr("5"));
   freqCombo ->addItem(tr("6"));
   freqCombo ->addItem(tr("7"));
   freqCombo ->addItem(tr("8"));
   freqCombo ->addItem(tr("9"));
   freqCombo ->addItem(tr("10最慢"));

   dataMirrorCombo = new QComboBox(this);
   dataMirrorCombo->addItem(tr("正常"));
   dataMirrorCombo->addItem(tr("镜像"));

   lineOrderCombo = new QComboBox(this);

   lineOrderCombo->addItem(tr("正常"));
   lineOrderCombo->addItem(("+1"));
   lineOrderCombo->addItem(("-1"));

   vLayout = new QVBoxLayout(this);

   gridLayout = new QGridLayout(this);
   freqLabel = new QLabel(tr("刷新频率"),this);

   dataMirrorLabel = new QLabel(tr("数据镜像"),this);
   lineOrderLabel = new QLabel(tr("行顺序"),this);
   _138Label= new QLabel(tr("138译码器"), this);

   gridLayout->addWidget(defParaCheck,0,0,1,2);

   gridLayout->addWidget(freqLabel, 1, 0);
   gridLayout->addWidget(freqCombo, 1, 1);

   gridLayout->addWidget(lineHideLabel, 1, 2);
   gridLayout->addWidget(lineHideCombo,1,3);
   //gridLayout->addWidget(dataMirrorLabel, 2, 0);
   //gridLayout->addWidget(dataMirrorCombo, 2, 1);
   gridLayout->addWidget(_138Label, 2, 0);
   gridLayout->addWidget(_138Combo, 2, 1);

   gridLayout->addWidget(lineOrderLabel, 2, 2);
   gridLayout->addWidget(lineOrderCombo,2,3);

   advanceParaGroup->setLayout(gridLayout);
   tabWidget->addTab(advanceParaGroup, tr("高级参数"));

   //参数回读
   vLayout = new QVBoxLayout(this);
   hLayout = new QHBoxLayout(this);
   readParaGroup = new QWidget(this);//QGroupBox(tr("参数回传"),this);
   readParaEdit = new QTextEdit(tr("--显示读回参数--"),this);
   readParaEdit->setFocusPolicy(Qt::NoFocus); //禁止键盘输入(false);
   readParaEdit->setFixedHeight(60);
   readParaButton = new QPushButton(tr("回读参数"),this);
   importParaButton = new QPushButton(tr("导入参数"),this);
   vLayout->addWidget(readParaEdit);
   //hLayout->addStretch();
   hLayout->addWidget(readParaButton);
   hLayout->addWidget(importParaButton);
   vLayout->addLayout(hLayout);
   readParaGroup->setLayout(vLayout);
   tabWidget->addTab(readParaGroup, tr("回读参数"));


   hLayout = new QHBoxLayout(this);
   endButton = new QPushButton(tr("关闭"), this);
   comLoadButton = new QPushButton(tr("通信加载参数"), this);
   udiskLoadButton = new QPushButton(tr("U盘加载参数"), this);
   //exportButton = new QPushButton(tr("导出配置文件"), this);
  // saveButton = new QPushButton(tr("保存参数"), this);
   //defButton = new QPushButton(tr("恢复默认"), this);

   hLayout->addStretch();
   hLayout->addWidget(comLoadButton);
   hLayout->addStretch();
   hLayout->addWidget(udiskLoadButton);
   hLayout->addStretch();
   hLayout->addWidget(endButton);
   hLayout->addStretch();
   //vLayout->addWidget(exportButton);
   //vLayout->addStretch(10);
   //vLayout->addWidget(cancelButton);
   //hLayout->addStretch(10);
   //hLayout = new QHBoxLayout(this);
   //QGroupBox *comTestGroup = new QGroupBox(this);
   //comTest = new CcomTest(this);
   //hLayout->addWidget(comTest);
   //comTestGroup->setLayout(hLayout);

   mainLayout->addWidget(tabWidget);
   //mainLayout->addWidget(endButton);
   //mainLayout->addWidget(comTest);
   //mainLayout->addLayout(vLayout);
   mainVLayout->addLayout(mainLayout);
   mainVLayout->addLayout(hLayout);

   //endButton->setVisible(false);
   //comLoadButton->setVisible(false);

   //mainLayout->addStretch(10);
   setLayout(mainVLayout);


   if(paraFlag EQ SHOW_SCN) //显示参数
   {
       setEditEnable(false);
       //comTest->setVisible(false);
       endButton->setVisible(false);
       comLoadButton->setVisible(false);
       udiskLoadButton->setVisible(false);
       tabWidget->removeTab(tabWidget->indexOf(readParaGroup));
   }
     //this->setc

  setTitle(tr("屏幕参数"));

  connect(defParaCheck, SIGNAL(stateChanged(int)), this, SLOT(defParaCheckProc()));
  connect(cardCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(cardChangeProc()));
   connect(comLoadButton, SIGNAL(clicked()), this, SLOT(comLoadParaProc()));
   connect(udiskLoadButton, SIGNAL(clicked()), this, SLOT(udiskLoadParaProc()));
   connect(endButton, SIGNAL(clicked()), this, SLOT(endProc()));
   connect(selfTestButton, SIGNAL(clicked()), this, SLOT(setTestProc()));
   connect(readParaButton, SIGNAL(clicked()), this, SLOT(readParaProc()));
   connect(importParaButton, SIGNAL(clicked()), this, SLOT(importParaProc()));
   connect(readCardTypeButton, SIGNAL(clicked()), this ,SLOT(readCardType()));
   connect(scanModeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setDefAdvPara()));

   importParaButton->setEnabled(false);

   defParaCheckProc();
   cardChangeProc();

   //----------------------
   readScreenParaFlag = false;
   memset(&readScreenPara, 0, sizeof(readScreenPara));


  //----暂时将网络参数和回读参数删除！
   //tabWidget->removeTab(tabWidget->indexOf(netParaGroup));
   //tabWidget->removeTab(tabWidget->indexOf(readParaGroup));
   //-------------
   //oePolarityLabel->setVisible(false);
   //oePolarityCombo->setVisible(false);

   dataMirrorLabel->setVisible(false);
   dataMirrorCombo->setVisible(false);
}

/*
 //QComboBox *ipModeCombo; //IP获取方式
 //QLineEdit *ipEdit; //IP地址
 CipInput *ipEdit;
 //QLineEdit *newIpEdit; //新IP地址
 CipInput *maskEdit; //子网掩码
 CipInput *gateEdit; //网关掩码
 CipInput *macEdit; //mac地址
 //基本参数
 QSpinBox *screenIDEdit; // 屏幕ID
 QComboBox *baudCombo; //波特率
 QCheckBox *redGreenRevCheck; //红绿
 QComboBox *dataPolarityCombo; //数据极性
 QComboBox *oePolarityCombo; //OE极性

 QComboBox *colorCombo; //颜色
 QSpinBox *widthEdit; //屏宽
 QSpinBox *heightEdit; //屏高
 QCheckBox *_138Combo;     //是否有138译码器
 QComboBox *scanModeCombo; //扫描方式

 //高级设置
 QCheckBox *defParaCheck; //使用默认参数
 QComboBox *freqCombo; //扫描频率
 QSpinBox *lineHideCombo; //行消隐藏
 QComboBox *dataMirrorCombo; //数据镜像
 QComboBox *lineOrderCombo; //行顺序
 //------------------

 CcomTest *comTest;
 */

void CfacScreenProperty::getSettingsFromWidget(QString str)
{/*
    ipEdit->getSettingsFromWidget(str+"/facPara");
    maskEdit->getSettingsFromWidget(str+"/facPara");
    gateEdit->getSettingsFromWidget(str+"/facPara");
    macEdit->getSettingsFromWidget(str+"/facPara");
    //comTest->getSettingsFromWidget(str+"/facPara");
*/
  settings.beginGroup(str);
  settings.beginGroup("facPara");

  settings.setValue("cardType", cardCombo->currentIndex());
  settings.setValue("screenID", screenIDEdit->value()); //硬件地址
  settings.setValue("baud", baudCombo->currentIndex());
  settings.setValue("redGreenRev", redGreenRevCheck->isChecked());
  settings.setValue("dataPolarity", dataPolarityCombo->currentIndex());
  settings.setValue("oePolarity", oePolarityCombo->currentIndex());
  settings.setValue("color", colorCombo->currentIndex());
  settings.setValue("width", widthEdit->value());
  settings.setValue("height", heightEdit->value());
  settings.setValue("138Check", _138Combo->currentIndex());
  settings.setValue("scanMode", scanModeCombo->currentText().mid(0, 4).toInt());

  settings.setValue("advDefPara", defParaCheck->isChecked());
  settings.setValue("freq", freqCombo->currentIndex());
  settings.setValue("lineHide", lineHideCombo->currentIndex());
  settings.setValue("dataMirror", dataMirrorCombo->currentIndex());
  settings.setValue("lineOrder", lineOrderCombo->currentIndex());

  settings.setValue("ip", ipEdit->getIP());
  settings.setValue("mask", maskEdit->getIP());
  settings.setValue("gate", gateEdit->getIP());

  settings.setValue("setFlag", 1);
  settings.endGroup();
  settings.endGroup();


}

void CfacScreenProperty::setSettingsToWidget(QString str)
{
/*
    ipEdit->setSettingsToWidget(str+"/facPara");
    maskEdit->setSettingsToWidget(str+"/facPara");
    gateEdit->setSettingsToWidget(str+"/facPara");
    macEdit->setSettingsToWidget(str+"/facPara");
    //comTest->setSettingsToWidget(str+"/facPara");
*/
    disconnect(defParaCheck, SIGNAL(stateChanged(int)), this, SLOT(defParaCheckProc()));
    disconnect(cardCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(cardChangeProc()));

    settings.beginGroup(str);
    settings.beginGroup("facPara");

    cardCombo->setCurrentIndex(settings.value("cardType").toInt());
    screenIDEdit->setValue(settings.value("screenID").toInt());
    baudCombo->setCurrentIndex(settings.value("baud").toInt());
    redGreenRevCheck->setChecked(settings.value("redGreenRev").toBool());
    dataPolarityCombo->setCurrentIndex(settings.value("dataPolarity").toInt());
    oePolarityCombo->setCurrentIndex(settings.value("oePolarity").toInt());
    colorCombo->setCurrentIndex(settings.value("color").toInt());

    if(settings.value("setFlag").toInt() > 0)
    {
      ipEdit->setIP(settings.value("ip").toInt());
      maskEdit->setIP(settings.value("mask").toInt());
      gateEdit->setIP(settings.value("gate").toInt());

      widthEdit->setValue(settings.value("width").toInt());
      heightEdit->setValue(settings.value("height").toInt());
    }
    else
    {
        ipEdit->setIP(DEF_ETH_DST_IP);//settings.value("ip").toInt());
        maskEdit->setIP(0x00FFFFFF);//settings.value("mask").toInt());
        gateEdit->setIP(0x0101A8C0);//settings.value("gate").toInt());

        widthEdit->setValue(DEF_SCN_WIDTH);
        heightEdit->setValue(DEF_SCN_HEIGHT);
    }

    _138Combo->setCurrentIndex(settings.value("138Check").toInt());
    scanModeCombo->setCurrentIndex(getScanModeIndex(settings.value("scanMode").toInt()));

    defParaCheck->setChecked(settings.value("advDefPara").toBool());
    freqCombo->setCurrentIndex(settings.value("freq").toInt());
    lineHideCombo->setCurrentIndex(settings.value("lineHide").toInt());
    dataMirrorCombo->setCurrentIndex(settings.value("dataMirror").toInt());
    lineOrderCombo->setCurrentIndex(settings.value("lineOrder").toInt());

    settings.endGroup();
    settings.endGroup();

    connect(defParaCheck, SIGNAL(stateChanged(int)), this, SLOT(defParaCheckProc()));
    connect(cardCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(cardChangeProc()));

    this->defParaCheckProc();
    this->cardChangeProc();

}

CfacScreenProperty::~CfacScreenProperty()
{

}

void CfacScreenProperty::setEditEnable(bool flag)
{
    if(flag EQ false)
    {
        cardGroup->setEnabled(false);
        netParaGroup->setEnabled(false);
        baseParaGroup->setEnabled(false);
        scanParaGroup->setEnabled(false);
        advanceParaGroup->setEnabled(false);
        readParaGroup->setEnabled(false);
        comLoadButton->setEnabled(false);
        udiskLoadButton->setEnabled(false);
        //exportButton->setEnabled(false);
        //comTest->setEnabled(false);
    }
    else
    {
        cardGroup->setEnabled(true);
        netParaGroup->setEnabled(true);
        baseParaGroup->setEnabled(true);
        scanParaGroup->setEnabled(true);
        advanceParaGroup->setEnabled(true);
        readParaGroup->setEnabled(true);
        comLoadButton->setEnabled(true);
        udiskLoadButton->setEnabled(true);
        //exportButton->setEnabled(true);
        //comTest->setEnabled(true);
    }
}

extern INT32U RevIP(INT32U IP);

void CfacScreenProperty::readParaProc()
{
    INT8U rcvBuf[500]; //读取屏幕参数缓冲区
    int len;
    bool re;
    QString cardTypeStr;

    QString screenParaStr;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    this->readParaButton->setEnabled(false);

    QString screenStr = w->screenArea->getCurrentScreenStr();

    //读取版本号
    if(QT_SIM_EN)
      makeProtoBufData(screenStr, SIM_MODE, C_SOFT_VERSION | RD_CMD, (char *)0 , 0);
    else
      makeProtoBufData(screenStr, COM_MODE, C_SOFT_VERSION | RD_CMD, (char *)0, 0);

    re = w->comStatus->waitComEnd(rcvBuf, sizeof(rcvBuf), &len);
    if(re EQ true)
    {
      screenParaStr = tr("固件版本:")+QString((char *)rcvBuf) + " ";

      for(int i = 0; i < (int)sizeof(rcvBuf); i ++)
        {
          if(rcvBuf[i] == ' ')
              rcvBuf[i] = 0;
      }

      cardTypeStr = QString(COMPANY_NAME) + QString("-") + QString((char *)rcvBuf);//板卡名称
    }

    if(QT_SIM_EN)
      makeProtoBufData(screenStr, SIM_MODE, C_SCREEN_PARA | RD_CMD, (char *)0 , 0);
    else
      makeProtoBufData(screenStr, COM_MODE, C_SCREEN_PARA | RD_CMD, (char *)0, 0);

    memset(rcvBuf, 0, sizeof(rcvBuf));
    re = w->comStatus->waitComEnd(rcvBuf, sizeof(rcvBuf), &len);
    if(re EQ true)
    {
        //串口卡没有网络相关参数
        if(len > (int)(sizeof(S_Screen_Para) - CHK_BYTE_LEN))
        {
            QMessageBox::warning(w, QObject::tr("提示"),
                                    QObject::tr("读取参数长度错误！"),QObject::tr("确定"));

            this->readParaButton->setEnabled(true);
           return;
        }

        memcpy(&readScreenPara.Base_Para, rcvBuf, len);
        readScreenParaFlag = true;

        //扫描方式
        INT16U scanMode = getScanCodeFromScreenPara(readScreenPara);
        QString scanString = getScanCodeString(scanMode);

        screenParaStr += QObject::tr("\r\n扫描方式:") + scanString;
        //---------------

        screenParaStr += tr("\r\n屏幕宽度:%1,高度:%2,颜色:").arg(readScreenPara.Base_Para.Width).arg(readScreenPara.Base_Para.Height);
        if(readScreenPara.Base_Para.Color & 0x01)
            screenParaStr += tr("红色");
        if(readScreenPara.Base_Para.Color & 0x02)
            screenParaStr += tr("+绿色");
        if(readScreenPara.Base_Para.Color & 0x04)
            screenParaStr += tr("+蓝色");

        screenParaStr += tr("\r\n屏幕地址:%1,波特率:%2,数据极性:%3,红绿取反:%4").\
                         arg(readScreenPara.COM_Para.Addr).\
                         arg((readScreenPara.COM_Para.Baud EQ 0)?57600:9600).\
                         arg((readScreenPara.Scan_Para.Data_Polarity EQ 0)?tr("负极性"):tr("正极性")).\
                         arg((readScreenPara.Scan_Para.RG_Reverse EQ 0)?tr("无"):tr("有"));


        screenParaStr += tr("\r\n刷新频率:%1,行消隐:%2,138译码器:%3,行顺序:%4").\
                         arg(freqCombo->itemText(readScreenPara.Scan_Para.Screen_Freq)).\
                         arg(lineHideCombo->itemText(readScreenPara.Scan_Para.Line_Hide)).\
                         arg(_138Combo->itemText(readScreenPara.Scan_Para._138Check)).\
                         arg(lineOrderCombo->itemText(readScreenPara.Scan_Para.Line_Order));

        S_Card_Para Card_Para;
        getCardParaFromSettings(cardTypeStr, Card_Para);

        if(Card_Para.Com_Mode & COM_ETH)
        {
            //IP地址等
            QHostAddress dstAddr;
            dstAddr.setAddress(RevIP(readScreenPara.Net_Para.IP));
            screenParaStr += tr("\r\nIP地址:")+dstAddr.toString();

            dstAddr.setAddress(RevIP(readScreenPara.Net_Para.Mask));
            screenParaStr += tr(",子网掩码:")+dstAddr.toString();

            dstAddr.setAddress(RevIP(readScreenPara.Net_Para.Gate));
            screenParaStr += tr(",网关:")+dstAddr.toString();
        }

        importParaButton->setEnabled(true);//可以导入参数了
    }


    readParaEdit->setText(screenParaStr);

    this->readParaButton->setEnabled(true);
}

//导入参数处理
void CfacScreenProperty::importParaProc()
{
    QString screenStr = w->screenArea->getCurrentScreenStr();

    setScreenParaToSettings(screenStr, this->readScreenPara);
    setSettingsToWidget(screenStr);

    QMessageBox::information(w, QObject::tr("提示"),
                            QObject::tr("参数导入成功!"),QObject::tr("确定"));
}

//设置默认的高级参数
void CfacScreenProperty::setDefAdvPara()
{
    defParaCheckProc();
}

void CfacScreenProperty::readCardType()
{
    INT8U rcvBuf[500]; //读取屏幕参数缓冲区
    int len;
    bool re;

    QString cardTypeStr;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    this->readCardTypeButton->setEnabled(false);

    QString screenStr = w->screenArea->getCurrentScreenStr();

    //读取版本号
    if(QT_SIM_EN)
      makeProtoBufData(screenStr, SIM_MODE, C_SOFT_VERSION | RD_CMD, (char *)0 , 0);
    else
      makeProtoBufData(screenStr, COM_MODE, C_SOFT_VERSION | RD_CMD, (char *)0, 0);

    re = w->comStatus->waitComEnd(rcvBuf, sizeof(rcvBuf), &len);
    if(re EQ true)
    {
      //screenParaStr = tr("版本号:")+QString((char *)rcvBuf) + " ";
      for(int i = 0; i < (int)sizeof(rcvBuf); i ++)
        {
          if(rcvBuf[i] == ' ')
              rcvBuf[i] = 0;
      }

      cardTypeStr = QString(COMPANY_NAME) + QString("-") + QString((char *)rcvBuf);

      int cardIndex = cardCombo->findText(cardTypeStr);
      if(cardIndex == -1) //没有找到
      {
          QMessageBox::information(w, QObject::tr("提示"),
                                  QObject::tr("控制卡型号为") +cardTypeStr + QObject::tr("，当前软件版本不支持该型号卡，请使用较新版本软件"),QObject::tr("确定"));
      }
      else
      {
        QMessageBox::information(w, QObject::tr("提示"),
                                QObject::tr("控制卡型号为") +cardTypeStr + QObject::tr("，该型号将被设置为当前控制组件"),QObject::tr("确定"));
        cardCombo->setCurrentIndex(cardIndex);
/*
        QString str = w->screenArea->getCurrentScreenStr(); //当前屏幕str
        settings.beginGroup(str);
        settings.beginGroup("facPara");
        settings.setValue("cardType", cardCombo->currentIndex());
        settings.endGroup();
        settings.endGroup();
*///应该等到加载成功才能更新参数

      }
    }
    else
    {
        QMessageBox::warning(w, QObject::tr("提示"),
                                QObject::tr("读取控制卡版本号失败，请检查与控制器通信连接是否正常！"),QObject::tr("确定"));
    }

    this->readCardTypeButton->setEnabled(true);
}

void CfacScreenProperty::udiskLoadParaProc()
{
  this->udiskLoadButton->setEnabled(false);
  loadParaProc(UDISK_MODE);
  this->udiskLoadButton->setEnabled(true);
}

void CfacScreenProperty::comLoadParaProc()
{
  this->comLoadButton->setEnabled(false);
  loadParaProc(COM_MODE);
  this->comLoadButton->setEnabled(true);

}

//加载参数
void CfacScreenProperty::loadParaProc(INT8U Mode)
{
    QString str;
    INT8U temp[100];
    int colorNum;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    str = w->screenArea->getCurrentScreenStr(); //当前屏幕str
    debug("loadpara:%s",(const char *)str.toLocal8Bit());

    settings.beginGroup(str);
    settings.beginGroup("facPara");

    int width = settings.value("width").toInt();
    int height = settings.value("height").toInt();
    int color = settings.value("color").toInt();
    int card = settings.value("cardType").toInt();
    settings.endGroup();   
    settings.endGroup();

    if(card != cardCombo->currentIndex()) //板卡类型发生了变化
    {
       mainObj->emitScreenChangeSignal();

       settings.beginGroup(str);
       settings.beginGroup("facPara");
       settings.setValue("cardType", cardCombo->currentIndex());
       settings.endGroup();
       settings.endGroup();
    }

    getScreenCardParaFromSettings(str, Screen_Para, Card_Para);//重新获取屏幕参数和板卡参数
    w->setActonsEnable();

    int index = getScreenIndex(str);
    QString screenName = QString::number(index) + QObject::tr("号屏幕");

    colorNum = colorCombo->currentIndex() + 1;

    if(!(widthEdit->value() > 0 &&\
         heightEdit->value() > 0 &&\
         widthEdit->value() % 8 == 0 &&\
         heightEdit->value() % 8 == 0))
    {
       QMessageBox::warning(w, QObject::tr("提示"),
                              QObject::tr("屏幕的长宽应必须大于0且为8的倍数，请重新设置！"),QObject::tr("确定"));
       //setSettingsToWidget(str);
       return;
    }

    if(Card_Para.Max_Points < (unsigned int)(widthEdit->value() * heightEdit->value()*colorNum))
    {
       QMessageBox::warning(w, QObject::tr("提示"),
                                screenName + QObject::tr("超出控制组件") + QObject::tr("最大支持点数：单色") + QString::number(Card_Para.Max_Points) +\
                                                                                   tr("，双色") + QString::number(Card_Para.Max_Points/2) + QObject::tr("，请重新设置!"),QObject::tr("确定"));

       setSettingsToWidget(str);
       return;
    }

    getSettingsFromWidget(str);
    getScreenCardParaFromSettings(str, Screen_Para, Card_Para);//重新获取屏幕参数和板卡参数

    //刷新当前屏幕的屏幕参数
    memcpy(&(w->screenArea->screenPara), &Screen_Para, sizeof(Screen_Para));

    //宽度、高度、颜色发生了修改则需要清掉所有的节目
    if(width != widthEdit->value() ||\
       height != heightEdit->value() ||\
       color != colorCombo->currentIndex())
    {
        if(paraFlag EQ MODI_SCN)
          QMessageBox::information(w, tr("提示"),
                                 tr("您此次修改了屏幕的宽度、高度、颜色之中的一项，这将导致该屏幕下的所有节目被重置！"),tr("确定"));


        //重新修改显示窗口大小
        QMdiSubWindow * subWin =w->mdiArea->currentSubWindow();
        w->screenArea->setFixedSize(widthEdit->value() * (w->screenArea->dotWidth + w->screenArea->spaceWidth), heightEdit->value() * (w->screenArea->dotWidth + w->screenArea->spaceWidth));

        for(int i = 0; i <MAX_AREA_NUM ;i ++)
          (*(w->screenArea->pArea[i])).screenPara.Base_Para.Color = Screen_Para.Base_Para.Color;

        subWin->setFixedSize(w->screenArea->width() + 14, w->screenArea->height() + 37);//subWin->sizeHint());
        //清除所有子项
        QTreeWidgetItem *screenItem = w->screenArea->screenItem;
        int count = screenItem->childCount();
        for(int i = 0; i < count; i ++)
        {
            w->progManage->clickItem(screenItem->child(0),0);
            w->progManage->treeWidget->setCurrentItem(screenItem->child(0));
            w->progManage->_deleteItem(1);
        }
        //w->screenArea->screenItem->removeChild(w->screenArea->screenItem->child(i));
        //w->progManage->settingsInit();
        memset(w->screenArea->showData.Color_Data, 0, sizeof(w->screenArea->showData.Color_Data));//清显示数据
        memset(&w->screenArea->progPara, 0, sizeof(w->screenArea->progPara));
        mainObj->emitScreenChangeSignal();
    }

    int flag = 0;
    SET_BIT(flag, C_SCREEN_PARA);
    //SET_BIT(flag, C_SCREEN_COM_PARA);
    //SET_BIT(flag, C_SCREEN_NET_PARA);
    //SET_BIT(flag, C_SCREEN_GPRS_PARA);
    //SET_BIT(flag, C_SCAN_PARA);
    //SET_BIT(flag, C_SCREEN_OC_TIME);

    if(QT_SIM_EN)
      makeProtoFileData(str, SIM_MODE, flag);
    else
      makeProtoFileData(str, Mode, flag);

    if(Mode EQ UDISK_MODE)
    {
        QMessageBox::information(w, QObject::tr("提示"),
                                w->comStatus->getComReStr(),QObject::tr("确定"));
    }
    else
    {
        int len;
        if(w->comStatus->waitComEnd(temp, sizeof(temp), &len))
        {
          QMessageBox::information(w, tr("提示"),
                                 tr(SEND_PARA_OK_STR),tr("确定"));
          //this->parentWidget()->close(); //参数设置成功则关闭窗口
        }
        else
        {
            QMessageBox::warning(w, tr("提示"),
                                   tr(SEND_PARA_FAIL_STR),tr("确定"));
        }
    }

    w->progManage->saveCurItem(w->screenArea->screenItem);
    w->setActonsEnable();

}

//设置进入检测状态
void CfacScreenProperty::setTestProc()
{
    char tmp;
    INT8U Temp[100];
    int len;
    QString screenStr;
    //char frameBuf[BLOCK_DATA_LEN + 20];

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    if(this->selfTestButton->text() EQ tr("自动检测"))
    {
        QMessageBox::information(w, tr("提示"),
                               tr("进入自动检测状态前请确定已加载正确的屏幕宽度、高度参数到屏幕，进入自检状态后，请观察屏幕左上角的显示内容（3分钟左右），如正常显示4位数字，则该4位数字作为特征码对应的扫描方式就是该屏幕正确的扫描方式，例如显示\"0200\"，则该屏幕的扫描方式为 \"0200,1/16扫,右入直行一路带16行数据(室内常规)\""),tr("确定"));
        //this->parentWidget()->close(); //参数设置成功则关闭窗口
      tmp = 0x00; //进入
      this->selfTestButton->setText(tr("退出检测"));
    }
    else
    {
        tmp = 0x01;
        this ->selfTestButton->setText(tr("自动检测"));
    }

    //len = makeFrame((char *)&tmp, sizeof(tmp), C_SELF_TEST | WR_CMD, frameInfo.seq++, frameBuf);

    screenStr = w->screenArea->getCurrentScreenStr();

    if(QT_SIM_EN)
      makeProtoBufData(screenStr, SIM_MODE, C_SELF_TEST | WR_CMD, &tmp, sizeof(tmp));
    else
      makeProtoBufData(screenStr, COM_MODE, C_SELF_TEST | WR_CMD, &tmp, sizeof(tmp));

    if(w->comStatus->waitComEnd(Temp, sizeof(Temp), &len))
    {
      QMessageBox::information(w, tr("提示"),
                             tr(SEND_PARA_OK_STR),tr("确定"));
      //this->parentWidget()->close(); //参数设置成功则关闭窗口
    }
    else
    {
        comFailedProc();
    }
}

/*
//发送参数
int CfacScreenProperty::sendPara()
{
    char frameBuf[BLOCK_DATA_LEN + 20];
    S_Screen_Para screenPara;
    S_Card_Para cardPara;
    int len;

    QString str = w->screenArea->getCurrentScreenStr();

    getScreenCardParaFromSettings(str, screenPara, cardPara); //
    //基本参数
    len = Make_Frame((INT8U *)&screenPara.Base_Para, sizeof(screenPara.Base_Para),\
               (INT8U *)&screenPara.COM_Para.Addr, C_SCREEN_BASE_PARA, 0, 0, 0, frameBuf);

    if(QT_SIM_EN)
      sendProtoData(frameBuf, len, SIM_MODE); //仿真模式
    else
      sendProtoData(frameBuf, len, COM_MODE);

    //扫描参数
    len = Make_Frame((INT8U *)&screenPara.Scan_Para, sizeof(screenPara.Scan_Para),\
               (INT8U *)&screenPara.COM_Para.Addr, C_SCAN_PARA, 0, 0, 0, frameBuf);

    if(QT_SIM_EN)
      sendProtoData(frameBuf, len, SIM_MODE); //仿真模式
    else
      sendProtoData(frameBuf, len, COM_MODE);
}
*/
void CfacScreenProperty::defParaCheckProc()
{
  if(defParaCheck->checkState()) //选中
  {
    freqCombo->setCurrentIndex(0);
    //lineHideCombo->setCurrentIndex(0);
    dataMirrorCombo->setCurrentIndex(0);
    lineOrderCombo->setCurrentIndex(0);
    _138Combo->setCurrentIndex(0);

    //当前在
    //int scanModeIndex =
    if(getScanModeIndex(200) EQ scanModeCombo->currentIndex())
    {
      freqCombo->setCurrentIndex(0); //最快速度扫描
      lineHideCombo->setCurrentIndex(0); //消隐时间最短
    }
    else// if(getScanModeIndex(2213) EQ scanModeCombo->currentIndex())
    {
      freqCombo->setCurrentIndex(2); //降低扫描速度
      lineHideCombo->setCurrentIndex(2); //拉长消隐时间
    }

    freqCombo->setEnabled(false);
    //lineHideCombo->setEnabled(false);
    dataMirrorCombo->setEnabled(false);
    lineOrderCombo->setEnabled(false);
    _138Combo->setEnabled(false);

    freqLabel->setEnabled(false);
    //lineHideLabel->setEnabled(false);
    dataMirrorLabel->setEnabled(false);
    lineOrderLabel->setEnabled(false);
    _138Label->setEnabled(false);

    lineHideCombo->setEnabled(false);
    lineHideLabel->setEnabled(false);
  }
  else
  {
      freqCombo->setEnabled(true);
      //lineHideCombo->setEnabled(true);
      dataMirrorCombo->setEnabled(true);
      lineOrderCombo->setEnabled(true);
      _138Combo->setEnabled(true);

      freqLabel->setEnabled(true);
      //lineHideLabel->setEnabled(true);
      dataMirrorLabel->setEnabled(true);
      lineOrderLabel->setEnabled(true);
      _138Label->setEnabled(true);

      lineHideCombo->setEnabled(true);
      lineHideLabel->setEnabled(true);
  }
}

void CfacScreenProperty::cardChangeProc()
{
    //S_Card_Para cardPara;
    S_Card_Para cardPara_Bak;

    memcpy(&cardPara_Bak, &Card_Para, sizeof(Card_Para));

    cardParaEdit->clear();

    getCardParaFromSettings(cardCombo->currentText(), Card_Para);
    QString pointsStr = tr("最大点数：单色") + QString::number(Card_Para.Max_Points) +\
                          tr("，双色") + QString::number(Card_Para.Max_Points/2);

    if(Card_Para.Flag & 0x01) //支持全彩
      pointsStr += tr("，全彩") + QString::number(Card_Para.Max_Points/3);

    //pointsStr += tr("，最大高度：") + QString::number(Card_Para.Max_Height);
    //cardParaEdit->setText(pointsStr);

    pointsStr += tr("。最大分区数：") + QString::number(Card_Para.Max_Area_Num);
    cardParaEdit->setText(pointsStr);

    QString fileStr = tr("支持：") +\
    ((Get_Border_Show_En()>0)?tr("边框"):tr("")) +\
    ((Get_Pic_Show_En()>0)?tr("、字幕、文本、表格、图片、动画"):tr("")) +\
    ((Get_Clock_Show_En()>0)?tr("、表盘"):tr("")) +\
    ((Get_Lun_Show_En()>0)?tr("、农历"):tr(""))+\
    ((Get_Time_Show_En()>0)?tr("、时间"):tr(""))+\
    ((Get_Timer_Show_En()>0)?tr("、计时"):tr(""))+\
    ((Get_Temp_Show_En()>0)?tr("、温度"):tr(""))+\
    ((Get_Humidity_Show_En()>0)?tr("、湿度"):tr(""))+\
    ((Get_Noise_Show_En()>0)?tr("、噪音"):tr(""));

    cardParaEdit->append(fileStr);

    QString modeStr = tr("引入特效：") + QString::number(Card_Para.InMode_Num) +\
                      tr("，引出特效：") + QString::number(Card_Para.OutMode_Num);
    cardParaEdit->append(modeStr);

    QString comStr = tr("通信方式：") +\
                     (((Card_Para.Com_Mode & COM_RS232)>0)?tr("串口"):tr("")) +\
                     (((Card_Para.Com_Mode & COM_UDISK)>0)?tr("、U盘"):tr("")) +\
                     (((Card_Para.Com_Mode & COM_ETH)>0)?tr("、以太网"):tr("")) +\
                     (((Card_Para.Com_Mode & COM_SMS)>0)?tr("、短信"):tr("")) +\
                     (((Card_Para.Com_Mode & COM_GPRS)>0)?tr("、GPRS"):tr(""));


    if(Card_Para.Com_Mode & COM_ETH)
    {
        if(tabWidget->indexOf(netParaGroup) < 0)
          tabWidget->insertTab(4, netParaGroup, tr("网络参数"));
        //tabWidget->removeTab(tabWidget->indexOf(netParaGroup));
        //tabWidget->removeTab(tabWidget->indexOf(readParaGroup));
    }
    else
    {
        if(tabWidget->indexOf(netParaGroup) > 0)
          tabWidget->removeTab(tabWidget->indexOf(netParaGroup));
        //tabWidget->removeTab(tabWidget->indexOf(readParaGroup));
    }
    cardParaEdit->append(comStr);
    memcpy(&Card_Para, &cardPara_Bak, sizeof(Card_Para));

    if(this->comTest)
      this->comTest->cardChangedProc(cardCombo->currentText());

}

void CfacScreenProperty::endProc()
{

}

CsetFacPara::CsetFacPara(QWidget *parent):QMainWindow(parent)
{
    facScreenProperty = new CfacScreenProperty(MODI_SCN, 0, this);
    this->setCentralWidget(facScreenProperty);
    this->setWindowTitle(tr("设置屏幕参数"));

}

CsetFacPara::~CsetFacPara()
{

}

//screen属性编辑
CupdateFirmwareDialog::CupdateFirmwareDialog(INT8U flag, QWidget *parent):QDialog(parent)
{

    QVBoxLayout *mainLayout;
    QGroupBox *readVersionGroup;
    QGroupBox *updateFirmGroup;
    QGridLayout *gLayout;

    readVersionGroup = new QGroupBox(tr("查询控制器程序"), this);
    updateFirmGroup = new QGroupBox(tr("升级控制器程序"), this);

    mainLayout = new QVBoxLayout(this);

/*
    QLineEdit *oldVersionEdit; //老的程序版本
    QLineEdit *newVersionEdit; //新升级的程序版本

    QLineEdit *newFirmPath; //新固件路径
    QPushButton *updateButton; //固件升级命令
    QPushButton *readVersionButton; //读取版本号命令
 */
    gLayout = new QGridLayout(readVersionGroup);
    QLabel *versionLabel = new QLabel(tr("版本号"), readVersionGroup);
    oldVersionEdit = new QLineEdit(readVersionGroup);
    readVersionButton = new QPushButton(tr("查询"), this);
    gLayout->addWidget(versionLabel, 1, 1,1,1);
    gLayout->addWidget(oldVersionEdit,1,2,1,10);
    gLayout->addWidget(readVersionButton,1,12,1,1);
    readVersionGroup->setLayout(gLayout);

    gLayout = new QGridLayout(updateFirmGroup);
    QLabel *firmNameLabel = new QLabel(tr("程序名"), updateFirmGroup);
    newFirmPath = new QLineEdit(updateFirmGroup);
    openButton = new QPushButton(tr("打开"), this);
    makeButton = new QPushButton(tr("生成"), this);

    QLabel *firmVersionLabel = new QLabel(tr("版本号"), updateFirmGroup);
    newVersionEdit = new QLineEdit(updateFirmGroup);
    updateButton = new QPushButton(tr("升级"), updateFirmGroup);
    gLayout ->addWidget(firmNameLabel, 1,1,1,1);
    gLayout ->addWidget(newFirmPath, 1,2,1,10);
    gLayout ->addWidget(openButton, 1,12,1,1);
    gLayout->addWidget(firmVersionLabel, 2,1,1,1);
    gLayout->addWidget(newVersionEdit, 2,2,1,10);
    gLayout->addWidget(updateButton, 2,12,1,1);
    gLayout->addWidget(makeButton, 3,12,1,1);

    oldVersionEdit->setFocusPolicy(Qt::NoFocus);
    newVersionEdit->setFocusPolicy(Qt::NoFocus);
    if(makeFlag EQ 0) //用于生成文件时，版本号是可输入的，用于写入fwb文件中
      newFirmPath->setFocusPolicy(Qt::NoFocus);

    mainLayout->addWidget(readVersionGroup);
    mainLayout->addWidget(updateFirmGroup);

    this->setLayout(mainLayout);
    this->setFixedWidth(500);
    this->setWindowTitle(tr("固件升级"));

    if(flag EQ 0)
    {
      makeButton->setVisible(false);
      makeFlag = 0;
    }
    else
      makeFlag = 1;

    newFirmFrameCounts = 0;

    updateButton->setEnabled(false);
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFirmwareFile()));
    connect(makeButton, SIGNAL(clicked()), this, SLOT(makeFirmwareFile()));
    connect(updateButton, SIGNAL(clicked()), this, SLOT(updateFirmware()));
    connect(readVersionButton, SIGNAL(clicked()), this, SLOT(readVersion()));
}

void CupdateFirmwareDialog::updateFirmware()
{
    INT8U Temp[100];
    int len;
    bool re;


    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    QString screenStr = w->screenArea->getCurrentScreenStr();

    this->setEnabled(false);

    if(readVersion() == false) //没有读取到版本号
    {
        this->setEnabled(true);
        return;

    }

    //比较两个版本是否相同
    int equFlag = 0;

    for(int i = 0; i < oldVersionEdit->text().size() && i < newVersionEdit->text().size(); i ++)
    {
      if(oldVersionEdit->text().at(i) == ' ' && newVersionEdit->text().at(i) == ' ') //第一个空格
      {
         equFlag = 1;
         break;
      }
      else if(oldVersionEdit->text().at(i) != newVersionEdit->text().at(i))
      {
          equFlag = 0;
          break;
      }
    }

    if(equFlag EQ 0)
    {
        QMessageBox::warning(w, tr("提示"),
                               tr("固件和控制器版本不兼容，请选择正确的固件程序升级！"),tr("确定"));

        this->setEnabled(true);
        return;
    }

    //读取前一版本的版本号
    INT8U flag = 0x02; //维护标志02表示控制器进入固件升级状态
    makeProtoBufData(screenStr, COM_MODE, C_SELF_TEST | WR_CMD, (char *)&flag, sizeof(flag));

    re = w->comStatus->waitComEnd(Temp, sizeof(Temp), &len);
    if(re EQ false)
    {
        QMessageBox::warning(w, tr("提示"),
                               tr("固件升级失败，请检查与控制器通信连接是否正常！"),tr("确定"));

        this->setEnabled(true);
        return;
    }

    if(newFirmFrameCounts > 0)
    {
      w->comStatus->setTotalFrameCounts(newFirmFrameCounts);
      w->comStatus->getCOMParaFromSettings(screenStr); //获取通信参数

      Delay_ms(500);

      w->comStatus->sendProtoFile(newFirmPath->text());

      re = w->comStatus->waitComEnd(Temp, sizeof(Temp), &len);
      if(re EQ true)
      {
        QMessageBox::information(w, tr("提示"),
                               tr("固件升级成功！"),tr("确定"));
        //close(); //校时成功则关闭--不关闭，可能需要升级很多板

      }
      else
      {
        QMessageBox::warning(w, tr("提示"),
                               tr("固件升级失败，请检查与控制器通信连接是否正常！"),tr("确定"));
      }
    }

    this->setEnabled(true);
}

bool CupdateFirmwareDialog::readVersion()
{
    QString screenStr = w->screenArea->getCurrentScreenStr();
    INT8U rcvBuf[500] = {0};
    bool re;
    int len;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return 0;

    //读取前一版本的版本号
    makeProtoBufData(screenStr, COM_MODE, C_SOFT_VERSION | RD_CMD, (char *)0, 0);

    re = w->comStatus->waitComEnd(rcvBuf, sizeof(rcvBuf), &len);
    if(re EQ true)
    {
       oldVersionEdit->setText(QString((char *)rcvBuf));
    }
    else
    {
        QMessageBox::warning(w, tr("提示"),
                               tr("查询控制器版本号失败，请检查与控制器通信连接是否正常！"),tr("确定"));

    }

    return re;
}

void CupdateFirmwareDialog::openFirmwareFile()
{
    QString newFileName;
    FILE *fwbFile;
    int len;
    //INT16U addr;

    if(makeFlag)
    {
      newFileName = QFileDialog::getOpenFileName(this, tr("打开固件文件"), WORKDIR(), tr("二进制文件(*.bin)"));
      if(newFileName.length()==0)
      {
          return;
      }

      newFirmPath->setText(newFileName);
      return;
    }
    else
    {
      newFileName = QFileDialog::getOpenFileName(this, tr("打开固件文件"), WORKDIR(), tr("固件(*.fwb)"));

      if(newFileName.length()==0)
          return;

      newFirmPath->setText(newFileName);

      fwbFile = fopen(newFirmPath->text().toLocal8Bit(), "rb");

      fseek(fwbFile, 0, SEEK_END);
      len = ftell(fwbFile);

      fseek(fwbFile, 0, SEEK_SET);

      memset(fwbFileData, 0, sizeof(fwbFileData));

      len = fread(fwbFileData, 1, len, fwbFile); //读取整个文件内容!!
      fclose(fwbFile);

      if(Check_Frame_Format((INT8U *)fwbFileData, VERSION_FRAME_DATA_LEN + F_NDATA_LEN) == 0)
      {
          updateButton->setEnabled(false);

          QMessageBox::warning(w, tr("提示"),
                                 tr("这不是一个合法的固件升级文件！"),tr("确定"));
          return;
      }
      INT32U sum;
      //校验和
      OS_Set_Sum(fwbFileData + VERSION_FRAME_DATA_LEN + F_NDATA_LEN, len - VERSION_FRAME_DATA_LEN - F_NDATA_LEN,\
                 &sum, 4, &sum, sizeof(sum));



      if(memcmp(&sum, fwbFileData + FDATA + VERSION_FRAME_SUM_OFF, 4) != 0)
      {
          updateButton->setEnabled(false);

          QMessageBox::warning(w, tr("提示"),
                                 tr("这不是一个合法的固件升级文件！"),tr("确定"));
          return;
      }

      newVersionEdit->setText(QString(QByteArray(fwbFileData + FDATA)));
      memcpy(&newFirmFrameCounts, fwbFileData + FDATA + VERSION_FRAME_FCOUNTS_OFF, 2); //帧个数

      updateButton->setEnabled(true);
    }




}
/*
#define WIDEN2(x,y, z) "Line " #y " of file" x z
#define WIDEN(x,y,z) WIDEN2(x , y, z)
#define __WFILE__ WIDEN( __FILE__ , __LINE__ , __DATE__)
*/
//多字符串连接,好办法
/*
#define _CON(X,Y,Z) X Y #Z
#define CON(X,Y,Z) _CON(X,Y,Z)
*/
//生成固件文件

void CupdateFirmwareDialog::makeFirmwareFile()
{
  FILE *binFile,*fwbFile;
  INT8U seq = 0;
  INT16U addr;
  unsigned int len, frameDataLen, frameLen;
  unsigned int i = 0;
  char frameBuf[FIRMWARE_FRAME_DATA_LEN + 100];
  char version[VERSION_FRAME_DATA_LEN + 100] = {0};
  char endFlag = 0;
  INT16U fCounts = 0;
  //char a[] = CON(__DATE__ , __TIME__, __LINE__);

  if(newFirmPath->text() == "")
      return;

  binFile = fopen(newFirmPath->text().toLocal8Bit(), "rb");
  if(binFile EQ (FILE *)0)
  {
      ASSERT_FAILED();
      return;
  }

  fseek(binFile, 0, SEEK_END);

  len = ftell(binFile); //获取文件长度

  fseek(binFile, 0, SEEK_SET); //定位到文件起始处
  len = fread(binFileData, 1, len, binFile);
  fclose(binFile);

  endFlag = 0;
  seq = 1; //第0帧后面生成
  int fileOff = VERSION_FRAME_DATA_LEN + F_NDATA_LEN; //整个版本号帧的长度

  if(len) //生成fwb文件
  {
      //先获取版本号
      while(i < sizeof(version) - 1 && binFileData[VERSION_OFF + i] != 0)
      {
         version[i] = binFileData[VERSION_OFF + i];
         i++;
      }

      newVersionEdit->setText(QString(QByteArray(version)));

      addr = 0x9999;
      i = 0;
      while(i < len)
      {
          if(i + FIRMWARE_FRAME_DATA_LEN < len)
          {
             frameDataLen = FIRMWARE_FRAME_DATA_LEN;
             endFlag = 0;
         }
          else
          {
             frameDataLen = len - i;
             endFlag = 0xA5;
          }

          //memcpy(frameBuf + FDATA, &len, 4); //文件长度，4字节
          memcpy(frameBuf + FDATA, &i, 4); //内部偏移，4字节
          memcpy(frameBuf + FDATA + 4, &endFlag, 1); //最有一帧标志,0xA5

          memcpy(frameBuf + FDATA + 5, binFileData + i, frameDataLen); //为真正数据
          //对数据进行简单加密
          for(unsigned int j = 0; j < frameDataLen; j ++)
             frameBuf[FDATA + 5 + j] = (frameBuf[FDATA + 5 + j] ^ 0x55) + 0x33;

          //生成CRC校验
          OS_Set_Sum(frameBuf + FDATA, frameDataLen + 5, frameBuf + FDATA + frameDataLen + 5, 2, frameBuf, sizeof(frameBuf));

          frameLen = _makeFrame(frameBuf + FDATA, frameDataLen + 7, addr, C_UPDATE | WR_CMD, 0, 0, seq++, frameBuf);
          i += frameDataLen;

          //fwrite(frameBuf, 1, frameLen, fwbFile);
          //fclose(fwbFile);
          memcpy(fwbFileData + fileOff, frameBuf, frameLen);
          fileOff += frameLen;

          fCounts++;
      }

      //第一帧只用于发送版本信息以及整体校验,以及整个bin文件长度
      //将整个fwb文件(不包含第一帧，因为此时第一帧还没生成)的校验写入第一帧中, 数据域的第30个字节中
      OS_Set_Sum(fwbFileData + VERSION_FRAME_DATA_LEN + F_NDATA_LEN, fileOff - VERSION_FRAME_DATA_LEN - F_NDATA_LEN,  version + VERSION_FRAME_SUM_OFF, 4, version, sizeof(version)); //将版本号记录到version中

      //总的帧数
      fCounts ++; //增加帧个数
      memcpy(version + VERSION_FRAME_FCOUNTS_OFF, &fCounts, 2);
      memcpy(version + VERSION_FRAME_BINSIZE_OFF, &len, 4); //4个字节的bin文件长度

      //将第一帧本身的校验写入数据域的组后两个字节
      OS_Set_Sum(version, VERSION_FRAME_DATA_LEN - 2, version + VERSION_FRAME_DATA_LEN - 2, 2, version, sizeof(version));
      //生成第一帧
      frameLen = _makeFrame(version, VERSION_FRAME_DATA_LEN, addr, C_UPDATE | WR_CMD, 0, 0, 0, fwbFileData);

      QString outputFwbFile = newFirmPath->text() + QString(".fwb");
      fwbFile = fopen(outputFwbFile.toLocal8Bit(), "wb+");
      fseek(fwbFile, 0, SEEK_SET); //前50字节用于记录版本号、校验和等程序信息

      fwrite(fwbFileData, fileOff, 1, fwbFile);
      fclose(fwbFile);
  }

}

CupdateFirmwareDialog::~CupdateFirmwareDialog()
{

}


CInvalidDateDialog::CInvalidDateDialog(QWidget *parent):QDialog(parent)
{
  QHBoxLayout *hLayout;
  QGridLayout *gLayout;

  invalidDateGroup = new QGroupBox(this);
  invalidDateGroup->setTitle(tr("启用锁定时间"));
  invalidDateGroup->setCheckable(true);

  invalidDateEdit = new QDateEdit(this);
  hLayout = new QHBoxLayout(invalidDateGroup);
  hLayout->addWidget(invalidDateEdit);
  invalidDateGroup->setLayout(hLayout);

  sendButton = new QPushButton(tr("发送参数"),this);
  udiskButton = new QPushButton(tr("导出U盘参数"), this);

  gLayout = new QGridLayout(this);
  gLayout->addWidget(invalidDateGroup, 0, 0, 1, 2);
  gLayout->addWidget(sendButton,1,0,1,1);
  gLayout->addWidget(udiskButton, 1,1,1,1);

  this->setLayout(gLayout);
  this->setWindowTitle(tr("屏幕锁定时间设置"));

  QString str = w->screenArea->getCurrentScreenStr();
  setSettingsToWidget(str);

  connect(sendButton, SIGNAL(clicked()), this, SLOT(sendPara()));
  connect(udiskButton, SIGNAL(clicked()), this, SLOT(udiskPara()));

  connect(invalidDateGroup, SIGNAL(clicked()), this, SLOT(editSlot()));
  connect(invalidDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(editSlot()));
}

void CInvalidDateDialog::sendPara()
{
    //char frameBuf[BLOCK_DATA_LEN + 20];
    //S_Screen_Para screenPara;
    //S_Card_Para cardPara;
    INT8U temp[100];
    int len;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    QString str = w->screenArea->getCurrentScreenStr();

    this->sendButton->setEnabled(false);

    int flag = 0;
    SET_BIT(flag, C_SCREEN_LOCK_DATE);
    if(QT_SIM_EN)
      makeProtoFileData(str, SIM_MODE, flag);
    else
      makeProtoFileData(str, COM_MODE, flag);

    if(w->comStatus->waitComEnd(temp, sizeof(temp), &len))
    {
        QMessageBox::information(w, tr("提示"),
                               tr(SEND_PARA_OK_STR),tr("确定"));
        close(); //校时成功则关闭
    }
    else
    {
        comFailedProc();
    }

    this->sendButton->setEnabled(true);
}
/*
//锁定时间
settings.beginGroup("validTime");

if(settings.value("validTimeFlag").toBool())
    screenPara.Lock_Date.Lock_Date_Flag = LOCK_DATE_FLAG;
else
    screenPara.Lock_Date.Lock_Date_Flag = 0;

screenPara.Lock_Date.Time[0] = (INT8U)settings.value("date").toInt();
screenPara.Lock_Date.Time[1] = (INT8U)settings.value("month").toInt();
screenPara.Lock_Date.Time[2] = (INT8U)settings.value("year").toInt();

settings.endGroup();
*/
void CInvalidDateDialog::getSettingsFromWidget(QString str)
{
  settings.beginGroup(str);
  settings.beginGroup("validTime");

  settings.setValue("validTimeFlag", invalidDateGroup->isChecked());

  settings.setValue("date", invalidDateEdit->date().day());
  settings.setValue("month", invalidDateEdit->date().month());
  settings.setValue("year", invalidDateEdit->date().year());
  //debug("get year = %d", invalidDateEdit->date().year());
  settings.endGroup();
  settings.endGroup();
}

void CInvalidDateDialog::setSettingsToWidget(QString str)
{
    int year,month,day;
    QDate date;

    disconnect(invalidDateGroup, SIGNAL(clicked()), this, SLOT(editSlot()));
    disconnect(invalidDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(editSlot()));

    settings.beginGroup(str);
    settings.beginGroup("validTime");

    //settings.setValue("validTimeFlag", invalidDateGroup->isChecked());
    invalidDateGroup->setChecked(settings.value("validTimeFlag").toBool());

    year = settings.value("year").toInt();
    month = settings.value("month").toInt();
    day = settings.value("date").toInt();
    date.setDate(year, month, day);

    invalidDateEdit->setDate(date);
    //debug("set year = %d", settings.value("year").toInt());
    settings.endGroup();
    settings.endGroup();

    connect(invalidDateGroup, SIGNAL(clicked()), this, SLOT(editSlot()));
    connect(invalidDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(editSlot()));
}

void CInvalidDateDialog::editSlot()
{
    QString screenStr;

    screenStr = w->screenArea->getCurrentScreenStr();

    getSettingsFromWidget(screenStr);
}

void CInvalidDateDialog::udiskPara()
{
    //S_Screen_Para screenPara;
    //S_Card_Para cardPara;
    //INT8U temp[100];
    //int len;

    if(w->comStatus->comThread->isRunning())//当前线程还在运行
        return;

    QString str = w->screenArea->getCurrentScreenStr();

    this->udiskButton->setEnabled(false);

    int flag = 0;
    SET_BIT(flag, C_SCREEN_LOCK_DATE);

    makeProtoFileData(str, UDISK_MODE, flag);

    //U盘模式下不需要等待waitComEnd，因为没有通信返回数据需要等待
    if(w->comStatus->getComStatus() == COM_OK) //通信成功的情况下关闭
    {
        QMessageBox::information(w, QObject::tr("提示"),
                                w->comStatus->getComReStr(),QObject::tr("确定"));
        close();
    }
    else
    {
        QMessageBox::warning(w, QObject::tr("提示"),
                                w->comStatus->getComReStr(),QObject::tr("确定"));
    }

    this->udiskButton->setEnabled(true);
}

CInvalidDateDialog::~CInvalidDateDialog()
{

}

//生成一个临时的Mac地址
void Make_Rand_Mac_Para(INT8U Mac[])
{
    INT8U rand;

    rand = qrand() % 256;
    QDateTime dateTime = QDateTime::currentDateTime();

    Mac[0] = dateTime.time().second() + (rand << 6);
    Mac[1] = dateTime.time().minute() + (rand << 6);
    Mac[2] = dateTime.time().hour() + (rand << 5);
    Mac[3] = dateTime.date().day() + (rand << 5);
    Mac[4] = ((dateTime.date().year() - 2010) << 4) + dateTime.date().month();
    Mac[5] = (INT8U)rand;
}
