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

#define NEW_SCN 0x00  //�½���Ļ
#define MODI_SCN 0x01 //�޸���Ļ
#define SHOW_SCN 0x02 //��ʾ��Ļľ
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

class CipInput:public QWidget
{
    Q_OBJECT

public:
    QLineEdit *edit;

    int getIP();
    void setIP(int ip);

    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);

    CipInput(QWidget *parent=0);
    ~CipInput();
};

class CcomTest:public QGroupBox
{
    Q_OBJECT

public:
    QComboBox *comModeCombo; //ͨ�ŷ�ʽ
    QSpinBox *screenIDEdit; //��ĻID��Ӳ����ַ
    QComboBox *comPortEdit; //���ں�
    QComboBox *comBaudCombo; //������
    CipInput *ipEdit; //IP��ַ
    QPushButton *connectButton; //���Ӱ�ť

    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);

    CcomTest(QWidget *parent=0);
    ~CcomTest();
};

//��ʱ���ػ�����
class CopenCloseProperty:public QGroupBox
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
class ClightnessProperty:public QGroupBox
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
class CfacScreenProperty:public QGroupBox
{
    Q_OBJECT
public slots:
 void endProc(); //�������
 void loadParaProc(); //���ز���
 public:
 QTabWidget *tabWidget;

 QWidget *cardGroup;
 QWidget *netParaGroup;
 QWidget *baseParaGroup;
 QWidget *advanceParaGroup;
 QWidget *readParaGroup;

 QComboBox *cardCombo; //ѡ������
 QTextEdit *cardParaEdit; //������

 //ͨ�Ų���

 //QComboBox *ipModeCombo; //IP��ȡ��ʽ
 //QLineEdit *ipEdit; //IP��ַ
 CipInput *ipEdit;
 //QLineEdit *newIpEdit; //��IP��ַ
 CipInput *maskEdit; //��������
 CipInput *gateEdit; //��������
 CipInput *macEdit; //mac��ַ
 //��������
 QSpinBox *screenIDEdit; // ��ĻID
 QComboBox *baudCombo; //������
 QCheckBox *redGreenRevCheck; //����
 QComboBox *dataPolarityCombo; //���ݼ���
 QComboBox *oePolarityCombo; //OE����

 QComboBox *colorCombo; //��ɫ
 QSpinBox *widthEdit; //����
 QSpinBox *heightEdit; //����
 QCheckBox *_138Check;     //�Ƿ���138������
 QComboBox *scanModeCombo; //ɨ�跽ʽ

 //�߼�����
 QCheckBox *defParaCheck; //ʹ��Ĭ�ϲ���
 QComboBox *freqCombo; //ɨ��Ƶ��
 QComboBox *lineHideCombo; //��������
 QComboBox *dataMirrorCombo; //���ݾ���
 QComboBox *lineOrderCombo; //��˳��
 //------------------

 CcomTest *comTest;
 //�������
 QTextEdit *readParaEdit;
 QPushButton *readParaButton;
 QPushButton *importParaButton;

 QPushButton *endButton;
 QPushButton *loadButton;
 QPushButton *exportButton;
 //QPushButton *defButton;
 int paraFlag; //��ʾ�½���Ļ��1��ʾ�޸���Ļ��2��ʾ��ʾ��Ļ
 void setEditEnable(bool flag);
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CfacScreenProperty(int flag, QWidget *parent=0);
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
signals:
    void editSignal();
public:
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CscreenProperty(QWidget *parent=0);
    ~CscreenProperty();
};

INT8U getScreenParaFromSettings(QString screenStr, S_Screen_Para &screenPara);
#endif // SCREENPROPERTY_H
