#include"GoldenHashMapExt.h"
#include"String8.h"
#include<stdio.h>
#include<map>
using namespace std;

struct DictWordItem{
    DictWordItem(int t,int o){
        type = t;
        offset = o;
    }
    unsigned int type:4;
    unsigned int offset:28;
};

//typedef br_stl::HMap<long, std::string, br_stl::HashFun<long> > MapType


class defaultHashCode {
    public :
        int operator()(const String8 &key){
            unsigned int val;
            val = 0;
            const char *ptr = key.string();
            while (*ptr != '\0') {
                unsigned int tmp;
                val = (val << 4) + (*ptr);
                if (tmp = (val & 0xf0000000)) {
                    val = val ^ (tmp >> 24);
                    val = val ^ tmp;
                }
                ptr++;
            }
            return val ;
        }
};

typedef HashMapExt<String8,DictWordItem,defaultHashCode,1000> HMAPType;

int main(int argc,char **argv){
    //HMAPType *hme  = new HMAPType();

    HMAPType hme; 
    map<String8,DictWordItem> kkmap;
    const char *hello = "hello" ;
    String8 Hello(hello);
    DictWordItem item(3,4);
    //hme->insert(Hello,item);
    //list<DictWordItem> dlist = hme->find(Hello);
    //
    pair<String8,DictWordItem> pitem(Hello,item);
    kkmap.insert(pitem);

    hme.insert(Hello,item);
    list<DictWordItem> dlist = hme.find(Hello);
    printf("dlist->size()  = %ld  \n",dlist.size());

    return 0;
}
