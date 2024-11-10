#include <stdio.h>
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

void criarMoeda(){
    Moeda md;
    FILE *arq = fopen("moedas.bin", "ab");
    printf("Digite o nome da criptomoeda: ");
    fgets(md.nome, 30, stdin);
    md.nome[strcspn(md.nome, "\n")] = '\0';
    printf("Digite o codigo de identificacao da criptomoeda: ");
    fgets(md.codigo, 5, stdin);
    md.codigo[strcspn(md.codigo, "\n")] = '\0';
    printf("Digite a cota da criptomoeda: ");
    scanf("%f", &md.cota);
    clearBuffer();
    printf("Digite a taxa de compra da criptomoeda: ");
    scanf("%f", &md.txCompra);
    clearBuffer();
    printf("Digite a taxa de venda da criptomoeda: ");
    scanf("%f", &md.txVenda);
    clearBuffer();
    fwrite(&md, sizeof(md), 1, arq);
    fclose(arq);

    printf("Moeda criada com sucesso!!!!\n");
}

void exibirMoedas() {
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