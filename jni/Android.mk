LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := foo
LOCAL_SRC_FILES := foo.cpp
LOCAL_CPP_FEATURES := exceptions
LOCAL_CPPFLAGS += -fopenmp
LOCAL_LDFLAGS += -fopenmp
include $(BUILD_EXECUTABLE)



