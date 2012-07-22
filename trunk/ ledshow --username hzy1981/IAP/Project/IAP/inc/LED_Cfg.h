#ifndef LED_CFG_H
#define LED_CFG_H

#ifdef CARD_A
#define HSE_VALUE 12000000 //外部晶振频率
#define HCLK_VALUE  HSE_VALUE*3
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_3	//正常运行时AHB速度
#define PCLK1_DIV RCC_HCLK_Div2 //最高APB/2--这是正常运行时速度,这里不能为DIV1，因为定时器使用的分频系数默认PCLK1分频>1
#define PCLK2_DIV RCC_HCLK_Div1 //最高和AHB一样,注意SPIFlash的速度是APB2/2不能超过50M,CH376的速度是APB2/8不能超过24M

#elif defined(CARD_B)
#define HSE_VALUE 12000000 //外部晶振频率
#define HCLK_VALUE  HSE_VALUE*6
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_6	//正常运行时AHB速度
#define PCLK1_DIV RCC_HCLK_Div2 //最高APB/2--这是正常运行时速度,这里不能为DIV1，因为定时器使用的分频系数默认PCLK1分频>1
#define PCLK2_DIV RCC_HCLK_Div1 //最高和AHB一样,注意SPIFlash的速度是APB2/2不能超过50M,CH376的速度是APB2/4不能超过24M

#elif defined(CARD_C)

#define HSE_VALUE 25000000 //外部晶振频率
#define HCLK_VALUE  72000000
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_9	//正常运行时AHB速度
#define PCLK1_DIV RCC_HCLK_Div2 //最高APB/2--这是正常运行时速度,这里不能为DIV1，因为定时器使用的分频系数默认PCLK1分频>1
#define PCLK2_DIV RCC_HCLK_Div1 //最高和AHB一样,注意SPIFlash的速度是APB2/2不能超过50M,CH376的速度是APB2/8不能超过24M

#elif defined(CARD_D)

#define HSE_VALUE 12000000 //外部晶振频率
#define HCLK_VALUE  HSE_VALUE*7
//#define H_HCLK_VALUE HSE_VALUE*9
#define PCLK1_VALUE HCLK_VALUE/2
#define PCLK2_VALUE	HCLK_VALUE/1

#define HCLK_MUL  RCC_PLLMul_7	//正常运行时AHB速度
#define PCLK1_DIV RCC_HCLK_Div2 //最高APB/2--这是正常运行时速度,这里不能为DIV1，因为定时器使用的分频系数默认PCLK1分频>1
#define PCLK2_DIV RCC_HCLK_Div1 //最高和AHB一样,注意SPIFlash的速度是APB2/2不能超过50M,CH376的速度是APB2/8不能超过24M

#endif
#endif
