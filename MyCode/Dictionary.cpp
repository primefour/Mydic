#include"Dictionary.h"



class DictionarySet{
    public:
        DictionarySet();
        ~DictionarySet();
        Dictionary *get_dict(const char *name);
        int  scan_dir(const char *path);
        void remove_dict(const char *name);
    private:
        void add_dict(const char *name,Dictionary *dict);
        HashList *dict_set;
}


static unsigned long dict_hash_func(const void *data){
    assert(data != NULL);
    dict_ident_t *tmp = (dict_ident_t*)data;
    const char *ptr = tmp->name;
    unsigned int val;
    val = 0;
    ptr = (char *)data;
    while(*ptr != '\0'){
        unsigned int tmp = 0;
        val = (val<<4) + (*ptr);
        if(tmp = (val&0xf0000000)){
            val = val ^(tmp >> 24);
            val = val ^tmp;
        }
        ptr ++;
    }
    return val;
}

static int dict_hash_compare(const void *data1,const void *data2){
    assert(data1 != NULL && data2 != NULL);
    dict_ident_t *tmp1 = (dict_ident_t*)data1;
    dict_ident_t *tmp2 = (dict_ident_t*)data2;
    //note NULL pointer
    return strcmp(tmp1->name,tmp2->name);
}

static void dict_hash_destroy(void *data){
    assert(data != NULL);
    dict_ident_t *tmp = (dict_ident_t*)data;
    free(tmp->name);
    delete tmp->dict;
    free(data);
}


DictionarySet::DictionarySet(){
    dict_set = new HashList(dict_hash_func,dict_hash_compare,dict_hash_destroy,20);
}

DictionarySet::~DictionarySet(){
    delete dict_set;
}

void DictionarySet::add_dict(const char *name,Dictionary *dict){
    dict_ident_t *di = (dict_ident_t *)malloc(sizeof(dict_ident_t));
    memset(di,0,sizeof(dict_ident_t));
    int len = strlen(name);
    di->name = (char *)malloc(len + 1);
    memset(di->name,0,len+1);
    strcpy(di->name,name);
    di->dict = dict;
    di->status = 1;
    dict_set->hash_insert(di);
}

void DictionarySet::remove_dict(const char *name){
    dict_ident_t tmp = {0};
    assert(name != NULL);
    tmp.name = name;
    dict_set->hash_remove(&tmp);
}

int DictionarySet::scan_dir(const char *path){
    DirectoryScanner *ds = new DirectoryScanner();
    char tmp_path[PATH_MAX]={0};
    ds->add_suffix(".ifo");
    const char *parent_dir = "..";
    const char *tmpp = strstr(path,parent_dir);
    //forbid accessing to the parent directary
    if(tmpp == path){
        return 0;
    }

    if(strcmp(path,".") == 0 || strcmp(path,"./") == 0){
        getcwd(tmp_path,sizeof(tmp_path));
        path = tmp_path;
    }
    ds->processDirectory(path);

    ds->DumpFileList();
}


