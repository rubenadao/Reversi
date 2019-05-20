//
// Created by pja on 28/02/2019.
//
#include <stdio.h>
#include "estado.h"
#include "validos.h"
#include "linkedLists.h"
#include "game.h"
#include <stdlib.h>

// exemplo de uma função para imprimir o estado (Tabuleiro)
/**
 * Imprime a grelha de um Estado no ecrã
 * @param e - Estado atual
 */
void printa(ESTADO e)
{
    char c = ' ';

    printf("  1 2 3 4 5 6 7 8");
    printf("\tPontuacao:\n");

    int k = 1;
    for (int i = 0; i < 8; i++) {
        printf("%d ",k++);
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
        if (i == 3) printf("\tTurno: %c",pecaParaChar(e.peca));
        printf("\n");
    }

}

//TODO Eliminar
//Função meio desnecessária
void printWithH(ESTADO e, POSICAO hint){
    char c = ' '; int ln, cl;

    printf("  1 2 3 4 5 6 7 8");
    printf("\tPontuacao:\n");
    ln = hint.ln;
    cl = hint.cl;


    int k = 1;
    for (int i = 0; i < 8; i++) {
        printf("%d ",k++);
        for (int j = 0; j < 8; j++) {
            if (i == ln && j ==  cl) {
                c = '?';
            } else {
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
            }
            printf("%c ", c);

        }
        if (i == 0) printf("\tX: %d",pontuacao(&e,VALOR_X));
        if (i == 1) printf("\tO: %d",pontuacao(&e,VALOR_O));
        if (i == 3) printf("\tTurno: %c",pecaParaChar(e.peca));
        printf("\n");
    }
}

/**
 * Inicializa um Estado com as peças genéricas do centro do Tabuleiro
 * @param e - Estado
 */
void initEstado(ESTADO * e) {
    // estado inicial do tabuleiro. Inicio do jogo!
    e->grelha[3][4] = VALOR_X;
    e->grelha[4][3] = VALOR_X;
    e->grelha[3][3] = VALOR_O;
    e->grelha[4][4] = VALOR_O;
    e->iniciado = 1;
}

/**
 * Calcula a pontuação associadada a uma dada peça (numero de peças)
 * @param e - Estado Atual
 * @param p - Peça
 * @return
 */
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

/**
 * Coloca a grelha de um Estado vazia
 * @param e - Estado
 */
void cleanEstado(ESTADO * e) {
    for (int i = 0; i<8; i++) {
        for (int j = 0; j < 8; j++) {
            e->grelha[i][j] = VAZIA;
        }
    }
}

/**
 * Retira os pontos de uma Grelha de um Estado
 * @param e - Estado
 */
void resetValidos(ESTADO * e){
    for (int i = 0; i<8; i++) {
        for (int j = 0; j < 8; j++) {
            if(e->grelha[i][j] == VALIDO) e->grelha[i][j] = VAZIA;
        }
    }
}

/**
 * Coloca pontos nas posições válidas a jogar de uma grelha de um Estado
 * @param e - Estado
 */
void colocaValidos(ESTADO * e) {
    resetValidos(e);
    LPos l;
    l = posValidas(e,e->peca);
    //printList(l);
    //TODO é de 0 a length??
    for (int i = 0; i < lengthList(l);i++) {
        POSICAO p = getPosIndex(l,i);
        e->grelha[p.ln][p.cl] = VALIDO;
    }
    freeList(l);
}

/**
 * Alterna o turno em jogo
 * @param e - Estado Atual
 */
void proxTurno(ESTADO * e) {
    if (e->peca == VALOR_X) e->peca = VALOR_O;
    else e->peca = VALOR_X;
}

/**
 * Transforma uma variável do tipo VALOR, num caracter
 * @param peca - Peca (VALOR)
 * @return - char retornado
 */
char pecaParaChar(VALOR peca){
    if (peca == VALOR_O) return  'O';
    else if (peca == VALOR_X) return 'X';
    else return '-';
}

/**
 * Transforma uma variável do tipo char, num VALOR
 * @param peca - Caracter
 * @return - VALOR retornado
 */

//TODO ocho que n deveria fazer distinção para o Valido
VALOR charParaPeca (char peca){
    if (peca == 'X') return  VALOR_X;
    else if (peca == 'O') return VALOR_O;
    else if (peca == '.') return VALIDO;
    else return VAZIA;
}

/**
 * Coloca uma peça no Tabuleiro de um Estado e efetua as mudanças necessárias
 * de acordo com as regras do jogo
 * @param e - Estado Atual
 * @param a - Posição a executar
 */
void executaMudanca (ESTADO * e, POSICAO a) {
    POSICAO direcoes[8];
    initDirecoes(direcoes);
    for(int k = 0; k < 8; k++) {

        int ln = a.ln + (direcoes[k].ln), cl = a.cl + (direcoes[k].cl);
        while (ln > -1 && ln < 8 && cl > -1 && cl < 8 && e->grelha[ln][cl] == (pecaOposta(e->peca))) {
            ln += direcoes[k].ln;
            cl += direcoes[k].cl;
        }
        //primeira condição é redundante
        if (ln != -1 && ln != 8 && cl != -1 && cl != 8 &&
            !(ln == a.ln + (direcoes[k].ln) && cl == a.cl + (direcoes[k].cl))) {
            if (e->grelha[ln][cl] == e->peca) {
                ln = a.ln + (direcoes[k].ln); cl = a.cl + (direcoes[k].cl);
                while (ln > -1 && ln < 8 && cl > -1 && cl < 8 && e->grelha[ln][cl] == (pecaOposta(e->peca))) {
                    e->grelha[ln][cl] = e->peca;
                    ln += direcoes[k].ln;
                    cl += direcoes[k].cl;
                }

            }
        }
    }
}