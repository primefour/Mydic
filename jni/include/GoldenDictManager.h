#ifndef __GOLDEN_DICT_MANAGER_H__
#define __GOLDEN_DICT_MANAGER_H__
#include"String8.h"
#include"GoldenRef.h"
#include"GoldenPathScanner.h"
#include"GoldenHashSet.h"

using namespace std;

class GoldenDictInterface:public virtual Ref{
    public:
        GoldenDictInterface(){
            mIsEnable = true;
        }
        ~GoldenDictInterface(){

        }
        static const char *getPhoneticPath();
        static const char *getImgPath();
        virtual const String8& GetDictonaryName() = 0;
        virtual int GoldenDictQuery(const char *word,char *buff) = 0;
        virtual void SetEnable(bool enable){
            mIsEnable = enable;
        }
        virtual bool IsEnable(){
            return mIsEnable;
        }
    private:
        bool mIsEnable;
};

enum{
    STAR_DICT_TYPE = 1,
    DSL_DICT_TYPE,
    DICT_TYPE,MAX,
};


class GoldenDictManager :public Ref,GoldenPathFilter{
    public:
        GoldenDictManager(); 
        virtual bool FilterFiles(const char *fileName){
            return true;
        }
        virtual bool IgnorePath(const char *dirPath){
            return false;
        }
        virtual void doWithFiles(const char *file);
        void GoldenDictAdd(const char *path);
        void GoldenDictDelete(const char *path);
        int GoldenDictQuery(const char *word,char *buff);
    private:
       map<String8,SObject<GoldenDictInterface> > mDictionaryMap;
       map<String8,int> mDictionaryType;
       DictHashSet<SObject<String8> > mIgnoreFileExtend;
       DictHashSet<SObject<String8> > mIgnorePath;
       DictHashSet<SObject<String8> > mFileExtend;
};
#endif
