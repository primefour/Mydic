

int GoldenDictManager::GoldenDictAdd(const char *path){
    //check the path
    String8 tmp_path(path);
    //just stardict now
    golden_printfd("tmp_path.getBasePath() = %s ",tmp_path.getBasePath().string());
    
    //
    GoldenDictInterface *tmp =  new StardictInstance(tmp_path.getBasePath());
    mDictionaryMap->[String8(tmp_path.getBasePath())] = tmp;  
}

DictInterface *StardictMain::getDictIdx(int idx){
    if(idx < MAX_DICT_COUNT && mDict[idx] != NULL){
        return mDict[idx];
    }
    return NULL;
}

void StardictMain::DeleteDict(const char *path){
    golden_printfd("%s %d ",__func__,__LINE__);
}

StardictMain::StardictMain(){
    int i = 0;
    while(i < MAX_DICT_COUNT){
        mDict[i] = NULL;
        i++;
    }

}
