#ifndef SCREENPROPERTY_H
#define SCREENPROPERTY_H


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
#include <QSlider>
#include <QRadioButton>
#include "showArea.h"
#include "areaProperty.h"

//#define LIGHT

/*
class CipInput:public QGroupBox
{
  Q_OBJECT

  QLineEdit *inputEdit[4];
signals:
    void edited();
public:
  INT32U getInputIP();
  CipInput(QWidget *parent=0);
  ~CipInput();

};
*/


//��ʱ���ػ�����
class CopenCloseProperty:public QWidget
{
    Q_OBJECT
    //QRadioButton *manualButton;
    //QRadioButton *timerButton;
signals:
    void TimeEditSignal();
public slots:
    void allEditSlot();
public:
    void timeCheckProc();
    QCheckBox *timeCheck[MAX_OPEN_CLOSE_TIME];
    QTimeEdit *openTimeEdit[MAX_OPEN_CLOSE_TIME];
    QTimeEdit *closeTimeEdit[MAX_OPEN_CLOSE_TIME];
    //QSlider *timerSlider[MAX_LIGHTNESS_TIME];

    //QSlider *manualSlider;
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CopenCloseProperty(QWidget *parent=0);
    ~CopenCloseProperty();
};

//���ȵ���
class ClightnessProperty:public QWidget
{
    Q_OBJECT
    QRadioButton *manualButton;
    QRadioButton *timerButton;
    QRadioButton *autoButton;
signals:
    void adjModeEditSignal();
    void allEditSignal();
public slots:
    void adjModeEditSlot();
    void allEditSlot();
public:
    QCheckBox *timerCheck[MAX_LIGHTNESS_TIME];
    QTimeEdit *timerEdit[MAX_LIGHTNESS_TIME];
    QSlider *timerSlider[MAX_LIGHTNESS_TIME];
    QLabel *timerLabel[MAX_LIGHTNESS_TIME];

    QSlider *manualSlider;
    QLabel *manualLabel;

    QLabel *autoLabel;
    void sliderEditProc();
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    ClightnessProperty(QWidget *parent=0);
    ~ClightnessProperty();
};
//screen���Դ�
class CfacScreenProperty:public QWidget
{
    Q_OBJECT
public slots:
 void lockParaProc();
 public:
 QWidget *cardGroup;
 QWidget *comParaGroup;
 QWidget *baseParaGroup;
 QWidget *advanceParaGroup;
 QWidget *readParaGroup;

 QComboBox *cardCombo; //ѡ������
 QTextEdit *cardParaEdit; //������

 //ͨ�Ų���
 QLineEdit *screenIDEdit; // ��ĻID
 QLineEdit *newScreenIDEdit; //������ĻID
 QComboBox *comModeCombo; //ͨ�ŷ�ʽ
 QComboBox *baudCombo; //������
 QComboBox *ipModeCombo; //IP��ȡ��ʽ
 QLineEdit *ipEdit; //IP��ַ
 QLineEdit *newIpEdit; //��IP��ַ
 QLineEdit *maskEdit; //��������
 QLineEdit *gateEdit; //��������
 //��������

 QComboBox *dataPolarityCombo; //���ݼ���
 QComboBox *oePolarityCombo; //OE����
 QComboBox *colorCombo; //��ɫ
 QLineEdit *widthEdit; //����
 QLineEdit *heightEdit; //����
 QCheckBox *_138Check;     //�Ƿ���138������
 QComboBox *scanModeCombo; //ɨ�跽ʽ

 //�߼�����
 QCheckBox *defParaCheck; //ʹ��Ĭ�ϲ���
 QComboBox *freqCombo; //ɨ��Ƶ��
 QSpinBox *lineHideBox; //��������
 QComboBox *dataMirrorCombo; //���ݾ���
 QComboBox *lineOrderCombo; //��˳��
 //------------------

 //�������
 QTextEdit *readParaEdit;
 QPushButton *readParaButton;
 QPushButton *importParaButton;

 QPushButton *lockParaButton;
 QPushButton *sendButton;
 QPushButton *exportButton;
 //QPushButton *defButton;

 void setEditEnable(bool flag);
    //void getSettingsFromWidget(QString str);
    //void setSettingsToWidget(QString str);
    CfacScreenProperty(QWidget *parent=0);
    ~CfacScreenProperty();
};

//screen���Դ�
class CsetFacPara:public QMainWindow
{
    Q_OBJECT
    CfacScreenProperty *facScreenProperty;
public:
    //void getSettingsFromWidget(QString str);
    //void setSettingsToWidget(QString str);
    CsetFacPara(QWidget *parent=0);
    ~CsetFacPara();
};

//screen���Դ�
class CscreenProperty:public QWidget
{
    Q_OBJECT
    CnameEdit *nameEdit;
    CfacScreenProperty *facProperty;
    ClightnessProperty *lightnessProperty;
    CopenCloseProperty *openCloseProperty;
public:
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CscreenProperty(QWidget *parent=0);
    ~CscreenProperty();
};

INT8U getScreenParaFromSettings(QString screenStr, S_Screen_Para &screenPara);
#endif // SCREENPROPERTY_H
