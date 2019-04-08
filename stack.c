//
// Created by Ruben on 03/04/2019.
//
#include "stack.h"
#include <stdio.h>
#include "estado.h"
#include <stdlib.h>


STACK pushS(STACK l, smpESTADO e) {
    STACK new;
    new = (STACK) malloc(sizeof(NodoS));
    new->est = e;
    new->prox = l;
    return new;
}

STACK popS(STACK l, ESTADO *e) {
    if (l != NULL) {
        STACK head = l;
        l = l->prox;
        free(head);
        e->peca=(l->est).peca;
        int i=0,j=0;
        for(i;i<8;i++) {
            for(j;j<8;j++)
                e->grelha[i][j]=(l->est).grelha[i][j];
            j=0;
        }
        return l;
    }
}

void printStack(STACK s) {
    while ( s != NULL) {
        printf("+ ");
        s = s->prox;
    }
    printf("\n");
}