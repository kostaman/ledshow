#define PARM_CONFIG__FILE__
#include "system.h"//ƽ̨���
#include "common.h"//Ӳ���޹ر�׼ͷ�ļ�
#include "marvell_ops.h"

char marvel_mode='1';
char marvel_ssid[32]={"Newpower_ADHOC"};
char marvel_key[32]={"1234567890123"};
char wireless_ip[4]={192,168,10,10};
char wireless_mask[4]={255,255,255,0};
char wireless_gw[4]={192,168,10,1};
char wireless_dns[4]={202,99,96,68}; // DNSҲ�ɲ��ظ���
char wireless_mac[6]={0x00,0x1D,0x2f,0x00,0x4e,0x2d}; //mac ��ַ���Բ��ظ���

/*****************************************
�������ΪADHOCģʽ�Ͱ�����������ӽ�������
char marvel_mode='1';
char marvel_ssid[32]={"Newpower_ADHOC"};
char marvel_key[32]={"1234567890123"};
char wireless_ip[4]={192,168,10,10};
char wireless_mask[4]={255,255,255,0};
char wireless_gw[4]={192,168,10,1};
char wireless_dns[4]={202,99,96,68}; // DNSҲ�ɲ��ظ���
char wireless_mac[6]={0x00,0x1D,0x2f,0x00,0x4e,0x2d}; //mac ��ַ���Բ��ظ���

�����������·������ô�Ͱ�����������ӽ�������
char marvel_mode='0';
char marvel_ssid[32]={"MYTEST"};		//����·����������
char marvel_key[32]={"12345679"};		//����·����������
char wireless_ip[4]={192,168,1,222};		//һ����·��������ͬһ���εĿ�������Ч��IP��ַ
char wireless_mask[4]={255,255,255,0};		//�������룬Ĭ�ϲ����޸�
char wireless_gw[4]={192,168,1,1};		//���ص�ַ��һ��Ϊ·�����ĵ�ַ
char wireless_dns[4]={202,99,96,68}; // DNSҲ�ɲ��ظ���
char wireless_mac[6]={0x00,0x1D,0x2f,0x00,0x4e,0x2d}; //mac ��ַ���Բ��ظ���

�����main�����п�����//load_netcfg ����������������ò�����Ч����ʱ�����ĸı���Ҫ���ⲿWEB���ƣ�
���������̻����Ǻ��˽�����ֽ��鲻Ҫʹ������ģʽ��
******************************************/


static int get_parmer(unsigned char *str,unsigned char *name,unsigned char *context,unsigned char chr)
{
	int cnt=0;
	unsigned char *parm;
	while(*context){
		if((*(context-1)!=chr)&&(*(context-1)!='?')){
			context++;
			continue;
		}
		if((memcmp(context,name,strlen((const char *)name))==0)&&
			(*(context+strlen((const char *)name))=='=')){//����ƥ������ԡ�=����ʼ����
			parm=context+strlen((const char *)name)+1;//"name=
			context+=(strlen((const char *)name)+1);
			while((*context!=chr)&&(*context!='\0')){//&��ʾ��������
				cnt++;
				context++;
			}
			memcpy(str,parm,cnt);//copy parm to str
			*(str+cnt)='\0';
			return 0;
		}
		else
			context++;	
	}
	return -1;//cann't find the parm
}


static int atohl(char *str,char hex)
{
	char bit_cnt=0;
	int index=1;
	int num=0;
	char chr;
	while(*str++){
		bit_cnt++;		
	}
	str-=2;
	while(bit_cnt--){
		if(!hex){
			chr=*str--;
			if((chr>'0'-1)&&(chr<'9'+1)){
				num+=(chr-'0')*index;
				index*=10;
			}
			else
				break;
		}
		else{
			chr=*str--;
			if((chr>'0'-1)&&(chr<'9'+1)){
				num+=(chr-'0')*index;
				index*=16;
			}
			else if((chr>'a'-1)&&(chr<'f'+1)){
				num+=((chr-'a')+10)*index;
				index*=16;
			}
			else if((chr>'A'-1)&&(chr<'F'+1)){
				num+=((chr-'A')+10)*index;
				index*=16;
			}
			else
				break;
		}
	}
	return num;
}
static void para_string(unsigned char *str)
{
	 unsigned char tmp[32];
	//infra or adhoc 
	get_parmer(tmp,"NET",str,'&');
	marvel_mode=tmp[0];
	
	//ssid
	get_parmer(tmp,"SSID",str,'&');
	sprintf((char *)marvel_ssid,"%s",tmp);

	//ssid
	get_parmer(tmp,"KEY",str,'&');
	sprintf((char *)marvel_key,"%s",tmp);

	//wireless ip
	get_parmer(tmp,"WIP1",str,'&');
	wireless_ip[0]=atohl((char *)tmp,0);
	get_parmer((unsigned char *)tmp,"WIP2",str,'&');
	wireless_ip[1]=atohl((char *)tmp,0);
	get_parmer(tmp,"WIP3",str,'&');
	wireless_ip[2]=atohl((char *)tmp,0);
	get_parmer(tmp,"WIP4",str,'&');
	wireless_ip[3]=atohl((char *)tmp,0);
	//�����޸�	
	memcpy(wireless_mac,pgmarvel_priv->current_addr,6);
	//mask
	get_parmer(tmp,"MASK1",str,'&');
	wireless_mask[0]=atohl((char *)tmp,0);
	get_parmer(tmp,"MASK2",str,'&');
	wireless_mask[1]=atohl((char *)tmp,0);
	get_parmer(tmp,"MASK3",str,'&');
	wireless_mask[2]=atohl((char *)tmp,0);
	get_parmer(tmp,"MASK4",str,'&');
	wireless_mask[3]=atohl((char *)tmp,0);
	//gw
	get_parmer(tmp,"GW1",str,'&');
	wireless_gw[0]=atohl((char *)tmp,0);
	get_parmer(tmp,"GW2",str,'&');
	wireless_gw[1]=atohl((char *)tmp,0);
	get_parmer(tmp,"GW3",str,'&');
	wireless_gw[2]=atohl((char *)tmp,0);
	get_parmer(tmp,"GW4",str,'&');
	wireless_gw[3]=atohl((char *)tmp,0);
	//dns
	get_parmer(tmp,"DNS1",str,'&');
	wireless_dns[0]=atohl((char *)tmp,0);
	get_parmer(tmp,"DNS2",str,'&');
	wireless_dns[1]=atohl((char *)tmp,0);
	get_parmer(tmp,"DNS3",str,'&');
	wireless_dns[2]=atohl((char *)tmp,0);
	get_parmer(tmp,"DNS4",str,'&');
	wireless_dns[3]=atohl((char *)tmp,0);
}


void config_delay(void)
{
	int i=1000;
	long j=36000;
	while(i--){
		j=36000;
		while(j--);
	}
}
//default system config

/*
        ����˵��
        NET=1 AD-HOC ģʽ
        NET=0 ������ģʽ

        KEY="����Ҫ������,��������һ��Ҫ��13λ����һλ��һλ������Ŷ ^_^" 

        ������Ҫ�뽨��һ��SSID��ΪNewPower_ADHOC������Ϊ1234567890123 ip ��ַΪ 192.168.1.10 ��AD-HOC ������ô
        default_cfg[] ��Ӧ���ַ���ӦΪ
        {"Route?NET=1&SSID=NewPower_ADHOC&KEY=1234567890123&WIP1=192&WIP2=168&WIP3=001&WIP4=010&MASK1=255&MASK2=255&MASK3=255&MASK4=000&GW1=192&GW2=168&GW3=001&GW4=001&DNS1=202&DNS2=096&DNS3=134&DNS4=133&WMAC0=00&WMAC1=1A&WMAC2=6B&WMAC3=6E&WMAC4=82&WMAC5=0E&OK=%B1%A3%B4%E6"};

        ������������һ��SSID��Ϊ TESTWIFI WEP ������1234567890123 ��·����IPΪ 192.168.1.1 ����ָ��IPΪ 192.168.1.10
        default_cfg[] ��Ӧ���ַ���ӦΪ
        {"Route?NET=1&SSID=TESTWIFI&KEY=1234567890123&WIP1=192&WIP2=168&WIP3=001&WIP4=010&MASK1=255&MASK2=255&MASK3=255&MASK4=000&GW1=192&GW2=168&GW3=001&GW4=001&DNS1=202&DNS2=096&DNS3=134&DNS4=133&WMAC0=00&WMAC1=1A&WMAC2=6B&WMAC3=6E&WMAC4=82&WMAC5=0E&OK=%B1%A3%B4%E6"};
*/


//const char default_cfg[]={"Route?NET=0&SSID=softap&KEY=12345679&WIP1=192&WIP2=168&WIP3=123&WIP4=010&MASK1=255&MASK2=255&MASK3=255&MASK4=000&GW1=192&GW2=168&GW3=123&GW4=001&DNS1=202&DNS2=096&DNS3=134&DNS4=133&WMAC0=00&WMAC1=1A&WMAC2=6B&WMAC3=6E&WMAC4=82&WMAC5=0E&OK=%B1%A3%B4%E6"};

#if 1
const char default_cfg[]={"\
Route?NET=1\
&SSID=Newpower_ADHOC\
&KEY=1234567890123\
&WIP1=192\
&WIP2=168\
&WIP3=010\
&WIP4=010\
&MASK1=255\
&MASK2=255\
&MASK3=255\
&MASK4=000\
&GW1=192\
&GW2=168\
&GW3=010\
&GW4=001\
&DNS1=202&DNS2=096&DNS3=134&DNS4=133\
&WMAC0=00&WMAC1=1A&WMAC2=6B&WMAC3=6E&WMAC4=82&WMAC5=0E&OK=%B1%A3%B4%E6"};

#endif

#define FLASH_START_ADDR	((u32)0x0803F800)//250K
/*����Ĭ��������Ϣ������FLASH_START_ADDR��ָ����flash��ַ��
ģ���ϵ�ʱ�Զ���ȡ������struct marvell_cfg�ṹ��*/
void write_flash_config(u16 *buf,int len)
{
	write_flash(FLASH_START_ADDR,buf,len);
}
/***********************************************************************************************
****������:load_netcfg
****����:�ָ����������flash������
****����:��
****����:0:ʧ�� ����:struct lbs_private *
***********************************************************************************************/

int load_netcfg(void)
{
#if 0
	int len=10;
	char str_tmp[256];
	//char *p=str_tmp;
	if(!DEFAULT_PIN){//�а���
		config_delay();
		if(!DEFAULT_PIN){//ȷ�ϰ���
			write_flash_config((u16 *)default_cfg,sizeof(default_cfg));
			while(!DEFAULT_PIN);//�ȴ���������λ
			NVIC_GenerateSystemReset();
			return 0;
		}
	}
	read_flash(FLASH_START_ADDR,(u16 *)str_tmp,256);
	if(len==0)
		return -1;
	para_string((unsigned char *)str_tmp);
#else
	para_string((unsigned char *)default_cfg);
#endif
	return 0;
}

