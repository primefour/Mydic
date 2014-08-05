#ifndef __DIRECTORY_UTILS_H__
#define __DIRECTORY_UTILS_H__
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

    virtual MediaScanResult processFile(const char *path, const char *mimeType);
    virtual MediaScanResult processDirectory(const char *path);
    MediaScanResult doProcessDirectory(char *path, int pathRemaining);
    MediaScanResult doProcessDirectoryEntry(char *path, int pathRemaining,struct dirent* entry, char* fileSpot);
};


#endif
