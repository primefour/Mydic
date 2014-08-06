#ifndef __DIRECTORY_UTILS_H__
#define __DIRECTORY_UTILS_H__
#include"HashList.h"

int  split_path_no_suffix(const char *file_path,char *file_main_path,int path_len ,char *file_name,int len);
char *get_path_without_suffix(const char *file_path,char *file_name,int len);
char *get_path_suffix(const char *file_path,char *suffix,int len);
//This code is ported from android media scanner 
/*
class DirectoryScanner{
    public:
        DirectoryScanner();
        ~DirectoryScanner();
        int processDirectory(const char *path);
        void add_suffix(const char *str);
        void remove_suffix(const char *str);
        char*enum_each_file();
    private:
        void insert_file(const char *str);
        int doProcessDirectoryEntry(char *path, int pathRemaining,struct dirent* entry, char* fileSpot);
        int doProcessDirectory(char *path, int pathRemaining);
        HashList *ext_hash;
        List *file_list;
};
*/

#endif

