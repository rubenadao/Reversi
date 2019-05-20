//
// Created by Ruben on 29/03/2019.
//
#include "estado.h"

#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H

void interpretador(char * comando, ESTADO *e);
int isIniciado(ESTADO *e);
void printInstruc(ESTADO *e);
void novoJogo(VALOR peca, ESTADO *e, char modo);
void novaJogada(POSICAO p, ESTADO *e);
void jogadaBot(ESTADO *e, int n);
void addHistorico(ESTADO *e);
void mostrarJogo(ESTADO * e);
void processEndSwitch(ESTADO *e);
void startEngine();
VALOR pecaOposta(VALOR p);
void processFim(ESTADO *e);
int calculaVencedor(ESTADO *e);
void botFacil (ESTADO *e);
void botMedio (ESTADO *e);
void botDificil (ESTADO *e);
void criaSMPEstado(ESTADO *e, smpESTADO *s);
void executaJogada(ESTADO *e, POSICAO p);

#endif //REVERSI_GAME_H
