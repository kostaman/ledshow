#ifndef TIMERPROPERTY_H
#define TIMERPROPERTY_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include "simpleTextEdit.h"
#include "areaProperty.h"
#include "showArea.h"

//��Ŀ���Դ�
class CtimerProperty:public QWidget
{
    Q_OBJECT
private:

    QGroupBox *timerPropertyGroup; //����

    QGroupBox *textGroup;
    QLabel *textLabel;  //�ı�
    CsimpleTextEdit *simpleTextEdit;
    CsmLineEdit *smLineEdit;
    CshowModeEdit *showModeEdit;
    QGroupBox *dstTimeGroup;
    QLabel *dstTimeLabel; //Ŀ��ʱ��
    QLabel *styleLabel; //��ʽ
    QLabel *colorLabel; //��ɫ
    QLabel *fontSizeLabel; //��С
    QDateTimeEdit *dstDateTimeEdit; //Ŀ��ʱ������
    CcolorCombo *colorCombo;  //��ɫ
    QComboBox *styleCombo;  //��ʽ
    CsizeCombo *fontSizeCombo; //�����С
public slots:
    void edited();
public:
    Carea *area;
    CnameEdit *nameEdit;
    void screenCardParaChangeProc();
    void connectSignal();
    void disconnectSignal();
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CtimerProperty(QWidget *parent=0);
    ~CtimerProperty();
};

void getTimerParaFromSettings(QString str, U_File_Para &para);
void updateTimerShowArea(CshowArea *area);
void Get_Timer_Text_Point(INT8U Area_No, INT16U Width, INT16U Height, S_Point &P0);
#endif // TIMERPROPERTY_H
