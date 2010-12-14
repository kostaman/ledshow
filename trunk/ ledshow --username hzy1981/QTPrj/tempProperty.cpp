#include "tempProperty.h"

//������ʱ�༭
CtempProperty::CtempProperty(QWidget *parent):QWidget(parent)
{
    //QGridLayout *gridLayout,*mainLayout;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;

    hLayout = new QHBoxLayout(this);
    vLayout = new QVBoxLayout(this);

    nameEdit = new CnameEdit(this);
    area = new Carea(this);
    vLayout->addWidget(nameEdit);
    vLayout->addWidget(area);
    hLayout->addLayout(vLayout);
    //textGroup = new QGroupBox(tr("�̶��ı�"), this);
    simpleTextEdit = new CsimpleTextEdit(this);
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(simpleTextEdit);
    hLayout->addLayout(vLayout);
    hLayout->addStretch(10);
    setLayout(hLayout);
}

CtempProperty::~CtempProperty()
{

}

void CtempProperty::getSettingsFromWidget(QString str)
{

}

void CtempProperty::setSettingsToWidget(QString str)
{

}
