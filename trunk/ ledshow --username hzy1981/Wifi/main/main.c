#include "system.h"
#include "lwip.h"
#include "lwip/ip_addr.h"
#include "marvell_ops.h"
#include "parmcfg.h"
#include "netapp.h"
#include "config.h"

#if 1

static void dns_found_callbackx(const char *name, struct ip_addr *ipaddr, void *callback_arg){
}

void recv_mac_event(int event)
{
	//���յ������쳣����״̬��Ϊ����
	if (event == 3 || event == 8 || event == 9 || event == 14 || event == 13 )
	{
		pgmarvel_priv->connect_status = LBS_DISCONNECTED;
	}

	if (event == 999)
	{
		//Init_lwIP();
		//netbios_init();
	}
}

static int dns_test_test()
{
	char hostname[]="www.yeelink.net";
	struct ip_addr addr;
	err_t err;
	if (err = dns_gethostbyname((char*)(hostname), &(addr),dns_found_callbackx,NULL) == ERR_OK) {
	} else {
	}
}
#endif


void pollmac()
{
	extern struct netif netif;
	IWDG_ReloadCounter();
	ethernetif_input(&netif);
	IWDG_ReloadCounter();
	timer_thread();
	IWDG_ReloadCounter();
}

int  main (void)
{
	extern struct netif netif;
	extern int app_time;
	extern int app_time2;
	extern int newpower_time_out_current_state;
	extern int g_random;
	extern int g_imgbuf_index;
#if (USEOV2640 == 1)
	OV2640_IDTypeDef ov2640type;
#endif
	struct lbs_private *priv;
	char dhcp_ok=0;//using by dhcp
	long *cfg_ip;
	extern char * psk_out;
	int tmp;
	newpower_time_out_current_state = 0;

#if (USEOV2640 == 1)
	OV2640_HW_Init();
	memset(&ov2640type,0x0,sizeof(ov2640type));
	OV2640_ReadID(&ov2640type);
	OV2640_JPEGConfig(JPEG_320x240);        //����OV2640���320*240���ص�JPGͼƬ
	OV2640_BrightnessConfig(0x20);
	OV2640_AutoExposure(2);
#endif

	RCC_Configuration();   
	NVIC_Configuration();
	GPIO_Configuration();
	USART_Configuration(CONSOLE_UART);

	adc_init();
	MAR_POW(1);
#if (USEOV2640 == 1)
	printf("ov2640 chip id: 0x%02x , x%02x , x%02x , x%02x .\n",ov2640type.Manufacturer_ID1,ov2640type.Manufacturer_ID2,ov2640type.PIDH,ov2640type.PIDL);
#endif


#if (USEOV2640 == 1)
	OV2640_CaptureGpioInit();                               //���ݲɼ����ų�ʼ��
	disable_ov2640();

#endif

	printf("stm32 sdio\n");

	mem_init(); //�����Ȱ��ڴ��ʼ��Ū����

	printf("adc value : %d \n",get_adcval());
	g_random = get_adcval();

	//load_netcfg();//�����������ò���,�����Ҫ��������������Ϣ��FLASH������ش򿪴�ѡ������ڲ�flash���ܲ���Ч����ͻ����������һ���֡�

	priv=init_marvell_driver();//��ʼ��marvellģ������,����SDIO�豸ö�٣������豸�̼��Ȳ���*/
	lbs_scan_worker(priv);//ɨ��wifi������������priv->network�������У�ʹ��bss_descriptor�ṹ������*/
	printf("####################################### scanning finish !\r\n");
	psk_out = mem_malloc(32);
	marvel_assoc_network(priv,marvel_ssid,marvel_key,marvel_mode);//��������
	mem_free(psk_out);
	Init_lwIP();
	printf("init lwip finish .\r\n");

	UDP_Test();
	watch_dog_config();


	cfg_ip=(long *)wireless_ip;
	if(*cfg_ip!=0){//static ip,web config
		dhcp_ok=1;	
#if LWIP_DHCP_SERVER
		if(marvel_mode=='1')//adhoc mode start dhcp server
			dhcpsrv_start(&netif);//dhcp server start
#endif
		httpd_init();
		TCP_Client_Init(); 
		tcp_server_init();
		Yee_Client_Init();
		netbios_init();
	}

	//goto last
	while(1){
		if((priv->connect_status==LBS_DISCONNECTED)&&marvel_mode=='0')//AP����,��������,Ad-hoc������
		{
			printf("LBS_DISCONNECTED!!!\r\n");
#if (AUTO_CONN == 1)
			//����Ͽ����ӽ�����������
			config_delay();	
			config_delay();	
			config_delay();
			lbs_scan_worker(priv);//ɨ��wifi������������priv->network�������У�ʹ��bss_descriptor�ṹ������*/
			printf("####################################### re scanning finish !\r\n");
			psk_out = mem_malloc(32);
			marvel_assoc_network(priv,marvel_ssid,marvel_key,marvel_mode);//��������
			mem_free(psk_out);
#elif (AUTO_CONN == 2)
			NVIC_GenerateSystemReset(); // reset system
#else
			while(1);
#endif
		}

		pollmac(); // ��ѵ��������

		if(app_time>10){ // sleep 18 tick
			if (newpower_time_out_current_state != 8  && marvel_mode == 0)  //����ADHOCģʽ��timeout������8��ʱ���continue
				continue;

#if (YEELINK_ENABLE == 1)
			Yee_Client_ReInit();
			REQUEST_YEE();
#endif
			app_time=0;
		}

		if (app_time2 > 50)
		{
			app_time2 = 0;
		}
	}
}

// ------------------------------------------------------------------------------------------------------------
#if 0
	/***********************DHCP Assign IP**********************************************/

	while(0){ // �����ǹر�DHCP �ͻ���
		unsigned char *pchr;
		if((priv->connect_status==LBS_DISCONNECTED)&&
				marvel_mode=='0')//AP����,��������,Ad-hoc������
		{
			printf("LBS_DISCONNECTED!!!\r\n");
			//NVIC_GenerateSystemReset();
			config_delay();	
			config_delay();	
			config_delay();	
			lbs_scan_worker(priv);//ɨ��wifi������������priv->network�������У�ʹ��bss_descriptor�ṹ������*/
			printf("####################################### re scanning finish !\r\n");
			psk_out = mem_malloc(32);
			marvel_assoc_network(priv,marvel_ssid,marvel_key,marvel_mode);//��������
			mem_free(psk_out);
		}
		IWDG_ReloadCounter();
		ethernetif_input(&netif);
		IWDG_ReloadCounter();

		if((!dhcp_ok)&&(netif.dhcp!=NULL &&
					netif.dhcp->offered_ip_addr.addr!=0 &&
					netif.dhcp->offered_sn_mask.addr!=0 &&
					netif.dhcp->offered_gw_addr.addr!=0)){
			dhcp_ok=1;
			pchr=(unsigned char *)&netif.dhcp->offered_ip_addr.addr;
			printf("dhcp ip=%d:%d:%d:%d\n",pchr[0],pchr[1],pchr[2],pchr[3]);	
			pchr=(unsigned char *)&netif.dhcp->offered_gw_addr.addr;
			printf("dhcp gw=%d:%d:%d:%d\n",pchr[0],pchr[1],pchr[2],pchr[3]);	
			netif_set_addr(&netif, &(netif.dhcp->offered_ip_addr),
					&(netif.dhcp->offered_sn_mask),&(netif.dhcp->offered_gw_addr));
			printf("dhcp ok!\n");
			netif_set_default(&netif);    //reassign ip address
			netif_set_up(&netif);     
			ip_init();             
			dhcp_stop(&netif);	
			httpd_init();
			TCP_Client_Init(); 
			tcp_server_init();
			netbios_init();
		}
		else if(dhcp_ok)//assign ip address ok
			break;
	}
#endif
