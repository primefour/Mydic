#ifndef __DIRECTORY_UTILS_H__
#define __DIRECTORY_UTILS_H__
#include"HashList.h"
#include<dirent.h>
#include<sys/stat.h>
#include<sys/stat.h>
#include<sys/types.h>
#include"list.h"

int  split_path(const char *file_path,char *file_main_path,int path_len ,char *file_name,int len);
char *get_path_without_suffix(const char *file_path,char *file_name,int len);
char *get_path_suffix(const char *file_path,char *suffix,int len);
typedef void (*scanner_callback)(void *data,const char *file_full_path,const char *suffix);
//This code is ported from android media scanner 

class DirectoryScanner{
    public:
        DirectoryScanner();
        ~DirectoryScanner();
        int processDirectory(const char *path,scanner_callback callback,void *data);
        void add_suffix(const char *str);
        void remove_suffix(char *str);
        void DumpFileList();
    private:
        void insert_file(const char *str);
        int doProcessDirectoryEntry(char *path, int pathRemaining,struct dirent* entry, char* fileSpot);
        int doProcessDirectory(char *path, int pathRemaining);
        HashList *ext_hash;
        List *file_list;
        scanner_callback callback;
        void *callback_data;
};

#endif

