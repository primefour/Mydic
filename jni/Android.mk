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
	src/String8.cpp \
	src/Unicode.cpp \
	src/adler32.c \
	src/compress.c \
	src/crc32.c \
	src/deflate.c \
	src/gzclose.c \
	src/gzlib.c \
	src/gzread.c \
	src/gzwrite.c \
	src/infback.c \
	src/inffast.c \
	src/inflate.c \
	src/inftrees.c \
	src/trees.c \
	src/uncompr.c \
	src/zutil.c \

LOCAL_MODULE := searchEngine

LOCAL_C_INCLUDES += ./include/
LOCAL_LDLIBS := -llog
LOCAL_CFLAGS += -g -DANDROID_PLATFORM


include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_EXECUTABLE)
