#include <stdio.h>
#include <direct.h>
#include <string.h>
#include "moedas.h"
#include "funcsInvestidor.h"
#include "variaveis.h"

int main(){
    // srand((unsigned int)time(NULL));
    // int user = login();
    // menu(user);

    char tmp[30];
    char nomes[10][15] = {"Lineu", "Nene", "Bebel", "Agostinho", "Tuco", "Beicola", "Floriano", "Marilda", "Mendonca", "Genilson"};

    for(int i = 1; i <= 10; i++){
        snprintf(tmp, sizeof(tmp), "usuarios/%s/dados.bin", nomes[i - 1]);
        escVarFloat(tmp, "reais", 0);
        escVarFloat(tmp, "bcSaldo", 0);
        escVarFloat(tmp, "ethSaldo", 0);
        escVarFloat(tmp, "xrpSaldo", 0);
    }

    // int user = login();
    // consSaldo(user);
    
    return 0;
}
