#ifndef __MY_TEST_TOOLS__
#define __MY_TEST_TOOLS__
#include<pthread.h>

void* tools_malloc(int size,const char *file_name,int line);
void  tools_free(void *ptr,const char *file,int line );
char* tools_strdup( const char *str, const char*file_name, int line);
void  init_global_env();
void  release_global_env();

#define malloc(n)       tools_malloc(n,__FILE__,__LINE__)
#define strdup(p)       tools_strdup(p,__FILE__,__LINE__)
#define free(p)         tools_free(p,__FILE__,__LINE__)




#endif //__MY_TEST_TOOLS__


