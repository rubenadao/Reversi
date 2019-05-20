//
// Created by Ruben on 09/05/2019.
//

#include "competicao.h"
#include "estado.h"
#include "file_manager.h"
#include "game.h"

#include <stdio.h>

void competicao(char nome_file[]) {
    FILE *file;
    char linha[20];
    file = fopen(nome_file, "r");
    if (file != NULL) {
        // tabuleiro existente
        /*
        while (fgets(linha, sizeof(linha), file)) {
            fputs(linha, stdout);
        }
         */
        executaC(nome_file);
        fclose(file);
    }
    else {
        // tabuleiro inexistente/
        // / criar novo tabuleiro
        // ...
        file = fopen(nome_file, "w");
        if (file != NULL) {
            fputs("A X 3\n", file);
            fputs("- - - - - - - -\n", file);
            fputs("- - - - - - - -\n", file);
            fputs("- - - - - - - -\n", file);
            fputs("- - - X O - - -\n", file);
            fputs("- - - O X - - -\n", file);
            fputs("- - - - - - - -\n", file);
            fputs("- - - - - - - -\n", file);
            fputs("- - - - - - - -\n", file);
            fclose(file);}
        else {
            printf("Erro ao criar o ficheiro %s. Certifique-se que tem permissões.\n", nome_file);
        }
    }
}

void executaC(char nome_file[]){
    ESTADO e = {0};
    e.modo = '1';
    e.iniciado = 1;
    e.nivelBot = 3;
    lerFicheiro(nome_file,&e);
    jogadaBot(&e,3);
    escreverFicheiro(nome_file,&e);
}

void guardaHistFile(){

}
