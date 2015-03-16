#include"Ref.h"

class Object :public Ref{
    public:
        Object(){
        }
};


int main(){
    Object a ;
    Object b = a;
    Object c = b;
    Object *ap = new Object();
    return 0;
}
