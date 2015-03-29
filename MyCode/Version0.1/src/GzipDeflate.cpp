#include"GzipDeflate.h"
extern "C"{
#include"zlib.h"
}

#define IN_BUFFER_SIZE 0xffffL
#define OUT_BUFFER_SIZE 0xffffL


GzipDeflate::GzipDeflate(const char *path):file_path(path){
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
   int end = (mPos + len)/mCheckLength;
   if(end > mCheckCount -1){
       end = mCheckCount -1;
   }

   SimpleFile file_obj(file_path.string(),O_RDONLY);
   int i = 0;
   unsigned char *inBuff = new unsigned char[IN_BUFFER_SIZE];
   unsigned char *outBuff = new unsigned char[OUT_BUFFER_SIZE];
   unsigned char *ptrOut = buf;
   file_obj.Seek(SEEK_SET,mHeaderLength + mPos);
   for(i = mbegin ;i <=end ;i++){
       printf("*(mChunkArray + %d) = %d \n",i,*(mChunkArray + i));
       file_obj.Read(inBuff,*(mChunkArray + i)); 

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

       if(mbegin == i){
           if(mOffset > zStream.avail_out){
               printf("error mOffset > zStream.avail_out \n");
           }
           int cpylen = 0 ;
           if(len > zStream.avail_out - mOffset){
               cpylen = zStream.avail_out - mOffset;
           }else{
               //one chunk is ok
               cpylen = len;
           }
           memcpy(ptrOut,zStream.next_out + mOffset,cpylen);
           len -= cpylen;
           ptrOut += cpylen;
       }else{
           int cpylen = 0 ;
           if(len > zStream.avail_out){
               cpylen = zStream.avail_out;
           }else{
               cpylen = len;
           }
           memcpy(ptrOut,zStream.next_out,cpylen);
           len -= cpylen;
           ptrOut += cpylen;
       }
   }
}

int GzipDeflate::Seek(int where,int offset){
    if(where != SEEK_SET){
        return -1;
    }
    int mbegin = offset/mCheckLength;
    int i = 0;
    mOffset = offset - mbegin * mCheckLength;
    mPos = 0;
    while(i < mbegin){
        mPos += *(mChunkArray + i);
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
