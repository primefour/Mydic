#include"GoldenPathScanner.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<list>
#include<map>
#include<stdexcept>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>
#include<sys/stat.h>
#include<unistd.h>


using namespace std;

GoldenPathScanner::GoldenPathScanner(const char *path,GoldenPathFilter *filter){
    mScanFilter = filter;
    if (access(path, F_OK) != 0) {
        golden_printfe("Can't access this file\n");
        throw exception();
    }
    mPath = (char *)malloc(PATH_MAX + 1);
    if (!mPath) {
        golden_printfe("No memory for file scanner \n");
        throw exception();
    }
    memset(mPath,0,PATH_MAX + 1);
    strcpy(mPath, path);
    char *tmp = mPath + strlen(mPath) -1;
    if(*tmp != '/'){
        *(tmp+1) = '/';
    }
}


GoldenPathScanner::~GoldenPathScanner(){
    if(mPath){
        free(mPath);
    }
}

void GoldenPathScanner::GoldenStartScan(){
    doProcessDirectory(mPath);
}


bool GoldenPathScanner::doProcessDirectory(char *path){
    struct dirent* entry;
    if (mScanFilter != NULL && mScanFilter->IgnorePath(path)){
        return false;
    }
    DIR* dir = opendir(path);
    if (!dir) {
        golden_printfe("Error opening directory '%s', skipping: %s.\n", path, strerror(errno));
        return false;
    }

    char *pathEnd = path + strlen(path);
    while ((entry = readdir(dir))) {
        if (!doProcessDirectoryEntry(path,entry)) {
            golden_printfe("do entry '%s' skip\n",entry->d_name);
            continue;
        }
        memset(pathEnd,0,(mPath + PATH_MAX - pathEnd));
    }
    closedir(dir);
    return true;
}

bool GoldenPathScanner::doProcessDirectoryEntry( char *path,struct dirent* entry){
    struct stat statbuf;
    const char* name = entry->d_name;

    // ignore "." and ".."
    if (name[0] == '.' && (name[1] == 0 || (name[1] == '.' && name[2] == 0))) {
        return false;
    }

    strcat(path, name);

    int type = entry->d_type;

    if (type == DT_UNKNOWN) {
        // If the type is unknown, stat() the file instead.
        // This is sometimes necessary when accessing NFS mounted filesystems, but
        // could be needed in other cases well.
        if (stat(path, &statbuf) == 0) {
            if (S_ISREG(statbuf.st_mode)) {
                type = DT_REG;
            } else if (S_ISDIR(statbuf.st_mode)) {
                type = DT_DIR;
            }
        } else {
            golden_printfe("stat() failed for %s: %s \n", path, strerror(errno) );
            return false;
        }
    }

    if(type == DT_DIR){
        if(mScanFilter != NULL && mScanFilter->IgnorePath(path)){
            return false;
        }
        strcat(path, "/");
        if(doProcessDirectory(path)){
            return true;
        }
    }

    if(type == DT_REG){
        if(mScanFilter != NULL && mScanFilter->FilterFiles(path)){
            mScanFilter->doWithFiles(path);
            return true;
        }else{
            return false;
        }
    }
    return false;
}

