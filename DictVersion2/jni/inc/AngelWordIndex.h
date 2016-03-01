#ifndef __ANGEL_WORD_INDEX__
#define __ANGEL_WORD_INDEX__
#include"GoldenHashMapExt.h"
#include"String8.h"
#include<vector>
#include<list>
#include<map>

using namespace std;

struct WordOffsetInfo{
    WordOffsetInfo(){
        idx = 0;
        size = 0;
        offset = 0 ;
    }
    WordOffsetInfo(unsigned int i,unsigned int s,int ds){
        idx = i;
        offset= s;
        size = ds;
    }
    //only 16 dictionary 
    unsigned int idx:4;
    //content size
    unsigned int size:28;
    //file offset
    unsigned int offset;
};


struct WordInfoListItem{
    String8 mWord ;
    vector<WordOffsetInfo> mOffsetList;
};

struct DictInfo{
        String8 mDictName;
        String8 mDictPath;
        String8 mIconUrl;
        int type;
};

/*
class DictionaryManager{
    public:
        void AddDictByPath(String8 path);
        void RMDictByPath(String8 path);
        void RMDictByName(String8 name);
        int QueryWordByDict(String8 word,String8 dictName,char *buff,len);
        int QueryWordByAll(String8 word,String8 res,char *buff,len);
    private:
        vector<DictInfo> mDList;
        WordIndexManager mDictIdx;
}
*/

class defaultHashCode {
    public :
        int operator()(const String8 &key){
            unsigned int val;
            val = 0;
            const char *ptr = key.string();
            while (*ptr != '\0') {
                unsigned int tmp;
                val = (val << 4) + (*ptr);
                if (tmp = (val & 0xf0000000)) {
                    val = val ^ (tmp >> 24);
                    val = val ^ tmp;
                }
                ptr++;
            }
            return val ;
        }
};

typedef HashMapExt<String8,WordOffsetInfo,defaultHashCode> HMAPType;

class WordIndexManager{
    public:
        WordIndexManager();
        void AddWord(String8 word, WordOffsetInfo t);
        //return offset of word in the dictionary
        const WordOffsetInfo& QueryWordByIdx(String8 &word,int idx);
        //return count of item
        const list<WordOffsetInfo> & QueryWordByAll(String8 &word);
    private :
        //hash idx for index word
        HMAPType  mHashIdx;
};


#endif
