#ifndef __GOLDEN_DICT_MANAGER_H__
#define __GOLDEN_DICT_MANAGER_H__
#include"String8.h"
#include"GoldenRef.h"
#include<map>
using namespace std;
class GoldenDictInterface:public virtual Ref{
    public:
        virtual const String8& GetDictonaryName() = 0;
        virtual int GoldenDictQuery(const char *word,char *buff) = 0;
};

enum{
    STAR_DICT_TYPE,
    DSL_DICT_TYPE,
    DICT_TYPE,MAX,
};


class GoldenDictManager :public Ref{
    public:
       GoldenDictManager(); 
       void GoldenDictAdd(const char *path);
       void GoldenDictDelete(const char *path);
       int GoldenDictQuery(const char *word,char *buff);
    private:
       map<String8,SObject<GoldenDictInterface> > mDictionaryMap;
       map<String8,int> mDictionaryType;
};

#endif
