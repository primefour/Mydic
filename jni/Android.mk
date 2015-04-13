LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := src/com_Dict_DictApp2_DictSearchEngine.cpp \
	src/GzipDeflate.cpp \
	src/GzipHeaderParser.cpp \
	src/StandardIO.cpp \
	src/Stardict.cpp \
	src/StardictDict.cpp \
	src/StardictIdx.cpp \
	src/StardictInfo.cpp \
	src/StardictMain.cpp \
	src/StardictSyn.cpp \
	src/String8.cpp \
	src/Unicode.cpp

LOCAL_MODULE := searchEngine

LOCAL_C_INCLUDES += ./include/

LOCAL_LDFLAGS := -L ./lib/

LOCAL_CFLAGS := -lz 

#LOCAL_STATIC_LIBRARIES := libz

LOCAL_LILIBS := -llog -lz

include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_EXECUTABLE)
