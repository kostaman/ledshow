/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/
/*
#include <QApplication>
#include <QtCore>

#include <stdlib.h>

#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dialog dialog;
    dialog.show();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return dialog.exec();
}
*/

//main.cpp

#include <QtGui>
#include <server.h>
#include <mainwindow.h>
#include <QSqlQuery>
#include <Qtsql>
/*
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� IOCPLIB_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// IOCPLIB_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef IOCPLIB_EXPORTS
#define IOCPLIB_API __declspec(dllexport)
#else
#define IOCPLIB_API __declspec(dllimport)
#endif

typedef LPVOID	HIOCP;
typedef LPVOID	IOCPOOL;
typedef UINT	SOCKET;

//	�ͻ��˽���
typedef void (__stdcall* ONACCEPT)(SOCKET,char*,unsigned int);

//	�ͻ����뿪
typedef void (__stdcall* ONCLOSE)(SOCKET,char*,unsigned int);

//	�ͻ������󵽴�
typedef void (__stdcall* ONRECV)(SOCKET,char*,unsigned int,BYTE*,int);

//	����һ��IOCP������ʵ�����ɹ�����ʵ�������ʧ�ܷ���NULL
IOCPLIB_API HIOCP WINAPI IocpCreate();

//	ɾ��һ���Ѿ����ڵķ�����ʵ��
IOCPLIB_API void WINAPI IocpDelete(HIOCP hIocp);

//	���÷���������ģʽ��0 ΪIOCP��IOCPЭ��ģʽ����ΪԭʼЭ��ģʽ����ônMode ������һ���������Ĵ�С
IOCPLIB_API void WINAPI IocpSetMode(HIOCP hIocp,int nMode);

//	���ûص�����
IOCPLIB_API void WINAPI IocpSetCallFun(HIOCP hIocp,ONACCEPT fn1, ONCLOSE fn2, ONRECV fn3);

//	ɾ��һ���Ѿ����ڵķ�����ʵ��
//	����˵��(ʵ�����,�����˿�,�����߳���,�����߳���)
IOCPLIB_API int WINAPI IocpStart(HIOCP hIocp,UINT nPort,UINT nAcceptThreadCount,UINT nWorkerThreadCount);

//	ֹͣ����
IOCPLIB_API void WINAPI IocpStop(HIOCP hIocp);

//	ȡ��ǰʵ��������
IOCPLIB_API int WINAPI IocpGetConn(HIOCP hIocp);

//	��ͻ��˷�������
IOCPLIB_API int WINAPI IocpSendBytes(HIOCP hIocp,SOCKET s,const BYTE* lpBuff,int nBufLen);

//	���û�ȡһ���û��Զ�����
IOCPLIB_API BOOL WINAPI IocpSetUserData(HIOCP hIocp, SOCKET s,int nUserData );
IOCPLIB_API int WINAPI IocpGetUserData(HIOCP hIocp, SOCKET s);
*/


bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("xxx.db");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    /*
    query.exec("create table screen (id int primary key, "
               "name varchar(20), addr varchar(20), comType varchar(20), comProgress varchar(20), remark varchar(20))");

    query.exec("insert into screen values(101, 'Danny', 'Young', 'Danny', 'Young', 'Danny')");
    query.exec("insert into screen values(102, 'Christine', 'Holand', 'Christine', 'Holand', 'Christine')");
    query.exec("insert into screen values(103, 'Lars', 'Gordon', 'Lars', 'Gordon', 'Lars')");
    query.exec("insert into screen values(104, 'Roberto', 'Robitaille', 'Roberto', 'Robitaille', 'Roberto')");
    query.exec("insert into screen values(105, 'Maria', 'Papadopoulos', 'Maria', 'Papadopoulos', 'Maria')");
*/
    query.exec("create table allScreens (id int primary key, "
               "name varchar(20), simNo varchar(20), addr varchar(20), comType varchar(20), screenGroup varchar(20), remark varchar(20))");
    query.exec("insert into allScreens values(101, 'Danny', 'Young','Young', 'Young', 'Young', 'Young')");
    query.exec("insert into allScreens values(102, 'Christine', 'Holand', 'Young','Holand', 'Holand', 'Holand')");
    query.exec("insert into allScreens values(103, 'Lars', 'Gordon', 'Gordon','Young', 'Gordon', 'Gordon')");
    query.exec("insert into allScreens values(104, 'Roberto', 'Robitaille','Young', 'Robitaille', 'Robitaille', 'Robitaille')");
    query.exec("insert into allScreens values(105, 'Maria', 'Papadopoulos','Young', 'Papadopoulos', 'Papadopoulos', 'Papadopoulos')");
 /*
    query.exec("create table offices (id int primary key,"
                                             "imagefile int,"
                                             "location varchar(20),"
                                             "country varchar(20),"
                                             "description varchar(100))");
    query.exec("insert into offices "
               "values(0, 0, 'Oslo', 'Norway',"
               "'Oslo is home to more than 500 000 citizens and has a "
               "lot to offer.It has been called \"The city with the big "
               "heart\" and this is a nickname we are happy to live up to.')");
    query.exec("insert into offices "
               "values(1, 1, 'Brisbane', 'Australia',"
               "'Brisbane is the capital of Queensland, the Sunshine State, "
               "where it is beautiful one day, perfect the next.  "
               "Brisbane is Australia''s 3rd largest city, being home "
               "to almost 2 million people.')");
    query.exec("insert into offices "
               "values(2, 2, 'Redwood City', 'US',"
               "'You find Redwood City in the heart of the Bay Area "
               "just north of Silicon Valley. The largest nearby city is "
               "San Jose which is the third largest city in California "
               "and the 10th largest in the US.')");
    query.exec("insert into offices "
               "values(3, 3, 'Berlin', 'Germany',"
               "'Berlin, the capital of Germany is dynamic, cosmopolitan "
               "and creative, allowing for every kind of lifestyle. "
               "East meets West in the metropolis at the heart of a "
               "changing Europe.')");
    query.exec("insert into offices "
               "values(4, 4, 'Munich', 'Germany',"
               "'Several technology companies are represented in Munich, "
               "and the city is often called the \"Bavarian Silicon Valley\". "
               "The exciting city is also filled with culture, "
               "art and music. ')");
    query.exec("insert into offices "
               "values(5, 5, 'Beijing', 'China',"
               "'Beijing as a capital city has more than 3000 years of "
               "history. Today the city counts 12 million citizens, and "
               "is the political, economic and cultural centre of China.')");

    query.exec("create table images (locationid int, file varchar(20))");
    query.exec("insert into images values(0, 'images/oslo.png')");
    query.exec("insert into images values(1, 'images/brisbane.png')");
    query.exec("insert into images values(2, 'images/redwood.png')");
    query.exec("insert into images values(3, 'images/berlin.png')");
    query.exec("insert into images values(4, 'images/munich.png')");
    query.exec("insert into images values(5, 'images/beijing.png')");
*/
    return true;
}


void initializeModel(QSqlTableModel *model)
{
    model->setTable("allScreens");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("���"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("����"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("SIM����"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("��ַ"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ͨ�ŷ�ʽ"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("��Ļ��"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("��ע"));
/*
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("addr"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("comType"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("comProgress"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("remark"));
*/
}

void setTableViewModel(QTableView *view, QSqlTableModel *model)
{
    // = new QTableView;
    view->setModel(model);
    view->setWindowTitle(QObject::tr("�ն��б�"));
    //return view;
}

int main(int argv,char **argc)
{
    QApplication app(argv,argc);
    //tcpServer listenSocket;
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb2312"));
    QFont font(QObject::tr("������"),9,QFont::Normal,FALSE);
    app.setFont(font);

    createConnection();

    QSqlTableModel model;
    initializeModel(&model);

    MainWindow mwin;

    setTableViewModel(mwin.ui.tableView, &model);

    mwin.show();
    //if(!listenSocket.listen((QHostAddress::Any,8888)))



    return app.exec();
}
