#include"AngelRef.h"
#include<stdio.h>


class A:public Ref{
    public :
    A(){
        angel_printfe("create a obj \n");
    }
    ~A(){
        angel_printfe("delete obj \n");
    }
};

int main(int argc,char **argv){
    //error using 
    //A t;
    //Sobj<A> a = &t ;

    A *b = new A();
    Sobj<A> y = b;

    Sobj<A> x = new A();

    return 0;
}
