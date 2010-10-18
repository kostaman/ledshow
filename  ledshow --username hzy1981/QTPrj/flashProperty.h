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


//flash���Դ�
class CflashProperty:public QWidget
{
    Q_OBJECT
private:
    QGroupBox *groupBox;
    QLabel *flashSourceLabel; //flashԴ��־
    QLineEdit *flashSourceEdit; //flashԴ�༭��
    QPushButton *openButton; //�򿪰�ť

    QLabel *frameNumLabel; //֡����־
    QLineEdit *frameNumEdit; //֡���༭
    QLabel *runSpeedLabel; //�����ٶȱ�־
    QLineEdit *runSpeedEdit; //�����ٶȱ༭
    QLabel *speedUnitLabel; //�ٶȵ�λ

    QLabel *totalFrameNumLabel; //��֡��


public:
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CflashProperty(QWidget *parent=0);
    ~CflashProperty();
};

#endif // FLASHPROPERTY_H
