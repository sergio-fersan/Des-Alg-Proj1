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
    int user = login();
    menu(user);
    
    return 0;
}
