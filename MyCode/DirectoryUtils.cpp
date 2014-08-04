#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
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
 */

void scan_directory_with_suffix(const char *path,const char *suffix,char **file_list){
    readdir
}

void scan_directory_with_prefix(const char *path,const char *prefix,char **file_list){

}
