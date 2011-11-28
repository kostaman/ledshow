#ifndef IMAGEPROPERTY_H
#define IMAGEPROPERTY_H

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


//image���Դ�
class CimageProperty:public QWidget
{
    Q_OBJECT
private:
    QGroupBox *groupBox;
    QLabel *imageSourceLabel; //imageԴ��־
    QLineEdit *imageSourceEdit; //imageԴ�༭��
    QPushButton *openButton; //�򿪰�ť

    //QLabel *totalFrameNumLabel; //��֡��
    //QLineEdit *totalFrameNumEdit; //��

    //QLabel *frameNumLabel; //֡����־
    //QSpinBox *frameNumEdit; //֡���༭

    //QLabel *runSpeedLabel; //�����ٶȱ�־
    //QComboBox *runSpeedCheck; //�����ٶȱ༭
    //QLineEdit *stayTimeEdit;
    //QLabel *speedUnitLabel; //�ٶȵ�λ
    CimageSize *imageSize;
    CborderEdit *borderEdit;
    CshowModeEdit *showModeEdit;
public slots:
    void openImageFile();
    void edited();
public:
    Carea *area;
    CnameEdit *nameEdit;
    void connectSignal();
    void disconnectSignal();
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CimageProperty(QWidget *parent=0);
    ~CimageProperty();
};

void getImageParaFromSettings(QString str, U_File_Para &para);
void updateImageShowArea(CshowArea *area);
QSize getImageShowData(QImage image, S_Show_Data *pDst, INT8U Area_No, INT16U x, INT16U y);
void getImagePageShowData(QString str, INT8U page, S_Show_Data *pDst, INT8U Area_No, INT16U x, INT16U y, INT16U width, INT16U height);
int getImageFrameCount(QString str);

#endif // IMAGEPROPERTY_H
