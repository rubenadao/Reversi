//
// Created by Ruben on 11/04/2019.
//

//BACKUP
/*
void testeBots(ESTADO *e) {
    int vitF = 0, vitD = 0, emp = 0;

    for (int i = 0; i < 200; i++) {
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
        if (vitoria == 0) printf("%d - BOT FACIL GANHOU\n",i+1);
        else if (vitoria == 1) printf("%d - BOT DIFICIL GANHOU\n",i+1);
        else printf("%d - EMPATE\n",i+1);
        if (vitoria == 0) vitF++;
        else if (vitoria == 1) vitD++;
        else emp++;
    }
    printf("Vitorias de Dificil:%d\n",vitD);
    printf("Empates:%d\n",emp);
    float inven = ((vitD+emp)/200.0) *100;
    printf("Invencibilidade:%f\n",inven);
}
*/

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


/*
 * int minmax(smpESTADO *est, int depth, int alpha, int beta, int maximizante, VALOR pecaMax) {
    if (depth==0) return avaliaEst(est,pecaMax);

    if (maximizante == 1) {
        int maxEval = -65;
        LPos l = posValidasS(est,est->peca);
        //printf("length:%d\n",lengthList(l));
        for (int i = 0; i < lengthList(l);i++) {
            //printf("iteracao: %d\n",i);
            POSICAO pos;
            pos = getPosIndex(l,i);
            smpESTADO new;
            for(int k = 0;k<8;k++) {
                int j = 0;
                for(;j<8;j++)
                    new.grelha[k][j]=est->grelha[k][j];
                j=0;
            }
            new.grelha[pos.ln][pos.cl] = est->peca;
            executaMudancaS(&new,pos);
            new.peca = pecaOposta(est->peca);
            //printaS(*est);
            int eval = minmax(&new,depth-1,alpha,beta,0,pecaMax);
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
            smpESTADO new;
            for(int k = 0;k<8;k++) {
                int j = 0;
                for(;j<8;j++)
                    new.grelha[k][j]=est->grelha[k][j];
                j=0;
            }
            new.grelha[pos.ln][pos.cl] = est->peca;
            executaMudancaS(&new, pos);
            new.peca = pecaOposta(est->peca);
            //printaS(*est);
            int eval = minmax(&new, depth - 1, alpha, beta, 1, pecaMax);
            printf("%d\n",eval);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        freeList(l);
        return minEval;
    }
}
 */









/*
smpESTADO minmax2(smpESTADO est, int depth, int alpha, int beta, int maximizante, VALOR pecaMax, int init) {
    //TODO ao acrescentar a segunda parte dá erro
    int x;
    x = ganhouS(&est);
    printf("ganhou: %d\n",x);
    if (depth == 0 || ganhouS(&est) != -1) {
        printf("pelo menos cheguei\n");
        if (init == 1) {
            LPos l = posValidasS(&est,est.peca);
            POSICAO p;
            p = getPosIndex(l,0);
            est.posInit = p;
        }
        //TODO Caso em que o pecaInit n é alterado pq o jogo acaba
        est.eval = avaliaEst(&est,pecaMax);
        printf("eval: %d\n",est.eval);
        printf("pos: (%d,%d)\n",est.posInit.ln,est.posInit.cl);
        return est;
    }
    if (maximizante == 1) {
        smpESTADO nEst;
        nEst.eval = -65;
        //int maxEval = -65;
        LPos l = posValidasS(&est,est.peca);
        printf("length:%d\n",lengthList(l));
        for (int i = 0; i < lengthList(l);i++) {
            printf("%d\n",i);
            printf("1\n");
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
                printf("a\n");
                POSICAO p;
                p.ln = pos.ln;
                p.cl = pos.cl;
                printf("(%d,%d)\n",p.ln,p.cl),
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
*/

