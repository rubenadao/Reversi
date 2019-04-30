//
// Created by user on 05/04/2019.
//

#ifndef REVERSI_VALIDOS_H
#define REVERSI_VALIDOS_H
#include "linkedLists.h"
void initDirecoes(POSICAO direcoes []);
LPos posValidas(ESTADO * e, VALOR peca);
int posExiste(LPos l, int ln, int cl);

#endif //REVERSI_VALIDOS_H
