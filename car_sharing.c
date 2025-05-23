#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "item.h"

int main() {

    //interfaccia grafica che fa inserire nome e cf utente
    // successivamente in crea prenotazione ti fa scegliere il veicolo
    // e crea la prenotazione se checkValidita true

    Utente* nuovoUtente = creaUtente("Ubaldo", "1234567891111111");
    Veicolo* nuovoVeicolo = creaVeicolo("EH103TH","Dacia");
    Prenotazione* nuovaPrenotazione = creaPrenotazione(nuovoUtente, nuovoVeicolo, 12, 14);

    stampaValidita(nuovoVeicolo);
    getNome(nuovoUtente);
    liberaPrenotazione(nuovaPrenotazione);
    return 0;

    //occhio a come si gestisce creaPrenot e aggiungiPrenot nello switch case


    //1 crea utente
    //2 verifica macchine
    //3
}