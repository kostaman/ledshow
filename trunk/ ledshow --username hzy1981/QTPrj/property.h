#ifndef PROPERTY_H
#define PROPERTY_H

#include <QtGui/QMainWindow>
#include "areaProperty.h"
#include "progProperty.h"
#include "timerProperty.h"
#include "picProperty.h"
#include "clockProperty.h"
#include "flashProperty.h"
#include "timeProperty.h"
#include "tempProperty.h"
#include "textedit.h"
#include <QDockWidget>
#include <QStackedWidget>
#include <QTreeWidgetItem>



//���Դ���
class Cproperty :public QDockWidget
{
    Q_OBJECT
private:


    CprogProperty *progProperty; //��Ŀ����
    CtimeProperty *timeProperty; //����ʱ��
    CtimerProperty *timerProperty; //��ʱ��

    CclockProperty *clockProperty; //����
    CflashProperty *flashProperty; //flash����
    CtempProperty *tempProperty; //�¶�

public:
    Carea *area;
    CareaProperty *areaProperty; //��������
    CpicProperty *picProperty;  //ͼ��

    void setSettingsToWidget(QTreeWidgetItem *item);
    void getSettingsFromWidget(QTreeWidgetItem *item);

    void updateProperty(QTreeWidgetItem *item);
    void progChangedProc(QString settingsStr);

    QStackedWidget *stackedWidget;
    Cproperty(QWidget *parent = 0);
    ~Cproperty();
};
#endif // PROPERTY_H
