#include"Ref.h"

class Object :public Ref{
    public:
        Object(){
        }
};


int main(){
    //Object *ap = new Object();
    Object a ;
    SimpleObject<Object> sa ;
    SimpleObject<Object> sb = a;
    SimpleObject<Object> sc = sa;
    return 0;
}
