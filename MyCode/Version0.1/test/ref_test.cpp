#include"Ref.h"

class Object :public Ref{
    public:
        Object(){
        }
};


int main(){
    //Object *ap = new Object();
    Object *a = new Object() ;
    SimpleObject<Object> sa ;
    SimpleObject<Object> sb(a);
    SimpleObject<Object> sc = sa;
    a->put();
    return 0;
}
