#include "flashProperty.h"
/*
//flash���Դ�
class CflashProperty:public QWidget
{
    Q_OBJECT
private:
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
    CflashProperty(QWidget *parent=0);
    ~CflashProperty();
};
*/
//flash���Ա༭
CflashProperty::CflashProperty(QWidget *parent):QWidget(parent)
{

    QGridLayout *gridLayout = new QGridLayout(this);
    groupBox = new QGroupBox(this);

   flashSourceLabel = new QLabel(tr("��ȡԴ"), this);
   flashSourceEdit = new QLineEdit(this);
   openButton = new QPushButton(tr("��"), this);

   frameNumLabel = new QLabel(tr("֡��"), this);
   frameNumEdit = new QLineEdit(this);
   runSpeedLabel = new QLabel(tr("�����ٶ�"), this);
   speedUnitLabel = new QLabel(tr("΢��"), this);

   totalFrameNumLabel = new QLabel(tr("��֡��"), this);

   gridLayout->addWidget(flashSourceLabel, 0, 0);
   gridLayout->addWidget(flashSourceEdit, 0, 1);
   gridLayout->addWidget(openButton, 0, 2);
   gridLayout->addWidget(frameNumLabel, 1, 0);
   gridLayout->addWidget(frameNumEdit, 1, 1);
   gridLayout->addWidget(runSpeedLabel, 1, 2);
   gridLayout->addWidget(speedUnitLabel, 1, 3);
   gridLayout->addWidget(totalFrameNumLabel, 3, 0);
   groupBox->setLayout(gridLayout);
}

CflashProperty::~CflashProperty()
{

}

void CflashProperty::getSettingsFromWidget(QString str)
{

}

void CflashProperty::setSettingsToWidget(QString str)
{

}


