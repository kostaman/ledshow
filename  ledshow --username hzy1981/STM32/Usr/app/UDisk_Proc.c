#define UDISK_PROC_C
#include "Includes.h"
#include "FILE_SYS.H"

#define UDISK_RT_PLAY_TIME 3

void UDisk_Init(void)
{
 INT8U Re;

  Unselect_SPI_Device();

  SPI1_CH376_Init();
  Delay_ms(100);
  //SET_CH376_CS(0);	//ѡ��CH376
  Re = mInitCH376Host();
  if(Re != USB_INT_SUCCESS)
  {
    ASSERT_FAILED();
  }

  //SET_CH376_CS(1);	//��ѡ��CH376
}


void Set_UDisk_Status(INT8U Status)
{
  Screen_Status.UDisk_Flag = Status;
}

INT8U Chk_UDisk_Processing(void)
{
   if(Screen_Status.UDisk_Flag EQ UDISK_ING) //��ǰ��U�̲��룬�������ڴ���״̬
     return 1;
   else
     return 0;

	/*
   //��ǰû����U�̴���״̬��
   if(Query376Interrupt() EQ TRUE)
   {
     //Set_UDisk_Status(UDISK_ING);
	 Screen_Status.UDisk_Flag = UDISK_ING;
     return 1;
   }
   else
   {
     Screen_Status.UDisk_Flag = UDISK_NULL;
     return 0;
	 }
   	  */
}
     
void UDisk_Proc(void)
{
    //static S_Int8U Flag = {CHK_BYTE, 0, CHK_BYTE};
    volatile static INT8U Re;
	INT8U Counts;
    INT16U RealCount,len;
	unsigned char buf[30];

    //if(Screen_Status.UDisk_Flag != UDISK_ING) //��ǰ��U���ж���Ҫ����
	  //return;

	if(Query376Interrupt() EQ FALSE)//�ٴ�ȷ���ж��ź�
	{
      Set_UDisk_Status(UDISK_NULL);
	  return;
	 }
    
	Set_UDisk_Status(UDISK_ING); 

    Unselect_SPI_Device();
	SPI1_CH376_Init();
	
	    Counts = 0;
		//while(!=USB_INT_SUCCESS) //SPI�����ѯ�Ƿ���U�̲���
 		do
		{
		  Re = CH376DiskConnect();
		  if(Re EQ USB_INT_DISCONNECT || Re EQ ERR_DISK_DISCON) //U�̱��γ�
		  {
		    //RT_Play_Status_Exit(); //�˳�ʵʱ��ʾ״̬

            Set_UDisk_Status(UDISK_NULL);
		    goto UDiskProcEnd;
		  }
					  
		  Counts++;
		  if(Counts >= 20)
		  {
            Set_UDisk_Status(UDISK_NULL);
		    goto UDiskProcEnd;
		   }
		   
		   Delay_ms(100);	   
		 }while(Re != USB_INT_SUCCESS);
		 
		Delay_ms(200);

		Counts = 0;
 		while(Counts <= 10)//for ( i = 0; i < 100; i ++ ) {  /* ��ȴ�ʱ��,100*50mS */
	    {
			Re = CH376DiskMount( );  /* ��ʼ�����̲����Դ����Ƿ���� */
			if ( Re == USB_INT_SUCCESS ) 
			   break;  /* ׼���� */
			else if ( Re == ERR_DISK_DISCON ) 
			{
			  /* ��⵽�Ͽ�,���¼�Ⲣ��ʱ */
			   Set_UDisk_Status(UDISK_NULL);
		       goto UDiskProcEnd;
			}

			if ( CH376GetDiskStatus( ) >= DEF_DISK_MOUNTED && Counts >= 5 ) 
			    break;  /* �е�U�����Ƿ���δ׼����,�������Ժ���,ֻҪ�佨������MOUNTED�ҳ���5*50mS */
		    
		    Delay_ms(50);
			Counts ++;
		}

		Set_RT_Show_Area(0, 0, 32, 16);
        RT_Play_Status_Enter(UDISK_RT_PLAY_TIME);

  		if ( CH376GetDiskStatus( ) < DEF_DISK_MOUNTED )/* δ֪USB�豸,����USB���̡���ӡ���� */ 
		{ 
			Clr_All_Show_Data();
			LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "ERR4");
			Set_UDisk_Status(UDISK_NULL);
			goto UDiskProcEnd;
		}

		if(CH376DiskMount()==USB_INT_SUCCESS) //���̾���?
		{
			//strcpy((char *)buf, "\\led_data\\");
			//itoa(Screen_Para.COM_Para.Addr, buf + 10, 10); //�ļ����ǰ��ַ,�Ҳ����ļ����Թ㲥��ַ��
			//sprintf(buf, (const char *)"\\%d.dat", Screen_Para.COM_Para.Addr);
			//strcpy((char *)buf, "\\LEDDATA\\0.DAT");
			sprintf((char *)buf, "\\LEDDATA\\%d.DAT", Screen_Para.COM_Para.Addr);
			Re = CH376FileOpenPath(buf);
			//LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "%d", Re);
			if(Re != USB_INT_SUCCESS)
			{
			  strcpy((char *)buf, "\\LEDDATA\\65536.DAT");
			  Re = CH376FileOpenPath(buf);
			  if(Re != USB_INT_SUCCESS) //�Ҳ����ļ����Թ㲥��ַ��
			  {
			    Set_UDisk_Status(UDISK_NULL);
			    Clr_All_Show_Data();
			    LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "ERR0");
				goto UDiskProcEnd;
			  }
			}

 			while(1)
			{
			    //Set_Screen_Com_Time(0); //����ʱ0������²��Ž�Ŀ

				CH376ByteRead((INT8U *)RCV_DATA_BUF, FLEN + 2, &RealCount );
                if(RealCount EQ 0)
				{
  				  Clr_All_Show_Data();
				  LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "OK");
				  break;
				}
			    else if(RealCount != FLEN + 2)
				{
				  //Screen_Status.UDisk_Flag = UDISK_END; //�������
				  Clr_All_Show_Data();
				  LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "ERR1");
				  break;
				}

                memcpy(&len, (INT8U *)RCV_DATA_BUF + FLEN, 2);
				if(len <= sizeof(RCV_DATA_BUF) && len > FLEN + 2)
				{
				  CH376ByteRead((INT8U *)RCV_DATA_BUF + FLEN + 2, len - (FLEN + 2), &RealCount );
		          if(RealCount EQ len - (FLEN + 2) && Check_Frame_Format((INT8U *)RCV_DATA_BUF, len))
		          {

				    Re = Rcv_Frame_Proc(CH_UDISK, (INT8U *)RCV_DATA_BUF, len, sizeof(RCV_DATA_BUF)); 
                    
					Unselect_SPI_Device();
	                SPI1_CH376_Init();
					
					if(Re EQ 0)
					{
					  //Screen_Status.UDisk_Flag = UDISK_END; //�������
					  ASSERT_FAILED();
					  Clr_All_Show_Data();
					  LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "ERR2");
					  break;
					} 
		          }
		        }
				else
				{
				      //Screen_Status.UDisk_Flag = UDISK_END; //�������
   					  ASSERT_FAILED();
					  Clr_All_Show_Data();
					  LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "ERR3");
					  break;
				}
		    }


		CH376FileClose(FALSE);
	    Set_UDisk_Status(UDISK_NULL);
	}
	else
	{
	  ASSERT_FAILED();
	  Clr_All_Show_Data();
	  LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "ERR5");
	}
	
	Set_Screen_Com_Time(0); //����ʱ0������²��Ž�Ŀ
UDiskProcEnd:
	Restore_Show_Area();
}
