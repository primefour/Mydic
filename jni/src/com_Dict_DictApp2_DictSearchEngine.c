#include"com_Dict_DictApp2_DictSearchEngine.h"
#include<stdio.h>
#include"StardictInfo.h"
#include"StardictIdx.h"
#include"GzipHeaderParser.h"
#include"GzipDeflate.h"
#include"StardictDict.h"
#include"StardictMain.h"

static StardictMain *pDictMain = NULL ;

JNIEXPORT jstring JNICALL Java_com_Dict_DictApp2_DictSearchEngine_engQueryWord (JNIEnv *pEnv, jclass pobj, jstring pstring){
    const jbyte *str;
    jboolean *isCopy;
    str = (*pEnv)->GetStringUTFChars(pEnv, pStringP, isCopy);
    __android_log_print(ANDROID_LOG_INFO, "native", "print UTF-8 string: %s, %d", str, isCopy);
    TextMetaData * tmd = pDictMain->getDictIdx(0)->DictQuery(str);

    (*pEnv)->ReleaseStringUTFChars(pEnv, pStringP, str)
    return a; 
}

/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    engAsyncQueryWord
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_Dict_DictApp2_DictSearchEngine_engAsyncQueryWord (JNIEnv *penv, jclass pobj, jstring pstring){
    return ;
}

/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    engAddDictionary
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_Dict_DictApp2_DictSearchEngine_engAddDictionary (JNIEnv *pEnv, jclass pObj, jstring pString){
    const jbyte *str;
    jboolean *isCopy;
    str = (*pEnv)->GetStringUTFChars(pEnv, pString, isCopy);
    __android_log_print(ANDROID_LOG_INFO, "native", "print UTF-8 string: %s, %d", str, isCopy);
    if(pDictMain != NULL){
        pDictMain->InsertDict(str);
    }else{
        printf("StardictMain should be init before using\n");
    }
    (*pEnv)->ReleaseStringUTFChars(pEnv, pString,str)
    return 1;
}

/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    engRemoveDictionary
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_Dict_DictApp2_DictSearchEngine_engRemoveDictionary (JNIEnv *penv, jclass pobj, jstring pstring){
    return 0;
}


/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    initEng
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_Dict_DictApp2_DictSearchEngine_initEng(JNIEnv *pEnv, jclass pObj){
    if(pDictMain != NULL){
        return ;
    }else{
        pDictMain = new StardictMain();
    }
}

/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    destroyEng
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_Dict_DictApp2_DictSearchEngine_destroyEng(JNIEnv *pEnv, jclass pObj){
    if(pDictMain != NULL){
        delete pDictMain ;
        pDictMain NULL;
    }
}

