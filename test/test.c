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

//ID per la sprintf
void testPrenotazione(char* ID, FILE* testResult) {

    printf("ID corrente %s\n", ID);

    char percorsoInput[percorso_MAX];
    char percorsoOracle[percorso_MAX];
    char percorsoOutput[percorso_MAX];

    sprintf(percorsoInput, "test/casi_test/%s_input.txt", ID);
    sprintf(percorsoOracle, "test/casi_test/%s_oracle.txt", ID);
    sprintf(percorsoOutput, "test/casi_test/%s_output.txt", ID);

    FILE* f_input = fopen(percorsoInput, "r");
    if (!f_input) {
        printf("Errore apertura file input\n");
        return;
    }

    FILE* f_oracle = fopen(percorsoOracle, "r");
    if (!f_oracle) {
        printf("Errore apertura file oracle\n");
        fclose(f_input);
        return;
    }

    FILE* f_output = fopen(percorsoOutput, "w");
    if (!f_output) {
        printf("Errore apertura file output\n");
        fclose(f_input);
        fclose(f_oracle);
        return;
    }

    char* NOME = leggiDaFileSingolaRiga(f_input);
    char* CF = leggiDaFileSingolaRiga(f_input);
    char* TARGA = leggiDaFileSingolaRiga(f_input);
    char* MODELLO = leggiDaFileSingolaRiga(f_input);
    char* POSIZIONE = leggiDaFileSingolaRiga(f_input);

    char* temp_ora_in = leggiDaFileSingolaRiga(f_input);
    if (temp_ora_in == NULL) return; //controlla se il puntatore ricevuto dalla funzione e' NULL
    int ORA_IN = atoi(temp_ora_in);

    char* temp_ora_fin = leggiDaFileSingolaRiga(f_input);
    if (temp_ora_fin == NULL) return;
    int ORA_FIN = atoi(temp_ora_fin);
    //perche' l'input e' nativo stringa, quindi cambio di tipo

    Utente nuovoUtente = creaUtente(NOME, CF);
    if (nuovoUtente == NULL) {
        fprintf(f_output, "NOT PASS (utente) %s\n", ID);
        return;
    }

    Veicolo nuovoVeicolo = creaVeicolo(TARGA, MODELLO, POSIZIONE);
    if (nuovoVeicolo == NULL){
        fprintf(f_output, "NOT PASS (veicolo) %s\n", ID);
        return;
    }
    Prenotazione nuovaPrenotazione = creaPrenotazione(nuovoUtente, nuovoVeicolo, ORA_IN, ORA_FIN);
    if (nuovaPrenotazione == NULL){
        fprintf(f_output, "NOT PASS (prenotazione) %s\n", ID);
        return;
    }

    fprintf(f_output, "PASS %s\n", ID);

    /*
    fprintf(f_output, "%s\n", getNome(getUtente(nuovaPrenotazione)));
    fprintf(f_output, "%s\n", getCF(getUtente(nuovaPrenotazione)));
    fprintf(f_output, "%s\n", getTarga(getVeicolo(nuovaPrenotazione)));
    fprintf(f_output, "%s\n", getModello(getVeicolo(nuovaPrenotazione)));
    fprintf(f_output, "%s\n", getPosizione(getVeicolo(nuovaPrenotazione)));
    fprintf(f_output, "%d\n", getInizio(nuovaPrenotazione));
    fprintf(f_output, "%d\n", getFine(nuovaPrenotazione));
    */

    int confronto = confrontaFileRigaPerRiga(f_oracle, f_output);

    if (confronto == 1)
        fprintf(testResult, "PASS %s\n", ID);
    else
        fprintf(testResult, "NOT PASS %s\n", ID);


    fclose(f_input);
    fclose(f_oracle);
    fclose(f_output);

    free(temp_ora_in);
    free(temp_ora_fin);
    liberaUtente(nuovoUtente);
    liberaVeicolo(nuovoVeicolo);
    liberaPrenotazione(nuovaPrenotazione);
}

int main(int argc, char** argv) {
    //argc > 2, da testare se funzia con argv e argc

    FILE* testSuite = fopen("test/test_suite.txt","r");
    FILE* testResult = fopen("test/test_result.txt", "a");
    if (!testSuite || !testResult) {
        printf("Errore dei file.");
        exit(1);
    }

    char ID[4+1];

    while (fgets(ID, sizeof(ID), testSuite)) {

        ID[strcspn(ID, "\n")] = '\0';  // rimuove newline
        if (ID[0] == '\0') continue;  // salta righe vuote

        switch (ID[0]) {
            case '1': printf("INIZIO TEST CREA PRENOTAZIONE --- "); testPrenotazione(ID, testResult); break;
            case '2': printf("\nTESTING CHECKPRENOT..."); break;
            case '3': printf("\nTESTING 3..."); break;
            case '4': printf("\nTESTING 4..."); break;
            default: printf("Errore testing\n");
        }
    }
    fclose(testSuite);
    fclose(testResult);
}


