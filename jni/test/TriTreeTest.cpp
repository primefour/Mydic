#include"GoldenTriTree.h"
#include<string.h>
#include<stdio.h>


class String8 {
    public:
        class iterator {
            public:
                iterator(char *data){
                    ptr = data;
                }
                iterator& operator++(){
                    ptr ++;
                    return *this;
                }
                iterator operator++(int){
                    iterator tmp(*this);
                    ptr ++;
                    return tmp;
                }
                bool operator==(const iterator &t){
                    return t.ptr == ptr;
                }
                bool operator!=(const iterator &t){
                    return ptr != t.ptr;
                }

                char& operator*(){
                    return *ptr;
                }

            private:
               char *ptr; 
        };

        String8(const char *data):mdata(strdup(data)),mBegin(mdata),mEnd(mdata+strlen(mdata)){

        }

        String8::iterator& begin(){
            return mBegin;
        }

        String8::iterator& end(){
            return mEnd;
        }

    private :
        char *mdata;
        String8::iterator mBegin;
        String8::iterator mEnd;
};

int main(int argc,char **argv){
    TriTree<String8,char,int> Root;
    String8 tmp = String8("hello");
    Root.InsertData(tmp);
    String8 kk = String8("he");
    if(Root.FindData(tmp) != NULL){
        printf("find data \n");
    }

    if(Root.FindData(kk) != NULL){
        printf("find data \n");
    }

    String8 kkk = String8("world");

    if(Root.FindData(kkk) != NULL){
        printf("find data \n");
    }

    return 0;
}

