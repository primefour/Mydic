#include"list.h"
#include"HashList.h"
#include<stdio.h>

static unsigned long hash_function(void *key){
    return (long)key;
}

static int hash_compare(void *key1,void *key2){
    if(key1 == key2){
        return 0;
    }else{
        return 1;
    }
}

static void hash_destroy(void *data){

}

int main(){
    List *list = new List(List::default_list_compare,NULL);
    list->dump_list();
    list->insert_list_tail((void *)0);
    list->insert_list_tail((void *)1);
    list->insert_list_tail((void *)2);
    list->insert_list_tail((void *)3);
    list->insert_list_tail((void *)4);
    list->dump_list();

    list->insert_list_head((void *)0);
    list->insert_list_head((void *)1);
    list->insert_list_head((void *)2);
    list->insert_list_head((void *)3);
    list->insert_list_head((void *)4);

    list->remove_list_item((void *)4);
    list->dump_list();
    //list->remove_list_item((void *)4);

    void *ret = list->find_list_item((void *)4);

    printf("ret = %ld \n",(long)ret);

    ret = list->find_list_item((void *)10);
    printf("ret = %ld \n",(long)ret);

    ret = list->get_prev_item((void *)3);
    printf("ret = %ld \n",(long)ret);

    ret = list->get_prev_item((void *)5);
    printf("ret = %ld \n",(long)ret);

    printf("#####################%d ##################\n",__LINE__);
    ret = list->get_next_item((void *)3);
    printf("ret = %ld \n",(long)ret);

    printf("#####################%d ##################\n",__LINE__);
    ret = list->get_next_item((void *)5);
    printf("ret = %ld \n",(long)ret);

    printf("#####################%d ##################\n",__LINE__);
    HashList *hash = new HashList(hash_function,hash_compare,hash_destroy,10);
    printf("#####################%d ##################\n",__LINE__);
    hash->hash_insert((void *) 0);
    printf("#####################%d ##################\n",__LINE__);
    hash->hash_insert((void *) 1);
    hash->hash_insert((void *) 4);
    hash->hash_insert((void *) 3);
    hash->hash_insert((void *) 2);
    hash->hash_insert((void *) 1);

    ret = hash->hash_find((void*) 1);
    printf("ret = %ld \n",(long)ret);

    ret = hash->hash_find((void*) 3);
    printf("ret = %ld \n",(long)ret);

    ret = hash->hash_find((void*) 4);
    printf("ret = %ld \n",(long)ret);

    ret = hash->hash_find((void*) 5);
    printf("ret = %ld \n",(long)ret);

    hash->hash_remove((void*) 4);
    ret = hash->hash_find((void*) 4);
    printf("ret = %ld \n",(long)ret);
    return 0 ;
}
