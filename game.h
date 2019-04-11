//
// Created by Ruben on 29/03/2019.
//
#include "estado.h"

#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H

void interpretador(char * comando, ESTADO *e);
void novoJogo(VALOR peca, ESTADO *e, char modo);
void testeBots(ESTADO *e);
void novoJogoB(ESTADO *e);
void novaJogada(POSICAO p, ESTADO *e);
void jogadaBot(ESTADO *e);
void addHistorico(ESTADO *e);
void mostrarJogo(ESTADO * e);
void startEngine();
//void confirmarLeitura(char * ficheiro);
VALOR pecaOposta(VALOR p);
int ganhou (ESTADO * e);
int calculaVencedor(ESTADO *e);
void botFacil (ESTADO *e);
void botMedio (ESTADO *e);
void botDificil (ESTADO *e);

#endif //REVERSI_GAME_H
