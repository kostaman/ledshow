#ifndef PROGMANAGE_H
#define PROGMANAGE_H

#include <QtGui/QMainWindow>
#include <QDockWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QList>
#include <QVariant>

#define FILE_TYPE 1
#define AREA_TYPE 2
#define PROG_TYPE 3
#define NULL_TYPE 0

#define PROG_STR "program"
#define AREA_STR "area"
#define FILE_STR "file"

#define PROG_PROPERTY 0x00
#define AREA_PROPERTY 0x01
#define PIC_PROPERTY    0x02 //ͼƬ
#define FLASH_PROPERTY  0x03 //����
#define CLOCK_PROPERTY  0x04 //����
#define TIME_PROPERTY   0x05 //����ʱ��
#define TIMER_PROPERTY  0x06 //��ʱ
#define TEMP_PROPERTY   0x07 //�¶�



//��Ŀ����
class CprogManage:public QDockWidget
{
    Q_OBJECT
private:
    //QString settingsStr;
    QTreeWidgetItem *curItem;
    //QTreeWidget *treeWidget;
    void newFile(int fileType); //���ļ�
    void updateTextHead(QTreeWidgetItem *item); //���º�itemͬ��������item���ı�ͷ

private slots:
    void newProg(); //�½�Ŀ
    void newArea(); //�·���

    void newPic(); //��ͼ��
    void newFlash(); //�¶���
    void newTime(); //������
    void newTimer(); //�¼�ʱ
    void newClock(); //�±���
    void newTemp(); //���¶�

    void deleteItem();
    void clickItem(QTreeWidgetItem * item, int column);
public:
    QTreeWidgetItem *getCurItem();
    void saveCurItem(QTreeWidgetItem *item);

    QTreeWidget *treeWidget;
    void settingsInit(); //��settings
    CprogManage(QWidget *parent = 0);
    ~CprogManage();
};


#endif // PROGMANAGE_H
