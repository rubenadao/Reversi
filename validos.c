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

//TODO Vazia ou Valido
LPos posValidas(ESTADO * e, VALOR peca) {
    LPos l = NULL;
    POSICAO direcoes[8];
    initDirecoes(direcoes);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (e->grelha[i][j] == peca) {
                for(int k = 0; k < 8; k++) {
                    int ln = i+(direcoes[k].ln), cl = j+(direcoes[k].cl);
                    while (ln>-1 && ln<8 && cl>-1 && cl<8 && e->grelha[ln][cl]==(pecaOposta(e->peca))) {
                        ln += direcoes[k].ln;
                        cl += direcoes[k].cl;
                    }
                    if (ln!=-1 && ln!=8 && cl!=-1 && cl!=8 && !(ln == i+(direcoes[k].ln) && cl == j+(direcoes[k].cl)) ){
                        if (e->grelha[ln][cl] == VAZIA || e->grelha[ln][cl] == VALIDO) {
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
    return l;
}
/*
LPos posValidas(ESTADO * e, VALOR peca) {
    LPos l=NULL;
    VALOR t=peca;
    int i=0,j=0;
    for(;i<8;i++) {
        for(;j<8;j++) {
            if (e->grelha[i][j] == t) {
                pcima(e,i,j,&l);
                pbaixo(e,i,j,&l);
                pesquerda(e,i,j,&l);
                pdireita(e,i,j,&l);
                pdiagDC(e,i,j,&l);
                pdiagDB(e,i,j,&l);
                pdiagEC(e,i,j,&l);
                pdiagEB(e,i,j,&l);
            }
        }
        j=0;
    }
    return l;
}

void pcima(ESTADO *e,int l,int c,LPos *t) {
    int i = l-1;
    for(i;i>-1 && e->grelha[i][c]==(pecaOposta(e->peca));i--);
    if (i!=-1 && i!=l-1) {
        if (e->grelha[i][c] == VAZIA) {
            POSICAO p;
            p.ln = i;
            p.cl = c;
            *t = addPos(*t,p);
        }
    }
}

void pbaixo(ESTADO *e,int l,int c,LPos *t) {
    int i = l+1;
    for(i;i<8 && e->grelha[i][c]==(pecaOposta(e->peca));i++);
    if (i!=8 && i!=l+1) {
        if (e->grelha[i][c] == VAZIA) {
            POSICAO p;
            p.ln = i;
            p.cl = c;
            *t = addPos(*t,p);
        }
    }
}

void pesquerda(ESTADO *e,int l,int c,LPos *t) {
    int i = c-1;
    for(i;i>-1 && e->grelha[l][i]==(pecaOposta(e->peca));i--);
    if (i!=-1 && i!=c-1) {
        if (e->grelha[l][i] == VAZIA) {
            POSICAO p;
            p.ln = l;
            p.cl = i;
            *t = addPos(*t,p);
        }
    }
}

void pdireita(ESTADO *e,int l,int c,LPos *t) {
    int i = c+1;
    for(i;i<8 && e->grelha[l][i]==(pecaOposta(e->peca));i++);
    if (i!=8 && i!=c+1) {
        if (e->grelha[l][i] == VAZIA) {
            POSICAO p;
            p.ln = l;
            p.cl = i;
            *t = addPos(*t,p);
        }
    }
}

void pdiagDC(ESTADO *e,int l,int c,LPos *t) {
    int i = l-1,j = c+1;
    for(i,j;i>-1 && j<8 && e->grelha[i][j]==(pecaOposta(e->peca));i--,j++);
    if (j!=8 && j!=c+1 && i!=-1 && i!=l-1) {
        if (e->grelha[i][j] == VAZIA) {
            POSICAO p;
            p.ln = i;
            p.cl = j;
            *t = addPos(*t,p);
        }
    }
}

void pdiagDB(ESTADO *e,int l,int c,LPos *t) {
    int i = l+1,j = c+1;
    for(i,j;i<8 && j<8 && e->grelha[i][j]==(pecaOposta(e->peca));i++,j++);
    if (j!=8 && j!=c+1 && i!=8 && i!=l+1) {
        if (e->grelha[i][j] == VAZIA) {
            POSICAO p;
            p.ln = i;
            p.cl = j;
            *t = addPos(*t,p);
        }
    }
}

void pdiagEC(ESTADO *e,int l,int c,LPos *t) {
    int i = l-1,j = c-1;
    for(i,j;i>-1 && j>-1 && e->grelha[i][j]==(pecaOposta(e->peca));i--,j--);
    if (j!=-1 && j!=c-1 && i!=-1 && i!=l-1) {
        if (e->grelha[i][j] == VAZIA) {
            POSICAO p;
            p.ln = i;
            p.cl = j;
            *t = addPos(*t,p);
        }
    }
}

void pdiagEB(ESTADO *e,int l,int c,LPos *t) {
    int i = l+1,j = c-1;
    for(i,j;i<8 && j>-1 && e->grelha[i][j]==(pecaOposta(e->peca));i++,j--);
    if (j!=-1 && j!=c-1 && i!=8 && i!=l+1) {
        if (e->grelha[i][j] == VAZIA) {
            POSICAO p;
            p.ln = i;
            p.cl = j;
            *t = addPos(*t,p);
        }
    }
}
 */