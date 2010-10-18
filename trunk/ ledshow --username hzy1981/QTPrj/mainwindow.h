#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "..\LED_Cfg.h"
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
#include "showArea.h"
#include "areaProperty.h"
#include "progManage.h"
#include "property.h"
#include "timerProperty.h"



//������
class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void settingsInit();
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

    QAction *actionSave;
public:
    QWidget *widget;
    CprogManage *progManage; //��Ŀ����
    Cproperty *property; //���Ա༭

    CscreenArea *screenArea; //��ʾ����

    //QWidget *widget;

    //QLabel *Label;
//protected:
    //void paintEvent(QPaintEvent *);
public:
    void setCurSettingsStr(QString str);  //��ȡ��ǰ��settings��str
    QString getCurSettingsStr();   //���õ�ǰsettings��str

    //int getColor();
    void closeEvent(QCloseEvent *event);
    //void createProgTreeArea();
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
