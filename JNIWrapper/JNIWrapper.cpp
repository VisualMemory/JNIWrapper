#include <utility>
#include <vector>
#include "JNIWrapper.h"

using namespace std;

#pragma region JVMWrapper
JavaVM* JVMWrapper::jvm = NULL;

JavaVM* JVMWrapper::GetJVM()
{
	if (!jvm && !CreateJVM())
	{
		jvm = NULL;
		return NULL;
	}
	return jvm;
}

void JVMWrapper::DestoryJVM()
{
	jvm->DestroyJavaVM();
}

bool JVMWrapper::CreateJVM()
{
	JavaVMOption options[1];
	options[0].optionString = "-Djava.class=."; //ÉèÖÃclassÄ¿Â¼

	JavaVMInitArgs args;
	args.options = options;
	args.nOptions = 1;
	args.version = JNI_VERSION_1_8; //java°æ±¾

	JNIEnv* env;
	jint status = JNI_CreateJavaVM(&jvm, (void**)&env, &args);
	return status == JNI_OK;
}
#pragma endregion

#pragma region JNIWrapper
JNIEnv* JNIEnvWrapper::env = NULL;
std::unordered_map<std::string, jclass> JNIEnvWrapper::cls;

JNIEnv* JNIEnvWrapper::GetInstance()
{
	if (!env)
	{
		if (JVMWrapper::GetJVM()->AttachCurrentThread((void**)&env, NULL) != JNI_OK)
		{
			env = NULL;
			return NULL;
		}
		if (!InitEnv())
		{
			env = NULL;
			return NULL;
		}
	}
	return env;
}

JNIEnvWrapper::JNIEnvWrapper()
{
}

JNIEnvWrapper::~JNIEnvWrapper()
{
	for (auto &jcls : cls)
	{
		env->DeleteGlobalRef(jcls.second);
		jcls.second = NULL;
	}
}

bool JNIEnvWrapper::InitEnv()
{
	vector<string> clsNames = {}; //find and maintain the classes TODO(read a file)
	for (const auto& clsName : clsNames)
	{
		jclass jcls = env->FindClass(clsName.data());
		if (!jcls)
		{
			return false;
		}
		cls.insert(make_pair(clsName, (jclass)env->NewGlobalRef(jcls)));
	}

	// TODO(add your code if necessary)

	return true;
}

#pragma endregion
