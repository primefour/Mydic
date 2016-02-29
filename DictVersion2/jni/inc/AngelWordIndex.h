#ifndef __ANGEL_WORD_INDEX__
#define __ANGEL_WORD_INDEX__

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


class WordIndexManager{
    public:
        void AddWord(String8 word, WordOffsetInfo t);
        //return offset of word in the dictionary
        const WordOffsetInfo& QueryWordByIdx(String8 &word,int idx);
        //return count of item
        int QueryWordByAll(String8 &word,vector<WordOffsetInfo> &vW);

    private :
        HashMapExt<
};


#endif
