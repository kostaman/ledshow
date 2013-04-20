/**
* @file udpclient.c
* @brief A brief file description.
* @details
*     A more elaborated file description.
* @author Wang Mengyin
* @date 2010Jul31 21:27:15
* @note
*               Copyright 2010 Wang Mengyin.ALL RIGHTS RESERVED.
*                            http://tigerwang202.blogbus.com
*    This software is provided under license and contains proprietary and
* confidential material which is the property of Company Name tech.
*/


#define __UDPCLIENT_C


/* Includes ------------------------------------------------------------------*/
#include "udpclient.h"
#include <lwip/netdb.h> /* Ϊ�˽�������������Ҫ����netdb.hͷ�ļ� */
#include <lwip/sockets.h> /* ʹ��BSD socket����Ҫ����sockets.hͷ�ļ� */
#include "lwip/mem.h"
#include "includes.h"
/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
const char send_data[] = "This is UDP Client from RT-Thread.\n"; /* �����õ������� */

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
void udpclient(const char* url, int port, int count)
{
   int sock;
   struct hostent *host;
   struct sockaddr_in server_addr;

   /* ͨ��������ڲ���url���host��ַ��������������������������� */
   host= (struct hostent *) gethostbyname(url);

   /* ����һ��socket��������SOCK_DGRAM��UDP���� */
   if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
       printf("Socket error\n");
       return;
   }

   /* ��ʼ��Ԥ���ӵķ���˵�ַ */
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(port);
   server_addr.sin_addr = *((struct in_addr *)host->h_addr);
   memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

   /* �ܼƷ���count������ */
   while (count)
   {
       /* �������ݵ�����Զ�� */
       sendto(sock, send_data, strlen(send_data), 0,
              (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

       /* �߳�����һ��ʱ�� */
       OSTimeDly(50);

       /* ����ֵ��һ */
       count --;
   }

   /* �ر����socket */
   lwip_close(sock);
}

/*-- File end --*/

