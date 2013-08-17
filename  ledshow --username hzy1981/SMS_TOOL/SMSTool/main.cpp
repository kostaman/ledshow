#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //����Ϊ֧������---��Ҫ
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb2312"));
    QFont font(QObject::tr("������"),9,QFont::Normal,FALSE);
    a.setFont(font);

    MainWindow w;
    w.show();
    
    return a.exec();
}
