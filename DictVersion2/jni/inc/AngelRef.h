#ifndef __ANGEL_REF_H__
#define __ANGEL_REF_H__ 

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
            return mRef
        }

        ~Ref(){
            if(mRef != 0){
                angel_printfe("Remove Object Error \n");
            }
        }

    private:
        int mRef ;
};


template<typename T> 
class Sobj{
    public:
        Sobj(T *obj){
            mObj = obj;
            mObj->get();
        }

    private :
        T *mObj;
}



#endif 
