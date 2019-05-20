//
// Created by Ruben on 04/04/2019.
//

#ifndef REVERSI_LINKEDLISTS_H
#define REVERSI_LINKEDLISTS_H

#include "estado.h"

/**
 * Estrutura que armazena uma Lista de Posições
 */
typedef struct slist *LPos;
typedef struct slist {
    POSICAO pos;
    LPos prox;
} Nodo;

LPos addPos (LPos l, POSICAO p);
int lengthList(LPos l);
POSICAO getPosIndex(LPos l, int i);
void freeList(LPos l);

#endif //REVERSI_LINKEDLISTS_H
