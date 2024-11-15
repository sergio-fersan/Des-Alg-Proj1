#include <stdio.h>
#include <string.h>
#include "variaveis.h"

typedef struct {
    char nome[15];
    char valor[50];
} VariavelString;

typedef struct {
    char nome[15];
    float valor;
} VariavelFloat;

typedef struct {
    char nome[15];
    int valor;
} VariavelInt;

void escVarFloat(const char *arquivo, const char *variavel, float valor){
    FILE *arq = fopen(arquivo, "rb+");
    if(!arq){
        arq = fopen(arquivo, "wb"); // cria o arquivo se nn existe
    }

    VariavelFloat var;
    int achou = 0;
    while(fread(&var, sizeof(VariavelFloat), 1, arq) == 1){
        if(strcmp(var.nome, variavel) == 0){
            achou = 1;
            var.valor = valor;
            fseek(arq, -sizeof(VariavelFloat), SEEK_CUR);
            fwrite(&var, sizeof(VariavelFloat), 1, arq);
            break;
        }
    }

    if(achou != 1){
        strcpy(var.nome, variavel);
        var.valor = valor;
        fwrite(&var, sizeof(VariavelFloat), 1, arq);
    }

    fclose(arq);
}

float lerVarFloat(const char *arquivo, const char *variavel){
    FILE *arq = fopen(arquivo, "rb");

    VariavelFloat var;
    while(fread(&var, sizeof(VariavelFloat), 1, arq) == 1){
        if(strcmp(var.nome, variavel) == 0){
            fclose(arq);
            return var.valor;
        }
    }

    fclose(arq);
    return 0;
}

void escVarStr(const char* arquivo, const char* variavel, const char* valor){
    FILE* arq = fopen(arquivo, "rb+");
    if (!arq) {
        arq = fopen(arquivo, "wb");
    }

    VariavelString var;
    int achou = 0;

    while (fread(&var, sizeof(VariavelString), 1, arq) == 1) {
        if (strcmp(var.nome, variavel) == 0) {
            fseek(arq, -sizeof(VariavelString), SEEK_CUR);
            strncpy(var.valor, valor, 49);
            var.valor[49] = '\0';
            fwrite(&var, sizeof(VariavelString), 1, arq);
            achou = 1;
            break;
        }
    }
    
    if (achou == 0) {
        fseek(arq, 0, SEEK_END);
        strncpy(var.nome, variavel, 49);
        var.nome[49] = '\0';
        strncpy(var.valor, valor, 49);
        var.valor[49] = '\0';
        fwrite(&var, sizeof(VariavelString), 1, arq);
    }

    fclose(arq);
}

char* lerVarStr(const char* arquivo, const char* variavel) {
    FILE* arq = fopen(arquivo, "rb");

    VariavelString var;
    while (fread(&var, sizeof(VariavelString), 1, arq) == 1) {
        if (strcmp(var.nome, variavel) == 0) {
            fclose(arq);
            return strdup(var.valor);
        }
    }

    fclose(arq);
    return NULL;
}

char* lerNomeDoCpf(int cpf){
    FILE *arq = fopen("usuarios.bin", "rb");

    VariavelFloat var;

    while(fread(&var, sizeof(VariavelFloat), 1, arq) == 1){
        if(var.valor == cpf){
            fclose(arq);
            return strdup(var.nome);
        }
    }

    fclose(arq);
    return strdup(""); // quando nn tem ngm com esse cpf
}