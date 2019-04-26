//
// Created by Ruben on 07/04/2019.
//

#include "minmax.h"
#include "stdlib.h"
#include "stdio.h"
#include "estado.h"
#include "linkedLists.h"
#include "validos.h"
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
smpESTADO minmax2(smpESTADO est, int depth, int alpha, int beta, int maximizante, VALOR pecaMax, int init) {
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
        nEst.eval = -65;
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
        nEst.eval = 65;
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
        int maxEval = -65;
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
        int minEval = 65;
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



int min(int x, int y) {
    if (x > y) return y;
    else return x;
}

int max(int x, int y) {
    if (x > y) return x;
    else return y;
}

//TODO implica o depth ser par, devido á forma como a pontucao é calculada
int avaliaEst(smpESTADO * e, VALOR pecaMax){
    int x = pontuacaoS(e,pecaMax);
    int y = pontuacaoS(e,pecaOposta(pecaMax));
    return x-y;
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


void executaMudancaS(smpESTADO * e, POSICAO a){
    //posParaGrelha(&a);
    int i,j;
    for(i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (e->grelha[i][j] == e->peca) {
                POSICAO vetor = subtraiVetorGrelha(&a,i,j);
                if (isPotencial(vetor)) {
                    normalizaVetor(&vetor);
                    auxMudancaS(e,i,j,vetor,a);
                }
            }
        }
    }
}

void auxMudancaS(smpESTADO * e, int ln, int cl , POSICAO vetor, POSICAO final) {
    int i = 0; int initln = ln; int initcl = cl;
    for (;ln < 8 && cl < 8 && ln >= 0 && cl >= 0 && e->grelha[ln][cl] != VAZIA && (final.ln != ln || final.cl != cl);i++) {
        ln += vetor.ln;
        cl += vetor.cl;
    }
    if (final.ln == ln && final.cl == cl) {
        while (initln != final.ln || initcl != final.cl) {
            e->grelha[initln][initcl] = e->peca;
            initln+=vetor.ln;
            initcl+=vetor.cl;
        }
    }
}

void printaS(smpESTADO e)
{
    char c = ' ';

    printf("  1 2 3 4 5 6 7 8\n");

    int k = 1;
    for (int i = 0; i < 8; i++) {
        printf("%d ",k++);
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
                case VALIDO: {
                    printf("N ERA SUPOSTO!");
                    break;
                }
            }
            printf("%c ", c);

        }
        printf("\n");
    }

}


