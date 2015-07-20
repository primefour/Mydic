#include<stdio.h>
#include"GoldenDictLog.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdexcept>
#include "GoldenHashSet.h"

using namespace std;

class File{
    public:
        File(const char *file_path){
            struct stat st; 
            int ret = 0;
            ret = stat(file_path,&st);
            if(ret < 0){
                perror(file_path);
                throw runtime_error("hello world exception");
            }
        }
        ~File(){
            golden_printfd("file destruction\n");
        }
        const char *string(){
            return "Hello world";
        }
    private:
        int m_fd;
};


int main(){
    File *obj = NULL;
    try{
        obj= new File("./test/hello");
    }catch(runtime_error a){
        golden_printfd("hello exception catch\n");
    }

    if(obj == NULL){
        golden_printfd("obj - is NULL \n");
    }else{
        delete obj;
    }
    return 0;
}



