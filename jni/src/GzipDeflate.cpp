#include"GzipDeflate.h"
extern "C"{
#include"zlib.h"
}

#define IN_BUFFER_SIZE 0xffffL
#define OUT_BUFFER_SIZE 0xffffL


GzipDeflate::GzipDeflate(const char *path,int mode):file_path(path){
    mPos = 0;
    GZipHeader header(path);
    header.getExtraInfo(mCheckCount,mCheckLength,mVersion);
    mChunkArray = new int[mCheckCount];
    memset(mChunkArray,0,mCheckCount * sizeof(int));
    int i = 0;
    while(i < mCheckCount){
        *(mChunkArray + i) = header.getChunkCode(i + 1);
        i ++;
    }
    mHeaderLength = header.getDataOffset();
}

int GzipDeflate::Read(unsigned char *buf,int len){
   z_stream zStream;

   zStream.zalloc    = NULL;
   zStream.zfree     = NULL;
   zStream.opaque    = NULL;
   zStream.next_in   = 0;
   zStream.avail_in  = 0;
   zStream.next_out  = NULL;
   zStream.avail_out = 0;

   if(inflateInit2(&zStream, -15 ) != Z_OK){
       printf("zStream init failed  \n");
   }
   int end = (mEnd + len)/mCheckLength;
   if(end > mCheckCount -1){
       end = mCheckCount -1;
   }
   printf("end = %d \n",end);

   SimpleFile file_obj(file_path.string(),O_RDONLY);
   int i = 0;
   int cpylen = 0 ;
   unsigned char *inBuff = new unsigned char[IN_BUFFER_SIZE];
   unsigned char *outBuff = new unsigned char[OUT_BUFFER_SIZE];
   unsigned char *ptrOut = buf;
   printf("mHeaderLength + mPos = %d mbegin = %d end = %d \n",mHeaderLength + mPos,mbegin,end);
   file_obj.Seek(SEEK_SET,mHeaderLength + mPos);
   for(i = mbegin ;i <=end ;i++){
       printf("*(mChunkArray + %d) = %d \n",i,*(mChunkArray + i));
       int ret = file_obj.Read(inBuff,*(mChunkArray + i)); 
       if(ret != *(mChunkArray + i)){
           printf("error read file failed \n");
       }

       zStream.next_in   = (Bytef* )inBuff;
       zStream.avail_in  = *(mChunkArray + i);

       zStream.next_out  = (Bytef* )outBuff;
       zStream.avail_out = OUT_BUFFER_SIZE;

       if(inflate(&zStream,Z_PARTIAL_FLUSH) != Z_OK){
           printf("inflate failed \n");
       }
       printf("zStream.avail_in = %d zStream.avail_out = %d mOffset = %d \n",zStream.avail_in,zStream.avail_out,mOffset );
       if(zStream.avail_in){
           printf("zstream flush mode failed \n");
       }
       int avail_content = OUT_BUFFER_SIZE - zStream.avail_out ;
       printf(" avail_content  = %d \n",avail_content); 
        //printf(" avail_content  = %s \n",outBuff ); 
       
       if(mbegin == i){
           if(mOffset > avail_content ){
               printf("error mOffset > (OUT_BUFFER_SIZE - zStream.avail_out)\n");
           }
           if(len > avail_content - mOffset){
               cpylen = avail_content - mOffset;
           }else{
               //one chunk is ok
               cpylen = len;
           }
           memcpy(ptrOut,outBuff + mOffset,cpylen);
           len -= cpylen;
           ptrOut += cpylen;
       }else{
           int cpylen = 0 ;
           if(len > avail_content){
               cpylen = avail_content ;
           }else{
               cpylen = len;
           }
           memcpy(ptrOut,outBuff,cpylen);
           len -= cpylen;
           ptrOut += cpylen;
       }
   }
   delete outBuff;
   delete inBuff;
   return cpylen;
}

int GzipDeflate::Seek(int where,int offset){
    if(where != SEEK_SET){
        return -1;
    }
    printf("offset = %d mCheckLength = %d \n",offset,mCheckLength);
    mbegin = offset/mCheckLength;
    int i = 0;
    mOffset = offset - mbegin * mCheckLength;
    mPos = 0;
    mEnd = 0;
    printf("mbegin  = %d \n",mbegin); 
    while(i < mbegin){
        mPos += *(mChunkArray + i);
        mEnd += mCheckLength;
        i++;
    }
    return mPos;
}

GzipDeflate::~GzipDeflate(){
    if(mChunkArray != NULL){
        delete mChunkArray ;
    }
    mChunkArray = NULL;
}

int GzipDeflate::ReadLine(unsigned char *buf,int len){
    return 0;
}
int GzipDeflate::ReadTerminating(unsigned char *buff,int len,unsigned char terminate){
    return 0;
}
