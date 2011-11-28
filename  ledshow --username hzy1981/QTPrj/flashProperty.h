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
    //QComboBox *runSpeedCheck; //�����ٶȱ༭
    QLineEdit *stayTimeEdit;
    QLabel *speedUnitLabel; //�ٶȵ�λ

    CimageSize *imageSize;
    CborderEdit *borderEdit;
public slots:
    void openFlashFile();
    void edited();
public:
    Carea *area;
    CnameEdit *nameEdit;
    void connectSignal();
    void disconnectSignal();
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CflashProperty(QWidget *parent=0);
    ~CflashProperty();
};

void getFlashParaFromSettings(QString str, U_File_Para &para);
void updateFlashShowArea(CshowArea *area);
QSize getFlashShowData(QImage image, S_Show_Data *pDst, INT8U Area_No, INT16U x, INT16U y);
void getFlashPageShowData(QString str, INT8U page, S_Show_Data *pDst, INT8U Area_No, INT16U x, INT16U y, INT16U width, INT16U height);
int getFlashFrameCount(QString str);
#endif // FLASHPROPERTY_H
