#ifndef CLOCKPROPERTY_H
#define CLOCKPROPERTY_H

#include "..\Includes.h"
#include <QtGui/QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include "simpleTextEdit.h"
#include "colorCombo.h"
#include "showArea.h"

class CclockProperty:public QWidget
{
    Q_OBJECT
private:
    QGroupBox *editGroup;

    QLabel *pointRadiusLabel; //����뾶
    QLabel *point369RadiusLabel; //369��뾶
    QLabel *hourWidthLabel; //Сʱ���
    QLabel *minWidthLabel; //���ӿ��
    QLabel *secWidthLabel; //���ӿ��

    QLabel *pointColorLabel; //������ɫ
    QLabel *point369ColorLabel; //369����ɫ
    QLabel *hourColorLabel; //Сʱ��ɫ
    QLabel *minColorLabel; //������ɫ
    QLabel *secColorLabel; //������ɫ

    QLineEdit *pointRadiusEdit; //����뾶
    QLineEdit *point369RadiusEdit; //
    QLineEdit *hourWidthEdit;
    QLineEdit *minWidthEdit;
    QLineEdit *secWidthEdit;

    CcolorCombo *pointColorCombo;
    CcolorCombo *point369ColorCombo;
    CcolorCombo *hourColorCombo;
    CcolorCombo *minColorCombo;
    CcolorCombo *secColorCombo;

    QGroupBox *textGroup;
    CsimpleTextEdit *simpleTextEdit;
public slots:
    void propertyEdited();
public:
    void updateShowAreaa(CshowArea *area);

    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CclockProperty(QWidget *parent);
    ~CclockProperty();
};

void getClockParaFromSettings(QString str, U_File_Para &para);
void updateClockShowArea(CshowArea *area);
#endif // CLOCKPROPERTY_H
