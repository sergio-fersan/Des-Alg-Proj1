#include <stdio.h>
#include "variaveis.h"

typedef struct {
    char nome[15];
    float valor;
} Variavel;

float lerVar(const char *arquivo, const char *variavel){
    FILE *arq = fopen(arquivo, "rb");

    Variavel var;
    while(fread(&var, sizeof(Variavel), 1, arq)){
        if(strcmp(var.nome, variavel) == 0){
            fclose(arq);
            return var.valor;
        }
    }

    fclose(arq);
    return 0; // 0 se nn achou
}