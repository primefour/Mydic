#ifndef __GOLDEN_DICT_REF__
#define __GOLDEN_DICT_REF__
#include<stdio.h>
class Ref {
    public:
        Ref(){
            ref = 1;
            printf("ref = %d \n",ref);
        }

        Ref(const Ref & obj){
            ref = 1;
            printf("ref = %d \n",ref);
        }

        void get(){
            ref ++;
            printf("ref = %d \n",ref);
        }

        int put(){
            ref --;
            printf("ref = %d \n",ref);
            return ref ;
        }

        virtual ~Ref(){
            ref --;
            if(ref > 0){
                printf("leak error !\n");
            }else{
                printf("delete object! \n");
            }
        }
    private:
        int ref;
};
#endif
