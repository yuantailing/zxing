LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := qrdecoder
LOCAL_SRC_FILES := wrapper.cpp qrdecoder/qr.cpp qrdecoder/rs.cpp qrdecoder/gf.cpp
LOCAL_CPP_FEATURES += exceptions
LOCAL_CPPFLAGS  := -std=c++17 -O3

include $(BUILD_SHARED_LIBRARY)
