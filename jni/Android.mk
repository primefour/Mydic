LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

##LOCAL_INC_FILES := include/AVLTreeTemplate.h \
##	include/BinTreeTemplate.h \
##	include/GzipDeflate.h \
##	include/GzipHeaderParser.h \
##	include/Ref.h \
##	include/StandardIO.h \
##	include/Stardict.h \
##	include/StardictDict.h \
##	include/StardictIdx.h \
##	include/StardictInfo.h \
##	include/StardictSyn.h \
##	include/String8.h \
##	include/Unicode.h \
##	include/com_Dict_DictApp2_DictSearchEngine.h \
##	include/com_Dict_DictApp2_DictSearchEngine_Callbacks.h \
##	include/gzappend.h \
##	include/list.h \
##	include/zconf.h \
##	include/zlib.h \
##	zran.h


LOCAL_SRC_FILES := src/com_Dict_DictApp2_DictSearchEngine.c \
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


LOCAL_PREBUILT_LIBS := libz.a
include $(BUILD_MULTI_PREBUILT)
LOCAL_PATH := $(MY_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := searchEngine

LOCAL_C_INCLUDES = ./include/

LOCAL_STATIC_LIBRARIES := libz

#LOCAL_LILIBS := -llog -lz

#LOCAL_PREBUILT_LIBS := ./lib/libz.a
 
#LOCAL_PREBUILT_LIBS += libz.a


include $(BUILD_SHARED_LIBRARY)
