/**
 * @file
 * Ethernet Interface Skeleton
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/*
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethernetif" to replace it with
 * something that better describes your network interface.
 */

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include <lwip/stats.h>
#include <lwip/snmp.h>
#include <string.h>

#include "netif/etharp.h"
#include "netif/ppp_oe.h"
#include "netif/ethernetif.h"
#include "marvell_ops.h"

/* TCP and ARP timeouts */
volatile int tcp_end_time, arp_end_time;
/* Define those to better describe your network interface. */
#define IFNAME0 's'
#define IFNAME1 't'
/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct ethernetif
{
  struct eth_addr *ethaddr;
  /* Add whatever per-interface state that is needed here. */
  int unused;
};
err_t  ethernetif_input(struct netif *netif);
extern struct netif netif;
/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static void low_level_init(struct netif *netif)
{
  /* set MAC hardware address length */
  printf("enter low level!\n");
  printf("mac %2x:%2x:%2x:%2x:%2x:%2x\n",pgmarvel_priv->current_addr[0],
									  	pgmarvel_priv->current_addr[1],
									  	pgmarvel_priv->current_addr[2],
									  	pgmarvel_priv->current_addr[3],
									  	pgmarvel_priv->current_addr[4],
									  	pgmarvel_priv->current_addr[5]);
  netif->hwaddr_len = ETHARP_HWADDR_LEN;
  memcpy(netif->hwaddr,pgmarvel_priv->current_addr,ETHARP_HWADDR_LEN);
  /* maximum transfer unit */
  netif->mtu = 1500;
  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
  printf("leave low level!\n");

}

/***********************************************************************************************
****������:lbs_sendpbuf
****����:ʵ��lwip��������Ľӿ�
****����:priv:ȫ����������
	    p:lwip���ݱ�������pbuf
****����:0:���� ����:����	 #include "lwip.h"//��ǿ�ⲿ�������Ҫ��Ϊ����ߴ����ٶ�

***********************************************************************************************/
char  lbs_sendpbuf(struct lbs_private *priv, struct pbuf *p)
{
	struct txpd *txpd;//�������ڿ���Ӳ�����͵�ͷ��Ϣ������������ݰ�ǰ��д������
	struct pbuf *q;
	char *p802x_hdr;
	char *buffer;
	uint16_t pkt_len;
	int ret = 0;
	int l = 0;
	sdio_sys_wait=0;
	txpd=(void *)&priv->resp_buf[0][4];
	memset(txpd, 0, sizeof(struct txpd));
	p802x_hdr = (char *)p->payload;//802.3 macͷ
	pkt_len = (uint16_t)p->tot_len;
	//���յ�ַ
	memcpy(txpd->tx_dest_addr_high, p802x_hdr, ETH_ALEN);
	txpd->tx_packet_length = cpu_to_le16(pkt_len);//802.3����Ч���ݳ��ȣ��̼����Զ���װ802.11����֡
	txpd->tx_packet_location = cpu_to_le32(sizeof(struct txpd));//���ݵ�ƫ��
	buffer=(char *)&txpd[1];
	for(q = p; q != NULL; q = q->next) {
	    memcpy(buffer+l, q->payload, q->len);
		l+= (int)q->len;
	  }
	//memcpy(, p802x_hdr, le16_to_cpu(txpd->tx_packet_length));//�������ݴ�ŵĵط�
	priv->resp_len[0] = pkt_len + sizeof(struct txpd);//�Ƿ���������Ҫ���Ϳ��ľ����ж���pkt_len�Ƿ�ֵ
	if (priv->resp_len[0] > 0) {//�������ݴ���
	//������ǵ���if_sdio_host_to_card����������������豸��������
	//	debug_data_stream("send data",buffer,priv->resp_len[0]);
		ret=if_sdio_send_data(priv,priv->resp_buf[0],
								priv->resp_len[0]);
		if (ret) {
			lbs_deb_tx("host_to_card failed %d\n", ret);
			priv->dnld_sent = DNLD_RES_RECEIVED;
		}
		priv->resp_len[0] = 0;
	}
	sdio_sys_wait=1;
	return ret;
}



/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
  /* Interrupts are disabled through this whole thing to support multi-threading
	   transmit calls. Also this function might be called from an ISR. */
  //BSP_IntDis(BSP_INT_ID_TIM2);
  lbs_sendpbuf(pgmarvel_priv,p);
  wait_for_data_end();
 // BSP_IntEn(BSP_INT_ID_TIM2);
 // pbuf_free(p);//
  return ERR_OK;
}
/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
extern struct wpa_sm wpasm;
void rest_sys_mem(void);
#include "netif/etharp.h"
extern int wpa_rx_eapol(const u8 *src_addr,
		    const u8 *buf, size_t len);

//static u8 xxxbuf[] = {0x00,0x1a,0x6b,0x6e,0x90,0x67,0x00,0x26,0xf2,0xa8,0x17,0x5b,0x88,0x8e,0x01,0x03,0x00,0x5f,0x02,0x00,0x8a,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xa7,0x38,0x03,0x5e,0xf0,0x21,0x81,0xf4,0x12,0xb2,0x61,0x49,0x4d,0x19,0xa9,0xca,0xe0,0xfc,0xca,0x47,0x20,0x46,0x36,0x26,0xce,0x14,0xfc,0x01,0xee,0x7d,0x3b,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
struct pbuf *low_level_input(struct netif *netif)
{
  struct eth_packet *rx_pkt=&pgmarvel_priv->rx_pkt;
  struct eth_hdr* ethhdr;
  struct pbuf *p, *q;
  u16 len=0;
  int l =0;
  char *buffer;
  p = NULL;
  /* Obtain the size of the packet and put it into the "len"
     variable. */ 
 // BSP_IntDis(BSP_INT_ID_TIM2);
  len=lbs_rev_pkt();
//  BSP_IntEn(BSP_INT_ID_TIM2);
  if(len>0){
	buffer=rx_pkt->data;
	//debug_data_stream("Wireless data",buffer,rx_pkt->len);
	  /* We allocate a pbuf chain of pbufs from the pool. */
	
	 p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
	 if (p != NULL){
	   for (q = p; q != NULL; q = q->next){
		  memcpy((u8_t*)q->payload, (u8_t*)&buffer[l], q->len);
	      l = l + q->len;
	    }    
	  }
	  else{
	  	rest_sys_mem();
	  }
	  	
  }
  return p;
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
err_t
ethernetif_input(struct netif *netif)
{
  err_t err;
  //INT8U ret;
  struct pbuf *p=NULL;
  /* move received packet into a new pbuf */
  p = low_level_input(netif);
  /* no packet could be read, silently ignore this */
  if (p == NULL){
  	 return ERR_OK;
  }
  err = netif->input(p, netif); // ��pbuf���ݸ��ϲ�Э��ջ
  if (err != ERR_OK){
    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
    pbuf_free(p);
    p = NULL;
	return err;
  }
  return err;
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t
ethernetif_init(struct netif *netif)
{
  struct ethernetif *ethernetif;
  LWIP_ASSERT("netif != NULL", (netif != NULL));
  ethernetif = mem_malloc(sizeof(struct ethernetif));
  if (ethernetif == NULL)
  {
    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory\n"));
    return ERR_MEM;
  }
  /*
   * Initialize the snmp variables and counters inside the struct netif.
   * The last argument should be replaced with your link speed, in units
   * of bits per second.
   */
  NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 10000000);
  netif->state = ethernetif;
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;
  ethernetif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);
  low_level_init(netif);
  return ERR_OK;
}



