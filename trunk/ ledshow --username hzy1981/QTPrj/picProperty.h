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
public:
    Carea *area;
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    QPushButton *editButton; //�༭��ť
    CpicProperty(QWidget *parent=0);
    ~CpicProperty();
};

#endif // picProperty_H