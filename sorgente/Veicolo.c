#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Veicolo.h"
#include "macro_utili.h"

// Struttura Veicolo
struct veicolo {
    char targa[7 + 1];
    char* modello;
    char* posizione;
    bool data[24];  // Disponibilità su 24 ore
};
/*
Funzione che crea un nuovo veicolo e alloca memoria per i suoi campi dinamici

parametri:
targa: stringa valida di 7 caratteri
modello: stringa valida con lunghezza <= MODELLO_MAX_NOME
posizione: stringa valida indicante la posizione iniziale del veicolo

precondizioni:
i parametri devono essere stringhe valide e non NULL

postcondizioni:
viene restituito un veicolo con dati correttamente inizializzati, memoria allocata per modello e posizione, disponibilità inizializzata a false

ritorna:
un puntatore a struct veicolo correttamente allocata e inizializzata
*/
Veicolo creaVeicolo(char* targa, char* modello, char* posizione) {
    Veicolo nuovoVeicolo = malloc(sizeof(struct veicolo));
    if (nuovoVeicolo == NULL) {
        printf("Errore allocazione veicolo.\n");
        exit(1);
    }

    if (strlen(targa) != 7) {
        printf("Errore caratteri targa. Nr elem %llu\n", strlen(targa));
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

    nuovoVeicolo->posizione = malloc(strlen(posizione) + 1);
    if (nuovoVeicolo->posizione == NULL) {
        printf("Errore allocazione posizione.\n");
        exit(1);
    }
    strcpy(nuovoVeicolo->posizione, posizione);

    // Inizializza la disponibilità oraria a false (cioè tutte le ore sono disponibili)
    for (int i = 0; i < 24; i++)
        nuovoVeicolo->data[i] = false;

    return nuovoVeicolo;
}

/*
Funzione che stampa la disponibilità oraria di un veicolo

parametri:
veicolo: puntatore a veicolo valido

precondizioni:
veicolo deve essere valido e non NULL

postcondizioni:
stampa su console la disponibilità del veicolo per ogni ora del giorno
*/
void stampaValidita(Veicolo veicolo) {
    for (int i = 0; i < 24; i++)
        printf("| %dh: %s ", i, veicolo->data[i] ? "no" : "si");
    printf("|\n");
}

/*
Funzione che legge una riga formattata e crea un veicolo

parametri:
riga: stringa in formato "targa;modello;posizione"

precondizioni:
riga è una stringa valida e contiene almeno due separatori ';'

postcondizioni:
viene creato un veicolo con i dati letti dalla riga

ritorna:
veicolo creato se i dati sono corretti
NULL se il formato è errato
*/
Veicolo leggiVeicoloDaRiga(char* riga) {
    char* targa = strtok(riga, ";");
    char* modello = strtok(NULL, ";");
    char* posizione = strtok(NULL, ";\n");

    if (targa == NULL || modello == NULL || posizione == NULL) {
        printf("Errore formato riga veicolo.\n");
        return NULL;
    }

    return creaVeicolo(targa, modello, posizione);
}

/*
Funzione che stampa una lista di veicoli

parametri:
numVeicoli: numero di veicoli nella lista
listaVeicoli: array di puntatori a veicoli

precondizioni:
numVeicoli >= 0, listaVeicoli contiene veicoli validi

postcondizioni:
stampa a schermo i dati di ciascun veicolo nella lista
*/
void stampaVeicoli(int numVeicoli, Veicolo* listaVeicoli) {
    for (int i = 0; i < numVeicoli; i++) {
        printf("\n[%d] %s (targa: %s): \n",
               i + 1,
               getModello(listaVeicoli[i]),
               getTarga(listaVeicoli[i]));
        stampaValidita(listaVeicoli[i]);
    }
}

/*
Funzione che carica i veicoli da un file di testo

parametri:
file: puntatore a FILE aperto in lettura
numVeicoli: puntatore a intero dove verrà salvato il numero di veicoli letti

precondizioni:
file deve essere aperto correttamente, numVeicoli deve essere valido

postcondizioni:
alloca un array di veicoli e aggiorna numVeicoli con il numero di veicoli caricati

ritorna:
array di puntatori a veicoli
*/
Veicolo* caricaVeicoliDaFile(FILE* file, int* numVeicoli) {
    Veicolo* veicoli = malloc(sizeof(Veicolo) * MAX_VEICOLI);
    if (!veicoli) {
        printf("Errore allocazione memoria veicoli.\n");
        exit(1);
    }

    char riga[BUFFER];
    *numVeicoli = 0;

    int c = fgetc(file);
    if (c == EOF) {
        printf("Il file e' vuoto.\n");
        fclose(file);
        exit(1);
    }
    rewind(file);

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

/*
Funzione che restituisce la disponibilità in una determinata ora

parametri:
veicolo: veicolo valido
i: indice dell’ora (0-23)

ritorna:
true se occupato, false se disponibile
*/
bool getData(Veicolo veicolo, int i) {
    return veicolo->data[i];
}

/*
Funzione che imposta la disponibilità di una determinata ora

parametri:
veicolo: veicolo valido
i: indice ora (0-23)
b: true se occupato, false se disponibile

postcondizioni:
la disponibilità all’ora indicata viene aggiornata
*/
void setData(Veicolo veicolo, int i, bool b) {
    veicolo->data[i] = b;
}

/*
Funzione che restituisce il modello di un veicolo

parametri:
veicolo: veicolo valido

ritorna:
puntatore alla stringa del modello
*/
char* getModello(Veicolo veicolo) {
    return veicolo->modello;
}

/*
Funzione che restituisce la posizione attuale del veicolo

parametri:
veicolo: veicolo valido

ritorna:
puntatore alla stringa della posizione
*/
char* getPosizione(Veicolo veicolo) {
    return veicolo->posizione;
}

/*
Funzione che restituisce la targa di un veicolo

parametri:
veicolo: veicolo valido

ritorna:
puntatore alla stringa della targa
*/
char* getTarga(Veicolo veicolo) {
    return veicolo->targa;
}

/*
Funzione che libera la memoria allocata per un veicolo

parametri:
veicolo: veicolo valido

postcondizioni:
la memoria occupata da modello, posizione e veicolo viene deallocata
*/
void liberaVeicolo(Veicolo veicolo) {
    free(veicolo->modello);
    free(veicolo->posizione);
    free(veicolo);
/*
Funzione che libera la memoria di un array di veicoli

parametri:
lista: array di puntatori a veicoli
n: numero di veicoli presenti nell’array

precondizioni:
lista deve essere un array valido contenente n puntatori a veicoli inizializzati

postcondizioni:
la memoria occupata da ciascun veicolo viene liberata
l’array stesso (lista) viene deallocato
*/
void liberaVeicoli(Veicolo* lista, int n) {
    for (int i = 0; i < n; i++)
        liberaVeicolo(lista[i]);
    free(lista);
}
