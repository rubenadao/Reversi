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
#include "minmax.h"
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
            //TODO Melhorar isto
            if (e->iniciado) {
                //TODO POR ISTO NUMA FUNÇÃO E USAR TBM NO 'A'
                smpESTADO s;
                s.peca = e->peca;
                int i=0,j=0;
                for(;i<8;i++) {
                    for(;j<8;j++)
                        s.grelha[i][j]=e->grelha[i][j];
                    j=0;
                }
                POSICAO p;
                p = minmax2(s,5,-65,65,1,e->peca,1).posInit;
                printWithH(*e,p);
            } else printf("Nao tem nenhum jogo iniciado!\n\n");
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
        case 'M':
            if (1){
                smpESTADO s;
                s.peca = e->peca;
                int i=0,j=0;
                for(;i<8;i++) {
                    for(;j<8;j++)
                        s.grelha[i][j]=e->grelha[i][j];
                    j=0;
                }
                int f;
                smpESTADO f2 = {0};
                f = minmax(&s,5,-65,65,1,e->peca);
                printf("f:%d\n",f);
                printf("---------------------\n");
                f2 = minmax2(s,5,-65,65,1,e->peca,1);
                printf("f2:%d\n",f2.eval);
                printf("jogada:(%d,%d)\n",f2.posInit.ln,f2.posInit.cl);
            }
            break;
        case 'T':
            testeBots(e);
            break;
        case 'R':
            if (ganhou(e) != -1) {
                printf("Acabou\n");
            }
            else printf("Nao Acabou\n");
            //if (posValidas(e,e->peca) == NULL) printf("E NULL\n");
            //printList(posValidas(e,e->peca));
            //printf("\n Validas\n");
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

//TODO Invocação de posValidas provoca MemoryLeak

void testeBots(ESTADO *e) {
    for(int k = 0; k < 5; k++) {
        float inven = 0.0;
        int vitF = 0, vitD = 0, emp = 0;
        for (int i = 0; i < 200; i++) {
            novoJogo(VALOR_X,e,'1');
            while (ganhou(e) == -1) {
                LPos lx =posValidas(e, VALOR_X);
                LPos lo = posValidas(e ,VALOR_O);
                if (e->peca == VALOR_X && lx != NULL) botFacil(e);
                else if (e->peca == VALOR_X) {
                    e->peca = VALOR_O;
                    botDificil(e);
                }
                else if (e->peca == VALOR_O && lo != NULL) botDificil(e);
                else if (e->peca == VALOR_O) {
                    e->peca = VALOR_X;
                    botFacil(e);
                }
                freeList(lx);
                freeList(lo);
            }
            int vitoria = ganhou(e);

            if (vitoria == 0) printf("%d - BOT FACIL GANHOU\n",i+1);
            else if (vitoria == 1) printf("%d - BOT DIFICIL GANHOU\n",i+1);
            else printf("%d - EMPATE\n",i+1);

            if (vitoria == 0) vitF++;
            else if (vitoria == 1) vitD++;
            else emp++;
        }
        printf("Vitorias de Dificil:%d\n",vitD);
        printf("Empates:%d\n",emp);
        inven = ((vitD+emp)/200.0) *100;
        printf("Invencibilidade:%f\n",inven);
    }

}

/*
void testeBots(ESTADO *e) {
    novoJogo(VALOR_X,e,'1');
    while (ganhou(e) == -1) {
        if (e->peca == VALOR_X && posValidas(e,VALOR_X) != NULL) botFacil(e);
        else if (e->peca == VALOR_X) {
            e->peca = VALOR_O;
            botDificil(e);
        }
        else if (e->peca == VALOR_O && posValidas(e,VALOR_O) != NULL) botDificil(e);
        else if (e->peca == VALOR_O) {
            e->peca = VALOR_X;
            botFacil(e);
        }
    }
    int vitoria = ganhou(e);
    if (vitoria == 0) printf("BOT FACIL GANHOU\n");
    else if (vitoria == 1) printf("BOT DIFICIL GANHOU\n");
    else printf("EMPATE\n");
}
*/

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
    //TODO Pode ser não especifico
    if (e->nivelBot == 1) botFacil(e);
    else if (e->nivelBot == 3) botDificil(e);
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
    char comando[MAX_BUFFER];
    comando[0] = '1';
    printf("Cmd:\n");
    while(fgets(comando, MAX_BUFFER, stdin)) {
        interpretador(comando, &e);
        printf("Cmd:\n");
    }
}

VALOR pecaOposta(VALOR p) {
    if (p==VALOR_X) return VALOR_O;
    else return VALOR_X;
}

//TODO Invocação de posValidas provoca MemoryLeak
int ganhou(ESTADO * e) {
    int i = 0, j = 0;
    LPos lx =posValidas(e, VALOR_X);
    LPos lo = posValidas(e ,VALOR_O);
    for (; i<8 && e->grelha [i][j] != VAZIA ; i++) {
        for (; j<8 && e->grelha [i][j] != VAZIA ; j++);
        j=0;
    }
    if (i==8)  {
        freeList(lx);
        freeList(lo);
        return calculaVencedor(e);
    }
    if (lx == NULL  && lo == NULL) {
        freeList(lx);
        freeList(lo);
        return calculaVencedor(e);
    }
    freeList(lx);
    freeList(lo);
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
    //TODO é preciso usar seed?
    x = (rand() % i);
    pos = getPosIndex(l , x);
    resetValidos(e);
    e->grelha[pos.ln][pos.cl] = e->peca;
    executaMudanca(e,pos);
    proxTurno(e);
    mostrarJogo(e);
}

void botMedio (ESTADO *e) {
    smpESTADO s; POSICAO pos;
    s.peca = e->peca;
    int i=0,j=0;
    for(;i<8;i++) {
        for(;j<8;j++)
            s.grelha[i][j]=e->grelha[i][j];
        j=0;
    }
    smpESTADO f2 = {0};
    f2 = minmax2(s,1,-65,65,1,e->peca,1);
    pos = f2.posInit;
    resetValidos(e);
    e->grelha[pos.ln][pos.cl] = e->peca;
    executaMudanca(e,pos);
    proxTurno(e);
    mostrarJogo(e);
}

void botDificil (ESTADO *e) {
    smpESTADO s; POSICAO pos;
    s.peca = e->peca;
    int i=0,j=0;
    for(;i<8;i++) {
        for(;j<8;j++)
            s.grelha[i][j]=e->grelha[i][j];
        j=0;
    }
    smpESTADO f2 = {0};
    f2 = minmax2(s,5,-65,65,1,e->peca,1);
    pos = f2.posInit;
    resetValidos(e);
    e->grelha[pos.ln][pos.cl] = e->peca;
    executaMudanca(e,pos);
    proxTurno(e);
    mostrarJogo(e);
}


