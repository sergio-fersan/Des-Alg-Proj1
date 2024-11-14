#include <stdio.h>
#include <direct.h>
#include <string.h>
#include "moedas.h"
#include "funcsInvestidor.h"


int main(){
    // srand((unsigned int)time(NULL));
    // int user = login();
    // menu(user);

    // char tmp[30];
    // char nomes[10][15] = {"Lineu", "Nene", "Bebel", "Agostinho", "Tuco", "Beicola", "Floriano", "Marilda", "Mendonca", "Genilson"};

    // for(int i = 1; i <= 10; i++){
    //     snprintf(tmp, sizeof(tmp), "usuarios/%s/dados.bin", lerNomeDoCpf(i));
    //     escVarFloat(tmp, "bcSaldo", 100);
    // }

    int user = login();
    consSaldo(user);
    
    return 0;
}
