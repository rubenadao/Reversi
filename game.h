//
// Created by Ruben on 29/03/2019.
//
#include "estado.h"

#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H

void interpretador(char * comando, ESTADO *e);
void novoJogo(VALOR peca, ESTADO *e);
void novaJogada(POSICAO p, ESTADO *e);
void mostrarJogo(ESTADO * e);
void startEngine();
//void confirmarLeitura(char * ficheiro);
VALOR contrario(VALOR p);
int ganhou (ESTADO * e);
void humanVShuman(ESTADO * e);
int pontuacao (ESTADO *e,VALOR p);

#endif //REVERSI_GAME_H
