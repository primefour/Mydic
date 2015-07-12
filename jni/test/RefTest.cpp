#include"GoldenRef.h"
#include"GoldenDictLog.h"

class B:public Ref{
    public:
    B(){
        golden_printfd("B create \n");
    }
    B(const B &t){
        golden_printfd("B copy create \n");
    }
    ~B(){
        golden_printfd("B destroy\n");
    }
    int a;
};

int main(){
    SObject<B> T = NULL;
    B *p = new B();
    T = p;
    (*T).a = 3;
    T->a = 4;
    return 0;
}
