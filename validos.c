//
// Created by user on 05/04/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "game.h"
#include "estado.h"
#include "stack.h"
#include "file_manager.h"
#include "linkedLists.h"
#include "validos.h"

/**
 * Modifica uma Lista de Posições, colocando
 * todos os possíveis vetores de direção.
 * @param direcoes - Lista de Posições
 */
void initDirecoes(POSICAO direcoes []) {
    POSICAO d;
    d.ln = -1;
    d.cl = -1;
    for (int i = 0; i < 3; i++) {
        direcoes[i] = d; d.cl++;
    }
    d.ln++; d.cl =-1;
    for (int i = 0; i < 2; i++) {
        direcoes[i+3] = d; d.cl+=2;
    }
    d.ln++; d.cl =-1;
    for (int i = 0; i < 3; i++) {
        direcoes[i+5] = d; d.cl++;
    }
}

/**
 * Origina uma lista com todas as posições que constituem
 * jogadas válidas num Estado
 * @param e - Estado Atual
 * @param peca - Peça da qual queremos obter a lista
 * @return - Lista de tipo LPos
 */
//TODO Vazia ou Valido
LPos posValidas(ESTADO * e, VALOR peca) {
    //TODO Chamo isto atrás muitas vezes
    resetValidos(e);
    LPos l = NULL;
    POSICAO direcoes[8];
    initDirecoes(direcoes);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (e->grelha[i][j] == peca) {
                for(int k = 0; k < 8; k++) {

                    int ln = i+(direcoes[k].ln), cl = j+(direcoes[k].cl);
                    while (ln>-1 && ln<8 && cl>-1 && cl<8 && e->grelha[ln][cl]==(pecaOposta(peca))) {
                        ln += direcoes[k].ln;
                        cl += direcoes[k].cl;
                    }
                    //primeira condição é redundante
                    if (ln!=-1 && ln!=8 && cl!=-1 && cl!=8 && !(ln == i+(direcoes[k].ln) && cl == j+(direcoes[k].cl)) ){
                        if (e->grelha[ln][cl] == VAZIA || e->grelha[ln][cl] == VALIDO) {
                            if (posExiste(l,ln,cl) == 0) {

                            POSICAO p;
                            p.ln = ln;
                            p.cl = cl;

                            l = addPos(l,p);
                            }
                        }
                    }
                }
            }
        }
    }
    return l;
}

/**
 * Verifica se uma Posição já existe em uma lista
 * @param l - lista de tipo LPos
 * @param ln - linha da Posição
 * @param cl - coluna da Posição
 * @return - 1 ou 0 conforme for verdadeira ou falsa
 */
int posExiste(LPos l, int ln, int cl){
    int r = 0;
    while(l != NULL && r == 0) {
        if (l->pos.ln == ln && l->pos.cl == cl) r =1;
        l = l->prox;
    }
    return r;
}
