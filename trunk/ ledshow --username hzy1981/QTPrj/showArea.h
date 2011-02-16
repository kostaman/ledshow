#ifndef SHOWAREA_H
#define SHOWAREA_H

//#include "..\LED_Cfg.h"
//#include "..\LED_Para.h"
//#include "..\LED_Show.h"
#include "..\Includes.h"
#include <QtGui/QMainWindow>
#include <QFrame>
#include <QLabel>
#include <Qmouseevent>
#include <QPainter>
#include <QTreeWidgetItem>
#include <QMdiSubWindow>

#define DRAG_MOVE  0x00
//#define DRAG_FDIAG 0x01
//#define DRAG_HOR   0x02
//#define DRAG_VER   0x03

#define DRAG_L   0x01
#define DRAG_LU  0x02
#define DRAG_LD  0x03
#define DRAG_R   0x04
#define DRAG_RU  0x05
#define DRAG_RD  0x06
#define DRAG_U   0x07
#define DRAG_D   0x08

#define RED    0x01
#define GREEN  0x02
#define YELLOW 0x03
#define BLUE   0x04  //SCREEN����
#define BLACK  0x05  //AREA����

//#define AREA_POINTS 5000
#define ANTIALIAS_VALUE 0x50

#define MIN_AREA 10

class CshowArea:public QWidget
{
    Q_OBJECT
private:
    //int width,height;

    //QPainter *Painter;
    QPoint dragPosition;
    QPoint framePosition;
    QSize oldSize;

    //unsigned char color0[MAX_POINTS/8];
    //unsigned char color1[MAX_POINTS/8];
    //unsigned char color2[MAX_POINTS/8];


    int dragFlag;
    bool mousePressed;

    int areaType; //0��ʾ������Ļ��1��ʾ����
    //int last_x; //�϶�ʱǰһ��λ��
    //int last_y; //
    //QPixmap *Pixmap;
    QPainter painter;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
public:
    bool updateFlag;
    S_Show_Data showData;
    int previewFlag; //0��ʾ���������ڣ�1��ʾ��Ԥ������

    //S_Show_Data showDataBak;
    QImage imageBk;

    //-----------ͼ�Ĳ���----------//
    QString picStr; //��ʾ���ı�
    bool smLineFlag; //�����б�־
    bool moveLeftFlag; //�������Ʊ�־
    int page;  //��ʾ��ҳ��
    //--------------------
    S_Screen_Para screenPara; //��Ļ����
    S_Prog_Para progPara; //��Ŀ����

    //-----------------------
    U_File_Para filePara; //�÷�������ʾ����
    int color;
    bool focusFlag;
    int getColor();

    QTreeWidgetItem *screenItem;
    QTreeWidgetItem *progItem;
    QTreeWidgetItem *areaItem; //��Ӧ��treeitem
    QTreeWidgetItem *fileItem; //��Ӧ���ļ�item

    //int getWidth();
    //int getHeight();

    void draw_point(int x,int y, int value);
    void setAreaType(int type);
    CshowArea(QWidget *parent = 0, int i = 0);
    ~CshowArea();
};

class CscreenArea:public CshowArea
{
    Q_OBJECT
private:
    int x0,y0; //�½�һ������ʱ��λ��

    CshowArea *focusArea;


public:

    CshowArea *pArea[MAX_AREA_NUM];
    //U_File_Para File_Para[MAX_AREA_NUM]; //��ǰ�������ļ������������ļ�ʱˢ��֮

    QTreeWidgetItem *pTreeWidgetItem[MAX_AREA_NUM];
    int areaUsed[MAX_AREA_NUM];

    void updateShowArea(QTreeWidgetItem *item);
    void screenSettingsInit(QTreeWidgetItem *item);
    void areaSettingsInit(QTreeWidgetItem *item);
    void progSettingsInit(QTreeWidgetItem *item);
    void fileSettingsInit(QTreeWidgetItem *item);

    int checkEnoughArea(); //���ʣ���㹻�Ŀ���ʾ�������򷵻����������򷵻�false
    CshowArea *getFocusArea(); //��ǰ����ʾ����
    void setFocusArea(CshowArea *area);

    void progChangedProc(QString settingsStr);

    //int setOneAreaVisible(QString settingsStr);
    void setAreaVisible(int index, bool flag);

    QString getCurrentFileStr();
    CshowArea * newShowArea();
    CscreenArea(QWidget *parent = 0);
    ~CscreenArea();

};

class CMdiSubWindow:public QMdiSubWindow
{
        Q_OBJECT
protected:
    void closeEvent(QCloseEvent *closeEvent);
public:
    int previewFlag;

    CMdiSubWindow(QWidget *parent = 0);
    ~CMdiSubWindow();
};

class CpreviewWin:public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *closeEvent);
public:
    //int previewFlag;

    CpreviewWin(QWidget *parent = 0);
    ~CpreviewWin();
};

INT8U Get_Border_Show_En();
INT8U Get_Clock_Show_En();
INT8U Get_Pic_Show_En();
INT8U Get_Lun_Show_En();
INT8U Get_Temp_Show_En();
INT8U Get_Time_Show_En();
INT8U Get_Timer_Show_En();
INT8U Get_Humidity_Show_En();
INT8U Get_Noise_Show_En();
void saveScreenPara(S_Screen_Para &Screen_Para_Bak);
//�����Ŀ����Prog_Para��Prog_Para_Bak
void saveProgPara(S_Prog_Para &Prog_Para_Bak);
void saveCardPara(S_Card_Para &Card_Para_Bak);
//��Screen_Para_Bak�лָ�������Screen_Para
void restoreScreenPara(S_Screen_Para &Screen_Para_Bak);
//��Prog_Para_Bak�лָ�������Prog_Para
void restoreProgPara(S_Prog_Para &Prog_Para_Bak);
void resetShowPara(int width, int height, int color);
void restoreCardPara(S_Card_Para &Card_Para_Bak);
#endif // MAINWINDOW_H
