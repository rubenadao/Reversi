//
// Created by Ruben on 07/04/2019.
//

#ifndef REVERSI_MINMAX_H
#define REVERSI_MINMAX_H
#include "estado.h"
#include "linkedLists.h"

/*
typedef struct posAvaliada{
    int eval;
    POSICAO pos;
} POS_AVAL;
*/

smpESTADO minmax2(smpESTADO est, int depth, int alpha, int beta, int maximizante, VALOR pecaMax, int init);
int ganhouS(smpESTADO * e);
int calculaVencedorS(smpESTADO *e);
int minmax(smpESTADO *est, int depth, int alpha, int beta, int maximizante, VALOR pecaMax);
int avaliaEst(smpESTADO * e, VALOR pecaMax);
int min(int x, int y);
int max(int x, int y);
LPos posValidasS(smpESTADO * e, VALOR peca);
int pontuacaoS (smpESTADO *e,VALOR p);
void executaMudancaS(smpESTADO * e, POSICAO a);
void auxMudancaS(smpESTADO * e, int ln, int cl , POSICAO vetor, POSICAO final);
void printaS(smpESTADO e);

#endif //REVERSI_MINMAX_H
