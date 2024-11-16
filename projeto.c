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

    char tmp[100];
    char nomes[10][15] = {"Lineu", "Nene", "Bebel", "Agostinho", "Tuco", "Beicola", "Floriano", "Marilda", "Mendonca", "Genilson"};

    for(int i = 1; i <= 10; i++){
        snprintf(tmp, sizeof(tmp), "usuarios/%s/ext.txt", nomes[i - 1]);
    }

    // int user = login();
    // escVarFloat("usuarios/Agostinho/dados.bin", "reais", 0);
    // depReais(4);
    // depReais(4);
    // depReais(4);
    
    // consExt(4);

    // printf("%f\n", lerVarFloat("usuarios/Agostinho/dados.bin", "senha"));
    
    return 0;
}
