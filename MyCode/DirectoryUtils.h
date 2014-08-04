#ifndef __DIRECTORY_UTILS_H__
#define __DIRECTORY_UTILS_H__
void scan_directory_with_suffix(const char *path,const char *suffix,char **file_list);
void scan_directory_with_prefix(const char *path,const char *prefix,char **file_list);
#endif
