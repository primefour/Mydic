#ifndef __GOLDEN_DICT_REF__
#define __GOLDEN_DICT_REF__
#include<stdio.h>
#define NO_LOG

class Ref {
    public:
        Ref(){
            ref = 1;
            //printf("ref() ref = %d \n",ref);
        }

        Ref(const Ref & obj){
            ref = 1;
            //printf("ref (obj) ref = %d \n",ref);
        }

        void get(){
            ref ++;
            //printf("get ref = %d \n",ref);
        }

        int put(){
            ref --;
            //printf("put ref = %d \n",ref);
            return ref ;
        }

        virtual int getDumpValue(){
            return ref;
        }

        virtual ~Ref(){
            ref --;
            if(ref > 0){
                //printf("~ref leak error !\n");
            }else{
                //printf("~ref delete object! \n");
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
            printf("SimpleObject(T *obj)\n");
            if(obj != NULL){
                m_obj = obj ;
                m_obj->get();
            }
        }

        /*
        SimpleObject(const T &obj){
            printf("SimpleObject(const T&obj)\n");
            m_obj = &obj;
            if(m_obj != NULL){
                m_obj->get();
            }
        }

        SimpleObject(T &obj){
            printf("SimpleObject(T&obj)\n");
            m_obj = &obj;
            if(m_obj != NULL){
                m_obj->get();
            }
        }
        */

        SimpleObject(){
            printf("SimpleObject()\n");
            m_obj = NULL;
        }

        //copy constructor
        SimpleObject(SimpleObject &obj){
            printf("SimpleObject(const SimpleObject &obj)\n");
            m_obj = obj.m_obj;
            if(m_obj != NULL){
                m_obj->get();
            }
        }


        SimpleObject& operator=(SimpleObject &ob){
            printf("SimpleObject& operator=(const SimpleObject)\n");
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
            }
            if(ob.m_obj == NULL){
                printf("m_obj  is NULL\n");
            }else{
                m_obj = ob.m_obj;
                m_obj->get();
            }
            return *this;
        }
        /*
        SimpleObject* operator=(const SimpleObject *ob){
            printf("SimpleObject& operator=(const SimpleObject *)\n");
            if(ob == NULL){
                return this;
            }else{
                if(m_obj && m_obj->put() <= 0){
                    delete m_obj;
                }
                m_obj = NULL;
                if(ob->m_obj == NULL){
                    printf("m_obj  is NULL\n");
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
            printf("operator=(const T &ob) \n");
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
            }
            m_obj = &ob;
            m_obj->get();
        }
        */

        void operator=(const T *ob){
            printf("operator=(const T *ob)\n");
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
            }
            m_obj = NULL;
            if(ob == NULL){
                printf("m_obj  is NULL\n");
            }else{
                m_obj = ob;
                m_obj->get();
            }
        }

        ~SimpleObject(){
            printf("~SimpleObject()\n");
            if(m_obj && m_obj->put() <= 0){
                delete m_obj;
                m_obj = NULL;
            }
        }
    private:
        T *m_obj;
};

#endif
