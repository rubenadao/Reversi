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
        //TODO RUSSO

        STACK head = l;
        l = l->prox;
        free(head);
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