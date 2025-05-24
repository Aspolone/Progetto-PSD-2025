#ifndef UTENTE_H
#define UTENTE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UTENTE_MAX_NOME 50
#define CF_MAX 17
#define MAX_PRENOTAZIONI 10

typedef struct prenotazione Prenotazione; //servendomi solo
typedef struct utente Utente;

// Struttura Utente
struct utente {
    char codiceFiscale[16 + 1];
    char* nome;
    int nPrenotazioni; //aggiunta inizio e fine ora
    Prenotazione** prenotazioni;  // Array di puntatori a prenotazioni
};

Utente* creaUtente(char* , char*);
void getNome(Utente* utente);
void liberaUtente(Utente* utente);

#endif // UTENTE_H
