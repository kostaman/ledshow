#ifndef PROPERTY_H
#define PROPERTY_H

#include <QtGui/QMainWindow>
#include "areaProperty.h"
#include "screenProperty.h"
#include "progProperty.h"
#include "timerProperty.h"
#include "picProperty.h"
#include "clockProperty.h"
#include "flashProperty.h"
#include "timeProperty.h"
#include "tempProperty.h"
#include "lunProperty.h"
#include "humidityProperty.h"
#include "noiseProperty.h"
#include "textedit.h"
#include <QDockWidget>
#include <QStackedWidget>
#include <QTreeWidgetItem>



//���Դ���
class Cproperty :public QDockWidget
{
    Q_OBJECT
private:

    CscreenProperty *screenProperty; //��Ļ����
    CprogProperty *progProperty; //��Ŀ����
    CtimeProperty *timeProperty; //����ʱ��
    CtimerProperty *timerProperty; //��ʱ��

    CclockProperty *clockProperty; //����
    CflashProperty *flashProperty; //flash����
    CtempProperty *tempProperty; //�¶�
    ClunProperty *lunProperty; //ũ��
    ChumidityProperty *humidityProperty;
    CnoiseProperty *noiseProperty;
public:
    Carea *area;
    CareaProperty *areaProperty; //��������
    CpicProperty *picProperty;  //ͼ��

    void screenCardParaChangeProc();
    void setSettingsToWidget(QTreeWidgetItem *item);
    void getSettingsFromWidget(QTreeWidgetItem *item);

    void updateProperty(QTreeWidgetItem *item);
    void progChangedProc(QString settingsStr);

    QStackedWidget *stackedWidget;
    Cproperty(QWidget *parent = 0);
    ~Cproperty();
};
#endif // PROPERTY_H
