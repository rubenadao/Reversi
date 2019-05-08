//
// Created by Ruben on 03/04/2019.
//
#include "stack.h"
#include <stdio.h>
#include "estado.h"
#include <stdlib.h>

//descnecessário dar a stack
STACK pushS(STACK l, smpESTADO e) {
    STACK new;
    new = (STACK) malloc(sizeof(NodoS));
    new->est = e;
    new->prox = l;
    return new;
}

//descnecessário dar a stack
STACK popS(STACK l, ESTADO *e) {
    if (l != NULL && l->prox != NULL) {
        STACK head = l;
        l = l->prox;
        free(head);
        e->peca=l->est.peca;
        int i=0,j=0;
        for(;i<8;i++) {
            for(;j<8;j++)
                e->grelha[i][j]=(l->est).grelha[i][j];
            j=0;
        }
        printf("Jogada Desfeita!\n\n");
        return l;
    //} else printf("Nao existem jogadas anteriores!\n\n");
    } else e->iniciado = 0;
}

void printStack(STACK s) {
    while ( s != NULL) {
        printf("+ ");
        s = s->prox;
    }
    printf("\n");
}