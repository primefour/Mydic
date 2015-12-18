#include"GoldenTriTree.h"
#include<string.h>
#include<stdio.h>

class TriString8 {
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

        TriString8(const char *data):mdata(strdup(data)),mBegin(mdata),mEnd(mdata+strlen(mdata)){
        }

        TriString8::iterator& begin(){
            return mBegin;
        }

        TriString8::iterator& end(){
            return mEnd;
        }
    private :
        char *mdata;
        TriString8::iterator mBegin;
        TriString8::iterator mEnd;
};

struct TriLeaves{
        TriLeaves(int offset,int size){
            this->offset = offset;
            this->size = size;
        }

        bool operator==(const TriLeaves &dd) const {
            return dd.offset == offset && dd.size== size;
        }

        int offset ;
        int size;
};


int main(int argc,char **argv){
    TriTree<TriString8,char,TriLeaves> Root;
    TriString8 tmp = TriString8("hello");
    TriNode<char,TriLeaves>* tmp_node = Root.InsertData(tmp);
    TriLeaves tl(100,3);
    tmp_node->InsertLeaves(tl);

    TriNode<char,TriLeaves> *kk = Root.FindData(tmp);
    vector<TriLeaves> tt = kk->GetLeaves();

    vector<TriLeaves>::iterator begin = tt.begin();
    vector<TriLeaves>::iterator end = tt.end();
    while(begin != end) {
        printf("offset = %d idx = %d  \n",begin->offset,begin->idx);
        begin ++;
    }

    return 0;
}

