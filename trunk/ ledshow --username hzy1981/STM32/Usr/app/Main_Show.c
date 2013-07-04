#define MAIN_SHOW_C
#include "includes.h"

#if QT_EN
#include <mainwindow.h>
extern MainWindow *w;
#endif

/*
//ÿ���ٶȵ���ʱ,��λΪ����
const INT16U Step_Delay[]=
{
  10,
  20,
  30,
  40,
  50,
  60,
  70,
  80,
  90,
  100
};
*/
//��ȡĳ����������ĳ��������ͣ��ʱ��
INT32U Get_Area_In_Step_Delay(INT8U Area_No)
{/*
    if(Prog_Status.File_Para[Area_No].Pic_Para.In_Speed > 1)
      return MOVE_STEP_PERIOD + (Prog_Status.File_Para[Area_No].Pic_Para.In_Speed - 1) * MOVE_STEP_PERIOD*2; //CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.In_Speed);///(100/MOVE_STEP);
    else
      return MOVE_STEP_PERIOD;
	  */
#if QT_EN
    if(Prog_Status.File_Para[Area_No].Pic_Para.In_Speed > 1)
      return MOVE_STEP_PERIOD + ((INT32U)Prog_Status.File_Para[Area_No].Pic_Para.In_Speed - 1) * MOVE_STEP_PERIOD; //CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.In_Speed);///(100/MOVE_STEP);
    else
      return MOVE_STEP_PERIOD;
#else
    if(Prog_Status.File_Para[Area_No].Pic_Para.In_Speed > 1)
      return MOVE_STEP_PERIOD + ((INT32U)Prog_Status.File_Para[Area_No].Pic_Para.In_Speed - 1)* 2 * MOVE_STEP_PERIOD; //CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.In_Speed);///(100/MOVE_STEP);
    else
      return MOVE_STEP_PERIOD;
#endif
}

//��ȡĳ����������ĳ��������ͣ��ʱ��
INT32U Get_Area_Out_Step_Delay(INT8U Area_No)
{	/*
    if(Prog_Status.File_Para[Area_No].Pic_Para.Out_Speed > 1)
      return MOVE_STEP_PERIOD + (Prog_Status.File_Para[Area_No].Pic_Para.Out_Speed - 1)* MOVE_STEP_PERIOD*2; //CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.In_Speed);///(100/MOVE_STEP);
    else
      return MOVE_STEP_PERIOD;
	  */
#if QT_EN
    if(Prog_Status.File_Para[Area_No].Pic_Para.Out_Speed > 1)
      return MOVE_STEP_PERIOD + ((INT32U)Prog_Status.File_Para[Area_No].Pic_Para.Out_Speed - 1) * MOVE_STEP_PERIOD; //CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.In_Speed);///(100/MOVE_STEP);
    else
      return MOVE_STEP_PERIOD;
#else
    if(Prog_Status.File_Para[Area_No].Pic_Para.Out_Speed > 1)
      return MOVE_STEP_PERIOD + ((INT32U)Prog_Status.File_Para[Area_No].Pic_Para.Out_Speed - 1) * 2 * MOVE_STEP_PERIOD; //CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.In_Speed);///(100/MOVE_STEP);
    else
      return MOVE_STEP_PERIOD;
#endif
}
/*
//��ȡ�ļ�����ʱ��
INT32U Get_File_In_Speed(INT8U Area_No)
{
 return CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.In_Speed);
  
}
*/
//��ȡ�ļ���ͣ��ʱ��,��λΪms
//ԭ�������Ϊ��ʾ��λ��0Ϊs��1Ϊms
INT32U Get_File_Stay_Time(INT8U Area_No)
{
  return CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time);
}
/*
//��ȡ�ļ�����ʱ��
INT32U Get_File_Out_Speed(INT8U Area_No)
{
  return CONVERT_TIME(Prog_Status.File_Para[Area_No].Pic_Para.Out_Speed);
}
*/
//�����ļ���ͣ��ʱ��
void Set_File_Stay_Time(INT8U Area_No, INT16U ms)
{
  Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time = ms;
  Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time = Prog_Status.File_Para[Area_No].Pic_Para.Stay_Time | 0x8000;
}

//���Area_No������ǰ��ʾ�����Ƿ���������
INT8U Chk_Pic_Continuous_Move(INT8U Area_No)
{
#if QT_EN EQ 0 //qt��������²������⴦����Ϊ���Դ���̫�������¿�
    //��ʱֻ���������ƺ��������ƶ�������
    if(Prog_Status.Area_Status[Area_No].In_Mode >= 1 &&\
       Prog_Status.Area_Status[Area_No].In_Mode <= 2 &&\
       Get_File_Stay_Time(Area_No) EQ 0 &&\
       (Prog_Status.File_Para[Area_No].Pic_Para.Flag EQ SHOW_PIC || Prog_Status.File_Para[Area_No].Pic_Para.Flag EQ SHOW_TXT))
        return 1;
    else
        return 0;
#else
    return 0;
#endif

}

//ÿ��MOVE_STEP_TIMER ms���øú���,ʵ���ƶ���ʾ��Ч��
void Update_Show_Data(void)
{
  static INT8U i = 0;

  if(Screen_Status.Time_OC_Flag EQ CLOSE_FLAG ||\
     Screen_Status.Manual_OC_Flag EQ CLOSE_FLAG ||\
	 Screen_Status.Self_OC_Flag EQ CLOSE_FLAG ||\
	 Chk_UDisk_Processing() ||\
	 CHK_ENC28J60_INT() ||\
	 CHK_TEST_KEY_STATUS())
    return;

  if(Prog_Status.Play_Status.RT_Play_Time > 0) //��ǰ�ڹػ�״̬����ʵʱ��ʾ״̬
	{/*
	  if(Prog_Status.Play_Status.RT_Play_Flag EQ RT_PLAY_FLAG)
	  {
	    Prog_Status.Play_Status.RT_Play_Time -= MOVE_STEP_PERIOD;
		if(Prog_Status.Play_Status.RT_Play_Time EQ 0)
		  RT_Play_Status_Exit();  
	  }    
	  */
	  return;
	}
/*
 for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
 {
  if(Chk_File_Play_Status(i) EQ 0)
    return;
  }
*/
 
  //for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  if(i < Prog_Para.Area_Num && i < MAX_AREA_NUM) 
  {
      if(Screen_Status.Com_Time > 0) //�յ�һ֡���ȴ����֡
          return;
//#if PIC_SHOW_EN    
    //if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_PIC)
      Update_Pic_Data(i);

      if(Screen_Status.Com_Time > 0) //�յ�һ֡���ȴ����֡
          return;
		  	  
#if BORDER_SHOW_EN
      Update_Border_Data(i); //���±߿�����
#endif


//#endif
/*
#if CLOCK_SHOW_EN
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_CLOCK)
      Update_Clock_Data(i);
#endif
      */
    /*
#if TIMER_SHOW_EN
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_TIMER)
      Update_Timer_Data(i);
#endif
      */
    /*
#if TIME_SHOW_EN
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_TIME)
      Update_Time_Data(i);
#endif
      */
    /*
#if TEMP_SHOW_EN
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_TEMP)
      Update_Temp_Data(i);
#endif
      */
    /*
#if LUN_SHOW_EN
    else if(Prog_Status.File_Para[i].Pic_Para.Flag EQ SHOW_LUN)
      Update_Lun_Data(i);
#endif
      */
  }
       if(Screen_Status.Com_Time > 0) //�յ�һ֡���ȴ����֡
          return;

#if BORDER_SHOW_EN
      Update_Border_Data(MAX_AREA_NUM); //���±߿�����
#endif

  i++;

  if(!(i < Prog_Para.Area_Num && i < MAX_AREA_NUM))
    i = 0;

}

//������ʾ���������ݡ���ʾ�ǹ̶��ı�����Ϣ
INT8U Update_XXX_Data(S_Show_Data *pDst, INT8U Area_No)
{
  INT8U Flag; 
  
  Flag = Prog_Status.File_Para[Area_No].Pic_Para.Flag;
  
  //ĳЩ��ͼ��������Ҫ��ʱˢ��!Ӧ�ñ�֤ÿ���ӽ���һ��
  if(PIC_SHOW_EN && Flag EQ SHOW_PIC)
    ;
#if CLOCK_SHOW_EN  
  else if(Flag EQ SHOW_CLOCK)
    Update_Clock_Data(pDst, Area_No);
#endif
#if TIME_SHOW_EN  
  else if(Flag EQ SHOW_TIME)
    Update_Time_Data(pDst, Area_No);
#endif
#if TIMER_SHOW_EN  
  else if(Flag EQ SHOW_TIMER)
    Update_Timer_Data(pDst, Area_No);
#endif
#if TEMP_SHOW_EN  
  else if(Flag EQ SHOW_TEMP)
    Update_Temp_Data(pDst, Area_No);
#endif
#if LUN_SHOW_EN  
  else if(Flag EQ SHOW_LUN)
    Update_Lun_Data(pDst, Area_No);
#endif
#if HUMIDITY_SHOW_EN
  else if(Flag EQ SHOW_HUMIDITY)
    Update_Humidity_Data(pDst, Area_No);
#endif
#if NOISE_SHOW_EN
  else if(Flag EQ SHOW_NOISE)
    Update_Noise_Data(pDst, Area_No);
#endif
  else
    ASSERT_FAILED(); 
  
  return 1;
}

//���ĳ��������״̬
void Clr_Area_Status(INT8U Area_No)
{
  if(Area_No >= MAX_AREA_NUM)
  {
    ASSERT_FAILED();
    return;
  }
  
  memset((void *)&Prog_Status.Area_Status[Area_No], 0, sizeof(Prog_Status.Area_Status[Area_No]));
  SET_HT(Prog_Status.Area_Status[Area_No]);
}

void Clr_All_Area_Status()
{
    INT8U i;

    for(i = 0; i < MAX_AREA_NUM; i++)
    {
        Clr_Area_Status(i);
    }
}


void Clr_Show_Bak_Data(void)
{
    Clr_Watch_Dog();
  //if(Screen_Para.Scan_Para.Data_Polarity EQ 0)
    //memset(Show_Data.Color_Data, 0xFF, sizeof(Show_Data.Color_Data));
  //else
    memset(Show_Data_Bak.Color_Data, 0x00, sizeof(Show_Data_Bak.Color_Data));
}

void Clr_Show_Data(void)
{
    Clr_Watch_Dog();
  //if(Screen_Para.Scan_Para.Data_Polarity EQ 0)
    //memset(Show_Data.Color_Data, 0xFF, sizeof(Show_Data.Color_Data));
  //else
    memset(Show_Data.Color_Data, 0x00, sizeof(Show_Data.Color_Data));
}

void Set_Show_Data(void)
{
    Clr_Watch_Dog();
 // if(Screen_Para.Scan_Para.Data_Polarity EQ 0)
   // memset(Show_Data.Color_Data, 0x00, sizeof(Show_Data.Color_Data));
  //else
    memset(Show_Data.Color_Data, 0xFF, sizeof(Show_Data.Color_Data));
}
/*
void Clr_All_Show_Data(void)
{
  Clr_Show_Data();

  memset(Show_Data_Bak.Color_Data, 0, sizeof(Show_Data_Bak.Color_Data));
  SET_HT(Show_Data);
  SET_HT(Show_Data_Bak);
}
*/

//��ȡ��������
void Read_Continous_Move_Show_Data(S_Show_Data *pDst, INT8U Area_No)
{
    INT16U Area_Width, Area_Height, Border_Height,i,j;

    Area_Width = Get_Area_Width(Area_No);
    Area_Height = Get_Area_Height(Area_No);
    Border_Height = Get_Area_Border_Height(Area_No);

    if(Area_Height > 2*Border_Height)
        Area_Height = Area_Height - 2*Border_Height;
    else
        return;

    if(Area_Width > 2*Border_Height)
        Area_Width = Area_Width - 2*Border_Height;
    else
        return;

    //��ƽ�ƻ�����������
    //ʵ��ֻ���������ƺ��������ƲŻ���봦��
    //�������ַ�ʽ��ʱ�������룬�Ա���
    if(Prog_Status.Area_Status[Area_No].In_Mode EQ 1 ||\
       Prog_Status.Area_Status[Area_No].In_Mode EQ 3)
    {
        for(j = 0; j < Area_Height; j ++)
        {
           i = Prog_Status.Area_Status[Area_No].In_Step;
             Read_Show_Data_Point(Area_No, \
                                  Prog_Status.Area_Status[Area_No].File_No, \
                                  (U_File_Para *)&Prog_Status.File_Para[Area_No], \
                                  Prog_Status.Area_Status[Area_No].SCN_No,\
                                  pDst, \
                                  i, \
                                  j);
        }
    }
    else if(Prog_Status.Area_Status[Area_No].In_Mode EQ 2 ||\
            Prog_Status.Area_Status[Area_No].In_Mode EQ 5)//�������ƻ�������
    {
        for(i = 0; i < Area_Width; i = i+8)
        {
             j = Prog_Status.Area_Status[Area_No].In_Step;
             Read_Show_Data_Point(Area_No, \
                                  Prog_Status.Area_Status[Area_No].File_No, \
                                  (U_File_Para *)&Prog_Status.File_Para[Area_No], \
                                  Prog_Status.Area_Status[Area_No].SCN_No,\
                                  pDst, \
                                  i, \
                                  j);
        }
    }
    else if(Prog_Status.Area_Status[Area_No].In_Mode EQ 4) //��ƽ��
    {
        for(j = 0; j < Area_Height; j ++)
        {
           i = Prog_Status.Area_Status[Area_No].In_Max_Step - Prog_Status.Area_Status[Area_No].In_Step;
             Read_Show_Data_Point(Area_No, \
                                  Prog_Status.Area_Status[Area_No].File_No, \
                                  (U_File_Para *)&Prog_Status.File_Para[Area_No], \
                                  Prog_Status.Area_Status[Area_No].SCN_No,\
                                  pDst, \
                                  i, \
                                  j);
        }
    }
    else//��ƽ��
    {
        for(i = 0; i < Area_Width; i = i+8)
        {
             j = Prog_Status.Area_Status[Area_No].In_Max_Step - Prog_Status.Area_Status[Area_No].In_Step;
             Read_Show_Data_Point(Area_No, \
                                  Prog_Status.Area_Status[Area_No].File_No, \
                                  (U_File_Para *)&Prog_Status.File_Para[Area_No], \
                                  Prog_Status.Area_Status[Area_No].SCN_No,\
                                  pDst, \
                                  i, \
                                  j);
        }
    }
}

//���Area_No��ǰ�����ļ��Ƿ񲥷ŵ������?
INT8U Chk_File_Play_End(INT8U Area_No)
{
    if(Prog_Status.Area_Status[Area_No].SCN_No >= Prog_Status.File_Para[Area_No].Pic_Para.SNum)
    {
        Prog_Status.Area_Status[Area_No].New_File_Flag = NEW_FLAG;

        Prog_Status.Area_Status[Area_No].Play_Counts ++;
        if(Prog_Status.Area_Status[Area_No].Play_Counts >= Prog_Status.File_Para[Area_No].Pic_Para.Play_Counts + 1)
        {
          Prog_Status.Area_Status[Area_No].File_No ++;
          Prog_Status.Area_Status[Area_No].Play_Counts = 0;
        }
        SET_SUM(Prog_Status.Area_Status[Area_No]);
        return 1;
    }
    else
        return 0;

}

//��ȡһ����ʾ����
//prog��Ŀ��
//area������
INT8U Update_Show_Data_Bak(INT8U Prog_No, INT8U Area_No)
{
  INT16U Len;//,SNum;
  INT16S Len0,Len1;
  INT16U X,Y,Width,Height;
  INT8U Re = 1, File_Flag = 0;
  //INT8U File_No;
  //INT8U Counts;

  Re &= CHK_SUM(Prog_Status.Play_Status);
  if(Re EQ 0)
      ASSERT_FAILED();
  Re &= CHK_SUM(Prog_Status.Area_Status[Area_No]);
  if(Re EQ 0)
      ASSERT_FAILED();
  Re &= CHK_SUM(Prog_Para);
  if(Re EQ 0)
      ASSERT_FAILED();

  //���з�������ʾ�����л����¸���ʾ�ļ�
  if(Prog_Status.Play_Status.New_Prog_Flag) //�ڽ�Ŀ����״̬�У��������ļ�����
      return 0;

  //if(Prog_Para.Area_File_Num[Area_No] EQ 0)
      //return 0;
/*
  if(Prog_Status.Area_Status[Area_No].New_File_Flag EQ 0 &&\
     Prog_Status.Area_Status[Area_No].New_SCN_Flag > 0)
  {
      if(Prog_Status.Area_Status[Area_No].SCN_No >= Prog_Status.File_Para[Area_No].Pic_Para.SNum)
      {
          Prog_Status.Area_Status[Area_No].New_File_Flag = NEW_FLAG; //�������һ�����л�����һ���ļ�
          Prog_Status.Area_Status[Area_No].File_No ++;
          SET_SUM(Prog_Status.Area_Status[Area_No]);
      }
  }
*/
  TRACE();

  //����Ƿ���Ҫ���µ���һ�ļ�
  if(Prog_Status.Area_Status[Area_No].New_File_Flag)//SNum > Prog_Status.File_Para[Area_No].Pic_Para.SNum)
  {
      TRACE();

    //debug("prog %d area %d file %d play end!", Prog_Status.Play_Status.Prog_No, Area_No, Prog_Status.Area_Status[Area_No].File_No);

    Prog_Status.Area_Status[Area_No].SCN_No = 0;
    SET_SUM(Prog_Status.Area_Status[Area_No]);
    //�ļ�������ȡʧ�����л����¸��ļ�

#if SMS_EN
    if((Area_No EQ 0 && SMS_File_Play_End() > 0) ||\
       (Area_No > 0 && \
        (Prog_Status.Area_Status[Area_No].File_No >= Prog_Para.Area_File_Num[Area_No] ||\
        Prog_Status.Area_Status[Area_No].File_No >= MAX_FILE_NUM)))
    {
        //��0�����Ƕ�����ʾ����
		  Prog_Status.Area_Status[Area_No].File_No = 0;
          Prog_Status.Area_Status[Area_No].Counts++; //�ļ�����һ��+1
          SET_SUM(Prog_Status.Area_Status[Area_No]);

          Calc_Prog_Play_Counts();
          if(Check_Prog_End() > 0) //��Ŀ�����ˣ�
          {
             Prog_Status.Play_Status.New_Prog_Flag = NEW_FLAG; //�½�Ŀ
             Prog_Status.Play_Status.Prog_No ++;
             SET_SUM(Prog_Status.Play_Status);
             return 0;
          }
    }
#else
    if(Prog_Status.Area_Status[Area_No].File_No >= Prog_Para.Area_File_Num[Area_No] ||\
       Prog_Status.Area_Status[Area_No].File_No >= MAX_FILE_NUM) //�����ļ�ȫ����������һ��
    {
      Prog_Status.Area_Status[Area_No].File_No = 0;
      Prog_Status.Area_Status[Area_No].Counts++; //�ļ�����һ��+1
      SET_SUM(Prog_Status.Area_Status[Area_No]);

      Calc_Prog_Play_Counts();
      if(Check_Prog_End() > 0) //��Ŀ�����ˣ�
      {
         Prog_Status.Play_Status.New_Prog_Flag = NEW_FLAG; //�½�Ŀ
         Prog_Status.Play_Status.Prog_No ++;
         SET_SUM(Prog_Status.Play_Status);
         return 0;
      }
   }

   if(Prog_Para.Area_File_Num[Area_No] EQ 0)
      return 0;
#endif

    debug("\r\nprog %d area %d play new file: %d", Prog_No, Area_No, Prog_Status.Area_Status[Area_No].File_No);
    //�Ƚ��ļ��������� 
    //Prog_Status.Area_Status[Area_No].Play_Flag = 0; //�رձ�������ʾ
    //SET_SUM(Prog_Status.Area_Status[Area_No]);
#if SMS_EN == 0
    if(Prog_Status.Area_Status[Area_No].Last_File_No EQ Prog_Status.Area_Status[Area_No].File_No &&\
       CHK_HT(Prog_Status.Area_Status[Area_No]) &&\
       CHK_SUM(Prog_Status.Area_Status[Area_No]) &&\
       Prog_Status.File_Para[Area_No].Pic_Para.Flag != SHOW_NULL &&\
       Chk_File_Para_HT_Sum((U_File_Para *)&Prog_Status.File_Para[Area_No]))
    {
        debug("the same as last file");
       	File_Flag = 1;
    }
    else
#endif
    {
        Len = 0;
        Prog_Status.Area_Status[Area_No].Last_SCN_No = 0xFFFF;
        Prog_Status.Area_Status[Area_No].Last_File_No = 0xFF; //��Ԥ��һ�������ڵ��ļ���
        SET_SUM(Prog_Status.Area_Status[Area_No]);
/*
        //�����ǰ��Ŀ�б߿����˳�ʱ����������Ӧ������߿�
        if(Prog_Status.File_Para[Area_No].Pic_Para.Border_Check > 0 &&\
           ((Prog_Status.File_Para[Area_No].Pic_Para.In_Mode >= 2 && Prog_Status.File_Para[Area_No].Pic_Para.In_Mode <= 7) ||\
            Prog_Status.File_Para[Area_No].Pic_Para.Out_Mode EQ 1))
*/

        if(Prog_Status.File_Para[Area_No].Pic_Para.Border_Check > 0)
        {
            //Prog_Status.Area_Status[Area_No].Restore_Border_Flag = 1;
            //Restore_Border_Data(Area_No);
            Clr_Border(&Show_Data, Area_No);
        }
 
        Len = Read_File_Para(Prog_No, Area_No, Prog_Status.Area_Status[Area_No].File_No,\
                       Pub_Buf, Pub_Buf, sizeof(Pub_Buf));
        if(Len > 0)
        {
            Len1 = Get_Show_Para_Len(Pub_Buf[0]);
			if(Len1 > 0)
			{
			    if(Prog_Status.File_Para[Area_No].Pic_Para.Out_Mode EQ 1) //��ǰ�˳���ʽΪ�����򣬻��ļ�ʱӦ������Ļ
				  Clear_Area_Data(&Show_Data, Area_No);
                //debug("read file para no = %d, flag = %d", Prog_Status.Area_Status[Area_No].File_No, Prog_Status.File_Para[Area_No].Pic_Para.Flag );
	            mem_cpy((void *)&Prog_Status.File_Para[Area_No].Pic_Para.Flag, Pub_Buf, Len1, (void *)&Prog_Status.File_Para[Area_No].Pic_Para.Flag, sizeof(U_File_Para));
	
	            Clear_Area_Data(&Show_Data_Bak, Area_No);
	            
				if(Prog_Status.File_Para[Area_No].Pic_Para.Border_Check)
	            {
	              Draw_Border(&Show_Data_Bak, Area_No, Pub_Buf + Len1, 0, 0);
	            }

				File_Flag = 1;
			}
        }
    }

    if(File_Flag EQ 0) //�����������������һ���ļ�����
    {
      ASSERT_FAILED();

      Prog_Status.File_Para[Area_No].Pic_Para.Flag = SHOW_NULL;
      Prog_Status.Area_Status[Area_No].New_File_Flag = NEW_FLAG;
      Prog_Status.Area_Status[Area_No].File_No ++;
    }
    else
    {
        //Set_File_Para_HT_Sum(&Prog_Status.File_Para[Area_No]);
        //�����ļ������ˣ�����Ϊ�ϴζ������ļ�����
        Prog_Status.Area_Status[Area_No].Last_File_No = Prog_Status.Area_Status[Area_No].File_No;
        Prog_Status.Area_Status[Area_No].New_File_Flag = 0;
        Prog_Status.Area_Status[Area_No].SCN_No = 0;

        Prog_Status.Area_Status[Area_No].In_Step = 0;
        Prog_Status.Area_Status[Area_No].Out_Step = 0;
        Prog_Status.Area_Status[Area_No].Stay_Time = 0;
        Prog_Status.Area_Status[Area_No].Step_Timer = 0;

        Calc_Show_Mode_Step(Area_No); //�������ļ��Ľ����˳�ģʽ����󲽽���

        if(Chk_Pic_Continuous_Move(Area_No))
        {
           Prog_Status.Area_Status[Area_No].New_CStep_Flag = NEW_FLAG;
           Prog_Status.Area_Status[Area_No].New_SCN_Flag = 0;
        }
        else
        {
           Prog_Status.Area_Status[Area_No].New_SCN_Flag = NEW_FLAG;
           Prog_Status.Area_Status[Area_No].New_CStep_Flag = 0;
        }
    }

    SET_SUM(Prog_Status.Area_Status[Area_No]);
    Set_File_Para_HT_Sum((U_File_Para *)&Prog_Status.File_Para[Area_No]);
  }

  TRACE();
  //�����ļ����������в����·�������
  if(Prog_Status.Area_Status[Area_No].New_File_Flag)// EQ 0 &&
    return 0;

  //�������ݵ��µ�һ��
  if(Prog_Status.Area_Status[Area_No].New_SCN_Flag)
  {
      TRACE();
      //�Ѿ���������һĻ���л����¸��ļ�
      if(Chk_File_Play_End(Area_No))
          return 0;

/*
      //�������ƶ��������,�ڸ�����һ����ǰ,���뽫֮ǰ��Ļ�ı߿����ݻָ�,����߿��������ƶ���ͼ����
      if(Prog_Status.File_Para[Area_No].Pic_Para.In_Mode >= 2 &&\
         Prog_Status.File_Para[Area_No].Pic_Para.In_Mode <= 7)
      {
          //Prog_Status.Area_Status[Area_No].Restore_Border_Flag = 1;
          Restore_Border_Data(Area_No);
		  //Clr_Border(&Show_Data, Area_No, Get_Area_Border_Width(Area_No), Get_Area_Border_Height(Area_No));
      }
*/
      //������ʾ����
      //Prog_Status.Area_Status[Area_No].Play_Flag = 0; //--��ȡ��ʾ���ݹ����н����ű�־��0���Ӷ��жϳ����в�����
      //SET_SUM(Prog_Status.Area_Status[Area_No]);

      debug("\r\nread prog %d area %d, file %d %dth SCN show data", \
            Prog_No, Area_No, Prog_Status.Area_Status[Area_No].File_No,Prog_Status.Area_Status[Area_No].SCN_No);
#if 0
      if(Prog_Status.Area_Status[Area_No].Last_SCN_No EQ Prog_Status.Area_Status[Area_No].SCN_No &&\
         CHK_HT(Prog_Status.Area_Status[Area_No]) &&\
         Check_XXX_Data(Prog_Status.File_Para[Area_No].Pic_Para.Flag) EQ 0)
      {
         debug("the same as last SCN ,no update");
         Len0 = 1;
      }
      else
#endif
      {
          Set_Area_Border_Out(Area_No);
          Clear_Area_Data(&Show_Data_Bak, Area_No);
          Set_Area_Border_In(Area_No);

          Prog_Status.Area_Status[Area_No].Last_SCN_No = 0xFFFF;
          SET_SUM(Prog_Status.Area_Status[Area_No]);

          Len0 = Read_Show_Data(Area_No, \
                         Prog_Status.Area_Status[Area_No].File_No, \
                         (U_File_Para *)&Prog_Status.File_Para[Area_No],\
                         Prog_Status.Area_Status[Area_No].SCN_No,\
                         &Show_Data_Bak,&X,&Y,&Width,&Height);

      }

      TRACE();

      if(Len0 >= 0)
      {
        Prog_Status.Area_Status[Area_No].Last_SCN_No = Prog_Status.Area_Status[Area_No].SCN_No;
        //Prog_Status.Area_Status[Area_No].Play_Flag = 1; //�򿪱�������ʾ
        Prog_Status.Area_Status[Area_No].New_SCN_Flag = 0;
        SET_SUM(Prog_Status.Area_Status[Area_No]);
      }
      else
      {
        //������ʾ����û�ж��������������

        ASSERT_FAILED();
        Prog_Status.Area_Status[Area_No].New_SCN_Flag = NEW_FLAG;
        Prog_Status.Area_Status[Area_No].SCN_No ++; //��ʾ��������
        SET_SUM(Prog_Status.Area_Status[Area_No]);
      }
  }

  if(Prog_Status.Area_Status[Area_No].New_CStep_Flag)
  {
      //�Ѿ���������һĻ���л����¸��ļ�
      if(Chk_File_Play_End(Area_No))
          return 0;

      if(Prog_Status.Area_Status[Area_No].In_Step < Prog_Status.Area_Status[Area_No].In_Max_Step)
      {
          Read_Continous_Move_Show_Data(&Show_Data_Bak, Area_No);
      }
      else
      {
          Prog_Status.Area_Status[Area_No].SCN_No ++; //��ʾ��������
          SET_SUM(Prog_Status.Area_Status[Area_No]);
      }

      Prog_Status.Area_Status[Area_No].New_CStep_Flag = 0;
      SET_SUM(Prog_Status.Area_Status[Area_No]);
  }
//-----------------
  return AREA_OK;
}


//��������ʾ����������
INT8U Check_Update_Show_Data_Bak(void)
{
  INT8U i;
  //INT32U Stay_Time;
  //S_Int8U Sec = {CHK_BYTE, 0xFF, {0},CHK_BYTE};
  
  if(Prog_Status.Play_Status.RT_Play_Time > 0 ||\
     Prog_Num.Num EQ 0)
      return 0;

  for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
  {

     if(Screen_Status.Com_Time > 0 ||\
	    Screen_Status.Rcv_Flag EQ FRAME_FLAG) //�յ�һ֡���ȴ����֡
         return 1;

     if(Prog_Status.Area_Status[i].New_File_Flag ||\
        Prog_Status.Area_Status[i].New_SCN_Flag ||\
        Prog_Status.Area_Status[i].New_CStep_Flag)
     {
      Update_Show_Data_Bak(Prog_Para.Prog_No, i);// == FILE_END)
    }
  }
 /*
  //ÿ�����һ��ʱ�ӡ��¶ȡ���ʱ������
  if(Sec.Var != Cur_Time.Time[T_SEC])
  {
    Sec.Var = Cur_Time.Time[T_SEC];    
    for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
    {    
      Update_XXX_Data_Bak(i);
    }
  }
  */
  return 1;
}

void Check_Update_Show_Data(void)
{
  
}

void Clr_Prog_Status(void)
{
  memset((void *)&Prog_Status, 0, sizeof(Prog_Status));
  //SET_HT(Prog_Status);
  
}

//����Ŀ�Ƿ񲥷Ž���
//����1��ʾ�����ˣ�0��ʾ��û�н���
INT8U _Check_Prog_End(void)
{
#if CLOCK_EN
  if(Check_Prog_Play_Time() EQ 0)
  {
     debug("prog %d now not play time, end", Prog_Status.Play_Status.Prog_No);
     return 1;
  }

  if(Prog_Para.Area_Num EQ 0) //û�з���
      return 1;

  //����ģʽ
  if(Prog_Para.Mode EQ PROG_COUNTS_MODE)
  {
    if(Prog_Status.Play_Status.Counts >= Prog_Para.Counts && Prog_Status.Play_Status.Counts >= 1) //���ٲ���һ��
    {
      debug("prog %d play counts %d, end", Prog_Status.Play_Status.Prog_No, Prog_Status.Play_Status.Counts);
      return 1;
    }
    else
      return 0;
  }
  else if(Prog_Para.Mode EQ PROG_TIME_MODE)//ʱ��ģʽ
  {
    if(Prog_Status.Play_Status.Time > Prog_Para.Time) //���ܻ�ȶ�ʱ�༸ʮ�룬�����೬��1����
    {
      debug("prog %d play times %d, end", Prog_Status.Play_Status.Prog_No, Prog_Status.Play_Status.Time);
      return 1;
    }
    else
      return 0;
  }
  else
  {
    ASSERT_FAILED();
    return 1;
  }
#else //û��ʱ������£�������ģʽ��
	if(Prog_Status.Play_Status.Counts >= Prog_Para.Counts)
	{
	  debug("prog %d play counts %d, end", Prog_Status.Play_Status.Prog_No, Prog_Status.Play_Status.Counts);
	  return 1;
	}
	else
	  return 0;
#endif
}

//����Ŀ�Ƿ񲥷Ž���
//����1��ʾ�����ˣ�0��ʾ��û�н���
INT8U Check_Prog_End(void)
{
/*
#if QT_EN
  if(Preview_Mode EQ PREVIEW_SCREEN)
      return _Check_Prog_End();
  else
      return 1;
#else
  return _Check_Prog_End();
#endif
  */

    return _Check_Prog_End();
}

//��ʱ��Ϣ�У����ڵĵ�0λ��ʾ����1����6λ��ʾ������
//��鵱ǰʱ���Ƿ��ڽ�Ŀ��������ʱ���ڣ����򷵻�1�����򷵻�0
INT8U Check_Prog_Play_Time(void)
{   
#if CLOCK_EN
  //INT8U Temp[20];
  INT16U Temp1,Temp2,Temp3;

  //memset(Temp, 0xFF, sizeof(Temp));
#if QT_EN
  if(Preview_Mode EQ PREVIEW_PROG) //��ĿԤ������£������ţ�������ĻԤ������£���Ҫ�жϽ�Ŀʱ���
      return 1;
#endif

  //�����ڶ�ʱ
  if(Prog_Para.Timing[0].Week_Check > 0)
  {
    if(GET_BIT(Prog_Para.Timing[0].Week_Flag, Cur_Time.Time[T_WEEK]) EQ 0)
      return 0;
  }


  //�����ڶ�ʱ
  if(Prog_Para.Timing[0].Date_Check > 0)
  {
    Temp1 = (INT16U)Cur_Time.Time[T_YEAR]*365 + (INT16U)Cur_Time.Time[T_MONTH] * 31 + Cur_Time.Time[T_DATE];
	Temp2 = (INT16U)Prog_Para.Timing[0].Start_Date[0] * 365 + (INT16U)Prog_Para.Timing[0].Start_Date[1] * 31 + Prog_Para.Timing[0].Start_Date[2];
	Temp3 = (INT16U)Prog_Para.Timing[0].End_Date[0] * 365 + (INT16U)Prog_Para.Timing[0].End_Date[1] * 31 + Prog_Para.Timing[0].End_Date[2];
    
	if(!(Temp1 >= Temp2 && Temp1 <= Temp3))
      return 0;

  }

  //��ʱ�䶨ʱ
  if(Prog_Para.Timing[0].Time_Check > 0)
  {
    Temp1 = (INT16U)Cur_Time.Time[T_HOUR]*60 + (INT16U)Cur_Time.Time[T_MIN];
	Temp2 = (INT16U)Prog_Para.Timing[0].Start_Time[0] * 60 + (INT16U)Prog_Para.Timing[0].Start_Time[1];
	Temp3 = (INT16U)Prog_Para.Timing[0].End_Time[0] * 60 + (INT16U)Prog_Para.Timing[0].End_Time[1];

    if(Temp2 <= Temp3)
	{
	  if(Temp1 < Temp2 || Temp1 >= Temp3)
	    return 0;
	}
	else
	{
	  if(Temp1 >= Temp3 && Temp1 < Temp2)
	    return 0;
	}
  }

  return 1;
#else
  return 1;
#endif
}

/*
INT8U Check_Prog_Play_Time()
{
 return 1;
}
*/
//ÿ��MOVE_STEP_TIMER ms ���øú�����ʵ���ƶ�Ч��
void Show_Timer_Proc(void)
{
  //Pub_Timer_Proc(); //��ʱ��
  Update_Show_Data(); //������ʾ����

}

INT8U Inc_Prog_No(INT8U Prog_No)
{
  return 1;
}

void Calc_Prog_Play_Counts(void)
{
    INT16U Min_Counts = 0xFFFF;
    INT8U i;

    //��С���Ŵ����ǽ�Ŀ�Ĳ��Ŵ���---����Ҳ�ɲ����������Ĳ��Ŵ���
    Min_Counts = 0xFFFF;
    for(i = 0; i < Prog_Para.Area_Num && i < MAX_AREA_NUM; i ++)
    {
      if(Prog_Status.Area_Status[i].Counts < Min_Counts)
        Min_Counts = Prog_Status.Area_Status[i].Counts;
    }

    Prog_Status.Play_Status.Counts = Min_Counts; //�����з����ڵ���С���Ŵ������ǽ�Ŀ���ܲ��Ŵ���
    SET_SUM(Prog_Status.Play_Status);
}

void Check_RT_Play_Status()
{
  static S_Int32U Sec = {CHK_BYTE, 0xFF, CHK_BYTE};
  
  if(Sec.Var != Pub_Timer.Sec) //ÿ���ʵʱ��ʾ����ʱ
  {
    TRACE();

    Sec.Var = Pub_Timer.Sec;
	if(Prog_Status.Play_Status.RT_Play_Time > 0) //��ǰ�Ƿ���ʵʱ����״̬���Ǽ�ʱ������ʱ���˳�
	{
	  Prog_Status.Play_Status.RT_Play_Time--;
	  if(Prog_Status.Play_Status.RT_Play_Time EQ 0)
	    RT_Play_Status_Exit();
	  //return;
	}
  }
}

INT8U Check_Prog_Para(S_Prog_Para *pPara)
{
  INT8U i;

  if(pPara->Area_Num > MAX_AREA_NUM)
    return 0;

  for(i = 0; i<pPara->Area_Num; i ++)
  {
    if(pPara->Area[i].X >= Screen_Para.Base_Para.Width ||\
	   pPara->Area[i].X + pPara->Area[i].X_Len > Screen_Para.Base_Para.Width ||\
	   pPara->Area[i].Y >= Screen_Para.Base_Para.Height ||\
	   pPara->Area[i].Y + pPara->Area[i].Y_Len > Screen_Para.Base_Para.Height)
	   return 0; 
  }
  return 1;
}

//����Ƿ���Ҫ���½�Ŀ����
void Check_Update_Program_Para(void)
{
  INT8U Re,Prog_Re;
  INT8U i,Prog_No;//,Count = 0;
  INT16U Len;
#if CLOCK_EN
  static S_Int8U Min = {CHK_BYTE, 0xFF, CHK_BYTE};
#endif   
  Re = CHK_HT(Prog_Status);
  if(Re EQ 0)
    ASSERT_FAILED();
 
  if(Screen_Status.Com_Time > 0 ||\
     Prog_Status.Play_Status.RT_Play_Time > 0)
    return;

  if(Prog_Status.Play_Status.New_Prog_Flag EQ 0)//--��ǰ�ڽ�Ŀ����״̬
  {
    TRACE();

#if CLOCK_EN
    if(Min.Var EQ 0xFF) //��һ�ν���,ͬ��ʱ��
      Min.Var = Cur_Time.Time[T_MIN];

    if(GET_VAR(Min) != Cur_Time.Time[T_MIN]) //ÿ����+1����ǰ��Ŀ�Ĳ���ʱ��
    {
      Min.Var = Cur_Time.Time[T_MIN];
      Prog_Status.Play_Status.Time ++;
      SET_SUM(Prog_Status.Play_Status);
    }
#endif   
    
    //debug("check prog end! counts = %d", Min_Counts);
    if(Check_Prog_End() > 0)//==0��ʾ��Ŀ����
    {
      //��ȡ�ý�Ŀ�Ĵ洢����
      Prog_Status.Play_Status.Play_Flag = 0;
      Prog_Status.Play_Status.New_Prog_Flag = NEW_FLAG;
      Prog_Status.Play_Status.Prog_No ++;
      SET_SUM(Prog_Status.Play_Status);

    }
  }

  //if(Prog_Status.Play_Status.Play_Flag EQ 0) //��δ�����Ŀ����״̬
  //{
    if(Prog_Status.Play_Status.New_Prog_Flag &&
	   Prog_Num.Num)//while(1) //Ѱ����һ���ɲ��ŵĽ�Ŀ
    {
      TRACE();

#if QT_EN
      if(Preview_Mode EQ PREVIEW_PROG)
      {
        Prog_Status.Play_Status.Prog_No = Preview_Prog_No;
        SET_SUM(Prog_Status.Play_Status);
      }
#endif

      if(Prog_Status.Play_Status.Prog_No >= Prog_Num.Num ||\
         Prog_Status.Play_Status.Prog_No >= MAX_PROG_NUM)
      {
        Prog_Status.Play_Status.Prog_No = 0;
        SET_SUM(Prog_Status.Play_Status);
      }
#if SMS_EN
      Reset_Cur_SMS_File_No();
#endif
      debug("\r\n-----update new prog %d para-----\r\n", Prog_Status.Play_Status.Prog_No);

      Re = 1;
      Re &=(Prog_Status.Play_Status.Prog_No EQ Prog_Status.Play_Status.Last_Prog_No)?1:0;
      Re &= CHK_HT(Prog_Status.Play_Status);
      Re &= CHK_SUM(Prog_Status.Play_Status);
      Re &= CHK_SUM(Prog_Para);
      //Re &= CHK_SUM(Prog_Status.Block_Index);

      //����ϴβ��ź͵��β��ŵĽ�Ŀ��һ���ģ��򲻸��½�Ŀ������
      if(Re)//Prog_Status.Play_Status.Play_Flag = 0;
      {
        TRACE();

        debug("same prog, no update");
        for(i = 0; i < MAX_AREA_NUM; i ++)
        {
          Prog_Status.Area_Status[i].Counts = 0;
          SET_SUM(Prog_Status.Area_Status[i]);
        }
        //memset((INT8U *)Prog_Status.Area_Status[i].CS + CS_BYTES, 0, S_OFF(S_Area_Status, Tail) - S_OFF(S_Area_Status, CS) - CS_BYTES);

        Prog_Status.Play_Status.Time = 0;
        Prog_Status.Play_Status.Counts = 0;
        Prog_Status.Play_Status.New_Prog_Flag = 0;
        SET_SUM(Prog_Status.Play_Status);

        //Clr_Show_Data();
		if(Check_Prog_Play_Time() EQ 0)//�ý�Ŀ���ڲ���ʱ����,����ǰ�沥�ŵ���ͬһ����Ŀ��˵����ǰû�пɲ��Ž�Ŀ
		{
          Screen_Status.Self_OC_Flag = CLOSE_FLAG; //�����Լ��ر���Ļ����ΪΨһһ����Ŀ����������
		  SET_SUM(Screen_Status);

          Prog_Status.Play_Status.New_Prog_Flag = NEW_FLAG;
          SET_SUM(Prog_Status.Play_Status);
		}
        return;
      }
      
      TRACE();

      Prog_Status.Play_Status.Last_Prog_No = 0xFF; //����Ϊһ�������ڵĽ�Ŀ��
      //SET_HT(Prog_Status.Play_Status);
      SET_SUM(Prog_Status.Play_Status);

      Len = Read_Prog_Para(Prog_Status.Play_Status.Prog_No, Pub_Buf, Pub_Buf, sizeof(Pub_Buf)); //���¸��½�Ŀ����

	  Prog_Re = 0;

      if(Len > 0)
      {
		memcpy((INT8U *)&Prog_Para.Head + 1, Pub_Buf, sizeof(Prog_Para) - CHK_BYTE_LEN);
        SET_HT(Prog_Para);
	    SET_SUM(Prog_Para);

	    if(Check_Prog_Para(&Prog_Para) > 0 && Check_Prog_Play_Time() > 0)
		{
	        TRACE();
	
	        Prog_No = Prog_Status.Play_Status.Prog_No;
	        Prog_Status_Init();//Clr_Prog_Status();���˸��½�Ŀ����������״̬
	        Prog_Status.Play_Status.Prog_No = Prog_No;
	        SET_SUM(Prog_Status.Play_Status);

                //Len = Read_Prog_Block_Index(Prog_Status.Play_Status.Prog_No);//���¶�ȡ��Ŀ�Ĵ洢����
	
	          TRACE();
	
	          Clr_All_Show_Data();
	
	          //memcpy((INT8U *)&(pProg_Para->Prog_No), Pub_Buf, sizeof(S_Prog_Para) - CHK_BYTE_LEN);
	          //void Draw_Border(S_Show_Data *pDst, INT8U Area_No, INT8U *pData, INT8U Width, INT8U Height,  INT32U Step)
	          if(Prog_Para.Border_Check)
	          Draw_Border(&Show_Data_Bak, MAX_AREA_NUM, Pub_Buf + sizeof(S_Prog_Para) - CHK_BYTE_LEN, 0,0);
	
	          Prog_Status.Play_Status.Last_Prog_No = Prog_No;
	          Prog_Status.Play_Status.New_Prog_Flag = 0;
	          //SET_HT(Prog_Status.Play_Status);
	          SET_SUM(Prog_Status.Play_Status);
	
	          for(i = 0; i < MAX_AREA_NUM; i ++)
	          {
	            Prog_Status.Area_Status[i].New_File_Flag = NEW_FLAG;
	            Prog_Status.Area_Status[i].File_No = 0;
	            Prog_Status.Area_Status[i].SCN_No = 0;
	
	            Prog_Status.Area_Status[i].Last_File_No = 0xFF;
	            Prog_Status.Area_Status[i].Last_SCN_No = 0xFFFF;
	            SET_SUM(Prog_Status.Area_Status[i]);
	          }
	
	          Screen_Status.Self_OC_Flag = OPEN_FLAG; //���ز��ţ���ֹ֮ǰ�ر���
			  SET_SUM(Screen_Status);
	
	          Prog_Re = 1;
              }

      }
      
	  if(Prog_Re EQ 0) //û�ж�ȡ����ȷ����,������ȡ��һ����Ŀ����
      {
        TRACE();

        Prog_Status.Play_Status.New_Prog_Flag = NEW_FLAG;
		//Prog_Status.Play_Status.Last_Prog_No = 0xFF;
        Prog_Status.Play_Status.Prog_No ++;
        SET_SUM(Prog_Status.Play_Status);

        ASSERT_FAILED();
        if(Len EQ 0)
          debug("read prog para failed");
        else
          debug("prog %d now not play time", Prog_Status.Play_Status.Prog_No);
      }

      //Prog_Status.Play_Status.Prog_No ++; //��û�ж�����Ŀ����������£���ȡ��һ����Ŀ�Ĳ���
      //����ѯ����������Screen_Para.Prog_Num��MAX_PROG_NUM��
      //if(Count > Screen_Para.Prog_Num || Count > MAX_PROG_NUM)
        //break;
    }
  //}
}

//����ڴ��е����ݻ��߲����Ƿ���ȷ
void Check_Show_Data_Para(void)
{
  INT8U i, Re = 1;
  //INT8U Flag;

  Re &= CHK_HT(Screen_Para);
  //Re &= CHK_SUM(Screen_Para);

  Re &= CHK_HT(Prog_Num);
  //Re &= CHK_SUM(Prog_Num);
    
  Re &= CHK_HT(Prog_Para);
  //Re &= CHK_SUM(Prog_Para);

  Re &= CHK_HT(Prog_Status);
  Re &= CHK_HT(Cur_Block_Index);
  Re &= CHK_HT(Show_Data);
  Re &= CHK_HT(Show_Data_Bak);
#if CLOCK_EN
  Re &= CHK_HT(Cur_Time);
#endif
  if(Re EQ 0)
    ASSERT_FAILED();

  for(i = 0; i < S_NUM(Prog_Status.Area_Status); i ++)
  {
    Re = CHK_HT(Prog_Status.Area_Status[i]);
    if(Re EQ 0)
      ASSERT_FAILED();

    Re = CHK_SUM(Prog_Status.Area_Status[i]);
    if(Re EQ 0)
        ASSERT_FAILED();

    Re = Chk_File_Para_HT_Sum((U_File_Para *)&Prog_Status.File_Para[i]);
    if(Re EQ 0)
        ASSERT_FAILED();
  }
}

//����ʵʱ��ʾ״̬
void RT_Play_Status_Enter(INT16U Sec)
{
  //if(Area_No EQ 0)
  {
    //Prog_Status.Play_Status.RT_Play_Flag = RT_PLAY_FLAG;
	Prog_Status.Play_Status.RT_Play_Time = Sec;//*1000; //msΪ��λ
    SET_SUM(Prog_Status.Play_Status);
  }/*
  else if(Area_No <= MAX_AREA_NUM)
  {
    Prog_Status.Area_Status[Area_No] = RT_PLAY_FLAG;
	SET_SUM(Screen_Status);
  }
  else
    ASSERT_FAILED();
	*/
}

//�˳�ʵʱ��ʾ״̬
void RT_Play_Status_Exit(void)
{
	Restore_Show_Area();
	Prog_Status.Play_Status.RT_Play_Time = 0;
    SET_SUM(Prog_Status.Play_Status);

    debug("rt play exit\r\n");
}

void Prog_Status_Init(void)
{
    INT8U i;

  memset((void *)&Prog_Status, 0, sizeof(Prog_Status));
  SET_HT(Prog_Status);
  for(i = 0; i < MAX_AREA_NUM; i ++)
  {
      SET_HT(Prog_Status.Area_Status[i]);

      Prog_Status.Area_Status[i].Last_File_No = 0xFF;
      Prog_Status.Area_Status[i].Last_SCN_No = 0xFFFF;

      SET_SUM(Prog_Status.Area_Status[i]);

      Set_File_Para_HT_Sum((U_File_Para *)&Prog_Status.File_Para[i]);
      if(Chk_File_Para_HT_Sum((U_File_Para *)&Prog_Status.File_Para[i]) EQ 0)
          ASSERT_FAILED();
  }

  SET_HT(Prog_Status.Play_Status);
  SET_SUM(Prog_Status.Play_Status);
}

//���ڴ��еı�����ʼ��ͷβ
void Ram_Init(void)
{
  //INT8U i;
  memset(&Show_Data, 0x00, sizeof(Show_Data));
  memset(&Show_Data_Bak, 0, sizeof(Show_Data_Bak));

  memset(&Screen_Para, 0, sizeof(Screen_Para));
  memset(&Prog_Num, 0, sizeof(Prog_Num));
  memset(&Prog_Para, 0, sizeof(Prog_Para));

  //memset((void *)&Screen_Status, 0, sizeof(Screen_Status));
  Screen_Status.Time_OC_Flag = CLOSE_FLAG;

  memset((void *)&Prog_Status, 0, sizeof(Prog_Status));

#if DATA_PREP_EN >0
  memset(&Prep_Data, 0, sizeof(Prep_Data));
#endif  

  memset(&Cur_Block_Index, 0, sizeof(Cur_Block_Index));
  //memset(&Cur_Time, 0, sizeof(Cur_Time));		//����ʼ��ʱ�ӣ���Ϊreplay��ʱ��Ҳ���øĺ������ᵼ����ʾʱ��Ϊ0

  SET_HT(Screen_Para);
  SET_HT(Prog_Num);
  SET_HT(Prog_Para);
  SET_HT(Screen_Status);
#if DATA_PREP_EN >0
  SET_HT(Prep_Data);
#endif  
  SET_HT(Cur_Block_Index);
  SET_HT(Show_Data);
  SET_HT(Show_Data_Bak);
  SET_HT(Cur_Block_Index);
#if CLOCK_EN
  SET_HT(Cur_Time);
#endif
  SET_HT(Pub_Timer);

  Prog_Status_Init();

  Prog_Status.Play_Status.Prog_No = 0x00;
  Prog_Status.Play_Status.New_Prog_Flag = NEW_FLAG;

  Prog_Status.Play_Status.Last_Prog_No = 0xFF;
  SET_HT(Prog_Status.Play_Status);
  SET_SUM(Prog_Status.Play_Status);

#if TXT_SHOW_EN
  Clr_Txt_Ram_Show_Data();
#endif
/*
#if QT_EN EQ 0
  memset(Scan_Data, 0xFF, sizeof(Scan_Data));
  memset(Scan_Data0, 0xFF, sizeof(Scan_Data0));
#endif
*/
}
/*
//��Ч����������ʱ����
void Effect_Proc(void)
{
  static S_Int32U Ms_Timer = {CHK_BYTE, 0x00, CHK_BYTE};
  //if(Prog_Status.Play_Status.Effect_Flag > 0)
  if(Pub_Timer.Ms >= MOVE_STEP_PERIOD + Ms_Timer.Var)
  {
    Ms_Timer.Var = Pub_Timer.Ms; 

    Prog_Status.Play_Status.Effect_Counts = 0;
    Prog_Status.Play_Status.Effect_Flag = 0;
	
    Show_Timer_Proc();

	if(Prog_Status.Play_Status.Effect_Counts >= Prog_Status.Play_Status.Max_Effect_Counts)	//����Ӧ�ٶȵ��ڣ�
	  Prog_Status.Play_Status.Max_Effect_Counts = Prog_Status.Play_Status.Effect_Counts + 15;
  }
}
*/
//��ʾ��ش���
void Show_Main_Proc(void)
{
  Screen_Proc();
 
  if(Get_Screen_Open_Status() != CLOSE_FLAG) //��ǰ�ڿ���״̬�Ž���
  {
    Check_RT_Play_Status();
    Check_Update_Program_Para(); //����Ƿ���Ҫ���½�Ŀ
    Check_Update_Show_Data_Bak(); //����Ƿ���Ҫ������ʾ����������
	//Effect_Proc();
#if DATA_PREP_EN >0    
    Check_Update_Data_Prep();
#endif    
    Check_Show_Data_Para();
  }
}

//����һ��ʵʱ��ʾ����,������ԭ������ʾ����
void Set_RT_Show_Area(INT16U X, INT16U Y, INT16U Width, INT16U Height)
{
//---���ݵ�ǰ����
  RT_Show_Para.Area_Num = Prog_Para.Area_Num;
  RT_Show_Para.X = Prog_Para.Area[0].X;
  RT_Show_Para.Y = Prog_Para.Area[0].Y;
  RT_Show_Para.X_Len = Prog_Para.Area[0].X_Len;
  RT_Show_Para.Y_Len = Prog_Para.Area[0].Y_Len;	 
  RT_Show_Para.Time_OC_Flag = Screen_Status.Time_OC_Flag;
  RT_Show_Para.Manual_OC_Flag = Screen_Status.Manual_OC_Flag;
  RT_Show_Para.Self_OC_Flag	= Screen_Status.Self_OC_Flag;
  //RT_Show_Para.Screen_Width = Screen_Para.Base_Para.Width;
  //RT_Show_Para.Screen_Height = Screen_Para.Base_Para.Height;
  //RT_Show_Para.Screen_Color = Screen_Para.Base_Para.Color;
  SET_HT(RT_Show_Para);

  Prog_Para.Area_Num = 1; //������1
  Prog_Para.Area[0].X = X;
  Prog_Para.Area[0].Y = Y;
  Prog_Para.Area[0].X_Len = Width;//Screen_Para.Base_Para.Width;
  Prog_Para.Area[0].Y_Len = Height;//Screen_Para.Base_Para.Height;
  SET_SUM(Prog_Para);

  //Screen_Para.Base_Para.Width = Width;
  //Screen_Para.Base_Para.Height = Height;
  //Screen_Para.Base_Para.Color = 0x01;
  //SET_SUM(Screen_Para);
 
  Screen_Status.Time_OC_Flag = OPEN_FLAG;
}

//�ָ���ʾ����
void Restore_Show_Area(void)
{
  Prog_Para.Area_Num =RT_Show_Para.Area_Num; //������1
  Prog_Para.Area[0].X = RT_Show_Para.X;
  Prog_Para.Area[0].Y = RT_Show_Para.Y;
  Prog_Para.Area[0].X_Len = RT_Show_Para.X_Len;//Screen_Para.Base_Para.Width;
  Prog_Para.Area[0].Y_Len = RT_Show_Para.Y_Len;//Screen_Para.Base_Para.Height;
  SET_SUM(Prog_Para);

  //Screen_Para.Base_Para.Width = RT_Show_Para.Screen_Width;
  //Screen_Para.Base_Para.Height = RT_Show_Para.Screen_Height;
  //Screen_Para.Base_Para.Color = RT_Show_Para.Screen_Color;
  //SET_SUM(Screen_Para);
  Screen_Status.Time_OC_Flag = RT_Show_Para.Time_OC_Flag;
  Screen_Status.Manual_OC_Flag = RT_Show_Para.Manual_OC_Flag;
  Screen_Status.Self_OC_Flag = RT_Show_Para.Self_OC_Flag;
}




 //����format��ap���������������Ϣ
 // INT16U LED_Print(INT8U Font, INT8U Color, S_Show_Data *pData, INT8U Area_No, INT16U X, INT16U Y, const INT8S *format,...)

extern void Reset_Ram_Screen_Para(void);
extern void Reset_Ram_SMS_Phone_No(void);
extern void Reset_Ram_SMS_File_Flag(void);
extern void Write_SMS_File_Flag(void);
//��ʾ��ʼ��
void Para_Init(void)
{
  Ram_Init();

#if QT_EN == 0
  //����Ĭ�ϲ����ж�
  if(Chk_JP_Status() EQ FAC_STATUS && Chk_Test_Key_Down()) //����״̬�Ҳ��԰�������
  {
    Delay_sec(1);
	if(Chk_JP_Status() EQ FAC_STATUS && Chk_Test_Key_Down())
	{
	   Reset_Ram_Screen_Para();
	   Write_Screen_Para();

	   Prog_Num.Num = 0;
	   Write_Prog_Num();

#if SMS_EN
	   Reset_Ram_SMS_Phone_No();
	   Write_Storage_Data(SDI_SMS_PHONE_NO, &SMS_Phone_No, sizeof(SMS_Phone_No));

	   Reset_Ram_SMS_File_Flag();
	   Write_SMS_File_Flag();
#endif
	}
  }
#endif

  Read_Screen_Para();
  Read_Prog_Num();
  Calc_Screen_Color_Num(); //������Ļ��ɫ����
  Build_Scan_Data_Index(); //����������

#if SMS_EN
  Read_SMS_File_Flag();
  Reset_Cur_SMS_File_No();
#endif


/*--���´��������
  One_SMS_Proc("*DEL999");
  
  One_SMS_Proc("*P00002B5001+���ǵ�һ�������ƶ��Ų��Ի�ӭʹ�á�.");

  One_SMS_Proc("*P0021AB0101+������");
  One_SMS_Proc("*P0040AB0101+kji�ڶ�");
  One_SMS_Proc("*P0041AB0101+������xxx");

  One_SMS_Proc("*P005+���������׶���");
  
  One_SMS_Proc("*P0060AB01+��������");
  One_SMS_Proc("*P0061AB01+��xxx");

  //One_SMS_Proc("*SCN0512X128,100,0200");
  One_SMS_Proc("*MPN18900732873");
  One_SMS_Proc("*MPN0");
*/
}

void Para_Show(void)
{/*
  INT16U Len;
  //INT8U IP[4];
  //INT32U Baud; //���ڲ�����

 //��ʾ�忨��ַ�ʹ��ڲ�����

  Len = RT_LED_Print(FONT0, 0x01, 0, 0, 3, "%d-%d", Screen_Para.COM_Para.Addr, Screen_Para.COM_Para.Baud);

#if UDISK_EN  
  memcpy(IP, &Screen_Para.ETH_Para.IP, 4);	//��ʾIP��ַ�Ͷ˿ں�
  Len = RT_LED_Print(FONT0, 0x01, Len, 0, 3, "%d.%d.%d.%d:%d", IP[3], IP[2], IP[1], IP[0], Screen_Para.ETH_Para.Port);
#endif
  */
}

#if CLOCK_EN
void Print_Cur_Time(void)
{
  debug("cur time: %2d-%2d-%2d %2d:%2d:%2d", Cur_Time.Time[T_YEAR], Cur_Time.Time[T_MONTH], Cur_Time.Time[T_DATE],\
                                             Cur_Time.Time[T_HOUR], Cur_Time.Time[T_MIN], Cur_Time.Time[T_SEC]);
}
#endif

//Direct��ʾ����,��б�߻�����б��,0��ʾ��1��ʾ��
//FlagΪ0��ʾ��ż��λ��б�ߣ�1��ʾ����λ��б��
void Screen_Test_Draw_Line(INT8U Direct, INT8U Flag)
{
  INT16U i;
  S_Point P0,P1;

  for(i = 0; i < Screen_Para.Base_Para.Width + Screen_Para.Base_Para.Height - 1; i ++)
  {
    Clr_Watch_Dog();

    if(Direct EQ 0)
	{ 
	    P0.X = (i < Screen_Para.Base_Para.Width)?i:Screen_Para.Base_Para.Width - 1;
		P0.Y = (i < Screen_Para.Base_Para.Width)?0:(i - Screen_Para.Base_Para.Width + 1);
	
	    P1.X = (i < Screen_Para.Base_Para.Height)?0:(i - Screen_Para.Base_Para.Height + 1);
		P1.Y = (i < Screen_Para.Base_Para.Height)?i:(Screen_Para.Base_Para.Height - 1);	
	}
	else
	{
	    P0.X = (i < Screen_Para.Base_Para.Height)?0:(i - Screen_Para.Base_Para.Height + 1);
		P0.Y = (i < Screen_Para.Base_Para.Height)?(Screen_Para.Base_Para.Height - 1 - i):0;
	
	    P1.X = (i < Screen_Para.Base_Para.Width)?i:(Screen_Para.Base_Para.Width - 1);// - (i - Screen_Para.Base_Para.Width + 1);
		P1.Y = (i < Screen_Para.Base_Para.Width)?(Screen_Para.Base_Para.Height - 1):(Screen_Para.Base_Para.Height - 1 - (i - Screen_Para.Base_Para.Width + 1));
	}

    if(i % 4 <= Flag)
      Draw_Line(&Show_Data, 0, &P0, &P1, 0x03);
  }

}

//����1��ʾ�а����˳�
//����0��ʾ������ʱ�˳�
INT8U Screen_Test_Wait_Key(void)
{
  INT16U i;
  INT8U Test_Key_Up_Flag = 0;

    for(i = 0; i< 300; i ++)
	{
		Delay_ms(1);

		if(Test_Key_Up_Flag EQ 0)
		  Test_Key_Up_Flag = Chk_Test_Key_Up();

		if(Test_Key_Up_Flag && Chk_Test_Key_Down())
		{
		  Test_Key_Up_Flag = 0;
		  break;
		}
	 }

	if(i != 300)
	  return 1;
	else
	  return 0;
}

//����Ļ���в���
void Screen_Test(void)
{
  S_Point P0;
  INT8U i;

#if 0
   Screen_Para.Base_Para.Width = 64; 
   Screen_Para.Base_Para.Height = MAX_SCAN_BLOCK_NUM * 16;
   Screen_Para.Base_Para.Color = 0x03;
   Screen_Status.Color_Num = 2;

   Screen_Para.Scan_Para.Direct = 0x02;//0x03;
   Screen_Para.Scan_Para.Rows_Fold = 0x00;//0x01;
   Screen_Para.Scan_Para.Cols_Fold = 0x00;//0x02;
   Screen_Para.Scan_Para.Rows = 16;
   Screen_Para.Scan_Para.Data_Polarity = 0;

   Screen_Status.Time_OC_Flag = 0;

   memset((INT8U *)Show_Data.Color_Data, 0x01, sizeof(Show_Data.Color_Data));

   Set_RT_Show_Area(0, 0, Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);
   P0.X = 0;
   P0.Y = 0;

   P1.X = 0;
   P1.Y = 0;
   
   while(1)
   {
	 //Set_Area_Point_Data(&Show_Data, 0, 0, 0, 0x01);
	 //Set_Area_Point_Data(&Show_Data, 0, 63, 0, 0x01);
	 //for(i = 0; i < 64; i ++)
	  // Set_Area_Point_Data(&Show_Data, 0, 23, 16, 0x01);
	   //Set_Area_Point_Data(&Show_Data, 0, 24, 16, 0x01);

	 //Set_Area_Point_Data(&Show_Data, 0, 32, 17, 0x02);
	 //Set_Area_Point_Data(&Show_Data, 0, 48, 17, 0x03);

   //Copy_Filled_Rect(&Show_Data_Bak, 0, &P0, 1064, 64, &Show_Data, &P1, 0);
   }  
#endif
 //--------------------
#if RMDK_SIM_EN EQ 0
  //���԰������²��ҵ�ǰû���ڹ���״̬���������Ļ�Լ�
  if(!(Chk_Test_Key_Down() && Chk_JP_Status() EQ NORMAL_STATUS))
    return;
#else
#if defined(CARD_A)
   Screen_Para.Base_Para.Width = 720; 
   Screen_Para.Base_Para.Height = 32;
   Screen_Para.Base_Para.Color = 0x01;
   SET_SUM(Screen_Para);
#elif defined(CARD_B)
   Screen_Para.Base_Para.Width = 1024; 
   Screen_Para.Base_Para.Height = 64;
   Screen_Para.Base_Para.Color = 0x01;
#elif defined(CARD_C)
   Screen_Para.Base_Para.Width = 2048; 
   Screen_Para.Base_Para.Height = 64;
   Screen_Para.Base_Para.Color = 0x01;
   SET_SUM(Screen_Para);
#else
#error "RMDK_SIIM card type error"
#endif
#endif

 //����ʵʱ��ʾ����
  Set_RT_Show_Area(0, 0, Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);
 
  //ȫ���������
  RT_Play_Status_Enter(1);
 /*-------------
  while(1)
  {
	 Show_Data.Color_Data[(120 -1 )*2] = 0x55;
	 Show_Data.Color_Data[120 * 2 * 40 + (120 - 2) * 2 + 1] = 0x55;
	 Show_Data.Color_Data[120 * 2 * 41 + (120 - 2) * 2 + 1] = 0xAA;
  	 Show_Data.Color_Data[120 * 2 * 42 + (120 - 1) * 2 + 1] = 0x00;
   	 Show_Data.Color_Data[120 * 2 * 43 + (120 - 1) * 2 + 1] = 0xFF;
  }*/
  //-------------------
  //Set_Show_Data();
  Clr_Show_Data();

  for(i = 1; i <= 2; i ++)
  {
	  if(Screen_Para.Base_Para.Color & i)
	  {
	    P0.X = P0.Y = 0;
	    Fill_Rect(&Show_Data, 0, &P0, Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height, i);
	    while(1)
	    {
	      if(Screen_Test_Wait_Key())
		  break;
	     }
	  }
  }

   
  //��б�߲���
  Clr_Show_Data();
  Clr_Watch_Dog();

  for(i = 0 ; i<4; i++)
  {	
	  Screen_Test_Draw_Line(0, i);
	
	  while(1)
	  {
	    if(Screen_Test_Wait_Key())
		  break;
	  }
  }

  //��б�߲���
  Clr_Show_Data();
  Clr_Watch_Dog();

  for(i = 0 ; i<4; i++)
  {	
	  Screen_Test_Draw_Line(1, i);
	
	  while(1)
	  {
	    if(Screen_Test_Wait_Key())
		  break;
	  }
  }

  Clr_Show_Data();
  
  //Restore_Show_Area();
  RT_Play_Status_Exit(); //�˳�ʵʱ��ʾ״̬
}

//���²������н�Ŀ
void Replay_Prog(void)
{
	debug("replay prog");

	Para_Init();
/*	
	Clr_Show_Data();
	memset(Show_Data_Bak.Color_Data, 0, sizeof(Show_Data_Bak.Color_Data));

	#if DATA_PREP_EN
	memset(&Prep_Data, 0, sizeof(Prep_Data));
	SET_HT(Prep_Data);
	#endif
	Screen_Status.Replay_Flag = 0; //������²��ű�־
	SET_SUM(Screen_Status);
	
	//���¿�ʼ�ӵ�0��Ŀ����
	Prog_Status.Play_Status.Last_Prog_No = 0xFF;
	Prog_Status.Play_Status.Prog_No = 0;
	Prog_Status.Play_Status.New_Prog_Flag = NEW_FLAG;
	SET_SUM(Prog_Status);
	
	Calc_Screen_Color_Num(); //������Ļ��ɫ����
	Build_Scan_Data_Index(); //���¹�����������
*/
}

//ɨ��ģʽ���Լ�
void Scan_Mode_Test(INT8U Mode)
{
  //INT32U Data = 0x55AA5AA5;
  INT8U i,j,k, m, n, tmp, Max_Cols_Fold, Max_Rows_Fold;
  //INT8U Direct,ErrFlag = 0;
  //S_Time TempTime,TempTime1;

  if(Screen_Status.Scan_Mode_Test_Flag EQ 0xA5) //��ֹ�ظ�����
    return;

  Screen_Status.Scan_Mode_Test_Flag = 0xA5;

  Read_Screen_Para();
 /*
  //-----------
  Screen_Para.Base_Para.Width = 64;
  Screen_Para.Base_Para.Height = 32;
  Screen_Para.Scan_Para.Cols_Fold = 0;
  Screen_Para.Scan_Para.Rows_Fold = 0;
  Screen_Para.Scan_Para.Rows = 16;
  Screen_Para.Scan_Para.Direct = 0x02;
  Screen_Para.Base_Para.Color = 0x01;
  SET_SUM(Screen_Para);
  */
  //---------------
  //debug("test!!!");
  //Screen_Test();
  //----------
  Set_RT_Show_Area(0, 0, 32, 16);
  Clr_Show_Data();

  Screen_Status.Time_OC_Flag = OPEN_FLAG;
  //Show_Data.Color_Data[0] = 0x55;
  //Show_Data.Color_Data[128] = 0xA5;
  //Show_Data.Color_Data[255] = 0x5A;
  //Show_Data.Color_Data[17] = 0x55;

  Build_Scan_Data_Index();

  while(1)
  {
   //if(Mode EQ FAC_TEST && Chk_JP_Status() != SELF_TEST_STATUS) //�����Լ�״̬�˳�
     //     break;

  for(m = 0; m < 3; m ++)	//���ֳ��õ�ɨ�跽ʽ
  {
    Clr_Watch_Dog();

    if(m EQ 0)
	  Screen_Para.Scan_Para.Rows = 16;  //1/16ɨ��
	else if(m EQ 1)
	  Screen_Para.Scan_Para.Rows = 8;	//1/8ɨ��
	else if(m EQ 2)
	  Screen_Para.Scan_Para.Rows = 4;	//1/4ɨ��
	  /*
	else if(m EQ 3)
	  Screen_Para.Scan_Para.Rows = 2;	//1/2ɨ��
	else
	  Screen_Para.Scan_Para.Rows = 1;	//��̬ɨ��
	 */

	SET_SUM(Screen_Para);

	if(Screen_Para.Scan_Para.Rows EQ 16) //1/16ɨû�д�������
	  Max_Rows_Fold = 0;
	else
	  Max_Rows_Fold = MAX_ROWS_FOLD;

    for(i = 0; i < 4; i ++)	//4������
	{
	   Clr_Watch_Dog();

        Screen_Para.Scan_Para.Direct = i;

		if(i EQ 0x01 || i EQ 0x03) //��������������룬�������ٲ���ֱ�е����ݣ���Ϊ���������������ֱ����һ���ġ�
		  tmp = 0x01; //����Rows_Fold��ʼ==1
		else
		  tmp = 0x00;

      for(j = tmp; j <= Max_Rows_Fold; j ++)
	  {
	    Clr_Watch_Dog();

	    Screen_Para.Scan_Para.Rows_Fold = j;

		if(j EQ 0)
		{
		  Max_Cols_Fold = 0;
		  tmp = 0;
		}
	    else
		{
		  Max_Cols_Fold = MAX_COLS_FOLD;
		  tmp = 1;
		 }

		for(k = tmp; k <= Max_Cols_Fold; k ++)
	    {
          Screen_Para.Scan_Para.Cols_Fold = k;
		  
		  //5��ɨ�跽ʽ������


			RT_Play_Status_Enter(1);
            LED_Print(FONT0, Screen_Para.Base_Para.Color, &Show_Data, 0, 0, 0, "%d%d%d%d", m, i, j, k);
		    //memset(Show_Data.Color_Data, 0x55, sizeof(Show_Data.Color_Data));
           	//Delay_sec(100);
			
		    for(n = 0; n < 8; n ++)
			{
			  Clr_Watch_Dog();

			  Delay_ms(100);
			  Screen_Com_Proc();
#if QT_EN
   memcpy(&(w->previewArea->screenPara), &Screen_Para, sizeof(Screen_Para));
   w->previewArea->setFixedSize(Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);
   w->previewTimerProc();
#endif
			}
			

		  }
	    }
	   }
	 }

	 //Restore_Show_Area();

  }
}

void Set_Scan_Interface_Test_Para(INT16U Width)
{
  INT8U i;
  
  Screen_Status.Color_Num = 2;
  Screen_Status.Lightness = 7; //�м�����

  Screen_Para.Base_Para.Width = Width;
  Screen_Para.Base_Para.Height = MAX_SCAN_BLOCK_NUM * 16;
  Screen_Para.Base_Para.Color = 0x03;

  Screen_Para.Scan_Para.Line_Hide = 0;

  if(Width EQ 64)
  {
    //08�ӿڵ�ɨ��
	Screen_Para.Scan_Para.Rows = 16;
	Screen_Para.Scan_Para.Rows_Fold	= 0x00;
	Screen_Para.Scan_Para.Cols_Fold	= 0x00;
	Screen_Para.Scan_Para.Direct = 0x02;
	Screen_Para.Scan_Para.OE_Polarity = 0x00;

  }
  else
  {
    //12�ӿ�
	Screen_Para.Scan_Para.Rows = 4;
	Screen_Para.Scan_Para.Rows_Fold	= 0x03;
	Screen_Para.Scan_Para.Cols_Fold	= 0x01;
	Screen_Para.Scan_Para.Direct = 0x02;
	Screen_Para.Scan_Para.OE_Polarity = 0x01;
  }

  SET_SUM(Screen_Para);

  Clr_Watch_Dog();

  memset(Show_Data.Color_Data, 0x00, sizeof(Show_Data.Color_Data)); 
  Set_RT_Show_Area(0, 0, Screen_Para.Base_Para.Width, Screen_Para.Base_Para.Height);

  for(i = 0; i < MAX_SCAN_BLOCK_NUM ; i ++)
    LED_Print(FONT0, 0x03, &Show_Data, 0, 0, i * 16, "%d", i);
}

//ɨ��ӿڲ���
INT8U Scan_Interface_Test(void) 
{
  INT8U i;
  static INT8U Enter_Flag = 0;

  if(Screen_Status.Encryption_Err_Flag) //�������ݴ���������������������ڷ�ֹ©���������
    return 0;

  if(Enter_Flag EQ 0xA5)
    return 0;

  Enter_Flag = 0xA5;
 //�����ú�ʵʱ��ʾ�������ʾ����
  
  while(1)
  {
	RT_Play_Status_Enter(2);

   //08�ӿ�
    Set_Scan_Interface_Test_Para(64);

    for(i = 0; i < 50; i ++)
	{
		Delay_ms(10);
		Screen_Com_Proc();
		Clr_Watch_Dog();
	}
 
	//12�ӿڵ�ɨ��
	Set_Scan_Interface_Test_Para(32);

    for(i = 0; i < 50; i ++)
	{
		Delay_ms(10);
		Screen_Com_Proc();
		Clr_Watch_Dog();
	}
  }
}

