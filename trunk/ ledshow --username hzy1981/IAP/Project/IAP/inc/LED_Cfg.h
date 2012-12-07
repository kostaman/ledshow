#ifndef LED_CFG_H
#define LED_CFG_H

//#define CARD_A

#ifdef CARD_A
#define HSE_VALUE 12000000 //�ⲿ����Ƶ��
#define HCLK_VALUE  HSE_VALUE*3
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_3	//��������ʱAHB�ٶ�
#define PCLK1_DIV RCC_HCLK_Div2 //���APB/2--������������ʱ�ٶ�,���ﲻ��ΪDIV1����Ϊ��ʱ��ʹ�õķ�Ƶϵ��Ĭ��PCLK1��Ƶ>1
#define PCLK2_DIV RCC_HCLK_Div1 //��ߺ�AHBһ��,ע��SPIFlash���ٶ���APB2/2���ܳ���50M,CH376���ٶ���APB2/8���ܳ���24M

#elif defined(CARD_B)
#define HSE_VALUE 12000000 //�ⲿ����Ƶ��
#define HCLK_VALUE  HSE_VALUE*6
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_6	//��������ʱAHB�ٶ�
#define PCLK1_DIV RCC_HCLK_Div2 //���APB/2--������������ʱ�ٶ�,���ﲻ��ΪDIV1����Ϊ��ʱ��ʹ�õķ�Ƶϵ��Ĭ��PCLK1��Ƶ>1
#define PCLK2_DIV RCC_HCLK_Div1 //��ߺ�AHBһ��,ע��SPIFlash���ٶ���APB2/2���ܳ���50M,CH376���ٶ���APB2/4���ܳ���24M

#elif defined(CARD_C) || defined(CARD_CW)

#define HSE_VALUE 25000000 //�ⲿ����Ƶ��
#define HCLK_VALUE  72000000
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_9	//��������ʱAHB�ٶ�
#define PCLK1_DIV RCC_HCLK_Div2 //���APB/2--������������ʱ�ٶ�,���ﲻ��ΪDIV1����Ϊ��ʱ��ʹ�õķ�Ƶϵ��Ĭ��PCLK1��Ƶ>1
#define PCLK2_DIV RCC_HCLK_Div1 //��ߺ�AHBһ��,ע��SPIFlash���ٶ���APB2/2���ܳ���50M,CH376���ٶ���APB2/8���ܳ���24M

#elif defined(CARD_D)

#define HSE_VALUE 12000000 //�ⲿ����Ƶ��
#define HCLK_VALUE  HSE_VALUE*7
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_7	//��������ʱAHB�ٶ�
#define PCLK1_DIV RCC_HCLK_Div2 //���APB/2--������������ʱ�ٶ�,���ﲻ��ΪDIV1����Ϊ��ʱ��ʹ�õķ�Ƶϵ��Ĭ��PCLK1��Ƶ>1
#define PCLK2_DIV RCC_HCLK_Div1 //��ߺ�AHBһ��,ע��SPIFlash���ٶ���APB2/2���ܳ���50M,CH376���ٶ���APB2/8���ܳ���24M

#endif

#define CMD_STRING_SIZE       128

#ifdef CARD_CW
#define ApplicationAddress    0x8008000
#else
#define ApplicationAddress    0x8001000
#endif

#define PAGE_SIZE                         (0x400)    /* 1 Kbyte */
#define FLASH_SIZE                        (0x20000)  /* 128 KBytes */

#if 0
#if defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
 #define PAGE_SIZE                         (0x400)    /* 1 Kbyte */
 #define FLASH_SIZE                        (0x20000)  /* 128 KBytes */
#elif defined STM32F10X_CL
 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x40000)  /* 256 KBytes */
#elif defined STM32F10X_HD || defined (STM32F10X_HD_VL)
 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x80000)  /* 512 KBytes */
#elif defined STM32F10X_XL
 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x100000) /* 1 MByte */
#else 
 #error "Please select first the STM32 device to be used (in stm32f10x.h)"    
#endif
#endif

#endif
