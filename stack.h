//
// Created by Ruben on 03/04/2019.
//
#ifndef REVERSI_STACK_H
#define REVERSI_STACK_H
#include "estado.h"


STACK pushS(STACK l, smpESTADO e);
STACK popS(STACK l, ESTADO *e);
void printStack(STACK s);

#endif //REVERSI_STACK_H
