#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "..\Stm32\usr\app\LED_Cfg.h"
#include <QtGui/QMainWindow>
#include <QLineEdit.h>
#include <QListView>
#include <QDockWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QStackedWidget>
#include <QDialog>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QSettings>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QList>
#include <QObjectList>
#include "showArea.h"
#include "areaProperty.h"
#include "progManage.h"
#include "property.h"
#include "timerProperty.h"
#include "Communication.h"


#define CARD_INI_FILE ".\\cfg\\card.ini"     //�忨�����ļ�
#define SCREEN_INI_FILE ".\\cfg\\screen.ini" //��Ļ�����ļ�
#define PROG_INI_FILE ".\\cfg\\temp.ini"     //��Ŀ�����ļ�

#define PROTO_DATA_FILE ".\\data\\protoData.dat"      //Э�������ļ�
#define UDISK_PROTO_FILE ".\\data\\uDiskData.dat"      //Э�������ļ�
#define PREVIEW_PROTO_FILE ".\\data\\previewData.dat" //Ԥ�������ļ�
#define SIM_PROTO_FILE ".\\data\\simData.dat" //Ԥ�������ļ�
#define COM_PROTO_FILE ".\\data\\comData.dat"
#define UDISK_DATA_DIR ".\\data\\"

class MainObj:public QObject
{
  Q_OBJECT
private:
signals:
    void screenChange();
public:
    void emitScreenChangeSignal();
    MainObj(QObject *parent = 0);
    ~MainObj();
};

//������
class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void fileSaveAs();
    void fileSave();
    void fileNew();
    void fileOpen();
    void settingsInit();
    void updateTreeWidget(QMdiSubWindow*);
private:
    int color;

    QString curSettingsStr; //��ǰ�Ľ�Ŀ���������ļ���settings��STR

    void setupFileActions();
    void setupViewActions();
    void setupEditActions();
    void setupCtrlActions();
    void setupToolActions();
    void setupHelpActions();
    //void settingsInit();

    QMenu *ctrlMenu;
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
    QAction *actionDel;
    QAction *actionPreview;
    QAction *actionScreenPreiew;
    QAction *actionModiScreenPara;
    QAction *actionUDisk;
    QAction *actionSendData;
    QAction *actionAdjTime;
    QAction *actionLightness;
    QAction *actionOpenClose;

public slots:
    void modifyScreenPara();
    void setLightness();
    void adjTime();
    void sendDataProc();
    void exportUdsikProc();
    void setOpenCloseTime();
    void previewScreen();
    void previewProg();
    void previewProc();
    void previewTimerProc();
    void comStatusShow();
public:
    QAction *actionComStatus;

    int MDISubWinClickFlag;
    QWidget *widget;
    CprogManage *progManage; //��Ŀ����
    Cproperty *property; //���Ա༭

    CscreenArea *screenArea; //��ʾ����
    QMdiArea *mdiArea;

    QMainWindow *previewWin;
    CscreenArea *previewArea;
    QTimer *timer;
    int timerFlag;
    INT8U previewProgNo;

    CcomStatus *comStatus; //ͨ��״̬

    void actionEnProc(int type);
    void screenCardParaChangeProc();
    void setCurSettingsStr(QString str);  //��ȡ��ǰ��settings��str
    QString getCurSettingsStr();   //���õ�ǰsettings��str

    void closeEvent(QCloseEvent *event);

    void preview(INT8U previewMode);
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

class CinputPSWDialog:public QDialog
{
    Q_OBJECT
public slots:
    void okClickProc();
public:
    bool *verifyRe;
    QLineEdit *lineEdit;

    QPushButton *okButton;
    QPushButton *cancelButton;

    QLabel *reLabel;
   CinputPSWDialog(bool *re, QWidget *parent);
   ~CinputPSWDialog();
};

extern MainWindow *w;
extern MainObj *mainObj;
extern QString rsrcPath1;//  ":/images/win1"
extern QString rsrcPath;// ":/images/win"

QMdiSubWindow *getSubWinByIndex(QMdiArea *parentArea, int index);
int getIndexBySubWin(QMdiArea *parentArea, QMdiSubWindow *subWin);
QIcon getTypeIcon(INT8U type);
void traversalControl(const QObjectList& q);
bool verifyPSW();
#endif // MAINWINDOW_H
