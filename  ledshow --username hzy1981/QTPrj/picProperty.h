#ifndef PICPROPERTY_H
#define PICPROPERTY_H

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
#include <simpleTextEdit.h>
#include "areaProperty.h"
#include "textedit.h"
#include <showArea.h>

#define MOVE_LEFT_CONTINUOUS 0x02
#define MOVE_UP_CONTINUOUS   0x01
#define MOVE_NORMAL          0x00

//��Ŀ���Դ�
class CpicProperty:public QWidget
{
    Q_OBJECT
private:

    QGroupBox *picPropertyGroup; //����

    QGroupBox *textGroup;
    QLabel *textLabel;  //�ı�
    QTextEdit *textEdit; //��ʾ�ı�

/*
    QGroupBox *paraGroup;
    QLabel *showModeLabel; //��ʾģʽ
    QLabel *speedLabel; //�����ٶ�
    QLabel *stayTimeLabel; //ͣ��ʱ��

    CshowModeCombo *showModeCombo;
    CshowSpeedCombo *speedCombo;
    QLineEdit *stayTimeEdit;
*/
    CshowModeEdit *showModeEdit;
    TextEdit *edit;
public slots:
    void showModeEdited();
    //void getSettings();
public:
    Carea *area;
    CnameEdit *nameEdit;
    void screenCardParaChangeProc();
    void connectSignal();
    void disconnectSignal();
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    QPushButton *editButton; //�༭��ť
    CpicProperty(QWidget *parent=0);
    ~CpicProperty();
};
void updatePicShowArea(CshowArea *area);
int checkSLineMoveLeftContinuous(QString str);
void getPicParaFromSettings(QString str, U_File_Para &para);
#endif // picProperty_H
