LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

LOCAL_CFLAGS += -fexceptions
LOCAL_CFLAGS += -D__STDC_CONSTANT_MACROS
LOCAL_CPPFLAGS += -std=c++11

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../SDL

# Add your application source files here...
LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/Helper/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/Protocol/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ScriptSystem/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ScriptSystem/json/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ScriptSystem/lfs/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ScriptSystem/sqlite/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ScriptSystem/sqlite/*.c) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ThirdPart/md5/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ThirdPart/sha1/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ThirdPart/csv/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ThirdPart/base64/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/Tool/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/AudioSystem/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/AudioSystem/bcg729/*.c) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/Helper/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/NetSystem/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/Platform/Android/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/RenderSystem/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/RenderSystem/DisplayObject/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/RenderSystem/Image/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/RenderSystem/Text/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/RenderSystem/TextArea/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/RenderSystem/TextEdit/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/RenderSystem/TextInput/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/RenderSystem/Texture/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ScheduleSystem/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ScriptSystem/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/ThreadSystem/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/LibCommon/Tool/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ALittle/ALittleClient/*.cpp) \
	)

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer SDL2_image SDL2_net SDL2_ttf
LOCAL_STATIC_LIBRARIES := luajit
LOCAL_LDLIBS := -lGLESv1_CM -llog -lGLESv2 -lOpenSLES -lz -lm

include $(BUILD_SHARED_LIBRARY)
