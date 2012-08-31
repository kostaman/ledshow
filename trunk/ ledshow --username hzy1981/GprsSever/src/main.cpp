#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <QtCore/QSettings>
#include <QtGui/QFont>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtGui/QMessageBox>
#include <QtGui/QPlastiqueStyle>
#include "mainwindow.h"


int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	//QApplication::setStyle(new QPlastiqueStyle);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

	// �������壬Ĭ������һ��Ϊ���壬�������������Ϊ9
	QApplication::setFont(QFont("SimSun", 9));
	// ����Library·����ʹ�ò���ϵͳ�ڲ���װQt�����������������
	QApplication::addLibraryPath("../plugins");
	
	QSettings settings("../etc/bpms.conf", QSettings::IniFormat, &app);
	QString db_hostname = settings.value("hostname").toString();
	QString db_database = settings.value("database").toString();
	QString db_username = settings.value("username").toString();
	QString db_password = settings.value("password").toString();

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(db_hostname);
	db.setDatabaseName(db_database);
	db.setUserName(db_username);
	db.setPassword(db_password);
	
	if (db.open() == false)
	{
		QMessageBox::critical(NULL, QObject::tr("����"), QObject::tr("MySQL���ݿ����Ӵ���, �������������ݿ����"), QMessageBox::Ok, QMessageBox::NoButton);	
		return !EXIT_SUCCESS;
	}
	db.exec("SET NAMES 'gbk'");
	MainWindow mainwindow;
	mainwindow.show();
	return app.exec();
}
