#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/Prenotazione.h"
#define percorso_MAX 100
#define BUFFER 256



int confrontaFileRigaPerRiga(FILE* f1, FILE* f2) {
    char riga1[BUFFER];
    char riga2[BUFFER];

    while (fgets(riga1, BUFFER, f1) && fgets(riga2, BUFFER, f2)) {

        riga1[strcspn(riga1, "\n")] = '\0';
        riga2[strcspn(riga2, "\n")] = '\0';

        if (strcmp(riga1, riga2) != 0) {
            return 0;  //righe diverse
        }
    }

    return 1;
}

char* leggiDaFileSingolaRiga(FILE* f) {  //TODO da riutilizzare
    char buffer[BUFFER];
    if (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        int lunghezza = strlen(buffer);
        char* riga = malloc(lunghezza + 1);  //asciuga la lunghezza
        if (!riga) return NULL;  //controlla la malloc

        strcpy(riga, buffer);
        return riga;
    }
    return NULL;  // fine file o errore
}

int inizializzaTest(const char* percorsoInput, const char* percorsoOracle, const char* percorsoOutput,
                    FILE** f_input, FILE** f_oracle, FILE** f_output,
                    char** NOME, char** CF, char** TARGA, char** MODELLO, char** POSIZIONE,
                    int* ORA_IN, int* ORA_FIN) {

    *f_input = fopen(percorsoInput, "r");
    if (!*f_input) {
        printf("Errore apertura file input\n");
        return 1;
    }

    *f_oracle = fopen(percorsoOracle, "r");
    if (!*f_oracle) {
        printf("Errore apertura file oracle\n");
        fclose(*f_input);
        return 1;
    }

    *f_output = fopen(percorsoOutput, "w");
    if (!*f_output) {
        printf("Errore apertura file output\n");
        fclose(*f_input);
        fclose(*f_oracle);
        return 1;
    }

    *NOME = leggiDaFileSingolaRiga(*f_input);
    *CF = leggiDaFileSingolaRiga(*f_input);
    *TARGA = leggiDaFileSingolaRiga(*f_input);
    *MODELLO = leggiDaFileSingolaRiga(*f_input);
    *POSIZIONE = leggiDaFileSingolaRiga(*f_input);

    char* temp_ora_in = leggiDaFileSingolaRiga(*f_input);
    char* temp_ora_fin = leggiDaFileSingolaRiga(*f_input);

    if (!temp_ora_in || !temp_ora_fin) {
        free(temp_ora_in);
        free(temp_ora_fin);
        return 1;
    }

    *ORA_IN = atoi(temp_ora_in);
    *ORA_FIN = atoi(temp_ora_fin);

    free(temp_ora_in);
    free(temp_ora_fin);

    return 0;
}

//ID per la sprintf
void testPrenotazione (char* ID, FILE* testResult) {
    printf("ID corrente %s\n", ID);

    char percorsoInput[percorso_MAX];
    char percorsoOracle[percorso_MAX];
    char percorsoOutput[percorso_MAX];

    sprintf(percorsoInput, "test/casi_test/%s_input.txt", ID);
    sprintf(percorsoOracle, "test/casi_test/%s_oracle.txt", ID);
    sprintf(percorsoOutput, "test/casi_test/%s_output.txt", ID);

    FILE *f_input = NULL, *f_oracle = NULL, *f_output = NULL;
    char *NOME = NULL, *CF = NULL, *TARGA = NULL, *MODELLO = NULL, *POSIZIONE = NULL;
    int ORA_IN = 0, ORA_FIN = 0;

    int flag = inizializzaTest(percorsoInput, percorsoOracle, percorsoOutput,
                               &f_input, &f_oracle, &f_output,
                               &NOME, &CF, &TARGA, &MODELLO, &POSIZIONE,
                               &ORA_IN, &ORA_FIN);

    Utente nuovoUtente = creaUtente(NOME, CF);
    if (nuovoUtente == NULL) {
        flag = 1;
    }

    Veicolo nuovoVeicolo = creaVeicolo(TARGA, MODELLO, POSIZIONE);
    if (nuovoVeicolo == NULL){
        flag = 1;
    }

    Prenotazione nuovaPrenotazione = creaPrenotazione(nuovoUtente, nuovoVeicolo, ORA_IN, ORA_FIN);
    if (nuovaPrenotazione == NULL){
        flag = 1;
    }

    fprintf(f_output, "%s\n", getNome(getUtente(nuovaPrenotazione)));
    fprintf(f_output, "%s\n", getCF(getUtente(nuovaPrenotazione)));
    fprintf(f_output, "%s\n", getTarga(getVeicolo(nuovaPrenotazione)));
    fprintf(f_output, "%s\n", getModello(getVeicolo(nuovaPrenotazione)));
    fprintf(f_output, "%s\n", getPosizione(getVeicolo(nuovaPrenotazione)));
    fprintf(f_output, "%d\n", getInizio(nuovaPrenotazione));
    fprintf(f_output, "%d\n", getFine(nuovaPrenotazione));

    if (flag == 0)
        fprintf(f_output, "PASS %s\n", ID);
    else
        fprintf(f_output, "FAIL %s\n", ID);

    fflush(f_output);
    rewind(f_output);

    int confronto = confrontaFileRigaPerRiga(f_oracle, f_output);//in questo caso input ha gli elementi, oracolo quello che mi aspetto (input + fail o pass)
    //quindi il confronto serve a capire il test com'e andato
    //ci sta flag, perché l'errore si puo trovare durante la creazione della prenotazione (orario - CF - TARGA)
    //quindi e' un controllo ulteriore

    if (flag == 0 && confronto == 1)
        fprintf(testResult, "PASS %s\n", ID);
    else
        fprintf(testResult, "FAIL %s\n", ID);

    fclose(f_input);
    fclose(f_oracle);
    fclose(f_output);

    free(NOME);
    free(CF);
    free(TARGA);
    free(MODELLO);
    free(POSIZIONE);
    liberaUtente(nuovoUtente);
    liberaVeicolo(nuovoVeicolo);
    liberaPrenotazione(nuovaPrenotazione);
}

void testControlloPrenotazione (char* ID, FILE* testResult) {
    printf("ID corrente %s\n", ID);

    char percorsoInput[percorso_MAX];
    char percorsoOracle[percorso_MAX];
    char percorsoOutput[percorso_MAX];

    sprintf(percorsoInput, "test/casi_test/%s_input.txt", ID);
    sprintf(percorsoOracle, "test/casi_test/%s_oracle.txt", ID);
    sprintf(percorsoOutput, "test/casi_test/%s_output.txt", ID);

    FILE *f_input = NULL, *f_oracle = NULL, *f_output = NULL;
    char *NOME = NULL, *CF = NULL, *TARGA = NULL, *MODELLO = NULL, *POSIZIONE = NULL;
    int ORA_IN = 0, ORA_FIN = 0;

    int flag = inizializzaTest(percorsoInput, percorsoOracle, percorsoOutput,
                               &f_input, &f_oracle, &f_output,
                               &NOME, &CF, &TARGA, &MODELLO, &POSIZIONE,
                               &ORA_IN, &ORA_FIN);

    Utente nuovoUtente = creaUtente(NOME, CF);
    if (nuovoUtente == NULL) {
        flag = 1;
    }

    Veicolo nuovoVeicolo = creaVeicolo(TARGA, MODELLO, POSIZIONE);
    if (nuovoVeicolo == NULL){
        flag = 1;
    }

    Prenotazione nuovaPrenotazione = creaPrenotazione(nuovoUtente, nuovoVeicolo, ORA_IN, ORA_FIN);
    if (nuovaPrenotazione == NULL){
        flag = 1;
    }

    for (int i = 0; i < 24; i++) {
        int disponibile = getData(getVeicolo(nuovaPrenotazione), i) ? 1 : 0;
        fprintf(f_output, "%d\n", disponibile);
    }

    fflush(f_output);
    fclose(f_output);

    f_output = fopen(percorsoOutput, "r");
    if (!f_output) {
        printf("Errore riapertura file output in lettura\n");
        return;
    }

    int confronto = confrontaFileRigaPerRiga(f_oracle, f_output);

    if (flag == 0 && confronto == 1)
        fprintf(testResult, "PASS %s\n", ID);
    else
        fprintf(testResult, "FAIL %s\n", ID);

    fclose(f_input);
    fclose(f_oracle);
    fclose(f_output);

    free(NOME);
    free(CF);
    free(TARGA);
    free(MODELLO);
    free(POSIZIONE);

    if (nuovoUtente) liberaUtente(nuovoUtente);
    if (nuovoVeicolo) liberaVeicolo(nuovoVeicolo);
    if (nuovaPrenotazione) liberaPrenotazione(nuovaPrenotazione);
}

void testCalcoloCosto (char* ID, FILE* testResult) {
    printf("ID corrente %s\n", ID);

    char percorsoInput[percorso_MAX];
    char percorsoOracle[percorso_MAX];
    char percorsoOutput[percorso_MAX];

    sprintf(percorsoInput, "test/casi_test/%s_input.txt", ID);
    sprintf(percorsoOracle, "test/casi_test/%s_oracle.txt", ID);
    sprintf(percorsoOutput, "test/casi_test/%s_output.txt", ID);

    FILE *f_input = NULL, *f_oracle = NULL, *f_output = NULL;
    char *NOME = NULL, *CF = NULL, *TARGA = NULL, *MODELLO = NULL, *POSIZIONE = NULL;
    int ORA_IN = 0, ORA_FIN = 0;

    int flag = inizializzaTest(percorsoInput, percorsoOracle, percorsoOutput,
                               &f_input, &f_oracle, &f_output,
                               &NOME, &CF, &TARGA, &MODELLO, &POSIZIONE,
                               &ORA_IN, &ORA_FIN);

    Utente nuovoUtente = creaUtente(NOME, CF);
    if (nuovoUtente == NULL) {
        flag = 1;
    }

    Veicolo nuovoVeicolo = creaVeicolo(TARGA, MODELLO, POSIZIONE);
    if (nuovoVeicolo == NULL){
        flag = 1;
    }

    Prenotazione nuovaPrenotazione = creaPrenotazione(nuovoUtente, nuovoVeicolo, ORA_IN, ORA_FIN);
    if (nuovaPrenotazione == NULL){
        flag = 1;
    }

    int costo = calcolaCosto(nuovaPrenotazione);
    fprintf(f_output,"%d\n", costo);

    fflush(f_output);
    fclose(f_output);

    f_output = fopen(percorsoOutput, "r");
    if (!f_output) {
        printf("Errore riapertura file output in lettura\n");
    }

    int confronto = confrontaFileRigaPerRiga(f_oracle, f_output);

    if (flag == 0 && confronto == 1)
        fprintf(testResult, "PASS %s\n", ID);
    else
        fprintf(testResult, "FAIL %s\n", ID);

    fclose(f_input);
    fclose(f_oracle);
    fclose(f_output);

    free(NOME);
    free(CF);
    free(TARGA);
    free(MODELLO);
    free(POSIZIONE);

    if (nuovoUtente) liberaUtente(nuovoUtente);
    if (nuovoVeicolo) liberaVeicolo(nuovoVeicolo);
    if (nuovaPrenotazione) liberaPrenotazione(nuovaPrenotazione);
}

void testStorico (char* ID, FILE* testResult) {
    printf("ID corrente %s\n", ID);

    char percorsoInput[percorso_MAX];
    char percorsoOracle[percorso_MAX];
    char percorsoOutput[percorso_MAX];

    sprintf(percorsoInput, "test/casi_test/%s_input.txt", ID);
    sprintf(percorsoOracle, "test/casi_test/%s_oracle.txt", ID);
    sprintf(percorsoOutput, "test/casi_test/%s_output.txt", ID);

    FILE *f_input = NULL, *f_oracle = NULL, *f_output = NULL;
    char *NOME = NULL, *CF = NULL, *TARGA = NULL, *MODELLO = NULL, *POSIZIONE = NULL;
    int ORA_IN = 0, ORA_FIN = 0;

    int flag = inizializzaTest(percorsoInput, percorsoOracle, percorsoOutput,
                               &f_input, &f_oracle, &f_output,
                               &NOME, &CF, &TARGA, &MODELLO, &POSIZIONE,
                               &ORA_IN, &ORA_FIN);

    Utente nuovoUtente = creaUtente(NOME, CF);
    if (nuovoUtente == NULL) {
        flag = 1;
    }

    Veicolo nuovoVeicolo = creaVeicolo(TARGA, MODELLO, POSIZIONE);
    if (nuovoVeicolo == NULL){
        flag = 1;
    }

    Prenotazione nuovaPrenotazione = creaPrenotazione(nuovoUtente, nuovoVeicolo, ORA_IN, ORA_FIN);
    if (nuovaPrenotazione == NULL){
        flag = 1;
    }

    aggiungiStorico(f_output, nuovaPrenotazione);

    fflush(f_output);
    fclose(f_output);

    f_output = fopen(percorsoOutput, "r");
    if (!f_output) {
        printf("Errore riapertura file output in lettura\n");
    }

    int confronto = confrontaFileRigaPerRiga(f_oracle, f_output);

    if (flag == 0 && confronto == 1)
        fprintf(testResult, "PASS %s\n", ID);
    else
        fprintf(testResult, "FAIL %s\n", ID);

    fclose(f_input);
    fclose(f_oracle);
    fclose(f_output);

    free(NOME);
    free(CF);
    free(TARGA);
    free(MODELLO);
    free(POSIZIONE);

    if (nuovoUtente) liberaUtente(nuovoUtente);
    if (nuovoVeicolo) liberaVeicolo(nuovoVeicolo);
    if (nuovaPrenotazione) liberaPrenotazione(nuovaPrenotazione);
}

int main(int argc, char** argv) {
    //argc > 2, da testare se funzia con argv e argc

    FILE* testSuite = fopen("test/test_suite.txt","r");
    FILE* testResult = fopen("test/test_result.txt", "w");
    if (!testSuite || !testResult) {
        printf("Errore dei file.");
        exit(1);
    }

    char ID[4+1], buffer[BUFFER];

    while (fgets(ID, sizeof(ID), testSuite)) {

        ID[strcspn(ID, "\n")] = '\0';  // rimuove newline
        if (ID[0] == '\0') continue;  // salta righe vuote

        switch (ID[0]) {
            case '1': printf("INIZIO TEST CREA PRENOTAZIONE      --- "); testPrenotazione(ID, testResult); break;
            case '2': printf("INIZIO TEST CONTROLLO PRENOTAZIONE --- "); testControlloPrenotazione(ID, testResult); break;
            case '3': printf("INIZIO TEST CALCOLO DEL COSTO      --- "); testCalcoloCosto(ID, testResult); break;
            case '4': printf("INIZIO TEST DELLO STORICO          --- "); testStorico(ID, testResult); break;
            default: printf("Errore testing\n");
        }
    }
    fclose(testSuite);
    fclose(testResult);
}


