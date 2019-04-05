//
// Created by pja on 28/02/2019.
//
#include <stdio.h>
#include "estado.h"
#include <stdlib.h>

// exemplo de uma função para imprimir o estado (Tabuleiro)
void printa(ESTADO e)
{
    char c = ' ';

    printf("  1 2 3 4 5 6 7 8\n");

    int j = 1;
    for (int i = 0; i < 8; i++) {
        printf("%d ",j++);
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
            }
            printf("%c ", c);

        }
        printf("\n");
    }

}

void initEstado(ESTADO * e) {
    // estado inicial do tabuleiro. Inicio do jogo!
    e->grelha[3][4] = VALOR_X;
    e->grelha[4][3] = VALOR_X;
    e->grelha[3][3] = VALOR_O;
    e->grelha[4][4] = VALOR_O;

    e->iniciado = 1;

    //e.grelha[2][2] = VALOR_X;
}

void cleanEstado(ESTADO * e) {
    for (int i = 0; i<8; i++) {
        for (int j = 0; j < 8; j++) {
            e->grelha[i][j] = VAZIA;
        }
    }
}

void proxTurno(ESTADO * e) {
    if (e->peca == VALOR_X) e->peca = VALOR_O;
    else e->peca = VALOR_X;
}

char pecaParaChar(VALOR peca){
    if (peca == VALOR_O) return  'O';
    else if (peca == VALOR_X) return 'X';
    else return '-';
}

VALOR charParaPeca (char peca){
    if (peca == 'X') return  VALOR_X;
    else if (peca == 'O') return VALOR_O;
    else return VAZIA;
}


