//
// Created by Ruben on 29/03/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "game.h"
#include "estado.h"
#include "stack.h"
#include "linkedLists.h"
#include "validos.h"
#include "file_manager.h"
#include <zconf.h>

#define MAX_BUFFER 100


void interpretador(char * comando, ESTADO *e) {
    char opcode[MAX_BUFFER];
    char fstArg[MAX_BUFFER];
    char sndArg[MAX_BUFFER];
    sscanf(comando,"%s",opcode);
    switch (toupper(opcode[0])) {
        case 'N':
            sscanf(comando,"%s %s",opcode,fstArg);
            if ( charParaPeca(toupper(fstArg[0])) != VAZIA  ) {
                novoJogo(charParaPeca(toupper(fstArg[0])),e,'0');
            } else printf("Peca invalida!\n");
            break;
        case 'L':
            sscanf(comando,"%s %s",opcode,fstArg);
            lerFicheiro(fstArg,e);
            //TODO este if??
            if (e->iniciado) {
                mostrarJogo(e);
                e->mostravalidos = 0;
            }
            break;
        case 'E':
            sscanf(comando,"%s %s",opcode,fstArg);
            colocaValidos(e);
            escreverFicheiro(fstArg,e);
            if (e->iniciado) mostrarJogo(e);
            break;
        case 'J':
            if (e->iniciado) {
                sscanf(comando,"%s %s %s",opcode,fstArg,sndArg);
                if (isdigit(fstArg[0]) && isdigit(sndArg[0])) {
                    POSICAO p;
                    p.ln = (int)fstArg[0]-49;
                    p.cl = (int)sndArg[0]-49;
                    colocaValidos(e);
                    if (e->grelha[p.ln][p.cl] == VALIDO) {
                        novaJogada(p,e);
                        e->mostravalidos = 0;
                    }
                    else {
                        //TODO mesmo que a jogada seja invalida ainda mostra os pontos validos
                        printf("Escolha uma jogada valida!\n\n");
                        mostrarJogo(e);
                    }
                }
                else {
                    printf("Posicao Invalida!\n\n");
                    mostrarJogo(e);
                }
            } else printf("Nao tem nenhum jogo iniciado!\n\n");
            break;
        case 'S':
            if (e->iniciado) {
                e->mostravalidos = 1;
                colocaValidos(e);
                mostrarJogo(e);
            } else printf("Nao tem nenhum jogo iniciado!\n\n");
            break;
        case 'H':
            if (1) {
                POSICAO p[8];
                initDirecoes(p);
            }
            break;
        case 'U':
            if (e->iniciado) {
                e->historico=popS(e->historico,e);
                mostrarJogo(e);
            } else printf("Nao tem nenhum jogo iniciado!\n\n");
            break;
        case 'A':
            //TODO caso n seja nem x nem ou nivel que n existe
            sscanf(comando,"%s %s %s",opcode,fstArg,sndArg);
            e->nivelBot = (int) (sndArg[0]-48);
            if (toupper(fstArg[0]) != 'X') {
                novoJogoB(e);
            } else novoJogo(VALOR_X,e,'1');
            break;
        case 'Q':
            exit(0);
        default:
            //TODO
            printf("Comando Invalido!\n");
    }
}

void novoJogo(VALOR peca, ESTADO *e, char modo) {
    cleanEstado(e);
    initEstado(e);
    e->modo = modo;
    e->peca = peca;
    e->mostravalidos = 0;
    e->historico = NULL;
    addHistorico(e);
    mostrarJogo(e);
}

//TODO Função desnecessária ou codigo desnec.
void novoJogoB(ESTADO *e) {
    cleanEstado(e);
    initEstado(e);
    e->modo = '1';
    e->peca = VALOR_X;
    e->mostravalidos = 0;
    e->historico = NULL;
    mostrarJogo(e);
    jogadaBot(e);
}

void novaJogada(POSICAO p, ESTADO *e) {
    resetValidos(e);
    e->grelha[p.ln][p.cl] = e->peca;
    executaMudanca(e,p);
    proxTurno(e);
    addHistorico(e);
    mostrarJogo(e);
    if (e->modo == '1') jogadaBot(e);
}

void jogadaBot(ESTADO *e){
    printf("A Processar jogada..\n");
    //TODO Pode ser não especifico
    sleep(1);
    if (e->nivelBot == 1) botFacil(e);
    /*
     * else
     */
}

void addHistorico(ESTADO *e) {
    smpESTADO s;
    s.peca = e->peca;
    int i=0,j=0;
    for(;i<8;i++) {
        for(;j<8;j++)
            s.grelha[i][j]=e->grelha[i][j];
        j=0;
    }
    e->historico = pushS(e->historico,s);
}

void mostrarJogo(ESTADO * e){
    //TODO se usar esta linha eliminar as "\n\n" das outras
    printf("\n");
    //showPontuacao(e);
    //TODO Qual preferem?
    //printf("Turno de %c\n\n", pecaParaChar(e->peca));
    printa(*e);
    printf("\n");
}


void startEngine() {
    //TODO porquê {0}?
    ESTADO e = {0};
    e.iniciado = 0;
    //TODO Fazer dinamico??
    char comando[100];
    comando[0] = '1';
    printf("Cmd:\n");
    while(fgets(comando, 100, stdin)) {
        interpretador(comando, &e);
        printf("Cmd:\n");
    }
}


VALOR pecaOposta(VALOR p) {
    if (p==VALOR_X) return VALOR_O;
    else return VALOR_X;
}

int ganhou(ESTADO * e) {
    int i = 0, j = 0;
    for (; i<8 && e->grelha [i][j] != VAZIA ; i++) {
        for (; j<8 && e->grelha [i][j] != VAZIA ; j++);
        j=0;
    }
    if (i==8)  return calculaVencedor(e);
    if ((posValidas(e , VALOR_O )== NULL &&  (posValidas(e, VALOR_X)== NULL))) {
        calculaVencedor(e);
    }
    return -1;
}

int calculaVencedor(ESTADO *e) {
        if (pontuacao(e,VALOR_X) > pontuacao(e,VALOR_O)) return 0;
        else if (pontuacao(e,VALOR_X) < pontuacao(e,VALOR_O)) return 1;
        else return 2;
}


void botFacil (ESTADO *e){
    LPos l; int i; int x; POSICAO pos;
    l= posValidas(e, e->peca);
    i = lengthList(l);
    x = (rand() % i);
    pos= getPosIndex(l , x);
    resetValidos(e);
    e->grelha[pos.ln][pos.cl] = e->peca;
    executaMudanca(e,pos);
    proxTurno(e);
    mostrarJogo(e);
}

