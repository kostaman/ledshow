#ifndef INCLUDES_H
#define INCLUDES_H

#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include <math.h>
#include "time.h"
#include "LED_Cfg.h"
#include "OS_Includes.h"
//#include "QT_SIM.h"
//#include "STM32.h"
//#include "spi_flash.h"
#include "pub.h"
#include "nongli.h"
#include "zk.h"
#include <stdlib.h>
#include "LED_Cfg.h"

#if QT_EN == 0
//#include <intrinsic.h>
#include "stm32f10x_conf.h"
#include "STM32.h"
#include "DS1302.h"
#include "SHT1X.h"
#include "DS18B20.h"

#if UDISK_EN
#ifdef CHIP_USB_HOST
#include "usbh_usr.h"
#include "usb_bsp.h"
#else
#include "CH376INC.h"
#include "ch376.h"
#include "FILE_SYS.h"
#endif
#include "UDisk_Proc.h"
#endif


#if NET_EN
#include "ENC28J60.h"
#include "EMAC.h"
#endif

#if GPRS_EN || SMS_EN
#include "SIM900a.h"
#endif

#if SMS_EN || GPRS_EN
#include "sms.h"
#endif

#include "spi_flash.h"
#include "LED_Scan.h"
#endif

#if SMS_EN
#include "sms_show.h"
#endif

#include "Storage.h"
#include "LED_Para.h"
#include "LED_Show.h"
#include "Screen_Status.h"
#include "Txt_Show.h"
#include "Time_Show.h"
#include "Pic_Show.h"
#include "Flash_Show.h"
#include "Clock_Show.h"
#include "Timer_Show.h"
#include "Temp_Show.h"
#include "Lun_Show.h"
#include "Humidity_Show.h"
#include "Noise_Show.h"
#include "Border_Show.h"
#include "Main_Show.h"
#include "com.h"
#include "Shell.h"
#include "Net_Proc.h"
#endif










