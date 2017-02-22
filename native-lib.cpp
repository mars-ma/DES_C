#include <jni.h>
#include <string>
#include <android/log.h>
#include "CCrypto.h"

#define LOG_TAG "dev_mars_ndk"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

//DES
#define EQUAL 0
#define bool int
#define false 0
#define true 1

const char PASSWORD[168] = "ABCDEFGH12345678";

extern "C" {
JNIEXPORT jstring JNICALL
Java_dev_mars_utils_DesUtils_desDecrypt(JNIEnv *env, jclass type, jstring jdata) {
    char *data = (char *) env->GetStringUTFChars(jdata, NULL);
    char out[strlen(data)];
    CTripleDesEncryptAlgorithm tripleDesEncryptAlgorithm = CTripleDesEncryptAlgorithm(PASSWORD);
    tripleDesEncryptAlgorithm.Decrypt(data,out);
    return env->NewStringUTF(out);
}

JNIEXPORT jstring JNICALL
Java_dev_mars_utils_DesUtils_desEncrypt(JNIEnv *env, jobject obj, jstring jdata) {
    unsigned char* des_key = (unsigned char*) malloc(8*sizeof(char));
    char* data = (char*) env->GetStringUTFChars(jdata,NULL);
    int data_length = strlen(data);

    int password_length = strlen(PASSWORD);
    int out_length1=(int)(data_length*1.5);
    char out[out_length1];
    CTripleDesEncryptAlgorithm tripleDesEncryptAlgorithm = CTripleDesEncryptAlgorithm(PASSWORD);
    tripleDesEncryptAlgorithm.Encrypt(data,out);
    return env->NewStringUTF( out);
}
}
