#ifdef __GOLDEN_DICT_MANAGER_H__
#define __GOLDEN_DICT_MANAGER_H__

class GoldenDictInterface{
    public:
        virtual const String8& GoldenDictName() = 0;
        virtual int GoldenDictQuery(const char *word,char *buff);
};


class GoldenDictManager{
    public:
       GoldenDictManager(); 
       int GoldenDictAdd(const char *path);
       int GoldenDictDelete(const char *path);
       int GoldenDictQuery(const char *word,char *buff);
    private:
       map<String8,SObject<GoldenDictInterface> > mDictionaryMap;
};

#endif
