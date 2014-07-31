#ifndef __MY_TEST_TOOLS__
#define __MY_TEST_TOOLS__
#include<pthread.h>

void* tools_malloc(int size,const char *file_name,int line);
void  tools_free(void *ptr);
char* tools_strdup( const char *str, const char*file_name, int line);
void  tools_get_leak_mem();
void  init_global_env();

#define malloc(n)       tools_malloc(n,__FILE__,__LINE__)
#define dupstr(p)         tools_strdup(p,__FILE__,__LINE__)
#define free(p)         tools_free(p)


#endif //__MY_TEST_TOOLS__


