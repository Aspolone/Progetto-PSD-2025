#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "item.h"

int main(){

    Utente* nuovoUtente = creaUtente("Ubaldo", "1234567891111111");
    printf("cf: %s\n", nuovoUtente->codiceFiscale);
    getNome(nuovoUtente);
    liberaUtente(nuovoUtente);
    return 0;

    //occhio a come si gestisce creaPrenot e aggiungiPrenot nello switch case


    //1 crea utente
    //2 verifica macchine
    //3
}