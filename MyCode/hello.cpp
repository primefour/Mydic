#include<stdio.h>


RefBase{
    public :
        RefBase(){
            mRef ++;
        }
        RefBase(const RefBase & b){
            mRef ++;
        }

    private :
        int mRef;
    
}


class test{
    public :
    test(){
        printf("test default construct\n");
    }
    test(const test &a){
        printf("test copy construct \n");
    }
    ~test(){
        printf("test default deconstruct\n");
    }
    void operator=(const test &a){
        printf("test operator = & \n");
        //return *this;
    }

    void operator=(const test *a){
        printf("test operator = * \n");
        //return *this;
    }
    bool operator==(const test &c){
        printf("test operator == \n");
        return 1;
    }
    void setvalue(int a){
        value = a;
    }
    int value ;
};

template <class T>
class hello {
    hello(T b){
    }
};


void get_item(test & h){

}

void get_item_kk(test h){

}


test item(){
    test *hello = (new test());
    return *hello;
}


int main(){
    test *a = new test();
    a->setvalue(1);
    test b = *a;
    printf("b = %d\n",b.value);

    test c = b ;

    printf("c = %d \n",c.value);

    b = c ;
    
    printf("b = %d\n",b.value);
    b = a;

    printf("b = %d\n",b.value);
    get_item_kk(b);
    get_item(b);

    printf("hello world \n");
    test d = item();
    //test *p = & item();
    printf("hello world end \n");
    delete a;
    return 0;
}
