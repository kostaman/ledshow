#ifndef __MARVELL_OPS__H__
#define __MARVELL_OPS__H__

#include "system.h"//ƽ̨���
#include "common.h"//Ӳ���޹ر�׼ͷ�ļ�
#include "host.h"
#include "card.h"
#include "if_sdio.h"
#include "core.h"
#include "dev.h"
#include "rxtx.h"
#include "cmd.h"
#include "assoc.h"
#include "system.h"
#include "sdio_func.h"
#include "hostcmdcode.h"


#ifndef	 __MARVELL_OPS_FILE__//ϵͳ�ؼ���ȫ�ֱ���
extern struct lbs_private *pgmarvel_priv;
extern u8 sdio_sys_wait;
#endif

struct lbs_private * init_marvell_driver(void);
void marvel_assoc_network(struct lbs_private *priv,char *ssid,char *key,char mode);
void lbs_scan_worker(struct lbs_private *priv);
u16 lbs_rev_pkt(void);
char  lbs_hard_start_xmit(struct lbs_private *priv,struct eth_packet * tx_ethpkt);
int wpa_L2_send_pkt(u8 *buf,u16 len);
int lbs_set_key_material(struct lbs_private *priv,int key_type,int key_info,u8 *key, u16 key_len);

extern int __lbs_set_key_material(int key_type,int key_info,u8 *key, u16 key_len);


/*************��Դ����****************************************************************/
void lbs_ps_wakeup(struct lbs_private *priv); 
void lbs_ps_sleep(struct lbs_private *priv);
void init_sleep_mode(void);
void lbs_send_confirmsleep(struct lbs_private *priv);

enum wpa_states {
	/**
	 * WPA_DISCONNECTED - Disconnected state
	 *
	 * This state indicates that client is not associated, but is likely to
	 * start looking for an access point. This state is entered when a
	 * connection is lost.
	 */
	WPA_DISCONNECTED,

	/**
	 * WPA_INACTIVE - Inactive state (wpa_supplicant disabled)
	 *
	 * This state is entered if there are no enabled networks in the
	 * configuration. wpa_supplicant is not trying to associate with a new
	 * network and external interaction (e.g., ctrl_iface call to add or
	 * enable a network) is needed to start association.
	 */
	WPA_INACTIVE,

	/**
	 * WPA_SCANNING - Scanning for a network
	 *
	 * This state is entered when wpa_supplicant starts scanning for a
	 * network.
	 */
	WPA_SCANNING,

	/**
	 * WPA_AUTHENTICATING - Trying to authenticate with a BSS/SSID
	 *
	 * This state is entered when wpa_supplicant has found a suitable BSS
	 * to authenticate with and the driver is configured to try to
	 * authenticate with this BSS. This state is used only with drivers
	 * that use wpa_supplicant as the SME.
	 */
	WPA_AUTHENTICATING,

	/**
	 * WPA_ASSOCIATING - Trying to associate with a BSS/SSID
	 *
	 * This state is entered when wpa_supplicant has found a suitable BSS
	 * to associate with and the driver is configured to try to associate
	 * with this BSS in ap_scan=1 mode. When using ap_scan=2 mode, this
	 * state is entered when the driver is configured to try to associate
	 * with a network using the configured SSID and security policy.
	 */
	WPA_ASSOCIATING,

	/**
	 * WPA_ASSOCIATED - Association completed
	 *
	 * This state is entered when the driver reports that association has
	 * been successfully completed with an AP. If IEEE 802.1X is used
	 * (with or without WPA/WPA2), wpa_supplicant remains in this state
	 * until the IEEE 802.1X/EAPOL authentication has been completed.
	 */
	WPA_ASSOCIATED,

	/**
	 * WPA_4WAY_HANDSHAKE - WPA 4-Way Key Handshake in progress
	 *
	 * This state is entered when WPA/WPA2 4-Way Handshake is started. In
	 * case of WPA-PSK, this happens when receiving the first EAPOL-Key
	 * frame after association. In case of WPA-EAP, this state is entered
	 * when the IEEE 802.1X/EAPOL authentication has been completed.
	 */
	WPA_4WAY_HANDSHAKE,

	/**
	 * WPA_GROUP_HANDSHAKE - WPA Group Key Handshake in progress
	 *
	 * This state is entered when 4-Way Key Handshake has been completed
	 * (i.e., when the supplicant sends out message 4/4) and when Group
	 * Key rekeying is started by the AP (i.e., when supplicant receives
	 * message 1/2).
	 */
	WPA_GROUP_HANDSHAKE,

	/**
	 * WPA_COMPLETED - All authentication completed
	 *
	 * This state is entered when the full authentication process is
	 * completed. In case of WPA2, this happens when the 4-Way Handshake is
	 * successfully completed. With WPA, this state is entered after the
	 * Group Key Handshake; with IEEE 802.1X (non-WPA) connection is
	 * completed after dynamic keys are received (or if not used, after
	 * the EAP authentication has been completed). With static WEP keys and
	 * plaintext connections, this state is entered when an association
	 * has been completed.
	 *
	 * This state indicates that the supplicant has completed its
	 * processing for the association phase and that data connection is
	 * fully configured.
	 */
	WPA_COMPLETED,
	WPA_NO_IMPL
};



#if 0
/**********************************************************************
����ע�Ͳ�������Ϊ�ṹ��ؼ���Ա����������Ϊ�������ݣ�������δʹ�á����ṹ��
��Ҫ���ڹ�����������������������ݡ��󲿷�������ʹ���в����漰����rx_pkt��mac
��network�������ر���Ҫʱ����ʹ�á�
***********************************************************************/
struct lbs_private {
	struct eth_packet rx_pkt;/*�������յ������ݰ����Ⱥ�������ָ��*/
	char name[DEV_NAME_LEN];/*�������������ƣ�Ŀǰδʹ��*/
	void *card;/*ָ��ö�ٵ���sdio card��������������ʹ��*/
	/* remember which channel was scanned last, != 0 if currently scanning */
	int scan_channel;/*��¼��һ���û�ָ��ɨ����ŵ��ţ�������δʹ��*/
	u8 scan_ssid[IW_ESSID_MAX_SIZE + 1];/*��¼��һ���û�ָ��ɨ����������ƣ�������δʹ��*/
	u8 scan_ssid_len;/*��¼��һ���û�ָ��ɨ����������Ƴ��ȣ�������δʹ��*/
	/** Hardware access */
	int (*hw_host_to_card) (struct lbs_private *priv, u8 type, u8 *payload, u16 nb);/*������д�����ݵĺ���ָ��*/
	//void (*reset_card) (struct lbs_private *priv);
	struct lbs_offset_value offsetvalue;/*���ڴ洢��ȡ��MAC��baseband��RF�ȼĴ�����ֵ*/
	/* Wake On LAN */
 	uint32_t wol_criteria;/****δʹ��****/
	uint8_t wol_gpio;
	uint8_t wol_gap; 
	/** Wlan adapter data structure*/
	/** STATUS variables */
	u32 fwrelease;/*********�̼���Ϣ**********/
	u32 fwcapinfo;
	/* TX packet ready to be sent... */
	int tx_pending_len;	/*�ȴ����͵����ݱ����ȣ������ڲ�ʹ��*/	/* -1 while building packet */
	/* protected by hard_start_xmit serialization */
	/** command-related variables */
	u16 seqnum;/*��ǰ��������кţ���������Ӧ�����кŶ�Ӧ*/
	 struct cmd_ctrl_node *cmd_array;/*����ڵ㻺������*/
	/** Current command */
	 struct cmd_ctrl_node *cur_cmd;/*��ǰ����ִ�е�����*/
	int cur_cmd_retcode;
	/** command Queues */
	/** Free command buffers */
	 struct list_head cmdfreeq;/*���ڹ������������ṹ������������������͹�����������*****/
	/** Pending command buffers */
	 struct list_head cmdpendingq;
	/* Events sent from hardware to driver */
	struct kfifo *event_fifo;/*ģ��̼����¼�ͨ�����ʹ��*/
	/* nickname */
	u8 nodename[16];
	int nr_retries;
	int cmd_timed_out;/****���ʱ*****/
	/** current ssid/bssid related parameters*/
	struct current_bss_params curbssparams;
	/* IW_MODE_* */
	u8 mode;/*��ǰ����ģʽ*/
	/* Scan results list */
	struct list_head network_list;
	struct list_head network_free_list;/*�������������ڴ������ɨ����*/
	struct bss_descriptor *networks;/*ɨ�赽�ĵ�ǰ��������ʹ�����������ʹ��list_for_each_entry_bssdes�����*/
	struct bss_descriptor *cur_bss;/*��ǰ������������Ϣ*/
	u16 beacon_period;/*�����beacon֡����*/
	u8 beacon_enable;
	u8 adhoccreate;/*�Ƿ񴴽���adhoc����*/
	/** capability Info used in Association, start, join */
	u16 capability;/*����֧�ֵĹ�����Ϣ*/
	/** MAC address information */
	u8 current_addr[ETH_ALEN];/*�����̼���MAC��ַ*/
	u8 multicastlist[MRVDRV_MAX_MULTICAST_LIST_SIZE][ETH_ALEN];/*�����ಥMAC��ַ*/
	u32 nr_of_multicastmacaddr;/*�����ಥ��ַ����*/
	uint16_t enablehwauto;
	uint16_t ratebitmap;/*֧�ֵ�����λͼ*/
	u8 txretrycount;
	/** NIC Operation characteristics */
	u16 mac_control;
	u32 connect_status;
	u32 mesh_connect_status;
	u16 regioncode;
	s16 txpower_cur;
	s16 txpower_min;
	s16 txpower_max;
	/** POWER MANAGEMENT AND PnP SUPPORT */
	u8 surpriseremoved;
	u16 psmode;		/* Wlan802_11PowermodeCAM=disable
				   Wlan802_11PowermodeMAX_PSP=enable */
	u32 psstate;
	u8 needtowakeup;
	struct assoc_request * pending_assoc_req;/********�ȴ�����Ĺ�������***********/
	struct assoc_request * in_progress_assoc_req;/********���ڴ���Ĺ�������***********/
	/** Encryption parameter */
	struct lbs_802_11_security secinfo;/*802.11���������Ϣ������ʹ��*/
	/** WEP keys */
	struct enc_key wep_keys[4];/***********wep����ʹ�õ�4����Կ*******/
	u16 wep_tx_keyidx;/***********wep����ʹ�õ���Կ�����*******/
	/** WPA keys */
	 struct enc_key wpa_mcast_key;/***********wpa���ܶಥ��Կ*******/
	 struct enc_key wpa_unicast_key;/***********wpa���ܵ�����Կ*******/
	/** Requested Signal Strength*/
	u16 SNR[MAX_TYPE_B][MAX_TYPE_AVG];
	u16 NF[MAX_TYPE_B][MAX_TYPE_AVG];
	u8 RSSI[MAX_TYPE_B][MAX_TYPE_AVG];
	u8 rawSNR[DEFAULT_DATA_AVG_FACTOR];
	u8 rawNF[DEFAULT_DATA_AVG_FACTOR];
	u16 nextSNRNF;
	u16 numSNRNF;
	u8 radio_on;
	/** data rate stuff */
	u8 cur_rate;
	/** RF calibration data */
#define	MAX_REGION_CHANNEL_NUM	2
	/** region channel data */
	struct region_channel region_channel[MAX_REGION_CHANNEL_NUM];
	struct region_channel universal_channel[MAX_REGION_CHANNEL_NUM];
	/** 11D and Domain Regulatory Data */
	struct lbs_802_11d_domain_reg domainreg;
	struct parsed_region_chan_11d parsed_region_chan;
	/** FSM variable for 11d support */
	u32 enable11d;
	/**	MISCELLANEOUS */
	u32 monitormode;
	u8 fw_ready;
	/* Command responses sent from the hardware to the driver */
	u8 resp_idx;
	u32 resp_len[1];/*������Ӧ�����ݳ���*/
	u8 resp_buf[1][LBS_UPLD_SIZE];/*������Ӧ�����ݻ���յ����ݰ�����ڴ�*/
	int mesh_open;
	int mesh_fw_ver;
	int infra_open;
	int mesh_autostart_enabled;
	
	u32 mac_offset;
	u32 bbp_offset;
	u32 rf_offset;
	u8 dnld_sent;

	uint16_t mesh_tlv;
	u8 mesh_ssid[IW_ESSID_MAX_SIZE + 1];
	u8 mesh_ssid_len;
	/*
 * In theory, the IE is limited to the IE length, 255,
 * but in practice 64 bytes are enough.
 */
    #define MAX_WPA_IE_LEN 64
	/** WPA Information Elements*/
	u8 wpa_ie[MAX_WPA_IE_LEN];/*wpa-psk ��psk��Կ*/
	u8 wpa_ie_len;
	u8 eapol_finish;/*wpa����epolͨ�����*/
	
};
#endif









#endif

