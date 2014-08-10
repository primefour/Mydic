#include<stdio.h>
class A{
    public:
        virtual void print(){
            printf("hello world a\n");
        }
        void printa(){
            printf("Hello world ta\n");
        }
};

class B :public A{
    public:
        virtual void print(){
            printf("hello world b\n");
        }

};


class C:public A{
    public:
        
};


int main(){
    class A *ptr = new A();

    ptr->print();
    ptr = new B();

    ptr->print();
    
    ptr = new C();
    ptr->print();
    class C *cptr = new C();
    cptr->print();

    ptr->printa();
    cptr->printa();
}
