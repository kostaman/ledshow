
#define CS_BYTES 1
#define ROM_CS_BYTES 2
#define MAX_BORDER_POINTS 50

#define QT_EN 1 //ʹ��QT����

#if QT_EN == 0 //û��ʹ��QT���� ---STM32�Ļ�����
#define ASSERT_EN 1

#define MOVE_STEP_TIMER 10 //�ƶ�����ʱ��,��λΪms
#define MIN_STAY_TIME  10//ÿ����Сͣ��ʱ��,��λΪms
#define MOVE_STEP 1 //ÿ�����ȵ�λ�ƶ������ݰٷֱ� ��λ%

//----���ݲ�ͬ����Ļ��Ӳ������������Ŀ
#define MAX_POINTS (1024*256L) //������
#define MAX_PROG_NUM 10 //����Ŀ��
#define MAX_AREA_NUM 10 //ÿ����Ŀ����������
#define MAX_FILE_NUM 10 //ÿ������������ļ���
#define MAX_BLOCK_NUM  200 //��ʾ���ݿ�Ĵ�С
#define ONE_BLOCK_SIZE 250 //һ����ʾ���ݿ�Ĵ�С
#define MAX_OPEN_CLOSE_TIME 4 //��󿪹ػ�ʱ��
#define MAX_LIGHTNESS_TIME 4 //������ȿ���ʱ��



#else
#define ASSERT_EN 1

//��ʾЧ������
#define MOVE_STEP_TIMER 10 //�ƶ�����ʱ��,��λΪms
#define MIN_STAY_TIME  10//ÿ����Сͣ��ʱ��,��λΪms
#define MOVE_STEP 1 //ÿ�����ȵ�λ�ƶ������ݰٷֱ� ��λ%


//----���ݲ�ͬ����Ļ��Ӳ������������Ŀ
#define MAX_POINTS (1024*256L) //������
#define MAX_PROG_NUM 10 //����Ŀ��
#define MAX_AREA_NUM 10 //ÿ����Ŀ����������
#define MAX_FILE_NUM 10 //ÿ������������ļ���
#define MAX_BLOCK_NUM  200
#define ONE_BLOCK_SIZE 250
#define MAX_OPEN_CLOSE_TIME 4 //��󿪹ػ�ʱ��
#define MAX_LIGHTNESS_TIME 4 //������ȿ���ʱ��

#endif
