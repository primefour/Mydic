#include<stdio.h>
extern "C"{
#include"zlib.h"
}


int hello(){

   z_stream zStream;

   zStream.zalloc    = NULL;
   zStream.zfree     = NULL;
   zStream.opaque    = NULL;
   zStream.next_in   = 0;
   zStream.avail_in  = 0;
   zStream.next_out  = NULL;
   zStream.avail_out = 0;
   inflateInit2(&zStream, -15 ); 
   return 0;
}
