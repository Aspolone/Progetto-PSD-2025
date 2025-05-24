#ifndef VEICOLO_H
#define VEICOLO_H

#include <stdbool.h>
#include <stdio.h>

typedef struct veicolo Veicolo;

// Struttura Veicolo

struct veicolo {
    char targa[7];
    char* modello;
    bool data[24];  // Disponibilità su 24 ore
};

//crea veicolo e temporanea
Veicolo* creaVeicolo(char*, char*);
void stampaValidita(Veicolo* veicolo);
void liberaVeicolo(Veicolo* veicolo);

Veicolo* leggiVeicoloDaRiga(char* riga);
Veicolo** caricaVeicoliDaFile(const char* nomeFile, int* numVeicoli);

void stampaVeicoli(int numVeicoli, Veicolo** listaVeicoli);


#endif // VEICOLO_H
