#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct LinkedList{
    void*value;
    size_t size;
    LinkedList*node;
}LinkedList;
size_t LinkedList_getLength(LinkedList*self){
    size_t count=0;
    LinkedList*aux=self;
    while(aux!=NULL){
        count++;
        aux=aux->node;
    }
    return count;
}
void LinkedList_append(LinkedList*self,void*value){
    LinkedList*aux=self;
    while(aux->node!=NULL){
        aux=aux->node;
    }
    aux->node=(LinkedList*)malloc(sizeof(LinkedList));
    if(aux->node==NULL){
        fprintf(stderr,"\nalocação falhou na LinkedList");
        return;
    }
    aux->node->size=self->size;
    memcpy(aux->node->value,value,self->size);
    aux->node->node=NULL;
}
LinkedList LinkedList_new(size_t size){
    LinkedList result;
    result.size=size;
    result.value=NULL;
    return result;
}
#endif