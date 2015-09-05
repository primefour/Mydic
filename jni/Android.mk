LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := src/com_Dict_DictApp2_DictSearchEngine.cpp \
	src/GoldenHtmlHeader.cpp \
	src/GoldenZipTool.cpp \
	src/GoldenIConvTool.cpp \
	src/GoldenDictManager.cpp \
	src/GoldenGzipHeaderParser.cpp \
	src/GoldenGzipinflate.cpp \
	src/GoldenStandardIO.cpp \
	src/GoldenWordIndexItem.cpp \
	src/StardictDict.cpp \
	src/StardictIdx.cpp \
	src/StardictInfo.cpp \
	src/StardictManager.cpp \
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

LOCAL_STATIC_LIBRARIES += libiconv.a
LOCAL_STATIC_LIBRARIES += libzip.a

LOCAL_LDLIBS := -L./lib/ -llog -liconv -lzip

LOCAL_CFLAGS += -g -DANDROID_PLATFORM -fexceptions 


include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_EXECUTABLE)
