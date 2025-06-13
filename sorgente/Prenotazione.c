#include "Prenotazione.h"
#include <stdlib.h>
#include <stdio.h>
#include "macro_utili.h"

int prossimoId = 0;  // Contatore globale per assegnare ID univoci alle prenotazioni

// Struttura Prenotazione
struct prenotazione {
    int id_prenotazione;
    Utente utente;
    Veicolo veicolo;
    int inizio_data; // Ora di inizio (0-23)
    int fine_data;   // Ora di fine (> inizio_data, entro 23)
    float costo;
};

/*
Funzione che crea una nuova prenotazione

parametri:
u: utente che effettua la prenotazione
v: veicolo da prenotare
i_data: ora di inizio (0-23)
f_data: ora di fine (0-23, deve essere maggiore di i_data)

precondizioni:
utente e veicolo devono essere validi, l'intervallo deve essere coerente

postcondizioni:
crea e restituisce una prenotazione valida, con disponibilità aggiornata e costo calcolato

ritorna:
puntatore a prenotazione se creata con successo, NULL altrimenti
*/
Prenotazione creaPrenotazione(Utente u, Veicolo v, int i_data, int f_data) {
    Prenotazione nuovaPrenotazione = malloc(sizeof(struct prenotazione));
    if (!nuovaPrenotazione) {
        printf("Errore allocazione prenotazione.\n");
        return NULL;
    }

    nuovaPrenotazione->utente = u;
    nuovaPrenotazione->veicolo = v;
    nuovaPrenotazione->inizio_data = i_data;
    nuovaPrenotazione->fine_data = f_data;

    if (!checkValidita(nuovaPrenotazione)) {
        printf("Errore di prenotazione, orario occupato.\n");
        free(nuovaPrenotazione);
        return NULL;
    }

    impostaValidita(nuovaPrenotazione, true);
    nuovaPrenotazione->id_prenotazione = prossimoId++;
    nuovaPrenotazione->costo = calcolaCosto(nuovaPrenotazione);

    aggPrenot(u, nuovaPrenotazione);  // Aggiunge la prenotazione all'utente

    return nuovaPrenotazione;
}

/*
Funzione che imposta la validità delle ore per un veicolo

parametri:
p: prenotazione valida
x: valore da assegnare (true = occupato, false = disponibile)

postcondizioni:
aggiorna la disponibilità del veicolo per l’intervallo della prenotazione
*/
void impostaValidita(Prenotazione p, bool x) {
    int ora = ((p->fine_data - p->inizio_data) % 24 + 24) % 24;

    for (int i = 0; i <= ora; i++)
        setData(p->veicolo, (p->inizio_data + i) % 24, x);
}

/*
Funzione che verifica se l'intervallo della prenotazione è disponibile

parametri:
prenot: prenotazione da verificare

ritorna:
true se tutte le ore sono disponibili, false se almeno una è occupata
*/
bool checkValidita(Prenotazione prenot) {
    int ora = ((prenot->fine_data - prenot->inizio_data) % 24 + 24) % 24;

    for (int i = 0; i <= ora; i++) {
        if (getData(prenot->veicolo, (prenot->inizio_data + i) % 24)) {
            return false; // già occupato
        }
    }
    return true;
}

/*
Funzione che calcola il costo di una prenotazione

parametri:
prenot: prenotazione valida

ritorna:
valore del costo totale, considerando eventuali sconti
*/
float calcolaCosto(Prenotazione prenot) {
    int ora = ((prenot->fine_data - prenot->inizio_data) % 24 + 24) % 24;

    float costo = (float)(ora) * TARIFFA;

    costo = applicaSconto(prenot, costo);

    return costo;
}

/*
Funzione che stampa un messaggio all’utente se è vicino a ottenere uno sconto

parametri:
prenot: prenotazione associata all’utente

postcondizioni:
mostra all’utente se ha diritto a uno sconto
*/
void controllaSconto(Prenotazione prenot) {
    int numPrenot = getNPrenot(prenot->utente);
    if (numPrenot > 0 && numPrenot < 3)
        printf("\n[=== Mancano ancora %d prenotazioni, per uno sconto! ===]\n", (NUM_PRENOT_SCONTO - numPrenot));
    if (numPrenot >= NUM_PRENOT_SCONTO)
        printf("\n[=== Complimenti! sconto del 10%% ottenuto! ===]");
}

/*
Funzione che applica eventuali sconti al costo della prenotazione

parametri:
prenot: prenotazione valida
costo: costo base da modificare

ritorna:
costo aggiornato con eventuali sconti
*/
float applicaSconto(Prenotazione prenot, float costo) {
    if (prenot->inizio_data >= 22 || prenot->fine_data <= 6)
        costo *= 0.90f;

    if (getNPrenot(prenot->utente) > NUM_PRENOT_SCONTO)
        costo *= 0.90f;

    return costo;
}

/*
Funzione che scrive i dati di una prenotazione su un file

parametri:
file: puntatore a FILE aperto in scrittura
prenotazione: prenotazione valida da salvare

precondizioni:
file e prenotazione devono essere validi

postcondizioni:
scrive su file i dati principali della prenotazione
*/
void aggiungiStorico(FILE* file, Prenotazione prenotazione) {
    if (file == NULL || prenotazione == NULL) {
        printf("Errore: file o prenotazione non validi.\n");
        exit(1);
    }

    fprintf(file, "\nCODICE FISCALE: %s;"
                  "\nTARGA VEICOLO : %s;"
                  "\nINIZIO ORA    : %d;"
                  "\nFINE ORA      : %d.\n",
            getCF(prenotazione->utente),
            getTarga(prenotazione->veicolo),
            prenotazione->inizio_data,
            prenotazione->fine_data);
    fflush(file);
}

/*
Funzione che stampa lo storico delle prenotazioni da un file

parametri:
fileName: nome del file da leggere

ritorna:
1 se la lettura è andata a buon fine, 0 altrimenti
*/
int stampaStorico(char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (!fp) {
        printf("Errore apertura file %s\n", fileName);
        return 0;
    }

    int c = fgetc(fp);
    if (c == EOF) {
        printf("Il file è vuoto.\n");
        fclose(fp);
        return 0;
    }

    ungetc(c, fp); // Rimette il carattere per non perderlo

    char line[BUFFER];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line); // Stampa la riga letta
    }

    fclose(fp);
    return 1;
}

/*
Funzione che restituisce l’ora di inizio della prenotazione

parametri:
p: prenotazione valida

ritorna:
ora di inizio (0-23)
*/
int getInizio(Prenotazione p) {
    return p->inizio_data;
}

/*
Funzione che restituisce l’ora di fine della prenotazione

parametri:
p: prenotazione valida

ritorna:
ora di fine (0-23)
*/
int getFine(Prenotazione p) {
    return p->fine_data;
}

/*
Funzione che restituisce il costo della prenotazione

parametri:
p: prenotazione valida

ritorna:
valore del costo in euro
*/
float getCosto(Prenotazione p) {
    return p->costo;
}

/*
Funzione che restituisce l’ID della prenotazione

parametri:
p: prenotazione valida

ritorna:
identificativo univoco della prenotazione
*/
int getID(Prenotazione p) {
    return p->id_prenotazione;
}

/*
Funzione che restituisce l’utente della prenotazione

parametri:
p: prenotazione valida

ritorna:
utente che ha effettuato la prenotazione
*/
Utente getUtente(Prenotazione p) {
    return p->utente;
}

/*
Funzione che restituisce il veicolo prenotato

parametri:
p: prenotazione valida

ritorna:
veicolo prenotato
*/
Veicolo getVeicolo(Prenotazione p) {
    return p->veicolo;
}

/*
Funzione che libera la memoria associata a una prenotazione

parametri:
prenotazione: prenotazione da deallocare

postcondizioni:
la memoria occupata dalla prenotazione viene rilasciata
*/
void liberaPrenotazione(Prenotazione prenotazione) {
    free(prenotazione);
}
