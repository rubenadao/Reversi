//
// Created by Ruben on 04/04/2019.
//

#include "linkedLists.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void printList(LPos l){
    LPos new = l;
    while(new != NULL) {
        printf("(%d,%d) ",new->pos.ln,new->pos.cl);
        new = new->prox;
    }
    printf("\n");
}

LPos addPos (LPos l, POSICAO p) {
    LPos n1;
    n1 = (LPos) malloc(sizeof(Nodo));
    n1->pos = p;
    if (l == NULL) n1->prox = NULL;
    else n1->prox = l;
    return n1;
}

int lengthList(LPos l) {
    LPos aux = l;
    int c=0;
    while(aux != NULL) {
        c++;
        aux = aux->prox;
    }
    return c;
}

POSICAO getPosIndex(LPos l, int i) {
    for (int j = 0; j < i; j++) {
        l=l->prox;
    }
    return l->pos;
}

void freeList(LPos l) {
    LPos head = l;
    LPos tmp;
    while (head != NULL) {
        tmp = head->prox;
        free(head);
        head = tmp;
    }
}