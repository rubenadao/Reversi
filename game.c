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
#include "competicao.h"
#include "menu.h"

#define MAX_BUFFER 500

/**
 * Executa o comando escolhido pelo utilizador
 * @param comando - comando
 * @param e - estado
 */
void interpretador(char * comando, ESTADO *e) {
    char opcode[MAX_BUFFER];
    char fstArg[MAX_BUFFER];
    char sndArg[MAX_BUFFER];
    sscanf(comando,"%s",opcode);
    switch (toupper(opcode[0])) {
        case 'N':
            cmdNovoJogo(e,comando,opcode,fstArg);
            break;
        case 'L':
            cmdLer(e,comando,opcode,fstArg);
            break;
        case 'E':
            cmdEscrever(e,comando,opcode,fstArg);
            break;
        case 'J':
            cmdJogada(e,comando,opcode,fstArg,sndArg);
            break;
        case 'S':
            cmdValidas(e);
            break;
        case 'H':
            cmdSugestao(e);
            break;
        case 'U':
            cmdUndo(e);
            break;
        case 'A':
            cmdJogoBot(e,comando,opcode,fstArg,sndArg);
            break;
        case 'C':
            sscanf(comando,"%s %s",opcode,fstArg);
            competicao(fstArg);
            break;
            /*
        case 'T':
            testeBots(e);
            break;
             */
        case '?':
            printInstruc(e);
            break;
        case 'Q':
            exit(0);
        default:
            printf("Comando Invalido!\n");
            break;
    }
}

/**
 * Faz print da instrução
 * @param e - estado
 */
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

/**
 * Verifica se o jogo está iniciado
 * @param e - estado
 * @return - 1 ou 0, dependendo da veracidade da afirmação (se está iniciado ou não)
 */
int isIniciado(ESTADO *e){
    if (e->iniciado) {
        return 1;
    } else printf("Nao tem nenhum jogo iniciado!\n\n");
    return 0;
}

/**
 * Inicializa um jogo
 * @param e - estado
 */
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


/**
 * Nova jogada
 * @param p - posiçao
 * @param e - estado
 */
void novaJogada(POSICAO p, ESTADO *e) {
    VALOR pecaAtual = e->peca;
    resetValidos(e);
    executaJogada(e,p);
    addHistorico(e);
    mostrarJogo(e);
    processEndSwitch(e);
    if (e->iniciado == 1 && e->modo == '1' && e->peca != pecaAtual) jogadaBot(e,e->nivelBot);;
}


/**
 * Aplica a jogada do bot dependendo do nivel
 * @param e - estado anterior
 * @param n - nível
 */
void jogadaBot(ESTADO *e, int n){
    //TODO Pode ser não especifico
    VALOR pecaAtual = e->peca;
    if (n == 1) botFacil(e);
    else if (n == 2) botMedio(e);
    else if (n == 3) botDificil(e);
    processEndSwitch(e);
    if (e->iniciado == 1 && e->modo == '1' && e->peca == pecaAtual) jogadaBot(e,n);
}

/**
 * Adiciona o estado ao histórico do jogo
 * @param e - estado
 */

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

/**
 * Imprime/print o estado do jogo
 * @param e - estado
 */
void mostrarJogo(ESTADO * e){
    //TODO se usar esta linha eliminar as "\n\n" das outras
    printf("\n");
    //showPontuacao(e);
    //TODO Qual preferem?
    //printf("Turno de %c\n\n", pecaParaChar(e->peca));
    printa(*e);
    printf("\n");
}

/**
 * Primeira inicialização do Estado e loop para os comandos
 */
void startEngine() {
    //TODO porquê {0}?
    ESTADO e = {0};
    //fazer push aqui
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

/**
 * Retorna peça oposta da recebida
 * @param p - peça
 * @return - peça oposta
 */
VALOR pecaOposta(VALOR p) {
    if (p==VALOR_X) return VALOR_O;
    else return VALOR_X;
}


/**
 * Imprime no ecrã o vencedor do jogo
 * @param e -estado
 */
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
/**
 * Função responsável pela passagem de turnos e fim do jogo
 * @param e - Estado Atual
 */
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



/**
 * calcula o vencedor do jogo
 * @param e - estado anterior
 * @return - vencedor
 */

int calculaVencedor(ESTADO *e) {
        if (pontuacao(e,VALOR_X) > pontuacao(e,VALOR_O)) return 0;
        else if (pontuacao(e,VALOR_X) < pontuacao(e,VALOR_O)) return 1;
        else return 2;
}

/**
 * Executa a jogada do bot facil
 * @param e - estado anterior
 */
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

/**
 * Executa a jogada do bot medio
 * @param e - estado anterior
 */
void botMedio (ESTADO *e) {
    smpESTADO s; POSICAO pos;
    criaSMPEstado(e,&s);
    s = minmax2(s,1,-INFINITY,INFINITY,1,e->peca,1);
    pos = s.posInit;
    resetValidos(e);
    executaJogada(e,pos);
    mostrarJogo(e);
}
/**
 * Executa a jogada do bot dificil
 * @param e - estado anterior
 */
void botDificil (ESTADO *e) {
    smpESTADO s; POSICAO pos;
    criaSMPEstado(e,&s);
    s = minmax2(s,5,-INFINITY,INFINITY,1,e->peca,1);
    pos = s.posInit;
    resetValidos(e);
    executaJogada(e,pos);
    mostrarJogo(e);
}

/**
 * Simplifica a versão do estado
 * @param e - estado anterior
 * @param s - estado na versão simplificada
 */
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

/**
 * Executa uma jogada
 * @param e - estado anterior
 * @param p - posição
 */
void executaJogada(ESTADO *e, POSICAO p) {
    e->grelha[p.ln][p.cl] = e->peca;
    executaMudanca(e,p);
    proxTurno(e);
}

//TODO Invocação de posValidas provoca MemoryLeak


/*
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
*/