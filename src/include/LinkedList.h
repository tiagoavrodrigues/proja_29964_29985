#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <stdlib.h>
typedef struct LinkedList{
    void*value;
    size_t size;
    LinkedList*node;
}LinkedList;
size_t LinkedList_getLength(LinkedList*self){
    size_t count=0;
    LinkedList*aux=self;
    while (aux!=NULL){
        count++;
        aux=aux->node;
    }
    return count;
}
LinkedList LinkedList_new(size_t size){
    LinkedList result;
    result.size=size;
    result.value=NULL;
    return result;
}
#endif