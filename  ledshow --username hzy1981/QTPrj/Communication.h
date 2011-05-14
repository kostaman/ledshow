#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QextSerialPort>
#include <QextSerialEnumerator>
#include <QString>
#include <QProgressDialog>
#include "..\Stm32\usr\app\Includes.h"

class CcomStatus:public QWidget
{
    Q_OBJECT
private:
    INT8U COM_Mode;//ͨ�ŷ�ʽ
    INT8U COM_Port;

    //ͨ�Ų���
    S_COM_Para COM_Para; //PC��ͨ�Ų���
    S_ETH_Para ETH_Para;
    S_GPRS_Para GPRS_Para;

    //����
    QextSerialPort * port;

    QProgressDialog *progressDialog;

    //ͨ�Ž��ջ�����
    INT8U Rcv_Buf[1000];
    int Rcv_Posi;
    INT8U Rcv_Flag;
    INT8U Rcv_Ch;

    QString comReStr; //ͨ�Ž���ַ���

signals:
    void comStatusChanged(QString str);

public:
        int connect(QString str); //������Ļ
        int disConnect(); //�Ͽ�����

        int sendFrame(char *data, int len);

        int sendProtoFile(QString fileName);

        void setComMode(int mode);
        int waitComRcv(int ms); //�ȴ�ͨ�ŷ�������

        void getCOMParaFromSettings(QString str); //��ȡͨ�Ų���
        void clearRcvData(); //�����������

        CcomStatus(QWidget * parent = 0);
public slots:
        /**
         * Receive data from serial port.
         */
        void comReceive();
};

QStringList getComPortList();
#endif // COMMUNICATION_H
