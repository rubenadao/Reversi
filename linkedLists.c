//
// Created by Ruben on 04/04/2019.
//

#include "linkedLists.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Adiciona uma nova Posição a uma Lista
 * @param l - Lista do tipo LPos
 * @param p - Posição
 * @return - Lista alterada
 */
LPos addPos (LPos l, POSICAO p) {
    LPos n1;
    n1 = (LPos) malloc(sizeof(Nodo));
    n1->pos = p;
    if (l == NULL) n1->prox = NULL;
    else n1->prox = l;
    return n1;
}

/**
 * Calcula o número de elementos de uma lista
 * @param l - Lista do tipo LPos
 * @return - Número de Elementos
 */
int lengthList(LPos l) {
    LPos aux = l;
    int c=0;
    while(aux != NULL) {
        c++;
        aux = aux->prox;
    }
    return c;
}

/**
 * Devolve a Posição de um determinado indíce numa Lista
 * @param l - Lista do tipo LPos
 * @param i - índice
 * @return - Posição
 */
POSICAO getPosIndex(LPos l, int i) {
    for (int j = 0; j < i; j++) {
        l=l->prox;
    }
    return l->pos;
}

/**
 * Liberta a memória alocada por uma Lista
 * @param l - Lista do tipo LPos
 */
void freeList(LPos l) {
    LPos head = l;
    LPos tmp;
    while (head != NULL) {
        tmp = head->prox;
        free(head);
        head = tmp;
    }
}