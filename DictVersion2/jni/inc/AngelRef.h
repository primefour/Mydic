#ifndef __ANGEL_REF_H__
#define __ANGEL_REF_H__ 
#include"AngelLog.h"
#include<assert.h>

class Ref {
    public:
        Ref(){
            mRef = 0;
        }

        Ref(const Ref & ins){
            mRef = 0;
        }

        int get(){
            mRef ++;
            return mRef;
        }


        int put(){
            mRef --;
            return mRef;
        }

        virtual ~Ref(){
            if(mRef != 0){
                angel_printfe("Remove Object Error \n");
            }else{
                angel_printfe("ref = %d Object \n",mRef);
            }
        }

    private:
        int mRef ;
};


template<typename T> 
class Sobj{
    public:
        //constructor
        Sobj(){
            mObj = NULL;
        }
        Sobj(T *obj){
            if(obj != NULL){
                mObj = obj;
                mObj->get();
            }
        }

        //copy constructor
        Sobj(const Sobj<T> &ins){
            mObj = ins.mObj ;
            assert(mObj != NULL);
            mObj->get();
        }

        //destrutor
        virtual ~Sobj(){
            int ref = mObj->put();
            angel_printfe("##ref = %d \n",ref);
            if(ref == 0){
                delete mObj ;
                mObj = NULL;
            }
        }


        //operator overide
        const Sobj<T>& operator=(const Sobj<T> & ins) const {
            if(mObj){
                int ref = mObj->put();
                if(ref == 0){
                    delete mObj;
                }
            }
            assert(ins.mObj != NULL);
            mObj = ins.mObj;
            mObj->get();
            return *this;
        }


        Sobj<T>& operator=(Sobj<T> & ins) {
            if(mObj){
                int ref = mObj->put();
                if(ref == 0){
                    delete mObj;
                }
            }
            assert(ins.mObj != NULL);
            mObj = ins.mObj;
            mObj->get();
            return *this;
        }

        //operator overide
        const Sobj<T>& operator=(const T *p) const {
            if(mObj){
                int ref = mObj->put();
                if(ref == 0){
                    delete mObj;
                }
            }
            assert(p != NULL);
            mObj = p ;
            mObj->get();
            return *this;
        }


        Sobj<T>& operator=( T *p) {
            if(mObj){
                int ref = mObj->put();
                if(ref == 0){
                    delete mObj;
                }
            }
            assert(p != NULL);
            mObj = p ;
            mObj->get();
            return *this;
        }

        const T* operator->() const {
            return mObj;
        }

        T* operator->(){
            return mObj;
        }

        bool operator==(const Sobj<T> &ins){
            return (*mObj == *(ins.mObj));
        }

    private :
        T *mObj;
};

#endif 
