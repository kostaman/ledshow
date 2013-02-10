#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QTimer>

class tcpThread : public QThread
{
    Q_OBJECT
    public:
        void run();
        tcpThread(int socketDescriptor, QObject *parent);
        ~tcpThread();
        bool createConnection();
    public slots:
        void sendSearch();
        void readMessage();
        void sendCommand();
    private:
        int socketDescriptor;
        QTcpSocket* tcpSocket;
        QTimer* dataTimer;
        QTimer* cmdTimer;
        int sendNum;
        QSqlDatabase* db;

        char fileSendFlag; //�����ļ�,1��ʾ��ǰ���ļ����ͣ�0��ʾ���ļ�����
        int fileSendOffset;   //�����ļ�ƫ��
        QString fileName; //�����ļ�����
 };
#endif // TCPTHREAD_H
