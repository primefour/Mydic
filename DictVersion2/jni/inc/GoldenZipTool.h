#ifndef __GOLDEN_ZIP_TOOL_H__
#define __GOLDEN_ZIP_TOOL_H__
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include "zlib.h"

#ifndef HAVE_GETOPT
#include "getopt.h"
#endif
#include "zip.h"
#include "AngelRef.h"
#include "String8.h"
#include<set>
#include<list>
using namespace std;


struct ZipEntry:public Ref{
        String8 mName;
        unsigned int mSize;
        unsigned int mCrc;
        bool operator==(const ZipEntry &obj){
            return !strcmp(mName,obj.mName);
        }
        const char *string()const {
            return mName.string();
        }
};


class GoldenZipTool{
    public:
        GoldenZipTool(const char *file);
        virtual ~GoldenZipTool();
        bool IsExist(const char *infile);
        int GetInFile(const char *infile,char *buff,int len);
        int GetInFile(const char *infile,const char *outputFile);
        void ReleaseAllFiles();
    private:
        int CheckZipFile(int idx, zip_int64_t size, unsigned int crc);
        struct zip*  mZip;
        ZipEntry *mPtrEntries;
        zip_uint64_t mEntryCount;
};


#endif
