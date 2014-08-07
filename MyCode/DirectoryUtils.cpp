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




int  DirectoryScanner::processDirectory(const char *path){ 
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

int DirectoryScanner::doProcessDirectory(char *path, int pathRemaining){ 
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

int DirectoryScanner::doProcessDirectoryEntry(char *path, int pathRemaining,struct dirent* entry, char* fileSpot) {
    struct stat statbuf;
    const char* name = entry->d_name;
    if (name[0] == '.' && (name[1] == 0 || (name[1] == '.' && name[2] == 0))) {
        return 0;
    }
    const char *suffix = strchr(name,'.');
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
        if(ext_hash->get_size() == 0){
            insert_file(path);
        }else{
            void *ret = ext_hash->hash_find(suffix);
            if(ret != NULL){
                printf("######ret = %s \n",(char *)ret);
            }
            if(suffix != NULL && ret != NULL){
                insert_file(path);
            }
        }
    }
    return 0;
}


void DirectoryScanner::add_suffix(const char *str){
    int len = strlen(str);
    char *suffix = (char *)malloc(len + 1);
    memset(suffix,0,len + 1);
    strcpy(suffix,str);
    ext_hash->hash_insert(suffix);
}

void DirectoryScanner::remove_suffix(char *str){
    ext_hash->hash_remove(str);
}

void DirectoryScanner::insert_file(const char *str){
    int len = strlen(str);
    char *path = (char *)malloc(len + 1);
    printf("%s ########%s \n",__func__,str);
    memset(path,0,len + 1);
    strcpy(path,str);
    file_list->insert_list_tail(path);
}

static unsigned long directory_hash_func(const void *data){
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

static int directory_hash_compare(const void *key1,const void *key2){
    const char *str1 = (const char *)key1; 
    const char *str2 = (const char *)key2;
    //note NULL pointer
    return strcmp(str1,str2);
}

static void directory_hash_destroy(void *data){
    if(data != NULL){
        free(data);
    }
}

static int directory_list_compare(void *key1,void *key2){
    char *str1 = (char *)key1; 
    char *str2 = (char *)key2;
    //note NULL pointer
    return strcmp(str1,str2);
}

static void directory_list_destroy(void *data){
    if(data != NULL){
        free(data);
    }
}
void DirectoryScanner::DumpFileList(){
    file_list->begin_iterate();
    char *tmp = (char *)file_list->iterate_item();
    while(tmp != NULL){
        printf("####%s \n",tmp);
        tmp = (char *)file_list->iterate_item();
    }
}

DirectoryScanner::DirectoryScanner(){
    ext_hash = new HashList(directory_hash_func,directory_hash_compare,directory_hash_destroy,10);
    assert(ext_hash != NULL);
    file_list = new List(directory_list_compare,directory_list_destroy);
    assert(file_list != NULL);
}

DirectoryScanner::~DirectoryScanner(){
    delete ext_hash;
    delete file_list;
}


