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
/*
 *
       #include <dirent.h>

       struct dirent *readdir(DIR *dirp);

       int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       readdir_r():
           _POSIX_C_SOURCE >= 1 || _XOPEN_SOURCE || _BSD_SOURCE || _SVID_SOURCE || _POSIX_SOURCE

DESCRIPTION
       The  readdir()  function  returns  a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp.  It returns NULL on reaching the end of the
       directory stream or if an error occurred.

       On Linux, the dirent structure is defined as follows:

           struct dirent {
               ino_t          d_ino;       // inode number 
               off_t          d_off;       // offset to the next dirent 
               unsigned short d_reclen;    // length of this record 
               unsigned char  d_type;      // type of file; not supported
                                              by all file system types 
               char           d_name[256]; // filename 
           };
RETURN VALUE
       On success, readdir() returns a pointer to a dirent structure.  (This structure may be statically allocated; do not attempt to free(3) it.)  If the end of the directory stream is reached, NULL
       is returned and errno is not changed.  If an error occurs, NULL is returned and errno is set appropriately.

       The readdir_r() function returns 0 on success.  On error, it returns a positive error number (listed under ERRORS).  If the end of the directory stream is reached, readdir_r() returns  0,  and
       returns NULL in *result.

ERRORS
       EBADF  Invalid directory stream descriptor dirp.

CONFORMING TO
       SVr4, 4.3BSD, POSIX.1-2001.

NOTES
       Only  the  fields d_name and d_ino are specified in POSIX.1-2001.  The remaining fields are available on many, but not all systems.  Under glibc, programs can check for the availability of the
       fields not defined in POSIX.1 by testing whether the macros _DIRENT_HAVE_D_NAMLEN, _DIRENT_HAVE_D_RECLEN, _DIRENT_HAVE_D_OFF, or _DIRENT_HAVE_D_TYPE are defined.

       Other than Linux, the d_type field is available mainly only on BSD systems.  This field makes it possible to avoid the expense of calling lstat(2) if further actions depend on the type of  the
       file.  If the _BSD_SOURCE feature test macro is defined, then glibc defines the following macro constants for the value returned in d_type:

       DT_BLK      This is a block device.

       DT_CHR      This is a character device.

       DT_DIR      This is a directory.

       DT_FIFO     This is a named pipe (FIFO).

       DT_LNK      This is a symbolic link.

       DT_REG      This is a regular file.

       DT_SOCK     This is a UNIX domain socket.

       DT_UNKNOWN  The file type is unknown.

       If the file type could not be determined, the value DT_UNKNOWN is returned in d_type.

       Currently, only some file systems (among them: Btrfs, ext2, ext3, and ext4) have full support returning the file type in d_type.  All applications must properly handle a return of DT_UNKNOWN.

       Since  POSIX.1 does not specify the size of the d_name field, and other nonstandard fields may precede that field within the dirent structure, portable applications that use readdir_r() should
       allocate the buffer whose address is passed in entry as follows:

           len = offsetof(struct dirent, d_name) +
                     pathconf(dirpath, _PC_NAME_MAX) + 1
           entryp = malloc(len);

       (POSIX.1 requires that d_name is the last field in a struct dirent.)

SEE ALSO
       getdents(2), read(2), closedir(3), dirfd(3), ftw(3), offsetof(3), opendir(3), rewinddir(3), scandir(3), seekdir(3), telldir(3)

COLOPHON
       This page is part of release 3.35 of the Linux man-pages project.  A description of the project, and information about reporting bugs, can be found at http://man7.org/linux/man-pages/.

      #include <sys/types.h>
       #include <dirent.h>

       DIR *opendir(const char *name);
       DIR *fdopendir(int fd);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       fdopendir():
           Since glibc 2.10:
               _XOPEN_SOURCE >= 700 || _POSIX_C_SOURCE >= 200809L
           Before glibc 2.10:
               _GNU_SOURCE

SCANDIR(3)                                                                             Linux Programmer's Manual                                                                             SCANDIR(3)

NAME
       scandir, alphasort, versionsort - scan a directory for matching entries

SYNOPSIS
       #include <dirent.h>

       int scandir(const char *dirp, struct dirent ***namelist,
              int (*filter)(const struct dirent *),
              int (*compar)(const struct dirent **, const struct dirent **));

       int alphasort(const void *a, const void *b);

       int versionsort(const void *a, const void *b);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       scandir(), alphasort(): _BSD_SOURCE || _SVID_SOURCE
       versionsort(): _GNU_SOURCE

DESCRIPTION
       The  scandir()  function  scans  the directory dirp, calling filter() on each directory entry.  Entries for which filter() returns nonzero are stored in strings allocated via malloc(3), sorted
       using qsort(3) with the comparison function compar(), and collected in array namelist which is allocated via malloc(3).  If filter is NULL, all entries are selected.

       The alphasort() and versionsort() functions can be used as the comparison function compar().  The former sorts directory entries using strcoll(3), the latter using strverscmp(3) on the strings
       (*a)->d_name and (*b)->d_name.

RETURN VALUE
       The scandir() function returns the number of directory entries selected or -1 if an error occurs.

       The  alphasort()  and versionsort() functions return an integer less than, equal to, or greater than zero if the first argument is considered to be respectively less than, equal to, or greater
       than the second.

ERRORS
       ENOENT The path in dirp does not exist.

       ENOMEM Insufficient memory to complete the operation.

       ENOTDIR
              The path in dirp is not a directory.

SYNOPSIS
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>

       int stat(const char *path, struct stat *buf);
       int fstat(int fd, struct stat *buf);
       int lstat(const char *path, struct stat *buf);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       lstat():
           _BSD_SOURCE || _XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED

DESCRIPTION
       These  functions return information about a file.  No permissions are required on the file itself, but—in the case of stat() and lstat() — execute (search) permission is required on all of the
       directories in path that lead to the file.

       stat() stats the file pointed to by path and fills in buf.

       lstat() is identical to stat(), except that if path is a symbolic link, then the link itself is stat-ed, not the file that it refers to.

       fstat() is identical to stat(), except that the file to be stat-ed is specified by the file descriptor fd.

       All of these system calls return a stat structure, which contains the following fields:

           struct stat {
               dev_t     st_dev;     // ID of device containing file 
               ino_t     st_ino;     // inode number 
               mode_t    st_mode;    // protection 
               nlink_t   st_nlink;   // number of hard links 
               uid_t     st_uid;     // user ID of owner 
               gid_t     st_gid;     // group ID of owner 
               dev_t     st_rdev;    // device ID (if special file) 
               off_t     st_size;    // total size, in bytes 
               blksize_t st_blksize; // blocksize for file system I/O 
               blkcnt_t  st_blocks;  // number of 512B blocks allocated 
               time_t    st_atime;   // time of last access 
               time_t    st_mtime;   // time of last modification 
               time_t    st_ctime;   // time of last status change 
           };
 */


//This code is ported from android media scanner 
//
int doProcessDirectoryEntry(char *path, int pathRemaining,struct dirent* entry, char* fileSpot);
int doProcessDirectory(char *path, int pathRemaining);
char *get_path_suffix(const char *file_path,char *suffix,int len);

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

int split_path_no_suffix(const char *file_path,char *file_main_path,int path_len ,char *file_name,int len){
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

