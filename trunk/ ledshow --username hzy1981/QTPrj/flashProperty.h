#ifndef FLASHPROPERTY_H
#define FLASHPROPERTY_H

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
#include <QSpinBox>
#include "showArea.h"
#include "areaProperty.h"


//flash���Դ�
class CflashProperty:public QWidget
{
    Q_OBJECT
private:
    QGroupBox *groupBox;
    QLabel *flashSourceLabel; //flashԴ��־
    QLineEdit *flashSourceEdit; //flashԴ�༭��
    QPushButton *openButton; //�򿪰�ť

    QLabel *totalFrameNumLabel; //��֡��
    QLineEdit *totalFrameNumEdit; //��

    QLabel *frameNumLabel; //֡����־
    QSpinBox *frameNumEdit; //֡���༭

    QLabel *runSpeedLabel; //�����ٶȱ�־
    QComboBox *runSpeedCheck; //�����ٶȱ༭
    QLabel *speedUnitLabel; //�ٶȵ�λ
public slots:
    void openFlashFile();
public:
    Carea *area;
    CnameEdit *nameEdit;
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CflashProperty(QWidget *parent=0);
    ~CflashProperty();
};

void getFlashParaFromSettings(QString str, U_File_Para &para);
void updateFlashShowArea(CshowArea *area);
QSize getFlashShowData(QImage image, S_Show_Data *pDst, INT16U x, INT16U y);
#endif // FLASHPROPERTY_H
