#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QTextCodec>
#include "mainwindow.h"
#include "textedit.h"

MainWindow *w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //����Ϊ֧������---��Ҫ

    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb2312"));
    QFont font(QObject::tr("������"),9,QFont::Normal,FALSE);
    a.setFont(font);

/*
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb2312"));
    QFont font("wenquanyi_120_50"); //ʹ��wenquanyi����
    a.setFont(font); //��������
*/

    w = new MainWindow;
    QRect desktopRect = QApplication::desktop()->availableGeometry();
    int iTitleBarHeight = w->style()->pixelMetric(QStyle::PM_TitleBarHeight);  // ��ȡ�������߶�

    w->setGeometry(0, iTitleBarHeight, desktopRect.width(), desktopRect.height() - iTitleBarHeight);  // ���ô����������ͻ���
    w->setFixedSize(desktopRect.width(), desktopRect.height() - iTitleBarHeight);      // �̶������С

    if(w->progManage->treeWidget->topLevelItemCount()>0)
      w->progManage->clickItem(w->progManage->treeWidget->topLevelItem(0), 0);
    //w->progManage->newProg();
    //w->progManage->newArea();
    w->show();

    return a.exec();

/*
    TextEdit mw;
    mw.resize( 700, 800 );
    mw.show();
    return a.exec();
    */
}
