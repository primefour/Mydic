#ifndef __GOLDEN_DICT_MANAGER_H__
#define __GOLDEN_DICT_MANAGER_H__
#include"String8.h"
#include"GoldenRef.h"
#include"GoldenPathScanner.h"
#include"GoldenHashSet.h"

using namespace std;

class TextMetaData:public Ref{
    public:
        TextMetaData(); 
        TextMetaData(const TextMetaData & inst); 
        TextMetaData(const char *word):mWord(word){
            mWavDataLength = 0;
            mPicDataLength = 0;
            mWav = NULL;
            mPic = NULL;
        }
        void setWord(const char *word){
            mWord.setTo(word);
        }
        void dumpInfo();
        ~TextMetaData();

        String8 mWord;
        String8 mTextMeaning;//m l g
        String8 mTextPhonetic;
        String8 mImagePath;
        String8 mVideoPath;
        String8 mSoundPath;
        String8 mOther; //h
        int mWavDataLength;
        int mPicDataLength;
        unsigned char *mWav;
        unsigned char *mPic;
};


class GoldenDictInterface:public virtual Ref{
    public:
        GoldenDictInterface(){
            mIsEnable = true;
        }
        ~GoldenDictInterface(){
        }
        virtual const String8& GetDictonaryName() = 0;
        virtual const String8& GetIdentifyPath() = 0;
        virtual const String8 GetResourcePath()=0;
        virtual void SetEnable(bool enable){ mIsEnable = enable; };
        virtual bool IsEnable(){ return mIsEnable; };

        virtual int GoldenDictQuery(const char *word,TextMetaData *ptrMeta) = 0;
    private:
        bool mIsEnable;
};

enum{
    STAR_DICT_TYPE = 1,
    DSL_DICT_TYPE,
    DICT_TYPE_MAX,
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
        int  GoldenDictQuery(const char *word,char *buff);

        void GoldenScanDisk(const char *path);
        void GoldenDictPersist();
        //read DictIdx and restore dictionaries
        void GoldenDictReload();
        //add a single file
        void GoldenDictAddDict(const char *name);
        void GoldenDictRemoveDict(const char *name);
        void GoldenDictEnableDict(const char *name,bool enable);
        void GoldenDictGetDicts(const char **list);



        static const char *GoldenGetCachePath();
        static const char *GoldenGetTmpPhoneticPath();
        static const char *GoldenGetTmpImgPath();
    private:
        char *GoldenDictGetPersistData(const char *dictName,char *buff,int length);
        map<String8,SObject<GoldenDictInterface> > mDictionaryMap;
        map<String8,int> mDictionaryType;
        map<String8,String8> mDictionaryPath;

        DictHashSet<SObject<String8> > mIgnoreFileExtend;
        DictHashSet<SObject<String8> > mIgnorePath;
};
#endif
