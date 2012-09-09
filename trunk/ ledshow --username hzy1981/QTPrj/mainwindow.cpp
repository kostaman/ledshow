#include <QObject>
#include "mainwindow.h"
#include "progProperty.h"
#include "progManage.h"
#include "makeProto.h"
#include "..\Stm32\usr\app\Includes.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QApplication>
#include <QUrl>

extern MainWindow *w;

QString rsrcPath1 =  ":/images/win1";
QString rsrcPath = ":/images/win";

//��Ŀ�����ļ�
QSettings settings(PROG_INI_FILE,QSettings::IniFormat,0);


#define QT_MOVE_STEP_TIMER MOVE_STEP_PERIOD //����ʱ��ʱ���

#if QT_MOVE_STEP_TIMER > MOVE_STEP_PERIOD
#error "QT_MOVE_STEP_TIMER error"
#endif

int stepTimer = 0;

QString getItemStr(QTreeWidgetItem *item)
{
    return item->data(0,Qt::UserRole).toString();
}
/*
class MainObj:public QObject
{
  Q_OBJECT
signals:
    screenChange();
public:
    MainObj(QObject *parent = 0);
    ~MainObj();
};
*/
MainObj::MainObj(QObject *parent):QObject(parent)
{

}

void MainObj::emitScreenChangeSignal()
{
    emit this->screenChange();
}

MainObj::~MainObj()
{

}

void MainWindow::setupFileActions()
{
    //QToolBar *tb = new QToolBar(this);
    //tb->setWindowTitle(tr("File Actions"));
    //addToolBar(tb);

    QMenu *menu = new QMenu(tr("�ļ�"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    a = new QAction(tr("�½�����"), this);
    //a->setPriority(QAction::LowPriority);
    ////a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    //tb->addAction(a);
    menu->addAction(a);

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("�򿪹���"), this);
    //a->setPriority(QAction::LowPriority);
    ////a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    //tb->addAction(a);
    menu->addAction(a);
/*
    a = new QAction(tr("����"), this);
    //a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSave()));
    //tb->addAction(a);
    menu->addAction(a);
*/
    a = new QAction(tr("�������Ϊ"), this);
    ////a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
    //tb->addAction(a);
    menu->addAction(a);

    menu->addSeparator();

    a = new QAction(tr("�˳�"), this);
    //a->setPriority(QAction::LowPriority);
    connect(a, SIGNAL(triggered()), this, SLOT(close()));
    menu->addAction(a);

}

void MainWindow::setupViewActions()
{
    //QToolBar *tb = new QToolBar(this);
    //tb->setWindowTitle(tr("File Actions"));
    //addToolBar(tb);

    QMenu *menu = new QMenu(tr("��ͼ"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("״̬��"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("���ƴ���"), this);
    //a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("���Դ���"), this);
    //a->setShortcut(QKeySequence::Save);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileSave()));
    //tb->addAction(a);
    menu->addAction(a);
}


QIcon getTypeIcon(INT8U type)
{
  QIcon icon;
  if(type EQ SCREEN_PROPERTY)
      icon = QIcon::fromTheme(QObject::tr("��Ļ"), QIcon(rsrcPath1 + QObject::tr("/��Ļ.png")));
  else if(type EQ PROG_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("��Ŀ"), QIcon(rsrcPath1 + QObject::tr("/��Ŀ.png")));
  else if(type EQ AREA_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("����"), QIcon(rsrcPath1 + QObject::tr("/����.png")));
  else if(type EQ PIC_STEXT_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("��Ļ"), QIcon(rsrcPath1 + QObject::tr("/��Ļ.png")));
  else if(type EQ PIC_MTEXT_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("�ı�"), QIcon(rsrcPath1 + QObject::tr("/ͼ��.png")));
  else if(type EQ PIC_TABLE_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("���"), QIcon(rsrcPath1 + QObject::tr("/���.png")));
  else if(type EQ PIC_FLASH_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("����"), QIcon(rsrcPath1 + QObject::tr("/����.png")));
  else if(type EQ PIC_IMAGE_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("ͼƬ"), QIcon(rsrcPath1 + QObject::tr("/ͼƬ.png")));
  else if(type EQ CLOCK_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("����"), QIcon(rsrcPath1 + QObject::tr("/����.png")));
  else if(type EQ TIME_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("ʱ��"), QIcon(rsrcPath1 + QObject::tr("/����.png")));
  else if(type EQ TIMER_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("��ʱ"), QIcon(rsrcPath1 + QObject::tr("/��ʱ.png")));
  else if(type EQ LUN_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("ũ��"), QIcon(rsrcPath1 + QObject::tr("/ũ��.png")));
  else if(type EQ TEMP_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("�¶�"), QIcon(rsrcPath1 + QObject::tr("/�¶�.png")));
  else if(type EQ HUMIDITY_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("ʪ��"), QIcon(rsrcPath1 + QObject::tr("/ʪ��.png")));
  else if(type EQ NOISE_PROPERTY)
     icon = QIcon::fromTheme(QObject::tr("����"), QIcon(rsrcPath1 + QObject::tr("/����.png")));

  return icon;
}

void MainWindow::setupEditActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("���"), this);
    menuBar()->addMenu(menu);

    QAction *a;
/*
    QAction *actionScreen;
    QAction *actionProg;
    QAction *actionArea;
    QAction *actionSText;
    QAction *actionMText;
    QAction *actionTemp;
    QAction *actionHumidi;
    QAction *actionFlash;
    QAction *actionClock;
    QAction *actionTime;
    QAction *actionNoise;
    QAction *actionNongli;
    QAction *actionTimer;
 */
    QIcon screenIcon = getTypeIcon(SCREEN_PROPERTY);//QIcon::fromTheme(tr("��Ļ"), QIcon(rsrcPath1 + tr("/��Ļ.png")));
    actionScreen = a = new QAction(screenIcon, tr("��Ļ"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newScreen())); //�½���Ŀ
    //tb->addAction(a);

    menu->addAction(a);
    menu->addSeparator();

    QIcon progIcon = getTypeIcon(PROG_PROPERTY);//QIcon::fromTheme("��Ŀ", QIcon(rsrcPath1 + tr("/��Ŀ22.png")));
    actionProg = a = new QAction(progIcon, tr("��Ŀ"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newProg())); //�½���Ŀ
    tb->addAction(a);

    menu->addAction(a);
    menu->addSeparator();
    tb->addSeparator();

    QIcon areaIcon = getTypeIcon(AREA_PROPERTY);//QIcon::fromTheme(tr("����"), QIcon(rsrcPath1 + tr("/����.png")));
    actionArea = a = new QAction(areaIcon, tr("����"), this);
    a->setIconText(tr("����"));
    //a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newArea())); //�½�����
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();
    tb->addSeparator();

    QIcon stextIcon = getTypeIcon(PIC_STEXT_PROPERTY);//QIcon::fromTheme(tr("��Ļ"), QIcon(rsrcPath1 + tr("/��Ļ.ico")));
    actionSText = a = new QAction(stextIcon, tr("��Ļ"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled(true);//(bool)Get_Pic_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newSText())); //�½���Ŀ
    tb->addAction(a);
    menu->addAction(a);

    QIcon mtextIcon = getTypeIcon(PIC_MTEXT_PROPERTY);//QIcon::fromTheme(tr("�ı�"), QIcon(rsrcPath1 + tr("/ͼ��22.png")));
    actionMText = a = new QAction(mtextIcon, tr("�ı�"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Pic_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newPic())); //�½���Ŀ
    tb->addAction(a);
    menu->addAction(a);

    QIcon tableIcon = getTypeIcon(PIC_TABLE_PROPERTY);//QIcon::fromTheme(tr("�ı�"), QIcon(rsrcPath1 + tr("/ͼ��22.png")));
    actionTable = a = new QAction(tableIcon, tr("���"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Pic_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTable())); //�½���Ŀ
    tb->addAction(a);
    menu->addAction(a);

    QIcon flashIcon = getTypeIcon(PIC_FLASH_PROPERTY);//QIcon::fromTheme(tr("����"), QIcon(rsrcPath1 + tr("/����.ico")));
    actionFlash = a = new QAction(flashIcon, tr("����"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Pic_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newFlash()));
    tb->addAction(a);
    menu->addAction(a);

    QIcon imageIcon = getTypeIcon(PIC_IMAGE_PROPERTY);//QIcon::fromTheme(tr("����"), QIcon(rsrcPath1 + tr("/����.ico")));
    actionImage = a = new QAction(imageIcon, tr("ͼƬ"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Pic_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newImage()));
    tb->addAction(a);
    menu->addAction(a);

    QIcon clockIcon = getTypeIcon(CLOCK_PROPERTY);//QIcon::fromTheme(tr("����"), QIcon(rsrcPath1 + tr("/����.ico")));
    actionClock = a = new QAction(clockIcon, tr("����"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Clock_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newClock()));
    tb->addAction(a);
    menu->addAction(a);

    QIcon timeIcon = getTypeIcon(TIME_PROPERTY);//QIcon::fromTheme(tr("ʱ��"), QIcon(rsrcPath1 + tr("/����22.png")));
    actionTime = a = new QAction(timeIcon, tr("ʱ��"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Time_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTime()));
    tb->addAction(a);
    menu->addAction(a);

    QIcon lunIcon = getTypeIcon(LUN_PROPERTY);//QIcon::fromTheme(tr("ũ��"), QIcon(rsrcPath1 + tr("/ũ��22.png")));
    actionNongli = a = new QAction(lunIcon, tr("ũ��"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Lun_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newLun()));
    tb->addAction(a);
    menu->addAction(a);

    QIcon timerIcon = getTypeIcon(TIMER_PROPERTY);//QIcon::fromTheme(tr("��ʱ"), QIcon(rsrcPath1 + tr("/��ʱ.png")));
    actionTimer = a = new QAction(timerIcon, tr("��ʱ"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Timer_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTimer()));
    tb->addAction(a);
    menu->addAction(a);

    QIcon tempIcon = getTypeIcon(TEMP_PROPERTY);//QIcon::fromTheme(tr("�¶�"), QIcon(rsrcPath1 + tr("/�¶�22.png")));
    actionTemp = a = new QAction(tempIcon, tr("�¶�"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Temp_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTemp()));
    tb->addAction(a);
    menu->addAction(a);

    QIcon humidityIcon = getTypeIcon(HUMIDITY_PROPERTY);//QIcon::fromTheme(tr("ʪ��"), QIcon(rsrcPath1 + tr("/ʪ��.png")));
    actionHumidi = a = new QAction(humidityIcon, tr("ʪ��"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Humidity_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newHumidity()));
    tb->addAction(a);
    menu->addAction(a);

    QIcon noiseIcon = getTypeIcon(NOISE_PROPERTY);//QIcon::fromTheme(tr("ʪ��"), QIcon(rsrcPath1 + tr("/����.ico")));
    actionNoise = a = new QAction(noiseIcon, tr("����"), this);
    //a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Humidity_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newNoise()));
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();
    tb->addSeparator();

    QIcon delIcon = QIcon::fromTheme(tr("ɾ��"), QIcon(rsrcPath1 + tr("/ɾ��.png")));
    actionDel = a = new QAction(delIcon, tr("ɾ��"), this);
    //a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), progManage, SLOT(deleteItem())); //ɾ����Ŀ
    tb->addAction(a);
    menu->addAction(a);
}

void MainWindow::actionEnProc(int Type)
{
  if(Type EQ NULL_PROPERTY)
  {
    property->setEnabled(false);
    ctrlMenu->setEnabled(false);
    actionPreview->setEnabled(false);
    actionModiScreenPara->setEnabled(false);
    actionUpdateFirmware->setEnabled(false);
    actionUDisk->setEnabled(false);
    actionSendData->setEnabled(false);
    actionAdjTime->setEnabled(false);
    actionLightness->setEnabled(false);
    actionOpenClose->setEnabled(false);
    actionPreview->setEnabled(false);
    actionScreenPreiew->setEnabled(false);

    actionScreen->setEnabled(true);
    actionProg->setEnabled(false);
    actionArea->setEnabled(false);
    actionSText->setEnabled(false);
    actionMText->setEnabled(false);
    actionTable->setEnabled(false);
    actionTemp->setEnabled(false);
    actionHumidi->setEnabled(false);
    actionFlash->setEnabled(false);
    actionImage->setEnabled(false);
    actionClock->setEnabled(false);
    actionTime->setEnabled(false);
    actionNoise->setEnabled(false);
    actionNongli->setEnabled(false);
    actionTimer->setEnabled(false);
    actionDel->setEnabled(false);


  }
  else if(Type EQ SCREEN_PROPERTY)
  {
      property->setEnabled(true);
      ctrlMenu->setEnabled(true);
      actionPreview->setEnabled(false);
      actionModiScreenPara->setEnabled(true);
      actionUpdateFirmware->setEnabled(true);
      actionUDisk->setEnabled(true);
      actionSendData->setEnabled(true);
      actionAdjTime->setEnabled(true);
      actionLightness->setEnabled(true);
      actionOpenClose->setEnabled(true);
      actionPreview->setEnabled(false);
      actionScreenPreiew->setEnabled(true);

      actionScreen->setEnabled(true);
      actionProg->setEnabled(true);
      actionArea->setEnabled(false);
      actionSText->setEnabled(false);
      actionMText->setEnabled(false);
      actionTable->setEnabled(false);
      actionTemp->setEnabled(false);
      actionHumidi->setEnabled(false);
      actionFlash->setEnabled(false);
      actionImage->setEnabled(false);
      actionClock->setEnabled(false);
      actionTime->setEnabled(false);
      actionNoise->setEnabled(false);
      actionNongli->setEnabled(false);
      actionTimer->setEnabled(false);
      actionDel->setEnabled(true);
  }
  else if(Type EQ PROG_PROPERTY)
  {
      property->setEnabled(true);
      ctrlMenu->setEnabled(true);
      actionPreview->setEnabled(true);
      actionModiScreenPara->setEnabled(true);
      actionUpdateFirmware->setEnabled(true);
      actionUDisk->setEnabled(true);
      actionSendData->setEnabled(true);
      actionAdjTime->setEnabled(true);
      actionLightness->setEnabled(true);
      actionOpenClose->setEnabled(true);
      actionPreview->setEnabled(true);
      actionScreenPreiew->setEnabled(true);

      actionScreen->setEnabled(true);
      actionProg->setEnabled(true);
      actionArea->setEnabled(true);
      actionSText->setEnabled(false);
      actionMText->setEnabled(false);
      actionTable->setEnabled(false);
      actionTemp->setEnabled(false);
      actionHumidi->setEnabled(false);
      actionFlash->setEnabled(false);
      actionImage->setEnabled(false);
      actionClock->setEnabled(false);
      actionTime->setEnabled(false);
      actionNoise->setEnabled(false);
      actionNongli->setEnabled(false);
      actionTimer->setEnabled(false);
      actionDel->setEnabled(true);
  }
  else if(Type EQ AREA_PROPERTY)
  {
      property->setEnabled(true);
      ctrlMenu->setEnabled(true);
      actionPreview->setEnabled(true);
      actionModiScreenPara->setEnabled(true);
      actionUpdateFirmware->setEnabled(true);
      actionUDisk->setEnabled(true);
      actionSendData->setEnabled(true);
      actionAdjTime->setEnabled(true);
      actionLightness->setEnabled(true);
      actionOpenClose->setEnabled(true);
      actionPreview->setEnabled(true);
      actionScreenPreiew->setEnabled(true);

      actionScreen->setEnabled(true);
      actionProg->setEnabled(true);
      actionArea->setEnabled(true);
      actionSText->setEnabled(true);
      actionMText->setEnabled(true);
      actionTable->setEnabled(true);
      actionTemp->setEnabled(true);
      actionHumidi->setEnabled(true);
      actionFlash->setEnabled(true);
      actionImage->setEnabled(true);
      actionClock->setEnabled(true);
      actionTime->setEnabled(true);
      actionNoise->setEnabled(true);
      actionNongli->setEnabled(true);
      actionTimer->setEnabled(true);
      actionDel->setEnabled(true);
  }
  else
  {
      property->setEnabled(true);
      ctrlMenu->setEnabled(true);
      actionPreview->setEnabled(true);
      actionModiScreenPara->setEnabled(true);
      actionUpdateFirmware->setEnabled(true);
      actionUDisk->setEnabled(true);
      actionSendData->setEnabled(true);
      actionAdjTime->setEnabled(true);
      actionLightness->setEnabled(true);
      actionOpenClose->setEnabled(true);
      actionPreview->setEnabled(true);
      actionScreenPreiew->setEnabled(true);

      actionScreen->setEnabled(true);
      actionProg->setEnabled(true);
      actionArea->setEnabled(true);
      actionSText->setEnabled(true);
      actionMText->setEnabled(true);
      actionTable->setEnabled(true);
      actionTemp->setEnabled(true);
      actionHumidi->setEnabled(true);
      actionFlash->setEnabled(true);
      actionImage->setEnabled(true);
      actionClock->setEnabled(true);
      actionTime->setEnabled(true);
      actionNoise->setEnabled(true);
      actionNongli->setEnabled(true);
      actionTimer->setEnabled(true);
      actionDel->setEnabled(true);
  }
}

void MainWindow::setupCtrlActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("����"), this);
    ctrlMenu = menu;//���Ʋ˵�
    menuBar()->addMenu(menu);
    menu->setEnabled(false);

    QAction *a;

    actionModiScreenPara = a = new QAction(tr("�޸���Ļ����"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(modifyScreenPara()));
    //tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();

    actionUpdateFirmware = a = new QAction(tr("�̼�����"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(updateFirmware()));
    //tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();

    //QAction *actionManualClose; //�ֶ��ػ�
    //QAction *actionManualOpen; //�ֶ�����
    //QAction *atcionGetOCStatus; //��ȡ���ػ�״̬
    actionManualClose = a = new QAction(tr("�ֶ��ػ�"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(setManualClose()));
    //tb->addAction(a);
    menu->addAction(a);

    actionManualOpen = a = new QAction(tr("�ֶ�����"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(setManualOpen()));
    //tb->addAction(a);
    menu->addAction(a);

    actionOpenClose = a = new QAction(tr("��ʱ���ػ�"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(setOpenCloseTime()));
    //tb->addAction(a);
    menu->addAction(a);

    actionLightness = a = new QAction(tr("��������"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(setLightness()));
    //tb->addAction(a);
    menu->addAction(a);


    QIcon adjTimeIcon = QIcon::fromTheme(tr("Уʱ"), QIcon(rsrcPath1 + tr("/Уʱ.png")));
    actionAdjTime = a = new QAction(adjTimeIcon, tr("Уʱ"), this);
    //a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(adjTime()));
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();
    tb->addSeparator();

    QIcon sendIcon = QIcon::fromTheme(tr("��������"), QIcon(rsrcPath1 + tr("/����.png")));
    actionSendData = a = new QAction(sendIcon, tr("��������"), this);
    //a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(sendDataProc()));
    tb->addAction(a);
    menu->addAction(a);

    QIcon udiskIcon = QIcon::fromTheme(tr("����U��"), QIcon(rsrcPath1 + tr("/��U��.png")));
    actionUDisk = a = new QAction(udiskIcon, tr("����U���ļ�"), this);
    //a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(exportUdsikProc()));
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();
    tb->addSeparator();

    //QIcon udiskIcon = QIcon::fromTheme(tr("��ʾͨ��״̬"), QIcon(rsrcPath1 + tr("/��U��22.png")));
    actionComStatus = a = new QAction(tr("��ʾͨ��״̬"), this);
    a->setCheckable(true);
    connect(a, SIGNAL(triggered()), this, SLOT(comStatusShow()));
    //tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();

    QIcon previewIcon = QIcon::fromTheme("��ĿԤ��", QIcon(rsrcPath1 + tr("/Ԥ��.png")));
    actionPreview = a = new QAction(previewIcon, tr("��ĿԤ��"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(previewProg()));
    tb->addAction(a);
    menu->addAction(a);

    //QIcon previewIcon = QIcon::fromTheme("Ԥ��", QIcon(rsrcPath1 + tr("/Ԥ��2222.png")));
    actionScreenPreiew = a = new QAction(tr("��ĻԤ��"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(previewScreen()));
    menu->addAction(a);

    actionTestCard = a = new QAction(tr("�������"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(testCard()));
    tb->addAction(a);
}

void MainWindow::setupToolActions()
{
    //QToolBar *tb = new QToolBar(this);
    //tb->setWindowTitle(tr("File Actions"));
    //addToolBar(tb);

    QMenu *menu = new QMenu(tr("����"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("��ͼ��"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("������"), this);
    //a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("���±�"), this);
    //a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    //tb->addAction(a);
    menu->addAction(a);
}

void MainWindow::setupLanguageActions()
{
    //QToolBar *tb = new QToolBar(this);
    //tb->setWindowTitle(tr("File Actions"));
    //addToolBar(tb);

    QMenu *menu = new QMenu(tr("����"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("��������"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    //tb->addAction(a);
    menu->addAction(a);

}

void MainWindow::setupHelpActions()
{
    //QToolBar *tb = new QToolBar(this);
    //tb->setWindowTitle(tr("File Actions"));
    //addToolBar(tb);

    QMenu *menu = new QMenu(tr("����"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("����"), this);
    a->setPriority(QAction::LowPriority);
    //a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("����"), this);
    //a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(helpFileOpen()));
    //tb->addAction(a);
    menu->addAction(a);
}
/*
void MainWindow::createProgTreeArea()
{
    QDockWidget *dock0 = new QDockWidget(tr("prog"),this);
    //QDockWidget *dock1 = new QDockWidget(tr("area"),this);

    dock0->setAllowedAreas(Qt::LeftDockWidgetArea);
    //dock1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    treeView = new QTreeView(dock0);
    //listView = new QListView(dock1);

    dock0->setWidget(treeView);
    //dock1->setWidget(listView);
}
*/
//���õ�ǰ��ȫ�ֽ�Ŀ���������ļ�setting str
void MainWindow::setCurSettingsStr(QString str)
{
    curSettingsStr = str;
}

//��ȡ��ǰ��ȫ�ֽ�Ŀ���������ļ�setting str
QString MainWindow::getCurSettingsStr()
{
    return curSettingsStr;
}

//�ļ�����
void MainWindow::fileSave()
{
    QString fileName;

    settings.beginGroup("");
    fileName = settings.value("cfgFile").toString(); //�����ļ���
    settings.endGroup();

    QFile::copy(PROG_INI_FILE, fileName); //�����ϵ��ļ�
}

//�ļ����Ϊ
void MainWindow::fileSaveAs()
{

    //QString fileName;
    QString newFileName;

    newFileName = QFileDialog::getSaveFileName(this, tr("���湤���ļ�"), ".", tr("�����ļ�(*.ini)"));
    if(newFileName.length()==0)
        return;

    if(QFile::exists(newFileName)) //�ļ�����
    {
      if(QFile::remove(newFileName) == false) //ɾ��ʧ��
        {
          QMessageBox::warning(w, tr("��ʾ"),
                                   tr("�ļ��滻ʧ�ܣ���ȷ�ϸ��ļ��Ƿ���������ռ��") + newFileName, tr("ȷ��"));
          return;
      }

    }

    if(QFile::copy(PROG_INI_FILE, newFileName) == false) //�����ϵ��ļ�
    {
        QMessageBox::warning(w, tr("��ʾ"),
                                 tr("�����ļ�����ʧ��"), tr("ȷ��"));
   }

}

//�½��ļ�
void MainWindow::fileNew()
{
    if(progManage->treeWidget->topLevelItemCount() > 0)
    {
        int Re =  QMessageBox::warning(w, tr("��ʾ"),
                                 tr("��ǰ�༭���ݽ��ᱻ����ؽ���"), tr("���浱ǰ�������½�"),tr("������ֱ���½�"),tr("ȡ��"));

        if(Re EQ 0)
        {
            fileSaveAs();
            //return;
        }
        else if(Re EQ 2)
        {
            return;
        }
    }

    int count = progManage->treeWidget->topLevelItemCount();
    for(int i = 0; i < count; i ++)
    {
        QTreeWidgetItem *item = progManage->treeWidget->topLevelItem(0);
        progManage->treeWidget->setCurrentItem(item);
        progManage->_deleteItem(0);

    }

    settings.clear();//clear(); //���

    //settings.beginGroup("file");
    //settings.setValue("cfgFile", newFileName);
    //settings.endGroup();

    //screenArea->screenSettingsInit();
    progManage->settingsInit();
    //progManage->newScreen();
    //progManage->newProg();
    //progManage->newArea();
    QMessageBox::warning(w, tr("��ʾ"), tr("�����½��ɹ��������˵�\"���-��Ļ\"�½�һ����Ļ��"), tr("ȷ��"));


}

void MainWindow::showAboutDialog()
{
    QMessageBox::information(w, tr("����"), tr("LED���ʦ 2012\r\n\r\n\r\n����ʱ��  ")+QString(__TIME__) + QString(" ") + QString(__DATE__), tr("ȷ��"));

}

void MainWindow::helpFileOpen() //�򿪰����ļ�
{
    QString strUrl=QApplication::applicationDirPath () ;
    strUrl=QString("file:///%1/mainhelp.chm").arg (strUrl);
    QUrl qqq(strUrl);
    QDesktopServices::openUrl(qqq);


  //QDesktopServices::openUrl(QUrl("file:///C:/Documents and Settings/All Users/Desktop", QUrl::TolerantMode));
}

//���ļ�
void MainWindow::fileOpen()
{
    QString newFileName;
    QString oldFileName;

    if(progManage->treeWidget->topLevelItemCount() > 0)
    {
        int Re =  QMessageBox::warning(w, tr("��ʾ"),
                                 tr("��ǰ�༭���ݽ��ᱻ�����"), tr("���浱ǰ�����ٴ�"),tr("������ֱ�Ӵ�"),tr("ȡ��"));

        if(Re EQ 0)
        {
            fileSaveAs();
            //return;
        }
        else if(Re EQ 2)
        {
            return;
        }
    }
/*
    settings.beginGroup("file");
    oldFileName = settings.value("cfgFile").toString(); //�����ļ���
    settings.endGroup();
    QFile::remove(oldFileName);
    if(QFile::copy(PROG_INI_FILE, oldFileName)==false) //�����ϵ��ļ�
    {
        ASSERT_FAILED();
    }
*/
    int count = progManage->treeWidget->topLevelItemCount();
    for(int i = 0; i < count; i ++)
    {
        QTreeWidgetItem *item = progManage->treeWidget->topLevelItem(0);
        progManage->treeWidget->setCurrentItem(item);
        progManage->_deleteItem(0);

    }

    settings.clear();//clear(); //���

    newFileName = QFileDialog::getOpenFileName(this, tr("�򿪹����ļ�"), ".", tr("�����ļ�(*.ini)"));
    if(newFileName.length()==0)
    {
        return;
    }


    QSettings tempSettings(newFileName,QSettings::IniFormat,0);
    QStringList list = tempSettings.allKeys();
    int num = list.size();

    for(int i = 0; i < num; i ++)
    {
        settings.setValue(list.at(i), tempSettings.value(list.at(i)));
    }


    settings.beginGroup("file");
    settings.setValue("cfgFile", newFileName);
    settings.endGroup();

    //settings.setPath(QSettings::IniFormat, QSettings::UserScope, PROG_INI_FILE);

    progManage->settingsInit();
}

void MainWindow::settingsInit()
{/*
    QStringList str;

    settings.beginGroup("screen");
    str = settings.allKeys();
    //if(str.isEmpty() == true)
    {
        int xLen = 256;
        int yLen = 256;
        int color = 0x02;

        settings.setValue("width", xLen);
        settings.setValue("height", yLen);
        settings.setValue("color", color);
    }
    settings.endGroup();
    //color =
   //progManage->settingsInit();
*/
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //property->progProperty->getSettingsFromWidget();
}

void MainWindow::updateTreeWidget(QMdiSubWindow *subWin)
{

    //subWin->childAt()
  QList<QMdiSubWindow *> subWinList;

  subWinList = mdiArea->subWindowList(); //�Ӵ���ָ���б�
  int num = subWinList.size(); //�Ӵ��ڸ���
  for(int i = 0; i < num; i ++)
  {
    if(subWin EQ subWinList.at(i))
    {
       if(progManage->treeWidget->topLevelItemCount() > i)
       {
          qDebug("update screen %d",i);
          MDISubWinClickFlag = 1;
          //progManage->clickItem(progManage->treeWidget->topLevelItem(i),0);
          if(w->screenArea->screenItem != progManage->treeWidget->topLevelItem(i))
            progManage->treeWidget->setCurrentItem(progManage->treeWidget->topLevelItem(i));
       }
    }
  }


//progManage->clickItem(((CscreenArea *)(subWin->widget()))->screenItem,0);

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    settingsInit();
    //QGridLayout *gridLayout;
    setToolButtonStyle(Qt::ToolButtonFollowStyle);

    mdiArea = new QMdiArea(this);
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    property = new Cproperty(this);
    progManage = new CprogManage(this);
    comStatus = new CcomStatus(this);

    comStatus->hide(); //����������
    /*
    widget = new QWidget(this);
    widget->setAutoFillBackground(true);
    QPalette *palette;
    palette = new QPalette();
    palette->setColor(QPalette::Background, QColor(Qt::white));
    widget->setPalette(*palette);
*/
    //screenArea =  new CscreenArea;//CshowArea(this, 1);

    addDockWidget(Qt::LeftDockWidgetArea, progManage);
    addDockWidget(Qt::BottomDockWidgetArea, property);
    addDockWidget(Qt::RightDockWidgetArea, comStatus);

    setupFileActions();
    //setupViewActions();
    setupEditActions();
    setupCtrlActions();
    setupLanguageActions();
    setupHelpActions();



    /*
    gridLayout ->addWidget(progMange, 0, 0);//,0,0,2,2);
    gridLayout ->addWidget(showArea, 0, 1);
    gridLayout ->addWidget(property, 1, 0);
    //area = new CareaProperty(this);
    //gridLayout ->addWidget(area, 1, 0);//,0,0,2,2);

    //sArea = new showArea(this);
    //gridLayout ->addWidget(sArea, 0, 1);
    */
    //setCentralWidget(widget);
//screenArea->newShowArea();
    //setLayout(gridLayout);
   setCentralWidget(mdiArea);
   MDISubWinClickFlag = 0;

   previewWin = new CpreviewWin(this);//new QMainWindow(w);
   previewArea =  new CscreenArea(previewWin);
   previewWin->setCentralWidget(previewArea);

   //QHBoxLayout *hLayout = new QHBoxLayout(previewWin);
   //hLayout->addWidget(previewArea);
   //hLayout->setSizeConstraint(QLayout::SetFixedSize);
   //previewWin->setLayout(hLayout);

   //initComStatus(); //ͨ��״̬��ʼ��

   timer = new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(previewProc()));

   mmtimer = new MMTimer(QT_MOVE_STEP_TIMER, this);
   connect(mmtimer, SIGNAL(timeout()), this, SLOT(previewProc()));

   setWindowTitle(tr(APP_NAME));
}

void MainWindow::screenCardParaChangeProc()
{
  this->property->screenCardParaChangeProc();
}

MainWindow::~MainWindow()
{

}

QMdiSubWindow *getSubWinByIndex(QMdiArea *parentArea, int index)
{
  QList<QMdiSubWindow *> subWinList;

  subWinList = parentArea->subWindowList();
  if(subWinList.size() > index)
  {
    return subWinList.at(index);
  }
  else
  {
    ASSERT_FAILED();
    return (QMdiSubWindow *)0;
  }
}

//����-1��ʾû���������
int getIndexBySubWin(QMdiArea *parentArea, QMdiSubWindow *subWin)
{
    QList<QMdiSubWindow *> subWinList;

    subWinList = parentArea->subWindowList();
    for(int i = 0; i < subWinList.size();i ++)
    {
        if(subWinList.at(i) == subWin)
         return i;
    }

    ASSERT_FAILED();
    return -1;

}

//�޸ĵ�ǰ��Ļ����
void MainWindow::modifyScreenPara()
{
  QString str;
  INT8U Re;

  Re = verifyPSW();
  if(Re EQ 0)
      return;

  str = w->screenArea->getCurrentScreenStr(); //��ǰ��Ļstr

  if(Re EQ 1 || Re EQ 2)
  {
      QDialog *facParaWin = new QDialog(this);
      QHBoxLayout *hLayout = new QHBoxLayout(facParaWin);

      facParaWin->setWindowTitle(tr("�޸���Ļ����"));
      CfacScreenProperty *facScreenProperty = new CfacScreenProperty(MODI_SCN, facParaWin);
      CcomTest *comTest = new CcomTest(facParaWin);

      facScreenProperty->setSettingsToWidget(str);
      comTest->setSettingsToWidget(str);

      hLayout->addWidget(facScreenProperty);
      hLayout->addWidget(comTest);

      facParaWin->setLayout(hLayout);
      facParaWin->setAttribute(Qt::WA_DeleteOnClose);
      connect(facScreenProperty->endButton, SIGNAL(clicked()), facParaWin, SLOT(close()));
      facParaWin->exec();
  }
  else if(Re EQ 3)
  {
    CInvalidDateDialog *invalidDateDialog = new CInvalidDateDialog(this);
    invalidDateDialog->exec();
  }

}

//�̼�����
void MainWindow::updateFirmware()
{
  INT8U re, flag;

  re = verifyPSW();
  if(re EQ 0)
    return;

  if(re EQ 4) //������4��������ʾ�����ļ��İ�ť,�ڲ�ʹ��
      flag = 1;
  else
      flag = 0;

  CupdateFirmwareDialog *updateFirmwareDialog = new CupdateFirmwareDialog(flag, this);
  updateFirmwareDialog->exec();
}

//��������
void MainWindow::setLightness()
{
  ClightnessDialog *lightnessDialog = new ClightnessDialog(this);
  QString str = w->screenArea->getCurrentScreenStr();
  lightnessDialog->setSettingsToWidget(str);

  lightnessDialog->exec();
}

//У׼ʱ��
void MainWindow::adjTime()
{
  CadjTimeDialog *adjTimeDialog = new CadjTimeDialog(this);
  adjTimeDialog->exec();
}

//���ÿ��ػ�ʱ��
void MainWindow::setOpenCloseTime()
{
    CopenCloseDialog *openCloseDialog = new CopenCloseDialog(this);
    QString str = w->screenArea->getCurrentScreenStr();
    openCloseDialog->setSettingsToWidget(str);

    openCloseDialog->exec();
}

//�ֶ��ػ�
void MainWindow::setManualClose()
{
    char Flag;
    INT8U Temp[100];
    int len;

    if(w->comStatus->comThread->isRunning())//��ǰ�̻߳�������
        return;

    QString screenStr = w->screenArea->getCurrentScreenStr();

    Flag = CLOSE_FLAG;
#if QT_SIM_EN
    makeProtoBufData(screenStr, SIM_MODE, C_SCREEN_OC | WR_CMD, &Flag, 1);
#else
    makeProtoBufData(screenStr, COM_MODE, C_SCREEN_OC | WR_CMD, &Flag, 1);
#endif

    bool re = w->comStatus->waitComEnd(Temp, sizeof(Temp), &len);
    if(re EQ true)
    {
        QMessageBox::information(w,QObject::tr("��ʾ"),
                               QObject::tr(SEND_PARA_OK_STR),QObject::tr("ȷ��"));
        //close(); //Уʱ�ɹ���ر�

    }
    else
    {
        QMessageBox::warning(w, QObject::tr("��ʾ"),
                               QObject::tr(SEND_PARA_FAIL_STR),QObject::tr("ȷ��"));
    }
}

//�ֶ�����
void MainWindow::setManualOpen()
{
    char Flag;
    INT8U Temp[100];
    int len;

    if(w->comStatus->comThread->isRunning())//��ǰ�̻߳�������
        return;

    QString screenStr = w->screenArea->getCurrentScreenStr();

    Flag = 0;
#if QT_SIM_EN
    makeProtoBufData(screenStr, SIM_MODE, C_SCREEN_OC | WR_CMD, &Flag, 1);
#else
    makeProtoBufData(screenStr, COM_MODE, C_SCREEN_OC | WR_CMD, &Flag, 1);
#endif

    bool re = w->comStatus->waitComEnd(Temp, sizeof(Temp), &len);
    if(re EQ true)
    {
        QMessageBox::information(w,QObject::tr("��ʾ"),
                               QObject::tr(SEND_PARA_OK_STR),QObject::tr("ȷ��"));
        //close(); //Уʱ�ɹ���ر�

    }
    else
    {
        QMessageBox::warning(w, QObject::tr("��ʾ"),
                               QObject::tr(SEND_PARA_FAIL_STR),QObject::tr("ȷ��"));
    }
}

void MainWindow::sendDataProc()
{
   CsendDataDialog *sendDataDialog = new CsendDataDialog(0, this);
   sendDataDialog->exec();
}

void MainWindow::exportUdsikProc()
{
    CsendDataDialog *sendDataDialog = new CsendDataDialog(1, this);
    sendDataDialog->exec();
}

//Ԥ����ǰ��Ŀ
void MainWindow::previewProg()
{
  preview(PREVIEW_PROG);
}

//Ԥ����ǰ��Ļ�µ����н�Ŀ
void MainWindow::previewScreen()
{
  preview(PREVIEW_SCREEN);
}

//Ԥ��ͳһ����
void MainWindow::preview(INT8U previewMode)
{
  QString screenStr;//progStr;
  INT8U Screen_No,re;


  if(w->comStatus->comThread->isRunning())//��ǰ�̻߳�������
      return;

  //���ɷ����ļ�
  Mem_Open();

  screenStr = getItemStr(screenArea->screenItem);

  Screen_No = progManage->treeWidget->indexOfTopLevelItem(screenArea->screenItem);
  if(screenArea->screenItem->childCount() EQ 0)
  {
      if(previewMode EQ PREVIEW_PROG)
          QMessageBox::information(w, tr("��ʾ"),
                               tr("����ѡ��һ��Ԥ���Ľ�Ŀ"),tr("ȷ��"));
      else
          QMessageBox::warning(w, tr("��ʾ"),
                                   tr("����Ļ��û�н�Ŀ!"),tr("ȷ��"));
      return;
  }

  Ram_Init();

#if QT_SIM_EN
  re = makeProtoFileData(screenStr, SIM_MODE, 0xFFFFFFFF);
#else
  re = makeProtoFileData(screenStr, PREVIEW_MODE, 0xFFFFFFFF);
#endif

  if(re EQ 0)
      return;

  Preview_Prog_No = screenArea->screenItem->indexOfChild(screenArea->progItem);
  Preview_Mode = previewMode;
  //setCentralWidget(mdiArea);
  //CMdiSubWindow *subWin = new CMdiSubWindow;
  //subWin->previewFlag = 1; //���ڷ�����Ӵ���
  timerFlag = 0;
  stepTimer = 0;

  //previewWin = new CpreviewWin(w);//new QMainWindow(w);
 if(QT_SIM_EN EQ 0)
   previewWin->setWindowModality(Qt::WindowModal);

/*
  previewArea =  new CscreenArea(previewWin);
  previewArea->setWindowModality(Qt::WindowModal);
  */

  //previewArea->setGeometry(0,0,Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height); //resize(Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);
  //previewArea->setFixedSize(previewArea->size());
  previewArea->setFixedSize(Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);
  //previewWin->resize(Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);
  previewWin->setFixedSize(previewWin->sizeHint());
  //previewArea->setFixedSize(Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);
  //previewWin->setFixedSize(previewWin->sizeHint());

  previewArea->previewFlag = 1;
  //previewArea->updateFlag = true;

  //previewWin->setAttribute(Qt::WA_DeleteOnClose);

  QString title = tr("Ԥ��-")+QString::number(Screen_No + 1) + tr("��Ļ");
  if(Preview_Mode EQ PREVIEW_PROG)
      title = title + QString("-") + QString::number(Preview_Prog_No + 1) + tr("��Ŀ");
  previewWin->move((width() - previewArea->width())/2, (height() - previewArea->height())/2);

  previewWin->setWindowTitle(title);

  Para_Init(); //��ʾ��ʼ����

  memcpy(&previewArea->screenPara, &Screen_Para, sizeof(Screen_Para));
  previewWin->show();
  //previewWin->setFixedSize(previewWin->size());


  timer->stop();
  timer->start(QT_MOVE_STEP_TIMER);

  //mmtimer->start();
}

void MainWindow::comStatusShow()
{
  if(actionComStatus->isChecked()==true)
      comStatus->show();
  else
      comStatus->hide();
}

void MainWindow::previewTimerProc()
{
    Show_Timer_Proc();

    previewArea->previewFlag = 1;//Ԥ������
    //previewArea->updateFlag = 1;
    memcpy(previewArea->showData.Color_Data, Show_Data.Color_Data, sizeof(Show_Data.Color_Data));
    TRACE();
    previewArea->update(); //ˢ����ʾ����
    TRACE();
}

void MainWindow::previewProc()
{
  static INT32U msCounts = 0;

  //mmtimer->stop();

  msCounts += QT_MOVE_STEP_TIMER;
  stepTimer += QT_MOVE_STEP_TIMER;

  Get_Cur_Time();
  Pub_Timer.Ms = msCounts;
  Pub_Timer.Ms100 = msCounts / 100;
  Pub_Timer.Sec = Cur_Time.Time[T_SEC]; //��ʱ������

  Calc_Screen_Color_Num(); //���¼�����Ļ��ɫ�������������ط����޸�

  Show_Main_Proc();
  Show_Main_Proc();
  Show_Main_Proc();

  if(stepTimer >= MOVE_STEP_PERIOD)
  {
      stepTimer = 0;
      previewTimerProc();
  }

  //mmtimer->start();
}

void MainWindow::testCard()
{
  INT8U dataBuf[10];
  INT8U Temp[20];
  int len;

  loop:
  QDateTime dateTime = QDateTime::currentDateTime(); //��ǰʱ��s

  dataBuf[T_YEAR] = dateTime.date().year() - 2000;
  dataBuf[T_MONTH] = dateTime.date().month();
  dataBuf[T_DATE] = dateTime.date().day();
  dataBuf[T_WEEK] = dateTime.date().dayOfWeek();
  if(dataBuf[T_WEEK] EQ 7)
      dataBuf[T_WEEK] = 0;
  dataBuf[T_HOUR] = dateTime.time().hour();
  dataBuf[T_MIN] = dateTime.time().minute();
  dataBuf[T_SEC] = dateTime.time().second();

  QString screenStr = w->screenArea->getCurrentScreenStr();

  //����ϵͳУʱ����
  makeProtoBufData(screenStr, COM_MODE, C_SCREEN_TIME | WR_CMD, (char *)dataBuf, 7);

  bool re = w->comStatus->waitComEnd(Temp, sizeof(Temp), &len);
  if(re EQ false)
  {
      QMessageBox::critical(w, tr("��ʾ"),
                             tr("���ƿ��Լ�ʧ��:����ϵͳʱ��ʧ��"),tr("ȷ��"));
      return;

  }

  //����Ӳ���Լ�����
    dataBuf[0] = 0x03; //����Ӳ���Լ�

    makeProtoBufData(screenStr, COM_MODE, C_SELF_TEST | WR_CMD, (char *)dataBuf, 1);

    re = w->comStatus->waitComEnd(Temp, sizeof(Temp), &len);
    if(re EQ false)
    {
        QMessageBox::critical(w, tr("��ʾ"),
                             tr("���ƿ��Լ�ʧ��:û���յ�Ӳ���Լ�����Ӧ��!"),tr("ȷ��"));
        return;
    }
    else if(len > 0 && Temp[FDATA] > 0)
    {
        QString reStr ="";

        if(GET_BIT(Temp[0], 0))
            reStr += tr(",���ݴ洢���Լ�ʧ��");

        if(GET_BIT(Temp[0], 1))
            reStr += tr(",ʱ���Լ�ʧ��");

        if(GET_BIT(Temp[0], 2))
            reStr += tr(",���������Լ�ʧ��");

        QMessageBox::critical(w, tr("��ʾ"),
                             tr("���ƿ��Լ�ʧ��:") + reStr,tr("ȷ��"));
        return;
    }

    //���ͼ�������
      dataBuf[0] = 0x05; //����

      makeProtoBufData(screenStr, COM_MODE, C_SELF_TEST | WR_CMD, (char *)dataBuf, 1);

      re = w->comStatus->waitComEnd(Temp, sizeof(Temp), &len);
      if(re EQ false)
      {
          QMessageBox::critical(w, tr("��ʾ"),
                                 tr("���ƿ��Լ�ʧ��:���������ʧ��!"),tr("ȷ��"));
          return;

      }

    Delay_ms(500); //��ʱ�ȿ�������λ
    //���ͽӿ��Լ�����
    dataBuf[0] = 0x04; //����ɨ��ӿ��Լ�

    makeProtoBufData(screenStr, COM_MODE, C_SELF_TEST | WR_CMD, (char *)dataBuf, 1);

    re = w->comStatus->waitComEnd(Temp, sizeof(Temp), &len);
    if(re EQ false)
    {
      QMessageBox::critical(w, tr("��ʾ"),
                             tr("���ƿ��Լ�ʧ��:���ͽӿ��Լ�����ʧ��"),tr("ȷ��"));
      return;

    }
    else
    {
       re = QMessageBox::information(w, tr("��ʾ"),
                               tr("������ӿڽ�����ʾ��Ļ���۲���Ļ��ʾ�Ƿ���ȷ������ʾ��ȷ������ƿ��Լ�ɹ�!"),tr("������һ�����"), tr("�˳��������"));

       if(re EQ 0)
           goto loop;
       else
       {
           //���͸�λ����
             dataBuf[0] = 0x01; //��λ

             makeProtoBufData(screenStr, COM_MODE, C_SELF_TEST | WR_CMD, (char *)dataBuf, 1);

         }
   }
}

void traversalControl(const QObjectList& q)
{
   for(int i=0;i<q.length();i++)
    {
        if(!q.at(i)->children().empty())
        {
           traversalControl(q.at(i)->children());
        }
        else
        {

            QObject* o = q.at(i);
            if(o->inherits("QComboBox"))
            {
              QComboBox* b = qobject_cast<QComboBox *>(o);
              b->clear();//setText("<>");
            }
        }
    }
}

CinputPSWDialog::CinputPSWDialog(INT8U *re, QWidget *parent):QDialog(parent)
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    QHBoxLayout *hLayout = new QHBoxLayout(this);

    verifyRe = re;
    *verifyRe = false;

    QLabel *pswLabel = new QLabel(tr("����������"), this);
    lineEdit = new QLineEdit(this);
    lineEdit->setEchoMode(QLineEdit::Password);
    hLayout->addWidget(pswLabel);
    hLayout->addWidget(lineEdit);
    vLayout->addLayout(hLayout);

    reLabel = new QLabel(" ", this);
    vLayout->addWidget(reLabel);

    hLayout = new QHBoxLayout(this);
    okButton = new QPushButton(tr("ȷ��"), this);
    cancelButton = new QPushButton(tr("ȡ��"), this);
    hLayout->addStretch(1);
    hLayout->addWidget(okButton);
    hLayout->addWidget(cancelButton);

    vLayout->addLayout(hLayout);
    setLayout(vLayout);

    this->setWindowTitle(tr("������֤"));
    setAttribute(Qt::WA_DeleteOnClose);

    connect(okButton, SIGNAL(clicked()), this, SLOT(okClickProc()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

void CinputPSWDialog::okClickProc()
{
   if(lineEdit->text() == "888")//1������
    {
       *verifyRe = 1;
      close();
   }
   else if(lineEdit->text() == "168")//2������
   {
       *verifyRe = 2;
       close();
   }
   else if(lineEdit->text() == "112233")
   {
       *verifyRe = 3;
       close();
   }
   else if(lineEdit->text() =="445566") //��߼�����
   {
       *verifyRe = 4;
       close();
   }
   else
   {
       reLabel->setText(tr("�������!"));
       *verifyRe = 0;
   }
}

CinputPSWDialog::~CinputPSWDialog()
{

}


INT8U verifyPSW()
{/*

    bool ok;
    QString text = CinputPSWDialog::getText(0, QObject::tr("������֤"),
                                            QObject::tr("����������:"), QLineEdit::Password,
                                            QObject::tr("haha"), &ok);

    if(ok)
    {
       if(text != "168")
       {
          QMessageBox::information(w, QObject::tr("��ʾ"),
                                 QObject::tr("�����������"),QObject::tr("ȷ��"));
          return false;
       }
       else
          return true;
     }
     else
        return false;
  */

    INT8U re;

    CinputPSWDialog *pswDialog= new CinputPSWDialog(&re, w);
    pswDialog->exec();

    return re;
}
