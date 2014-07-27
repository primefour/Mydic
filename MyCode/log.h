#ifndef __DIC_LOG_H__
#define __DIC_LOG_H__
#include<stdio.h>

#define ALOGE(fmt,args...) printf("%s:%s:%d: " fmt,__FILE__, __func__, __LINE__,args)

#endif 
