#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QString>
#include <QStringList>

#define MAX_RAM_FILE_NUM 500//�������ڴ��еĶ�����ļ���
#define CHK_BYTE 0x5A
#define EQ ==

class tcpServer : public QTcpServer
{
    Q_OBJECT
    public:
        tcpServer(QObject *parent = 0);
    protected:
        void incomingConnection(int socketDescriptor);
 };

typedef struct
{
  char head;

  char fileName[100]; //�ļ���
  FILE *fp;  //ָ���ļ��ṹ���ָ��
  char *pBuf; //����buf
  int timerCounts;
  char useFlag; //��ǰ�Ƿ���ʹ��
  int fileLen;

  char tail;
}sfileInfo;

class fileServer// : public QTcpServer
{
    private:
    QStringList fileName;
    FILE *fp[MAX_RAM_FILE_NUM]; //���100���ļ�
    char *(fileBufp[MAX_RAM_FILE_NUM]); //ÿ���ļ���Ӧ��buf


    sfileInfo fileInfo[MAX_RAM_FILE_NUM]; //�ļ���Ϣ

    public:

        fileServer(QObject *parent = 0);
        int readFile(int index, char * fileName, int offset, int len, char *pDst, int dstLen); //��ȡ�ļ�
        int chkFileInRam(char * fileName);  //����ļ��Ƿ���ram�У��Ƿ���true�����򷵻�false
        int getFileToRam(char * fileName);
         //protected:
        //void incomingConnection(int socketDescriptor);
 };
#endif // TCPSERVER_H
