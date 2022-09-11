LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := JNITest
LOCAL_SRC_FILES := native-lib.cpp
LOCAL_LDFLAGS += -llog
include $(BUILD_SHARED_LIBRARY)