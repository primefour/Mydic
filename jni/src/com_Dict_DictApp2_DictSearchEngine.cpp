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

jobject String2JOBJ(JNIEnv* env, const char* pat){
    jclass strClass = env->FindClass("Ljava/lang/String;");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
    jstring encoding = env->NewStringUTF("utf-8");
    return env->NewObject(strClass, ctorID, bytes, encoding);
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
        jmethodID arrayList_add = pEnv->GetMethodID(cls_ArrayList,"add","(Ljava/lang/Object;)Z");
        if(arrayList_add == NULL){
            golden_printfe("*****tmp = get  arrayList_add  fail\n");
            return NULL;
        }
        GoldenDict->GoldenDictGetDicts(dictList);
        const char **tmp = dictList ;
        while(*tmp != NULL){
            golden_printfe("*****tmp = %s \n",*tmp);
            jstring obj= pEnv->NewStringUTF(*tmp);
            jobject o = (jobject) obj;
            //jobject obj = String2JOBJ(pEnv,*tmp);
            if(obj != NULL){
                //pEnv->CallObjectMethod(obj_ArrayList,arrayList_add,o);
                pEnv->CallBooleanMethod(obj_ArrayList,arrayList_add,o);

            }
            tmp ++;
        }
        return obj_ArrayList ;
    }
    free(dictList);
    return NULL;
}

/*
 * Class:     com_Dict_DictApp2_DictSearchEngine
 * Method:    dictEngGetDictList
 * Signature: ()Ljava/util/ArrayList;
 */
JNIEXPORT void JNICALL Java_com_Dict_DictApp2_DictSearchEngine_dictEngSetOrderList (JNIEnv *pEnv, jclass jc,jobject list){
    const char **dictList = (const char **)malloc(sizeof(const char *) * 20);
    golden_printfe("###########\n");
    if(list == NULL){
        return ;
    }
    jclass clazz = (pEnv)->GetObjectClass(list);
    jmethodID getMethodID = (pEnv)->GetMethodID(clazz, "get", "(I)Ljava/lang/Object;");
    jmethodID sizeMethodID = (pEnv)->GetMethodID(clazz, "size", "()I");
    int size = (pEnv)->CallIntMethod(list, sizeMethodID);
    golden_printfe("arrayList's size is : %d", size);
    const char **p = dictList;
    for (int i = 0; i < size; i++) {
        jstring str = (jstring)(pEnv)->CallObjectMethod(list, getMethodID, i);
        jboolean isCpopy;
        *p = (pEnv)->GetStringUTFChars(str, &isCpopy);
        p++;
    }
    GoldenDict->GoldenDictSetOrder(dictList);
    p = dictList;
    for (int i = 0; i < size; i++) {
        pEnv->ReleaseStringUTFChars((jstring)(pEnv)->CallObjectMethod(list, getMethodID, i),*p);
        p++;
    }
    free(dictList);
    return ;
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
