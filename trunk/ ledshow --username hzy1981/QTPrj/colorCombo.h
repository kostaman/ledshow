#ifndef COLORCOMBO_H
#define COLORCOMBO_H

#include <QObject>
#include <QWidget>
#include <QComboBox>

#define RED_INDEX 0
#define YEL_INDEX 1
#define GRE_INDEX 2

class CsizeCombo:public QComboBox
{
    Q_OBJECT
public:
    CsizeCombo(QWidget *parent = 0);
    ~CsizeCombo();

};

class CcolorCombo:public QComboBox
{
    Q_OBJECT
public:
    CcolorCombo(QWidget *parent = 0);
    ~CcolorCombo();
};

#endif // COLORCOMBO_H