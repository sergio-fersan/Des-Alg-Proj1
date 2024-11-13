#include <stdio.h>
#include <direct.h>
#include <string.h>
#include "moedas.h"



int main(){
    // srand((unsigned int)time(NULL));
    // int user = login();
    // menu(user);

    // bcCota 372983.718750
    // ethCota 15155.068359
    // rpCota 3.666251

    float cota1 = buscarCota("Ethereum");
    float cota2 = buscarCota("Bitcoin");
    float cota3 = buscarCota("Ripple");
    printf("%f\n", cota2);
    printf("%f\n", cota1);
    printf("%f\n", cota3);
    
    
    
    return 0;
}
