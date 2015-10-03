#include"com_Dict_DictApp2_DictSearchEngine.h"
#include<stdio.h>
#include"GoldenDictManager.h"
#include"GoldenDictLog.h"

static SObject<GoldenDictManager> GoldenDict = NULL;

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    dictEngQueryWord
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_Dict_DictApp2_DictSearchEngine_dictEngQueryWord (JNIEnv *pEnv, jclass jc, jstring js){
    const int BUFF_SIZE = 102400;
    jboolean isCopy;
    const char* str = pEnv->GetStringUTFChars(js, &isCopy);
    golden_printfe("print UTF-8 string: %s, %d", str, isCopy);
    char *queryResult = (char *)malloc(BUFF_SIZE);
    if(GoldenDict.GetPoint()){
        GoldenDict->GoldenDictQuery(str,queryResult);
        pEnv->ReleaseStringUTFChars(js, str);
        jstring obj= pEnv->NewStringUTF(queryResult);
        free(queryResult);
        queryResult = NULL;
        return obj ; 
    }else{
        golden_printfe("GoldenDict doesn't initialize\n");
        return NULL;
    }
}

/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    dictEngAddDictionary
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_Dict_DictApp2_DictSearchEngine_dictEngAddDictionary (JNIEnv *pEnv, jclass jc, jstring js){
    jboolean isCopy;
    const char* str = pEnv->GetStringUTFChars(js, &isCopy);
    golden_printfe("print UTF-8 string: %s, %d", str, isCopy);
    GoldenDict->GoldenDictAddDict(str);
    pEnv->ReleaseStringUTFChars(js, str);
    return true; 

}
/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    dictEngRemoveDictionary
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_Dict_DictApp2_DictSearchEngine_dictEngRemoveDictionary (JNIEnv *pEnv, jclass jc, jstring js){
    jboolean isCopy;
    const char* str = pEnv->GetStringUTFChars(js, &isCopy);
    golden_printfe("print UTF-8 string: %s, %d", str, isCopy);
    GoldenDict->GoldenDictRemoveDict(str);
    pEnv->ReleaseStringUTFChars(js, str);
    return true; 
}
/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    dictEngScanPath
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_Dict_DictApp2_DictSearchEngine_dictEngScanPath (JNIEnv *pEnv, jclass jc, jstring js){
    jboolean isCopy;
    const char* str = pEnv->GetStringUTFChars(js, &isCopy);
    golden_printfe("print UTF-8 string: %s, %d", str, isCopy);
    if(GoldenDict.GetPoint() != NULL){
        GoldenDict->GoldenScanDisk(str);
    }
    pEnv->ReleaseStringUTFChars(js, str);
}
/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    dictEngInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_Dict_DictApp2_DictSearchEngine_dictEngInit (JNIEnv *pEnv, jclass jc){
    if(GoldenDict.GetPoint() != NULL){
        return ;
    }else{
        GoldenDict = new GoldenDictManager();
    }
}
/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    dictEngDeinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_Dict_DictApp2_DictSearchEngine_dictEngDeinit (JNIEnv *pEnv, jclass jc){
    return ;
}
/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    dictEngGetDictList
 * Signature: ()Ljava/util/ArrayList;
 */
JNIEXPORT jobject JNICALL Java_com_Dict_DictApp2_DictSearchEngine_dictEngGetDictList (JNIEnv *pEnv, jclass jc){
    const char **dictList = (const char **)malloc(sizeof(const char *) * 20);
    memset(dictList,0,sizeof(const char *) * 20);
    if(GoldenDict.GetPoint() != NULL){
        jclass cls_ArrayList = pEnv->FindClass("java/util/ArrayList");  
        jmethodID construct = pEnv->GetMethodID(cls_ArrayList,"<init>","()V");  
        jobject obj_ArrayList = pEnv->NewObject(cls_ArrayList,construct,"");  
        jmethodID arrayList_add = pEnv->GetMethodID(cls_ArrayList,"add","(Ljava/lang/String;)");  

        GoldenDict->GoldenDictGetDicts(dictList);
        const char **tmp = dictList ;
        while(*tmp != NULL){
            jstring obj= pEnv->NewStringUTF(*tmp);
            pEnv->CallObjectMethod(obj_ArrayList,arrayList_add,obj);
            tmp ++;
        }
        return obj_ArrayList ;
    }
    free(dictList);
    return NULL;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved){
    JNIEnv* env;
    if (jvm->GetEnv((void **)&env, JNI_VERSION_1_6)) {
        return -1;
    }
    return JNI_VERSION_1_6;
}

#ifdef __cplusplus
}
#endif
