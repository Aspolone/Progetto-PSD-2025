#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H


#include <stdbool.h>
#include <stdio.h>

typedef struct prenotazione* Prenotazione;

#include "Utente.h"
#include "Veicolo.h"

// Prototipi delle funzioni

/*
Funzione che crea una nuova prenotazione

parametri:
u: utente valido che effettua la prenotazione
v: veicolo valido da prenotare
inizio_ora: ora di inizio (0–23)
fine_ora: ora di fine (0–23), deve essere > inizio_ora

precondizioni:
- u e v devono essere puntatori validi
- inizio_ora e fine_ora devono essere compresi tra 0 e 23
- fine_ora deve essere maggiore di inizio_ora
- il veicolo deve essere disponibile nell'intervallo

postcondizioni:
- viene restituita una prenotazione correttamente inizializzata
- il veicolo viene segnato come occupato nell'intervallo indicato
- la prenotazione viene associata all’utente

ritorna:
puntatore alla prenotazione creata, NULL in caso di errore
*/
Prenotazione creaPrenotazione(Utente, Veicolo, int, int);

/*
Funzione che controlla la validità di una prenotazione (disponibilità del veicolo)

parametri:
prenot: puntatore a prenotazione valida

precondizioni:
- prenot deve essere valido
- inizio_data e fine_data devono essere nell'intervallo 0–23

ritorna:
true se tutte le ore richieste sono libere, false altrimenti
*/
bool checkValidita(Prenotazione);

/*
Funzione che calcola il costo della prenotazione (senza sconti)

parametri:
prenot: puntatore a prenotazione valida

precondizioni:
prenot deve essere valido

ritorna:
costo calcolato in base alle ore richieste
*/
float calcolaCosto(Prenotazione);

/*
Funzione che applica eventuali sconti al costo base

parametri:
prenot: prenotazione valida
costo: costo base calcolato

precondizioni:
prenot deve essere valido, costo >= 0

ritorna:
costo aggiornato con eventuali sconti applicati
*/
float applicaSconto(Prenotazione, float);

/*
Funzione che stampa messaggi relativi agli sconti all’utente

parametri:
prenot: prenotazione valida

precondizioni:
prenot deve essere valido

postcondizioni:
messaggi informativi vengono stampati sulla console
*/
void controllaSconto(Prenotazione prenot);

/*
Funzione che imposta lo stato di occupazione per le ore di una prenotazione

parametri:
p: prenotazione valida
x: true per segnare come occupato, false per liberare

precondizioni:
p deve essere valido

postcondizioni:
lo stato delle ore nel veicolo viene aggiornato di conseguenza
*/
void impostaValidita(Prenotazione, bool);

/*
Ottieni l'ora di inizio della prenotazione

parametri:
p: prenotazione valida

ritorna:
intero rappresentante l’ora di inizio
*/
int getInizio(Prenotazione);

/*
Ottieni l'ora di fine della prenotazione

parametri:
p: prenotazione valida

ritorna:
intero rappresentante l’ora di fine
*/
int getFine(Prenotazione);

/*
Ottieni il costo della prenotazione

parametri:
p: prenotazione valida

ritorna:
valore float del costo finale (con eventuali sconti)
*/
float getCosto(Prenotazione);

/*
Ottieni l’utente associato alla prenotazione

parametri:
p: prenotazione valida

ritorna:
puntatore a Utente
*/
Utente getUtente(Prenotazione);

/*
Ottieni l’ID univoco della prenotazione

parametri:
p: prenotazione valida

ritorna:
intero ID della prenotazione
*/
int getID(Prenotazione);

/*
Ottieni il veicolo associato alla prenotazione

parametri:
p: prenotazione valida

ritorna:
puntatore a Veicolo
*/
Veicolo getVeicolo(Prenotazione);

/*
Funzione che aggiunge una prenotazione allo storico su file

parametri:
file: puntatore a FILE aperto in scrittura
prenotazione: prenotazione valida da registrare

precondizioni:
file e prenotazione devono essere validi

postcondizioni:
i dati della prenotazione vengono scritti su file
*/
void aggiungiStorico(FILE*, Prenotazione);

/*
Funzione che stampa a schermo lo storico delle prenotazioni da file

parametri:
fileName: stringa col nome del file

precondizioni:
il file deve esistere ed essere accessibile in lettura

ritorna:
1 se lo storico è stato stampato correttamente
0 se il file è vuoto o non leggibile
*/
int stampaStorico(char*);

/*
Funzione che libera la memoria associata a una prenotazione

parametri:
prenotazione: prenotazione valida

postcondizioni:
la memoria della prenotazione viene liberata
*/
void liberaPrenotazione(Prenotazione prenotazione);

#endif // PRENOTAZIONE_H
