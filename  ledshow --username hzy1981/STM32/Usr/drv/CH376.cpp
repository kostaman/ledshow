/*******************************************************************************

 * * * �ļ����ƣ�ch376.c

 * * * �ļ�˵����CH376оƬ SPI�������ӵ�Ӳ������� V1.0

 * * * �������ڣ�PowerAVR / 2009-12-19

 * * * �޸����ڣ� 


*******************************************************************************/
/*
#include "stm32f10x.h"
#include "LED_Cfg.h"
#include "CH376INC.h"
#include "ch376.h"
#include "stm32.h"
*/
#include "includes.h"
//#include "USART.h"

//extern INT8U SPI1_ReadWrite(INT8U writedat);
//#include "Includes.h"
/*
unsigned char CH376_ReadWrite(unsigned char writedat)
{
  return SPI1_ReadWrite(writedat);

}*/
/*****************************************************

 * Name:     mInitCH376Host

 * Function: ��ʼ��CH376

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8 mInitCH376Host( void )  
{
 u8 res;
 
 xWriteCH376Cmd( CMD11_CHECK_EXIST );  			/* ���Ե�Ƭ����CH376֮���ͨѶ�ӿ� */
 xWriteCH376Data( 0x65 );
 res = xReadCH376Data( );
 xEndCH376Cmd( );								// ����ͨ�Ų���
 if ( res != 0x9A ) 
 {
 	//USART1_SendByte(0xe1);
 	return( ERR_USB_UNKNOWN );  				/* ͨѶ�ӿڲ�����,����ԭ����:�ӿ������쳣,�����豸Ӱ��(Ƭѡ��Ψһ),���ڲ�����,һֱ�ڸ�λ,���񲻹��� */
 }
 xWriteCH376Cmd( CMD11_SET_USB_MODE );  		/* �豸USB����ģʽ */
 xWriteCH376Data( 0x06 );						// ģʽ����Ϊ0x06,��ʾ�л��������õ�USB������ʽ���Զ�����SOF��
 mDelayuS( 20 );
 res = xReadCH376Data( );						// ���ز���״̬
 xEndCH376Cmd( );							    // ����ģʽ���ý���

 xWriteCH376Cmd( CMD20_SET_SDO_INT );  			/* ����SPI��SDO���ŵ��жϷ�ʽ */
 xWriteCH376Data( 0x16 );
 xWriteCH376Data( 0x90 );  						/* SDO������SCSƬѡ��Чʱ�����ж�������� */
 xEndCH376Cmd( );							    // ��������SDO���ŷ�ʽ


 if ( res == CMD_RET_SUCCESS ) 
 	return( USB_INT_SUCCESS );
 else 
 {
 	//USART1_SendByte(0xe2);
 	return( ERR_USB_UNKNOWN );  				/* ����ģʽ���� */
 }	
}
/*****************************************************

 * Name:     CH376_PORT_INIT

 * Function: ��ʼ��CH376��SPI IO��

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8 mWaitInterrupt( void ) 
{								/* �ȴ�CH376�жϲ���ȡ״̬,�����˵ȴ��������,���ز���״̬ */
 while ( Query376Interrupt( ) == FALSE );  		/* һֱ���ж� */ 				
 xWriteCH376Cmd( CMD_GET_STATUS );  			/* ������������ж�,��ȡ�ж�״̬ */
 return( xReadCH376Data( ) );
}

/*****************************************************

 * Name:     xWriteCH376Cmd

 * Function: д���CH376ȥ

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
void	xWriteCH376Cmd( u8 mCmd )  /* ��CH376д���� */
{
    SET_CH376_CS(1);
	//GPIO_SetBits(GPIOA,GPIO_Pin_1);  /* ��ֹ֮ǰδͨ��xEndCH376Cmd��ֹSPIƬѡ */
	mDelay0_5uS( );
/* ����˫��I/O����ģ��SPI�ӿ�,��ô����ȷ���Ѿ�����SPI_SCS,SPI_SCK,SPI_SDIΪ�������,SPI_SDOΪ���뷽�� */
	//GPIO_ResetBits(GPIOA,GPIO_Pin_1);  /* SPIƬѡ��Ч */
	SET_CH376_CS(0);
	CH376_ReadWrite( mCmd );  /* ���������� */

//	DelayXms(1);;  /* ��ʱ1.5uSȷ����д���ڴ���1.5uS,����������һ�е�״̬��ѯ���� */

}
/*****************************************************

 * Name:     xWriteCH376Data

 * Function: д1�ֽ����ݵ�CH376

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
void	xWriteCH376Data( u8 mData )  /* ��CH376д���� */
{
	CH376_ReadWrite( mData );
//	mDelay0_5uS( );  /* ȷ����д���ڴ���0.6uS */
}

/*****************************************************

 * Name:     xReadCH376Data

 * Function: ��CH376��ȡ1�ֽ�����

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8	xReadCH376Data( void )  /* ��CH376������ */
{
//	mDelay0_5uS( );  /* ȷ����д���ڴ���0.6uS */
	return( CH376_ReadWrite( 0xff) );
}
/*****************************************************

 * Name:     Query376Interrupt

 * Function: ��ѯCH376�ж�(INT#�͵�ƽ)

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8	Query376Interrupt( void )
{
  return (CHK_CH376_INT()?FALSE:TRUE);
 //return( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)? FALSE : TRUE );  			/* ���δ����CH376���ж��������ѯ�����ж������SDO����״̬ */
}

/*****************************************************

 * Name:     mDelayuS

 * Function: delay

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
void mDelayuS(u8 us)
{
  Delay_us(us);
 //while(us--);
}

/*****************************************************

 * Name:     mDelayuS

 * Function: delay

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/

void mDelaymS(u8 ms)
{/*
 unsigned int i;
 for(;ms>0;ms--)
     for(i=0;i<940;i++);
  */
  Delay_ms(ms);
}

/*****************************************************

 * Name:     mDelayuS

 * Function: delay

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
void	mDelay0_5uS( void )  /* ������ʱ0.5uS,���ݵ�Ƭ����Ƶ���� */
{/*
 u8 i;
 i=20;
 while(i--);
 */
 Delay_us(100);
}
/*
void main(void)
{
   volatile int a ;

   a = 10;
   
}
*/
