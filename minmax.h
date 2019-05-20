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

smpESTADO minmax2(smpESTADO est, int depth, float alpha, float beta, int maximizante, VALOR pecaMax, int init);
smpESTADO funcMaximizante(smpESTADO est, int depth, float alpha, float beta, int maximizante, VALOR pecaMax, int init);
smpESTADO funcMinimizante(smpESTADO est, int depth, float alpha, float beta, int maximizante, VALOR pecaMax, int init);
smpESTADO minmax3(smpESTADO est, int depth, float alpha, float beta, int maximizante, VALOR pecaMax, int init);
void smpEstadoChild(smpESTADO *est, smpESTADO *new, POSICAO pos);
void criaSMPEstadoV(smpESTADO *e, smpESTADO *s);
int ganhouS(smpESTADO * e);
int calculaVencedorS(smpESTADO *e);
float aval_paridade(smpESTADO *e,VALOR pecaMax);
float aval_mobilidade(smpESTADO *e,VALOR pecaMax);
float aval_cantos(smpESTADO *e,VALOR pecaMax);
int cantosPecaS(smpESTADO *e, VALOR p);

int minmax(smpESTADO *est, int depth, int alpha, int beta, int maximizante, VALOR pecaMax);
float avaliaEst(smpESTADO * e, VALOR pecaMax);
float min(float x, float y);
float max(float x, float y);
LPos posValidasS(smpESTADO * e, VALOR peca);
int pontuacaoS (smpESTADO *e,VALOR p);
void executaMudancaS(smpESTADO * e, POSICAO a);
void auxMudancaS(smpESTADO * e, int ln, int cl , POSICAO vetor, POSICAO final);
void printaS(smpESTADO e);

#endif //REVERSI_MINMAX_H
