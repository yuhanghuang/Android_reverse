LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_CPP_EXTENSION := cpp
LOCAL_MODULE    := Myjni
LOCAL_SRC_FILES := Myjni.cpp
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)
