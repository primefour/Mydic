#ifndef __GOLDEN_DICT_REF__
#define __GOLDEN_DICT_REF__
#include<stdio.h>
#include"GoldenDictLog.h"

class Ref {
    public:
        Ref(){
            ref = 0;
            golden_printfd("ref() ref = %d \n",ref);
        }

        Ref(const Ref & obj){
            ref = 0;
            golden_printfd("ref (obj) ref = %d \n",ref);
        }

        void get(){
            ref ++;
            golden_printfd("get ref = %d \n",ref);
        }

        int put(){
            ref --;
            golden_printfd("put ref = %d \n",ref);
            return ref ;
        }

        virtual ~Ref(){
            ref --;
            if(ref > 0){
                golden_printfd("~ref leak error !\n");
            }else{
                golden_printfd("~ref delete object! \n");
            }
        }
    private:
        int ref;
};

template <typename T>
class SObject{
    public:
        //copy construction
        SObject(const SObject<T> &inst){
            m_obj = inst.m_obj;
            if(m_obj != NULL){
                m_obj->get();
            }
        }
        //default construction
        SObject(){
            m_obj = NULL;
        }
        //T construction
        SObject(T *obj){
            m_obj = obj ;
            if(m_obj != NULL){
                m_obj->get();
            }
        }
        //construction
        SObject(SObject<T> &inst){
            m_obj = inst.m_obj;
            if(m_obj != NULL){
                m_obj->get();
            }
        }

        const SObject<T>& operator=(SObject<T> &inst) const{
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
            }
            m_obj = inst.m_obj;
            if(m_obj != NULL){
                m_obj->get();
            }
            return *this ;
        }


        SObject<T>& operator=(SObject<T> &inst){
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
            }
            m_obj = inst.m_obj;
            if(m_obj != NULL){
                m_obj->get();
            }
            return *this;
        }

        const SObject<T>& operator=(T *obj) const{
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
            }
            m_obj = obj;
            if(m_obj != NULL){
                m_obj->get();
            }
            return *this;
        }

        SObject<T>& operator=(T *obj){
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
            }
            m_obj = obj;
            if(m_obj != NULL){
                m_obj->get();
            }
            return *this;
        }
        
        T& operator*(){
            return *m_obj;
        }

        const T& operator*() const{
            return *m_obj;
        }

        T* operator->(){
            return m_obj;
        }

        const T* operator->()const{
            return m_obj;
        }

        T* GetPoint(){
            return m_obj ;
        }

        ~SObject(){
            golden_printfi("~SimpleObject()\n");
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
                m_obj = NULL;
            }
        }
    private:
        T *m_obj;
};

#endif
