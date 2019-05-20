//
// Created by Utilizador on 20/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include "game.h"
#include "estado.h"
#include "stack.h"
#include "linkedLists.h"
#include "validos.h"
#include "file_manager.h"
#include "minmax.h"
#include "competicao.h"
#include "menu.h"

void cmdLer(ESTADO *e, char * comando, char * opcode, char* fstArg){
    sscanf(comando,"%s %s",opcode,fstArg);
    lerFicheiro(fstArg,e);
}

void cmdEscrever(ESTADO *e, char * comando, char * opcode, char* fstArg){
    sscanf(comando,"%s %s",opcode,fstArg);
    escreverFicheiro(fstArg,e);
}

void cmdNovoJogo(ESTADO *e, char * comando, char * opcode, char* fstArg) {
    sscanf(comando,"%s %s",opcode,fstArg);
    if ( charParaPeca(toupper(fstArg[0])) != VAZIA  ) {
        novoJogo(charParaPeca(toupper(fstArg[0])),e,'0');
    } else printf("Peca invalida!\n");
}

void cmdJogada(ESTADO *e, char * comando, char * opcode, char* fstArg, char* sndArg){
    if (isIniciado(e))  {
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
        } else {
            printf("Posicao Invalida!\n\n");
            mostrarJogo(e);
        }
    }
}

void cmdValidas(ESTADO *e){
    if (isIniciado(e)) {
        e->mostravalidos = 1;
        colocaValidos(e);
        mostrarJogo(e);
    }
}

void cmdSugestao(ESTADO *e){
    //TODO Melhorar isto
    if (isIniciado(e)) {
        //TODO POR ISTO NUMA FUNÇÃO E USAR TBM NO 'A'
        smpESTADO s;
        criaSMPEstado(e,&s);
        POSICAO p;
        p = minmax2(s,5,-INFINITY,INFINITY,1,e->peca,1).posInit;
        printWithH(*e,p);
    }
}

void cmdJogoBot(ESTADO *e, char * comando, char * opcode, char* fstArg, char* sndArg){
    //TODO caso n seja nem x nem ou nivel que n existe
    sscanf(comando,"%s %s %s",opcode,fstArg,sndArg);
    e->nivelBot = (int) (sndArg[0]-48);
    if (toupper(fstArg[0]) != 'X') {
        novoJogo(VALOR_X,e,'1');
        jogadaBot(e,e->nivelBot);
    } else novoJogo(VALOR_X,e,'1');
}