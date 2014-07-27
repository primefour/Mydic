#include<stdio.h>
#include"list.h"
#include<stdlib.h>

list_head_t head = {&head,&head };
typedef struct A {
    list_head_t a;
    int idx;
}A;
int main(){
    int i = 0;
    for(i = 0 ;i < 10 ;i++){
        struct A *tmp = (struct A*)malloc(sizeof(struct A));
        init_list_head(&(tmp->a));
        tmp->idx = i;
        insert_list_item_behind(&head,&(tmp->a));
    }

    for(i = 0 ;i < 10 ;i++){
        struct A *tmp = (struct A*)malloc(sizeof(struct A));
        init_list_head(&(tmp->a));
        tmp->idx = i;
        insert_list_item_ahead(&head,&(tmp->a));
    }

    list_head_t *tmp_next = head.next;
    while(tmp_next != &head){
        struct A *tmp = contain_of(tmp_next,A,a);
        printf("idx = %d \n",tmp->idx);
        tmp_next = tmp_next->next;
    }

    tmp_next = head.next;
    i = 0;
    while(i < 5){
        tmp_next = tmp_next->next;
        i++;
    }

    struct A *tmp = (struct A*)malloc(sizeof(struct A));
    init_list_head(&tmp->a);
    tmp->idx = 0xffff;
    insert_list_item_ahead(tmp_next,&(tmp->a));

    tmp_next = head.next;
    while(tmp_next != &head){
        struct A *tmp = contain_of(tmp_next,A,a);
        printf("idx = %d \n",tmp->idx);
        tmp_next = tmp_next->next;
    }
    
}
