
#define CS_BYTES 1
#define ROM_CS_BYTES 2
#define MAX_BORDER_POINTS (40*8)

#define QT_EN 0 //ʹ��QT����

#if QT_EN == 0 //û��ʹ��QT���� ---STM32�Ļ�����
#define ASSERT_EN 1

#define MOVE_STEP_TIMER 10 //�ƶ�����ʱ��,��λΪms
#define MIN_STAY_TIME  10//ÿ����Сͣ��ʱ��,��λΪms
#define MOVE_STEP 1 //ÿ�����ȵ�λ�ƶ������ݰٷֱ� ��λ%

//----���ݲ�ͬ����Ļ��Ӳ������������Ŀ
#define MAX_POINTS (1024*42L) //������--�˴�����ɫ��������������ɫ���ĵ����ڴ˻�����*3
#define MAX_PROG_NUM 10 //����Ŀ��
#define MAX_AREA_NUM 8 //ÿ����Ŀ����������
#define MAX_FILE_NUM 8 //ÿ������������ļ���
#define MAX_BLOCK_NUM  200 //��ʾ���ݿ�Ĵ�С
#define ONE_BLOCK_SIZE 250 //һ����ʾ���ݿ�Ĵ�С
#define MAX_OPEN_CLOSE_TIME 4 //��󿪹ػ�ʱ��
#define MAX_LIGHTNESS_TIME 4 //������ȿ���ʱ��

#define BORDER_SHOW_EN 1 //�߿���ʾʹ��
#define CLOCK_SHOW_EN  1 //ʱ����ʾʹ��
#define PIC_SHOW_EN    1 //ͼ����ʾʹ��
#define LUN_SHOW_EN    1 //ũ����ʾʹ��
#define TEMP_SHOW_EN   1 //�¶���ʾʹ��
#define TIME_SHOW_EN   1 //ʱ����ʾʹ��
#define TIMER_SHOW_EN  1 //��ʱ��ʾʹ�� 

#else
#define ASSERT_EN 1

//��ʾЧ������
#define MOVE_STEP_TIMER 10 //�ƶ�����ʱ��,��λΪms
#define MIN_STAY_TIME  10//ÿ����Сͣ��ʱ��,��λΪms
#define MOVE_STEP 1 //ÿ�����ȵ�λ�ƶ������ݰٷֱ� ��λ%


//----���ݲ�ͬ����Ļ��Ӳ������������Ŀ
#define MAX_POINTS (1024*256L) //������--�˴�����ɫ��������������ɫ���ĵ����ڴ˻�����*3
#define MAX_PROG_NUM 10 //����Ŀ��
#define MAX_AREA_NUM 8 //ÿ����Ŀ����������
#define MAX_FILE_NUM 8 //ÿ������������ļ���
#define MAX_BLOCK_NUM  200
#define ONE_BLOCK_SIZE 250
#define MAX_OPEN_CLOSE_TIME 4 //��󿪹ػ�ʱ��
#define MAX_LIGHTNESS_TIME 4 //������ȿ���ʱ��

#define BORDER_SHOW_EN 1 //�߿���ʾʹ��
#define CLOCK_SHOW_EN  1 //ʱ����ʾʹ��
#define PIC_SHOW_EN    1 //ͼ����ʾʹ��
#define LUN_SHOW_EN    1 //ũ����ʾʹ��
#define TEMP_SHOW_EN   1 //�¶���ʾʹ��
#define TIME_SHOW_EN   1 //ʱ����ʾʹ��
#define TIMER_SHOW_EN  1 //��ʱ��ʾʹ�� 
#endif
