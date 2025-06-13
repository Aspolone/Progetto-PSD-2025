#include "include/Utente.h"
#include "include/Prenotazione.h"
#include <stdlib.h>
#include <string.h>
#include "include/macro_utili.h"

struct utente {
    char codiceFiscale[16 + 1];
    char* nome;
    int nPrenotazioni; //aggiunta inizio e fine ora
    Prenotazione* prenotazioni;  // Array di puntatori a prenotazioni
};


/*
    Funzione per la creazione e inizializzazione di un utente

    parametri:
        char*: stringa valida con il nome dell’utente
        char*: stringa valida con il codice fiscale

    precondizioni:
        le stringhe in input sono non NULL
        il codice fiscale è lungo esattamente 16 caratteri

    postcondizioni:
        viene allocata dinamicamente una struttura Utente
        viene allocata memoria per il nome dell’utente
        viene allocato un array di puntatori a Prenotazione
        ogni elemento dell’array viene inizializzato a NULL
        il campo nPrenotazioni viene inizializzato a 0

    ritorna:
        Puntatore alla struttura Utente appena creata
        NULL in caso di codice fiscale non valido
        Interrompe il programma in caso di errore di allocazione
*/
Utente creaUtente(char* nome, char* CF) {
    Utente nuovoUtente = malloc(sizeof(struct utente));
    if (nuovoUtente == NULL) {
        printf("Errore allocazione utente.\n");
        exit(1);
    }
    if (strlen(CF)!=16) {
        return NULL;
    }
    else strcpy(nuovoUtente->codiceFiscale, CF);



    nuovoUtente->nome = malloc(strlen(nome) + 1);
    if (nuovoUtente->nome == NULL) {
        printf("Errore allocazione nome.\n");
        exit(1);
    }
    strcpy(nuovoUtente->nome, nome);

    nuovoUtente->nPrenotazioni = 0;


    nuovoUtente->prenotazioni = malloc (MAX_PRENOTAZIONI * sizeof(Prenotazione*));
    if (nuovoUtente->prenotazioni == NULL) {
        printf("Errore allocazione prenotazioni.\n");
        exit(1);
    }

    for (int i = 0; i < MAX_PRENOTAZIONI; i++) {
        nuovoUtente->prenotazioni[i] = NULL;
    }

    return nuovoUtente;
}

/*
    Funzione per ottenere il numero di prenotazioni di un utente

    parametri:
        Utente: puntatore a una struttura Utente valida

    precondizioni:
        Il puntatore Utente è non NULL e punta a una struttura Utente inizializzata correttamente

    postcondizioni:
        Nessuna

    ritorna:
        Il numero di prenotazioni attualmente associate all’utente
*/
int getNPrenot (Utente utente) {
    return utente->nPrenotazioni;
}

/*
    Funzione per ottenere il nome associato a un utente

    parametri:
        Utente: puntatore a una struttura Utente valida

    precondizioni:
        Il puntatore Utente è non NULL
        Il campo nome dell’utente è stato allocato e inizializzato correttamente

    postcondizioni:
        Nessuna

    ritorna:
        Puntatore alla stringa contenente il nome dell’utente
*/
char* getNome(Utente utente) {
    return utente->nome;
}

/*
    Funzione per ottenere il codice fiscale di un utente

    parametri:
        Utente: puntatore a una struttura Utente valida

    precondizioni:
        Il puntatore Utente è non NULL
        Il campo codiceFiscale dell’utente è stato inizializzato correttamente (16 caratteri)

    postcondizioni:
        Nessuna

    ritorna:
        Puntatore alla stringa contenente il codice fiscale dell’utente
*/
char* getCF(Utente utente) {
    return utente->codiceFiscale;
}
/*
    Funzione per ottenere una prenotazione specifica di un utente

    parametri:
        Utente: puntatore a una struttura Utente valida
        int: indice della prenotazione desiderata

    precondizioni:
        Il puntatore Utente è non NULL
        Il campo prenotazioni è stato allocato correttamente
        L’indice fornito è valido

    postcondizioni:
        Nessuna

    ritorna:
        Puntatore alla prenotazione corrispondente all’indice specificato
*/
Prenotazione getPrenot(Utente utente, int nPrenot) {
    return utente->prenotazioni[nPrenot];
}


/*
    Funzione per aggiungere una prenotazione all'elenco di un utente

    parametri:
        Utente: puntatore a una struttura Utente valida
        Prenotazione: struttura Prenotazione da aggiungere

    precondizioni:
        Il puntatore a Utente è non NULL e punta a una struttura Utente valida
        Il numero di prenotazioni dell'utente è minore di MAX_PRENOTAZIONI

    postcondizioni:
        La prenotazione viene aggiunta alla prima posizione libera nell’array di prenotazioni dell’utente
        Il numero di prenotazioni dell’utente viene incrementato di 1

    ritorna:
        1 se l’operazione ha avuto successo,
        0 se il numero massimo di prenotazioni è già stato raggiunto
*/
int aggPrenot(Utente utente, Prenotazione p) {
    if (utente->nPrenotazioni >= MAX_PRENOTAZIONI) {
        printf("Errore: limite prenotazioni superato.\n");
        return -1;
    }
    utente->prenotazioni[utente->nPrenotazioni] = p;
    utente->nPrenotazioni++;
    return 1;
}

/*
    Funzione per liberare tutta la memoria allocata associata a un utente

    parametri:
        Utente: puntatore a una struttura Utente valida o NULL

    precondizioni:
        Il puntatore utente può essere NULL oppure puntare a una struttura Utente allocata dinamicamente
        Se non NULL:
            il campo nome è stato allocato con malloc
            il campo prenotazioni è un array allocato dinamicamente
            gli elementi dell’array prenotazioni che non sono NULL sono anch’essi allocati dinamicamente

    postcondizioni:
        Tutta la memoria associata all’utente viene deallocata
        Se il puntatore è NULL, la funzione non ha effetto

    ritorna:
        Nulla
*/
void liberaUtente(Utente utente) {
    if (utente == NULL) return;

    free(utente->nome);

    free(utente->prenotazioni);
    free(utente);
}