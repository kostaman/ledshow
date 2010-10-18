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
#include "textedit.h"

class CshowModeCombo:public QComboBox
{
public:
    CshowModeCombo(QWidget *parent = 0);
    ~CshowModeCombo();
};

class CshowSpeedCombo:public QComboBox
{
public:
    CshowSpeedCombo(QWidget *parent = 0);
    ~CshowSpeedCombo();
};

//��Ŀ���Դ�
class CpicProperty:public QWidget
{
    Q_OBJECT
private:

    QGroupBox *picPropertyGroup; //����

    QGroupBox *textGroup;
    QLabel *textLabel;  //�ı�
    QTextEdit *textEdit; //��ʾ�ı�


    QGroupBox *paraGroup;
    QLabel *showModeLabel; //��ʾģʽ
    QLabel *speedLabel; //�����ٶ�
    QLabel *stayTimeLabel; //ͣ��ʱ��

    CshowModeCombo *showModeCombo;
    CshowSpeedCombo *speedCombo;
    QLineEdit *stayTimeEdit;

    TextEdit *edit;
public:
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    QPushButton *editButton; //�༭��ť
    CpicProperty(QWidget *parent=0);
    ~CpicProperty();
};

#endif // picProperty_H
