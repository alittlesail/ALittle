#ifndef CARP_PLATFORM_INCLUDED
#define CARP_PLATFORM_INCLUDED

#define SOKOL_IMPL
#define SOKOL_D3D11
#include "sokol/sokol_app.h"
#include "klib/kstring.h"

typedef struct
{
	kstring_t base_path;
} _platform_t;
static _platform_t _platform = {0};

#if defined(_SAPP_ANDROID)
JNIEnv* carp_android_get_jni()
{
	ANativeActivity* activity = (ANativeActivity*)sapp_android_get_native_activity();
	if (!activity)
	{
		SOKOL_LOG("sapp_android_get_native_activity failed!");
		return 0;
	}
	JNIEnv* env = 0;
	int status = activity->vm->AttachCurrentThread(&activity->vm, &env, NULL);
	if (status < 0 || env == 0)
	{
		SOKOL_LOG("Failed to attach current thread (err=%d or env=0)", status);
		return 0;
	}
	return env;
}
#endif


const char* carp_platform_base_path()
{
	if (ks_str(&_platform.base_path) == 0) kputs("", &_platform.base_path);
	if (ks_len(&_platform.base_path) > 0) return ks_str(&_platform.base_path);
	
#if defined(_SAPP_ANDROID)
	JNIEnv* env = carp_android_get_jni();
	if (!env) return ks_str(&_platform.base_path);
    JNIEnv* env = 0;
    int status = activity->vm->AttachCurrentThread(&activity->vm, &env, NULL);
    if (status < 0)
	{
        SOKOL_LOG("Failed to attach current thread (err=%d)", status);
        return 0;
	}
	{
		SOKOL_LOG("Failed to attach current thread (err=%d)", status);
		return 0;
	}
#elif defined(_SAPP_IOS)
#endif
}

#endif