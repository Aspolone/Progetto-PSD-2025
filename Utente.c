#include "utente.h"
#include "Prenotazione.h"
#include <stdlib.h>
#include <string.h>

struct utente {
    char codiceFiscale[16 + 1];
    char* nome;
    int nPrenotazioni; //aggiunta inizio e fine ora
    Prenotazione* prenotazioni;  // Array di puntatori a prenotazioni
};

//adesso riceve input come parametri, successivamente andra' cambiato
Utente creaUtente(char* nome, char* CF) {
    Utente nuovoUtente = malloc(sizeof(struct utente));  // allocazione memoria ad utente
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

int getNPrenot (Utente utente) {
    return utente->nPrenotazioni;
}

void setNPrenot (Utente utente, int n) {
    utente->prenotazioni += n;
}

char* getNome(Utente utente) {
    return utente->nome;
}

char* getCF(Utente utente) {
    return utente->codiceFiscale;
}

Prenotazione getPrenot(Utente utente, int nPrenot) {
    return utente->prenotazioni[nPrenot];
}

void setPrenot(Utente utente, int nPrenot, Prenotazione p) {
    utente->prenotazioni[nPrenot] = p;
}

void aggPrenot(Utente utente, Prenotazione p) {
    utente->prenotazioni[utente->nPrenotazioni] = p;
    utente->nPrenotazioni++;
}

void liberaUtente(Utente utente) {
    if (utente == NULL) return;

    free(utente->nome);

    for (int i = 0; i < utente->nPrenotazioni; i++) {
        if (utente->prenotazioni[i] != NULL)
            free(utente->prenotazioni[i]);
    }

    free(utente->prenotazioni);
    free(utente);
}