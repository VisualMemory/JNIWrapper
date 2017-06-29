#ifndef JNI_WRAPPER_H_
#define JNI_WRAPPER_H_

#include <string>
#include <unordered_map>
#include "jni.h"

class JVMWrapper
{
public:
	static JavaVM* GetJVM();
	static void DestoryJVM();
private:
	static JavaVM* jvm;
	static bool CreateJVM();
};


class JNIEnvWrapper
{
public:
	JNIEnvWrapper();
	~JNIEnvWrapper();
	JNIEnv* env;
	std::unordered_map<std::string, jclass> cls;
private:	
	bool InitEnv();
};

#endif //!JNI_WRAPPER_H_
