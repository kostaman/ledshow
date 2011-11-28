#ifndef TABLEPROPERTYEDIT_H
#define TABLEPROPERTYEDIT_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QInputDialog>
#include <QRadioButton>
#include "colorCombo.h"

class CtablePropertyEdit:public QDialog
{
    Q_OBJECT
signals:
        void createTable(int rows, int colums, QTextTableFormat tableFormat);
        void updateTable(int rows, int colums, QTextTableFormat tableFormat);

public slots:
        void accept();
        void reject();
        void setProperties(int rows, int colums, QTextTableFormat tableFormat, bool newTable);

        void apply();
        //void changeColorTable();
        //void changeColorBorder();

private:
        void getTableFormat();
        bool modeNewTable;
        QTextTableFormat tFormat;
        QColor colorTable, colorBorder;
public:
   QSpinBox *rowsEdit;  //����
   QSpinBox *colsEdit;  //����
   QSpinBox *widthEdit; //���

   QComboBox *alignCombo; //���뷽ʽ

   QSpinBox *borderWidth; //�ڱ߿���
   CcolorCombo *borderColor; //�߿���ɫ
   QComboBox *borderStyle; //�߿�ʽ��

   //QSpinBox *marginWidth; //��߿���
   //CcolorCombo *marginColor;

   QSpinBox *marginBetweenCells;
   QSpinBox *marginInCells;

   QPushButton *applyButton;
   QPushButton *okButton;
   QPushButton *cancelButton;

    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CtablePropertyEdit(QWidget *parent=0);
    ~CtablePropertyEdit();
};

#endif // TABLEPROPERTYEDIT_H
