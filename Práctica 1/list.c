// AUTOR: Daniel Rodriguez Sanchez
// AUTOR: Lucia Docampo Rodriguez

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct node {
    void *data;
    struct node *next;
};

#include "list.h"

void init_list(list *l) {
    *l = NULL;
}

int insert(list *l, void *comando) {

     if(*l == NULL) { // Lista vacia?
        *l = malloc(sizeof(struct node));
        (*l)->data = comando;
        (*l)->next = NULL;
      } else { // Lista no vacia?
        list aux = *l;
        while(aux->next != NULL) aux = aux->next;

        aux->next = malloc(sizeof(struct node));
        aux->next->data = comando;
        aux->next->next = NULL;

    }
    return 0;
}


pos first(list l) {
    return l;
}

pos next(list l, pos p) {
    if(p==NULL) return NULL;
    return p->next;
}

int end(list l, pos p) { // estamos al final?
    return p==NULL;
}

void *get(list l, pos p){
    if(p == NULL){
         return NULL;
     }
    return p->data;
}

void clear(list *l){
     list aux = *l;
     list aux_2;
     while(aux != NULL){
          aux_2 = aux->next;
          free(aux);
          aux = aux_2;
     }
     *l = NULL;
}
