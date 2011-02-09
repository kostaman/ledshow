#include "mainwindow.h"
#include "progProperty.h"
#include "progManage.h"
#include <QFileDialog>
#include <QMessageBox>


extern MainWindow *w;
//��Ŀ�����ļ�
QSettings settings(PROG_INI_FILE,QSettings::IniFormat,0);
//��Ļ�����ļ�
QSettings screenSettings(SCREEN_INI_FILE,QSettings::IniFormat,0);
//���ƿ������ļ�
QSettings cardSettings(CARD_INI_FILE,QSettings::IniFormat,0);

void MainWindow::setupFileActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("�ļ�"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    a = new QAction(tr("�½�"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    tb->addAction(a);
    menu->addAction(a);

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("��"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSave()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("���Ϊ"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
    tb->addAction(a);
    menu->addAction(a);

    menu->addSeparator();

    a = new QAction(tr("�˳�"), this);
    a->setPriority(QAction::LowPriority);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
    menu->addAction(a);

}

void MainWindow::setupViewActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("��ͼ"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("״̬��"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("���ƴ���"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("���Դ���"), this);
    a->setShortcut(QKeySequence::Save);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileSave()));
    tb->addAction(a);
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

    a = new QAction(tr("��Ļ"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newScreen())); //�½���Ŀ
    tb->addAction(a);

    menu->addAction(a);
    menu->addSeparator();

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("��Ŀ"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newProg())); //�½���Ŀ
    tb->addAction(a);

    menu->addAction(a);
    menu->addSeparator();

    a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newArea())); //�½���Ŀ
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();

    actionSave = a = new QAction(tr("��Ļ"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled(true);//(bool)Get_Pic_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newSText())); //�½���Ŀ
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("ͼ��"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Pic_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newPic())); //�½���Ŀ
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Pic_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newFlash()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Clock_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newClock()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("ʱ��"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Time_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTime()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("��ʱ"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Timer_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTimer()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("�¶�"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Temp_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTemp()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("ũ��"), this);
    a->setShortcut(QKeySequence::Save);
    a->setEnabled((bool)Get_Lun_Show_En());
    connect(a, SIGNAL(triggered()), progManage, SLOT(newLun()));
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();

    actionSave = a = new QAction(tr("ɾ��"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), progManage, SLOT(deleteItem())); //ɾ����Ŀ
    tb->addAction(a);
    menu->addAction(a);
}

void MainWindow::setupCtrlActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("����"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("Ԥ��"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), progManage, SLOT(preview()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("Уʱ"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("���ݷ���"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("����U���ļ�"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
    menu->addAction(a);
}

void MainWindow::setupToolActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("����"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("��ͼ��"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("������"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("���±�"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
    menu->addAction(a);
}

void MainWindow::setupHelpActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("����"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("����"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
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

    w->progManage->settingsInit();
    w->progManage->newProg();
    w->progManage->newArea();
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

    w->progManage->settingsInit();
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
  QList<QMdiSubWindow *> subWinList;

  subWinList = mdiArea->subWindowList(); //�Ӵ���ָ���б�
  int num = subWinList.size(); //�Ӵ��ڸ���
  for(int i = 0; i < num; i ++)
  {
    if(subWin EQ subWinList.at(i))
    {
       if(w->progManage->treeWidget->topLevelItemCount() > i)
       {
          w->progManage->clickItem(w->progManage->treeWidget->topLevelItem(i),0);
       }
    }
  }
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
    setupViewActions();
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
    //w->progManage->settingsInit();

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
