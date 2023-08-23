LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := checklibs

LOCAL_SRC_FILES := main.cpp
LOCAL_CPPFLAGS := -std=c++14
include $(BUILD_SHARED_LIBRARY)
