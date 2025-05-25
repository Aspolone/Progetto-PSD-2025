#include "Prenotazione.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define TARIFFA 8.0f
#define NUM_PRENOT_SCONTO 3

int prossimoId = 0;

struct prenotazione {
    int id_prenotazione;
    Utente utente;
    Veicolo veicolo;
    int inizio_data;// da 0 a 23
    int fine_data;  // Deve essere maggiore di inizio_data
    float costo;
};

//riempe semplicemente la struct prenot, va aggiunta alla lista con conslist
Prenotazione creaPrenotazione(Utente u, Veicolo v, int i_data, int f_data) {

    Prenotazione nuovaPrenotazione = malloc (sizeof(struct prenotazione));
    if (!nuovaPrenotazione) {
        printf("Errore allocazione prenotazione.\n");
        return NULL;
    }

    nuovaPrenotazione->utente = u;
    nuovaPrenotazione->veicolo = v;

    if ((getNPrenot(u)) == MAX_PRENOTAZIONI) { //controlla il numero di prenotazioni dell'utente prima di continuare
        printf("Numero di prenotazioni massime raggiunto."); //se raggiunge il max non continua
        exit(1);
    }

    nuovaPrenotazione->inizio_data = i_data;
    nuovaPrenotazione->fine_data = f_data;

    if (!checkValidita(nuovaPrenotazione)) {
        printf("Errore di prenotazione, orario occupato.");
        free(nuovaPrenotazione);
        return NULL;
    } else {
        impostaValidita(nuovaPrenotazione, true);
    }

    nuovaPrenotazione->id_prenotazione = prossimoId;
    prossimoId += 1;

    nuovaPrenotazione->costo = calcolaCosto(nuovaPrenotazione);
    aggPrenot(u,nuovaPrenotazione);

    return nuovaPrenotazione;
}

void impostaValidita(Prenotazione p, bool x) {
    int ora = ((p->fine_data - p->inizio_data) % 24 + 24) %24;

    for (int i = 0; i < ora; i++)
        setData(p->veicolo, (p->inizio_data + i) % 24, x);
}

bool checkValidita(Prenotazione prenot) {
    int ora = ((prenot->fine_data - prenot->inizio_data) % 24 + 24) %24;

    for (int i = 0; i < ora; i++) { //per non scorrere tutto il vettore controlla dalla data inizio, fino a data fine
        if (getData(prenot->veicolo, (prenot->inizio_data + i) % 24)) { //aggiunta del modulo per assicurare la ciclicita'
            return false; // già occupato
        }
    }
    return true; // veicolo libero
}


float calcolaCosto (Prenotazione prenot) {
    int ora = ((prenot->fine_data - prenot->inizio_data) % 24 + 24) %24;

    float costo = (float)(ora) * TARIFFA;

    costo = applicaSconto(prenot, costo);

    return costo;
}

void controllaSconto(Prenotazione prenot) {
    int numPrenot = getNPrenot(prenot->utente);
    if (numPrenot > 0 && numPrenot < 3)
        printf("\n[=== Mancano ancora %d prenotazioni, per uno sconto! ===]\n", (NUM_PRENOT_SCONTO - numPrenot) );
    if (numPrenot >= NUM_PRENOT_SCONTO)
        printf("\n[=== Complimenti! sconto del 10%% ottenuto! ===]");
}

float applicaSconto(Prenotazione prenot, float costo) {

    if (prenot->inizio_data >= 22 || prenot->fine_data <= 6)
        costo = costo * 0.90f;

    if (getNPrenot(prenot->utente) > NUM_PRENOT_SCONTO)
        costo = costo * 0.90f;

    return costo;
}

void aggiungiStorico(FILE* file, Prenotazione prenotazione) {
    if (file == NULL || prenotazione == NULL) {
        printf("Errore: file o prenotazione non validi.\n");
        exit(1);
    }

    // Scrive i dati della prenotazione nel file
    fprintf(file, "\nCODICE FISCALE: %s;"
                        "\nTARGA VEICOLO : %s;"
                        "\nINIZIO ORA    : %d;"
                        "\nFINE ORA      : %d.\n", getCF(prenotazione->utente),
                                             getTarga(prenotazione->veicolo),
                                             prenotazione->inizio_data,
                                             prenotazione->fine_data);
    fflush(file);
}

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
    ungetc(c, fp); // rimetti il carattere per non saltare niente

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line); // stampa la riga così com'è
    }

    fclose(fp);
    return 1;
}

int getInizio(Prenotazione p) {
    return p->inizio_data;
}

int getFine(Prenotazione p) {
    return p->fine_data;
}

float getCosto(Prenotazione p) {
    return p->costo;
}

int getID(Prenotazione p) {
    return p->id_prenotazione;
}

Utente getUtente(Prenotazione p) {
    return p->utente;
}

Veicolo getVeicolo(Prenotazione p) {
    return p->veicolo;
}

void liberaPrenotazione(Prenotazione prenotazione) {
    free(prenotazione); // libera solo la prenotazione
}