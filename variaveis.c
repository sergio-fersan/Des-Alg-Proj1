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

float lerVarInt(const char *arquivo, const char *variavel){
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

void escVar(const char *arquivo, const char *variavel, float valor){
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

// typedef struct {
//     char nome[15];
//     float valor; // Alterado para armazenar strings
// } Variavel;

// float lerVar(const char *arquivo, const char *variavel){
//     FILE *arq = fopen(arquivo, "rb");

//     Variavel var;
//     while(fread(&var, sizeof(Variavel), 1, arq)){
//         if(strcmp(var.nome, variavel) == 0){
//             fclose(arq);
//             return var.valor;
//         }
//     }

//     fclose(arq);
//     return 0; // 0 se nn achou
// }

// float lerVarInt(const char *arquivo, const char *variavel){
//     FILE *arq = fopen(arquivo, "rb");

//     Variavel var;
//     while(fread(&var, sizeof(Variavel), 1, arq)){
//         if(strcmp(var.nome, variavel) == 0){
//             fclose(arq);
//             return (int)var.valor;
//         }
//     }

//     fclose(arq);
//     return 0; // 0 se nn achou
// }

// void escVar(const char *arquivo, const char *variavel, float valor){
//     FILE *arq = fopen(arquivo, "rb+"); // leitura e escrita ao mesmo tempo

//     Variavel var;
//     int achou = 0;
//     long posicao = 0;
//     while(fread(&var, sizeof(Variavel), 1, arq)){
//         if(strcmp(var.nome, variavel) == 0){
//             achou = 1;
//             posicao = ftell(arq) - sizeof(Variavel);
//             break;
//         }
//     }

//     if(achou == 1){
//         fseek(arq, posicao, SEEK_SET); // encontra a posicao da variavel
//         snprintf(var.nome, sizeof(var.nome), "%s", variavel);
//         var.valor = valor;
//         fwrite(&var, sizeof(Variavel), 1, arq); // so escreve nessa linha
//     } else{ // se nn achou cria a variavle
//         snprintf(var.nome, sizeof(var.nome), "%s", variavel);
//         var.valor = valor;
//         fwrite(&var, sizeof(Variavel), 1, arq);
//     }
//     fclose(arq);
// }

// void escVar(const char *arquivo, const char *variavel, const char *valor){
//     FILE *arq = fopen(arquivo, "rb+"); // leitura e escrita ao mesmo tempo

//     if (arq == NULL) {
//         // Caso o arquivo não exista, criamos o arquivo em modo de escrita binária
//         arq = fopen(arquivo, "wb+");
//         if (arq == NULL) {
//             perror("Erro ao abrir o arquivo");
//             return;
//         }
//     }

//     Variavel var;
//     int achou = 0;
//     long posicao = 0;
//     while(fread(&var, sizeof(Variavel), 1, arq)){
//         if(strcmp(var.nome, variavel) == 0){
//             achou = 1;
//             posicao = ftell(arq) - sizeof(Variavel);
//             break;
//         }
//     }

//     if(achou == 1){
//         fseek(arq, posicao, SEEK_SET); // encontra a posição da variável
//         snprintf(var.nome, sizeof(var.nome), "%s", variavel); // Atualiza o nome da variável
//         snprintf(var.valor, sizeof(var.valor), "%s", valor); // Atualiza o valor com a nova string
//         fwrite(&var, sizeof(Variavel), 1, arq); // Sobrescreve a variável
//     } else { // Se não encontrou a variável, cria uma nova
//         snprintf(var.nome, sizeof(var.nome), "%s", variavel); // Define o nome
//         snprintf(var.valor, sizeof(var.valor), "%s", valor); // Define o valor como string
//         fwrite(&var, sizeof(Variavel), 1, arq); // Adiciona a nova variável
//     }

//     fclose(arq);
// }