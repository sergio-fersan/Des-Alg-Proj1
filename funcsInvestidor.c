#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    // menu(user);
}

// void consExt(int user){
//     char arquivo[50];
//     // while(1){
//     //     int senhaDigitada;
//     //     printf("Informe sua senha: ");
//     //     scanf("%d", &senhaDigitada);
//     //     char senhaArq[10];
//     //     snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", lerNomeDoCpf(user));
//     //     int senhaInt = (int)lerVarFloat(arquivo, "senha");
//     //     if(senhaDigitada != senhaInt){
//     //         printf("Senha incorreta!! Digite novamente\n");
//     //     } else{
//     //         break;
//     //     }
//     // }
//     snprintf(arquivo, sizeof(arquivo), "usuarios/%s/ext.bin", lerNomeDoCpf(user));
//     char linha[100];
//     FILE *arq = fopen(arquivo, "rb");
//     printf("Extrato da sua conta: \n");
//     while(fread(linha, sizeof(char), sizeof(linha), arq) > 0){
//         printf("%s\n", linha);
//     }
//     fclose(arq);
//     // menu(user);
// }

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

    // time_t t;
    // time(&t);
    // FILE *arq = fopen(arquivo2, "ab");
    // snprintf(linha, sizeof(linha), "Depositou %f reais na data %s", valor, ctime(&t));
    // size_t tamStr = strlen(linha) + 1;
    // fwrite(linha, sizeof(char), strlen(linha), arq);

    printf("Deposito realizado com sucesso!! Saldo atual: %.3f\n", lerVarFloat(arquivo, "reais"));
    // menu(user);
}

void sacarReais(int user){ // FEITO
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
    escVarFloat(arquivo, "reais", (lerVarFloat(arquivo, "reais")) - valor);
    printf("Saque realizado com sucesso!! Saldo atual: %.3f\n", lerVarFloat(arquivo, "reais"));
    // escExt(valor, "r", 2, user);
    // menu(user);
}

void compCrip(int user){
    char arquivo[50];
    // while(1){
    //     int senhaDigitada;
    //     printf("Informe sua senha: ");
    //     scanf("%d", &senhaDigitada);
    //     char senhaArq[10];
    //     snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", lerNomeDoCpf(user));
    //     int senhaInt = (int)lerVarFloat(arquivo, "senha");
    //     if(senhaDigitada != senhaInt){
    //         printf("Senha incorreta!! Digite novamente\n");
    //     } else{
    //         break;
    //     }
    // }

    int esc;
    float valor;
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
    // printf("1. Bitcoin\n"
    // "2. Ethereum\n"
    // "3. Ripple\n");
    // printf("Digite sua escolha: ");
    // scanf("%d", &esc);
    // switch(esc){
    //     case 1:
    //         printf("Comprar Bitcoin\n");
    //         while(1){
    //             printf("Digite o valor em reais: ");
    //             scanf("%f", &valor);
    //             if(valor * txBc > lerVar(arquivo, "rSaldo")){
    //                 printf("Saldo insuficiente!! Digite outro\n");
    //             } else{
    //                 escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") - (valor * txBc)));
    //                 escVar(arquivo, "bcSaldo", (valor/(lerVar(arquivo, "bcCota"))));
    //                 escExt(valor/(lerVar(arquivo, "bcCota")), "bc", 3, user);
    //                 printf("Compra realizada com sucesso!!\n");
    //                 break;
    //             }
    //         }
    //         break;
    //     case 2:
    //         printf("Comprar Ethereum\n");
    //         while(1){
    //             printf("Digite o valor em reais: ");
    //             scanf("%f", &valor);
    //             if(valor * txEth > lerVar(arquivo, "rSaldo")){
    //                 printf("Saldo insuficiente!! Digite outro\n");
    //             } else{
    //                 escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") - (valor * txEth)));
    //                 escVar(arquivo, "ethSaldo", (valor/(lerVar(arquivo, "ethCota"))));
    //                 escExt(valor/(lerVar(arquivo, "ethCota")), "eth", 3, user);
    //                 printf("Compra realizada com sucesso!!\n");
    //                 break;
    //             }
    //         }
    //         break;
    //     case 3:
    //         printf("Comprar Ripple\n");
    //         while(1){
    //             printf("Digite o valor em reais: ");
    //             scanf("%f", &valor);
    //             if(valor * txRp > lerVar(arquivo, "rSaldo")){
    //                 printf("Saldo insuficiente!! Digite outro\n");
    //             } else{
    //                 escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") - (valor * txRp)));
    //                 escVar(arquivo, "rpSaldo", (valor/(lerVar(arquivo, "rpCota"))));
    //                 escExt(valor/(lerVar(arquivo, "rpCota")), "rp", 3, user);
    //                 printf("Compra realizada com sucesso!!\n");
    //                 break;
    //             }
    //         }
    //         break;
    // }
    // menu(user);
}

// void venCrip(int user){
//     float txBc = 0.03;
//     float txEth = 0.02;
//     float txRp = 0.01;

//     char arquivo[25];
//     while(1){
//         char senhaDigitada[10];
//         printf("Informe sua senha: ");
//         scanf("%s", senhaDigitada);
//         char senhaArq[10];
//         snprintf(arquivo, sizeof(arquivo), "user%d/cpfesenha.txt", user);
//         int senhaInt = lerVarInt(arquivo, "senha");
//         snprintf(senhaArq, sizeof(senhaArq), "%d", senhaInt);
//         if(strcmp(senhaDigitada, senhaArq) != 0){
//             printf("Senha incorreta!! Digite novamente\n");
//         } else{
//             break;
//         }
//     }

//     int esc;
//     float valor;
//     float tmp;
//     snprintf(arquivo, sizeof(arquivo), "user%d/dados.txt", user);
//     printf("Saldo de Bitcoin: %.3f\n", lerVar(arquivo, "bcSaldo"));
//     printf("Saldo de Ethereum: %.3f\n", lerVar(arquivo, "ethSaldo"));
//     printf("Saldo de Ripple: %.3f\n", lerVar(arquivo, "rpSaldo"));
//     printf("Criptomoedas disponiveis:\n");
//     printf("1. Bitcoin\n"
//     "2. Ethereum\n"
//     "3. Ripple\n");
//     printf("Digite sua escolha: ");
//     scanf("%d", &esc);
//     switch(esc){
//         case 1:
//             printf("Vender Bitcoin\n");
//             while(1){
//                 printf("Digite o valor em Bitcoin: ");
//                 scanf("%f", &valor);
//                 if(valor > lerVar(arquivo, "bcSaldo")){
//                     printf("Saldo insuficiente!! Digite outro\n");
//                 } else{
//                     tmp = valor * lerVar(arquivo, "bcCota");
//                     escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") + (tmp - (tmp * txBc))));
//                     escVar(arquivo, "bcSaldo", (lerVar(arquivo, "bcSaldo")) - valor);
//                     escExt((lerVar(arquivo, "bcSaldo")) - valor, "bc", 4, user);
//                     printf("Venda realizada com sucesso!!\n");
//                     break;
//                 }
//             }
//             break;
//         case 2:
//             printf("Vender Ethereum\n");
//             while(1){
//                 printf("Digite o valor em Ethereum: ");
//                 scanf("%f", &valor);
//                 if(valor > lerVar(arquivo, "ethSaldo")){
//                     printf("Saldo insuficiente!! Digite outro\n");
//                 } else{
//                     tmp = valor * lerVar(arquivo, "ethCota");
//                     escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") + (tmp - (tmp * txEth))));
//                     escVar(arquivo, "ethSaldo", (lerVar(arquivo, "ethSaldo")) - valor);
//                     escExt((lerVar(arquivo, "ethSaldo")) - valor, "eth", 4, user);
//                     printf("Venda realizada com sucesso!!\n");
//                     break;
//                 }
//             }
//             break;
//         case 3:
//             printf("Vender Ripple\n");
//             while(1){
//                 printf("Digite o valor em Ripple: ");
//                 scanf("%f", &valor);
//                 if(valor > lerVar(arquivo, "rpSaldo")){
//                     printf("Saldo insuficiente!! Digite outro\n");
//                 } else{
//                     tmp = valor * lerVar(arquivo, "rpCota");
//                     escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") + (tmp - (tmp * txRp))));
//                     escVar(arquivo, "rpSaldo", (lerVar(arquivo, "rpSaldo")) - valor);
//                     escExt((lerVar(arquivo, "rpSaldo")) - valor, "rp", 4, user);
//                     printf("Venda realizada com sucesso!!\n");
//                     break;
//                 }
//             }
//             break;
//     }
//     menu(user);
// }

// void atualizar(int user){
//     float valor = (float)rand() / (float)RAND_MAX;
    
//     valor = (valor * 0.1) + 0.95;
//     char arquivo[25];
//     for(int i = 1; i <= 10; i++){
//         snprintf(arquivo, sizeof(arquivo), "user%d/dados.txt", i);
//         escVar(arquivo, "bcCota", (lerVar(arquivo, "bcCota")) * valor);
//         escVar(arquivo, "ethCota", (lerVar(arquivo, "ethCota")) * valor);
//         escVar(arquivo, "rpCota", (lerVar(arquivo, "rpCota")) * valor);
//     }
//     printf("Cotas atualizadas com sucesso!!");
//     menu(user);
// }

// void escExt(float valor, char moeda[], int operacao, int user){ // operacao = 1 pra depositar, 2 pra sacar, 3 pra comprar, 4 pra vender
//     char arquivo[25];
//     snprintf(arquivo, sizeof(arquivo), "user%d/extrato.txt", user);

//     FILE *arq = fopen(arquivo, "a");

//     if(arq == NULL){
//         printf("erro\n");
//     }

//     time_t t;
//     time(&t); // le o horario atual pra imprimir o extrato
    
//     switch(operacao){
//         case 1:
//             if(strcmp(moeda, "r") == 0){
//                 fprintf(arq, "Depositados %.3f em Reais na data %s", valor, ctime(&t));
//             } else if(strcmp(moeda, "bc") == 0){
//                 fprintf(arq, "Depositados %.3f em BitCoin na data %s", valor, ctime(&t));
//             } else if(strcmp(moeda, "eth") == 0){
//                 fprintf(arq, "Depositados %.3f em Ethereum na data %s", valor, ctime(&t));
//             } else{
//                 fprintf(arq, "Depositados %.3f em Ripple na data %s", valor, ctime(&t));
//             }
//             break;
//         case 2:
//             if(strcmp(moeda, "r") == 0){
//                 fprintf(arq, "Sacados %.3f em Reais na data %s", valor, ctime(&t));
//             } else if(strcmp(moeda, "bc") == 0){
//                 fprintf(arq, "Sacados %.3f em BitCoin na data %s", valor, ctime(&t));
//             } else if(strcmp(moeda, "eth") == 0){
//                 fprintf(arq, "Sacados %.3f em Ethereum na data %s", valor, ctime(&t));
//             } else{
//                 fprintf(arq, "Sacados %.3f em Ripple na data %s", valor, ctime(&t));
//             }
//             break;
//         case 3:
//             if(strcmp(moeda, "bc") == 0){
//                 fprintf(arq, "Comprados %.3f em BitCoin na data %s", valor, ctime(&t));
//             } else if(strcmp(moeda, "eth") == 0){
//                 fprintf(arq, "Comprados %.3f em Ethereum na data %s", valor, ctime(&t));
//             } else{
//                 fprintf(arq, "Comprados %.3f em Ripple na data %s", valor, ctime(&t));
//             }
//             break;
//         case 4:
//             if(strcmp(moeda, "bc") == 0){
//                 fprintf(arq, "Vendidos %.3f em BitCoin na data %s", valor, ctime(&t));
//             } else if(strcmp(moeda, "eth") == 0){
//                 fprintf(arq, "Vendidos %.3f em Ethereum na data %s", valor, ctime(&t));
//             } else{
//                 fprintf(arq, "Vendidos %.3f em Ripple na data %s", valor, ctime(&t));
//             }
//             break;
//     }
//     fclose(arq);
// }



// void menu(int user){
//     int esc;
    
//     printf("----------------------------------------\n");
//     printf("Menu:\n");
//     printf("1. Consultar Saldo\n"
//     "2. Consultar Extrato\n"
//     "3. Depositar Reais\n"
//     "4. Sacar Reais\n"
//     "5. Comprar Criptomoedas\n"
//     "6. Vender Criptomoedas\n"
//     "7. Atualizar Cotacao\n"
//     "8. Sair\n");
//     printf("----------------------------------------\n");
//     printf("Digite sua escolha: ");
//     scanf("%d", &esc);
//     switch(esc){
//         case 1:
//             consSaldo(user);
//             break;
//         case 2:
//             consExt(user);
//             break;
//         case 3:
//             depReais(user);
//             break;
//         case 4:
//             sacarReais(user);
//             break;
//         case 5:
//             compCrip(user);
//             break;
//         case 6:
//             venCrip(user);
//         case 7:
//             atualizar(user);
//         case 8:
//             printf("Saindo do programa, tchau!!!!");
//             exit(0);
//     }
// }