#if !defined(__SMS_H__)
#define __SMS_H__

// �û���Ϣ���뷽ʽ
#define GSM_7BIT		0
#define GSM_8BIT		4
#define GSM_UCS2		8

// Ӧ��״̬
#define GSM_WAIT		0		// �ȴ�����ȷ��
#define GSM_OK			1		// OK
#define GSM_ERR			-1		// ERROR

#define MSG_PROC_NUM 3

// ����Ϣ�����ṹ������/���빲��
// ���У��ַ�����'\0'��β
typedef struct {
	char SCA[16];			// ����Ϣ�������ĺ���(SMSC��ַ)
	char TPA[16];			// Ŀ������ظ�����(TP-DA��TP-RA)
	char TP_PID;			// �û���ϢЭ���ʶ(TP-PID)
	char TP_DCS;			// �û���Ϣ���뷽ʽ(TP-DCS)
	char TP_SCTS[16];		// ����ʱ����ַ���(TP_SCTS), ����ʱ�õ�
	char TP_UD[160];		// ԭʼ�û���Ϣ(����ǰ�������TP-UD)
	int index;			// ����Ϣ��ţ��ڶ�ȡʱ�õ�
} SM_PARAM;

// ��ȡӦ��Ļ�����
typedef struct {
	int len;
	char data[1280];
} SM_BUFF;

typedef struct{
  INT8U Head;
  char Buf[1280*5];
  INT16U WRPosi;
  INT16U RDPosi;
  INT8U Tail;
}S_SMS_GPRS_Rcv_Buf;

EXT S_SMS_GPRS_Rcv_Buf SMS_GPRS_Rcv_Buf;

int gsmBytes2String(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmString2Bytes(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmEncode7bit(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecode7bit(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmEncode8bit(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecode8bit(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmEncodeUcs2(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecodeUcs2(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmInvertNumbers(const char* pSrc, char* pDst, int nSrcLength);
int gsmSerializeNumbers(const char* pSrc, char* pDst, int nSrcLength);
int gsmEncodePdu(const SM_PARAM* pSrc, char* pDst);
int gsmDecodePdu(const char* pSrc, SM_PARAM* pDst);


int gsmSendMessage(SM_PARAM* pSrc);
int gsmReadMessageList(void);
int gsmDeleteMessage(int index);

int gsmGetResponse(SM_BUFF* pBuff);

int gsmParseMessageList(SM_PARAM* pMsg, SM_BUFF* pBuff);

void SmsProc(void);
#endif // !defined(__SMS_H__)
