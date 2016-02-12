#ifndef _ANGEL_LOG_H__
#define _ANGEL_LOG_H__

#include<stdio.h>

#define LEVEL_INFO  1 

#define LEVEL_DEBUG 3 

#define LEVEL_ERROR 5 

#define DEBUG_LEVEL 3 

#ifdef ANDROID_PLATFORM
#include<android/log.h>
#define  LOG_TAG    "DICT2"
#if DEBUG_LEVEL == LEVEL_INFO
#define angel_printfi(fmt,...) 
#define angel_printfd(fmt,...)
#define angel_printfe(fmt,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, "(%s:%u):" fmt, __func__, __LINE__ , ##__VA_ARGS__);
#else
#if DEBUG_LEVEL == LEVEL_DEBUG 
#define angel_printfi(fmt,...)
#define angel_printfd(fmt,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, "(%s:%u):" fmt, __func__, __LINE__ , ##__VA_ARGS__);
#define angel_printfe(fmt,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, "(%s:%u):" fmt, __func__, __LINE__ , ##__VA_ARGS__);
#else
#define angel_printfi(fmt,...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG, "(%s:%u): " fmt, __func__, __LINE__ , ##__VA_ARGS__);
#define angel_printfd(fmt,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, "(%s:%u):" fmt, __func__, __LINE__ , ##__VA_ARGS__);
#define angel_printfe(fmt,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, "(%s:%u):" fmt, __func__, __LINE__ , ##__VA_ARGS__);
#endif
#endif

#else

#if DEBUG_LEVEL == LEVEL_INFO
#define angel_printfi(fmt,...) 
#define angel_printfd(fmt,...)
#define angel_printfe(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#else
#if DEBUG_LEVEL == LEVEL_DEBUG 
#define angel_printfi(fmt,...) 
#define angel_printfd(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#define angel_printfe(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#else
#define angel_printfi(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#define angel_printfd(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#define angel_printfe(fmt,...) printf("%s:%u :" fmt,__func__,__LINE__,##__VA_ARGS__)
#endif
#endif

#endif //ANDROID_PLATFORM

#endif //_ANGEL_LOG_H__
