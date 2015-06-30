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




int hashFunction(tt *item){
    return 0;
}

int main(){
    DictHashSet<tt> as(100);
    DictHashSet<tt> ask(100,hashFunction);
    return 0;
}
