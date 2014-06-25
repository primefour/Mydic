#ifndef __DIC_FILE_H__
#define __DIC_FILE_H__

typedef enum dict_file_type {
    dict_stardict_info,
    dict_stardict_index,
    dict_stardict_dict,
    dict_stardict_sync,
}dict_file_type_t;


class dictionary{

}

class stardict_dict :public dictionary{
    public:


    private:
        file_opt finfo;
        file_opt fdict;
        file_opt fidx;
        ifle_opt fsync;
};

const unsigned int MAX_PATH_LENGTH=1024;
//implements genera file operations
class File{
    public :
        File(char *path);
        File();
        virtual int open(char *path,int mode);
        virtual int read(char *buf,int len);
        virtual int write(char *buf,int len);
        virtual int lseek(int where,int offset);
        virtual int readline(char *buf,int len);
        virtual int check_file_type();
    private:
        int fd;
        char file_path[MAX_PATH_LENGTH];
};

//using genera file operations to implements 
//file opt interface
class zipfile_opt:public File{
    static int check_file_type(char *buf,int len);
};



#endif 
