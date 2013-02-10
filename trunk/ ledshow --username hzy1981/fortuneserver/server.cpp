#ifndef TCPSERVER_CPP
#define TCPSERVER_CPP

#include <server.h>
#include <thread.h>

tcpServer::tcpServer(QObject *parent):QTcpServer(parent)
{

}

void tcpServer::incomingConnection(int socketDescriptor)
{
    tcpThread *Mythread = new tcpThread(socketDescriptor,this);
    connect(Mythread,SIGNAL(finished()),Mythread,SLOT(deleteLater()));
    Mythread->start();
}

fileServer::fileServer(QObject *parent)
{
  //��ʼ��fileInfo��Ϣ
  memset(fileInfo, 0, sizeof(fileInfo));

  for(int i = 0; i < MAX_RAM_FILE_NUM; i ++)
  {
      fileInfo[i].head = CHK_BYTE;
      fileInfo[i].tail = CHK_BYTE;
  }
}

int fileServer::readFile(int index, char* fileName, int offset, int len, char *pDst, int dstLen) //��ȡ�ļ�
{
    if(strcmp(fileName, fileInfo[index].fileName) != 0) //�ļ��������ļ����Բ��ϣ�
    {
        qDebug("�������ļ�������Ӧ, index = %d, name = %s", index, fileInfo[index].fileName);
        return 0;
    }

    if(offset + len > fileInfo[index].fileLen)
    {
        qDebug("��ȡ�ļ�Խ��, offset = %d, len = %d, filelen = %d", offset, len, fileInfo[index].fileLen);
        return 0;
    }

    if(len > dstLen)
        return 0;

    memcpy(pDst, fileInfo[index].pBuf + offset, len);

    return len;
}

//����ļ������Ƿ���ram��������򷵻�����
int fileServer::chkFileInRam(char* fileName)
{
  //char temp[200];

  if(strlen(fileName) >= 100)
  {
      qDebug("fileName lenght error");
      return 0;
  }

  //strcpy(temp, fileName);

  for(int i = 0; i < MAX_RAM_FILE_NUM; i ++)
  {
      if(strcmp(fileName, fileInfo[i].fileName) EQ 0)
          return i + 1;
  }

  return 0;
}

//��ȡ�ļ��洢���ڴ�ram��
int fileServer::getFileToRam(char *fileName)
{
  FILE *file;
  size_t len;

  file = fopen(fileName, "rb");
  if(file EQ 0)
  {
      qDebug("�Ҳ����ļ�%s", (const char *)fileName);
      return 0;
  }

  fseek(file, 0, SEEK_END);
  len = ftell(file); //�ļ���С

  for(int i = 0; i < MAX_RAM_FILE_NUM; i ++)
  {
    if(fileInfo[i].fileName[0] EQ 0) //û���ļ���--��������û�б�ռ��
    {
        fileInfo[i].pBuf = (char *)malloc(len); //���붯̬�ڴ�
        if(fileInfo[i].pBuf EQ 0)
        {
            qDebug("�����ڴ�ʧ�ܣ���С%d", len);
            fclose(file);
            return 0;
        }

        //��ȡ�ļ�ʧ�ܣ��ͷ���Դ
        if(fread(fileInfo[i].pBuf, len, 1, file) != len)
        {
            qDebug("��ȡ�ļ�%sʧ��", (const char *)fileName);

            free(fileInfo[i].pBuf);
            fileInfo[i].pBuf = 0;
            fclose(file);

            return 0;
        }

        fileInfo[i].fileLen = len;
        strcpy(fileInfo[i].fileName, fileName);
        fclose(file);

        return i + 1;

    }
  }


  return 0;
}

#endif // TCPSERVER_CPP
