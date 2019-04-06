//
// Created by user on 05/04/2019.
//

#ifndef REVERSI_VALIDOS_H
#define REVERSI_VALIDOS_H
#include "linkedLists.h"
LPos posValidas(ESTADO * e, VALOR peca);
void pcima(ESTADO *e,int l,int c,LPos *t);
void pbaixo(ESTADO *e,int l,int c,LPos *t);
void pesquerda(ESTADO *e,int l,int c,LPos *t);
void pdireita(ESTADO *e,int l,int c,LPos *t);
void pdiagDC(ESTADO *e,int l,int c,LPos *t);
void pdiagDB(ESTADO *e,int l,int c,LPos *t);
void pdiagEC(ESTADO *e,int l,int c,LPos *t);
void pdiagEB(ESTADO *e,int l,int c,LPos *t);

#endif //REVERSI_VALIDOS_H
