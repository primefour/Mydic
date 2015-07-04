#ifndef __GOLDEN_DICT_REF__
#define __GOLDEN_DICT_REF__
#include<stdio.h>
#include"GoldenDictLog.h"
class Ref {
    public:
        Ref(){
            ref = 1;
            golden_printfi("ref() ref = %d \n",ref);
        }

        Ref(const Ref & obj){
            ref = 1;
            golden_printfi("ref (obj) ref = %d \n",ref);
        }

        void get(){
            ref ++;
            golden_printfi("get ref = %d \n",ref);
        }

        int put(){
            ref --;
            golden_printfi("put ref = %d \n",ref);
            return ref ;
        }

        virtual int getDumpValue(){
            return ref;
        }

        virtual ~Ref(){
            ref --;
            if(ref > 0){
                golden_printfi("~ref leak error !\n");
            }else{
                golden_printfi("~ref delete object! \n");
            }
        }
    private:
        int ref;
};


template <typename T>
class SimpleObject{
    public:
    /*
        SimpleObject(const T *obj){
            printf("SimpleObject(const T *obj)\n");
            if(obj != NULL){
                m_obj = obj ;
                m_obj->get();
            }
        }
        */

        SimpleObject(T *obj){
            golden_printfi("SimpleObject(T *obj)\n");
            if(obj != NULL){
                m_obj = obj ;
                m_obj->get();
            }
        }

        /*
        SimpleObject(const T &obj){
            golden_printfi("SimpleObject(const T&obj)\n");
            m_obj = &obj;
            if(m_obj != NULL){
                m_obj->get();
            }
        }

        SimpleObject(T &obj){
            golden_printfi("SimpleObject(T&obj)\n");
            m_obj = &obj;
            if(m_obj != NULL){
                m_obj->get();
            }
        }
        */

        SimpleObject(){
            golden_printfi("SimpleObject()\n");
            m_obj = NULL;
        }

        //copy constructor
        SimpleObject(SimpleObject &obj){
            golden_printfi("SimpleObject(const SimpleObject &obj)\n");
            m_obj = obj.m_obj;
            if(m_obj != NULL){
                m_obj->get();
            }
        }


        SimpleObject& operator=(SimpleObject &ob){
            golden_printfi("SimpleObject& operator=(const SimpleObject)\n");
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
            }
            if(ob.m_obj == NULL){
                golden_printfi("m_obj  is NULL\n");
            }else{
                m_obj = ob.m_obj;
                m_obj->get();
            }
            return *this;
        }
        /*
        SimpleObject* operator=(const SimpleObject *ob){
            golden_printfi("SimpleObject& operator=(const SimpleObject *)\n");
            if(ob == NULL){
                return this;
            }else{
                if(m_obj && m_obj->put() <= 0){
                    delete m_obj;
                }
                m_obj = NULL;
                if(ob->m_obj == NULL){
                    golden_printfi("m_obj  is NULL\n");
                }else{
                    m_obj = ob->m_obj;
                    m_obj->get();
                }
                return this;
            }
        }
        */
        
        /*
        void operator=(const T &ob){
            golden_printfi("operator=(const T &ob) \n");
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
            }
            m_obj = &ob;
            m_obj->get();
        }
        */

        void operator=(const T *ob){
            golden_printfi("operator=(const T *ob)\n");
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
            }
            m_obj = NULL;
            if(ob == NULL){
                golden_printfi("m_obj  is NULL\n");
            }else{
                m_obj = ob;
                m_obj->get();
            }
        }

        ~SimpleObject(){
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
