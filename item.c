#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "item.h"


Utente* creaUtente(char* nome) {
    Utente* nuovoUtente = malloc(sizeof(Utente));  // allocazione memoria ad utente
    if (nuovoUtente == NULL) {
        printf("Errore allocazione utente.\n");
        exit(1);
    }

    nuovoUtente->ID_utente = 1; //TODO serve un diverso metodo per ID, magari lo riceve dal main

    // allocazione memoria per il nuovo nome
    nuovoUtente->nome = malloc(strlen(nome) + 1);
    if (nuovoUtente->nome == NULL) {
        printf("Errore allocazione nome.\n");
        exit(1);
    }
    strcpy(nuovoUtente->nome, nome);

    // allocazione memoria al vettore di prenotazioni
    nuovoUtente->prenotazioni = malloc(10*sizeof(Prenotazione*));
    if (nuovoUtente->prenotazioni == NULL) {
        printf("Errore allocazione prenotazioni.\n");
        exit(1);
    }

    return nuovoUtente;
}

void getNome(Utente* utente) {
    printf("Ecco il nome: %s", utente->nome);
}

void liberaUtente(Utente* utente) {
    free(utente->nome);

    for (int i = 0; i < 10; i++)
        free(utente->prenotazioni[i]);
}
