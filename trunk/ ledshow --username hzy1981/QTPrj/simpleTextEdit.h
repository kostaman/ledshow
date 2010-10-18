#ifndef SIMPLETEXTEDIT_H
#define SIMPLETEXTEDIT_H

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFontComboBox>
#include "colorCombo.h"
#include "..\Includes.h"

class CsimpleTextEdit :public QWidget
{
    Q_OBJECT
private:
    QLabel *fontLabel; //����
    QLabel *fontSizeLabel; //�����С
    QLabel *colorLabel; //��ɫ

    QFontComboBox *fontCombo;
    QComboBox *fontSizeCombo;
    CcolorCombo *colorCombo;

    QPushButton *bButton; //�Ӻ�
    QPushButton *iButton; //б��
    QPushButton *uButton; //����
    //QPushButton *oButton; //��

    QLineEdit *lineEdit; //�༭��
public:
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CsimpleTextEdit(QWidget *parent =0);
    ~CsimpleTextEdit();

};

QImage getTextImage(QString str);
QSize getTextShowData(QImage image, S_Show_Data *pDst, INT16U x, INT16U y);
#endif // SIMPLETEXTEDIT_H
