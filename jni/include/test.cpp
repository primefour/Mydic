#include"HashSet.h"
#include<list>
#include<vector>
#include<stdio.h>
#include"GoldenDictLog.h"

using namespace std;

class tt{
    public:
        tt(){
        }
        const char * string() const{
            return "ehllo world";
        }
        bool operator==(const tt & ins){
            return true;
        }
};




int hashFunction(const tt*item){
    return 0;
}

int main(){
    /*
    DictHashSet<tt> as(100);
    DictHashSet<tt> ask(100,hashFunction);
    tt a;
    as.DictHashInsert(a);
    */
    vector<list<int> > a(10,list<int>());

    golden_printfd("size = %d capicity = %d \n",a.size(),a.capacity());
    int i = 0;
    golden_printfd("empty = %d size = %d \n",a[0].empty(),a[0].size());
    a[0].push_back(1);
    a[0].push_back(1);
    golden_printfd("empty = %d size = %d \n",a[0].empty(),a[0].size());

    return 0;
}
