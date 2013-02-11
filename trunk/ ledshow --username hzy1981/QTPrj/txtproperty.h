#ifndef TXTPROPERTY_H
#define TXTPROPERTY_H

#include <QLabel>
#include <QTextEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFontComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QDialog>
#include "simpleTextEdit.h"
#include "areaProperty.h"
#include "showArea.h"
#include "colorCombo.h"
#include "progManage.h"
#include "..\Stm32\usr\app\Includes.h"

#define MAX_CHR_NUM  (BLOCK_DATA_LEN - 9 - 20)

class CsimpleTextEdit1 :public QGroupBox
{
    Q_OBJECT
private:
    QGroupBox *textGroup;
    QLabel *fontLabel; //����
    QLabel *colorLabel;
    QLabel *fontSizeLabel; //�����С
    //QLabel *colorLabel; //��ɫ

    //QFontComboBox *fontCombo;
    QComboBox *fontSizeCombo;
    CcolorCombo *colorCombo;

    //QPushButton *oButton; //��

    QTextEdit *txtEdit; //�༭��

signals:
    void edited();
public slots:
    void calcChrNum();
public:
    QSpinBox *pageBox;
    QLabel *chrNumLabel;
    QLabel *muLabel;

    void screenCardParaChangeProc();
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CsimpleTextEdit1(QWidget *parent =0);
    ~CsimpleTextEdit1();

};

//��Ŀ���Դ�
class CtxtProperty:public QWidget
{
    Q_OBJECT
public slots:
    void edited();
private:

    QGroupBox *txtPropertyGroup; //����

    QLabel *textLabel;  //�ı�

    //Ctemp *tempStyle;
    CshowModeEdit *showModeEdit;
    //QTextEdit *textEdit; //��ʾ�ı�
    //QPushButton *editButton; //�༭��ť
    CborderEdit *borderEdit;


public:

    CnameEdit *nameEdit;
    Carea *area;
    CsimpleTextEdit1 *simpleTextEdit;
    void connectSignal();
    void disconnectSignal();
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    void screenCardParaChangeProc();
    CtxtProperty(QWidget *parent=0);
    ~CtxtProperty();
};

void getTxtParaFromSettings(QString str, U_File_Para &para);
void updateTxtShowArea(CshowArea *area);
INT16U getTxtData(QString str, INT8U *pDst, INT32U dstLen);
//void Get_Temp_Text_Point(INT8U Area_No, INT16U Width, INT16U Height, S_Point &P0);
#endif // TXTPROPERTY_H
