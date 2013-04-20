/*
 *  include/linux/mmc/sdio_func.h
 *
 *  Copyright 2007-2008 Pierre Ossman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 */

#ifndef MMC_SDIO_FUNC_H
#define MMC_SDIO_FUNC_H

#include "type.h"
#include "mmc.h"
#include "core.h"
#include "host.h"
#include "card.h"
#include "sdio.h"
#include "if_sdio.h"
#include "common.h"

struct sdio_func;

//typedef void (sdio_irq_handler_t)(struct sdio_func *);

/*
 * SDIO function CIS tuple (unknown to the core)
 */
struct sdio_func_tuple {
	struct sdio_func_tuple *next;
	unsigned char code;
	unsigned char size;
	unsigned char data[255];
};

/*
 * SDIO function devices
 */
 #define SDIO_STATE_PRESENT	(1<<0)		/* present in sysfs */
 /********************************************************
 һ��SDIO�豸���ܾ��ж�����ܣ����ṹ��������SDIO�豸�����еĹ�����Ϣ
 **********************************************************/
struct sdio_func {
	struct mmc_card		*card;		/* ������sdio��*/
	struct if_sdio_card		*if_card;/*if_sdio_card��marvell������صģ���¼�豸�汾���̼�����Ϣ�������ָ�룬ֻ��Ϊ��ʹ�ø�����*/
//	struct device		dev;		/* the device */
	sdio_irq_handler_t	*irq_handler;	/* �����жϴ����� */
	unsigned int		num;		/* ���й�����Ŀ */
	/*NB*/
	unsigned char		class;		/* �ӿ���*/
	unsigned short		vendor;		/* ���ܰ汾*/
	unsigned short		device;		/*�豸ID*/

	unsigned		max_blksize;	/*����֧�ֵ�����ߴ�,���豸�ڲ�����*/
	unsigned		cur_blksize;	/* ��ǰʹ�õĿ�ߴ� */

	unsigned		enable_timeout;	/* sdioִ�е����ʱʱ�� */

	unsigned int		state;		/* ����״̬*/


	u8			tmpbuf[4];	/*ʹ��DMAʱ������������ */

	unsigned		num_info;	/* �����������ַ�����Ϣ��Ŀ */
	const char		**info;		/* ��¼����������Ϣ������*/

	struct sdio_func_tuple *tuples;/*sdio����������Ϣ��*/
};

#define sdio_func_present(f)	((f)->state & SDIO_STATE_PRESENT)

#define sdio_func_set_present(f) ((f)->state |= SDIO_STATE_PRESENT)

#define sdio_func_id(f)		("80211card")

/*#define sdio_get_drvdata(f)	dev_get_drvdata(&(f)->dev)
#define sdio_set_drvdata(f,d)	dev_set_drvdata(&(f)->dev, d)
#define dev_to_sdio_func(d)	container_of(d, struct sdio_func, dev)*/

#define SDIO_ANY_ID (~0)

struct sdio_device_id {
	u8	class;			/* Standard interface or SDIO_ANY_ID */
	u16	vendor;			/* Vendor or SDIO_ANY_ID */
	u16	device;			/* Device ID or SDIO_ANY_ID */
};


/*
 * SDIO function device driver
 */
struct sdio_driver {
	char *name;
	struct sdio_device_id *id_table;
	char *(*probe)(struct sdio_func *, struct sdio_device_id *);//��������һ��˽�б���
	void (*remove)(struct sdio_func *);

	//struct device_driver drv;
};



#define sdio_get_drvdata(f)	 		(f->if_card)
#define sdio_set_drvdata(func, card) 	 func->if_card=card


//#define to_sdio_driver(d)	container_of(d, struct sdio_driver, drv)

#endif
