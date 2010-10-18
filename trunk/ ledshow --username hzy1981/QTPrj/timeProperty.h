#ifndef TIMEPROPERTY_H
#define TIMEPROPERTY_H

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

//��Ŀ���Դ�
class CtimeProperty:public QWidget
{
    Q_OBJECT
private:

    QGroupBox *timePropertyGroup; //����

    QGroupBox *textGroup;
    QLabel *textLabel;  //�ı�
    CsimpleTextEdit *simpleTextEdit;
    //QTextEdit *textEdit; //��ʾ�ı�
    //QPushButton *editButton; //�༭��ť



public:
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CtimeProperty(QWidget *parent=0);
    ~CtimeProperty();
};

#endif // TIMEPROPERTY_H
