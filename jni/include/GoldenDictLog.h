#ifndef __GOLDEN_DICT_LOG_H__
#define __GOLDEN_DICT_LOG_H__

#include<stdio.h>

#define LEVEL_INFO  1 

#define LEVEL_DEBUG 3 

#define LEVEL_ERROR 5 

#define DEBUG_LEVEL 3 

#ifdef ANDROID_PLATFORM
#include<android/log.h>
#define  LOG_TAG    "DICT2"
#if DEBUG_LEVEL == LEVEL_INFO
#define golden_printfi(fmt,...) 
#define golden_printfd(fmt,...)
#define golden_printfe(fmt,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, "(%s:%u):" fmt, __func__, __LINE__ , ##__VA_ARGS__);
#else
#if DEBUG_LEVEL == LEVEL_DEBUG 
#define golden_printfi(fmt,...)
#define golden_printfd(fmt,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, "(%s:%u):" fmt, __func__, __LINE__ , ##__VA_ARGS__);
#define golden_printfe(fmt,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, "(%s:%u):" fmt, __func__, __LINE__ , ##__VA_ARGS__);
#else
#define golden_printfi(fmt,...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG, "(%s:%u): " fmt, __func__, __LINE__ , ##__VA_ARGS__);
#define golden_printfd(fmt,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, "(%s:%u):" fmt, __func__, __LINE__ , ##__VA_ARGS__);
#define golden_printfe(fmt,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, "(%s:%u):" fmt, __func__, __LINE__ , ##__VA_ARGS__);
#endif
#endif

#else

#if DEBUG_LEVEL == LEVEL_INFO
#define golden_printfi(fmt,...) 
#define golden_printfd(fmt,...)
#define golden_printfe(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#else
#if DEBUG_LEVEL == LEVEL_DEBUG 
#define golden_printfi(fmt,...) 
#define golden_printfd(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#define golden_printfe(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#else
#define golden_printfi(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#define golden_printfd(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#define golden_printfe(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#endif
#endif

#endif

#endif
