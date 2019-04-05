//
// Created by Ruben on 29/03/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <io.h>
#include "game.h"
#include "estado.h"
#include "stack.h"
#include "linkedLists.h"
#include "validos.h"
#include "file_manager.h"

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
                novoJogo(charParaPeca(toupper(fstArg[0])),e);
            } else printf("Peca invalida!\n");
            break;
        case 'L':
            sscanf(comando,"%s %s",opcode,fstArg);
            lerFicheiro(fstArg,e);
            if (e->iniciado) mostrarJogo(e);
            break;
        case 'E':
            sscanf(comando,"%s %s",opcode,fstArg);
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
                    novaJogada(p,e);
                }
                else printf("Posicao Invalida!\n\n");
            } else printf("Nao tem nenhum jogo iniciado!\n\n");
            break;
        case 'S':
            if (1) {
                LPos l;
                l = posValidas(e);
                printList(l);
            }
            break;
        case 'H':
            break;
        case 'U':
            break;
        case 'A':
            break;
        case 'Q':
            exit(0);
        default:
            //TODO
            printf("Comando Invalido!\n");
    }
}

void novoJogo(VALOR peca, ESTADO *e) {
    cleanEstado(e);
    initEstado(e);
    e->modo = 0;
    STACKG historico;
    initStackG(&historico);
    e->peca = peca;
    //TODO CHECK se pode jogar ainda..
    mostrarJogo(e);
}

void novaJogada(POSICAO p, ESTADO *e) {
    e->grelha[p.ln][p.cl] = e->peca;
    proxTurno(e);
    mostrarJogo(e);
}

void mostrarJogo(ESTADO * e){
    printf("Turno de %c\n\n", pecaParaChar(e->peca));
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


VALOR contrario(VALOR p) {
    if (p==VALOR_X) return VALOR_O;
    else return VALOR_X;
}


void humanVShuman(ESTADO * e) {
    int opcao = -1;
    int jogador = 1;
    while (opcao != 0) {
        printa(*e);
        printf("\nJogador %d:\n",jogador);
        scanf("%d",&opcao);

        if (jogador == 1) jogador++;
        else jogador--;
    }
}

