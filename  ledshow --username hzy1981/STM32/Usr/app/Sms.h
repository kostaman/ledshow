#if !defined(__SMS_H__)
#define __SMS_H__

// 用户信息编码方式
#define GSM_7BIT		0
#define GSM_8BIT		4
#define GSM_UCS2		8

// 应答状态
#define GSM_WAIT		0		// 等待，不确定
#define GSM_OK			1		// OK
#define GSM_ERR			-1		// ERROR

#define MSG_PROC_NUM 1

// 短消息参数结构，编码/解码共用
// 其中，字符串以'\0'结尾
typedef struct {
	char ToSCA; //号码格式
	char SCA[20];			// 短消息服务中心号码(SMSC地址)
	char TPA[20];			// 目标号码或回复号码(TP-DA或TP-RA)
	char TP_PID;			// 用户信息协议标识(TP-PID)
	char TP_DCS;			// 用户信息编码方式(TP-DCS)
	char TP_SCTS[20];		// 服务时间戳字符串(TP_SCTS), 接收时用到
	char TP_UD[160];		// 原始用户信息(编码前或解码后的TP-UD)
	int index;			// 短消息序号，在读取时用到
} SM_PARAM;

// 读取应答的缓冲区
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
int gsmDecodePdu(char* pSrc, SM_PARAM* pDst);


int gsmSendMessage(SM_PARAM* pSrc);
int gsmReadMessageList(void);
int gsmDeleteMessage(int index);

int gsmGetResponse(SM_BUFF* pBuff);

int gsmParseMessageList(SM_PARAM* pMsg, SM_BUFF* pBuff);

void SmsProc(void);
#endif // !defined(__SMS_H__)
