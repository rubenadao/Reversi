//
// Created by Ruben on 03/04/2019.
//

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXG 10

void initStackG(STACKG *s) {
    s->sp = 0;
    s->size = MAXG;
    s->posicoes = (POSICAO *) malloc(s->size * sizeof(POSICAO));
}

int isEmptyG(STACKG *s) {
    return (s->sp == 0);
}

void pushG(STACKG *s, POSICAO p) {
    if (s->sp < s->size) {
        *(s->posicoes + s->sp++) = p;
    } else {
        POSICAO *ns = (POSICAO *) malloc (sizeof(POSICAO) * s->size * 2);
        for (int i = 0; i < s->sp; i++) {
            *(ns+i) = *(s->posicoes + i);
        }
        *(ns+s->sp) = p;
        ++s->sp;
        free(s->posicoes);
        s->posicoes = ns;
        s->size *=2;
    }
}

/*
void printStack(STACKG *s) {
    for(int i = (s->sp)-1; i >= 0; i--)
        printf("%d ",s->valores[i]);
    printf("\n");
}
*/


int pop (STACKG *s, POSICAO *p) {
    if (isEmptyG(s)) return 1;
    else {
        *p = s->posicoes[s->sp - 1];
        s->sp--;
        return 0;
    }
}