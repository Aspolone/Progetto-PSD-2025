#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Veicolo.h"

// Struttura Veicolo
//aggiungi char* posizione;
struct veicolo {
    char targa[7];
    char* modello;
    bool data[24];  // Disponibilità su 24 ore
};

#define MODELLO_MAX_NOME 50
#define BUFFER 155
#define MAX_VEICOLI 50

Veicolo creaVeicolo(char* targa, char* modello) {

    Veicolo nuovoVeicolo = malloc(sizeof(struct veicolo));
    if (nuovoVeicolo == NULL) {
        printf("Errore allocazione veicolo.\n");
        exit(1);
    }

    if (strlen(targa) != 7) {
        printf("Errore caratteri targa.\n");
        exit(1);
    }
    strcpy(nuovoVeicolo->targa, targa);

    if (strlen(modello) > MODELLO_MAX_NOME) {
        printf("Errore modello troppo lungo.\n");
        exit(1);
    }

    nuovoVeicolo->modello = malloc(strlen(modello) + 1);
    if (nuovoVeicolo->modello == NULL) {
        printf("Errore allocazione veicolo.\n");
        exit(1);
    }
    strcpy(nuovoVeicolo->modello, modello);

    // Inizializza vettore data a false
    for (int i = 0; i < 24; i++)
        nuovoVeicolo->data[i] = false;

    return nuovoVeicolo;
}

void stampaValidita(Veicolo veicolo) {
    for (int i = 0; i < 24; i++)
        printf("| %dh: %s ", i, veicolo->data[i] ? "no" : "si");
    printf("|\n");
}

Veicolo leggiVeicoloDaRiga(char* riga) {
    char* targa = strtok(riga, ";");
    char* modello = strtok(NULL, ";\n");

    if (targa == NULL || modello == NULL) {
        printf("Errore formato riga veicolo.\n");
        return NULL;
    }

    return creaVeicolo(targa, modello);
}

void stampaVeicoli(int numVeicoli, Veicolo* listaVeicoli) {
    for (int i = 0; i < numVeicoli; i++) {
        printf("\n[%d] %s (targa: %s): \n",
               i + 1,
               getModello(listaVeicoli[i]),
               getTarga(listaVeicoli[i]));
        stampaValidita(listaVeicoli[i]);
    }
}


Veicolo* caricaVeicoliDaFile(const char* nomeFile, int* numVeicoli) {
    FILE* file = fopen(nomeFile, "r");
    if (!file) {
        printf("Errore apertura file veicoli.\n");
        exit(1);
    }

    Veicolo* veicoli = malloc(sizeof(struct veicolo*) * MAX_VEICOLI);
    if (!veicoli) {
        printf("Errore allocazione memoria veicoli.\n");
        exit(1);
    }

    char riga[BUFFER];
    *numVeicoli = 0;

    while (fgets(riga, sizeof(riga), file)) {
        if (*numVeicoli >= MAX_VEICOLI) {
            printf("Raggiunto numero massimo veicoli (%d). Stop caricamento.\n", MAX_VEICOLI);
            break;
        }
        Veicolo v = leggiVeicoloDaRiga(riga);
        if (v != NULL) {
            veicoli[*numVeicoli] = v;
            (*numVeicoli)++;
        }
    }

    fclose(file);
    return veicoli;
}

bool getData(Veicolo veicolo, int i) {
    return veicolo->data[i];
}

void setData(Veicolo veicolo, int i, bool b) {
    veicolo->data[i] = b;
}

char* getModello(Veicolo veicolo) {
    return veicolo->modello;
}

char* getTarga(Veicolo veicolo) {
    return veicolo->targa;
}

void liberaVeicolo(Veicolo veicolo) {
    free(veicolo->modello);
    free(veicolo);
}
