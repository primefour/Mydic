#include"AngelWordIndex.h"
#include"GoldenHashMapExt.h"
#include"AngelLog.h"
#include"String8.h"
#include<vector>
#include<list>
#include<map>

using namespace std;

WordIndexManager::WordIndexManager(){
    mHashIdx.reserve(199999);
}

void WordIndexManager::AddWord(String8 word, WordOffsetInfo t){
    mHashIdx.insert(word,t);
}

//return offset of word in the dictionary
const WordOffsetInfo& WordIndexManager::QueryWordByIdx(String8 &word,int idx){
    list<WordOffsetInfo>& ret = mHashIdx.find(word);
    if(!ret.empty()){
        angel_printfe("ret size = %ld  \n",ret.size());
        list<WordOffsetInfo>::iterator begin = ret.begin();
        list<WordOffsetInfo>::iterator end = ret.begin();
        while(begin != end && idx > 0){
            begin ++ ;
            idx --;
        }
        return *begin;
    }else{
        angel_printfe("ret size = %ld  \n",ret.size());
        return ret.front();
    }
}

//return count of item
const list<WordOffsetInfo>& WordIndexManager::QueryWordByAll(String8 &word){
    list<WordOffsetInfo>& ret = mHashIdx.find(word);
    return ret;
}




