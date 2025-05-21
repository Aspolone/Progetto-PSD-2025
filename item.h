#include <stdbool.h>
#include <stdio.h>

typedef struct utente Utente;
typedef struct veicolo Veicolo;
typedef struct prenotazione Prenotazione;
//il tipo da usare é il nome della struct con la maiuscola

// Struttura Utente
struct utente {
    char codiceFiscale[16 + 1];
    char* nome;
    int nPrenotazioni;
    Prenotazione** prenotazioni;  // Array di puntatori a prenotazioni
};

// Struttura Veicolo
//aggiungere posizione
struct veicolo {
    char targa[7];
    char* modello;
    bool data[24];  // Disponibilità su 24 ore
};

// Struttura Prenotazione
//magari cambia nome da data a ora
struct prenotazione {
    Utente* utente;
    Veicolo* veicolo;
    int inizio_data;// da 0 a 23
    int fine_data;  // Deve essere maggiore di inizio_data
    float costo;
};

// Prototipi delle funzioni
Utente* creaUtente(char* , char*);
Prenotazione* creaPrenotazione(Utente*, Veicolo*, int, int);
Veicolo* creaVeicolo(char*, char*); //da fare

bool checkValidita(Prenotazione*);
float calcolaCosto(Prenotazione *);
float applicaSconto(Prenotazione*, float);

//FILE creaFile(char*); sia per crea che chiudi forse non serve poiché già esistenti
//FILE chiudiFile(FILE*);
void aggiungiStorico(FILE*, Prenotazione*); //da chiamare ogni volta che si aggiunge un nodo alla lista [magari data]
//aggiungere funzioni di caricaDaFile.

void getNome(Utente* utente);
void liberaUtente(Utente* utente);
void liberaVeicolo(Veicolo* veicolo); //da fare
void liberaPrenotazione(Prenotazione* prenotazione); //da fare
