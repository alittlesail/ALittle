
#ifdef __ANDROID__

#include "AndroidSystem.h"
#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/Tool/MemoryPool.h"

namespace ALittle
{

std::string Android_jstring2stdstring(JNIEnv* env, jstring jstr)  
{  
	std::string rtn;  
	jclass clsstring	=	env->FindClass("java/lang/String"); 
	jstring strencode	=	env->NewStringUTF("utf-8");
	jmethodID mid		=	env->GetMethodID(clsstring,"getBytes", "(Ljava/lang/String;)[B");  
	jbyteArray barr		=	(jbyteArray)env->CallObjectMethod(jstr, mid, strencode); // String .getByte("utf-8"); 
	jbyte* ba			=	env->GetByteArrayElements(barr, JNI_FALSE);
	jsize alen			=	env->GetArrayLength(barr);

	if (ba && alen > 0) rtn.assign((char*)ba, alen);
	env->ReleaseByteArrayElements(barr, ba, 0);  // release memory

	env->DeleteLocalRef(clsstring);
	env->DeleteLocalRef(strencode);
	env->DeleteLocalRef(barr);
	return rtn;
}

jstring Android_stdstring2jstring(JNIEnv* env, const char* str)
{
	if(!env || !str) return 0;
	jstring js = env->NewStringUTF(str);
	return js;
}

int Android_InstallAPK(const char* file_path)
{
	JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	if (jni_env == 0) return 1;

	jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
	jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_InstallAPK", "(Ljava/lang/String;)I");

	jstring j_file_path = Android_stdstring2jstring(jni_env, file_path);
	int result = jni_env->CallStaticIntMethod(login_api, login_func, j_file_path);

	jni_env->DeleteLocalRef(login_api);
	jni_env->DeleteLocalRef(j_file_path);
	return result;
}

int Android_StartAPP(const char* package_name)
{
	JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	if (jni_env == 0) return 1;

	jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
	jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_StartAPP", "(Ljava/lang/String;)I");
	jstring j_package_name = Android_stdstring2jstring(jni_env, package_name);
	int result = jni_env->CallStaticIntMethod(login_api, login_func, j_package_name);

	jni_env->DeleteLocalRef(login_api);
	jni_env->DeleteLocalRef(j_package_name);
	return result;
}

const char* Android_GetNetworkType()
{
	JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	if (jni_env == 0) return "OtherSystem_NotifyNetwork_none";

	jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
	jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_GetNetworkType", "()Ljava/lang/String;");

	jstring result = (jstring)jni_env->CallStaticObjectMethod(login_api, login_func);

	static std::string result_return;
	result_return = Android_jstring2stdstring(jni_env, result);

	jni_env->DeleteLocalRef(login_api);
	jni_env->DeleteLocalRef(result);
	return result_return.c_str();
}

int Android_StartNetworkListener()
{
	JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	if (jni_env == 0) return 1;

	jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
	jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_StartNetworkListener", "()I");

	int result = jni_env->CallStaticIntMethod(login_api, login_func);
	jni_env->DeleteLocalRef(login_api);
	return result;
}

const char* Android_GetDeviceID()
{
	static std::string result_return;
	if (result_return.size()) return result_return.c_str();

	JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	if (jni_env == 0) return "";

	jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
	jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_GetDeviceID", "()Ljava/lang/String;");

	jstring result = (jstring)jni_env->CallStaticObjectMethod(login_api, login_func);

	result_return = Android_jstring2stdstring(jni_env, result);

	jni_env->DeleteLocalRef(login_api);
	jni_env->DeleteLocalRef(result);
	return result_return.c_str();
}

int Android_MoveTaskToBack()
{
	JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	if (jni_env == 0) return 1;

	jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
	jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_MoveTaskToBack", "()I");

	int result = jni_env->CallStaticIntMethod(login_api, login_func);
	jni_env->DeleteLocalRef(login_api);
	return result;
}

int Android_GetScreenWidth()
{
	JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	if (jni_env == 0) return 1;

	jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
	jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_GetScreenWidth", "()I");

	int result = jni_env->CallStaticIntMethod(login_api, login_func);
	jni_env->DeleteLocalRef(login_api);
	return result;
}

int Android_GetScreenHeight()
{
	JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	if (jni_env == 0) return 1;

	jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
	jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_GetScreenHeight", "()I");

	int result = jni_env->CallStaticIntMethod(login_api, login_func);
	jni_env->DeleteLocalRef(login_api);
	return result;
}

int Android_GetStatusBarHeight()
{
	JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	if (jni_env == 0) return 1;

	jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
	jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_GetStatusBarHeight", "()I");

	int result = jni_env->CallStaticIntMethod(login_api, login_func);
	jni_env->DeleteLocalRef(login_api);
	return result;
}

int Android_SystemSelectFile(const char* init_dir)
{
	JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	if (jni_env == 0) return 1;

	jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
	jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_SystemSelectFile", "(Ljava/lang/String;)I");
    jstring j_init_dir;
    if (init_dir)
        j_init_dir = Android_stdstring2jstring(jni_env, init_dir);
    else
        j_init_dir = Android_stdstring2jstring(jni_env, "");
	int result = jni_env->CallStaticIntMethod(login_api, login_func, j_init_dir);

	jni_env->DeleteLocalRef(login_api);
	jni_env->DeleteLocalRef(j_init_dir);
	return result;
}

int Android_SystemSelectFile(const char* init_dir)
{
	g_ScriptSystem.Invoke("__ALITTLEAPI_SystemSaveDirectory");
	return 0;
}

int Android_SystemSaveFile(const char* file_name, const char* init_dir)
{
	g_ScriptSystem.Invoke("__ALITTLEAPI_SystemSaveFile");
	return 0;
}

int Android_OpenUrlBySystemBrowser(const char* url)
{
	JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
	if (jni_env == 0) return 1;

	jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
	jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_OpenUrlBySystemBrowser", "(Ljava/lang/String;)I");
	jstring j_url = Android_stdstring2jstring(jni_env, url);
	int result = jni_env->CallStaticIntMethod(login_api, login_func, j_url);

	jni_env->DeleteLocalRef(login_api);
	jni_env->DeleteLocalRef(j_url);
	return result;
}

SDL_Surface* Android_GetClipboardImage()
{
	return 0;
}

bool Android_HasClipboardImage()
{
	return false;
}

bool Android_SetClipboardImage(SDL_Surface* surface)
{
	return false;
}

} // ALittle

void Java_org_libsdl_app_GlobalFunc_SurfaceResize(JNIEnv * env, jobject obj )
{
	if (g_RenderSystem.GetRender()) g_RenderSystem.m_android_surface_resize = true;
}

void Java_org_libsdl_app_GlobalFunc_J2CLog(JNIEnv * env, jobject obj, jstring content )
{
	CARP_INFO(ALittle::Android_jstring2stdstring(env, content));
}

void Java_org_libsdl_app_GlobalFunc_Invoke(JNIEnv * env, jobject obj, jstring method, jstring content )
{
	std::string str_method = ALittle::Android_jstring2stdstring(env, method);
	std::string str_content = ALittle::Android_jstring2stdstring(env, content);
	
	g_ScheduleSystem.PushExternalEvent(str_method.c_str(), str_method.size(), str_content.c_str(), str_content.size());
}

#endif // __ANDROID__
