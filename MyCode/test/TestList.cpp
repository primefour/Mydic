#include"list.h"
#include"HashList.h"
#include<stdio.h>


int main(){
    List *list = new List();
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

    list->dump_list();
    void *ret = list->find_list_item((void *)4);
    printf("ret = %ld \n",(long)ret);

    ret = list->find_list_item((void *)10);
    printf("ret = %ld \n",(long)ret);

    ret = list->get_prev_item((void *)3);
    printf("ret = %ld \n",(long)ret);

    ret = list->get_prev_item((void *)5);
    printf("ret = %ld \n",(long)ret);

    ret = list->get_next_item((void *)3);
    printf("ret = %ld \n",(long)ret);

    ret = list->get_next_item((void *)5);
    printf("ret = %ld \n",(long)ret);

    return 0 ;
}
