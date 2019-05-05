//
// Created by Ruben on 29/03/2019.
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
            break;
        case 'E':
            sscanf(comando,"%s %s",opcode,fstArg);
            escreverFicheiro(fstArg,e);
            //if (e->iniciado) mostrarJogo(e);
            break;
        case 'J':
            if (isIniciado(e)) {
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
            break;
        case 'S':
            if (isIniciado(e)) {
                e->mostravalidos = 1;
                colocaValidos(e);
                mostrarJogo(e);
            }
            break;
        case 'H':
            //TODO Melhorar isto
            if (isIniciado(e)) {
                //TODO POR ISTO NUMA FUNÇÃO E USAR TBM NO 'A'
                smpESTADO s;
                criaSMPEstado(e,&s);
                POSICAO p;
                p = minmax2(s,5,-INFINITY,INFINITY,1,e->peca,1).posInit;
                printWithH(*e,p);
            }
            break;
        case 'U':
            if (isIniciado(e)){
                e->historico=popS(e->historico,e);
                if (e->iniciado) mostrarJogo(e);
            }
            break;
        case 'A':
            //TODO caso n seja nem x nem ou nivel que n existe
            sscanf(comando,"%s %s %s",opcode,fstArg,sndArg);
            e->nivelBot = (int) (sndArg[0]-48);
            if (toupper(fstArg[0]) != 'X') {
                novoJogoB(e);
            } else novoJogo(VALOR_X,e,'1');
            break;
        case 'R':
            novaJogadaAl(e);
            break;
        case 'T':
            testeBots(e);
            break;
        case '1':
            jogadaBot(e,1);
            break;
        case '2':
            jogadaBot(e,2);
            break;
        case '3':
            jogadaBot(e,3);
            break;
        case '?':
            printInstruc(e);
        case 'Q':
            exit(0);
        default:
            //TODO
            printf("Comando Invalido!\n");
    }
}

void printInstruc(ESTADO *e){
    printf("N  Para novo jogo em que o primeiro a jogar e o jogador com peça.\n");
    printf("L  Para ler um jogo de ficheiro. Em modo automático (A), apos leitura do ficheiro, o proximo jogador a jogar e sempre o humano!\n");
    printf("E  Escrever em ficheiro estado do jogo.\n");
    printf("J <L> <C>  Jogar peça atual na posiçao (L,C). O comando J 1 1 pede para colocar a peça atual no canto superior esquerdo!\n");
    printf("S  Para imprimir um ponto ‘.’ nas posições com jogada válida.\n");
    printf("H  Para sugestão de jogada. Deve ser colocado um ‘?’ no sitio sugerido.\n");
    printf("U  Para desfazer a última jogada (Undo). Isto tem de permitir desfazer até ao estado inicial do jogo!\n");
    printf("A <peça> <nível>  Novo jogo contra ‘bot’ (computador) em que o ‘bot’ joga com a peça <peça> num nível de dificuldade <nível> (3 níveis possíveis).");
    printf("Neste modo quem joga primeiro é sempre o jogador com a peça preta ‘X’.\n");
    printf("Q  Para Sair!\n");
    if (e->iniciado) mostrarJogo(e);
}

int isIniciado(ESTADO *e){
    if (e->iniciado) {
        return 1;
    } else printf("Nao tem nenhum jogo iniciado!\n\n");
    return 0;
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
    jogadaBot(e,e->nivelBot);
}

//TODO Invocação de posValidas provoca MemoryLeak

void testeBots(ESTADO *e) {
    int times = 200;
    for(int k = 0; k < 1; k++) {
        float inven = 0.0;
        int vitF = 0, vitD = 0, emp = 0;
        for (int i = 0; i < times; i++) {
            novoJogo(VALOR_O,e,'1');
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
        inven = ((vitD+emp)/(times + 0.0)) *100;
        printf("Invencibilidade:%f\n",inven);
    }
}

void novaJogada(POSICAO p, ESTADO *e) {
    VALOR pecaAtual = e->peca;
    resetValidos(e);
    executaJogada(e,p);
    addHistorico(e);
    mostrarJogo(e);
    processEndSwitch(e);
    if (e->iniciado == 1 && e->modo == '1' && e->peca != pecaAtual) jogadaBot(e,e->nivelBot);;
}


void novaJogadaAl(ESTADO *e) {
    VALOR pecaAtual = e->peca;
    resetValidos(e);
    addHistorico(e);
    botFacil(e);
    processEndSwitch(e);
    if (e->iniciado == 1 && e->modo == '1' && e->peca == pecaAtual) novaJogadaAl(e);
    else if (e->iniciado == 1 && e->modo == '1' && e->peca != pecaAtual) jogadaBot(e,e->nivelBot);
}


void jogadaBot(ESTADO *e, int n){
    //TODO Pode ser não especifico
    VALOR pecaAtual = e->peca;
    if (n == 1) botFacil(e);
    else if (n == 2) botMedio(e);
    else if (n == 3) botDificil(e);
    processEndSwitch(e);
    if (e->iniciado == 1 && e->modo == '1' && e->peca == pecaAtual) jogadaBot(e,n);
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

void processFim(ESTADO *e){
    int venc = calculaVencedor(e);
    if (venc == 0) {
        printf("VENCEDOR: X\n\n");
    } else if (venc == 1) {
        printf("VENCEDOR: O\n\n");
    } else printf("EMPATE\n\n");
    e->iniciado = 0;
}

//TODO Se já estiver cheio escuso de perder tempo com o jogadasValidas

void processEndSwitch(ESTADO *e){
    LPos lx = posValidas(e, VALOR_X);
    LPos lo = posValidas(e ,VALOR_O);
    int jogs_X = lengthList(lx);
    int jogs_O = lengthList(lo);
    //acho que é redundante ver se está cheio.
    if (jogs_O + jogs_X > 0) {
        if (e->peca == VALOR_O && jogs_O == 0) e->peca = VALOR_X;
        else if (e->peca == VALOR_X && jogs_X == 0) e->peca = VALOR_O;
    } else {
        processFim(e);
    }
    freeList(lx);
    freeList(lo);
}


//TODO Invocação de posValidas provoca MemoryLeak
int ganhou(ESTADO * e) {
    int i = 0, j = 0;
    LPos lx = posValidas(e, VALOR_X);
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
    x = (rand() % i);
    pos = getPosIndex(l , x);
    resetValidos(e);
    executaJogada(e,pos);
    mostrarJogo(e);
}

void botMedio (ESTADO *e) {
    smpESTADO s; POSICAO pos;
    criaSMPEstado(e,&s);
    s = minmax2(s,5,-INFINITY,INFINITY,1,e->peca,1);
    pos = s.posInit;
    resetValidos(e);
    executaJogada(e,pos);
    mostrarJogo(e);
}

void botDificil (ESTADO *e) {
    smpESTADO s; POSICAO pos;
    criaSMPEstado(e,&s);
    s = minmax2(s,5,-INFINITY,INFINITY,1,e->peca,1);
    pos = s.posInit;
    resetValidos(e);
    executaJogada(e,pos);
    mostrarJogo(e);
}

void criaSMPEstado(ESTADO *e, smpESTADO *s) {
    s->peca = e->peca;
    int i=0,j=0;
    for(;i<8;i++) {
        for(;j<8;j++)
            s->grelha[i][j]=e->grelha[i][j];
        j=0;
    }
}

//TODO por estado sempre em primeiro ou segundo nas funções

void executaJogada(ESTADO *e, POSICAO p) {
    e->grelha[p.ln][p.cl] = e->peca;
    executaMudanca(e,p);
    proxTurno(e);
}