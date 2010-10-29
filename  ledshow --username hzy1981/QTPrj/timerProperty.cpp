#include "timerProperty.h"

//������ʱ�༭
CtimerProperty::CtimerProperty(QWidget *parent):QWidget(parent)
{
    QGridLayout *gridLayout,*mainLayout;

    gridLayout = new QGridLayout(this);
    mainLayout = new QGridLayout(this);

    area = new Carea(this);
    mainLayout->addWidget(area, 0, 0);
    textGroup = new QGroupBox(tr("�̶��ı�"), this);
    simpleTextEdit = new CsimpleTextEdit(this);

    gridLayout -> addWidget(simpleTextEdit, 0, 0);
    //gridLayout -> addWidget(editButton, 1, 0);
    textGroup -> setLayout(gridLayout);

    mainLayout -> addWidget(textGroup, 0, 1);
    gridLayout = new QGridLayout(this);
    dstTimeGroup = new QGroupBox(tr("Ŀ��ʱ��༭"), this);
    dstTimeLabel = new QLabel(tr("Ŀ��ʱ��"), this);
    styleLabel = new QLabel(tr("��ʽ"), this);
    colorLabel = new QLabel(tr("��ɫ"), this);
    fontSizeLabel = new QLabel(tr("��С"), this);
    dstDateTimeEdit = new QDateTimeEdit(this);
    colorCombo = new CcolorCombo(this);
    styleCombo = new QComboBox(this);
    fontSizeCombo = new QComboBox(this);
    gridLayout -> addWidget(dstTimeLabel, 0, 0);
    gridLayout -> addWidget(dstDateTimeEdit, 0, 1);
    gridLayout -> addWidget(colorLabel, 0, 2);
    gridLayout -> addWidget(colorCombo, 0, 3);
    gridLayout -> addWidget(styleLabel, 1, 0);
    gridLayout -> addWidget(styleCombo, 1, 1);
    gridLayout -> addWidget(fontSizeLabel, 1, 2);
    gridLayout -> addWidget(fontSizeCombo, 1, 3);
    dstTimeGroup -> setLayout(gridLayout);


    mainLayout -> addWidget(dstTimeGroup, 0, 2);
    setLayout(mainLayout);
}

CtimerProperty::~CtimerProperty()
{

}

void CtimerProperty::getSettingsFromWidget(QString str)
{

}

void CtimerProperty::setSettingsToWidget(QString str)
{

}
