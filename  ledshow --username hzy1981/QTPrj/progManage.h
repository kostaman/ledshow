#ifndef PROGMANAGE_H
#define PROGMANAGE_H

#include <QtGui/QMainWindow>
#include <QDockWidget>
#include <QTreeWidget>
#include <QTreeView>
#include <QTreeWidgetItem>
#include <QList>
#include <QVariant>
#include <QTimer>
#include <showArea.h>

#define FILE_TYPE 1
#define AREA_TYPE 2
#define PROG_TYPE 3
#define NULL_TYPE 0

#define PROG_STR "program"
#define AREA_STR "area"
#define FILE_STR "file"

#define NULL_PROPERTY   0xFF
#define SCREEN_PROPERTY 0x00
#define PROG_PROPERTY   0x01
#define AREA_PROPERTY   0x02
#define PIC_PROPERTY    0x03 //ͼƬ
#define CLOCK_PROPERTY  0x05 //����
#define TIME_PROPERTY   0x06 //����ʱ��
#define TIMER_PROPERTY  0x07 //��ʱ
#define TEMP_PROPERTY   0x08 //�¶�
#define LUN_PROPERTY    0x09    //ũ��
#define HUMIDITY_PROPERTY 0x0A //ʪ��
#define NOISE_PROPERTY 0x0B //����

#define PIC_TABLE_PROPERTY  0x30
#define PIC_FLASH_PROPERTY  0x31 //����
#define PIC_MTEXT_PROPERTY  0x32
#define PIC_STEXT_PROPERTY  0x33

#define SUB_INDEX_EN 0


//��Ŀ����
class CprogManage:public QDockWidget
{
    Q_OBJECT
private:
    //QString settingsStr;
    QTreeWidgetItem *curItem;
    //QTreeWidget *treeWidget;
    void newFile(int fileType, int subType); //���ļ�

public slots:
    void newScreen(); //����Ļ
    void newProg(); //�½�Ŀ
    void newArea(); //�·���

    void newSText(); //��Ļ
    void newPic(); //��ͼ��
    void newFlash(); //�¶���
    void newTime(); //������
    void newTimer(); //�¼�ʱ
    void newClock(); //�±���
    void newTemp(); //���¶�
    void newLun(); //��ũ��
    void newHumidity(); //��ʪ��
    void newNoise(); //������

    void _deleteItem(int flag);
    void deleteItem();
    void clickItem(QTreeWidgetItem * item, int column);
    void currentItemChangedProc(QTreeWidgetItem * current, QTreeWidgetItem * previous);

public:
    /*
    QMainWindow *previewWin;
    CscreenArea *previewArea;
    QTimer *timer;
    int timerFlag;
    INT8U previewProgNo;
*/
    void updateTextHead(QTreeWidgetItem *item); //���º�itemͬ��������item���ı�ͷ
    QTreeWidgetItem *getCurItem();
    void saveCurItem(QTreeWidgetItem *item);



    QTreeWidget *treeWidget;
    void settingsInit(); //��settings
    CprogManage(QWidget *parent = 0);
    ~CprogManage();
};
int checkItemType(QTreeWidgetItem *item);
int checkStrType(QString str);
#endif // PROGMANAGE_H
