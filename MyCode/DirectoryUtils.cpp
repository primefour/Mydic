#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
#include"MetaDataHead.h"
#include"DirectoryUtils.h"
#include<assert.h>

//This code is ported from android media scanner 
//
int doProcessDirectoryEntry(char *path, int pathRemaining,struct dirent* entry, char* fileSpot);
int doProcessDirectory(char *path, int pathRemaining);

char *get_path_suffix(const char *file_path,char *suffix,int len){
    const char *pdash = strrchr(file_path,'/');
    if(pdash == NULL){
        pdash = file_path;
    }
    const char *pdot = strchr(pdash,'.');
    if(pdot != NULL){
        strncpy(suffix,pdot,len);
    }else{
        return NULL;
    }
    printf("suffix = %s \n",suffix);
    return suffix;

}


static int FilterBySuffix(const struct dirent *entry,const char *suffix){
    char tmp_suff[1024]={0};
    printf("%s  entry->d_name = %s \n",__func__,entry->d_name);
    char * tmp = get_path_suffix(entry->d_name,tmp_suff,sizeof(tmp_suff));
    if(tmp != NULL){
        if(strcmp(suffix,tmp_suff) == 0){
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int split_path(const char *file_path,char *file_main_path,int path_len ,char *file_name,int len){
    if(file_path == NULL){
        return -1;
    }
    const char *pdash = strrchr(file_path,'/');
    const char *pdot = strrchr(file_path,'.');
    const char *file_name_begin = NULL;
    const char *file_name_end = NULL;

    if(pdash){
        file_name_begin = (pdash+1);
    }else{
        file_name_begin = file_path;
    }
    if(pdot && pdot > pdash){
        file_name_end = pdot;
    }else{
        file_name_end = file_path + strlen(file_path) +1;
    }
    if(len < file_name_end - file_name_begin){
        printf("path_len is more small \n");
        return -1 ;
    }else{
        memcpy(file_name,file_name_begin,file_name_end - file_name_begin);
    }

    if(path_len < file_name_begin - file_path){
        printf("path_len is more small \n");
        return -1;
    }else{
        memcpy(file_main_path,file_path,file_name_begin - file_path);
    }

    printf("%s file_main_path = %s file_name = %s \n",__func__,file_main_path,file_name);
    return 0;
}


char *get_path_without_suffix(const char *file_path,char *file_name,int len){
    const char *pdash = strrchr(file_path,'/');
    if(pdash == NULL){
        pdash = file_path;
    }
    const char *pdot = strchr(pdash,'.');
    if(len < pdot - file_path){
        printf("len is very small \n");
        assert(0);
        return NULL;
    }else{
        strncpy(file_name,file_path, pdot - file_path);
    }
    printf("file_name = %s \n",file_name);
    return file_name;
}




int  processDirectory(const char *path){ 
    int pathLength = strlen(path);
    if (pathLength >= PATH_MAX) {
        return 0;
    }
    char* pathBuffer = (char *)malloc(PATH_MAX + 1);
    if (!pathBuffer) {
        return -1;
    }

    int pathRemaining = PATH_MAX - pathLength;
    strcpy(pathBuffer, path);
    if (pathLength > 0 && pathBuffer[pathLength - 1] != '/') {
        pathBuffer[pathLength] = '/';
        pathBuffer[pathLength + 1] = 0;
        --pathRemaining;
    }

    int result = doProcessDirectory(pathBuffer, pathRemaining); 
    free(pathBuffer);
    return result;
}

int doProcessDirectory(char *path, int pathRemaining){ 
    char* fileSpot = path + strlen(path);
    struct dirent* entry;
    DIR* dir = opendir(path);
    if (!dir) {
        printf("Error opening directory '%s', skipping: %s.", path, strerror(errno));
        return 0;
    }
    int result = 0;
    while ((entry = readdir(dir))) {
        if (doProcessDirectoryEntry(path, pathRemaining, entry, fileSpot) < 0 ) {
            result = -1 ;
            break;
        }
    }
    closedir(dir);
    return result;
}

int doProcessDirectoryEntry(char *path, int pathRemaining,struct dirent* entry, char* fileSpot) {
    struct stat statbuf;
    const char* name = entry->d_name;
    if (name[0] == '.' && (name[1] == 0 || (name[1] == '.' && name[2] == 0))) {
        return 0;
    }

    int nameLength = strlen(name);
    if (nameLength + 1 > pathRemaining) {
        return 0;
    }

    strcpy(fileSpot, name);

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
            printf("stat() failed for %s: %s", path, strerror(errno) );
        }
    }
    
    if (type == DT_DIR) {
        // and now process its contents
        strcat(fileSpot, "/");
        int  result = doProcessDirectory(path, pathRemaining - nameLength - 1);
        if (result < -1) {
            return -1;
        }
    } else if (type == DT_REG){
        stat(path, &statbuf);
    }
    return 0;
}


class DirectoryScanner{
    public:
        DirectoryScanner();
        ~DirectoryScanner();
        int processDirectory(const char *path);
        void add_suffix(const char *str);
        void remove_suffix(const char *str);
    private:
        void insert_file(const char *str);
        int doProcessDirectoryEntry(char *path, int pathRemaining,struct dirent* entry, char* fileSpot);
        int doProcessDirectory(char *path, int pathRemaining);
        HashList *ext_hash;
        List *file_list;
};

static unsigned long default_string_hash_func(void *data){
    const char *ptr;
    unsigned int val;
    val = 0;
    ptr = (char *)data;
    while(*ptr != '\0'){
        unsigned int tmp = 0;
        val = (val<<4) + (*ptr);
        if(tmp = (val&0xf0000000)){
            val = val ^(tmp >> 24);
            val = val ^tmp;
        }
        ptr ++;
    }
    return val;
}

static int hash_compare(void *key1,void *key2){
    char *path1  
    if(key1 == key2){
        return 0;
    }else{
        return 1;
    }
}

static void hash_destroy(void *key,void *data){

}

DirectoryScanner::DirectoryScanner(){

}


