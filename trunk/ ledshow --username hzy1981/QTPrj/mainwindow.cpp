#include "mainwindow.h"
#include "progProperty.h"

QSettings settings("test", "test");
void MainWindow::setupFileActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("�½�"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    //QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction(tr("��"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(settingsInit()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Open);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("���Ϊ"), this);
    a->setShortcut(QKeySequence::Save);
    //connect(a, SIGNAL(triggered()), this, SLOT(fileSave()));
    //a->setEnabled(false);
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

    actionSave = a = new QAction(tr("ͼ��"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newPic())); //�½���Ŀ
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newFlash()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("����"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newClock()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("����ʱ��"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTime()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("��ʱ"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTimer()));
    tb->addAction(a);
    menu->addAction(a);

    actionSave = a = new QAction(tr("�¶�"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), progManage, SLOT(newTemp()));
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
    //connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
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

void MainWindow::settingsInit()
{
    QStringList str;

    settings.beginGroup("screen");
    str = settings.allKeys();
    //if(str.isEmpty() == true)
    {
        int xLen = 256;
        int yLen = 256;
        int color = 0x02;

        settings.setValue("xLen", xLen);
        settings.setValue("yLen", yLen);
        settings.setValue("color", color);
    }
    settings.endGroup();
    //color =
   //progManage->settingsInit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //property->progProperty->getSettingsFromWidget();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    settingsInit();
    //QGridLayout *gridLayout;
    setToolButtonStyle(Qt::ToolButtonFollowStyle);

    //gridLayout = new QGridLayout(this);
    progManage = new CprogManage(this);
    property = new Cproperty(this);

    widget = new QWidget(this);
    widget->setAutoFillBackground(true);
    QPalette *palette;
    palette = new QPalette();
    palette->setColor(QPalette::Background, QColor(Qt::white));
    widget->setPalette(*palette);

    screenArea =  new CscreenArea(widget);//CshowArea(this, 1);

    //CshowArea *p = new CshowArea(screenArea,2);
    //p->update();
    //p = new CshowArea(screenArea,1);

    //settings = new QSettings();

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
    setCentralWidget(widget);
//screenArea->newShowArea();
    //setLayout(gridLayout);

}

MainWindow::~MainWindow()
{

}
