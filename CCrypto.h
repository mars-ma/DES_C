/////////////////////////////////////////////////////////////////////////
#ifndef CCRYPTO_H
#define CCRYPTO_H
#include "CDes.h"
#include <string>
using namespace std;
/////////////////////////////////////////////////////////////////////////
///IEncryptoAlgorithm为加解密的接口类。需提供加密和解密两个方法。
/////////////////////////////////////////////////////////////////////////
class IEncryptAlgorithm
{
public:
	///构造函数
	IEncryptAlgorithm(){};
	///析构函数
	virtual ~IEncryptAlgorithm(){};

	///加密接口
	///@param	pIn		待加密字符串
	///@param	pOut	加密后字符串
	virtual int Encrypt(char *pIn, char *pOut) = 0;
	///解密接口
	///@param	pIn		待解密字符串
	///@param	pOut	解密后字符串
	virtual int Decrypt(char *pIn, char *pOut) = 0;
};

/////////////////////////////////////////////////////////////////////////
///NoEncryptoAlgorithm为接口类的一个简单实现，用作调试目的，仅将内容平进平出。
/////////////////////////////////////////////////////////////////////////
class NoEncryptAlgorithm:public IEncryptAlgorithm
{
public:
	///析构函数
	virtual ~NoEncryptAlgorithm(){};

	///加密接口
	///@param	pIn		待加密字符串
	///@param	pOut	加密后字符串
	virtual int Encrypt(char *pIn, char *pOut) {
		strcpy(pOut, pIn);
		return 0;
	}
	///解密接口
	///@param	pIn		待解密字符串
	///@param	pOut	解密后字符串
	virtual int Decrypt(char *pIn, char *pOut) {
		strcpy(pOut, pIn);
		return 0;
	}
};

/////////////////////////////////////////////////////////////////////////
///实现Des算法的接口类，需设置加解密用的口令。
/////////////////////////////////////////////////////////////////////////
class CDesEncryptAlgorithm:public IEncryptAlgorithm
{
public:
	///构造函数
	CDesEncryptAlgorithm() {
		m_szPassword[0]=0;
	}
	///带口令的构造函数
	CDesEncryptAlgorithm(const char *szPassword) {
		SetPassword(szPassword);
	}
	///析构函数
	virtual ~CDesEncryptAlgorithm(){};
	///加密接口
	///@param	pIn		待加密字符串
	///@param	pOut	加密后字符串
	virtual int Encrypt(char *pIn, char *pOut) {
		if (m_szPassword[0]==0) {
			strcpy(pOut, pIn);
			return 0;
		}
		crypto.EncryptBase64(pIn, pOut, strlen(pIn), true);
		return 0;
	}
	///解密接口
	///@param	pIn		待解密字符串
	///@param	pOut	解密后字符串
	virtual int Decrypt(char *pIn, char *pOut) {
		if (m_szPassword[0]==0) {
			strcpy(pOut, pIn);
			return 0;
		}
		crypto.EncryptBase64(pIn, pOut, strlen(pIn)-3, false);
		return 0;
	}
	///设置加解密用的口令
	virtual void SetPassword(const char *szPassword) {
		strcpy(m_szPassword, szPassword);
		crypto.password(m_szPassword);
	}
	bool IsEnOrDe(char* item_value){
		if (strstr(item_value,"@#$")){return true;}
		else return false;
	}
private:
	///des算法的具体实现
	des crypto;
	///des算法使用的口令
	char m_szPassword[60];
};

/////////////////////////////////////////////////////////////////////////
///实现TripleDes算法的接口类，需设置加解密用的口令。
/////////////////////////////////////////////////////////////////////////
class CTripleDesEncryptAlgorithm:public IEncryptAlgorithm
{
public:
	///构造函数
	CTripleDesEncryptAlgorithm() {
		m_szPassword[0]=0;
	}
	///带口令的构造函数
	CTripleDesEncryptAlgorithm(const char *szPassword) {
		SetPassword(szPassword);
	}
	///析构函数
	virtual ~CTripleDesEncryptAlgorithm(){};

	///解密接口
	///@param	pIn		待解密字符串
	///@param	pOut	解密后字符串
	virtual int Encrypt(char *pIn, char *pOut) {
		if (m_szPassword[0]==0) {
			strcpy(pOut, pIn);
			return 0;
		}
		crypto.EncryptBase64(pIn, pOut, strlen(pIn), true);
		return 0;
	}
	///解密接口
	///@param	pIn		待解密字符串
	///@param	pOut	解密后字符串
	virtual int Decrypt(char *pIn, char *pOut) {
		if (m_szPassword[0]==0) {
			strcpy(pOut, pIn);
			return 0;
		}
		crypto.EncryptBase64(pIn, pOut, strlen(pIn)-3, false);
		return 0;
	}
	///设置加解密用的口令
	virtual void SetPassword(const char *szPassword) {
		strcpy(m_szPassword, szPassword);
		crypto.password(m_szPassword);
	}
	///判断字符串为密文或者明文，true为密文
	bool IsEnOrDe(string item_value){
		if (item_value.rfind("@#$")==item_value.length()-3){return true;}
		else return false;
	}
private:
	///triple des算法的具体实现
	triple_des crypto;
	///triple des算法使用的口令
	char m_szPassword[60];
};

#endif
