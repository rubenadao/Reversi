//
// Created by Ruben on 07/04/2019.
//

#include "minmax.h"
#include "stdlib.h"
#include "stdio.h"
#include "estado.h"
#include "linkedLists.h"
#include "validos.h"
#include <math.h>
#include "game.h"

//TODO Caso de acabar jogo

/**
 * descricao da funcao
 * @param est - estado do tabuleiro
 * @param depth
 * @param alpha
 * @param beta
 * @param maximizante
 * @param pecaMax
 * @param init
 * @return
 */
smpESTADO minmax2(smpESTADO est, int depth, float alpha, float beta, int maximizante, VALOR pecaMax, int init) {
    //TODO listas de LPos com posições repetidas afetam desempenho
    //TODO Fzer free ás listas (sempre que invoco posValidas em todo o código)
    //TODO ao acrescentar a segunda parte dá
    if (depth == 0 || ganhouS(&est) != -1) {
        if (init == 1) {
            LPos l = posValidasS(&est,est.peca);
            POSICAO p;
            p = getPosIndex(l,0);
            est.posInit = p;
            freeList(l);
        }
        //TODO Caso em que o pecaInit n é alterado pq o jogo acaba
        est.eval = avaliaEst(&est,pecaMax);
        return est;
    }
    if (maximizante == 1) {
        smpESTADO nEst;
        nEst.eval = -INFINITY;
        //int maxEval = -65;
        LPos l = posValidasS(&est,est.peca);
        //TODO pode estar mal.. n sei
        if (l == NULL) {
            est.peca = pecaOposta(est.peca);
            return minmax2(est,depth,alpha,beta,0,pecaMax,init);
        }
        for (int i = 0; i < lengthList(l);i++) {
            //printf("iteracao: %d\n",i);
            POSICAO pos;
            pos = getPosIndex(l,i);
            smpESTADO new;
            for(int k = 0;k<8;k++) {
                int j = 0;
                for(;j<8;j++)
                    new.grelha[k][j]=est.grelha[k][j];
                j=0;
            }
            if (init == 1) {
                POSICAO p;
                p.ln = pos.ln;
                p.cl = pos.cl;
                new.posInit = p;
            }
            else {
                new.posInit = est.posInit;
            }
            new.peca = est.peca;
            new.grelha[pos.ln][pos.cl] = est.peca;
            executaMudancaS(&new,pos);
            new.peca = pecaOposta(est.peca);
            //printaS(*est);
            new = minmax2(new,depth-1,alpha,beta,0,pecaMax,0);
            //printf("%d\n",new.eval);
            //TODO E se isto nunca acontecer??
            if (max(nEst.eval,new.eval) == new.eval) {
                nEst.eval = max(nEst.eval,new.eval);
                nEst.posInit = new.posInit;
            }
            alpha = max(alpha,new.eval);
            if (beta <= alpha) break;
        }
        freeList(l);
        return nEst;
    } else {
        smpESTADO nEst;
        nEst.eval = INFINITY;
        LPos l = posValidasS(&est,est.peca);
        if (l == NULL) {
            est.peca = pecaOposta(est.peca);
            return minmax2(est,depth,alpha,beta,1,pecaMax,init);
        }
        for (int i = 0; i< lengthList(l);i++) {
            POSICAO pos;
            pos = getPosIndex(l, i);
            smpESTADO new;
            for(int k = 0;k<8;k++) {
                int j = 0;
                for(;j<8;j++)
                    new.grelha[k][j]=est.grelha[k][j];
                j=0;
            }
            new.posInit = est.posInit;
            new.peca = est.peca;
            new.grelha[pos.ln][pos.cl] = est.peca;
            executaMudancaS(&new, pos);
            new.peca = pecaOposta(est.peca);
            //printaS(*est);
            new = minmax2(new,depth-1,alpha,beta,1,pecaMax,0);

            if (min(nEst.eval,new.eval) == new.eval) {
                nEst.eval = min(nEst.eval,new.eval);
                nEst.posInit = new.posInit;
            }
            beta = min(beta,new.eval);
            if (beta <= alpha) break;
        }
        freeList(l);
        return nEst;
    }
}


/*
 * Coin Parity Heuristic Value =
	100 * (Max Player Coins - Min Player Coins ) / (Max Player Coins + Min Player Coins)
 */

float aval_paridade(smpESTADO *e,VALOR pecaMax) {
    float r;
    float max_c = (float) pontuacaoS(e,pecaMax);
    float min_c = (float) pontuacaoS(e,pecaOposta(pecaMax));
    r = 100 * (max_c - min_c) / (max_c + min_c);
    return r;
}

/*
 *f ( Max Player Moves + Min Player Moves != 0)
	Mobility Heuristic Value =
		100 * (Max Player Moves - Min Player Moves) / (Max Player Moves + Min Player Moves)
else
	Mobility Heuristic Value = 0
 */

float aval_mobilidade(smpESTADO *e,VALOR pecaMax){
    float r = 0;
    LPos posVmax = posValidasS(e,pecaMax);
    LPos posVmin = posValidasS(e,pecaOposta(pecaMax));
    float nm_max = (float) lengthList(posVmax);
    float nm_min = (float) lengthList(posVmin);
    if ( nm_max + nm_min != 0) {
        r = 100 * (nm_max - nm_min) / (nm_max + nm_min);
    }
    freeList(posVmax);
    freeList(posVmin);
    return r;
}

/*
 * if ( Max Player Corners + Min Player Corners != 0)
	Corner Heuristic Value =
		100 * (Max Player Corners - Min Player Corners) / (Max Player Corners + Min Player Corners)
else
	Corner Heuristic Value = 0
 */

float aval_cantos(smpESTADO *e,VALOR pecaMax){
    float r = 0;
    float ca_max = (float) cantosPecaS(e,pecaMax);
    float ca_min = (float) cantosPecaS(e,pecaOposta(pecaMax));
    if (ca_max + ca_min != 0) {
        //Sera que com 100 funciona melhor
        //Corner accessibility
        r =  100 * (ca_max - ca_min) / (ca_max + ca_min);
        //r =  25 * (ca_max - ca_min);
    }
    return r;
}

float aval_pertoCantos(smpESTADO *e,VALOR pecaMax) {
    float r;
    int max_c = 0;
    int min_c = 0;
    if(e->grelha[0][0] == '-')   {
        if(e->grelha[0][1] == pecaMax) max_c++;
        else if(e->grelha[0][1] == pecaOposta(pecaMax)) min_c++;
        if(e->grelha[1][1] == pecaMax) max_c++;
        else if(e->grelha[1][1] == pecaOposta(pecaMax)) min_c++;
        if(e->grelha[1][0] == pecaMax) max_c++;
        else if(e->grelha[1][0] == pecaOposta(pecaMax)) min_c++;
    }
    if(e->grelha[0][7] == '-')   {
        if(e->grelha[0][6] == pecaMax) max_c++;
        else if(e->grelha[0][6] == pecaOposta(pecaMax)) min_c++;
        if(e->grelha[1][6] == pecaMax) max_c++;
        else if(e->grelha[1][6] == pecaOposta(pecaMax)) min_c++;
        if(e->grelha[1][7] == pecaMax) max_c++;
        else if(e->grelha[1][7] == pecaOposta(pecaMax)) min_c++;
    }
    if(e->grelha[7][0] == '-')   {
        if(e->grelha[7][1] == pecaMax) max_c++;
        else if(e->grelha[7][1] == pecaOposta(pecaMax)) min_c++;
        if(e->grelha[6][1] == pecaMax) max_c++;
        else if(e->grelha[6][1] == pecaOposta(pecaMax)) min_c++;
        if(e->grelha[6][0] == pecaMax) max_c++;
        else if(e->grelha[6][0] == pecaOposta(pecaMax)) min_c++;
    }
    if(e->grelha[7][7] == '-')   {
        if(e->grelha[6][7] == pecaMax) max_c++;
        else if(e->grelha[6][7] == pecaOposta(pecaMax)) min_c++;
        if(e->grelha[6][6] == pecaMax) max_c++;
        else if(e->grelha[6][6] == pecaOposta(pecaMax)) min_c++;
        if(e->grelha[7][6] == pecaMax) max_c++;
        else if(e->grelha[7][6] == pecaOposta(pecaMax)) min_c++;
    }
    r = -12.5 * (max_c - min_c);
    return r;
}

int cantosPecaS(smpESTADO *e, VALOR p) {
    int r = 0;
    if (e->grelha[0][0] == p) r++;
    if (e->grelha[0][7] == p) r++;
    if (e->grelha[7][0] == p) r++;
    if (e->grelha[7][7] == p) r++;
    return r;
}

float aval_tab(smpESTADO * e, VALOR pecaMax) {
    float d = 0;
    int V[8][8] = {{20, -3, 11, 8,  8,  11, -3, 20},
                   {-3, -7, -4, 1,  1,  -4, -7, -3},
                   {11, -4, 2,  2,  2,  2,  -4, 11},
                   {8,  1,  2,  -3, -3, 2,  1,  8},
                   {8,  1,  2,  -3, -3, 2,  1,  8},
                   {11, -4, 2,  2,  2,  2,  -4, 11},
                   {-3, -7, -4, 1,  1,  -4, -7, -3},
                   {20, -3, 11, 8,  8,  11, -3, 20}};

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            if (e->grelha[i][j] == pecaMax) {
                d += V[i][j];
            } else if (e->grelha[i][j] == pecaOposta(pecaMax)) {
                d -= V[i][j];
            }
        }
    return d;
}

float aval_fromTiles(smpESTADO * e, VALOR pecaMax) {
    int r = 0;
    int my_front_tiles = 0, opp_front_tiles = 0;
    int X1[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int Y1[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    for(int i=0; i<8; i++) {
        for (int j = 0; j < 8; j++) {
            if(e->grelha[i][j] != VAZIA)   {
                for(int k=0; k<8; k++)  {
                    int x = i + X1[k]; int y = j + Y1[k];
                    if(x >= 0 && x < 8 && y >= 0 && y < 8 && e->grelha[x][y] == VAZIA) {
                        if(e->grelha[i][j] == pecaMax)  my_front_tiles++;
                        else opp_front_tiles++;
                        break;
                    }
                }
            }
        }
    }
    if (my_front_tiles - opp_front_tiles == 0) {
        r = 0;
    } else {
        r = 100 * (my_front_tiles - opp_front_tiles) / (my_front_tiles + opp_front_tiles);
    }
    return r;
}

//TODO implica o depth ser par, devido á forma como a pontucao é calculada
float avaliaEst(smpESTADO * e, VALOR pecaMax){
    float p = 10 * aval_paridade(e,pecaMax);
    float c = 801.724 * aval_cantos(e,pecaMax);
    float m = 78.922 * aval_mobilidade(e,pecaMax);
    float f = 74.396 * aval_fromTiles(e,pecaMax);
    float d = 10 * aval_tab(e,pecaMax);
    float l =  382.026 * aval_pertoCantos(e,pecaMax);
    return p + c + m + f + l + d;
    //return p + c + m;

    /*
    int x = pontuacaoS(e,pecaMax);
    int y = pontuacaoS(e,pecaOposta(pecaMax));
    return x-y;
     */
}



int ganhouS(smpESTADO * e) {
    int i = 0, j = 0;
    LPos lx =posValidasS(e, VALOR_X);
    LPos lo = posValidasS(e ,VALOR_O);
    for (; i<8 && e->grelha [i][j] != VAZIA ; i++) {
        for (; j<8 && e->grelha [i][j] != VAZIA ; j++);
        j=0;
    }
    if (i==8)  {
        freeList(lx);
        freeList(lo);
        return calculaVencedorS(e);
    }
    if (lo== NULL &&  lx== NULL) {
        freeList(lx);
        freeList(lo);
        return calculaVencedorS(e);
    }
    freeList(lx);
    freeList(lo);
    return -1;
}


int calculaVencedorS(smpESTADO *e) {
    if (pontuacaoS(e,VALOR_X) > pontuacaoS(e,VALOR_O)) return 0;
    else if (pontuacaoS(e,VALOR_X) < pontuacaoS(e,VALOR_O)) return 1;
    else return 2;
}

//BACKUP

int minmax(smpESTADO *est, int depth, int alpha, int beta, int maximizante, VALOR pecaMax) {
    if (depth==0) {
        //printaS(*est);
        int eval = avaliaEst(est,pecaMax);
        //printf("eval: %d\n",eval);
        return eval;
    }

    if (maximizante == 1) {
        int maxEval = -1000000;
        LPos l = posValidasS(est,est->peca);
        //printf("length:%d\n",lengthList(l));
        for (int i = 0; i < lengthList(l);i++) {
            //printf("iteracao: %d\n",i);
            POSICAO pos;
            pos = getPosIndex(l,i);
            smpESTADO new = {0};
            for(int k = 0;k<8;k++) {
                int j = 0;
                for(;j<8;j++)
                    new.grelha[k][j]=est->grelha[k][j];
                j=0;
            }
            new.peca = est->peca;
            new.grelha[pos.ln][pos.cl] = est->peca;
            executaMudancaS(&new,pos);
            new.peca = pecaOposta(est->peca);
            int eval = minmax(&new,depth-1,alpha,beta,0,pecaMax);
            //printf("%d\n",eval);
            maxEval = max(maxEval,eval);
            alpha = max(alpha,eval);
            if (beta <= alpha) break;
        }
        freeList(l);
        return maxEval;
    } else {
        int minEval = 1000000;
        LPos l = posValidasS(est,est->peca);
        for (int i = 0; i< lengthList(l);i++) {
            POSICAO pos;
            pos = getPosIndex(l, i);
            smpESTADO new = {0};
            for(int k = 0;k<8;k++) {
                int j = 0;
                for(;j<8;j++)
                    new.grelha[k][j]=est->grelha[k][j];
                j=0;
            }
            new.peca = est->peca;
            new.grelha[pos.ln][pos.cl] = est->peca;
            executaMudancaS(&new, pos);
            new.peca = pecaOposta(est->peca);
            //printaS(*est);
            int eval = minmax(&new, depth - 1, alpha, beta, 1, pecaMax);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        freeList(l);
        return minEval;
    }
}



float min(float x, float y) {
    if (x > y) return y;
    else return x;
}

float max(float x, float y) {
    if (x > y) return x;
    else return y;
}



LPos posValidasS(smpESTADO * e, VALOR peca) {
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

int pontuacaoS (smpESTADO *e,VALOR p){
    int i=0,j=0,n=0;
    for(;i<8;i++){
        for(;j<8;j++){
            if(e->grelha[i][j]==p)
                n++;
        }
        j=0;
    }
    return n;
}

void executaMudancaS (smpESTADO * e, POSICAO a) {
    POSICAO direcoes[8];
    initDirecoes(direcoes);
    for(int k = 0; k < 8; k++) {

        int ln = a.ln + (direcoes[k].ln), cl = a.cl + (direcoes[k].cl);
        while (ln > -1 && ln < 8 && cl > -1 && cl < 8 && e->grelha[ln][cl] == (pecaOposta(e->peca))) {
            ln += direcoes[k].ln;
            cl += direcoes[k].cl;
        }
        //primeira condição é redundante
        if (ln != -1 && ln != 8 && cl != -1 && cl != 8 &&
            !(ln == a.ln + (direcoes[k].ln) && cl == a.cl + (direcoes[k].cl))) {
            if (e->grelha[ln][cl] == e->peca) {
                ln = a.ln + (direcoes[k].ln); cl = a.cl + (direcoes[k].cl);
                while (ln > -1 && ln < 8 && cl > -1 && cl < 8 && e->grelha[ln][cl] == (pecaOposta(e->peca))) {
                    e->grelha[ln][cl] = e->peca;
                    ln += direcoes[k].ln;
                    cl += direcoes[k].cl;
                }

            }
        }
    }
}



int avaliaEstS(smpESTADO * e, VALOR pecaMax){
    int x = pontuacaoS(e,pecaMax);
    int y = pontuacaoS(e,pecaOposta(pecaMax));
    return x-y;
}


smpESTADO minmax3(smpESTADO est, int depth, float alpha, float beta, int maximizante, VALOR pecaMax, int init) {
    //TODO listas de LPos com posições repetidas afetam desempenho
    //TODO Fzer free ás listas (sempre que invoco posValidas em todo o código)
    //TODO ao acrescentar a segunda parte dá
    if (depth == 0 || ganhouS(&est) != -1) {
        if (init == 1) {
            LPos l = posValidasS(&est,est.peca);
            POSICAO p;
            p = getPosIndex(l,0);
            est.posInit = p;
            freeList(l);
        }
        //TODO Caso em que o pecaInit n é alterado pq o jogo acaba
        est.eval = avaliaEstS(&est,pecaMax);
        return est;
    }
    if (maximizante == 1) {
        smpESTADO nEst;
        nEst.eval = -65;
        //int maxEval = -65;
        LPos l = posValidasS(&est,est.peca);
        //TODO pode estar mal.. n sei
        if (l == NULL) {
            est.peca = pecaOposta(est.peca);
            return minmax3(est,depth,alpha,beta,0,pecaMax,init);
        }
        for (int i = 0; i < lengthList(l);i++) {
            //printf("iteracao: %d\n",i);
            POSICAO pos;
            pos = getPosIndex(l,i);
            smpESTADO new;
            for(int k = 0;k<8;k++) {
                int j = 0;
                for(;j<8;j++)
                    new.grelha[k][j]=est.grelha[k][j];
                j=0;
            }
            if (init == 1) {
                POSICAO p;
                p.ln = pos.ln;
                p.cl = pos.cl;
                new.posInit = p;
            }
            else {
                new.posInit = est.posInit;
            }
            new.peca = est.peca;
            new.grelha[pos.ln][pos.cl] = est.peca;
            executaMudancaS(&new,pos);
            new.peca = pecaOposta(est.peca);
            //printaS(*est);
            new = minmax3(new,depth-1,alpha,beta,0,pecaMax,0);
            //printf("%d\n",new.eval);
            //TODO E se isto nunca acontecer??
            if (max(nEst.eval,new.eval) == new.eval) {
                nEst.eval = max(nEst.eval,new.eval);
                nEst.posInit = new.posInit;
            }
            alpha = (int) max(alpha,new.eval);
            if (beta <= alpha) break;
        }
        freeList(l);
        return nEst;
    } else {
        smpESTADO nEst;
        nEst.eval = 65;
        LPos l = posValidasS(&est,est.peca);
        if (l == NULL) {
            est.peca = pecaOposta(est.peca);
            return minmax3(est,depth,alpha,beta,1,pecaMax,init);
        }
        for (int i = 0; i< lengthList(l);i++) {
            POSICAO pos;
            pos = getPosIndex(l, i);
            smpESTADO new;
            for(int k = 0;k<8;k++) {
                int j = 0;
                for(;j<8;j++)
                    new.grelha[k][j]=est.grelha[k][j];
                j=0;
            }
            new.posInit = est.posInit;
            new.peca = est.peca;
            new.grelha[pos.ln][pos.cl] = est.peca;
            executaMudancaS(&new, pos);
            new.peca = pecaOposta(est.peca);
            //printaS(*est);
            new = minmax3(new,depth-1,alpha,beta,1,pecaMax,0);

            if (min(nEst.eval,new.eval) == new.eval) {
                nEst.eval = min(nEst.eval,new.eval);
                nEst.posInit = new.posInit;
            }
            beta = (int) min(beta,new.eval);
            if (beta <= alpha) break;
        }
        freeList(l);
        return nEst;
    }
}


