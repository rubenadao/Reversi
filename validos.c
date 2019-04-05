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
    printList(l);
    return NULL;
}

void pcima(ESTADO *e,int l,int c,LPos *t) {
    int i = l-1;
    for(i;i>-1 && e->grelha[i][c]==(contrario(e->peca));i--);
    if (i!=-1 && i!=l-1) {
        if (e->grelha[i][c] == VAZIA) {
            POSICAO p;
            p.ln = i+1;
            p.cl = c+1;
            *t = addPos(*t,p);
        }
    }
}

void pbaixo(ESTADO *e,int l,int c,LPos *t) {
    int i = l+1;
    for(i;i<8 && e->grelha[i][c]==(contrario(e->peca));i++);
    if (i!=8 && i!=l+1) {
        if (e->grelha[i][c] == VAZIA) {
            POSICAO p;
            p.ln = i+1;
            p.cl = c+1;
            *t = addPos(*t,p);
        }
    }
}

void pesquerda(ESTADO *e,int l,int c,LPos *t) {
    int i = c-1;
    for(i;i>-1 && e->grelha[l][i]==(contrario(e->peca));i--);
    if (i!=-1 && i!=c-1) {
        if (e->grelha[l][i] == VAZIA) {
            POSICAO p;
            p.ln = l+1;
            p.cl = i+1;
            *t = addPos(*t,p);
        }
    }
}

void pdireita(ESTADO *e,int l,int c,LPos *t) {
    int i = c+1;
    for(i;i<8 && e->grelha[l][i]==(contrario(e->peca));i++);
    if (i!=8 && i!=c+1) {
        if (e->grelha[l][i] == VAZIA) {
            POSICAO p;
            p.ln = l+1;
            p.cl = i+1;
            *t = addPos(*t,p);
        }
    }
}

void pdiagDC(ESTADO *e,int l,int c,LPos *t) {
    int i = l-1,j = c+1;
    for(i,j;i>-1 && j<8 && e->grelha[i][j]==(contrario(e->peca));i--,j++);
    if (j!=8 && j!=c+1 && i!=-1 && i!=l-1) {
        if (e->grelha[i][j] == VAZIA) {
            POSICAO p;
            p.ln = i+1;
            p.cl = j+1;
            *t = addPos(*t,p);
        }
    }
}

void pdiagDB(ESTADO *e,int l,int c,LPos *t) {
    int i = l+1,j = c+1;
    for(i,j;i<8 && j<8 && e->grelha[i][j]==(contrario(e->peca));i++,j++);
    if (j!=8 && j!=c+1 && i!=8 && i!=l+1) {
        if (e->grelha[i][j] == VAZIA) {
            POSICAO p;
            p.ln = i+1;
            p.cl = j+1;
            *t = addPos(*t,p);
        }
    }
}

void pdiagEC(ESTADO *e,int l,int c,LPos *t) {
    int i = l-1,j = c-1;
    for(i,j;i>-1 && j>-1 && e->grelha[i][j]==(contrario(e->peca));i--,j--);
    if (j!=-1 && j!=c-1 && i!=-1 && i!=l-1) {
        if (e->grelha[i][j] == VAZIA) {
            POSICAO p;
            p.ln = i+1;
            p.cl = j+1;
            *t = addPos(*t,p);
        }
    }
}

void pdiagEB(ESTADO *e,int l,int c,LPos *t) {
    int i = l+1,j = c-1;
    for(i,j;i<8 && j>-1 && e->grelha[i][j]==(contrario(e->peca));i++,j--);
    if (j!=-1 && j!=c-1 && i!=8 && i!=l+1) {
        if (e->grelha[i][j] == VAZIA) {
            POSICAO p;
            p.ln = i+1;
            p.cl = j+1;
            *t = addPos(*t,p);
        }
    }
}