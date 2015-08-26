#ifndef __GOLDEN_ZIP_TOOL_H__
#define __GOLDEN_ZIP_TOOL_H__


class ZipEntry{
    String8 mName;
    unsigned int mSize;
    unsigned int mCrc;
    const char *string()const {
        return mName.string();
    }

};


class GoldenZipTool{
    public:
        GoldenZipTool(const char *file);
        GoldenZipTool(int fd);
    private:
        int CheckZipFile(int idx, zip_int64_t size, unsigned int crc);
        struct zip*  mZip
        ZipEntry *mPtrEntries;
        zip_uint64_t mEntryCount;
        DictHashSet<SObject<ZipEntry> > *mPtrEntryHash;
};


#endif
