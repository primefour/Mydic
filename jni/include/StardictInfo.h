#ifndef __STARDICT_INFO_H__
#define __STARDICT_INFO_H__
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"StandardIO.h"
#include"String8.h"

typedef enum{
    INFO_VERSION,
    INFO_BOOK_NAME,
    INFO_WORD_COUNT,
    INFO_SYC_WORD_COUNT,
    INFO_IDX_FILE_SIZE,
    INFO_IDX_OFFSET,
    INFO_AUTHOR,
    INFO_EMAIL,
    INFO_WEBSITE,
    INFO_DESCRIPTION,
    INFO_DATE,
    INFO_SAME_TYPE_SEQUENCE,
    INFO_MAX,
}STARDICT_INFO_TYPE;

class StardictInfo:public Ref{
    public:
        StardictInfo(const char *file_path);
        ~StardictInfo(){
        }

        String8 getVersion(){
            return mInfoString[INFO_VERSION].getStringValue('=');
        }
        inline String8 getBookName(){
            return mInfoString[INFO_BOOK_NAME].getStringValue('=');
        }
        inline String8 getAuthor(){
            return mInfoString[INFO_AUTHOR].getStringValue('=');
        }
        inline String8 getEmail(){
            return mInfoString[INFO_EMAIL].getStringValue('=');
        }
        inline String8 getWebsite(){
            return mInfoString[INFO_WEBSITE].getStringValue('=');
        }
        inline String8 getDescription(){
            return mInfoString[INFO_DESCRIPTION].getStringValue('=');
        }
        inline String8 getDate(){
            return mInfoString[INFO_DATE].getStringValue('=');
        }

        inline String8 getSameTypeSeq(){
            return mInfoString[INFO_SAME_TYPE_SEQUENCE].getStringValue('=');
        }

        inline int getLongValue(String8 & str){
            String8 value = str.getStringValue('=');
            if(!value.isEmpty()){
                return atoi(value);
            }
            return 0;
        }

        inline int getWordCount(){
            return getLongValue(mInfoString[INFO_WORD_COUNT]);
        }

        inline int getSynWordCount(){
            return getLongValue(mInfoString[INFO_SYC_WORD_COUNT]);
        }

        inline int getIdxFileSize(){
            return getLongValue(mInfoString[INFO_IDX_FILE_SIZE]);
        }

        inline int getOffsetBits(){
            return  getLongValue(mInfoString[INFO_IDX_OFFSET]);
        }
        void dumpInfo();
    private:
        static const char* infoFileList[INFO_MAX +1];
        String8 mInfoString[INFO_MAX +1];
        String8 file_name;
};
#endif //
