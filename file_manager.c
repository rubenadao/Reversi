//
// Created by Ruben on 04/04/2019.
//

#include "file_manager.h"
#include "estado.h"
#include "game.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void lerFicheiro(char ficheiro[], ESTADO *e) {
    strcat(ficheiro,".txt");
    FILE* file = fopen(ficheiro, "r");
    char line[256];
    if (file) {
        printf("Leitura concluida!\n\n");
        for (int i = 0; fgets(line, 256, file)!= NULL; i++) {
            if (i == 0) {
                if (line[0] == 'M') e->modo = 0;
                else e->modo = 1;
                e->peca = charParaPeca(line[2]);
            }
            else {
                int j = 0;
                int k = 0;
                for(;line[j] != '\0'; j++) {
                    if (line[j] != ' ' && line[j] != '\n') {
                        e->grelha[i-1][k] = charParaPeca(line[j]);
                        k++;
                    }
                }
            }
        }
        e->iniciado = 1;
    } else {
        printf("Ficheiro nao encontrado!\n\n");
    }


}

void escreverFicheiro(char * ficheiro, ESTADO *e){
    if (e->iniciado == 0) {
        printf("Ainda nao iniciou um jogo!\n\n");
        return;
    }
    strcat(ficheiro,".txt");
    FILE* file = fopen(ficheiro, "w");
    char s[4];
    if (e->modo == 0) s[0] = 'M';
    else s[0] = 'A';
    if (e->peca == VALOR_X) s[2] = 'X';
    else s[2] = 'O';
    s[1] = ' ';
    fprintf(file,"%s\n",s);
    for (int i = 0; i < 8; i++) {
        int k = 0;
        for (int j = 0; j < 8; j++) {
            fprintf(file,"%c",pecaParaChar(e->grelha[i][j]));
            k++;
            fprintf(file," ",NULL);
            k++;
        }
        fprintf(file,"\n",NULL);
    }
    printf("Jogo Guardado!\n");
    fclose(file);
}
