#ifndef __DIRECTORY_UTILS_H__
#define __DIRECTORY_UTILS_H__
//This code is ported from android media scanner 



int processFile(const char *path, const char *mimeType);
int processDirectory(const char *path);
int doProcessDirectory(char *path, int pathRemaining);
int doProcessDirectoryEntry(char *path, int pathRemaining,struct dirent* entry, char* fileSpot);



#endif

