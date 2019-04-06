//
// Created by pja on 28/02/2019.
//
#include <stdio.h>
#include "estado.h"
#include "validos.h"
#include "linkedLists.h"
#include <stdlib.h>

// exemplo de uma função para imprimir o estado (Tabuleiro)
void printa(ESTADO e)
{
    char c = ' ';

    printf("  1 2 3 4 5 6 7 8");
    printf("\tPontuacao:\n");

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
                case VALIDO: {
                    if (e.mostravalidos == 1) c = '.';
                    else c = '-';
                    break;
                }
            }
            printf("%c ", c);

        }
        if (i == 0) printf("\tX: %d",pontuacao(&e,VALOR_X));
        if (i == 1) printf("\tO: %d",pontuacao(&e,VALOR_O));
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

int pontuacao (ESTADO *e,VALOR p){
    int i=0,j=0,n=0;
    for(;i<8;i++){
        for(;j<8;j++){
            if(e->grelha[i][j]==p)
                n++;
        }
        j=0;
    }
    return n;
}

void cleanEstado(ESTADO * e) {
    for (int i = 0; i<8; i++) {
        for (int j = 0; j < 8; j++) {
            e->grelha[i][j] = VAZIA;
        }
    }
}

void resetValidos(ESTADO * e){
    for (int i = 0; i<8; i++) {
        for (int j = 0; j < 8; j++) {
            if(e->grelha[i][j] == VALIDO) e->grelha[i][j] = VAZIA;
        }
    }
}

void colocaValidos(ESTADO * e) {
    LPos l;
    l = posValidas(e,e->peca);
    //printList(l);
    //TODO é de 0 a length??
    for (int i = 0; i < lengthList(l);i++) {
        POSICAO p = getPosIndex(l,i);
        e->grelha[p.ln][p.cl] = VALIDO;
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

POSICAO subtraiVetorGrelha(POSICAO * a, int ln, int cl) {
    POSICAO c;
    c.ln = a->ln - ln;
    c.cl = a->cl - cl;
    return c;
}

void normalizaVetor(POSICAO * a){
    if (a->ln != 0) {
        if (a->ln > 0) a->ln = 1;
        else a->ln = -1;
    }
    if (a->cl != 0) {
        if (a->cl > 0) a->cl = 1;
        else a->cl = -1;
    }
}

int isPotencial(POSICAO a) {
    if ( (a.ln == 0 && a.cl != 0) || (a.ln != 0 && a.cl == 0) ) return 1;
    else if (a.ln != 0 && abs(a.ln) == abs(a.cl)) return 1;
    else return 0;
}

void posParaGrelha(POSICAO *a) {
    a->cl--;
    a->ln--;
}

void executaMudanca(ESTADO * e, POSICAO a){
    //posParaGrelha(&a);
    int i,j;
    for(i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (e->grelha[i][j] == e->peca) {
                POSICAO vetor = subtraiVetorGrelha(&a,i,j);
                if (isPotencial(vetor)) {
                    normalizaVetor(&vetor);
                    auxMudanca(e,i,j,vetor,a);
                }
            }
        }
    }
}

void auxMudanca(ESTADO * e, int ln, int cl , POSICAO vetor, POSICAO final) {
    int i = 0; int initln = ln; int initcl = cl;
    for (;ln < 8 && cl < 8 && ln >= 0 && cl >= 0 && e->grelha[ln][cl] != VAZIA && (final.ln != ln || final.cl != cl);i++) {
        ln += vetor.ln;
        cl += vetor.cl;
    }
    if (final.ln == ln && final.cl == cl) {
        while (initln != final.ln || initcl != final.cl) {
            e->grelha[initln][initcl] = e->peca;
            initln+=vetor.ln;
            initcl+=vetor.cl;
        }
    }
}
