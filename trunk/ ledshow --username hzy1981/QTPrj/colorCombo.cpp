#include "colorCombo.h"

CcolorCombo::CcolorCombo(QWidget *parent):QComboBox(parent)
{
    addItem(tr("��ɫ"));
    addItem(tr("��ɫ"));
    addItem(tr("��ɫ"));
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
