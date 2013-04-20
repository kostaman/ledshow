#ifndef __COMMON__H__
#define __COMMON__H__
#include "xxxconfig.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "type.h"
#include "system.h"
#include "s3cmci.h"




enum { MSG_MSGDUMP, MSG_DEBUG, MSG_INFO, MSG_WARNING, MSG_ERROR };


#define KERN_WARNING 
#define KERN_ERR
#define KERN_DEBUG
#define KERN_INFO

#define min(x1,x2) (((x1)<(x2))? (x1):(x2))
#define max(x1,x2) (((x1)>(x2))? (x1):(x2))
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))



#define HZ 1000
#define jiffies 0
#define MAX_ERRNO	4095
#define roundup(x, y) ((((x) + ((y) - 1)) / (y)) * (y))
#define IS_ERR_VALUE(x) (x<0||x==0)

/* define compiler specific symbols */
#if defined (__ICCARM__)

#define PACK_STRUCT_BEGIN	#pragma pack(1)
#define PACK_STRUCT_STRUCT 	
#define PACK_STRUCT_END	#pragma pack(0)
#define __inline 			inline
#define STRUCT_PACKED 		

#elif defined (__CC_ARM)

#define STRUCT_PACKED		__attribute__((packed))

#elif defined (__GNUC__)

#define STRUCT_PACKED __attribute__ ((__packed__))

#elif defined (__TASKING__)

#define STRUCT_PACKED 
#endif




/**************wpa��غ궨��***********************************/



#ifndef __OS_LIB__H__

#define os_memcpy memcpy
#define os_strlen strlen
#define os_memset memset
#define os_memcmp memcmp

#endif




#ifndef bswap_16
#define bswap_16(a) ((((u16) (a) << 8) & 0xff00) | (((u16) (a) >> 8) & 0xff))
#endif

#ifndef bswap_32
#define bswap_32(a) ((((u32) (a) << 24) & 0xff000000) | \
		     (((u32) (a) << 8) & 0xff0000) | \
     		     (((u32) (a) >> 8) & 0xff00) | \
     		     (((u32) (a) >> 24) & 0xff))
#endif


#ifndef __BYTE_ORDER
#ifndef __LITTLE_ENDIAN
#ifndef __BIG_ENDIAN
#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN 4321
#define __BYTE_ORDER __LITTLE_ENDIAN
#endif /* __BIG_ENDIAN */
#endif /* __LITTLE_ENDIAN */
#endif /* __BYTE_ORDER */

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define le_to_host16(n) (n)
#define host_to_le16(n) (n)
#define be_to_host16(n) bswap_16(n)
#define host_to_be16(n) bswap_16(n)
#define le_to_host32(n) (n)
#define be_to_host32(n) bswap_32(n)
#define host_to_be32(n) bswap_32(n)
#define le_to_host64(n) (n)
#define host_to_le64(n) (n)
//#define be_to_host64(n) bswap_64(n)
//#define host_to_be64(n) bswap_64(n)
#elif __BYTE_ORDER == __BIG_ENDIAN
#define le_to_host16(n) bswap_16(n)
#define host_to_le16(n) bswap_16(n)
#define be_to_host16(n) (n)
#define host_to_be16(n) (n)
#define le_to_host32(n) bswap_32(n)
#define be_to_host32(n) (n)
#define host_to_be32(n) (n)
//#define le_to_host64(n) bswap_64(n)
//#define host_to_le64(n) bswap_64(n)
#define be_to_host64(n) (n)
#define host_to_be64(n) (n)
#ifndef WORDS_BIGENDIAN
#define WORDS_BIGENDIAN
#endif
#else
#error Could not determine CPU byte order
#endif

#define PRIVATE1 priv->__mac_addr,priv->current_addr,psk_out
#define PRIVATE2 priv->__wpa_ie,&(priv->__wpa_ie_len) 


/*****************************����������**********************************************/
#define try_bug(val) 	do {if(val) break;}while(1)
#define Uart_Printf printf
#define printk Uart_Printf
#define pr_err Uart_Printf
#define lbs_pr_err Uart_Printf

#define RUN_TEST printk("RUN_TEST >>> LINE:%d ,,, FUNCTION:%s ,,, FILE:%s \r\n",__LINE__,__FUNCTION__,__FILE__);
static void xdbug_buf(const char * name , const unsigned char * buf , const int len)
{
	int i = 0;
	printf("dbug buf [%s]\n",name);
	for(;i<len;i++)
	{
		printf("0x%02x,",buf[i]);
	}
	printf("\n");
}
#define DEBUG_PARAM_SDIO
#define pr_sdio_interrupt(arg...) //void_dbg//Uart_Printf
#define printf_scan printf
#define lbs_pr_alert(arg...) 
#define lbs_deb_host(arg...)  
#define lbs_deb_thread(arg...)  
#define lbs_pr_debug(arg...) // void_dbg
#define lbs_pr_info(arg...) // void_dbg//Uart_Printf//
#define lbs_deb_cmd(arg...) // lbs_pr_info
#define lbs_deb_tx(arg...) // void_dbg//lbs_pr_info
#define lbs_deb_11d(arg...)// void_dbg


#define lbs_deb_sdio(arg...)//		Uart_Printf
#define lbs_deb_scan		Uart_Printf
#define lbs_deb_assoc 		Uart_Printf
#define lbs_deb_join  		Uart_Printf


#define pr_fifo_debug(arg...)// void_dbg//Uart_Printf
#define pr_debug(arg...)// void_dbg//Uart_Printf
#define pr_warning(arg...)// void_dbg//Uart_Printf
#define dbg(arg...)//void_dbg//Uart_Printf
#define  marvell_error Uart_Printf


#define sdio_deb_enter() 	    //Uart_Printf("enter %s\n",__func__)
#define sdio_deb_leave()	    //Uart_Printf("leave %s \n",__func__)

#define lbs_deb_rx Uart_Printf

#define dbg_netdata(info,buf,size)	 debug_data_stream(info,buf,size)	


#define lbs_deb_enter(fmt)    	     //Uart_Printf("enter %s\n",__func__)
#define lbs_deb_leave(fmt)		     //Uart_Printf("leave %s \n",__func__)
#define lbs_deb_cmd_enter(fmt)    	   
#define lbs_deb_cmd_leave(fmt)	  
#define lbs_deb_enter_args(fmt,arg) //Uart_Printf("enter %s (ret=%d)\n",__func__,arg)
#define lbs_deb_leave_args(fmt,arg) //Uart_Printf("leave %s (ret=%d)\n",__func__,arg)
#define lbs_deb_cmd_enter_args(fmt,arg) 
#define lbs_deb_cmd_leave_args(fmt,arg) 


#define MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"




void mmc_delay(unsigned int time);
void ms_delay(void);
void  mdelay(unsigned long time);
#define 	msleep	mdelay
bool time_after(char res, unsigned long *time_out);
const char *print_ssid(char *buf, const char *ssid, u8 ssid_len);
u8 convert_from_bytes_to_power_of_two(u16 NumberOfBytes);
void  *ERR_PTR(long error);
long  PTR_ERR(const void *ptr);
long  IS_ERR(const void *ptr);
void  lbs_hex(unsigned int grp, const char *prompt, u8 *buf, int len);
#define lbs_deb_hex lbs_hex
#if 0  // ��������ĺ���������WPA_COMMON ��ͻ���������ʱע�͵�
void wpa_hexdump(int level, const char *title, const u8 *buf, size_t len);
void wpa_hexdump_key(int level, const char *title, const u8 *buf, size_t len);
void wpa_printf(int level, char *fmt, ...);
void  void_dbg(void *fmt,...);
void debug_data_stream(char *info,char *pdata,u16 len);
#endif
#define INSERT_PARMA_INFO Ox0000008F(PRIVATE1);Ox0000008D(PRIVATE2);

#endif 
