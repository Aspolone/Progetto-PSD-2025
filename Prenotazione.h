#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H


#include <stdbool.h>
#include <stdio.h>

typedef struct prenotazione* Prenotazione;

#include "utente.h"
#include "veicolo.h"

// Prototipi delle funzioni
Prenotazione creaPrenotazione(Utente, Veicolo, int, int);
bool checkValidita(Prenotazione);
float calcolaCosto(Prenotazione );
float applicaSconto(Prenotazione, float);
void controllaSconto(Prenotazione prenot);
void impostaValidita(Prenotazione, bool);


int getInizio(Prenotazione);
int getFine(Prenotazione);
float getCosto(Prenotazione);
Utente getUtente(Prenotazione);
int getID(Prenotazione);
Veicolo getVeicolo(Prenotazione);

//void stampaPrenotazione(Prenotazione*);
void aggiungiStorico(FILE*, Prenotazione); //da chiamare ogni volta che si aggiunge un nodo alla lista [magari data]
int stampaStorico(char*);

void liberaPrenotazione(Prenotazione prenotazione);


#endif // PRENOTAZIONE_H
