#define	 __MARVELL_OPS_FILE__
#include "marvell_ops.h"



/********************************************************************************
���ṹ����ϵͳ������ص����в�������MAC������״̬���������͵���Ϣ�����Ӧ�ñ��ṹ
���Ը��õ��Ż�������Ƽ�������Ч��
********************************************************************************/
struct lbs_private *pgmarvel_priv;
u8 sdio_sys_wait=1;//sdio����bug�����������ڵ���ϵͳ�ȶ�ʱ�䣬ֱ��Ӱ��ϵͳ����
/***********************************************************************************************
****������:init_marvell_driver
****����:��ʼ��marvell�������򣬹���������Ϣ�����marvel_mode����
****����:��
****����:0:ʧ�� ����:struct lbs_private *
***********************************************************************************************/
struct lbs_private * init_marvell_driver(void)
{
  struct mmc_host *host;
  struct mmc_card *card;
  struct sdio_func *func;
  struct lbs_private *priv;
  MAR_POW(1);//�Ͽ�ģ���ԴΪsdioö����׼��
  host=stm32_probe();
  MAR_POW(0);//�ϵ�ģ���Դ��sdio������λ
  mmc_rescan(host);
  printk("init marvel driver ok!\n");
  card=host->card;//ȡ��card
  func=card->sdio_func[0];//ȡ����һ��func
  if(func){
		  priv=(struct lbs_private *)sdio_bus_probe(func);
		  if(priv){
			  printk("device probe success!\n");
			  return priv;
		  }
		  else
			  printk("device probe failed!\n");
  }
  else
	  printk("cann't find a function device!\n");
  return 0;
}

/***********************************************************************************************
****������:marvel_assoc_network
****����:��������
****����:priv:ȫ����������
	    ssid:ascll����������
	    key:ascll����Կ������Ϊ0:���������磬С��8bit����ԿĬ��Ϊwep���ܣ���������wpa����
	    mode:'0':��������(infra) ��1��:ad-hoc����
****����:0:���� ����:����
***********************************************************************************************/
void marvel_assoc_network(struct lbs_private *priv,char *ssid,char *key,char mode)
{
		marvel_assoc_open_network(priv,ssid,key,mode);
}

/***********************************************************************************************
****������:lbs_scan_worker
****����:ɨ�����磬ɨ���������struct lbs_private�ṹ�е�networks��
****����:priv:ȫ����������
****����:��
***********************************************************************************************/
void lbs_scan_worker(struct lbs_private *priv)
{
	lbs_deb_enter(LBS_DEB_SCAN);
	lbs_scan_networks(priv, 0);
	lbs_deb_leave(LBS_DEB_SCAN);
}

/***********************************************************************************************
****������:lbs_rev_pkt
****����:�������WIFI��·������ݽ��գ����յõ������ݴ����struct lbs_private *priv->rx_pkt�С�
****����:��
****����:���ؽ������ݳ��ȣ�
***********************************************************************************************/
u16 lbs_rev_pkt(void)
{
	struct lbs_private *priv=pgmarvel_priv;
	struct if_sdio_card *card=priv->card;
	struct eth_packet *rx_pkt=&priv->rx_pkt;
	int ret;
	sdio_sys_wait=0;
	memset(rx_pkt,0,sizeof(struct eth_packet ));//�������ж����ݽ�������
	ret=pool_sdio_interrupt(card->func);
	if(ret<0){
			lbs_pr_err("read interrupt error!\n");
			try_bug(0);
	}
	else if(ret&(IF_SDIO_H_INT_UPLD|IF_SDIO_H_INT_DNLD)){//���ж�����
		if_sdio_interrupt(card->func);
		if(rx_pkt->len){//���յ�����
			sdio_sys_wait=1;
			return rx_pkt->len;
		}
			
	}
	else{
		sdio_sys_wait=1;
		return 0;
	}
	sdio_sys_wait=1;
	return 0;
}
/***********************************************************************************************
****������:lbs_hard_start_xmit
****����:������̫�����ݰ����������ݴ����tx_ethpkt�е�data��
****����:priv:ȫ����������
	    tx_ethpkt:��̫�����ݰ����
****����:0:���� ����:����
***********************************************************************************************/
char  lbs_hard_start_xmit(struct lbs_private *priv,struct eth_packet * tx_ethpkt)
{
	struct txpd *txpd;//�������ڿ���Ӳ�����͵�ͷ��Ϣ������������ݰ�ǰ��д������
	char *p802x_hdr;
	unsigned int pkt_len;
	int ret = 0;
	lbs_deb_enter(LBS_DEB_TX);
	if (priv->surpriseremoved)
		goto free;

	if (!tx_ethpkt->len || (tx_ethpkt->len > MRVDRV_ETH_TX_PACKET_BUFFER_SIZE)) {
		lbs_deb_tx("tx err: skb length %d 0 or > %zd\n",
		       tx_ethpkt->len, MRVDRV_ETH_TX_PACKET_BUFFER_SIZE);
		goto free;
	}

	txpd=(void *)&priv->resp_buf[0][4];
	memset(txpd, 0, sizeof(struct txpd));

	p802x_hdr = tx_ethpkt->data;//802.3 macͷ
	pkt_len = tx_ethpkt->len;
	/* copy destination address from 802.3 header */
	//���յ�ַ
	memcpy(txpd->tx_dest_addr_high, p802x_hdr, ETH_ALEN);
	txpd->tx_packet_length = cpu_to_le16(pkt_len);//802.3����Ч���ݳ��ȣ��̼����Զ���װ802.11����֡
	txpd->tx_packet_location = cpu_to_le32(sizeof(struct txpd));//���ݵ�ƫ��
	memcpy(&txpd[1], p802x_hdr, le16_to_cpu(txpd->tx_packet_length));//�������ݴ�ŵĵط�
	priv->resp_len[0] = pkt_len + sizeof(struct txpd);//�Ƿ���������Ҫ���Ϳ��ľ����ж���pkt_len�Ƿ�ֵ
	lbs_deb_tx("%s lined up packet\n", __func__);
 free:	
	if (priv->resp_len[0] > 0) {//�������ݴ���//������ǵ���if_sdio_host_to_card����������������豸��������	
		 ret=if_sdio_send_data(priv,priv->resp_buf[0],
								priv->resp_len[0]);
		if (ret) {
			lbs_deb_tx("host_to_card failed %d\n", ret);
			priv->dnld_sent = DNLD_RES_RECEIVED;
		}
		priv->resp_len[0] = 0;
	}
	wait_for_data_end();
	lbs_deb_leave_args(LBS_DEB_TX, ret);
	return ret;
}

/***********************************************************************************************
****������:wpa_L2_send_pkt
****����:wpa eapol������·�㷢�ͺ���
****����:0:���� ����:����
***********************************************************************************************/
int wpa_L2_send_pkt(u8 *buf,u16 len)
{
	struct eth_packet tx_ethpkt;
	tx_ethpkt.data=(char *)buf;
	tx_ethpkt.len=len;
	//debug_data_stream("L2 send",buf,len);
	return lbs_hard_start_xmit(pgmarvel_priv,&tx_ethpkt);
}
/***********************************************************************************************
****������:lbs_ps_wakeup
****����:���ڻ�������sleepģʽ
****����:priv:ȫ����������
****����:��
***********************************************************************************************/
void lbs_ps_wakeup(struct lbs_private *priv) 
{
	__le32 Localpsmode;
	int wait_option=CMD_OPTION_WAITFORRSP;
	lbs_deb_enter(LBS_DEB_HOST);
	Localpsmode = cpu_to_le32(LBS802_11POWERMODECAM);
	lbs_prepare_and_send_command(priv, CMD_802_11_PS_MODE,//���������˳��͹���ģʽ
			      CMD_SUBCMD_EXIT_PS,
			      wait_option, 0, &Localpsmode);

	lbs_deb_leave(LBS_DEB_HOST);
}
/***********************************************************************************************
****������:lbs_ps_sleep
****����:���ڻ�������ģʽ��,����sleep״̬��AP��Ϊ�仺�汨��
****����:priv:ȫ����������
****����:��
***********************************************************************************************/
void lbs_ps_sleep(struct lbs_private *priv)
{
	int wait_option=CMD_OPTION_WAITFORRSP;
	lbs_deb_enter(LBS_DEB_HOST);
	/*
	 * PS is currently supported only in Infrastructure mode
	 * Remove this check if it is to be supported in IBSS mode also
	 */
	lbs_prepare_and_send_command(priv, CMD_802_11_PS_MODE,
			      CMD_SUBCMD_ENTER_PS, wait_option, 0, NULL);

	lbs_deb_leave(LBS_DEB_HOST);
}

/***********************************************************************************************
****������:init_sleep_mode
****����:��ʼ��ȫ�ֵ�confirm_sleep�������Ա���lbs_send_confirmsleepѸ�ٽ���͹���ģʽ
****����:��
****����:��
***********************************************************************************************/
struct cmd_confirm_sleep confirm_sleep;
void init_sleep_mode(void)
{
	memset(&confirm_sleep, 0, sizeof(confirm_sleep));
	confirm_sleep.hdr.command = cpu_to_le16(CMD_802_11_PS_MODE);
	confirm_sleep.hdr.size = cpu_to_le16(sizeof(confirm_sleep));
	confirm_sleep.action = cpu_to_le16(CMD_SUBCMD_SLEEP_CONFIRMED);
}
 /***********************************************************************************************
 ****������:lbs_send_confirmsleep
 ****����:��������͹���ģʽ
 ****����:priv:ȫ����������
 ****����:��
 ***********************************************************************************************/
 void lbs_send_confirmsleep(struct lbs_private *priv)
{
	 int ret;

	lbs_deb_enter(LBS_DEB_HOST);
	lbs_deb_hex(LBS_DEB_HOST, "sleep confirm", (u8 *) &confirm_sleep,
		sizeof(confirm_sleep));

	ret = priv->hw_host_to_card(priv, MVMS_CMD, (u8 *) &confirm_sleep,
		sizeof(confirm_sleep));
	if (ret) {
		lbs_pr_alert("confirm_sleep failed\n");
		goto out;
	}
	/* We don't get a response on the sleep-confirmation */
	priv->dnld_sent = DNLD_RES_RECEIVED;
out:
	lbs_deb_leave(LBS_DEB_HOST);
}


int __lbs_set_key_material(int key_type,int key_info,u8 *key, u16 key_len)
{
	printf("MARVELL TIME OUT TYPE %d , info %d \n",key_type,key_info);
	return lbs_set_key_material(pgmarvel_priv,key_type,key_info,key,key_len);
}

