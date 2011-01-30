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
#include "showArea.h"
#include "simpleTextEdit.h"

#define MAX_BORDER_TYPE 10
//��Ŀ���Դ�
class CprogProperty:public QWidget
{
    Q_OBJECT
private:
    QGroupBox *nameGroup;
    QGroupBox *timerGroup; //��ʱ����

    //-----------����-------------
    //QLabel *nameLabel;  //����
    //QLineEdit *nameEdit; //���������
    CnameEdit *nameEdit;
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
    QCheckBox *playCountCheck; //˳�β���
    QLineEdit *playCountEdit; //����
    QLabel *playCountLabel;//����label

    QCheckBox *playTimeCheck; //��������
    QLineEdit *playTimeEdit; //ʱ��
    QLabel *playTimeLabel;

    //-------------�߿�ѡ��----------
    QGroupBox *borderGroup; //�߿�
    QCheckBox *borderCheck;

    QLabel *stepLabel,*styleLabel,*modeLabel,*speedLabel;
    QLabel *pointsLabel,*usLabel;
    QComboBox *stepCombo,*speedCombo;
    QComboBox *styleCombo;
    QComboBox *modeCombo;
    CcolorCombo *colorCombo;

    QPixmap borderPixmap[MAX_BORDER_TYPE];

    //QSrting settingsStr; //��ǰ����Str
public slots:
    void allWeekDayCheckProc(int state);
    void dateTimerCheckProc(int state);
    void weekTimerCheckProc(int state);
    void timeCheckProc(int state);
    void playTimeCheckProc(int state);
    void playCountCheckProc(int state);
    void borderCheckProc(int state);
    void edited();
public:
    void connectSignal();
    void disconnectSignal();
    void setSettingsToWidget(QString str);
    void getSettingsFromWidget(QString str);

    CprogProperty(QWidget *parent=0);
    ~CprogProperty();
};

typedef struct
{
  int Width;
  int Height;

  char Data[300];

}S_Border_Data;

void getProgParaFromSettings(QString str, S_Prog_Para &para);
void updateProgShowArea(CscreenArea *area);
#endif // PROGPROPERTY_H
