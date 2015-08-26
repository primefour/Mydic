#include "GoldenZipTool.h"
#include<stdexcept>


GoldenZipTool::GoldenZipTool(const char *file){
    struct zip_stat st;
    char errstr[1024];
    int err;
	if ((mZip =zip_open(file,ZIP_RDONLY|ZIP_CHECKCONS, &err)) == NULL) {
	    zip_error_to_str(errstr, sizeof(errstr), err, errno);
	    fprintf(stderr, "%s: cannot open zip archive : %s\n",file,errstr);
        throw exception();//"file open error");
	}
    mEntryCount = zip_get_num_entries(mZip,0);
    if(mEntryCount != 0){
        mPtrEntryHash = new DictHashSet<SObject<ZipEntry> >(mEntryCount);
        mPtrEntries = new ZipEntry[mEntryCount];

    }else{
        printf("No Entry \n");
        throw exception();//"file open error");
    }
    int j = 0;
    for(j=0; j< mEntryCount ; j++) {
        zip_stat_index(mZip,j,0,&st);
        (mPtrEntries +j)->mName = st.name;
        (mPtrEntries +j)->mSize = st.size;
        (mPtrEntries +j)->mCrc= st.crc;
        mPtrEntryHash->DictHashInsert(SObject(mPtrEntries +j));
    }
}

bool GoldenZipTool::IsExist(const char *infile){
    if(infile == NULL){
        return false ;
    }else{
        SObject<ZipEntry> tmp = new ZipEntry();
        tmp->mName = infile;
        return mPtrEntryHash->DictHashfind(tmp)
    }
}


int GoldenZipTool::OpenInFile(const char *infile){
    if(IsExist(infile)){
        SObject<ZipEntry> tmp = new ZipEntry();
        tmp->mName = infile;
        const SObject<ZipEntry>&target = mPtrEntryHash->DictHashGet(tmp);

    }
}


int GoldenZipTool::ReadInFile(const char *infile,char *buff,int lenght){

}




int GoldenZipTool::CheckZipFile(int idx, zip_int64_t size, unsigned int crc){
    struct zip_file *zf;
    char buf[8192];
    zip_int64_t n, nsize;
    zip_uint32_t ncrc;

    if ((zf=zip_fopen_index(mZip, idx, 0)) == NULL) {
        fprintf(stderr, "cannot open file %d in archive: %s\n", idx, zip_strerror(za));
        return -1;
    }
    ncrc = (zip_uint32_t)crc32(0, NULL, 0);
    nsize = 0;

    while ((n=zip_fread(zf, buf, sizeof(buf))) > 0) {
        nsize += n;
        ncrc = (zip_uint32_t)crc32(ncrc, (const Bytef *)buf, (unsigned int)n);
    }

    if (n < 0) {
        fprintf(stderr, "error reading file %d in archive: %s\n",idx, zip_file_strerror(zf));
        zip_fclose(zf);
        return -1;
    }

    zip_fclose(zf);

    if (nsize != size) {
        fprintf(stderr, "file %d: unexpected length %" PRId64 " (should be %" PRId64 ")\n",idx, nsize, size);
        return -2;
    }
    if (ncrc != crc) {
        fprintf(stderr, "file %d: unexpected length %x (should be %x)\n",idx, ncrc, crc);
        return -2;
    }

    return 0;
}
