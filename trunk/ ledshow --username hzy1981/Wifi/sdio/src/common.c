#include "common.h"
#include "stdarg.h"
int g_random;
static  int wpa_debug_show_keys = 1;
extern  int wpa_debug_level;
static void _wpa_hexdump(int level, const char *title, const u8 *buf,
			 size_t len, int show)
{
	size_t i;
	if (level < wpa_debug_level)
		return;
	printf("%s - hexdump(len=%lu):", title, (unsigned long) len);
	if (buf == NULL) {
		printf(" [NULL]");
	} else if (show) {
		for (i = 0; i < len; i++)
			printf(" %02x", buf[i]);
	} else {
		printf(" [REMOVED]");
	}
	printf("\n");
}
void wpa_printf(int level, char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	if (level >= wpa_debug_level) {
		vprintf(fmt, ap);
		printf("\n");
	}
	va_end(ap);
}

void wpa_hexdump_key(int level, const char *title, const u8 *buf, size_t len)
 {
	 _wpa_hexdump(level, title, buf, len, wpa_debug_show_keys);
 }

 void wpa_hexdump(int level, const char *title, const u8 *buf, size_t len)
 {
	 _wpa_hexdump(level, title, buf, len, 1);
 }

 void  void_dbg(void *fmt,...)
{
    return;
}

 long  PTR_ERR(const void *ptr)
{
	return (long) ptr;
}
 long  IS_ERR(const void *ptr)
{
	return IS_ERR_VALUE((long)ptr);
}


 void  *ERR_PTR(long error)
{
	return (void *) error;
}
 void  lbs_hex(unsigned int grp, const char *prompt, u8 *buf, int len)
{
	int i = 0;
	if (len )
	{
		for (i = 1; i <= len; i++) {
			if ((i & 0xf) == 1) {
				if (i != 1)
					printf("\n");
				printk("marvell" " %s: ", prompt);
			}
			printf("%02x ", (u8) * buf);
			buf++;
		}
		printf("\n");
	}
}
void mmc_delay(unsigned int time)
{
	unsigned long i,ii;
	for(i=0;i<time;i++)
	{	
		ii=72000;
		while(ii--);
	}
}
void ms_delay(void)
{
	unsigned long i=72000;
	while(i--);
}


void  mdelay(unsigned long time)
{
	while(time--)
		ms_delay();
}


bool time_after(char res, unsigned long *time_out)
{
	unsigned long i=(*time_out);
	ms_delay();
	if(i){
		*time_out=i-1;
		return false;
	}
	return true;//time_out=0
}




 /*
int snprintf(char * buf, size_t size, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i=vsnprintf(buf,size,fmt,args);
	va_end(args);
	return i;
}
	   */

const char *print_ssid(char *buf, const char *ssid, u8 ssid_len)
{
	const char *s = ssid;
	char *d = buf;

	ssid_len = min(ssid_len, 32);
	while (ssid_len--) {
		if (isprint(*s)) {
			*d++ = *s++;
			continue;
		}

		*d++ = '\\';
		if (*s == '\0')
			*d++ = '0';
		else if (*s == '\n')
			*d++ = 'n';
		else if (*s == '\r')
			*d++ = 'r';
		else if (*s == '\t')
			*d++ = 't';
		else if (*s == '\\')
			*d++ = '\\';
		else
			d += snprintf(d, 3, "%03o", *s);
		s++;
	}
	*d = '\0';
	return buf;
}

/*
void debug_data_stream(char *info,char *pdata,u16 len)
{
	u16 i;
	printk("%s(len=%d):\n",info,len);
	for(i=0;i<len;i++){	
		if((!(i%10))&&(i))
			printk("\n");
		printk("0x%2x     ",*pdata++);			
	}
	printk("\n");
}	 */

 u8 convert_from_bytes_to_power_of_two(u16 NumberOfBytes)
{
  u8 count = 0;

  while (NumberOfBytes != 1)
  {
    NumberOfBytes >>= 1;
    count++;
  }
  return(count);
}



/*

void pr_debug(void *fmt,...);
void pr_warning(void *fmt,...);
void printk(void *fmt,...);
void dbg(void *fmt,...);*/

