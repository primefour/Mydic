#include"com_Dict_DictApp2_DictSearchEngine.h"
#include<stdio.h>
#include"StardictMain.h"
#include"GoldenDictLog.h"

static StardictMain* pDictMain = NULL ;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    engQueryWord
 * Signature: (Ljava/lang/String;)Lcom/Dict/DictApp2/TextMetaData;
 */
JNIEXPORT jobject JNICALL  Java_com_Dict_DictApp2_DictSearchEngine_engQueryWord (JNIEnv *pEnv, jclass pobj, jstring pString){
    jboolean isCopy;
    TextMetaData tmd;
    const char* str = pEnv->GetStringUTFChars(pString, &isCopy);
    golden_printfi("print UTF-8 string: %s, %d", str, isCopy);
    pDictMain->getDictIdx(0)->DictQuery(str,&tmd);

    pEnv->ReleaseStringUTFChars(pString, str);

    jclass tmd_class = pEnv->FindClass("com/Dict/DictApp2/TextMetaData");
    if(tmd_class == NULL){
        return NULL;
    }
    jmethodID cid = pEnv->GetMethodID(tmd_class,"<init>", "()V");
    jobject obj = pEnv->NewObject(tmd_class,cid);
    if(obj == NULL){
        pEnv->DeleteLocalRef(tmd_class);
        return NULL;
    }
    jfieldID meaning_fid= pEnv->GetFieldID(tmd_class,"mTextMeaning","Ljava/lang/String;");
    if(meaning_fid == NULL){
        pEnv->DeleteLocalRef(tmd_class);
        pEnv->DeleteLocalRef(obj);
        return NULL;
    }
    //jstring text = pEnv->GetObjectField(obj,meaning_fid); 
    tmd.mTextMeaning += "<p> </p> \n<a href hello.wav > audio </a> <p></p> " ; 
    jstring text = pEnv->NewStringUTF(tmd.mTextMeaning.string());
    pEnv->SetObjectField(obj,meaning_fid,text);
    return obj ; 
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
    const char *str = NULL;
    jboolean *isCopy;
    str = pEnv->GetStringUTFChars(pString, isCopy);
    if(pDictMain != NULL){
        pDictMain->InsertDict(str);
    }else{
        golden_printfe("StardictMain should be init before using\n");
    }
    pEnv->ReleaseStringUTFChars(pString,str);
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
    return ;
}

/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    destroyEng
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_Dict_DictApp2_DictSearchEngine_destroyEng(JNIEnv *pEnv, jclass pObj){
    if(pDictMain != NULL){
        delete pDictMain ;
        pDictMain = NULL;
    }
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved){
    JNIEnv* env;
    if (jvm->GetEnv((void **)&env, JNI_VERSION_1_6)) {
        return -1;
    }
/*
    JNINativeMethod nm[2];
    nm[0].name = "initEng";
    nm[0].signature = "()V";
    nm[0].fnPtr = (void *)Java_com_Dict_DictApp2_DictSearchEngine_initEng;

    nm[1].name = "engQueryWord";
    nm[1].signature = "(Ljava/lang/String;)Lcom/Dict/DictApp2/TextMetaData";
    nm[1].fnPtr = (void *)Java_com_Dict_DictApp2_DictSearchEngine_engQueryWord;


    jclass cls = env->FindClass("com/Dict/DictApp2/DictSearchEngine");
    // Register methods with env->RegisterNatives.
    env->RegisterNatives(cls, nm, 1);
    */
    
    return JNI_VERSION_1_6;
}


#ifdef __cplusplus
}
#endif

