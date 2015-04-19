#ifndef __MY_DICT_STACK_H__
#define __MY_DICT_STACK_H__
#include"list.h"

template <class T >
class Stack{
    public:
        Stack();
        T Pop();
        void Push(T& data);
        T& getHeader();
        bool isEmpty();

    private:
        List<T> mList;
};

template<class T>
Stack<T>::Stack(){

}

template<class T>
T Stack<T>::Pop(){
    if(isEmpty()){
        mHeader.get
    }
}





#endif 
