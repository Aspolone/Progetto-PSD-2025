#include "Utente.h"
#include "Prenotazione.h"


//adesso riceve input come parametri, successivamente andra' cambiato
Utente* creaUtente(char* nome, char* CF) {
    Utente* nuovoUtente = malloc(sizeof(Utente));  // allocazione memoria ad utente
    if (nuovoUtente == NULL) {
        printf("Errore allocazione utente.\n");
        exit(1);
    }
    if (strlen(CF)!=16) {
        printf("Errore codice fiscale, %lu caratteri. Riprova.\n", strlen(CF));
        return NULL;
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

    // allocazione memoria al vettore di prenotazioni di lunghezza MAX_PRENOTAZIONI.
    nuovoUtente->prenotazioni = malloc (MAX_PRENOTAZIONI * sizeof(Prenotazione*));
    if (nuovoUtente->prenotazioni == NULL) {
        printf("Errore allocazione prenotazioni.\n");
        exit(1);
    }

    for (int i = 0; i < MAX_PRENOTAZIONI; i++) { //inizializzo a NULL
        nuovoUtente->prenotazioni[i] = NULL;
    }

    return nuovoUtente;
}


void getNome(Utente* utente) {
    printf("Ecco il nome: %s\n", utente->nome);
}

void liberaUtente(Utente* utente) {
    if (utente == NULL) return;

    free(utente->nome);

    for (int i = 0; i < utente->nPrenotazioni; i++) {
        if (utente->prenotazioni[i] != NULL)
            free(utente->prenotazioni[i]);
    }

    free(utente->prenotazioni);
    free(utente);
}