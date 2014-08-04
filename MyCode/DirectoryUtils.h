#ifndef __DIRECTORY_UTILS_H__
#define __DIRECTORY_UTILS_H__
void scan_directory_with_suffix(const char *path,const char *suffix,char **file_list);
void scan_directory_with_prefix(const char *path,const char *prefix,char **file_list);

enum MediaScanResult {
    // This file or directory was scanned successfully.
    MEDIA_SCAN_RESULT_OK,
    // This file or directory was skipped because it was not found, could
    // not be opened, was of an unsupported type, or was malfored in some way.
    MEDIA_SCAN_RESULT_SKIPPED,
    // The scan should be aborted due to a fatal error such as out of memory
    // or an exception.
    MEDIA_SCAN_RESULT_ERROR,
};

struct MediaScanner {
    MediaScanner();
    virtual ~MediaScanner();

    virtual MediaScanResult processFile(
            const char *path, const char *mimeType, MediaScannerClient &client) = 0;

    virtual MediaScanResult processDirectory(
            const char *path, MediaScannerClient &client, bool isScanMediaFile = false, bool isNoMedia = false,  int layer = -1);

    void setLocale(const char *locale);

    // extracts album art as a block of data
    virtual char *extractAlbumArt(int fd) = 0;
    void setMediaFileExtension(const char *extensions);
    void setIgnoreList(const char *sIgnoreList); // fengjen - set ignore folder list 
    void clearIgnoreList(); // fengjen - set ignore folder list 
protected:
    const char *locale() const;

private:
    // current locale (like "ja_JP"), created/destroyed with strdup()/free()
    char *mLocale;
    char *mSkipList;
    int *mSkipIndex;

    MediaScanResult doProcessDirectory(
            char *path, int pathRemaining, MediaScannerClient &client, bool isScanMediaFile, bool noMedia, int layer);
    MediaScanResult doProcessDirectoryEntry(
            char *path, int pathRemaining, MediaScannerClient &client, bool isScanMediaFile, bool noMedia, int layer,
            struct dirent* entry, char* fileSpot);
    void loadSkipList();
    bool shouldSkipDirectory(char *path);
    bool shouldIgnoreDirectory(char *path); // fengjen - set ignore folder list 


    MediaScanner(const MediaScanner &);
    MediaScanner &operator=(const MediaScanner &);

    //Scan file(first time scan media file and second time scan non-media file), 2012.01.12, U17 fengjen++ 
    bool fileMatchesExtension(const char* path,  bool isScanMediaFile);
    unsigned int hashCode( const char* extension, int length );
    void hashtable(const char* extension );
    android::KeyedVector<unsigned int, char*> m_mmExtension; ///< Loaded Extension data. Key is the hash code of file type
    //Scan file(first time scan media file and second time scan non-media file), 2012.01.12, U17 fengjen--

    /* >> fengjen - set ignore folder list */
    android::Vector<String8> m_mmIgnoreList;
    /* << fengjen - set ignore folder list */
	
};

class MediaScannerClient
{
public:
    MediaScannerClient();
    virtual ~MediaScannerClient();
    void setLocale(const char* locale);
    void beginFile();
    status_t addStringTag(const char* name, const char* value);
    void endFile();

    virtual status_t scanFile(const char* path, long long lastModified,
            long long fileSize, bool isDirectory, bool noMedia) = 0;
    virtual status_t handleStringTag(const char* name, const char* value) = 0;
    virtual status_t setMimeType(const char* mimeType) = 0;

protected:
    void convertValues(uint32_t encoding, int index); 

    // cached name and value strings, for native encoding support.
    StringArray*    mNames;
    StringArray*    mValues;

    // default encoding based on MediaScanner::mLocale string
    uint32_t        mLocaleEncoding;
};

}; // namespace android

#endif
