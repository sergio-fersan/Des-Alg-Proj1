#include <stdio.h>
#include <direct.h>
#include <string.h>
#include "moedas.h"

typedef struct {
    char nome[15];
    float valor;
} VariavelFloat;

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
    return 0;
}

int main(){
    // srand((unsigned int)time(NULL));
    // int user = login();
    // menu(user);

    char tmp[30];
    char nomes[10][15] = {"Lineu", "Nene", "Bebel", "Agostinho", "Tuco", "Beicola", "Floriano", "Marilda", "Mendonca", "Genilson"};

    for(int i = 1; i <= 10; i++){
        printf("Dono do CPF %d: %s\n", i, lerNomeDoCpf(i));
    }
    
    
    return 0;
}
