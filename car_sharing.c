#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "item.h"

int main(){

    Utente* nuovoUtente = creaUtente("Ubaldo");
    getNome(nuovoUtente);
    liberaUtente(nuovoUtente);
    return 0;
}