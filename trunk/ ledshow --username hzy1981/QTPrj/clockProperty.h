#ifndef CLOCKPROPERTY_H
#define CLOCKPROPERTY_H

#include "..\Stm32\usr\app\Includes.h"
#include <QtGui/QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QSpinBox>
#include "areaProperty.h"
#include "simpleTextEdit.h"
#include "colorCombo.h"
#include "showArea.h"

class CposiEdit:public QGroupBox
{
  Q_OBJECT
public:
    QComboBox *item;
    QPushButton *left;
    QPushButton *right;
    QPushButton *up;
    QPushButton *down;
    QPushButton *def;


    CposiEdit(QWidget *parent);
    ~CposiEdit();
};

class CclockProperty:public QWidget
{
    Q_OBJECT
private:
    QGroupBox *editGroup;

    QLabel *pointRadiusLabel; //����뾶
    QLabel *point369RadiusLabel; //369��뾶
    QLabel *pointMinRadiusLabel;  //�ֵ�
    QLabel *hourWidthLabel; //Сʱ���
    QLabel *minWidthLabel; //���ӿ��
    QLabel *secWidthLabel; //���ӿ��

    QLabel *pointColorLabel; //������ɫ
    QLabel *point369ColorLabel; //369����ɫ
    QLabel *hourColorLabel; //Сʱ��ɫ
    QLabel *minColorLabel; //������ɫ
    QLabel *secColorLabel; //������ɫ

    QSpinBox *pointRadiusEdit; //����뾶
    QSpinBox *point369RadiusEdit; //
    QSpinBox *pointMinRadiusEdit;

    QSpinBox *hourWidthEdit;
    QSpinBox *minWidthEdit;
    QSpinBox *secWidthEdit;

    CcolorCombo *pointColorCombo;
    CcolorCombo *point369ColorCombo;
    CcolorCombo *pointMinColorCombo;
    CcolorCombo *hourColorCombo;
    CcolorCombo *minColorCombo;
    CcolorCombo *secColorCombo;

    QComboBox *pointStyle; //����ʽ��
    QComboBox *point369Style; //369��ʽ��
    QComboBox *pointMinStyle; //�ֵ�ʽ��

    CtimeDiffEdit *timeDiffEdit;
    CsimpleTextEdit *simpleTextEdit;
    CposiEdit *posiEdit;

    QGroupBox *timeGroup;
    CdateEdit *dateEdit;
    CweekEdit *weekEdit;

    CshowModeEdit *showModeEdit;
signals:
    void edited();
public slots:
    void leftEdit();
    void rightEdit();
    void upEdit();
    void downEdit();
    void defEdit();
    void propertyEdited();
public:
    Carea *area;
    CnameEdit *nameEdit;
    void screenCardParaChangeProc();
    void updateShowAreaa(CshowArea *area);

    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CclockProperty(QWidget *parent);
    ~CclockProperty();
};

void getClockParaFromSettings(QString str, U_File_Para &para);
void updateClockShowArea(CshowArea *area);
void Get_Clock_Text_Point(INT16U Width, INT16U Height, S_Clock_Para *pPara, S_Point *pPoint);
#endif // CLOCKPROPERTY_H
