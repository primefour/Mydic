#include"HashSet.h"
#include<list>
#include<vector>


using namespace std;

class tt{
    public:
        tt(){
        }
        const char * string(){
            return "ehllo world";
        }
};




int hashFunction(const int *item){
    return 0;
}

int main(){
    DictHashSet<int> as(100);
    DictHashSet<int> ask(100,hashFunction);
    int a = 0;
    as.DictHashInsert(a);
    return 0;
}
