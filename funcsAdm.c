#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <time.h>
#include <unistd.h>
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

typedef struct {
    char nome[15];
    float valor;
} VariavelFloat;

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
    FILE *arq = fopen("moedas.bin", "rb");
    Moeda md;
    while(fread(&md, sizeof(Moeda), 1, arq) == 1){
        snprintf(codigo, sizeof(codigo), "%s", md.codigo);
        codigo[strcspn(codigo, "\n")] = '\0';
        strcat(codigo, "Saldo");
        escVarFloat(tmp, codigo, 0);
    }
    snprintf(tmp, sizeof(tmp), "usuarios/%s/ext.bin", nome);
    FILE *arq1 = fopen(tmp, "wb");
    fclose(arq1);
    escVarFloat("usuarios.bin", nome, cpf);
    printf("Usuario %s criado com sucesso!!!!\n", nome);
}

void excluirUsuario(){ // FEITO
    int cpf;
    char nome[15];
    int esc;
    char tmp[50];
    while(1){
        printf("Digite o CPF do usuario a ser excluido: ");
        scanf("%d", &cpf);
        snprintf(nome, sizeof(nome), "%s", lerNomeDoCpf(cpf));
        if(strcmp(nome, "") == 0){
            printf("CPF nao registrado!! Tente outro\n");
        } else{
            printf("CPF encontrado!!\n");
            break;
        }
    }
    printf("Nome: %s, CPF: %d\n", nome, cpf);
    while(1){
        printf("Tem certeza que deseja excluir %s? Digite 1 para sim e 0 para nao\n", nome);
        scanf("%d", &esc);
        if(esc != 0 && esc != 1){
            printf("Opcao invalida!!\n");
        } else if(esc == 0){
            break;
        } else{
            excluirVar("usuarios.bin", nome);
            snprintf(tmp, sizeof(tmp), "usuarios/%s/dados.bin", nome);
            remove(tmp);
            snprintf(tmp, sizeof(tmp), "usuarios/%s/ext.bin", nome);
            remove(tmp);
            snprintf(tmp, sizeof(tmp), "usuarios/%s", nome);
            rmdir(tmp);
            
            printf("Usuario excluido com sucesso!!\n");
            break;
        }
    }
}

void criarMoeda(){ // FEITO
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

    FILE *arq2 = fopen("usuarios.bin", "rb");
    VariavelFloat var;
    char tmp[50];
    char codigo[15];
    while(fread(&var, sizeof(VariavelFloat), 1, arq) == 1){
        snprintf(tmp, sizeof(tmp), "usuarios/%s/dados.bin", var.nome);
        snprintf(codigo, sizeof(codigo), "%s", md.codigo);
        codigo[strcspn(codigo, "\n")] = '\0';
        strcat(codigo, "Saldo");
        escVarFloat(tmp, codigo, 0);
    }

    printf("Moeda criada com sucesso!!!!\n");
}

void excluirMoeda(){ // FEITO
    int achou = 0;
    char tmp[30];
    char tmp2[50];
    char codigo[15];
    Moeda md;
    VariavelFloat var;
    exibirMoedas();
    FILE *arqUsuarios = fopen("usuarios.bin", "rb");
    while(1){
        printf("Digite o nome da moeda a ser excluida: ");
        fgets(tmp, 30, stdin);
        tmp[strcspn(tmp, "\n")] = '\0';
        FILE *arq = fopen("moedas.bin", "rb");
        FILE *arqTmp = fopen("tmp.bin", "wb");
        
        while(fread(&md, sizeof(Moeda), 1, arq) == 1){
            if(strcmp(md.nome, tmp) == 0){
                achou = 1;
            } else{
                fwrite(&md, sizeof(Moeda), 1, arqTmp);
            }
        }
        fclose(arq);
        fclose(arqTmp);
        
        if(achou != 1){
            printf("Moeda nao encontrada!! Tente novamente\n");
            remove("tmp.bin");
        } else{
            remove("moedas.bin");
            rename("tmp.bin", "moedas.bin");
            while(fread(&var, sizeof(VariavelFloat), 1, arqUsuarios) == 1){
                snprintf(tmp2, sizeof(tmp2), "usuarios/%s/dados.bin", var.nome);
                snprintf(codigo, sizeof(codigo), "%s", md.codigo);
                codigo[strcspn(codigo, "\n")] = '\0';
                strcat(codigo, "Saldo");
                excluirVar(tmp2, codigo);
            }

            printf("Moeda excluida com sucesso!!\n");
            break;
        }
    }
    fclose(arqUsuarios);
}

void consSaldoInv(){ // FEITO
    int cpf;
    char arquivo[50];
    char nome[15];
    while(1){
        printf("Digite o CPF do usuario que deseja ver o saldo: ");
        scanf("%d", &cpf);
        snprintf(nome, sizeof(nome), "%s", lerNomeDoCpf(cpf));
        if(strcmp(nome, "") == 0){
            printf("CPF nao registrado!! Tente outro\n");
        } else{
            break;
        }
    }
    
    snprintf(arquivo, sizeof(arquivo), "usuarios/%s/dados.bin", nome);
    FILE *arq = fopen(arquivo, "rb");
    VariavelFloat var;
    char tmp[20];
    printf("Saldo da conta de %s: \n", nome);
    printf("Reais: %.3f\n", lerVarFloat(arquivo, "reais"));
    while(fread(&var, sizeof(VariavelFloat), 1, arq) == 1){
        if(strstr(var.nome, "Saldo") != NULL){
            snprintf(tmp, sizeof(tmp), "%s", var.nome);
            removerSaldo(tmp);
            printf("%s: %.3f\n", lerNomeDoCodigo(tmp), lerVarFloat(arquivo, var.nome));
        }
    }
    fclose(arq);
}

void consExtInv(){ // FEITO
    int cpf;
    char arquivo[50];
    char nome[15];
    while(1){
        printf("Digite o CPF do usuario que deseja ver o extrato: ");
        scanf("%d", &cpf);
        snprintf(nome, sizeof(nome), "%s", lerNomeDoCpf(cpf));
        if(strcmp(nome, "") == 0){
            printf("CPF nao registrado!! Tente outro\n");
        } else{
            break;
        }
    }

    snprintf(arquivo, sizeof(arquivo), "usuarios/%s/ext.bin", lerNomeDoCpf(cpf));
    FILE *arq = fopen(arquivo, "rb");
    
    size_t tamanho;
    char *str;
    printf("Extrato da conta de %s: \n", nome);
    while(fread(&tamanho, sizeof(size_t), 1, arq) == 1){
        str = (char *)malloc(tamanho);
        
        fread(str, sizeof(char), tamanho, arq);
        printf("%s", str);
        free(str);
    }
    
    fclose(arq);
}

void atualizarAdm(){ // FEITO
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
}

void menuAdm(){
    int esc;
    
    printf("----------------------------------------\n");
    printf("Menu:\n");
    printf("1. Cadastrar Novo Investidor\n"
    "2. Excluir Investidor\n"
    "3. Cadastrar Nova Criptomoeda\n"
    "4. Excluir Criptomoeda\n"
    "5. Consultar Saldo de um Investidor\n"
    "6. Consultar Extrato de um Investidor\n"
    "7. Atualizar Cotacao\n"
    "8. Sair\n");
    printf("----------------------------------------\n");
    printf("Digite sua escolha: ");
    scanf("%d", &esc);
    switch(esc){
        case 1:
            criarUsuario();
            break;
        case 2:
            excluirUsuario();
            break;
        case 3:
            criarMoeda();
            break;
        case 4:
            excluirMoeda();
            break;
        case 5:
            consSaldoInv();
            break;
        case 6:
            consExtInv();
        case 7:
            atualizarAdm();
        case 8:
            printf("Saindo do programa, tchau!!!!");
            sleep(2);
            exit(0);
    }
}