#include "tempProperty.h"

//������ʱ�༭
CtempProperty::CtempProperty(QWidget *parent):QWidget(parent)
{
    QGridLayout *gridLayout,*mainLayout;

    gridLayout = new QGridLayout(this);
    mainLayout = new QGridLayout(this);

    area = new Carea(this);
    textGroup = new QGroupBox(tr("�̶��ı�"), this);
    simpleTextEdit = new CsimpleTextEdit(this);

    gridLayout -> addWidget(simpleTextEdit, 0, 0);
    //gridLayout -> addWidget(editButton, 1, 0);
    textGroup -> setLayout(gridLayout);
    mainLayout->addWidget(area, 0, 0);
    mainLayout->addWidget(textGroup, 0, 1);
    setLayout(mainLayout);
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
