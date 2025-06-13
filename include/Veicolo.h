#ifndef VEICOLO_H
#define VEICOLO_H

#include <stdbool.h>
#include <stdio.h>

// Definizione opaca della struttura Veicolo
typedef struct veicolo* Veicolo;

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
Veicolo creaVeicolo(char*, char*, char*);

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
Veicolo leggiVeicoloDaRiga(char* riga);

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
Veicolo* caricaVeicoliDaFile(FILE*, int* numVeicoli);

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
void stampaVeicoli(int, Veicolo*);

/*
    Funzione che stampa la disponibilità oraria di un veicolo

    parametri:
        veicolo: puntatore a veicolo valido

    precondizioni:
        veicolo deve essere valido e non NULL

    postcondizioni:
        stampa su console la disponibilità del veicolo per ogni ora del giorno
*/
void stampaValidita(Veicolo);

/*
    Funzione che restituisce lo stato di disponibilità all'ora i

    parametri:
        veicolo: puntatore a un veicolo valido
        i: intero che rappresenta l'ora

    precondizioni:
        veicolo != NULL


    postcondizioni:
        restituisce true se il veicolo è disponibile nell'ora i
        restituisce false se il veicolo è occupato nell'ora i o se i è fuori range

    ritorna:
        true se disponibile, false altrimenti
*/
bool getData(Veicolo, int);

/*
    Funzione che imposta lo stato di disponibilità all'ora i

    parametri:
        veicolo: puntatore a un veicolo valido
        i: ora (0-23)
        b: valore booleano da assegnare (true = disponibile, false = occupato)

    precondizioni:
        veicolo != NULL

    postcondizioni:
        veicolo->disponibilita[i] viene impostato a b

    ritorna:
        nulla
*/
void setData(Veicolo, int, bool);

/*
    Funzione che restituisce la targa di un veicolo

    parametri:
        veicolo: puntatore a un veicolo valido

    precondizioni:
        veicolo != NULL

    postcondizioni:
        nessuna modifica allo stato del veicolo

    ritorna:
        puntatore alla stringa contenente la targa del veicolo
*/
char* getTarga(Veicolo);

/*
    Funzione che restituisce il modello di un veicolo

    parametri:
        veicolo: puntatore a un veicolo valido

    precondizioni:
        veicolo != NULL

    postcondizioni:
        nessuna modifica allo stato del veicolo

    ritorna:
        puntatore alla stringa contenente il modello del veicolo
*/
char* getModello(Veicolo);

/*
    Funzione che restituisce la posizione attuale del veicolo

    parametri:
        veicolo: puntatore a un veicolo valido

    precondizioni:
        veicolo != NULL

    postcondizioni:
        nessuna modifica allo stato del veicolo

    ritorna:
        puntatore alla stringa contenente la posizione attuale del veicolo
*/
char* getPosizione(Veicolo);

/*
    Funzione che libera la memoria allocata per un veicolo

    parametri:
        veicolo: puntatore a un veicolo valido

    precondizioni:
        veicolo != NULL
        modello e posizione sono stati allocati dinamicamente (malloc, strdup, ecc.)

    postcondizioni:
        la memoria occupata da modello, posizione e dal veicolo stesso viene deallocata

    ritorna:
        nulla
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
