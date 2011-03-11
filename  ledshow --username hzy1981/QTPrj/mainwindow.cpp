#include "mainwindow.h"
#include "progProperty.h"
#include "progManage.h"
#include "makeProto.h"
#include <QFileDialog>
#include <QMessageBox>


extern MainWindow *w;
//��Ŀ�����ļ�
QSettings settings(PROG_INI_FILE,QSettings::IniFormat,0);


#define QT_MOVE_STEP_TIMER MOVE_STEP_TIMER/2 //����ʱ��ʱ���

#if QT_MOVE_STEP_TIMER > MOVE_STEP_TIMER
#error "QT_MOVE_STEP_TIMER error"
#endif

int stepTimer = 0;

QString getItemStr(QTreeWidgetItem *item)
{
    return item->data(0,Qt::UserRole).toString();
}



void MainWindow::setupFileActions()
{
    //QToolBar *tb = new QToolBar(this);
    //tb->setWindowTitle(tr("File Actions"));
    //addToolBar(tb);

    QMenu *menu = new QMenu(tr("�ļ�"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    a = new QAction(tr("�½�"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    //tb->addAction(a);
    menu->addAction(a);

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("��"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSave()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("���Ϊ"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
    //tb->addAction(a);
    menu->addAction(a);

    menu->addSeparator();

    a = new QAction(tr("�˳�"), this);
    a->setPriority(QAction::LowPriority);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
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
    a->setShortcut(QKeySequence::New);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("���ƴ���"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("���Դ���"), this);
    a->setShortcut(QKeySequence::Save);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileSave()));
    //tb->addAction(a);
    menu->addAction(a);
}

void MainWindow::setupEditActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("�༭"), this);
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
    actionScreen = a = new QAction(tr("��Ļ"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newScreen())); //�½���Ŀ
    //tb->addAction(a);

    menu->addAction(a);
    menu->addSeparator();

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    actionProg = a = new QAction(tr("��Ŀ"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newProg())); //�½���Ŀ
    tb->addAction(a);

    menu->addAction(a);
    menu->addSeparator();
    tb->addSeparator();

    actionArea = a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newArea())); //�½���Ŀ
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();
    tb->addSeparator();

    actionSText = a = new QAction(tr("��Ļ"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled(true);//(bool)Get_Pic_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newSText())); //�½���Ŀ
    tb->addAction(a);
    menu->addAction(a);

    actionMText = a = new QAction(tr("�ı�"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Pic_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newPic())); //�½���Ŀ
    tb->addAction(a);
    menu->addAction(a);

    actionFlash = a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Pic_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newFlash()));
    tb->addAction(a);
    menu->addAction(a);

    actionClock = a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Clock_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newClock()));
    tb->addAction(a);
    menu->addAction(a);

    actionTime = a = new QAction(tr("ʱ��"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Time_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTime()));
    tb->addAction(a);
    menu->addAction(a);

    actionNongli = a = new QAction(tr("ũ��"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Lun_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newLun()));
    tb->addAction(a);
    menu->addAction(a);

    actionTimer = a = new QAction(tr("��ʱ"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Timer_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTimer()));
    tb->addAction(a);
    menu->addAction(a);

    actionTemp = a = new QAction(tr("�¶�"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Temp_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTemp()));
    tb->addAction(a);
    menu->addAction(a);

    actionHumidi = a = new QAction(tr("ʪ��"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Humidity_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newHumidity()));
    tb->addAction(a);
    menu->addAction(a);

    actionNoise = a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Humidity_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newNoise()));
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();
    tb->addSeparator();

    actionDel = a = new QAction(tr("ɾ��"), this);
    a->setShortcut(QKeySequence::Save);
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

    actionScreen->setEnabled(true);
    actionProg->setEnabled(false);
    actionArea->setEnabled(false);
    actionSText->setEnabled(false);
    actionMText->setEnabled(false);
    actionTemp->setEnabled(false);
    actionHumidi->setEnabled(false);
    actionFlash->setEnabled(false);
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

      actionScreen->setEnabled(true);
      actionProg->setEnabled(true);
      actionArea->setEnabled(false);
      actionSText->setEnabled(false);
      actionMText->setEnabled(false);
      actionTemp->setEnabled(false);
      actionHumidi->setEnabled(false);
      actionFlash->setEnabled(false);
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

      actionScreen->setEnabled(true);
      actionProg->setEnabled(true);
      actionArea->setEnabled(true);
      actionSText->setEnabled(false);
      actionMText->setEnabled(false);
      actionTemp->setEnabled(false);
      actionHumidi->setEnabled(false);
      actionFlash->setEnabled(false);
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

      actionScreen->setEnabled(true);
      actionProg->setEnabled(true);
      actionArea->setEnabled(true);
      actionSText->setEnabled(true);
      actionMText->setEnabled(true);
      actionTemp->setEnabled(true);
      actionHumidi->setEnabled(true);
      actionFlash->setEnabled(true);
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

      actionScreen->setEnabled(true);
      actionProg->setEnabled(true);
      actionArea->setEnabled(true);
      actionSText->setEnabled(true);
      actionMText->setEnabled(true);
      actionTemp->setEnabled(true);
      actionHumidi->setEnabled(true);
      actionFlash->setEnabled(true);
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
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("����"), this);
    ctrlMenu = menu;//���Ʋ˵�
    menuBar()->addMenu(menu);
    menu->setEnabled(false);

    QAction *a;

    a = new QAction(tr("�޸���Ļ����"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(modifyScreenPara()));
    //tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();

    a = new QAction(tr("��ʱ���ػ�"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(setOpenCloseTime()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("��������"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(setLightness()));
    //tb->addAction(a);
    menu->addAction(a);


    a = new QAction(tr("Уʱ"), this);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(adjTime()));
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();
    tb->addSeparator();

    a = new QAction(tr("��������"), this);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(sendDataProc()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("����U���ļ�"), this);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(exportUdsikProc()));
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();
    tb->addSeparator();

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    actionPreview = a = new QAction(tr("Ԥ��"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(preview()));
    tb->addAction(a);
    menu->addAction(a);
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
    a->setShortcut(QKeySequence::New);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("������"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("���±�"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
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
    a->setShortcut(QKeySequence::New);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    //tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
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

    newFileName = QFileDialog::getSaveFileName(this, tr("���������ļ�"), ".", tr("�����ļ�(.ini)"));
    if(newFileName.length()==0)
        return;

    if(QFile::copy(PROG_INI_FILE, newFileName) == true) //�����ϵ��ļ�
    {
      settings.beginGroup("file");
      settings.setValue("cfgFile", newFileName); //�����ļ���
      settings.endGroup();
   }

}

//�½��ļ�
void MainWindow::fileNew()
{
    QString newFileName;

    newFileName = QFileDialog::getSaveFileName(this, tr("�½������ļ�"), ".", tr("�����ļ�(.ini)"));
    if(newFileName.length()==0)
        return;

    fileSave(); //�������ļ�

    settings.remove("program");//clear(); //���

    settings.beginGroup("file");
    settings.setValue("cfgFile", newFileName);
    settings.endGroup();

    progManage->settingsInit();
    progManage->newProg();
    progManage->newArea();
}

//���ļ�
void MainWindow::fileOpen()
{
    QString newFileName;
    QString oldFileName;

    newFileName = QFileDialog::getOpenFileName(this, tr("�������ļ�"), ".", tr("�����ļ�(.ini)"));
    if(newFileName.length()==0)
    {
        return;
    }

    settings.beginGroup("file");
    oldFileName = settings.value("cfgFile").toString(); //�����ļ���
    settings.endGroup();

    QFile::remove(oldFileName);
    if(QFile::copy(PROG_INI_FILE, oldFileName)==false) //�����ϵ��ļ�
    {
        ASSERT_FAILED();
        //qDebug("file open copy oldFileName error");
    }

    QFile::remove(PROG_INI_FILE);
    if(QFile::copy(newFileName, PROG_INI_FILE)==false)
    {
        ASSERT_FAILED();
        //qDebug("file open copy PROG_INI_FILE error");
    }

    settings.beginGroup("file");
    settings.setValue("cfgFile", newFileName);
    settings.endGroup();

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

    setupFileActions();
    //setupViewActions();
    setupEditActions();
    setupCtrlActions();
    setupToolActions();
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

   QHBoxLayout *hLayout = new QHBoxLayout(previewWin);
   hLayout->addWidget(previewArea);
   hLayout->setSizeConstraint(QLayout::SetFixedSize);
   previewWin->setLayout(hLayout);


   timer = new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(previewProc()));

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

  if(verifyPSW() EQ false)
      return;

  str = w->screenArea->getCurrentScreenStr(); //��ǰ��Ļstr

  QDialog *facParaWin = new QDialog(this);
  QHBoxLayout *hLayout = new QHBoxLayout(facParaWin);

  facParaWin->setWindowTitle(tr("�޸İ�װ����"));
  CfacScreenProperty *facScreenProperty = new CfacScreenProperty(MODI_SCN, facParaWin);
  facScreenProperty->setSettingsToWidget(str);

  hLayout->addWidget(facScreenProperty);
  facParaWin->setLayout(hLayout);
  facParaWin->setAttribute(Qt::WA_DeleteOnClose);
  connect(facScreenProperty->endButton, SIGNAL(clicked()), facParaWin, SLOT(close()));
  facParaWin->exec();

}

//��������
void MainWindow::setLightness()
{
  ClightnessDialog *lightnessDialog = new ClightnessDialog(this);
  QString str = w->screenArea->getCurrentScreenStr();
  lightnessDialog->setSettingsToWidget(str);

  lightnessDialog->exec();
}

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

void MainWindow::preview()
{
  QString screenStr;//progStr;
  INT8U Screen_No;
  //���ɷ����ļ�
  Mem_Open();

  screenStr = getItemStr(screenArea->screenItem);
  makeProtoData(screenStr, PREVIEW_MODE);

  Screen_No = progManage->treeWidget->indexOfTopLevelItem(screenArea->screenItem);
  if(screenArea->screenItem->childCount() EQ 0)
  {
      QMessageBox::information(w, tr(APP_NAME),
                               tr("����ѡ��һ��Ԥ���Ľ�Ŀ"),tr("ȷ��"));

      return;
  }
  Preview_Prog_No = screenArea->screenItem->indexOfChild(screenArea->progItem);
  //setCentralWidget(mdiArea);
  //CMdiSubWindow *subWin = new CMdiSubWindow;
  //subWin->previewFlag = 1; //���ڷ�����Ӵ���
  timerFlag = 0;
  stepTimer = 0;

  //previewWin = new CpreviewWin(w);//new QMainWindow(w);
  previewWin->setWindowModality(Qt::WindowModal);
/*
  previewArea =  new CscreenArea(previewWin);
  previewArea->setWindowModality(Qt::WindowModal);
  */

  //previewArea->setGeometry(0,0,Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height); //resize(Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);
  //previewArea->setFixedSize(previewArea->size());
  previewArea->resize(Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);
  previewWin->resize(Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);

  previewArea->previewFlag = 1;
  //previewArea->updateFlag = true;

  //previewWin->setAttribute(Qt::WA_DeleteOnClose);
  previewWin->setWindowTitle(tr("Ԥ��-")+QString::number(Screen_No + 1) + tr("��Ļ-") + QString::number(Preview_Prog_No + 1) + tr("��Ŀ"));
  previewWin->move((width() - previewArea->width())/2, (height() - previewArea->height())/2);

  Show_Init(); //��ʾ��ʼ����


  previewWin->show();
  //previewWin->setFixedSize(previewWin->size());


  //�½���ʱ��


  //������ʱ�������źź���Ӧ�Ĳۺ���
  timer->start(QT_MOVE_STEP_TIMER);
  timer->stop();

  timer->start(QT_MOVE_STEP_TIMER);
  //previewProc();

}

void MainWindow::previewProc()
{
  stepTimer += QT_MOVE_STEP_TIMER;

  Show_Main_Proc();
  Show_Main_Proc();
  Show_Main_Proc();

  if(stepTimer >= MOVE_STEP_TIMER)
  {
      stepTimer = 0;
      Show_Timer_Proc();

      previewArea->previewFlag = 1;//Ԥ������
      //previewArea->updateFlag = 1;
      memcpy(previewArea->showData.Color_Data, Show_Data.Color_Data, sizeof(Show_Data.Color_Data));
      previewArea->update(); //ˢ����ʾ����
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

CinputPSWDialog::CinputPSWDialog(bool *re, QWidget *parent):QDialog(parent)
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
   if(lineEdit->text() == "168")
    {
       *verifyRe = true;
      close();
   }
   else
   {
       reLabel->setText(tr("�������!"));
       *verifyRe = false;
   }
}

CinputPSWDialog::~CinputPSWDialog()
{

}


bool verifyPSW()
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

    bool re;

    CinputPSWDialog *pswDialog= new CinputPSWDialog(&re, w);
    pswDialog->exec();

    return re;
}
