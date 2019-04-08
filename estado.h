//
// Created by pja on 27/02/2019.
//
#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H

//Estrutura que representa uma posição na Grelha do Estado
typedef struct posicao{
    int ln;
    int cl;
} POSICAO;

/**
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/


// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O, VALIDO} VALOR;


typedef struct simple_estado {
    VALOR peca; // peça do jogador que vai jogar!
    VALOR grelha[8][8];
} smpESTADO;

typedef struct stack *STACK;
typedef struct stack {
    smpESTADO est;
    STACK prox;
} NodoS;

/**
Estrutura que armazena o estado do jogo
*/
typedef struct estado {
    VALOR peca; // peça do jogador que vai jogar!
    VALOR grelha[8][8];
    char modo; // modo em que se está a jogar! 0-> manual, 1-> contra computador

    //TODO pode ser desnecessário
    int iniciado;
    int mostravalidos;
    int nivelBot;
    STACK historico;

    //TODO usar notação stack pointer

} ESTADO;


void printa(ESTADO);
void initEstado(ESTADO * e);
int pontuacao (ESTADO *e,VALOR p);
void cleanEstado(ESTADO * e);
void resetValidos(ESTADO * e);
void colocaValidos(ESTADO * e);
void proxTurno(ESTADO * e);
char pecaParaChar(VALOR peca);
VALOR charParaPeca (char peca);
POSICAO subtraiVetorGrelha(POSICAO * a, int ln, int cl);
void normalizaVetor(POSICAO * a);
int isPotencial(POSICAO a);
void posParaGrelha(POSICAO *a);
void executaMudanca(ESTADO * e, POSICAO a);
void auxMudanca(ESTADO * e, int ln, int cl , POSICAO vetor, POSICAO final);

#endif //PROJ_ESTADO_H