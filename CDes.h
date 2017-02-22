const int DES_KEY_SIZE      =  56;
const int DES_DATA_SIZE     =  64;
const int DES_SBUFFER_SIZE  =  48;
const int DES_ROUNDS =  16;

/////////////////////////////////////////////////////////////////////////
///Base64编码的包装类。
/////////////////////////////////////////////////////////////////////////
class CBase64 {
public:
	//返回编码后的ASCII字符串长度。
	int Encode(const unsigned char *pSrc, char *pDst, int nSrcLen, int nMaxLineLen=2000);
	//返回编码后的二进制字符串长度。
	int Decode(const char *pSrc, unsigned char *pDst, int nSrcLen);
};

class triple_des;

/////////////////////////////////////////////////////////////////////////
///des的算法实现；外部仅需调用password()和EncryptBase64()方法。
/////////////////////////////////////////////////////////////////////////
class des
{
private:
	const char *xmix(const char *,
					 unsigned char [DES_DATA_SIZE],
					 const unsigned char [DES_KEY_SIZE]);
	void encrypt_decrypt(unsigned char [DES_DATA_SIZE], int);
	unsigned char compressed_shifted_key[DES_ROUNDS][DES_SBUFFER_SIZE];
	CBase64 base64;

public:
	void initialize(const unsigned char[DES_KEY_SIZE]);
	void password(const char *);
	void encrypt(unsigned char data[DES_DATA_SIZE]) {
		encrypt_decrypt(data, 1);
	}
	void decrypt(unsigned char data[DES_DATA_SIZE]) {
		encrypt_decrypt(data, 0);
	}
	char* encryptbuffer(const char *buff,int size,bool isEncrypt);

public:
	///加解密函数。
	///秘文使用Base64方式编码。
	///@para pSrc	输入：加密则为明文；解密则为Base64编码的秘文。
	///@para pDst	输出：加密则为Base64编码的秘文；解密则为明文。
	///@para nSrcLen	输入数据长度。
	///@para isEncrypt	1为加密，0为解密。
	void EncryptBase64(const char *pSrc, char *pDst, int nSrcLen, bool isEncrypt);

	friend class triple_des;
};

/////////////////////////////////////////////////////////////////////////
///triple des的算法实现；外部仅需调用password()和EncryptBase64()方法。
/////////////////////////////////////////////////////////////////////////
class triple_des
{
private:
	des part[3];
	void encrypt_decrypt(unsigned char [DES_DATA_SIZE], int);
	CBase64 base64;
public:
	void initialize(const unsigned char key[3*DES_KEY_SIZE]) {
		part[0].initialize(key);
		part[1].initialize(key + DES_KEY_SIZE);
		part[2].initialize(key + 2*DES_KEY_SIZE);
	}
	void password(const char *);
	void encrypt(unsigned char data[DES_DATA_SIZE]) {
		part[0].encrypt(data);
		part[1].decrypt(data);
		part[2].encrypt(data);
	}
	void decrypt(unsigned char data[DES_DATA_SIZE]) {
		part[2].decrypt(data);
		part[1].encrypt(data);
		part[0].decrypt(data);
	}
public:
	char* encryptbuffer(const char *buff,int size,bool isEncrypt);
	///加解密函数。
	///秘文使用Base64方式编码。
	///@para pSrc	输入：加密则为明文；解密则为Base64编码的秘文。
	///@para pDst	输出：加密则为Base64编码的秘文；解密则为明文。
	///@para nSrcLen	输入数据长度。
	///@para isEncrypt	1为加密，0为解密。
	void EncryptBase64(const char *pSrc, char *pDst, int nSrcLen, bool isEncrypt);
};

