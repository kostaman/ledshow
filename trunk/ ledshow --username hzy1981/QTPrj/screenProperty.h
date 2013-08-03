#ifndef SCREENPROPERTY_H
#define SCREENPROPERTY_H


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

class CipInput:public QLineEdit
{
    Q_OBJECT
signals:
    void editSignal();
public:
    //QLineEdit *edit;
    INT32U getIP();
    void setIP(INT32U ip);

    //QString ipToStr(INT8U ip);
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);

    CipInput(QWidget *parent=0);
    ~CipInput();
};

class CcomTest:public QGroupBox
{
    Q_OBJECT
signals:
    void editSignal();
public slots:
    void editSlot();
    void autoConnect();
    void manualConnect();
    void cardChangedProc(QString cardName);
    void comModeChangedProc();
public:
    QComboBox *comModeCombo; //ͨ�ŷ�ʽ
    QSpinBox *screenIDEdit; //��ĻID��Ӳ����ַ
    QLabel *comPortLabel;
    QComboBox *comPortEdit; //���ں�
    QComboBox *comBaudCombo; //������
    QLabel *comBaudLabel;
    CipInput *ipEdit; //IP��ַ
    QLabel *ipEditLabel;
    QPushButton *manualConnectButton; //���Ӱ�ť
    QPushButton *autoConnectButton; //���԰�ť
    QLabel *comPortInfoLabel;

    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    void setSettingsToScreePara(QString str, S_Screen_Para &screenPara);

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

class ClightnessDialog:public QDialog
{
    Q_OBJECT
public slots:
    void sendPara(); //���Ͳ���
    void udiskPara(); //����u���ļ�
public:
    ClightnessProperty *lightnessProperty;
    QPushButton *sendButton;
    QPushButton *udiskButton;
    QPushButton *cancelButton;

    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    ClightnessDialog(QWidget *parent=0);
    ~ClightnessDialog();
};

class CopenCloseDialog:public QDialog
{
    Q_OBJECT
public slots:
    void sendPara(); //���Ͳ���
    void udiskPara(); //����u���ļ�
public:
    CopenCloseProperty *openCloseProperty;
    QPushButton *sendButton;
    QPushButton *udiskButton;
    QPushButton *cancelButton;

    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CopenCloseDialog(QWidget *parent=0);
    ~CopenCloseDialog();
};

class CadjTimeProperty:public QGroupBox
{
    Q_OBJECT
public slots:
    void adjTimeModeCheck();
public:
    //QDateTimeEdit *dateTimeEdit;
    //QPushButton *sysTimeButton;
    QRadioButton *sysTimeButton; //ϵͳʱ��
    QRadioButton *selfTimeButton; //�Զ����¼�
    QDateTimeEdit *dateTimeEdit;

    QDateTime getDateTime();
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CadjTimeProperty(QWidget *parent=0);
    ~CadjTimeProperty();
};

class CadjTimeDialog:public QDialog
{
    Q_OBJECT
public slots:
    void sendData();
    void udiskData();
public:
    CadjTimeProperty *adjTimeProperty;

    QPushButton *sendButton;
    QPushButton *udiskButton;
    QPushButton *cancelButton;

    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CadjTimeDialog(QWidget *parent=0);
    ~CadjTimeDialog();
};

/*
class CsendProgDialog:public QDialog
{
    Q_OBJECT
public:
    QCheckBox *openCloseCheck;
    QCheckBox *lightnessCheck;
    QCheckBox *adjTimeCheck;

    CopenCloseProperty *openCloseProperty;
    ClightnessProperty *lightnessProperty;


    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CopenCloseDialog(QWidget *parent=0);
    ~CopenCloseDialog();
};
*/
class CsendDataDialog:public QDialog
{
    Q_OBJECT
public slots:
    void propertyCheckProc();
    void sendData(); //��������
    void uDiskData(); //����U��������
signals:
    void closeSignal();
public:
    QCheckBox *lightnessCheck; //���ȿ���
    QCheckBox *openCloseCheck; //���ػ�ʱ�ο���
    QCheckBox *adjTimeCheck;  //Уʱ����

    QPushButton *sendButton; //����
    QPushButton *udiskButton; //u��
    QPushButton *cancelButton; //ȡ��

    ClightnessProperty *lightnessProperty;
    CopenCloseProperty *openCloseProperty;
    CadjTimeProperty *adjTimeProperty;

    CsendDataDialog(int flag, QWidget *parent=0);
    ~CsendDataDialog();


};

class CudiskListDialog:public QDialog
{
    Q_OBJECT
public slots:
    void okButtonSlot();
signals:
    void closeSignal();
public:
    QPushButton *okButton;
    QComboBox *udiskCombo;
    QStringList udiskList;
    QString udiskName;

    void updateUdiskList();
    CudiskListDialog(QWidget *parent=0);
    ~CudiskListDialog();
};

//screen���Դ�
class CfacScreenProperty:public QGroupBox
{
    Q_OBJECT
private:
    S_Screen_Para readScreenPara;
    bool readScreenParaFlag;

public slots:
 void defParaCheckProc();
 void cardChangeProc();
 void endProc(); //�������
 void importParaProc(); //�������
 void readParaProc(); //�ض�����
 void setTestProc(); // �Լ�
 void comLoadParaProc(); //ͨ�ż��ز���
 void udiskLoadParaProc(); //U�̼��ز���
 void readCardType();
 public:
 QTabWidget *tabWidget;
 CcomTest *comTest;

 QWidget *cardGroup;
 QWidget *netParaGroup;
 QWidget *baseParaGroup;
 QWidget *advanceParaGroup;
 QWidget *readParaGroup;
 QWidget *scanParaGroup;

 QWidget *scanPicWidget;

 QComboBox *cardCombo; //ѡ������
 QPushButton *readCardTypeButton;
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
 QComboBox *scanModeCombo; //ɨ�跽ʽ

 //�߼�����
 QLabel *freqLabel;// = new QLabel(tr("ʱ��Ƶ��"),this);
 QLabel *lineHideLabel;// = new QLabel(tr("������"),this);
 QLabel *dataMirrorLabel;// = new QLabel(tr("���ݾ���"),this);
 QLabel *lineOrderLabel;// = new QLabel(tr("��˳��"),this);
 QLabel *_138Label;

 QCheckBox *defParaCheck; //ʹ��Ĭ�ϲ���
 QComboBox *freqCombo; //ɨ��Ƶ��
 QComboBox *lineHideCombo; //��������
 QComboBox *dataMirrorCombo; //���ݾ���
 QComboBox *lineOrderCombo; //��˳��
 QComboBox *_138Combo;     //�Ƿ���138������
 //------------------

 //CcomTest *comTest;
 //�������
 QTextEdit *readParaEdit;
 QPushButton *readParaButton;
 QPushButton *importParaButton;

 QPushButton *endButton;
 QPushButton *comLoadButton;
 QPushButton *udiskLoadButton;
 QPushButton *exportButton;
 QPushButton *selfTestButton;

 //QPushButton *defButton;
 int paraFlag; //��ʾ�½���Ļ��1��ʾ�޸���Ļ��2��ʾ��ʾ��Ļ
 int SendPara();
 void setEditEnable(bool flag);
  void loadParaProc(INT8U Mode); //���ز���
 void getScreenCardParaFromWidget(S_Screen_Para &screenPara, S_Card_Para &cardPara);
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CfacScreenProperty(int flag, CcomTest *comTest, QWidget *parent=0);
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
    //ClightnessProperty *lightnessProperty;
    //CopenCloseProperty *openCloseProperty;
signals:
    void editSignal();
public:
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CscreenProperty(QWidget *parent=0);
    ~CscreenProperty();
};

class CupdateFirmwareDialog:public QDialog
{
    Q_OBJECT

public slots:
    void updateFirmware(); //�����汾��
    bool readVersion(); //��ȡ�汾��
    void openFirmwareFile(); //�򿪹̼�����
    void makeFirmwareFile(); //��bin�ļ����ɹ̼��ļ�
    //void uDiskData(); //����U��������
//signals:
    //void closeSignal();
private:
    INT8U makeFlag; //���ɹ̼��ļ���־
    INT16U newFirmFrameCounts; //�����̼���֡����
public:
    QLineEdit *oldVersionEdit; //�ϵĳ���汾
    QLineEdit *newVersionEdit; //�������ĳ���汾

    QLineEdit *newFirmPath; //�¹̼�·��
    QPushButton *openButton; //�򿪹̼��ļ�����
    QPushButton *updateButton; //�̼���������
    QPushButton *readVersionButton; //��ȡ�汾������

    QPushButton *makeButton; //���ɳ���İ�ť

    char binFileData[500000];
    char fwbFileData[500000];

    CupdateFirmwareDialog(INT8U flag, QWidget *parent=0);
    ~CupdateFirmwareDialog();

};

class CInvalidDateDialog:public QDialog
{
  Q_OBJECT
private:
   QGroupBox *invalidDateGroup;
   QDateEdit *invalidDateEdit;  //��Ч����
   QPushButton *sendButton; //���Ͱ�ť
   QPushButton *udiskButton; //������ť
public slots:
    void sendPara(); //����
    void udiskPara(); //����
    void editSlot();
public:
    void getSettingsFromWidget(QString str);
    void setSettingsToWidget(QString str);
    CInvalidDateDialog(QWidget *parent =0);
    ~CInvalidDateDialog();
};

void comFailedProc();
void getComTestParaFromSettings(QString str, S_Screen_Para &screenPara);
INT8U getCardParaFromSettings(QString cardName, S_Card_Para &cardPara);
INT8U getScreenCardParaFromSettings(QString screenStr, S_Screen_Para &screenPara, S_Card_Para &cardPara);
#endif // SCREENPROPERTY_H
