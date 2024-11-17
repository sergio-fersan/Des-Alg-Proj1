#include <stdio.h>
#include <direct.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "moedas.h"
#include "funcsInvestidor.h"
#include "variaveis.h"

int main(){
    srand((unsigned int)time(NULL));
    // int user = login();
    // menu(user);

    // char tmp[100];
    // char nomes[10][15] = {"Lineu", "Nene", "Bebel", "Agostinho", "Tuco", "Beicola", "Floriano", "Marilda", "Mendonca", "Genilson"};

    // for(int i = 1; i <= 10; i++){
    //     snprintf(tmp, sizeof(tmp), "usuarios/%s/ext.bin", nomes[i - 1]);
    //     FILE *arq = fopen(tmp, "wb");
    //     fclose(arq);
    // }

    // int user = login();
    exibirMoedas();
    atualizar(4);
    exibirMoedas();
    // atualizar(4);
    // exibirMoedas();
    

    // printf("%f\n", lerVarFloat("usuarios/Agostinho/dados.bin", "senha"));
    
    return 0;
}
