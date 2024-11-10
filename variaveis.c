#include <stdio.h>
#include "variaveis.h"

typedef struct {
    char nome[15];
    float valor;
} Variavel;

float lerVarBin(const char *arquivo, const char *variavel){
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

float lerVarIntBin(const char *arquivo, const char *variavel){
    FILE *arq = fopen(arquivo, "rb");

    Variavel var;
    while(fread(&var, sizeof(Variavel), 1, arq)){
        if(strcmp(var.nome, variavel) == 0){
            fclose(arq);
            return (int)var.valor;
        }
    }

    fclose(arq);
    return 0; // 0 se nn achou
}

void escVarBin(const char *arquivo, const char *variavel, float valor){
    FILE *arq = fopen(arquivo, "rb+"); // leitura e escrita ao mesmo tempo

    Variavel var;
    int achou = 0;
    long posicao = 0;
    while(fread(&var, sizeof(Variavel), 1, arq)){
        if(strcmp(var.nome, variavel) == 0){
            achou = 1;
            posicao = ftell(arq) - sizeof(Variavel);
            break;
        }
    }

    if(achou == 1){
        fseek(arq, posicao, SEEK_SET); // encontra a posicao da variavel
        snprintf(var.nome, sizeof(var.nome), "%s", variavel);
        var.valor = valor;
        fwrite(&var, sizeof(Variavel), 1, arq); // so escreve nessa linha
    } else{ // se nn achou cria a variavle
        snprintf(var.nome, sizeof(var.nome), "%s", variavel);
        var.valor = valor;
        fwrite(&var, sizeof(Variavel), 1, arq);
    }
    fclose(arq);
}

float lerVar(const char *arquivo, const char *variavel){
    FILE *arq = fopen(arquivo, "r");

    char linha[100];

    while(fgets(linha, sizeof(linha), arq)){
        char tmpVar[15];
        float tmpVal;

        if(sscanf(linha, "%[^ ] %f", tmpVar, &tmpVal) == 2){  // %[^ ] procura até o espaço, %d lê o valor da variável
            if(strcmp(tmpVar, variavel) == 0){
                fclose(arq);
                return tmpVal;
            }
        }
    }
    return 0;
}

int lerVarInt(const char *arquivo, const char *variavel){
    FILE *arq = fopen(arquivo, "r");

    char linha[100];

    while(fgets(linha, sizeof(linha), arq)){
        char tmpVar[15];
        int tmpVal;

        if(sscanf(linha, "%[^ ] %d", tmpVar, &tmpVal) == 2){  // %[^ ] procura até o espaço, %d lê o valor da variável
            if(strcmp(tmpVar, variavel) == 0){
                fclose(arq);
                return tmpVal;
            }
        }
    }
    return 0;
}

void escVar(const char *arquivo, const char *variavel, float valor){
    FILE *arq = fopen(arquivo, "r");
    
    int achouVar = 0; // diz se achou a variavel no txt
    char linha[100];
    char buffer[200] = "";

    while(fgets(linha, sizeof(linha), arq)){
        char tmpVar[15];
        float tmpVal;
        
        if(sscanf(linha, "%[^ ] %f", tmpVar, &tmpVal) == 2){
            if(strcmp(tmpVar, variavel) != 0){ // se as variaveis forem dif
                snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "%s %f\n", tmpVar, tmpVal);
            } else{
                snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "%s %f\n", tmpVar, valor);
                achouVar = 1;
            }
        } else{
            strncat(buffer, linha, sizeof(buffer) - strlen(buffer) - 1); // deixa a linha igual se nn for usar
        }
    } // nada disso ta escrevendo ainda, so armazenando em variavel
    fclose(arq);

    if(achouVar == 1){
        arq = fopen(arquivo, "w");
        fputs(buffer, arq);
        fclose(arq);
    }
}