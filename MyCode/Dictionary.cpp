#include"Dictionary.h"
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include"DirectoryUtils.h"
#include"Stardict.h"

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
    printf("%s ################### \n",__func__);
    assert(data != NULL);
    dict_ident_t *tmp = (dict_ident_t*)data;
    free(tmp->name);
    delete tmp->dict;
    free(data);
}


DictionarySet::DictionarySet(){
    dict_set = new HashList(dict_hash_func,dict_hash_compare,dict_hash_destroy,20);
    memset(dict_name_list,0,MAX_DICT_SUPPORT *(sizeof(char *)));
}

DictionarySet::~DictionarySet(){
    delete dict_set;
}

int DictionarySet::add_dict(const char *name,Dictionary *dict){
    dict_ident_t *di = (dict_ident_t *)malloc(sizeof(dict_ident_t));
    memset(di,0,sizeof(dict_ident_t));
    int len = strlen(name);
    di->name = (char *)malloc(len + 1);
    memset(di->name,0,len+1);
    strcpy(di->name,name);
    di->dict = dict;
    di->status = 1;
    if(dict_set->hash_find(di) != NULL){
        printf("##############the dictionary has already been in the set %s \n",name);
        goto INSERT_ERROR;
    }else{
        int i = 0 ;
        const char **loc = dict_name_list;
        while(*loc != NULL && i < MAX_DICT_SUPPORT){
            loc ++;
            i ++;
        }
        if(i == MAX_DICT_SUPPORT){
            printf("##############the count of dictionary is over MAX_DICT_SUPPORT\n");
            goto INSERT_ERROR; 
        }
        printf("##########insert %s dictionary to set \n",name);
        dict_name_list[i] = di->name;
        dict_set->hash_insert(di);
        return 0;
    }
INSERT_ERROR:
        free(di->name);
        free(di);
        return -1; 
}

void DictionarySet::remove_dict(char *name){
    dict_ident_t tmp = {0};
    assert(name != NULL);
    int i = 0 ;
    const char **loc = dict_name_list;
    while(i < MAX_DICT_SUPPORT){
        if(strcmp(name,dict_name_list[i]) == 0){
            break;
        }
        loc ++;
        i ++;
    }
    if(i == MAX_DICT_SUPPORT || *loc == NULL){
        return;
    }else{
        dict_name_list[i] = NULL; 
        tmp.name = name;
        dict_set->hash_remove(&tmp);
    }
}


const char *dict_info_suffix = ".ifo";

void dir_scanner_callback(void *data,const char *file_full_path,const char *suffix){
    DictionarySet *pds = (DictionarySet *)data;
    if(strcmp(suffix,dict_info_suffix) == 0){
        //stardict dict
        StardictDictionary *sd = new StardictDictionary(file_full_path);
        int ret = sd->init();
        printf("%s ret = %d \n",__func__,ret);
        if(ret < 0){
            delete sd;
            return ;
        }
        char dict_name[1024]={0};
        sd->get_dictionary_name(dict_name,sizeof(dict_name));
        printf("###dict_name = %s    %s \n",dict_name,__func__);
        pds->add_dict(dict_name,sd);
    }
}

int DictionarySet::scan_dir(const char *path){
    DirectoryScanner *ds = new DirectoryScanner();
    char tmp_path[PATH_MAX]={0};
    ds->add_suffix(dict_info_suffix);
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
    ds->processDirectory(path,dir_scanner_callback,this);
    ds->DumpFileList();
    delete ds;
}

void DictionarySet::get_dicts_name(const char **dict_array,int count){
    int i = 0 ;
    int j = 0 ;
    const char *loc = dict_name_list[0];
    while(i < MAX_DICT_SUPPORT && j < count){
        if(dict_name_list[i] != NULL){
            printf("%s      %s    \n",__func__,dict_name_list[i]);
            dict_array[j] = dict_name_list[i];
            j++;
        }
        loc ++;
        i ++;
    }
}

