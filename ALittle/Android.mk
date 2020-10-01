LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

LOCAL_CFLAGS += -fexceptions
LOCAL_CFLAGS += -D__STDC_CONSTANT_MACROS
LOCAL_CPPFLAGS += -std=c++11
LOCAL_CPPFLAGS += -frtti

LOCAL_C_INCLUDES += $(LOCAL_PATH)/..
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../SDL/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../lua
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../asio/asio/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../LuaBridge/Source

# Add your application source files here...
LOCAL_SRC_FILES := \
	../lualib/ajson/lua_ajson.c \
	../lualib/cjson/lua_cjson.c \
	../lualib/cjson/fpconv.c \
	../lualib/cjson/strbuf.c \
	../lualib/sqlite3/lsqlite3.c \
	../lualib/sqlite3/sqlite3.c \
	ALittleClient/Main.cpp

LOCAL_SHARED_LIBRARIES := SDL2
LOCAL_STATIC_LIBRARIES := lua
LOCAL_LDLIBS := -lGLESv1_CM -llog -lGLESv2 -lOpenSLES -lz -lm

include $(BUILD_SHARED_LIBRARY)
