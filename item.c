#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "item.h"


Utente* creaUtente(char* nome, char* CF) {
    Utente* nuovoUtente = malloc(sizeof(Utente));  // allocazione memoria ad utente
    if (nuovoUtente == NULL) {
        printf("Errore allocazione utente.\n");
        exit(1);
    }

    // inserimento CF da utente, non ci sta bisogno di allocare memoria perché
    // il codice fiscale é alfanumerico fisso a 16 cifre
    
    if (strlen(CF)!=16) {
        printf("Errore codice fiscale. %d", strlen(CF));
        exit(1);
    }
    else strcpy(nuovoUtente->codiceFiscale, CF);


    // allocazione memoria per il nuovo nome
    nuovoUtente->nome = malloc(strlen(nome) + 1);
    if (nuovoUtente->nome == NULL) {
        printf("Errore allocazione nome.\n");
        exit(1);
    }
    strcpy(nuovoUtente->nome, nome);

    nuovoUtente->nPrenotazioni = 0;

    // allocazione memoria al vettore di prenotazioni di lunghezza 10.
    nuovoUtente->prenotazioni = malloc(10*sizeof(Prenotazione*));
    if (nuovoUtente->prenotazioni == NULL) {
        printf("Errore allocazione prenotazioni.\n");
        exit(1);
    }

    return nuovoUtente;
}


//creare funzione che crei una prenotazione, prendendo in input utente e il veicolo
//prenot (il parametro) deve essere completato quindi la funzione consList deve essere chiamata da crea prenotazione (a mio parere)

bool checkValidita(Prenotazione* prenot) {
    if (prenot->veicolo->data[prenot->inizio_data]) {
        //se true, significa che il veicolo ha inizio data occupata, perció non é prenotabile 
        return false;
    } else {
        for (int i = prenot->inizio_data; i < (prenot->inizio_data -prenot->fine_data); i++)
            prenot->veicolo->data[i] = true;// se false (validita disponibile) allora imposta validitá a true , occupando il veicolo
        return true; //ritorna TRUE poiché il check é andato a buon fine
    }
}

Prenotazione* creaPrenotazione(Utente* u, Veicolo* v, int i_data, int f_data) {

    Prenotazione* nuovaPrenotazione = malloc (sizeof(Prenotazione));

    nuovaPrenotazione->utente = u;
    nuovaPrenotazione->veicolo = v;

    if (i_data > f_data) {
        printf("Data di inizio piu' grande della fine.");
        exit(1);
    } else nuovaPrenotazione->inizio_data = i_data; nuovaPrenotazione->fine_data = f_data;

    if (!checkValidita(nuovaPrenotazione)) {
        printf("Errore di prenotazione, orario occupato.");
        exit(1);
    }

    //calcolaCosto();

    return nuovaPrenotazione;
}

void getNome(Utente* utente) {
    printf("Ecco il nome: %s", utente->nome);
}

void liberaUtente(Utente* utente) {
    free(utente->nome);

    for (int i = 0; i < 10; i++)
        free(utente->prenotazioni[i]);
}
