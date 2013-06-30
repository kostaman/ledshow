#define SIM900A_C
#include "Includes.h"

#if GPRS_EN || SMS_EN

// ��ʼ��GSM״̬
INT8U GsmInit(void)
{
	//char ans[128];		// Ӧ��


	//UCS�ַ���
	if(ATSendResponse("AT+CSCS=\"UCS2\"\r", "OK", 2000) EQ 0)
	  ;//return 0;
	// PDUģʽ
	if(ATSendResponse("AT+CMGF=0\r", "OK", 2000) EQ 0)
	  ;//return 0;
    //ATSend("AT+CSCA?\r");
	return 1;
}

INT8U GprsInit(void) 
{   
    //uint8_t erro;
	unsigned int i;
	//unsigned char temp_c[64];
	//erro=0;
	
    //if(ATSendResponse("AT+GSV\r\n", "OK", 300) EQ 0)
	  //return 0; 	

 /*
    if(ATSendResponse("AT+CLIP=1\r\n", "OK", 200) EQ 0)  //ָʾ�������
      return 0;//erro+=GetResponse("OK", 2);
*/
    
    //ATSend("AT+CSQ\r\n");
    //erro+=GetResponse("OK", 2); //�ź�ǿ��
    
    
    //ATSend("AT+COPS?\r\n");
    //erro+= GetResponse("+COPS", 2);

	if(ATSendResponse("AT+CIPHEAD=1\r\n", "OK", 2000) EQ 0)
	  ;//return 0;

    for(i = 0; i < 20; i ++)
	{
        if(ATSendResponse("AT+CGATT=1\r\n", "OK", 2000))  //ע������
		  break;          
    }

	if(i EQ 20)
	  return 0;

    return 1;
    //erro += GetResponse("OK", 2);
 /*
    ATSend("AT+CIPSTATUS\r\n");
    erro+=GetResponse("STATE:", 2);
    delayMs(0, 200);
    if(check_respond("IP INITIAL") == 0) 
	{
    
        
        ATSend("AT+CIPMUX=1\r\n");
        erro+= GetResponse("OK", 2);
        
        
	
        strcpy(temp_c,"\"AT+CSTT=\"");
		strcat(temp_c,APN);
		strcat(temp_c,"\",\"");
		strcat(temp_c,usear);
		strcat(temp_c,"\",\"");
		strcat(temp_c,password);
		strcat(temp_c,"\"\r\n");
		ATSend(temp_c);
        erro += GetResponse("OK",2);
        
        
        ATSend("AT+CIICR\r\n");
        erro += GetResponse("OK", 20);
        
       
        ATSend("AT+CIFSR\r\n");
        erro += GetResponse(".", 3);
        
    } 
	else if(check_respond("IP STATUS") == 0) 
	{
        
        ;//printf("֮ǰ�Ѿ�����");
        
    }
	
	 else if(check_respond("CONNECT OK") == 0  ||
              check_respond("CONNECTING") == 0  ||
              check_respond("LISTENING") == 0   ||
              check_respond("CLOSING")== 0      ||
              check_respond("CLOSED") == 0) 
	{
              
        ATSend("AT+CIPSHUT\r\n");
        erro +=GetResponse("SHUT OK\r\n", 20);
        
    } 
	else if	(check_respond("IP GPRSACT") == 0 ) 
	{
		
        ATSend("AT+CIFSR\r\n");
        erro += GetResponse(".", 20);
	}
	else 
	{    
        erro = 1;
		gprs_power_down();
    }

exit:	
    return erro;
*/
}

void Module_PWR_KEY(void)
{
	SET_GSM_ON(1);
	OS_TimeDly_Ms(10);
	SET_GSM_ON(0);
	OS_TimeDly_Ms(10);
	SET_GSM_ON(1);
	OS_TimeDly_Ms(1100);
	SET_GSM_ON(0);
}

void ModuleInit(void) //ģ���ʼ��
{
    //INT8U i;

	//����GSMģ��	
	if(CHK_MODULE_STATUS() EQ 0)
	{
	    debug("reset sim900A module");
		Module_PWR_KEY();
	}

    Clr_Watch_Dog();

    OS_Core_Wait_Ms(CHK_MODULE_STATUS(),3000); //���ȴ�3000ms��

	// ����GSM-MODEM�Ĵ�����
	while(1)
	{
	  if(CHK_MODULE_STATUS() EQ 0)
	    return;

	  if(ATSendResponse("AT\r", "OK", 2000))
	    break;

	  OS_TimeDly_Ms(100);
	}
	// ECHO OFF
	ATSendResponse("ATE0&W\r\n", "OK", 2000);
	   
    ATSendResponse("AT+CFUN=1\r\n", "OK", 2000); //ȫ����
    
    ATSendResponse("AT+CMEE=1\r\n", "OK", 2000);// EQ 0)

	//���sim���Ƿ�����
    while(1)
	{
	  if(CHK_MODULE_STATUS() EQ 0)
	    return;

	  if(ATSendResponse("AT+CCID\r\n", "OK", 2000))
	    break;

	  OS_TimeDly_Ms(200);
	}

	ATSendResponse("AT+CSQ\r\n", "OK", 2000); //�ź�ǿ��

   	//ATSendResponse("AT+CMGDA=6\r\n", "OK", 2000);
/*       
    for(i = 0; i < 20; i ++)
	{
        if(ATSendResponse("AT+CREG?\r\n", "OK", 200))  //ע������
		  break;          
    }
*/
	//if(i EQ 20)
	 // return 0;
#if SMS_EN
    GsmInit();
#endif

#if GPRS_EN
	GprsInit();
#endif



}

//����TCP����
INT8U TCPConnect(void)
{
  INT8U Re;

  Screen_Para.GPRS_Para.Serv_Domain[sizeof(Screen_Para.GPRS_Para.Serv_Domain) - 1] = 0;	//Ŀ���ַ���һ���ֽ���0�����⸴���ַ������
  
  while(1)
  {
	  snprintf(GPRS_Buf.Data, sizeof(GPRS_Buf.Data), "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", \
	           Screen_Para.GPRS_Para.Serv_Domain,  Screen_Para.GPRS_Para.Serv_Port);
	
	  Re = ATSendResponse(GPRS_Buf.Data, "CONNECT OK", 2000);
	  if(Re)
	    return Re; 
	  
	  ATSend("AT+IPCLOSE=1\r\n");

	  if(Screen_Para.GPRS_Para.Heart_Period EQ 0)
	  {
	    Screen_Para.GPRS_Para.Heart_Period = 3;
	    SET_SUM(Screen_Para);
	  }

      OS_TimeDly_Sec(Screen_Para.GPRS_Para.Heart_Period * 60 - 25); 
      
  }
}

//ʹ��TCP��������
void TcpSendData(INT8U Data[], INT16U DataLen)
{


}

//��ȡCOM������
INT16U ReadComm(char *pDst, INT16U Len, INT16U ms)
{
  INT16U WRPosi, RDPosi;

  //100ms��û���յ���������Ϊ�����ȶ���.
  //OS_TimeDly_Ms(100);
  if(CHK_MODULE_STATUS() EQ 0)
    return 0;

  WRPosi = SMS_GPRS_Rcv_Buf.WRPosi;

  Clr_Watch_Dog();

  OS_Core_Wait_Ms(WRPosi != SMS_GPRS_Rcv_Buf.WRPosi, ms); //���ȴ�500ms���ȵ������ݽ���

  while(1)
  {
    WRPosi = SMS_GPRS_Rcv_Buf.WRPosi;
    
	OS_TimeDly_Ms(200);
	
	Clr_Watch_Dog();

	if(WRPosi EQ SMS_GPRS_Rcv_Buf.WRPosi)
	  break; 
  }

  WRPosi = SMS_GPRS_Rcv_Buf.WRPosi;
  RDPosi = SMS_GPRS_Rcv_Buf.RDPosi;

  if(RDPosi < WRPosi)
  {
    if(RDPosi + Len >= WRPosi)
	  Len = WRPosi - RDPosi;
  }
  else
    Len = 0;

  memcpy(pDst, SMS_GPRS_Rcv_Buf.Buf + RDPosi, Len);
  SMS_GPRS_Rcv_Buf.RDPosi += Len;

  return Len;
}

//дCOM������
INT16U WriteComm(char *pDst, INT16U Len)
{
  INT16U i;

  for(i = 0; i < Len; i ++)
  {
    Com_Send_Byte(CH_GPRS, pDst[i]);
    Com_Send_Byte(CH_DBG, pDst[i]);
  }
  return Len;
} 

INT8U ATSend(char *p)
{
  ClrComm();
  return WriteComm(p, strlen(p));
}

INT8U ATSendResponse(char *pSrc, char *pRes, INT16U ms)
{
	ATSend(pSrc);
	return GetResponse(pRes, ms);
}

char TempRcvData[200];
//����Ƿ��յ�p�ַ��������ȴ�ms
INT8U GetResponse(char *p, INT16U ms)
{
  INT16U Len;

  memset(TempRcvData, 0, sizeof(TempRcvData));
  Len = ReadComm(TempRcvData, sizeof(TempRcvData), ms);
  if(Len > 0 && strstr(TempRcvData, p) != 0)
    return 1; 
  else
    return 0;
}

void ClrComm(void)
{
  SMS_GPRS_Rcv_Buf.RDPosi = 0;
  SMS_GPRS_Rcv_Buf.WRPosi = 0;

  SMS_GPRS_Rcv_Buf.Buf[0] = 0;
  SMS_GPRS_Rcv_Buf.Buf[1] = 0;

}

void Chk_Module_Status(void)
{
  if(CHK_MODULE_STATUS() EQ 0)
  {
    OS_TimeDly_Ms(10);
	if(CHK_MODULE_STATUS() EQ 0)
	{
	  ModuleInit();
	}
  }
}
#endif
