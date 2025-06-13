#ifndef VEICOLO_H
#define VEICOLO_H

#include <stdbool.h>
#include <stdio.h>

// Definizione opaca della struttura Veicolo
typedef struct veicolo* Veicolo;

/*
Funzione che crea un nuovo veicolo

parametri:
targa: stringa con la targa del veicolo
modello: stringa con il modello del veicolo
posizione: stringa con la posizione iniziale del veicolo

precondizioni:
- targa, modello e posizione devono essere stringhe non nulle

postcondizioni:
- viene restituito un veicolo correttamente inizializzato con i dati forniti

ritorna:
puntatore al nuovo veicolo, NULL in caso di errore
*/
Veicolo creaVeicolo(char*, char*, char*);

/*
Funzione che crea un veicolo a partire da una riga di testo (es. CSV)

parametri:
riga: stringa contenente i dati del veicolo formattati correttamente

precondizioni:
- riga deve essere una stringa valida, non nulla e ben formattata

postcondizioni:
- viene restituito un veicolo con i dati estratti dalla riga

ritorna:
puntatore al veicolo, NULL in caso di errore
*/
Veicolo leggiVeicoloDaRiga(char* riga);

/*
Funzione che carica un array di veicoli da file

parametri:
file: file aperto in lettura contenente i dati dei veicoli
numVeicoli: puntatore a intero dove salvare il numero di veicoli letti

precondizioni:
- file deve essere valido e aperto
- numVeicoli deve essere un puntatore valido

postcondizioni:
- i veicoli vengono letti dal file e salvati in un array
- numVeicoli viene aggiornato con il numero di elementi

ritorna:
array di veicoli caricati, NULL in caso di errore
*/
Veicolo* caricaVeicoliDaFile(FILE*, int* numVeicoli);

/*
Funzione che stampa a video un array di veicoli

parametri:
n: numero di veicoli
veicoli: array di puntatori a veicoli

precondizioni:
- veicoli deve contenere almeno n elementi validi

postcondizioni:
- vengono stampate le informazioni di ogni veicolo su console
*/
void stampaVeicoli(int, Veicolo*);

/*
Funzione che stampa la validità (disponibilità oraria) di un veicolo

parametri:
v: puntatore a veicolo valido

precondizioni:
- v deve essere un puntatore valido a un veicolo inizializzato

postcondizioni:
- viene stampata la disponibilità oraria del veicolo
*/
void stampaValidita(Veicolo);

/*
Funzione che restituisce lo stato booleano associato a una specifica ora

parametri:
v: puntatore a veicolo
index: ora del giorno (0–23)

precondizioni:
- v deve essere valido
- index deve essere compreso tra 0 e 23

ritorna:
true se il veicolo è occupato in quell’ora, false altrimenti
*/
bool getData(Veicolo, int);

/*
Funzione che imposta lo stato booleano (occupato/libero) per una specifica ora

parametri:
v: puntatore a veicolo
index: ora del giorno (0–23)
value: true per occupato, false per libero

precondizioni:
- v deve essere valido
- index deve essere compreso tra 0 e 23

postcondizioni:
- lo stato dell’ora indicata viene aggiornato con value
*/
void setData(Veicolo, int, bool);

/*
Getter della targa del veicolo

parametri:
v: puntatore a veicolo valido

ritorna:
stringa contenente la targa
*/
char* getTarga(Veicolo);

/*
Getter del modello del veicolo

parametri:
v: puntatore a veicolo valido

ritorna:
stringa contenente il modello
*/
char* getModello(Veicolo);

/*
Getter della posizione corrente del veicolo

parametri:
v: puntatore a veicolo valido

ritorna:
stringa contenente la posizione
*/
char* getPosizione(Veicolo);

/*
Funzione che libera la memoria occupata da un veicolo

parametri:
v: puntatore al veicolo da liberare

postcondizioni:
- la memoria occupata dal veicolo viene rilasciata
*/
void liberaVeicolo(Veicolo);

/*
Funzione che libera la memoria di un array di veicoli

parametri:
veicoli: array di puntatori a veicoli
numVeicoli: numero di veicoli nell’array

precondizioni:
- veicoli deve contenere numVeicoli elementi validi

postcondizioni:
- tutta la memoria dei veicoli viene rilasciata
*/
void liberaVeicoli(Veicolo*, int);

#endif // VEICOLO_H
