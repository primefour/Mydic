#include "GoldenZipTool.h"

#include<stdexcept>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <zlib.h>

#ifndef HAVE_GETOPT
#include "getopt.h"
#endif
#include "zip.h"
#include "GoldenStandardIO.h"

GoldenZipTool::GoldenZipTool(const char *file):mPtrEntries(NULL){
    struct zip_stat st;
    char errstr[1024];
    int err;
	if ((mZip =zip_open(file,ZIP_CHECKCONS, &err)) == NULL) {
	    zip_error_to_str(errstr, sizeof(errstr), err, errno);
	    fprintf(stderr, "%s: cannot open zip archive : %s\n",file,errstr);
        throw exception();//"file open error");
	}
    mEntryCount = zip_get_num_entries(mZip,0);
    if(mEntryCount != 0){
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
        angel_printfe("%d  ==> %s  \n",j,(mPtrEntries +j)->mName.string());
    }
}

bool GoldenZipTool::IsExist(const char *infile){
    if(infile == NULL){
        return false ;
    }else{
        ZipEntry *tmp = mPtrEntries ;
        int i = 0 ;
        for(i = 0;i < mEntryCount;i++,tmp ++){
            if(strcmp(infile,tmp->mName) == 0){
                return true;
            }
        }
        return false;
    }
}


void GoldenZipTool::ReleaseAllFiles(){
    ZipEntry *tmp = mPtrEntries ;
    int i = 0 ;
    for(i = 0;i < mEntryCount;i++,tmp ++){
        GetInFile(tmp->mName,tmp->mName);
    }
}





int GoldenZipTool::GetInFile(const char *infile,char *buff,int len){
    assert(buff != NULL);
    ZipEntry *tmp = mPtrEntries ;
    int i = 0 ;
    for(i = 0;i < mEntryCount;i++,tmp ++){
        if(strcmp(infile,tmp->mName) == 0){
            break;
        }
    }

    //no this file
    if(i == mEntryCount){
        return -1; 
    }
    struct zip_file *ZipInfile;

    if ((ZipInfile =zip_fopen(mZip,infile,0)) == NULL) {
        printf("%s: cannot open file in archive: %s\n",infile,zip_strerror(mZip));
        return -1;
    }

    int n = 0;
    char *temp = buff;
    while (len > 0 && (n=zip_fread(ZipInfile,temp,len)) > 0) {
        temp += n;
        len -= n;
    }

    zip_fclose(ZipInfile);
    return temp - buff;
}

int GoldenZipTool::GetInFile(const char *infile,const char *outputFile){
    ZipEntry *tmp = mPtrEntries ;
    int i = 0 ;
    for(i = 0;i < mEntryCount;i++,tmp ++){
        if(strcmp(infile,tmp->mName) == 0){
            break;
        }
    }
    //no this file
    if(i == mEntryCount){
        return -1; 
    }

    struct zip_file *ZipInfile;
    SimpleFile wfile(outputFile,O_CREAT|O_TRUNC|O_EXCL|O_RDWR);
    int fSize = 0;
    const int buff_len = 1024;
    char *buff = new char[buff_len];

    if ((ZipInfile =zip_fopen(mZip,infile,0)) == NULL) {
        printf("%s: cannot open file in archive: %s\n",infile,zip_strerror(mZip));
        return -1;
    }

    int n = 0;
    while ((n=zip_fread(ZipInfile,buff,buff_len)) > 0) {
        wfile.Write((unsigned char *)buff,n);
        fSize += n;
    }
    zip_fclose(ZipInfile);
    delete[] buff;
    return 0;
}



int GoldenZipTool::CheckZipFile(int idx, zip_int64_t size, unsigned int crc){
    struct zip_file *zf;
    char buf[8192];
    zip_int64_t n, nsize;
    zip_uint32_t ncrc;

    if ((zf=zip_fopen_index(mZip, idx, 0)) == NULL) {
        printf("cannot open file %d in archive: %s\n", idx, zip_strerror(mZip));
        return -1;
    }
    ncrc = (zip_uint32_t)crc32(0, NULL, 0);
    nsize = 0;

    while ((n=zip_fread(zf, buf, sizeof(buf))) > 0) {
        nsize += n;
        ncrc = (zip_uint32_t)crc32(ncrc, (const Bytef *)buf, (unsigned int)n);
    }

    if (n < 0) {
        printf("error reading file %d in archive: %s\n",idx, zip_file_strerror(zf));
        zip_fclose(zf);
        return -1;
    }

    zip_fclose(zf);

    if (nsize != size) {
        printf("file %d: unexpected length %ld (should be %ld)\n",idx, nsize, size);
        return -2;
    }
    if (ncrc != crc) {
        printf("file %d: unexpected length %x (should be %x)\n",idx, ncrc, crc);
        return -2;
    }

    return 0;
}


GoldenZipTool::~GoldenZipTool(){
    if(mZip != NULL){
        zip_close(mZip);
    }
    if(mPtrEntries != NULL){
        delete[] mPtrEntries;
    }
}
