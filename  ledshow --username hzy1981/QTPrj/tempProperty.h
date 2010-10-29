#ifndef TEMPPROPERTY_H
#define TEMPPROPERTY_H

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

//��Ŀ���Դ�
class CtempProperty:public QWidget
{
    Q_OBJECT
private:

    QGroupBox *tempPropertyGroup; //����

    QGroupBox *textGroup;
    QLabel *textLabel;  //�ı�
    CsimpleTextEdit *simpleTextEdit;
    //QTextEdit *textEdit; //��ʾ�ı�
    //QPushButton *editButton; //�༭��ť



public:
    Carea *area;
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CtempProperty(QWidget *parent=0);
    ~CtempProperty();
};

#endif // TEMPPROPERTY_H
