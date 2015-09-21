#ifndef __GOLDEN_PATH_SCANNER__
#define __GOLDEN_PATH_SCANNER__
#include"GoldenDictLog.h"
#include<vector>
#include<map>


class GoldenPathFilter{
    public:
        virtual bool FilterFiles(const char *fileName) {
            return false;
        };
        virtual bool IgnorePath(const char *dirPath){
            return false;
        }
        virtual void doWithFiles(const char *file) {
            return ;
        }
};

class GoldenPathScanner{
    public:
        GoldenPathScanner(const char *path,GoldenPathFilter *filter = NULL);
        void GoldenStartScan();
        virtual ~GoldenPathScanner();
    private:
        bool doProcessDirectory(char *path);
        bool doProcessDirectoryEntry( char *path,struct dirent* entry);
        GoldenPathFilter *mScanFilter;
        char *mPath;
};


#endif //__GOLDEN_PATH_SCANNER__ 
