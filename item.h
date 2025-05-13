typedef struct utente Utente;
typedef struct veicolo Veicolo;
typedef struct prenotazione Prenotazione;
//il tipo da usare é il nome della struct con la maiuscola

// Struttura Utente
struct utente {
    int ID_utente;
    char* nome;
    Prenotazione** prenotazioni;  // Array di puntatori a prenotazioni
};

// Struttura Veicolo
struct veicolo {
    int ID_veicolo;
    char* modello;
    bool data[24];  // Disponibilità su 24 ore
};

// Struttura Prenotazione
struct prenotazione {
    Utente* utente;
    Veicolo* veicolo;
    int inizio_data;
    int fine_data;  // Deve essere maggiore di inizio_data
    float costo;
};

// Prototipi delle funzioni
Utente* creaUtente(char* nome);
void getNome(Utente* utente);
void liberaUtente(Utente* utente);

