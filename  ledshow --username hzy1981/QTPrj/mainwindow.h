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
#include "mmtimer.h"


#define CARD_INI_FILE ".\\cfg\\card.ini"     //�忨�����ļ�
#define SCREEN_INI_FILE ".\\cfg\\screen.ini" //��Ļ�����ļ�
#define PROG_INI_FILE ".\\cfg\\progData.ini"     //��Ŀ�����ļ�

#define PROTO_DATA_FILE ".\\data\\protoData.dat"      //Э�������ļ�
#define UDISK_PROTO_FILE ".\\data\\uDiskData.dat"      //Э�������ļ�
#define PREVIEW_PROTO_FILE ".\\data\\previewData.dat" //Ԥ�������ļ�
#define SIM_PROTO_FILE ".\\data\\simData.dat" //Ԥ�������ļ�
#define COM_PROTO_FILE ".\\data\\comData.dat"
#define UDISK_DATA_DIR ".\\data\\"

#define MCUZK_FILE ".\\font\\mcuzk.dat" //���͵���λ�����ֿ��ļ�
#define MCUZK_PROTO_FILE ".\\font\\mcuzkproto.dat"

#define WORKDIR() QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation)

#define SEND_PARA_OK_STR    "���ݷ��ͳɹ�"
#define SEND_PARA_DENIED_STR  "���ݷ���ʧ�ܣ��յ���Ӧ��"
#define SEND_PARA_FAIL_STR  "���ݷ���ʧ�ܣ�����ͨ�Ų�����ͨ����·�Ƿ�������"
#define SEND_PARA_FAIL_RECONNECT_STR  "���ݷ���ʧ�ܣ��Ƿ���Ҫ�Զ�������ʾ����������ĵ���ֻ������һ����ʾ�����������㡰ȷ������ť��������㡰ȡ������ť�����ֶ��Ų�ͨ�Ź���ԭ��"

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
    void helpFileOpen();
    void hardwareHelpFileOpen();
    void showAboutDialog();
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
    void setupLanguageActions();


    QMenu *ctrlMenu;
    QAction *actionScreen;
    QAction *actionProg;
    QAction *actionArea;
    QAction *actionTxt;
    QAction *actionSText;
    QAction *actionMText;
    QAction *actionTable;
    QAction *actionTemp;
    QAction *actionHumidi;
    QAction *actionFlash;
    QAction *actionImage;
    QAction *actionClock;
    QAction *actionTime;
    QAction *actionNoise;
    QAction *actionNongli;
    QAction *actionTimer;
    QAction *actionDel;
    QAction *actionPreview;
    QAction *actionLarge;
    QAction *actionSmall;
    QAction *actionScreenPreiew;
    QAction *actionTestCard;
    QAction *actionDownloadZK; //�����ֿ�
    QAction *actionModiScreenPara;
    QAction *actionUpdateFirmware;
    QAction *actionUDisk;
    QAction *actionSendData;
    QAction *actionAdjTime;
    QAction *actionLightness;
    QAction *actionOpenClose;
    QAction *actionManualClose; //�ֶ��ػ�
    QAction *actionManualOpen; //�ֶ�����
    QAction *atcionGetOCStatus; //��ȡ���ػ�״̬

public slots:
    void modifyScreenPara();
    void updateFirmware();
    void setLightness();
    void setManualClose();
    void setManualOpen();
    void adjTime();
    void sendDataProc();
    void exportUdsikProc();
    void setOpenCloseTime();
    void previewScreen();
    void previewProg();
    void previewProc();
    void largeScreen(); //�Ŵ���Ļ
    void smallScreen(); //��С��Ļ
    void previewTimerProc();
    void comStatusShow();
    void testCard(); //���Կ��ƿ�
    void downloadZK();
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
    MMTimer *mmtimer;

    int timerFlag;
    INT8U previewProgNo;

    CcomStatus *comStatus; //ͨ��״̬

    void setActonsEnable();
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
    INT8U *verifyRe;
    QLineEdit *lineEdit;

    QPushButton *okButton;
    QPushButton *cancelButton;

    QLabel *reLabel;
   CinputPSWDialog(INT8U *re, QWidget *parent);
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
INT8U verifyPSW();
#endif // MAINWINDOW_H
