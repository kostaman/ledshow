#define PIC_SHOW_C
#include "Includes.h"

//#undef QT_EN
//#define QT_EN 1

#if PIC_SHOW_EN
//�������뷽ʽ
const S_Mode_Func In_Mode_Func[]=
{
#if IN_SPEC_EFFECT_NUM > 0  
  {&Move_Show_RightNow, H_MODE, 1
#if QT_EN
   ,"������ʾ" 
#endif    
  } //������ʾ
#endif
#if IN_SPEC_EFFECT_NUM > 1 
  ,{&Move_Left_Continuous, H_MODE, 1
#if QT_EN
   ,"��������"
#endif    
  } //��������
#endif
#if IN_SPEC_EFFECT_NUM > 2  
  ,{&Move_Up_Continuous, V_MODE, 1
#if QT_EN
   ,"��������" 
#endif    
  }//��������
#endif
  //----------------
#if IN_SPEC_EFFECT_NUM > 3
  ,{&Move_Left_Continuous, H_MODE, 1
#if QT_EN
   ,"��ƽ��" 
#endif    
  } //��ƽ��
#endif
#if IN_SPEC_EFFECT_NUM > 4
  ,{&Move_Right_Continuous, H_MODE, 1
#if QT_EN
   ,"��ƽ��" 
#endif    
  } //��ƽ��
#endif
#if IN_SPEC_EFFECT_NUM > 5
  ,{&Move_Up_Continuous, V_MODE, 1
#if QT_EN
   ,"��ƽ��" 
#endif    
  } //��ƽ��
#endif
#if IN_SPEC_EFFECT_NUM > 6
  ,{&Move_Down_Continuous, V_MODE, 1
#if QT_EN
   ,"��ƽ��" 
#endif    
  } //��ƽ��
#endif
  //---------------------
#if IN_SPEC_EFFECT_NUM > 7
  ,{&Move_Left, H_MODE, 1
#if QT_EN
   ,"����" 
#endif    
  } //����
#endif
#if IN_SPEC_EFFECT_NUM > 8
  ,{&Move_Right, H_MODE, 1
#if QT_EN
   ,"����" 
#endif    
  } //����
#endif
#if IN_SPEC_EFFECT_NUM > 9
  ,{&Move_Up, V_MODE, 1
#if QT_EN
   ,"����" 
#endif    
  } //����
#endif
#if IN_SPEC_EFFECT_NUM > 10
  ,{&Move_Down, V_MODE, 1
#if QT_EN
   ,"����" 
#endif    
  } //����
#endif
#if IN_SPEC_EFFECT_NUM > 11
  ,{&Move_Left_Cover, H_MODE, 1
#if QT_EN
   ,"�󸲸�" 
#endif    
  } //�󸲸�
#endif
#if IN_SPEC_EFFECT_NUM > 12
  ,{&Move_Right_Cover, H_MODE, 1
#if QT_EN
   ,"�Ҹ���" 
#endif    
  }//�Ҹ���
#endif
#if IN_SPEC_EFFECT_NUM > 13
  ,{&Move_Up_Cover, V_MODE, 1
#if QT_EN
   ,"�ϸ���" 
#endif    
  } //�ϸ���
#endif
#if IN_SPEC_EFFECT_NUM > 14
  ,{&Move_Down_Cover, V_MODE, 1
#if QT_EN
   ,"�¸���" 
#endif    
  } //�¸���
#endif
#if IN_SPEC_EFFECT_NUM > 15
  ,{&Move_Left_Up_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"���ϸ���" 
#endif    
  } //���ϸ���
#endif
#if IN_SPEC_EFFECT_NUM > 16
  ,{&Move_Right_Up_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"���ϸ���" 
#endif    
  } //���ϸ���
#endif
#if IN_SPEC_EFFECT_NUM > 17
  ,{&Move_Left_Down_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"���¸���" 
#endif    
  } //���¸���
#endif
#if IN_SPEC_EFFECT_NUM > 18
  ,{&Move_Right_Down_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"���¸���" 
#endif    
  }//���¸���
#endif
#if IN_SPEC_EFFECT_NUM > 19
  ,{&Move_Left_Right_Open, H_MODE, 1
#if QT_EN
   ,"���ҿ���" 
#endif    
  } //���ҿ���
#endif
#if IN_SPEC_EFFECT_NUM > 20
  ,{&Move_Up_Down_Open, V_MODE, 1
#if QT_EN
   ,"������ʾ" 
#endif    
  } //���¿���
#endif
#if IN_SPEC_EFFECT_NUM > 21
  ,{&Move_Left_Right_Close, H_MODE, 1
#if QT_EN
   ,"���Һ���" 
#endif    
  } //���Һ���
#endif
#if IN_SPEC_EFFECT_NUM > 22
  ,{&Move_Up_Down_Close, H_MODE, 1
#if QT_EN
   ,"���º���" 
#endif    
  } //���º���
#endif
#if IN_SPEC_EFFECT_NUM > 23
  ,{&Move_Spin_CW, HV_ADD_MODE, 2
#if QT_EN
   ,"˳ʱ�븲��" 
#endif    
  }//˳ʱ��
#endif
#if IN_SPEC_EFFECT_NUM > 24
  ,{&Move_Spin_CCW, HV_ADD_MODE, 2
#if QT_EN
   ,"��ʱ�븲��" 
#endif    
  }//��ʱ�븲��
#endif
#if IN_SPEC_EFFECT_NUM > 25
  ,{&Move_Up_Snow, H_MODE, 3
#if QT_EN
   ,"��Ʈѩ" 
#endif    
  } //��Ʈѩ
#endif
#if IN_SPEC_EFFECT_NUM > 26
  ,{&Move_Down_Snow, H_MODE, 3
#if QT_EN
   ,"��Ʈѩ" 
#endif    
  } //��Ʈѩ
#endif
#if IN_SPEC_EFFECT_NUM > 27
  ,{&Move_Flash, FIX_MODE, 100
#if QT_EN
   ,"��˸" 
#endif    
  } //��˸
#endif
#if IN_SPEC_EFFECT_NUM > 28
  ,{&Move_Left_Laser, H_MODE, 1
#if QT_EN
   ,"������" 
#endif    
  } //������
#endif
#if IN_SPEC_EFFECT_NUM > 29
  ,{&Move_Right_Laser, H_MODE, 1
#if QT_EN
   ,"������" 
#endif    
  } //������
#endif
#if IN_SPEC_EFFECT_NUM > 30
  ,{&Move_Up_Laser, V_MODE, 1
#if QT_EN
   ,"������" 
#endif    
  } //������
#endif
#if IN_SPEC_EFFECT_NUM > 31
  ,{&Move_Down_Laser, V_MODE, 1
#if QT_EN
   ,"������" 
#endif    
  } //������
#endif
#if IN_SPEC_EFFECT_NUM > 32
  ,{&Move_Left_Tensile, FIX_MODE, 100
#if QT_EN
   ,"������" 
#endif    
  }//������
#endif
#if IN_SPEC_EFFECT_NUM > 33
  //{&Move_Right_Tensile}//������
  ,{&Move_Up_Tensile, FIX_MODE, 100
#if QT_EN
   ,"������" 
#endif    
  }//������
#endif
#if IN_SPEC_EFFECT_NUM > 34
  //{&Move_Down_Tensile}//������
  ,{&Move_Vertical_Tensile, V_MODE, 1
#if QT_EN
   ,"��ֱ����" 
#endif    
  }//��ֱ����
#endif
#if IN_SPEC_EFFECT_NUM > 35
  ,{&Move_Horizontal_Tensile, H_MODE, 1
#if QT_EN
   ,"ˮƽ����" 
#endif    
  }//ˮƽ����
#endif
#if IN_SPEC_EFFECT_NUM > 36
  ,{&Move_Left_Stretch, H_MODE, 3
#if QT_EN
   ,"���Ƶ���" 
#endif    
  } //���Ƶ���
#endif
#if IN_SPEC_EFFECT_NUM > 37
  ,{&Move_Up_Stretch, V_MODE, 1
#if QT_EN
   ,"���Ƶ���" 
#endif    
  } //���Ƶ���
#endif
#if IN_SPEC_EFFECT_NUM > 38
  ,{&Move_Horizontal_Window, FIX_MODE, 100
#if QT_EN
   ,"ˮƽ��Ҷ��" 
#endif    
  }//WIN_LEAF_WIDTH} //ˮƽ��Ҷ��
#endif
#if IN_SPEC_EFFECT_NUM > 39
  ,{&Move_Vertical_Window, FIX_MODE, 100
#if QT_EN
   ,"��ֱ��Ҷ��" 
#endif    
  }//WIN_LEAF_WIDTH} //��ֱ��Ҷ��
#endif
#if IN_SPEC_EFFECT_NUM > 40
  ,{&Move_Left_Compress, FIX_MODE, 100
#if QT_EN
   ,"����ѹ��" 
#endif    
  } //����ѹ��
#endif
#if IN_SPEC_EFFECT_NUM > 41
  ,{&Move_Up_Compress, FIX_MODE, 100
#if QT_EN
   ,"����ѹ��" 
#endif    
  }//����ѹ��
#endif
#if IN_SPEC_EFFECT_NUM > 42
  ,{&Move_Fade_In, FIX_MODE, 100
#if QT_EN
   ,"����" 
#endif    
  }//����
#endif
};

//�������뷽ʽ
const S_Mode_Func Out_Mode_Func[]=
{
#if OUT_SPEC_EFFECT_NUM > 0   
  {&Move_Show_RightNow, H_MODE, 1
#if QT_EN
   ,"�������" 
#endif    
  }
#endif
#if OUT_SPEC_EFFECT_NUM > 1
  ,{&Move_Left, H_MODE, 1
#if QT_EN
   ,"����" 
#endif    
  }//0
#endif
#if OUT_SPEC_EFFECT_NUM > 2  
  ,{&Move_Right, H_MODE, 1
#if QT_EN
   ,"����" 
#endif    
  }//1
#endif
#if OUT_SPEC_EFFECT_NUM > 3  
  ,{&Move_Up, V_MODE, 1
#if QT_EN
   ,"����" 
#endif    
  }//2
#endif
#if OUT_SPEC_EFFECT_NUM >4  
  ,{&Move_Down, V_MODE, 1
#if QT_EN
   ,"����" 
#endif    
  }//3
#endif
#if OUT_SPEC_EFFECT_NUM > 5  
  ,{&Move_Left_Cover, H_MODE, 1
#if QT_EN
   ,"�󸲸�" 
#endif    
  }//4
#endif
#if OUT_SPEC_EFFECT_NUM > 6  
  ,{&Move_Right_Cover, H_MODE, 1
#if QT_EN
   ,"�Ҹ���" 
#endif    
  }//5
#endif
#if OUT_SPEC_EFFECT_NUM > 7  
  ,{&Move_Up_Cover, V_MODE, 1
#if QT_EN
   ,"�ϸ���" 
#endif    
  }//6
#endif
#if OUT_SPEC_EFFECT_NUM > 8  
  ,{&Move_Down_Cover, V_MODE, 1
#if QT_EN
   ,"�¸���" 
#endif    
  }//7
#endif
#if OUT_SPEC_EFFECT_NUM > 9  
  ,{&Move_Left_Up_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"���ϸ���" 
#endif    
  }//8
#endif
#if OUT_SPEC_EFFECT_NUM > 10  
  ,{&Move_Right_Up_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"���ϸ���" 
#endif    
  }//9
#endif
#if OUT_SPEC_EFFECT_NUM > 11  
  ,{&Move_Left_Down_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"���¸���" 
#endif    
  }//10
#endif
#if OUT_SPEC_EFFECT_NUM > 12  
  ,{&Move_Right_Down_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"���¸���"
#endif
  }//11
#endif
#if OUT_SPEC_EFFECT_NUM > 13  
  ,{&Move_Left_Right_Open, H_MODE, 0.5
#if QT_EN
   ,"���ҿ���" 
#endif    
  }//12
#endif
#if OUT_SPEC_EFFECT_NUM > 14  
  ,{&Move_Up_Down_Open, V_MODE, 0.5
#if QT_EN
   ,"���¿���" 
#endif    
  }//13
#endif
#if OUT_SPEC_EFFECT_NUM > 15
  ,{&Move_Left_Right_Close, H_MODE, 0.5
#if QT_EN
   ,"���Һ���" 
#endif    
  }//14
#endif
#if OUT_SPEC_EFFECT_NUM > 16  
  ,{&Move_Up_Down_Close, V_MODE, 0.5
#if QT_EN
   ,"���º���" 
#endif    
  }//15
#endif
#if OUT_SPEC_EFFECT_NUM > 17  
  ,{&Move_Spin_CW, HV_ADD_MODE, 1
#if QT_EN
   ,"˳ʱ�븲��" 
#endif    
  }
#endif
#if OUT_SPEC_EFFECT_NUM > 18  
  ,{&Move_Spin_CCW, HV_ADD_MODE, 1
#if QT_EN
   ,"��ʱ�븲��" 
#endif    
  }
#endif
#if OUT_SPEC_EFFECT_NUM > 19
  ,{&Move_Fade_In, FIX_MODE, 100
#if QT_EN
   ,"����" 
#endif    
  }//����
#endif

};

INT16U Get_In_Max_Step(INT16U Width, INT16U Height, INT8U In_Mode)
{
    INT16U Re;

    if(In_Mode >= S_NUM(In_Mode_Func))
    {
       ASSERT_FAILED();
       In_Mode = 0;
    }

    switch(In_Mode_Func[In_Mode].Step_Mode)
    {
    case H_MODE:
        Re = Width*In_Mode_Func[In_Mode].Fac;
        break;
    case V_MODE:
        Re = Height*In_Mode_Func[In_Mode].Fac;
        break;
    case HV_ADD_MODE:
        Re = (Width + Height)*In_Mode_Func[In_Mode].Fac;
        break;
    case HV_SQRT_MODE:
        Re = Sqrt(Width*Width + Height*Height)*In_Mode_Func[In_Mode].Fac;
        break;
    case FIX_MODE:
        Re = In_Mode_Func[In_Mode].Fac;
        break;
    default:
        Re = 100;
        break;
    }

    return Re;

}

INT16U Get_Out_Max_Step(INT16U Width, INT16U Height, INT8U Out_Mode)
{
    INT16U Re;

    if(Out_Mode >= S_NUM(Out_Mode_Func))
    {
       ASSERT_FAILED();
       Out_Mode = 0;
    }

    switch(Out_Mode_Func[Out_Mode].Step_Mode)
    {
    case H_MODE:
        Re = Width*Out_Mode_Func[Out_Mode].Fac;
        break;
    case V_MODE:
        Re = Height*Out_Mode_Func[Out_Mode].Fac;
        break;
    case HV_ADD_MODE:
        Re = (Width + Height)*Out_Mode_Func[Out_Mode].Fac;
        break;
    case HV_SQRT_MODE:
        Re = Sqrt(Width*Width + Height*Height)*Out_Mode_Func[Out_Mode].Fac;
        break;
    case FIX_MODE:
        Re = Out_Mode_Func[Out_Mode].Fac;
        break;
    default:
        Re = 100;
        break;
    }

    return Re;
}

INT8U Check_XXX_Data(INT8U Flag)
{
    //INT8U Flag;

    //Flag = Prog_Status.File_Para[Area_No].Pic_Para.Flag;
  if(Flag EQ SHOW_CLOCK ||\
     Flag EQ SHOW_TIME ||\
     Flag EQ SHOW_TIMER ||\
     Flag EQ SHOW_TEMP ||\
     Flag EQ SHOW_LUN ||\
     Flag EQ SHOW_HUMIDITY ||\
     Flag EQ SHOW_NOISE)
      return 1;
  else
      return 0;
}

void Update_Pic_Data(INT8U Area_No)
{
  //INT8U SNum;
  INT8U In_Mode, Out_Mode;
  INT16U Area_Width, Area_Height;
  INT32U Stay_Time,In_Delay, Out_Delay;
  INT32U In_Step_Bak;
  //INT32U Out_Time;
  S_Point P0;
  //static S_Int8U Sec ={CHK_BYTE, 0xFF, {0}, CHK_BYTE};
  
  TRACE();
  //qDebug("update area %d, step = %d, max step = %d", Area_No, Prog_Status.Area_Status[Area_No].Step, Prog_Status.Area_Status[Area_No].Max_Step);

  if(Prog_Status.Play_Status.New_Prog_Flag ||\
     Prog_Status.Area_Status[Area_No].New_File_Flag ||\
     Prog_Status.Area_Status[Area_No].New_SCN_Flag) //�ý�Ŀ��÷�����û�н��벥��״̬?
    return;
  
  Stay_Time = Get_File_Stay_Time(Area_No);
  //Out_Time = Get_File_Out_Time(Area_No);
  
//---------------------------------------------------------  

  In_Step_Bak = Prog_Status.Area_Status[Area_No].In_Step;

 //------------------------------------------------------- 
 if(Prog_Status.Area_Status[Area_No].In_Step EQ 0 &&\
    Prog_Status.Area_Status[Area_No].Step_Timer EQ 0)
  {
    In_Mode = Prog_Status.File_Para[Area_No].Pic_Para.In_Mode;
    //In_Mode == 0���,1������ʾ,2��������
    if(In_Mode EQ 0) //���
        In_Mode = rand()%S_NUM(In_Mode_Func);//Cur_Time.Time[T_SEC] % S_NUM(In_Mode_Func);
    else
        In_Mode = In_Mode - 1;

    Prog_Status.Area_Status[Area_No].In_Mode = In_Mode;
    Prog_Status.Area_Status[Area_No].In_Max_Step = Get_In_Max_Step(Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len, In_Mode);
  }


 if(Prog_Status.Area_Status[Area_No].Out_Step EQ 0 &&\
    Prog_Status.Area_Status[Area_No].Step_Timer EQ 0)
 {
    Out_Mode = Prog_Status.File_Para[Area_No].Pic_Para.Out_Mode;

    if(Out_Mode EQ 0) //0���,1������,2��������,3����...
       Out_Mode = rand()%(S_NUM(Out_Mode_Func) + 1);//Cur_Time.Time[T_SEC] % S_NUM(Out_Mode_Func);
    else if(Out_Mode EQ 1)
       Out_Mode = 0; //����Ϊ0������
    else if(Out_Mode >= 2) //����������ʽ
       Out_Mode = Out_Mode - 1;

    //0���壬1-N����������ʽ...
    Prog_Status.Area_Status[Area_No].Out_Mode = Out_Mode; //��ʱ0��ʾ������,1-N��ʾ������ʽ

    if(Out_Mode >= 1)
      Prog_Status.Area_Status[Area_No].Out_Max_Step = Get_Out_Max_Step(Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len, Out_Mode - 1);
    else //������
      Prog_Status.Area_Status[Area_No].Out_Max_Step = 100;//Get_Out_Max_Step(Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len, Out_Mode - 1);
}

  //�����ƶ�״̬
  if(Prog_Status.Area_Status[Area_No].In_Step < Prog_Status.Area_Status[Area_No].In_Max_Step)
  {
      In_Delay = Get_Area_In_Step_Delay(Area_No);
        //��һ��
      if(Prog_Status.Area_Status[Area_No].Step_Timer EQ 0 &&\
         Prog_Status.Area_Status[Area_No].In_Step EQ 0)
        {
          Prog_Status.Area_Status[Area_No].Step_Timer = In_Delay;///---������һ��ֱ����ʾ��һ�εĲ���Ч��

          //Prog_Status.Area_Status[Area_No].In_Mode = In_Mode;
          //---------

          if(Check_XXX_Data(Prog_Status.File_Para[Area_No].Pic_Para.Flag))
            Update_XXX_Data(&Show_Data_Bak, Area_No);
      }


      if(Prog_Status.Area_Status[Area_No].Step_Timer < In_Delay)
        Prog_Status.Area_Status[Area_No].Step_Timer += MOVE_STEP_PERIOD;

      if(Prog_Status.Area_Status[Area_No].Step_Timer >= In_Delay)
      {
        Prog_Status.Area_Status[Area_No].Step_Timer = 0;
        Prog_Status.Area_Status[Area_No].In_Step += MOVE_STEP;

        if(Prog_Status.Area_Status[Area_No].In_Step > Prog_Status.Area_Status[Area_No].In_Max_Step)
          Prog_Status.Area_Status[Area_No].In_Step = Prog_Status.Area_Status[Area_No].In_Max_Step;

        In_Mode = Prog_Status.Area_Status[Area_No].In_Mode;

        if(In_Mode >= S_NUM(In_Mode_Func))
        {
            In_Mode = 0;
            ASSERT_FAILED();
        }

        Prog_Status.Area_Status[Area_No].Step = Prog_Status.Area_Status[Area_No].In_Step;
        Prog_Status.Area_Status[Area_No].Max_Step = Prog_Status.Area_Status[Area_No].In_Max_Step;

        //----------------
        //Prog_Status.Area_Status[Area_No].Restore_Border_Flag = 0;//���Ը���
        //-----------------
        (*(In_Mode_Func[In_Mode].Func))(Area_No);//ִ���ƶ�����

        TRACE();

        if(In_Mode EQ 0) //������ʾ
          Prog_Status.Area_Status[Area_No].In_Step = Prog_Status.Area_Status[Area_No].In_Max_Step;

        //����׶�����ﵽMAX_STEP_NUM%ͬʱͣ��ʱ��Ϊ0��ֱ�������˳��׶�
        if(Prog_Status.Area_Status[Area_No].In_Step >= Prog_Status.Area_Status[Area_No].In_Max_Step)
        {
          if(Stay_Time EQ 0) //����׶����꣬���ͣ��ʱ����0��ֱ�ӽ����˳��׶�!
          {
            Prog_Status.Area_Status[Area_No].Stay_Time = Stay_Time;
            Prog_Status.Area_Status[Area_No].Out_Step = 0;
            Prog_Status.Area_Status[Area_No].Step_Timer = 0;

            if(Prog_Status.Area_Status[Area_No].In_Mode >= 1 &&\
               Prog_Status.Area_Status[Area_No].In_Mode <= 6) //�������ƺ�����ֱ�ӽ�������
            {
                Prog_Status.Area_Status[Area_No].Stay_Time = Stay_Time;
                Prog_Status.Area_Status[Area_No].New_SCN_Flag = NEW_FLAG;
                Prog_Status.Area_Status[Area_No].SCN_No ++;
                Prog_Status.Area_Status[Area_No].In_Step = 0;
                //Prog_Status.Area_Status[Area_No].Step_Timer = 0;
                //Prog_Status.Area_Status[Area_No].Stay_Time = 0;
                Prog_Status.Area_Status[Area_No].Out_Time = 0;
                //Prog_Status.Area_Status[Area_No].Play_Flag = 0;
                SET_SUM(Prog_Status.Area_Status[Area_No]);
            }
          }

        }
      }
  }
  else if(Prog_Status.Area_Status[Area_No].Stay_Time < Stay_Time) //ͣ��ʱ��δ��
  {
    if(Check_XXX_Data(Prog_Status.File_Para[Area_No].Pic_Para.Flag))
    {
        if(Prog_Status.Area_Status[Area_No].Stay_Time EQ 0)
        {
          Prog_Status.Area_Status[Area_No].Stay_Time += MOVE_STEP_PERIOD;
          Prog_Status.Area_Status[Area_No].New_SCN_Flag = NEW_FLAG;
          Prog_Status.Area_Status[Area_No].SCN_No = 0; //���¸��±���
          Prog_Status.Area_Status[Area_No].Last_SCN_No = 0xFFFF;
          SET_SUM(Prog_Status.Area_Status[Area_No]);
          return;
        }

        if(Prog_Status.Area_Status[Area_No].Stay_Time EQ MOVE_STEP_PERIOD ||\
           Prog_Status.Area_Status[Area_No].Stay_Time % 500 EQ 0)//Sec.Var != Cur_Time.Time[T_SEC])//
        {
          //Sec.Var = Cur_Time.Time[T_SEC];
          P0.X = P0.Y = 0;
          Area_Width = Get_Area_Width(Area_No);
          Area_Height = Get_Area_Height(Area_No);
          Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Area_Width, Area_Height, &Show_Data, &P0);
          Update_XXX_Data(&Show_Data, Area_No);
        }
    }

    Prog_Status.Area_Status[Area_No].Stay_Time += MOVE_STEP_PERIOD;
    /*
    if(Prog_Status.Area_Status[Area_No].Stay_Time >= Stay_Time)//�����˳����ƶ�״̬
    {
      Prog_Status.Area_Status[Area_No].Out_Step = 0;
    }
    */
  }
  else if(Prog_Status.Area_Status[Area_No].Out_Step < Prog_Status.Area_Status[Area_No].Out_Max_Step)
  {
        Out_Delay = Get_Area_Out_Step_Delay(Area_No);
          //�ս���
        if(Prog_Status.Area_Status[Area_No].Out_Step EQ 0 &&\
           Prog_Status.Area_Status[Area_No].Step_Timer EQ 0)
          {
           Prog_Status.Area_Status[Area_No].Step_Timer = Out_Delay;

           //Prog_Status.Area_Status[Area_No].Out_Mode = Out_Mode;
           //-------------------------

           if(!(Prog_Status.Area_Status[Area_No].In_Mode >=1 &&\
              Prog_Status.Area_Status[Area_No].In_Mode <= 6)) //�����������ơ���������
           {
             Clear_Area_Data(&Show_Data_Bak, Area_No);
           }
           else
           {

             Prog_Status.Area_Status[Area_No].Out_Step = Prog_Status.Area_Status[Area_No].Out_Max_Step;
           }
         }

        //���ƶ��׶�
        if(Prog_Status.Area_Status[Area_No].Out_Step < Prog_Status.Area_Status[Area_No].Out_Max_Step)
        {
            if(Prog_Status.Area_Status[Area_No].Step_Timer < Out_Delay)
              Prog_Status.Area_Status[Area_No].Step_Timer += MOVE_STEP_PERIOD;

            if(Prog_Status.Area_Status[Area_No].Step_Timer >= Out_Delay)
            {
              Prog_Status.Area_Status[Area_No].Step_Timer = 0;
              Prog_Status.Area_Status[Area_No].Out_Step += MOVE_STEP;

              if(Prog_Status.Area_Status[Area_No].Out_Step > Prog_Status.Area_Status[Area_No].Out_Max_Step)
                Prog_Status.Area_Status[Area_No].Out_Step = Prog_Status.Area_Status[Area_No].Out_Max_Step;

              //---------
              Out_Mode = Prog_Status.Area_Status[Area_No].Out_Mode;
              if(Out_Mode EQ 0) //������
              {
                 Prog_Status.Area_Status[Area_No].Out_Step = Prog_Status.Area_Status[Area_No].Out_Max_Step;
              }
              else
              {
                Out_Mode --;//-1�л�����ӦOut_Mode_Func
                if(Out_Mode >= S_NUM(Out_Mode_Func))
                {
                  Out_Mode = 0;
                  ASSERT_FAILED();
                }

                //---------
                Prog_Status.Area_Status[Area_No].Step = Prog_Status.Area_Status[Area_No].Out_Step;
                Prog_Status.Area_Status[Area_No].Max_Step = Prog_Status.Area_Status[Area_No].Out_Max_Step;
                (*(Out_Mode_Func[Out_Mode].Func))(Area_No);//ִ���ƶ�����

                TRACE();

                if(Out_Mode EQ 0) //������ʾ
                  Prog_Status.Area_Status[Area_No].Out_Step = Prog_Status.Area_Status[Area_No].Out_Max_Step;
             }
           }
       }

       if(Prog_Status.Area_Status[Area_No].Out_Step >= Prog_Status.Area_Status[Area_No].Out_Max_Step)
       {
          //SNum��ʾ��ǰ�ļ��ܵ���Ļ����ֻ��ͼ�ĵ���Ļ�������1����
          //if(Prog_Status.File_Para[Area_No].Pic_Para.Flag EQ SHOW_PIC)
            //SNum = Prog_Status.File_Para[Area_No].Pic_Para.SNum;
          //else
            //SNum = 1;

          Prog_Status.Area_Status[Area_No].New_SCN_Flag = NEW_FLAG;
          Prog_Status.Area_Status[Area_No].SCN_No ++;
          Prog_Status.Area_Status[Area_No].Play_Flag = 0;
          SET_SUM(Prog_Status.Area_Status[Area_No]);

          Prog_Status.Area_Status[Area_No].In_Step = 0;
          Prog_Status.Area_Status[Area_No].Out_Step = 0;
          Prog_Status.Area_Status[Area_No].Step_Timer = 0;
          Prog_Status.Area_Status[Area_No].Stay_Time = 0;
          Prog_Status.Area_Status[Area_No].Out_Time = 0;

      }
  }
  else
  {
    ASSERT_FAILED(); 
  }

}
#endif

