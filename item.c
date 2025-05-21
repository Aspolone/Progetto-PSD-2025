#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "item.h"
#define MAX_PRENOTAZIONI 10
#define TARIFFA 8.0f

//adesso ricevce input come parametri, successivamente andra' cambiato
Utente* creaUtente(char* nome, char* CF) {
    Utente* nuovoUtente = malloc(sizeof(Utente));  // allocazione memoria ad utente
    if (nuovoUtente == NULL) {
        printf("Errore allocazione utente.\n");
        exit(1);
    }

    // inserimento CF da utente, non ci sta bisogno di allocare memoria perché
    // il codice fiscale é alfanumerico fisso a 16 cifre

    if (strlen(CF)!=16) {
        printf("Errore codice fiscale. %lu", strlen(CF));
        exit(1);
    }
    else strcpy(nuovoUtente->codiceFiscale, CF);


    // allocazione memoria per il nuovo nome
    nuovoUtente->nome = malloc(strlen(nome) + 1);
    if (nuovoUtente->nome == NULL) {
        printf("Errore allocazione nome.\n");
        exit(1);
    }
    strcpy(nuovoUtente->nome, nome);

    nuovoUtente->nPrenotazioni = 0;

    // allocazione memoria al vettore di prenotazioni di lunghezza 10.
    nuovoUtente->prenotazioni = malloc(MAX_PRENOTAZIONI * sizeof(Prenotazione*));
    if (nuovoUtente->prenotazioni == NULL) {
        printf("Errore allocazione prenotazioni.\n");
        exit(1);
    }

    return nuovoUtente;
}

Veicolo* creaVeicolo() {

}


//creare funzione che crei una prenotazione, prendendo in input utente e il veicolo
//prenot (il parametro) deve essere completato quindi la funzione consList deve essere chiamata da crea prenotazione (a mio parere)

bool checkValidita(Prenotazione* prenot) {
    if (prenot->veicolo->data[prenot->inizio_data]) {
        //controlla se il veicolo è occupato in data inizio
        return false;
    } else {
        for (int i = prenot->inizio_data; i < (prenot->fine_data -prenot->inizio_data); i++)
            prenot->veicolo->data[i] = true;// se false (validita disponibile) allora imposta validitá a true , occupando il veicolo
        return true; //ritorna TRUE poiché il check é andato a buon fine
    } //l'unico vincolo è che le prenotazioni sono minimo 1h
}

float calcolaCosto (Prenotazione* prenot) {
    float costo = (float)(prenot->fine_data - prenot->inizio_data) * TARIFFA;
    applicaSconto(prenot, costo);

    return costo;
}

float applicaSconto(Prenotazione* prenot, float costo) {

    if (prenot->inizio_data >= 22 || prenot->fine_data <= 6)
        costo = costo * 0.90f;

    if (prenot->utente->nPrenotazioni > 3)
        costo = costo * 0.90f;

    return costo;
}

Prenotazione* creaPrenotazione(Utente* u, Veicolo* v, int i_data, int f_data) {

    Prenotazione* nuovaPrenotazione = malloc (sizeof(Prenotazione));

    nuovaPrenotazione->utente = u;
    nuovaPrenotazione->veicolo = v;

    if ((u->nPrenotazioni) == MAX_PRENOTAZIONI) { //controlla il numero di prenotazioni dell'utente prima di continuare
        printf("Numero di prenotazioni massime raggiunto."); //se raggiunge il max non continua
        exit(1);
    }

    if (i_data > f_data) {
        printf("Data di inizio piu' grande della fine."); //controllo idonieta' data
        exit(1);
    } else nuovaPrenotazione->inizio_data = i_data; nuovaPrenotazione->fine_data = f_data;

    if (!checkValidita(nuovaPrenotazione)) { //verifica validita' del veicolo
        printf("Errore di prenotazione, orario occupato.");
        exit(1);
    }

    nuovaPrenotazione->costo = calcolaCosto(nuovaPrenotazione);

    return nuovaPrenotazione;
}

void aggiungiStorico(FILE* file, Prenotazione* prenotazione) {
    if (file == NULL || prenotazione == NULL) {
        printf("Errore: file o prenotazione non validi.\n");
        exit(1);
    }

    // Scrive i dati della prenotazione nel file
    fprintf(file, "\nNOME UTENTE  : %s;"
                        "\nTARGA VEICOLO: %s;"
                        "\nINIZIO ORA   : %d;"
                        "\nFINE ORA     : %d.\n", prenotazione->utente->codiceFiscale,
                                             prenotazione->veicolo->targa,
                                             prenotazione->inizio_data,
                                             prenotazione->fine_data);
}


//aggiungere funzioniFile

void getNome(Utente* utente) {
    printf("Ecco il nome: %s", utente->nome);
}

void liberaUtente(Utente* utente) {
    free(utente->nome); //libera la memoria allocata al nome utente

    for (int i = 0; i < MAX_PRENOTAZIONI; i++)
        free(utente->prenotazioni[i]); //libera la memoria allocata al vettore di prenotazioni
}