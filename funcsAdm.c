#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "variaveis.h"
#include "moedas.h"
#include "funcsAdm.h"

typedef struct {
    char nome[15];
    char codigo[5];
    float cota;
    float txCompra;
    float txVenda;
} Moeda;

void loginAdm(){ // FEITO
    int cpfDigitado;
    int senhaDigitada;
    while(1){
        printf("Digite o CPF do administrdor: ");
        scanf("%d", &cpfDigitado);
        printf("Digite a senha do administrador: ");
        scanf("%d", &senhaDigitada);
        if(cpfDigitado != (int)lerVarFloat("usuarios/dadosADM.bin", "cpf") || senhaDigitada != (int)lerVarFloat("usuarios/dadosADM.bin", "senha")){
            printf("CPF e/ou senha incorretos!!! Tente novamente\n");
        } else{
            printf("Bem vindo, administrador!!!!\n");
            break;
        }
    }
}

void criarUsuario(){ // FEITO
    char nome[15];
    int cpf;
    int senha;
    char tmp[50];
    char codigo[15];
    printf("Digite o nome do investidor: ");
    fgets(nome, 15, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Digite o cpf do investidor: ");
    scanf("%d", &cpf);
    printf("Digite a senha do investidor: ");
    scanf("%d", &senha);
    snprintf(tmp, sizeof(tmp), "usuarios/%s", nome);
    _mkdir(tmp);
    snprintf(tmp, sizeof(tmp), "usuarios/%s/dados.bin", nome);
    escVarFloat(tmp, "cpf", cpf);
    escVarFloat(tmp, "senha", senha);
    escVarFloat(tmp, "reais", 0);
    snprintf(tmp, sizeof(tmp), "usuarios/%s/ext.bin", nome);
    FILE *arq = fopen(tmp, "wb");
    fclose(arq);
    FILE *arq = fopen("moedas.bin", "rb");
    Moeda md;
    while(fread(&md, sizeof(Moeda), 1, arq) == 1){
        snprintf(codigo, sizeof(codigo), "%s", md.codigo);
        codigo[strcspn(codigo, "\n")] = '\0';
        strcat(codigo, "Saldo");
        escVarFloat(tmp, codigo, 0);
    }
    escVarFloat("usuarios.bin", nome, cpf);
    printf("Usuario %s criado com sucesso!!!!\n", nome);
}
