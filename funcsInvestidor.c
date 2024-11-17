#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "funcsInvestidor.h"
#include "moedas.h"
#include "variaveis.h"

typedef struct {
    char nome[15];
    float valor;
} VariavelFloat;

typedef struct {
    char nome[15];
    char codigo[5];
    float cota;
    float txCompra;
    float txVenda;
} Moeda;

int login(){ // FEITO
    char usuario[15];
    int cpfDigitado;
    while(1){
        printf("Digite seu CPF: ");
        scanf("%d", &cpfDigitado);
        if(strcmp(lerNomeDoCpf(cpfDigitado), "") == 0){
            printf("CPF nao cadastrado!! Tente outro\n");
        } else{
            snprintf(usuario, sizeof(usuario), "%s", lerNomeDoCpf(cpfDigitado));;
            printf("Login para o usuario %s\n", usuario);
            break;
        }
    }
    int senha;
    char tmp[50];
    snprintf(tmp, sizeof(tmp), "usuarios/%s/dados.bin", usuario);
    while(1){
        printf("Digite sua senha: ");
        scanf("%d", &senha);
        if(senha != (int)lerVarFloat(tmp, "senha")){
            printf("Senha incorreta!!!! Tente novamente\n");
        } else{
            printf("Senha correta!!\n*--------------------------*\n");
            printf("Bem vindo(a), %s!!!!!!\n", usuario);
            break;
        }
    }
    return cpfDigitado;
}

void consSaldo(int user){ // FEITO
    char arquivo[50];
    while(1){
        int senhaDigitada;
        printf("Informe sua senha: ");
        scanf("%d", &senhaDigitada);
        char senhaArq[10];
        snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", lerNomeDoCpf(user));
        int senhaInt = (int)lerVarFloat(arquivo, "senha");
        if(senhaDigitada != senhaInt){
            printf("Senha incorreta!! Digite novamente\n");
        } else{
            break;
        }
    }
    FILE *arq = fopen(arquivo, "rb");
    VariavelFloat var;
    char tmp[20];
    printf("Saldo da sua conta: \n");
    printf("Reais: %.3f\n", lerVarFloat(arquivo, "reais"));
    while(fread(&var, sizeof(VariavelFloat), 1, arq) == 1){
        if(strstr(var.nome, "Saldo") != NULL){
            snprintf(tmp, sizeof(tmp), "%s", var.nome);
            removerSaldo(tmp);
            printf("%s: %.3f\n", lerNomeDoCodigo(tmp), lerVarFloat(arquivo, var.nome));
        }
    }
    fclose(arq);
    menu(user);
}

void depReais(int user){ // FEITO
    float valor;
    char arquivo[50];
    char arquivo2[50];
    char linha[100];
    printf("Digite o valor a ser depositado: ");
    scanf("%f", &valor);
    snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", lerNomeDoCpf(user));
    snprintf(arquivo2, sizeof(arquivo2), "usuarios/%s/ext.bin", lerNomeDoCpf(user));
    escVarFloat(arquivo, "reais", (lerVarFloat(arquivo, "reais")) + valor);

    time_t t;
    time(&t);
    snprintf(linha, sizeof(linha), "Depositou %.3f reais na data %s", valor, ctime(&t));
    escExt(arquivo2, linha);

    printf("Deposito realizado com sucesso!! Saldo atual: %.3f\n", lerVarFloat(arquivo, "reais"));
    menu(user);
}

void sacarReais(int user){ // FEITO
    char arquivo[50];
    char arquivo2[50];
    while(1){
        int senhaDigitada;
        printf("Informe sua senha: ");
        scanf("%d", &senhaDigitada);
        char senhaArq[10];
        snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", lerNomeDoCpf(user));
        int senhaInt = (int)lerVarFloat(arquivo, "senha");
        if(senhaDigitada != senhaInt){
            printf("Senha incorreta!! Digite novamente\n");
        } else{
            break;
        }
    }

    float valor;
    snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", lerNomeDoCpf(user));
    while(1){
        printf("Digite o valor a ser sacado: ");
        scanf("%f", &valor);
        if(valor > lerVarFloat(arquivo, "reais")){
            printf("Saldo insuficiente!! Tente outro valor\n");
        } else{
            break;
        }
    }
    char linha[100];
    time_t t;
    time(&t);
    snprintf(arquivo2, sizeof(arquivo2), "usuarios/%s/ext.bin", lerNomeDoCpf(user));
    snprintf(linha, sizeof(linha), "Sacou %.3f reais na data %s", valor, ctime(&t));
    escExt(arquivo2, linha);
    escVarFloat(arquivo, "reais", (lerVarFloat(arquivo, "reais")) - valor);
    printf("Saque realizado com sucesso!! Saldo atual: %.3f\n", lerVarFloat(arquivo, "reais"));
    menu(user);
}

void compCrip(int user){ // FEITO
    char arquivo[50];
    char arquivo2[50];
    while(1){
        int senhaDigitada;
        printf("Informe sua senha: ");
        scanf("%d", &senhaDigitada);
        char senhaArq[10];
        snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", lerNomeDoCpf(user));
        int senhaInt = (int)lerVarFloat(arquivo, "senha");
        if(senhaDigitada != senhaInt){
            printf("Senha incorreta!! Digite novamente\n");
        } else{
            break;
        }
    }

    snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", lerNomeDoCpf(user));
    printf("Saldo disponivel: %.3f\n", lerVarFloat(arquivo, "reais"));

    FILE *arqMoedas = fopen("moedas.bin", "rb");
    Moeda moedas[20];
    int cont = 0;

    while(fread(&moedas[cont], sizeof(Moeda), 1, arqMoedas) == 1){
        cont++;
        if(cont >= 20){ // limitar pra só 20
            break;
        }
    }
    fclose(arqMoedas);

    printf("Criptomoedas disponiveis:\n");
    for(int i = 0; i < cont; i++){
        printf("%s\n", moedas[i].nome);
    }

    char esc[15];
    int achou = 0;
    char codigo[15];
    float cota, txCompra;
    while(1){
        printf("Digite o nome da criptomoeda que deseja comprar: ");
        scanf("%s", esc);
        for(int i = 0; i < cont; i++){
            if(strcmp(moedas[i].nome, esc) == 0){
                strcpy(codigo, moedas[i].codigo);
                cota = moedas[i].cota;
                txCompra = moedas[i].txCompra;
                achou = 1;
                break;
            }
        }
        if(achou == 0){
            printf("Nome nao registrado!!! Tente outro\n");
        } else{
            break;
        }
    }
    float valor;
    while(1){
        printf("Digite o valor em reais: ");
        scanf("%f", &valor);
        if(valor * txCompra > lerVarFloat(arquivo, "reais")){
            printf("Saldo insuficiente!!! Digite outro\n");
        } else{
            codigo[strcspn(codigo, "\n")] = '\0'; // tira o \n
            strcat(codigo, "Saldo");
            escVarFloat(arquivo, "reais", (lerVarFloat(arquivo, "reais") - (valor * txCompra))); // altera o valor do real
            escVarFloat(arquivo, codigo, (lerVarFloat(arquivo, codigo) + (valor/cota))); // altera o valor da moeda
            char linha[100];
            time_t t;
            time(&t);
            snprintf(arquivo2, sizeof(arquivo2), "usuarios/%s/ext.bin", lerNomeDoCpf(user));
            snprintf(linha, sizeof(linha), "Comprou %.3f em %s na data %s", valor/cota, esc, ctime(&t));
            escExt(arquivo2, linha);
            printf("Compra realizada com sucesso!!!\n");
            break;
        }
    }
    menu(user);
}

void venCrip(int user){ // FEITO
    char arquivo[50];
    char arquivo2[50];
    while(1){
        int senhaDigitada;
        printf("Informe sua senha: ");
        scanf("%d", &senhaDigitada);
        char senhaArq[10];
        snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", lerNomeDoCpf(user));
        int senhaInt = (int)lerVarFloat(arquivo, "senha");
        if(senhaDigitada != senhaInt){
            printf("Senha incorreta!! Digite novamente\n");
        } else{
            break;
        }
    }

    snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", lerNomeDoCpf(user));
    FILE *arq = fopen(arquivo, "rb");
    VariavelFloat var;
    char tmp[20];
    printf("Saldo da sua conta: \n");
    printf("Reais: %.3f\n", lerVarFloat(arquivo, "reais"));
    while(fread(&var, sizeof(VariavelFloat), 1, arq) == 1){
        if(strstr(var.nome, "Saldo") != NULL){
            snprintf(tmp, sizeof(tmp), "%s", var.nome);
            removerSaldo(tmp);
            printf("%s: %.3f\n", lerNomeDoCodigo(tmp), lerVarFloat(arquivo, var.nome));
        }
    }
    fclose(arq);

    FILE *arqMoedas = fopen("moedas.bin", "rb");
    Moeda moedas[20];
    int cont = 0;

    while(fread(&moedas[cont], sizeof(Moeda), 1, arqMoedas) == 1){
        cont++;
        if(cont >= 20){ // limitar pra só 20
            break;
        }
    }
    fclose(arqMoedas);

    printf("Criptomoedas disponiveis:\n");
    for(int i = 0; i < cont; i++){
        printf("%s\n", moedas[i].nome);
    }

    char esc[15];
    int achou = 0;
    char codigo[15];
    float cota, txVenda;
    while(1){
        printf("Digite o nome da criptomoeda que deseja vender: ");
        scanf("%s", esc);
        for(int i = 0; i < cont; i++){
            if(strcmp(moedas[i].nome, esc) == 0){
                strcpy(codigo, moedas[i].codigo);
                cota = moedas[i].cota;
                txVenda = moedas[i].txVenda;
                achou = 1;
                break;
            }
        }
        if(achou == 0){
            printf("Nome nao registrado!!! Tente outro\n");
        } else{
            break;
        }
    }
    float valor;
    float tmp2;
    while(1){
        printf("Digite o valor em %s: ", esc);
        scanf("%f", &valor);
        codigo[strcspn(codigo, "\n")] = '\0'; // tira o \n
        strcat(codigo, "Saldo");
        if(valor > lerVarFloat(arquivo, codigo)){
            printf("Saldo insuficiente!!! Digite outro\n");
        } else{
            tmp2 = valor * lerVarFloat(arquivo, codigo);
            escVarFloat(arquivo, "reais", (lerVarFloat(arquivo, "reais") + (tmp2 - (tmp2 * txVenda)))); // altera o valor do real
            escVarFloat(arquivo, codigo, (lerVarFloat(arquivo, codigo) - valor)); // altera o valor da moeda
            char linha[100];
            time_t t;
            time(&t);
            snprintf(arquivo2, sizeof(arquivo2), "usuarios/%s/ext.bin", lerNomeDoCpf(user));
            snprintf(linha, sizeof(linha), "Vendeu %.3f em %s na data %s", valor, esc, ctime(&t));
            escExt(arquivo2, linha);
            printf("Venda realizada com sucesso!!!\n");
            break;
        }
    }
    menu(user);
}

void atualizar(int user){ // FEITO
    FILE *arq = fopen("moedas.bin", "r+b");

    fseek(arq, 0, SEEK_END);
    long tamArquivo = ftell(arq);
    fseek(arq, 0, SEEK_SET);

    int numMoedas = tamArquivo / sizeof(Moeda);
    Moeda *moedas = (Moeda *)malloc(numMoedas * sizeof(Moeda));

    fread(moedas, sizeof(Moeda), numMoedas, arq);
    srand(time(NULL));
    for(int i = 0; i < numMoedas; i++){
        float fator = ((rand() % 11) - 5) / 100.0f;
        moedas[i].cota = moedas[i].cota * (1 + fator);
    }
    fseek(arq, 0, SEEK_SET);
    fwrite(moedas, sizeof(Moeda), numMoedas, arq);

    free(moedas);

    fclose(arq);
    printf("Cotas de todas as moedas alteradas!!!!\n");
    menu(user);
}

void consExt(int user){ // FEITO
    char arquivo[50];
    char arquivo2[50];
    while(1){
        int senhaDigitada;
        printf("Informe sua senha: ");
        scanf("%d", &senhaDigitada);
        char senhaArq[10];
        snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", lerNomeDoCpf(user));
        int senhaInt = (int)lerVarFloat(arquivo, "senha");
        if(senhaDigitada != senhaInt){
            printf("Senha incorreta!! Digite novamente\n");
        } else{
            break;
        }
    }
    snprintf(arquivo2, sizeof(arquivo2), "usuarios/%s/ext.bin", lerNomeDoCpf(user));
    FILE *arq = fopen(arquivo2, "rb");
    
    size_t tamanho;
    char *str;
    printf("Extrato da sua conta: \n");
    while(fread(&tamanho, sizeof(size_t), 1, arq) == 1){
        str = (char *)malloc(tamanho);
        
        fread(str, sizeof(char), tamanho, arq);
        printf("%s", str);
        free(str);
    }
    
    fclose(arq);
    menu(user);
}



void menu(int user){
    int esc;
    
    printf("----------------------------------------\n");
    printf("Menu:\n");
    printf("1. Consultar Saldo\n"
    "2. Consultar Extrato\n"
    "3. Depositar Reais\n"
    "4. Sacar Reais\n"
    "5. Comprar Criptomoedas\n"
    "6. Vender Criptomoedas\n"
    "7. Atualizar Cotacao\n"
    "8. Sair\n");
    printf("----------------------------------------\n");
    printf("Digite sua escolha: ");
    scanf("%d", &esc);
    switch(esc){
        case 1:
            consSaldo(user);
            break;
        case 2:
            consExt(user);
            break;
        case 3:
            depReais(user);
            break;
        case 4:
            sacarReais(user);
            break;
        case 5:
            compCrip(user);
            break;
        case 6:
            venCrip(user);
        case 7:
            atualizar(user);
        case 8:
            printf("Saindo do programa, tchau!!!!");
            sleep(2);
            exit(0);
    }
}