#define PIC_SHOW_C
#include "Includes.h"

//#undef QT_EN
//#define QT_EN 1
extern void LED_Scan_One_Row(void);

#if 1//PIC_SHOW_EN
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
  /*
#if IN_SPEC_EFFECT_NUM > 1
  ,{&Move_Right_Continuous, H_MODE, 1
#if QT_EN
   ,"��������"
#endif
  } //��������
#endif
  */
#if IN_SPEC_EFFECT_NUM > 2  
  ,{&Move_Up_Continuous, V_MODE, 1
#if QT_EN
   ,"��������" 
#endif    
  }//��������
#endif
/*
#if IN_SPEC_EFFECT_NUM > 1
  ,{&Move_Down_Continuous, V_MODE, 1
#if QT_EN
   ,"��������"
#endif
  } //��������
#endif
 */
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
   ,"����б�߸���"
#endif    
  } //����б�߸���
#endif
#if IN_SPEC_EFFECT_NUM > 16
  ,{&Move_Right_Up_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"����б�߸���"
#endif    
  } //����б�߸���
#endif
#if IN_SPEC_EFFECT_NUM > 17
  ,{&Move_Left_Down_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"����б�߸���"
#endif    
  } //����б�߸���
#endif
#if IN_SPEC_EFFECT_NUM > 18
  ,{&Move_Right_Down_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"����б�߸���"
#endif    
  }//����б�߸���
#endif

#if IN_SPEC_EFFECT_NUM > 19
  ,{&Move_Left_Up_Cover0, HV_MAX_MODE, 1
#if QT_EN
   ,"����ֱ�Ǹ���"
#endif
  }//����ֱ�Ǹ���
#endif

#if IN_SPEC_EFFECT_NUM > 29
  ,{&Move_Right_Up_Cover0, HV_MAX_MODE, 1
#if QT_EN
   ,"����ֱ�Ǹ���"
#endif
  }//����ֱ�Ǹ���
#endif

#if IN_SPEC_EFFECT_NUM > 21
  ,{&Move_Left_Down_Cover0, HV_MAX_MODE, 1
#if QT_EN
   ,"����ֱ�Ǹ���"
#endif
  }//����ֱ�Ǹ���
#endif

#if IN_SPEC_EFFECT_NUM > 22
  ,{&Move_Right_Down_Cover0, HV_MAX_MODE, 1
#if QT_EN
   ,"����ֱ�Ǹ���"
#endif
  }//����ֱ�Ǹ���
#endif

#if IN_SPEC_EFFECT_NUM > 23
  ,{&Move_Left_Right_Open, H_MODE, 1
#if QT_EN
   ,"���ҿ���" 
#endif    
  } //���ҿ���
#endif
#if IN_SPEC_EFFECT_NUM > 24
  ,{&Move_Up_Down_Open, V_MODE, 1
#if QT_EN
   ,"���¿���"
#endif    
  } //���¿���
#endif
#if IN_SPEC_EFFECT_NUM > 25
  ,{&Move_Left_Right_Close, H_MODE, 1
#if QT_EN
   ,"���Һ���" 
#endif    
  } //���Һ���
#endif
#if IN_SPEC_EFFECT_NUM > 26
  ,{&Move_Up_Down_Close, V_MODE, 1
#if QT_EN
   ,"���º���" 
#endif    
  } //���º���
#endif

#if IN_SPEC_EFFECT_NUM > 27
  ,{&Move_Left_Right_Reel_Open, H_MODE, 1
#if QT_EN
   ,"���Ҿ���"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 28
  ,{&Move_Up_Down_Reel_Open, V_MODE, 1
#if QT_EN
   ,"���¾���"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 29
  ,{&Move_Spin_CW, HV_ADD_MODE, 1
#if QT_EN
   ,"˳ʱ�븲��" 
#endif    
  }//˳ʱ��
#endif
#if IN_SPEC_EFFECT_NUM > 30
  ,{&Move_Spin_CCW, HV_ADD_MODE, 1
#if QT_EN
   ,"��ʱ�븲��" 
#endif    
  }//��ʱ�븲��
#endif
#if IN_SPEC_EFFECT_NUM > 31
  ,{&Move_Up_Snow, V_MODE, SNOW_RATIO
#if QT_EN
   ,"��Ʈѩ" 
#endif    
  } //��Ʈѩ
#endif
#if IN_SPEC_EFFECT_NUM > 32
  ,{&Move_Down_Snow, V_MODE, SNOW_RATIO
#if QT_EN
   ,"��Ʈѩ" 
#endif    
  } //��Ʈѩ
#endif
#if IN_SPEC_EFFECT_NUM > 33
  ,{&Move_Flash, FIX_MODE, 100
#if QT_EN
   ,"��˸" 
#endif    
  } //��˸
#endif
#if IN_SPEC_EFFECT_NUM > 34
  ,{&Move_Left_Laser, H_MODE, 1
#if QT_EN
   ,"������" 
#endif    
  } //������
#endif
#if IN_SPEC_EFFECT_NUM > 35
  ,{&Move_Right_Laser, H_MODE, 1
#if QT_EN
   ,"������" 
#endif    
  } //������
#endif
#if IN_SPEC_EFFECT_NUM > 36
  ,{&Move_Up_Laser, V_MODE, 1
#if QT_EN
   ,"������" 
#endif    
  } //������
#endif
#if IN_SPEC_EFFECT_NUM > 37
  ,{&Move_Down_Laser, V_MODE, 1
#if QT_EN
   ,"������" 
#endif    
  } //������
#endif
#if IN_SPEC_EFFECT_NUM > 38
  ,{&Move_Left_Tensile, H_MODE, 0.5
#if QT_EN
   ,"������"
#endif    
  }//������
#endif
#if IN_SPEC_EFFECT_NUM > 39
  //{&Move_Right_Tensile}//������
  ,{&Move_Up_Tensile, V_MODE, 0.5
#if QT_EN
   ,"������"
#endif    
  }//������
#endif
#if IN_SPEC_EFFECT_NUM > 40
  //{&Move_Down_Tensile}//������
  ,{&Move_Vertical_Tensile, V_MODE, 0.5
#if QT_EN
   ,"��ֱ����" 
#endif    
  }//��ֱ����
#endif
#if IN_SPEC_EFFECT_NUM > 41
  ,{&Move_Horizontal_Tensile, H_MODE, 0.5
#if QT_EN
   ,"ˮƽ����" 
#endif    
  }//ˮƽ����
#endif

#if IN_SPEC_EFFECT_NUM > 42
  ,{&Move_Horizontal_Window, FIX_MODE, 100
#if QT_EN
   ,"ˮƽ��Ҷ��" 
#endif    
  }//WIN_LEAF_WIDTH} //ˮƽ��Ҷ��
#endif
#if IN_SPEC_EFFECT_NUM > 43
  ,{&Move_Vertical_Window, FIX_MODE, 100
#if QT_EN
   ,"��ֱ��Ҷ��" 
#endif    
  }//WIN_LEAF_WIDTH} //��ֱ��Ҷ��
#endif

#if IN_SPEC_EFFECT_NUM > 44
  ,{&Move_Fade_In, FIX_MODE, 100
#if QT_EN
   ,"����" 
#endif    
  }//����
#endif
#if IN_SPEC_EFFECT_NUM > 45
  ,{&Move_Left_Up_In, HV_SQRT_MODE, 1
#if QT_EN
   ,"��������"
#endif
  }//��������
#endif

#if IN_SPEC_EFFECT_NUM > 46
  ,{&Move_Right_Up_In, HV_SQRT_MODE, 1
#if QT_EN
   ,"��������"
#endif
  }//��������
#endif

#if IN_SPEC_EFFECT_NUM > 47
  ,{&Move_Left_Down_In, HV_SQRT_MODE, 1
#if QT_EN
   ,"��������"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 48
  ,{&Mofe_Right_Down_In, HV_SQRT_MODE, 1
#if QT_EN
   ,"��������"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 49
  ,{&Move_Left_Compress_0, H_MODE, 2/STRETCH_RATIO
#if QT_EN
   ,"��ʸ��ѹ��"
#endif
  }//��������
#endif

#if IN_SPEC_EFFECT_NUM > 50
  ,{&Move_Right_Compress_0, H_MODE, 2/STRETCH_RATIO
#if QT_EN
   ,"��ʸ��ѹ��"
#endif
  }//��������
#endif

#if IN_SPEC_EFFECT_NUM > 51
  ,{&Move_Up_Compress_0, V_MODE, 2/STRETCH_RATIO
#if QT_EN
   ,"��ʸ��ѹ��"
#endif
  }//��������
#endif

#if IN_SPEC_EFFECT_NUM > 52
  ,{&Move_Down_Compress_0, V_MODE, 2/STRETCH_RATIO
#if QT_EN
   ,"��ʸ��ѹ��"
#endif
  }//��������
#endif

#if IN_SPEC_EFFECT_NUM > 53
  ,{&Move_Left_Compress_1, H_MODE, 2/STRETCH_RATIO
#if QT_EN
   ,"���ɢѹ��"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 54
  ,{&Move_Right_Compress_1, H_MODE, 2/STRETCH_RATIO
#if QT_EN
   ,"�ҷ�ɢѹ��"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 55
  ,{&Move_Up_Compress_1, V_MODE, 2/STRETCH_RATIO
#if QT_EN
   ,"�Ϸ�ɢѹ��"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 56
  ,{&Move_Down_Compress_1, V_MODE, 2/STRETCH_RATIO
#if QT_EN
   ,"�·�ɢѹ��"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM >57
  ,{&Move_Left_Compress, FIX_MODE, 100
#if QT_EN
   ,"�������ѹ��"
#endif    
  } //����ѹ��
#endif
#if IN_SPEC_EFFECT_NUM > 58
  ,{&Move_Up_Compress, FIX_MODE, 100
#if QT_EN
   ,"���ϱ���ѹ��"
#endif    
  }//����ѹ��
#endif

#if IN_SPEC_EFFECT_NUM > 59
  ,{&Move_Diamond_0, HV_ADD_MODE, 0.5
#if QT_EN
   ,"����չ��"
#endif
  } //���Ƶ���
#endif

#if IN_SPEC_EFFECT_NUM > 60
  ,{&Move_Diamond, HV_ADD_MODE, 0.5
#if QT_EN
   ,"��������"
#endif
  } //���Ƶ���
#endif

#if IN_SPEC_EFFECT_NUM > 61
  ,{&Move_Rect_Open, HV_SQRT_MODE, 0.5
#if QT_EN
   ,"����չ��"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 62
  ,{&Move_Rect_Close, HV_SQRT_MODE, 0.5
#if QT_EN
   ,"��������"
#endif
   }
#endif

#if IN_SPEC_EFFECT_NUM > 63
  ,{&Move_Up_Sector, HHV_ADD_MODE, 1
#if QT_EN
   ,"������չ��"
#endif
  } //���Ƶ���
#endif

#if IN_SPEC_EFFECT_NUM > 64
  ,{&Move_Down_Sector, HHV_ADD_MODE, 1
#if QT_EN
   ,"������չ��"
#endif
  } //���Ƶ���
#endif

#if IN_SPEC_EFFECT_NUM > 65
  ,{&Move_Up_Sector_Merge, HHV_ADD_MODE, 1
#if QT_EN
   ,"�����κϲ�"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 66
  ,{&Move_Down_Sector_Merge, HHV_ADD_MODE, 1
#if QT_EN
   ,"�����κϲ�"
#endif
   }
#endif

#if IN_SPEC_EFFECT_NUM > 67
  ,{&Move_Left_Sector, HVH_ADD_MODE, 1
#if QT_EN
   ,"������չ��"
#endif
  } //���Ƶ���
#endif

#if IN_SPEC_EFFECT_NUM > 68
  ,{&Move_Right_Sector, HVH_ADD_MODE, 1
#if QT_EN
   ,"������չ��"
#endif
  } //���Ƶ���
#endif

#if IN_SPEC_EFFECT_NUM > 69
  ,{&Move_Left_Sector_Merge, HVH_ADD_MODE, 1
#if QT_EN
   ,"�����ߺϲ�"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 70
  ,{&Move_Right_Sector_Merge, HVH_ADD_MODE, 1
#if QT_EN
   ,"�����ߺϲ�"
#endif
   }
#endif

#if IN_SPEC_EFFECT_NUM > 71
  ,{&Move_Left_Up_SpotLignt, TVH_ADD_MODE, 1
#if QT_EN
   ,"�������"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 72
  ,{&Move_Right_Up_SpotLignt, TVH_ADD_MODE, 1
#if QT_EN
   ,"�������"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 73
  ,{&Move_Left_Down_SpotLignt, THV_ADD_MODE, 1
#if QT_EN
   ,"�������"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 74
  ,{&Move_Right_Down_SpotLignt, THV_ADD_MODE, 1
#if QT_EN
   ,"�������"
#endif
   }
#endif

#if IN_SPEC_EFFECT_NUM > 75
  ,{&Move_Left_Right_Cross_Open, H_MODE, 0.5
#if QT_EN
   ,"���ҽ�����Ļ"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 76
  ,{&Move_Up_Down_Cross_Open, V_MODE, 0.5
#if QT_EN
   ,"���½�����Ļ"
#endif
   }
#endif

#if IN_SPEC_EFFECT_NUM > 77
  ,{&Move_LR_Mid_Overflow, H_MODE, 0.5
#if QT_EN
   ,"�����м����"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 78
  ,{&Move_UD_Mid_Overflow, V_MODE, 0.5
#if QT_EN
   ,"�����м����"
#endif
   }
#endif

#if IN_SPEC_EFFECT_NUM > 79
  ,{&Move_LR_Mid_In, H_MODE, 0.5
#if QT_EN
   ,"��������"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 80
  ,{&Move_UD_Mid_In, V_MODE, 0.5
#if QT_EN
   ,"��������"
#endif
   }
#endif

#if IN_SPEC_EFFECT_NUM > 81
  ,{&Move_Spin_CW_Windmill, HV_ADD_MODE, 0.5
#if QT_EN
   ,"˳ʱ��糵"
#endif
  }
#endif

#if IN_SPEC_EFFECT_NUM > 82
  ,{&Move_Spin_CCW_Windmill, HV_ADD_MODE, 0.5
#if QT_EN
   ,"��ʱ��糵"
#endif
   }
#endif

#if IN_SPEC_EFFECT_NUM > 83
  ,{&Move_Left_Stretch, H_MODE, 1
#if QT_EN
   ,"���Ƶ���" 
#endif    
  } //���Ƶ���
#endif

#if IN_SPEC_EFFECT_NUM > 84
  ,{&Move_Up_Stretch, V_MODE, 1
#if QT_EN
   ,"���Ƶ���" 
#endif    
  } //���Ƶ���
#endif

#if IN_SPEC_EFFECT_NUM > 85
  ,{&Move_Jump_Stretch, V_MODE, 1
#if QT_EN
   ,"���ڵ���"
#endif
  } //���Ƶ���
#endif
};

//�����Ƴ���ʽ
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
  ,{&Move_Left_Continuous, H_MODE, 1
#if QT_EN
   ,"����" 
#endif    
  }//0
#endif
#if OUT_SPEC_EFFECT_NUM > 2  
  ,{&Move_Right_Continuous, H_MODE, 1
#if QT_EN
   ,"����" 
#endif    
  }//1
#endif
#if OUT_SPEC_EFFECT_NUM > 3  
  ,{&Move_Up_Continuous, V_MODE, 1
#if QT_EN
   ,"����" 
#endif    
  }//2
#endif
#if OUT_SPEC_EFFECT_NUM >4  
  ,{&Move_Down_Continuous, V_MODE, 1
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
   ,"����б�߸���"
#endif    
  }//8
#endif
#if OUT_SPEC_EFFECT_NUM > 10  
  ,{&Move_Right_Up_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"����б�߸���"
#endif    
  }//9
#endif
#if OUT_SPEC_EFFECT_NUM > 11  
  ,{&Move_Left_Down_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"����б�߸���"
#endif    
  }//10
#endif
#if OUT_SPEC_EFFECT_NUM > 12  
  ,{&Move_Right_Down_Cover, HV_ADD_MODE, 1
#if QT_EN
   ,"����б�߸���"
#endif
  }//11
#endif

#if OUT_SPEC_EFFECT_NUM > 13
  ,{&Move_Left_Up_Cover0, HV_MAX_MODE, 1
#if QT_EN
   ,"����ֱ�Ǹ���"
#endif
  }//����ֱ�Ǹ���
#endif

#if OUT_SPEC_EFFECT_NUM > 14
  ,{&Move_Right_Up_Cover0, HV_MAX_MODE, 1
#if QT_EN
   ,"����ֱ�Ǹ���"
#endif
  }//����ֱ�Ǹ���
#endif

#if OUT_SPEC_EFFECT_NUM > 15
  ,{&Move_Left_Down_Cover0, HV_MAX_MODE, 1
#if QT_EN
   ,"����ֱ�Ǹ���"
#endif
  }//����ֱ�Ǹ���
#endif

#if OUT_SPEC_EFFECT_NUM > 16
  ,{&Move_Right_Down_Cover0, HV_MAX_MODE, 1
#if QT_EN
   ,"����ֱ�Ǹ���"
#endif
  }//����ֱ�Ǹ���
#endif

#if OUT_SPEC_EFFECT_NUM > 17
  ,{&Move_Left_Right_Open, H_MODE, 1
#if QT_EN
   ,"���ҿ���" 
#endif    
  }//12
#endif
#if OUT_SPEC_EFFECT_NUM > 18
  ,{&Move_Up_Down_Open, V_MODE, 1
#if QT_EN
   ,"���¿���" 
#endif    
  }//13
#endif
#if OUT_SPEC_EFFECT_NUM > 19
  ,{&Move_Left_Right_Close, H_MODE, 1
#if QT_EN
   ,"���Һ���" 
#endif    
  }//14
#endif
#if OUT_SPEC_EFFECT_NUM > 20
  ,{&Move_Up_Down_Close, V_MODE, 1
#if QT_EN
   ,"���º���" 
#endif    
  }//15
#endif

#if OUT_SPEC_EFFECT_NUM > 21
  ,{&Move_Left_Right_Reel_Close, H_MODE, 1
#if QT_EN
   ,"���Ҿ���"
#endif
  }//12
#endif

#if OUT_SPEC_EFFECT_NUM > 22
  ,{&Move_Up_Down_Reel_Close, V_MODE, 1
#if QT_EN
   ,"���¾���"
#endif
  }//12
#endif

#if OUT_SPEC_EFFECT_NUM > 23
  ,{&Move_Spin_CW, HV_ADD_MODE, 1
#if QT_EN
   ,"˳ʱ�븲��" 
#endif    
  }
#endif
#if OUT_SPEC_EFFECT_NUM > 24
  ,{&Move_Spin_CCW, HV_ADD_MODE, 1
#if QT_EN
   ,"��ʱ�븲��" 
#endif    
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 25
  ,{&Move_Fade_In, FIX_MODE, 100
#if QT_EN
   ,"����" 
#endif
   }
#endif

#if OUT_SPEC_EFFECT_NUM > 26
  ,{&Move_Diamond_0, HV_ADD_MODE, 0.5
#if QT_EN
   ,"����չ��"
#endif
   }
#endif

#if OUT_SPEC_EFFECT_NUM > 27
  ,{&Move_Diamond, HV_ADD_MODE, 0.5
#if QT_EN
   ,"��������"
#endif
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 28
  ,{&Move_Rect_Open, HV_SQRT_MODE, 0.5
#if QT_EN
   ,"����չ��"
#endif
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 29
  ,{&Move_Rect_Close, HV_SQRT_MODE, 0.5
#if QT_EN
   ,"��������"
#endif
   }
#endif

#if OUT_SPEC_EFFECT_NUM > 30
  ,{&Move_Up_Sector, HHV_ADD_MODE, 1
#if QT_EN
   ,"������չ��"
#endif
  } //���Ƶ���
#endif

#if OUT_SPEC_EFFECT_NUM > 31
  ,{&Move_Down_Sector, HHV_ADD_MODE, 1
#if QT_EN
   ,"������չ��"
#endif
  } //���Ƶ���
#endif

#if OUT_SPEC_EFFECT_NUM > 32
  ,{&Move_Up_Sector_Merge, HHV_ADD_MODE, 1
#if QT_EN
   ,"�����κϲ�"
#endif
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 33
  ,{&Move_Down_Sector_Merge, HHV_ADD_MODE, 1
#if QT_EN
   ,"�����κϲ�"
#endif
   }
#endif

#if OUT_SPEC_EFFECT_NUM > 34
  ,{&Move_Left_Sector, HVH_ADD_MODE, 1
#if QT_EN
   ,"������չ��"
#endif
  } //���Ƶ���
#endif

#if OUT_SPEC_EFFECT_NUM > 35
  ,{&Move_Right_Sector, HVH_ADD_MODE, 1
#if QT_EN
   ,"������չ��"
#endif
  } //���Ƶ���
#endif

#if OUT_SPEC_EFFECT_NUM > 36
  ,{&Move_Left_Sector_Merge, HVH_ADD_MODE, 1
#if QT_EN
   ,"�����ߺϲ�"
#endif
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 37
  ,{&Move_Right_Sector_Merge, HVH_ADD_MODE, 1
#if QT_EN
   ,"�����ߺϲ�"
#endif
   }
#endif

#if OUT_SPEC_EFFECT_NUM > 38
  ,{&Move_Left_Up_SpotLignt, TVH_ADD_MODE, 1
#if QT_EN
   ,"�������"
#endif
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 39
  ,{&Move_Right_Up_SpotLignt, TVH_ADD_MODE, 1
#if QT_EN
   ,"�������"
#endif
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 40
  ,{&Move_Left_Down_SpotLignt, THV_ADD_MODE, 1
#if QT_EN
   ,"�������"
#endif
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 41
  ,{&Move_Right_Down_SpotLignt, THV_ADD_MODE, 1
#if QT_EN
   ,"�������"
#endif
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 42
  ,{&Move_Left_Right_Cross_Open, H_MODE, 0.5
#if QT_EN
   ,"���ҽ�����Ļ"
#endif
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 43
  ,{&Move_Up_Down_Cross_Open, V_MODE, 0.5
#if QT_EN
   ,"���½�����Ļ"
#endif
   }
#endif

#if OUT_SPEC_EFFECT_NUM > 44
  ,{&Move_Spin_CW_Windmill, HV_ADD_MODE, 0.5
#if QT_EN
   ,"˳ʱ��糵"
#endif
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 45
  ,{&Move_Spin_CCW_Windmill, HV_ADD_MODE, 0.5
#if QT_EN
   ,"��ʱ��糵"
#endif
   }
#endif

#if OUT_SPEC_EFFECT_NUM > 46
  ,{&Move_LR_Mid_Out, H_MODE, 0.5
#if QT_EN
   ,"�����м��Ƴ�"
#endif
  }
#endif

#if OUT_SPEC_EFFECT_NUM > 47
  ,{&Move_UD_Mid_Out, V_MODE, 0.5
#if QT_EN
   ,"�����м��Ƴ�"
#endif
   }
#endif

};

void Calc_Screen_Color_Num(void)
{
  Screen_Status.Color_Num = Get_Screen_Color_Num();
/*
  if(Screen_Para.Base_Para.Color < 3 || Screen_Para.Base_Para.Color EQ 4)
  {
    Screen_Status.Color_Num = 1;
  } 
  else if(Screen_Para.Base_Para.Color EQ 3 || Screen_Para.Base_Para.Color EQ 5 || Screen_Para.Base_Para.Color EQ 6) //˫ɫ��)
  {
    Screen_Status.Color_Num = 2;
  }
  else if(Screen_Para.Base_Para.Color EQ 7)
  {
	Screen_Status.Color_Num = 3;
  }
  else
  {
	ASSERT_FAILED();
	Screen_Status.Color_Num = 1;
  }
  */ 
}

INT16U Get_Max_Step(INT16U Width, INT16U Height, const S_Mode_Func *pMode)
{
    float Re = 0;
    INT16U Re0 = 0;
/*
    if(In_Mode >= S_NUM(In_Mode_Func))
    {
       ASSERT_FAILED();
       In_Mode = 0;
    }
*/
    switch(pMode -> Step_Mode)
    {
    case H_MODE:
        Re = (Width*(pMode -> Fac));
        break;
    case V_MODE:
        Re = (Height*(pMode -> Fac));
        break;
    case HV_ADD_MODE:
        Re = ((Width + Height)*(pMode -> Fac));
        break;
    case HV_SQRT_MODE:
        Re = (Sqrt(Width*Width + Height*Height)*(pMode -> Fac));
        break;
    case FIX_MODE:
        Re = pMode -> Fac;
        break;
    case HV_MAX_MODE:
        Re = (Width > Height?Width:Height)*(pMode -> Fac);
        break;
    case HHV_ADD_MODE:
        Re = (float)Width / 2 + Height;
        break;
    case HVH_ADD_MODE:
        Re = (float)Height / 2 + Width;
        break;
    case THV_ADD_MODE:
        Re = Width * 2 + Height;
        break;
    case TVH_ADD_MODE:
        Re = Height * 2 + Width;
        break;
    default:
        Re = 100;
        break;
    }

    Re0 = (INT16U)(Re * 10);

    if(Re0 % 10)
      return (Re0 + 10) / 10;
    else
      return Re0 / 10;

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

void Set_Area_Border_Out(INT8U Area_No)
{
    INT8U Border_Height;

  if(Prog_Status.File_Para[Area_No].Pic_Para.Border_Check)
    {
      Border_Height = Get_Area_Border_Height(Area_No);//Get_Simple_Border_Height(Prog_Status.File_Para[Area_No].Pic_Para.Border_Type);
      Prog_Para.Area[Area_No].X +=Border_Height;
      Prog_Para.Area[Area_No].Y +=Border_Height;
      Prog_Para.Area[Area_No].X_Len -=2*Border_Height;
      Prog_Para.Area[Area_No].Y_Len -=2*Border_Height;
  }
}

void Set_Area_Border_In(INT8U Area_No)
{
     INT8U Border_Height;

    if(Prog_Status.File_Para[Area_No].Pic_Para.Border_Check)
      {
        Border_Height = Get_Area_Border_Height(Area_No);//Get_Simple_Border_Height(Prog_Status.File_Para[Area_No].Pic_Para.Border_Type);
        Prog_Para.Area[Area_No].X -=Border_Height;
        Prog_Para.Area[Area_No].Y -=Border_Height;
        Prog_Para.Area[Area_No].X_Len +=2*Border_Height;
        Prog_Para.Area[Area_No].Y_Len +=2*Border_Height;
    }
}

//������ʾ�����Ľ����˳�ģʽ���Լ���󲽽���
void Calc_Show_Mode_Step(INT8U Area_No)
{
    INT8U In_Mode, Out_Mode;

    In_Mode = Prog_Status.File_Para[Area_No].Pic_Para.In_Mode;
    //In_Mode == 0���,1������ʾ,2��������
    if(In_Mode EQ 0) //���
	{
        In_Mode = rand()%S_NUM(In_Mode_Func);//Cur_Time.Time[T_SEC] % S_NUM(In_Mode_Func);
        if(In_Mode >= 1 && In_Mode <= 2) //�������������ƺ�������Ϊ�����ʽ����Ϊ1����ʾ�����������ۡ�2����Ϊ�����ʽ��Ҫ���������ݲ����㴦��
		  In_Mode += 2;
	}
    else
        In_Mode = In_Mode - 1;

    Prog_Status.Area_Status[Area_No].In_Mode = In_Mode;
    Set_Area_Border_Out(Area_No);
    Prog_Status.Area_Status[Area_No].In_Max_Step = Get_Max_Step(Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len, &In_Mode_Func[In_Mode]);
    Set_Area_Border_In(Area_No);

    Out_Mode = Prog_Status.File_Para[Area_No].Pic_Para.Out_Mode;

    if(Out_Mode EQ 0) //0���,1������,2��������,3����...
       Out_Mode = rand()%(S_NUM(Out_Mode_Func) + 1);//Cur_Time.Time[T_SEC] % S_NUM(Out_Mode_Func);
    else if(Out_Mode EQ 1)
       Out_Mode = 0; //����Ϊ0������
    else if(Out_Mode >= 2) //����������ʽ
       Out_Mode = Out_Mode - 1;

    //0���壬1-N����������ʽ...
    Prog_Status.Area_Status[Area_No].Out_Mode = Out_Mode; //��ʱ0��ʾ������,1-N��ʾ������ʽ

        Set_Area_Border_Out(Area_No);
    if(Out_Mode >= 1)
      Prog_Status.Area_Status[Area_No].Out_Max_Step = Get_Max_Step(Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len, &Out_Mode_Func[Out_Mode - 1]);
    else //������
      Prog_Status.Area_Status[Area_No].Out_Max_Step = 100;//Get_Out_Max_Step(Prog_Para.Area[Area_No].X_Len, Prog_Para.Area[Area_No].Y_Len, Out_Mode - 1);
    Set_Area_Border_In(Area_No);
}

 INT8U Chk_File_Play_Status(INT8U Area_No)
 {
  if(Prog_Status.Play_Status.New_Prog_Flag ||\
     Prog_Status.Area_Status[Area_No].New_File_Flag ||\
     Prog_Status.Area_Status[Area_No].New_SCN_Flag ||\
     Prog_Status.Area_Status[Area_No].New_CStep_Flag) //�ý�Ŀ��÷�����û�н��벥��״̬?
    return 0;
   else
    return 1;
 }

//����ÿ�β����Ĳ���ֵ
INT16U Calc_Move_Step(void)
{
  //INT32U Size;

  return 1;
  //Size = Screen_Para.Base_Para.Width * Screen_Para.Base_Para.Height * GET_COLOR_NUM(Screen_Para.Base_Para.Color)/8;
  //return Size / 2048 + 1;
}

void Update_Pic_Data(INT8U Area_No)
{
  //INT8U i;
  INT8U In_Mode, Out_Mode;
  INT16U Area_Width, Area_Height;
  INT32U Stay_Time,In_Delay, Out_Delay, Step;// Size;
  //INT32U In_Step_Bak;
  //INT32U Out_Time;
  S_Point P0;
  //static S_Int8U Sec ={CHK_BYTE, 0xFF, {0}, CHK_BYTE};
  
  TRACE();
  //qDebug("update area %d, step = %d, max step = %d", Area_No, Prog_Status.Area_Status[Area_No].Step, Prog_Status.Area_Status[Area_No].Max_Step);

  if(Chk_File_Play_Status(Area_No) EQ 0)
    return;
  
  Stay_Time = Get_File_Stay_Time(Area_No);

  //Size = Screen_Para.Base_Para.Width * Screen_Para.Base_Para.Height * GET_COLOR_NUM(Screen_Para.Base_Para.Color)/8;
  //MOVE_STEP = Calc_Move_Step();//Size / 8192 + 1;
  //�����ƶ�״̬
  if(Prog_Status.Area_Status[Area_No].In_Step < Prog_Status.Area_Status[Area_No].In_Max_Step)
  {
      In_Delay = Get_Area_In_Step_Delay(Area_No);
        //��һ��
      if(Prog_Status.Area_Status[Area_No].Step_Timer EQ 0 &&\
         Prog_Status.Area_Status[Area_No].In_Step EQ 0)
        {
          //Prog_Status.Area_Status[Area_No].Step_Timer = In_Delay;///---������һ��ֱ����ʾ��һ�εĲ���Ч��

          //Prog_Status.Area_Status[Area_No].In_Mode = In_Mode;
          //---------
		  Calc_Show_Mode_Step(Area_No);

          if(Check_XXX_Data(Prog_Status.File_Para[Area_No].Pic_Para.Flag))
          {
            Set_Area_Border_Out(Area_No);
            Update_XXX_Data(&Show_Data_Bak, Area_No);
            Set_Area_Border_In(Area_No);
          }
      }


      if(Prog_Status.Area_Status[Area_No].Step_Timer < In_Delay)
        Prog_Status.Area_Status[Area_No].Step_Timer += MOVE_STEP_PERIOD;

      if(Prog_Status.Area_Status[Area_No].Step_Timer >= In_Delay)
      {
        Prog_Status.Area_Status[Area_No].Step_Timer = 0;

		//if(Prog_Status.Area_Status[Area_No].In_Step + MOVE_STEP > Prog_Status.Area_Status[Area_No].In_Max_Step) 
		  //MOVE_STEP = Prog_Status.Area_Status[Area_No].In_Max_Step - Prog_Status.Area_Status[Area_No].In_Step;
        
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

        //�Ƿ���������?
        if(Chk_Pic_Continuous_Move(Area_No))
        {
            Prog_Status.Area_Status[Area_No].New_CStep_Flag = NEW_FLAG;
            SET_SUM(Prog_Status.Area_Status[Area_No]);
        }

        Set_Area_Border_Out(Area_No);
		//STOP_SCAN_TIMER();
        (*(In_Mode_Func[In_Mode].Func))(Area_No);//ִ���ƶ�����
		//START_SCAN_TIMER();
        Set_Area_Border_In(Area_No);

        TRACE();

        if(In_Mode EQ 0) //������ʾ
          Prog_Status.Area_Status[Area_No].In_Step = Prog_Status.Area_Status[Area_No].In_Max_Step;

        //����׶�����ﵽMAX_STEP_NUM%ͬʱͣ��ʱ��Ϊ0��ֱ�������˳��׶�
        if(Prog_Status.Area_Status[Area_No].In_Step >= Prog_Status.Area_Status[Area_No].In_Max_Step)
        {
          //if(Stay_Time EQ 0) //����׶����꣬���ͣ��ʱ����0��ֱ�ӽ����˳��׶�!
          {
            Prog_Status.Area_Status[Area_No].Stay_Time = 0;
            Prog_Status.Area_Status[Area_No].Out_Step = 0;
            Prog_Status.Area_Status[Area_No].Step_Timer = 0;

            if(Chk_Pic_Continuous_Move(Area_No)) //�������ƺ�����ֱ�ӽ�������
            {
                Prog_Status.Area_Status[Area_No].In_Step = 0;
                Prog_Status.Area_Status[Area_No].New_CStep_Flag = NEW_FLAG;
                Prog_Status.Area_Status[Area_No].SCN_No ++;
                SET_SUM(Prog_Status.Area_Status[Area_No]);
            }/*
            else if()
            {
                Prog_Status.Area_Status[Area_No].In_Step = 0;
                Prog_Status.Area_Status[Area_No].New_SCN_Flag = NEW_FLAG;
                Prog_Status.Area_Status[Area_No].SCN_No ++;
                SET_SUM(Prog_Status.Area_Status[Area_No]);
            }*/
          }

        }
      }
  }
  else if(Prog_Status.Area_Status[Area_No].Stay_Time < Stay_Time) //ͣ��ʱ��δ��
  {
  
    if(Check_XXX_Data(Prog_Status.File_Para[Area_No].Pic_Para.Flag)) //����
    {
        //�������ʾ���̣���Ҫ��ʱ���±�������Ϊ����ÿ��ᱻ���Ӹ����޸�
        if(Prog_Status.Area_Status[Area_No].Step_Timer EQ 0)
        {
          Prog_Status.Area_Status[Area_No].Step_Timer = Pub_Timer.Ms100;

          if(Prog_Status.File_Para[Area_No].Pic_Para.Flag EQ SHOW_CLOCK)
          {
            Prog_Status.Area_Status[Area_No].New_SCN_Flag = NEW_FLAG;
            Prog_Status.Area_Status[Area_No].SCN_No = 0; //���¸��±���
            Prog_Status.Area_Status[Area_No].Last_SCN_No = 0xFFFF;
            SET_SUM(Prog_Status.Area_Status[Area_No]);
          }

          //return;
        }

        //���̺�ʱ�䡢��ʱ100ms����һ�Σ�������1s����һ��
        if(Prog_Status.File_Para[Area_No].Pic_Para.Flag EQ SHOW_CLOCK ||\
           Prog_Status.File_Para[Area_No].Pic_Para.Flag EQ SHOW_TIME ||\
           Prog_Status.File_Para[Area_No].Pic_Para.Flag EQ SHOW_TIMER)
          Step = 1;
        else
          Step = 10;

        //����XXX���ݣ�������̡��¶ȡ�ʪ�ȡ���ʱ�ȵȵ�
        if(Pub_Timer.Ms100 > Prog_Status.Area_Status[Area_No].Step_Timer + Step)
        {
          Prog_Status.Area_Status[Area_No].Step_Timer = 0;//Pub_Timer.Ms100;

          P0.X = P0.Y = 0;

          Set_Area_Border_Out(Area_No);
          Update_XXX_Data(&Show_Data_Bak, Area_No);
          Area_Width = Get_Area_Width(Area_No);
          Area_Height = Get_Area_Height(Area_No);
          Copy_Filled_Rect(&Show_Data_Bak, Area_No, &P0, Area_Width, Area_Height, &Show_Data, &P0,0); //���Ʊ�������
          Set_Area_Border_In(Area_No);
        }
       }
		//Prog_Status.Area_Status[Area_No].Step_Timer += MOVE_STEP_PERIOD;

        if(Prog_Status.Area_Status[Area_No].Stay_Time EQ 0)
		{
	      Prog_Status.Area_Status[Area_No].Bak_Ms100 = Pub_Timer.Ms100; 
		  Prog_Status.Area_Status[Area_No].Stay_Time = 1;
		}
		else
		{
              Prog_Status.Area_Status[Area_No].Stay_Time = 1 + (Pub_Timer.Ms100 - Prog_Status.Area_Status[Area_No].Bak_Ms100)*100;
		  if(Prog_Status.Area_Status[Area_No].Stay_Time >= Stay_Time)
		  {
		    Prog_Status.Area_Status[Area_No].Step_Timer = 0;
			Prog_Status.Area_Status[Area_No].Out_Step = 0;
		  }
		}
     //Prog_Status.Area_Status[Area_No].Stay_Time += MOVE_STEP_PERIOD;
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
             Set_Area_Border_Out(Area_No);
             Clear_Area_Data(&Show_Data_Bak, Area_No);
             Set_Area_Border_In(Area_No);
           }
           else
           {

             if(Prog_Status.Area_Status[Area_No].SCN_No + 1 >= Prog_Status.File_Para[Area_No].Pic_Para.SNum) //��ǰ�����һ��Ļ
             {
                 Set_Area_Border_Out(Area_No);
                 Clear_Area_Data(&Show_Data_Bak, Area_No);
                 Set_Area_Border_In(Area_No);
             }
             else
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

			  //if(Prog_Status.Area_Status[Area_No].Out_Step + MOVE_STEP > Prog_Status.Area_Status[Area_No].Out_Max_Step) 
			    //MOVE_STEP = Prog_Status.Area_Status[Area_No].Out_Max_Step - Prog_Status.Area_Status[Area_No].Out_Step;
              
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

                Set_Area_Border_Out(Area_No);
                (*(Out_Mode_Func[Out_Mode].Func))(Area_No);//ִ���ƶ�����
                Set_Area_Border_In(Area_No);

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
          //Prog_Status.Area_Status[Area_No].Play_Flag = 0;
          SET_SUM(Prog_Status.Area_Status[Area_No]);

          Prog_Status.Area_Status[Area_No].In_Step = 0;
          Prog_Status.Area_Status[Area_No].Out_Step = 0;
          Prog_Status.Area_Status[Area_No].Step_Timer = 0;
          Prog_Status.Area_Status[Area_No].Stay_Time = 0;
          //Prog_Status.Area_Status[Area_No].Out_Time = 0;

      }
  }
  else
  {
    //ASSERT_FAILED(); 
  }

}
#endif

