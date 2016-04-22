LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := oxygine-{{project}}_static
LOCAL_MODULE_FILENAME := oxygine-{{project}}

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/../oxygine-framework/oxygine/src/ \
		src/ \
		src/android \
					

LOCAL_SRC_FILES := \
		src/{{project}}.cpp \
		src/android/Android{{Project}}.cpp




LOCAL_EXPORT_C_INCLUDES += \
					$(LOCAL_PATH)/src \
					$(LOCAL_PATH)/src/android \
					
					
include $(BUILD_STATIC_LIBRARY)
