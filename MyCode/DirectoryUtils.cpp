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




static int filter_with_suffix(const struct dirent *entry,const char *suffix){
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

void scan_directory_with_suffix(const char *path,const char *suffix,char **file_list){
    dirent read_entry ={0};
    if(path != NULL){

    }

    int ret = readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);
    while(ret != 0){


        memset(&read_entry,0,sizeof(read_entry));
        ret = readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);
    }

}

void scan_directory_with_prefix(const char *path,const char *prefix,char **file_list){

}



MediaScanner::MediaScanner()
    : mLocale(NULL), mSkipList(NULL), mSkipIndex(NULL) {
    loadSkipList();
}

MediaScanner::~MediaScanner() {
    setLocale(NULL);
    free(mSkipList);
    free(mSkipIndex);
}

void MediaScanner::setLocale(const char *locale) {
    if (mLocale) {
        free(mLocale);
        mLocale = NULL;
    }
    if (locale) {
        mLocale = strdup(locale);
    }
}

const char *MediaScanner::locale() const {
    return mLocale;
}

void MediaScanner::loadSkipList() {
    mSkipList = (char *)malloc(PROPERTY_VALUE_MAX * sizeof(char));
    if (mSkipList) {
        property_get("testing.mediascanner.skiplist", mSkipList, "");
    }
    if (!mSkipList || (strlen(mSkipList) == 0)) {
        free(mSkipList);
        mSkipList = NULL;
        return;
    }
    mSkipIndex = (int *)malloc(PROPERTY_VALUE_MAX * sizeof(int));
    if (mSkipIndex) {
        // dup it because strtok will modify the string
        char *skipList = strdup(mSkipList);
        if (skipList) {
            char * path = strtok(skipList, ",");
            int i = 0;
            while (path) {
                mSkipIndex[i++] = strlen(path);
                path = strtok(NULL, ",");
            }
            mSkipIndex[i] = -1;
            free(skipList);
        }
    }
}

MediaScanResult MediaScanner::processDirectory(
        const char *path, MediaScannerClient &client, bool isScanMediaFile, bool isNoMedia, int layer) {
    int pathLength = strlen(path);
    if (pathLength >= PATH_MAX) {
        return MEDIA_SCAN_RESULT_SKIPPED;
    }
    char* pathBuffer = (char *)malloc(PATH_MAX + 1);
    if (!pathBuffer) {
        return MEDIA_SCAN_RESULT_ERROR;
    }

    int pathRemaining = PATH_MAX - pathLength;
    strcpy(pathBuffer, path);
    if (pathLength > 0 && pathBuffer[pathLength - 1] != '/') {
        pathBuffer[pathLength] = '/';
        pathBuffer[pathLength + 1] = 0;
        --pathRemaining;
    }

    MediaScanResult result = doProcessDirectory(pathBuffer, pathRemaining, client, isScanMediaFile, isNoMedia, layer);

    free(pathBuffer);

    return result;
}

bool MediaScanner::shouldSkipDirectory(char *path) {
    if (path && mSkipList && mSkipIndex) {
        int len = strlen(path);
        int idx = 0;
        // track the start position of next path in the comma
        // separated list obtained from getprop
        int startPos = 0;
        while (mSkipIndex[idx] != -1) {
            // no point to match path name if strlen mismatch
            if ((len == mSkipIndex[idx])
                // pick out the path segment from comma separated list
                // to compare against current path parameter
                && (strncmp(path, &mSkipList[startPos], len) == 0)) {
                return true;
            }
            startPos += mSkipIndex[idx] + 1; // extra char for the delimiter
            idx++;
        }
    }
    return false;
}

bool MediaScanner::fileMatchesExtension(const char* path, bool isScanMediaFile) {
    char* extension = strrchr(path, '.');
	int index;
	bool result;

    if (!extension) return (!isScanMediaFile);
    ++extension;    // skip the dot
    if (extension[0] == 0) return (!isScanMediaFile);

	//Scan file(first time scan media file and second time scan non-media file), 2012.01.12, U17 fengjen++
	int size = strlen(extension);
	char buf[size];
	
    for (int i=0; i < size; ++i)
    {
        buf[i] = toupper( extension[i] );
    }

	const unsigned int pathhashcode = hashCode( buf , size);

	index = m_mmExtension.indexOfKey(pathhashcode);
	if(index < 0)
	   result = false;
	else 
           result = true;

	if (isScanMediaFile)
	    return result;
	else
	    return !result;
	//Scan file(first time scan media file and second time scan non-media file), 2012.01.12, U17 fengjen--
}

MediaScanResult MediaScanner::doProcessDirectory(
        char *path, int pathRemaining, MediaScannerClient &client, bool isScanMediaFile, bool noMedia, int layer) {
    // place to copy file or directory name
    char* fileSpot = path + strlen(path);
    struct dirent* entry;

    if (shouldSkipDirectory(path)) {
        ALOGD("Skipping: %s", path);
        return MEDIA_SCAN_RESULT_OK;
    }

    // Treat all files as non-media in directories that contain a  ".nomedia" file
    if (pathRemaining >= 8 /* strlen(".nomedia") */ ) {
        strcpy(fileSpot, ".nomedia");
        if (access(path, F_OK) == 0) {
            ALOGV("found .nomedia, setting noMedia flag");
            noMedia = true;
        }

        // restore path
        fileSpot[0] = 0;
    }

    DIR* dir = opendir(path);
    if (!dir) {
        ALOGW("Error opening directory '%s', skipping: %s.", path, strerror(errno));
        return MEDIA_SCAN_RESULT_SKIPPED;
    }

    MediaScanResult result = MEDIA_SCAN_RESULT_OK;
    while ((entry = readdir(dir))) {
        if (doProcessDirectoryEntry(path, pathRemaining, client, isScanMediaFile, noMedia, layer, entry, fileSpot)
                == MEDIA_SCAN_RESULT_ERROR) {
            result = MEDIA_SCAN_RESULT_ERROR;
            break;
        }
    }
    closedir(dir);
    return result;
}

MediaScanResult MediaScanner::doProcessDirectoryEntry(
        char *path, int pathRemaining, MediaScannerClient &client, bool isScanMediaFile, bool noMedia, int layer,
        struct dirent* entry, char* fileSpot) {
    struct stat statbuf;
    const char* name = entry->d_name;

    // ignore "." and ".."
    if (name[0] == '.' && (name[1] == 0 || (name[1] == '.' && name[2] == 0))) {
        return MEDIA_SCAN_RESULT_SKIPPED;
    }

    int nameLength = strlen(name);
    if (nameLength + 1 > pathRemaining) {
        // path too long!
        return MEDIA_SCAN_RESULT_SKIPPED;
    }
    strcpy(fileSpot, name);

    /* >> fengjen - set ignore folder list */
    if (shouldIgnoreDirectory(path)) {
	ALOGD("Ignore path: %s", path);
	return MEDIA_SCAN_RESULT_OK;
    }
    /* << fengjen - set ignore folder list */

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
            ALOGD("stat() failed for %s: %s", path, strerror(errno) );
        }
    }
    
    if (layer > 0 || layer == -1) { // fengjen - Enhance MTP scan 1-level performance
	if (layer > 0)
	   layer --;
        if (type == DT_DIR) {
            bool childNoMedia = noMedia;
            // set noMedia flag on directories with a name that starts with '.'
            // for example, the Mac ".Trashes" directory
            if (name[0] == '.')
                childNoMedia = true;

            // report the directory to the client
            if (stat(path, &statbuf) == 0) {
                status_t status = client.scanFile(path, statbuf.st_mtime, 0,
                    true /*isDirectory*/, childNoMedia);
                if (status) {
                    return MEDIA_SCAN_RESULT_ERROR;
                }
            }

            // and now process its contents
            strcat(fileSpot, "/");
            MediaScanResult result = doProcessDirectory(path, pathRemaining - nameLength - 1,
	                client, isScanMediaFile, childNoMedia, layer);
            if (result == MEDIA_SCAN_RESULT_ERROR) {
                return MEDIA_SCAN_RESULT_ERROR;
            }
        } else if ((type == DT_REG)&&(fileMatchesExtension(path, isScanMediaFile))) {
            stat(path, &statbuf);
            status_t status = client.scanFile(path, statbuf.st_mtime, statbuf.st_size,
                false /*isDirectory*/, noMedia);
            if (status) {
                return MEDIA_SCAN_RESULT_ERROR;
            }
       }
    }
    return MEDIA_SCAN_RESULT_OK;
}

//Scan file(first time scan media file and second time scan non-media file), 2012.01.12, U17 fengjen++
unsigned int MediaScanner::hashCode( const char* extension, int length )
{
	if ( extension == 0 )
	{
		return 0;
	}

	// An algorithm produced by Professor Daniel J. Bernstein
	// One of the most efficient hash functions ever published.
	unsigned int nHash = 5381;
	unsigned int n = *extension;
	unsigned int position = 0;
		
	if ( n == 0 )
	{
	    return 0;
	}

	for ( ;
		  ((n != 0) && (n != 44) && (position < length ));
		  n = *(++extension), position++ )
	{
	    nHash = ((nHash << 5) + nHash) + n;
	}

	return (nHash & 0x7FFFFFFF);
}

void MediaScanner::hashtable(const char* extensions )
{
    while (extensions[0]) {
	char* comma = strchr(extensions, ',');
	size_t length = (comma ? comma - extensions : strlen(extensions));
		
	const unsigned int hash = hashCode( extensions, length );

	// Add new value
	m_mmExtension.add( hash, " " );

	extensions += length;

	if (extensions[0] == ',') ++extensions;
    }
}

void MediaScanner::setMediaFileExtension(const char *extensions){

    if(m_mmExtension.isEmpty())
	hashtable( extensions);
	
}
//Scan file(first time scan media file and second time scan non-media file), 2012.01.12, U17 fengjen--

/* >> fengjen - set ignore folder list */
bool MediaScanner::shouldIgnoreDirectory(char *path) {
    int length = 0;
    String8 tmpStr;
    for (int i = 0; i < m_mmIgnoreList.size(); i++){
	 tmpStr = m_mmIgnoreList.itemAt(i);
	 length = tmpStr.length();
	 if (!strncasecmp(path, m_mmIgnoreList.itemAt(i).string(), length))
	     return true;
    }
    return false;
}

void MediaScanner::setIgnoreList(const char *sIgnoreList){
    if(sIgnoreList == NULL)
       return;

    String8 ignorePath(sIgnoreList); 
    m_mmIgnoreList.push(ignorePath);
}

void MediaScanner::clearIgnoreList(){
    m_mmIgnoreList.clear();
}
/* << fengjen - set ignore folder list */

