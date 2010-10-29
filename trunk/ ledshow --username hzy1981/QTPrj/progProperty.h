#ifndef PROGPROPERTY_H
#define PROGPROPERTY_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QCheckBox>
#include <QComboBox>
#include "colorCombo.h"


//��Ŀ���Դ�
class CprogProperty:public QWidget
{
    Q_OBJECT
private:
    QGroupBox *nameGroup;
    QGroupBox *timerGroup; //��ʱ����

    //-----------����-------------
    QLabel *nameLabel;  //����
    QLineEdit *nameEdit; //���������

    //--------  �����ڶ�ʱ---------
    QGroupBox *dateGroup;
    QCheckBox *dateTimerCheck; //�����ڶ�ʱ
    QLabel *startDateLabel, *endDateLabel;
    QDateEdit *startDateEdit; //��ʼ����
    QDateEdit *endDateEdit; //��������

    //----------�����ڶ�ʱ-----------
    QGroupBox *weekGroup;
    QCheckBox *weekTimerCheck; //�����ڶ�ʱ
    QCheckBox *weekCheck[7]; //����ѡ��

    //----------��ʱ�䶨ʱ----------
    QGroupBox *timeGroup;
    QCheckBox *timeCheck; //��ʱ�䶨ʱ
    QLabel *startTimeLabel,*endTimeLabel;
    QTimeEdit *startTimeEdit; //��ʼʱ��
    QTimeEdit *endTimeEdit; //����ʱ��

    //------------��������----------
    QGroupBox *playTimeGroup; //����ʱ��
    QCheckBox *playTimeCheck; //��������
    QLineEdit *playTimeEdit; //ʱ��
    QLabel *playTimeLabel;

    //-------------�߿�ѡ��----------
    QGroupBox *borderGroup; //�߿�
    QCheckBox *borderCheck;

    QLabel *widthLabel,*styleLabel,*colorLabel,*speedLabel;
    QLabel *pointsLabel,*usLabel;
    QLineEdit *widthEdit, *speedEdit;
    QComboBox *styleCombo;
    CcolorCombo *colorCombo;

    //QSrting settingsStr; //��ǰ����Str
public slots:
    void allWeekDayCheckProc(int state);
    void dateTimerCheckProc(int state);
    void weekTimerCheckProc(int state);
    void timeCheckProc(int state);
    void playTimeCheckProc(int state);
    void borderCheckProc(int state);

public:

    void setSettingsToWidget(QString str);
    void getSettingsFromWidget(QString str);

    CprogProperty(QWidget *parent=0);
    ~CprogProperty();
};

#endif // PROGPROPERTY_H
