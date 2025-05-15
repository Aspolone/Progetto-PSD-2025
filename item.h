#include <stdbool.h>

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
    int ID_veicolo;
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
bool checkValidita(Prenotazione*);
void getNome(Utente* utente);
void liberaUtente(Utente* utente);

