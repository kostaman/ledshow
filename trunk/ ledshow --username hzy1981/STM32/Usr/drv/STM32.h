#ifndef STM32_H
#define STM32_H

//#if QT_EN == 0
//#include "LED_Cfg.h"

#undef EXT
#ifdef STM32_C
#define EXT
#else
#define EXT extern
#endif

//定义断言,多多使用，有益身心
#if ASSERT_EN>0
#define ASSERT(x) //Assert((BOOL)(x),__FILE__,__FUNCTION__,(INT16U)__LINE__)
#define ASSERT_FAILED() //Assert_Failed(__FILE__,__FUNCTION__,(INT16U)__LINE__)
#else
#define ASSERT(x)
#define ASSERT_FAILED()
#endif

#define SPI_FLASH_CS_HIGH() SET_FLASH_CS(1)
#define SPI_FLASH_CS_LOW() SET_FLASH_CS(0)
 
#define SET_SHIFT_BIT(Block, Data, i) do{\
     if(Block EQ 0)\
	 {\
	   SET_R1(GET_BIT(Data[0], i));\
	   SET_G1(GET_BIT(Data[1], i));\
	   SET_B1(GET_BIT(Data[2], i));\
	 }\
	 else if(Block EQ 1)\
	 { \
	   SET_R2(GET_BIT(Data[0], i));\
	   SET_G2(GET_BIT(Data[1], i));\
	   SET_B2(GET_BIT(Data[2], i));\
	 }\
	 else if(Block EQ 2)\
	 {\
	   SET_R3(GET_BIT(Data[0], i));\
	   SET_G3(GET_BIT(Data[1], i));\
	   SET_B3(GET_BIT(Data[2], i));\
	 }\
	 else if(Block EQ 3)\
	 {\
	   SET_R4(GET_BIT(Data[0], i));\
	   SET_G4(GET_BIT(Data[1], i));\
	   SET_B4(GET_BIT(Data[2], i));\
	 }\
	 else if(Block EQ 4)\
	 {\
	   SET_R5(GET_BIT(Data[0], i));\
	   SET_G5(GET_BIT(Data[1], i));\
	   SET_B5(GET_BIT(Data[2], i));\
	 }\
	 else if(Block EQ 5)\
	 {\
	   SET_R6(GET_BIT(Data[0], i));\
	   SET_G6(GET_BIT(Data[1], i));\
	   SET_B6(GET_BIT(Data[2], i));\
	 }\
	 else if(Block EQ 6)\
	 {\
	   SET_R7(GET_BIT(Data[0], i));\
	   SET_G7(GET_BIT(Data[1], i));\
	   SET_B7(GET_BIT(Data[2], i));\
	 }\
	 else if(Block EQ 7)\
	 {\
	   SET_R8(GET_BIT(Data[0], i));\
	   SET_G8(GET_BIT(Data[1], i));\
	   SET_B8(GET_BIT(Data[2], i));\
	 }\
	 else\
	 {\
       ASSERT_FAILED();\
	 }\
}while(0);

typedef unsigned int INT32U;
typedef int INT32S;
typedef unsigned short int INT16U;
typedef short int INT16S;
typedef unsigned char INT8U;
typedef char INT8S;
typedef unsigned char BOOL;


#ifndef DEF_WR_PHY_MEM
//读物理存储器
EXT INT8U Read_PHY_Mem(INT32U Offset, void *pDst, INT16U RD_Len, void *pDst_Start, INT16U DstLen);
//写物理存储器
EXT INT8U Write_PHY_Mem(INT32U Offset, void *pSrc, INT16U SrcLen);
#endif

EXT void delay_init(INT8U SYSCLK);
EXT void delay_ms(INT16U nms);
EXT void delay_us(INT32U nus);
EXT void SPI1_Init(void);
EXT INT8U SPI1_ReadWrite(INT8U writedat);
EXT void NVIC_Configuration(void);
EXT void TIM2_Configuration(void);
EXT void TIM4_Configuration(void);
EXT void TIM3_Configuration(void);
EXT void SPI1_FLASH_Init(void);
EXT void SPI1_CH376_Init(void);
#endif
