#include <stdio.h>
#include <string.h>
#include "variaveis.h"
#include "moedas.h"

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

typedef struct {
    char nome[15];
    char codigo[5];
    float cota;
    float txCompra;
    float txVenda;
} Moeda;

void exibirMoedas(){
    Moeda md;
    FILE *arq = fopen("moedas.bin", "rb");

    printf("Moedas:\n");
    while (fread(&md, sizeof(Moeda), 1, arq) == 1) {
        printf("Nome: %s\n", md.nome);
        printf("Codigo: %s\n", md.codigo);
        printf("Cota: %f\n", md.cota);
        printf("Taxa de compra: %f\n", md.txCompra);
        printf("Taxa de venda: %f\n\n", md.txVenda);
    }
    fclose(arq);
}

float lerValor(const char *nome, const char *valor){
    FILE *arq = fopen("moedas.bin", "rb");

    Moeda md;
    while(fread(&md, sizeof(Moeda), 1, arq)){
        if(strcmp(md.nome, nome) == 0){
            if(strcmp(valor, "cota") == 0){
                fclose(arq);
                return md.cota;
            }
            else if(strcmp(valor, "txCompra") == 0){
                fclose(arq);
                return md.txCompra;
            }
            else if(strcmp(valor, "txVenda") == 0){
                fclose(arq);
                return md.txVenda;
            }
        }
    }

    fclose(arq);
    return 0;
}

char* lerNomeDoCodigo(const char *codigo){
    FILE *arq = fopen("moedas.bin", "rb");
    
    Moeda md;
    while(fread(&md, sizeof(Moeda), 1, arq)){
        if(strcmp(md.codigo, codigo) == 0){
            fclose(arq);
            return strdup(md.nome);
        }
    }

    fclose(arq);
    return strdup("");
}

void removerSaldo(char *str) {
    char *pos;
    char subs[] = "Saldo";
    size_t lenSubs = strlen(subs);

    while((pos = strstr(str, subs)) != NULL){
        memmove(pos, pos + lenSubs, strlen(pos + lenSubs) + 1);
    }
}