//
// Created by Ruben on 04/04/2019.
//

#ifndef REVERSI_LINKEDLISTS_H
#define REVERSI_LINKEDLISTS_H

#include "estado.h"

typedef struct slist *LPos;
typedef struct slist {
    POSICAO pos;
    LPos prox;
} Nodo;

void printList(LPos l);
LPos addPos (LPos l, POSICAO p);
void freeList(LPos l);

#endif //REVERSI_LINKEDLISTS_H
