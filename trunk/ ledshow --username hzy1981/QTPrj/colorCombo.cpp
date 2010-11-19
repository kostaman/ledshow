#include "colorCombo.h"

CcolorCombo::CcolorCombo(QWidget *parent):QComboBox(parent)
{
    addItem(tr("��ɫ"));
    addItem(tr("��ɫ"));
    addItem(tr("��ɫ"));
}

QColor CcolorCombo::getColor()
{
    QColor col;

    if(currentIndex() == 0)
        col = QColor(Qt::red);
    else if(currentIndex() == 1)
        col = QColor(Qt::green);
    else
        col = QColor(Qt::yellow);

    return col;
}

CcolorCombo::~CcolorCombo()
{

}

CsizeCombo::CsizeCombo(QWidget *parent):QComboBox(parent)
{
    addItem(tr("16"));
    addItem(tr("24"));
    addItem(tr("32"));
}

CsizeCombo::~CsizeCombo()
{

}
