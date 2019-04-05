//
// Created by Ruben on 03/04/2019.
//
#include "estado.h"

#ifndef REVERSI_STACK_H
#define REVERSI_STACK_H

typedef struct stack {
    int size; // guarda o tamanho do array valores
    int sp;
    POSICAO *posicoes;
} STACKG;

void initStackG(STACKG *s);
int isEmptyG(STACKG *s);
void pushG(STACKG *s, POSICAO p);
int pop (STACKG *s, POSICAO *p);

#endif //REVERSI_STACK_H
