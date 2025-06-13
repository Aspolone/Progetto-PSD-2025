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

char* leggiDaFileSingolaRiga(FILE* f) {
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

    FILE* f_input = NULL;
    FILE* f_oracle = NULL;
    FILE* f_output = NULL;
    char* NOME = NULL;
    char* CF = NULL;
    char* TARGA = NULL;
    char* MODELLO = NULL;
    char* POSIZIONE = NULL;
    char* temp_ora_in = NULL;
    char* temp_ora_fin = NULL;
    Utente nuovoUtente = NULL;
    Veicolo nuovoVeicolo = NULL;
    Prenotazione nuovaPrenotazione = NULL;
    int errore = 0;
    int ORA_IN = 0;
    int ORA_FIN = 0;

    // Apertura file
    f_input = fopen(percorsoInput, "r");
    f_oracle = fopen(percorsoOracle, "r");
    f_output = fopen(percorsoOutput, "w");

    if (!f_input || !f_oracle || !f_output) {
        printf("Errore apertura file\n");
        errore = 1;
        goto cleanup;
    }

    // Lettura dati
    NOME = leggiDaFileSingolaRiga(f_input);
    CF = leggiDaFileSingolaRiga(f_input);
    TARGA = leggiDaFileSingolaRiga(f_input);
    MODELLO = leggiDaFileSingolaRiga(f_input);
    POSIZIONE = leggiDaFileSingolaRiga(f_input);
    temp_ora_in = leggiDaFileSingolaRiga(f_input);
    temp_ora_fin = leggiDaFileSingolaRiga(f_input);

    // Controllo lettura dati
    if (!NOME || !CF || !TARGA || !MODELLO || !POSIZIONE || !temp_ora_in || !temp_ora_fin) {
        printf("Errore lettura dati dal file\n");
        errore = 1;
        goto write_output;
    }

    // Conversione ore
    ORA_IN = atoi(temp_ora_in);
    ORA_FIN = atoi(temp_ora_fin);

    // Validazione orari
    if (ORA_IN < 0 || ORA_IN > 23 || ORA_FIN < 0 || ORA_FIN > 23 || ORA_IN >= ORA_FIN) {
        printf("Orari non validi: %d-%d\n", ORA_IN, ORA_FIN);
        errore = 1;
        goto write_output;
    }

    // Creazione oggetti
    printf("Tentativo creazione utente: %s, %s\n", NOME, CF);
    nuovoUtente = creaUtente(NOME, CF);
    printf("Risultato nuovoUtente: %p\n", (void*)nuovoUtente);
    if (!nuovoUtente) {
        errore = 1;
        printf("ERRORE: creaUtente ha restituito NULL\n");
        goto write_output;
    }

    printf("Tentativo creazione veicolo: %s, %s, %s\n", TARGA, MODELLO, POSIZIONE);
    nuovoVeicolo = creaVeicolo(TARGA, MODELLO, POSIZIONE);
    printf("Risultato nuovoVeicolo: %p\n", (void*)nuovoVeicolo);
    if (!nuovoVeicolo) {
        errore = 1;
        printf("ERRORE: creaVeicolo ha restituito NULL\n");
        goto write_output;
    }

    printf("Tentativo creazione prenotazione: %d-%d\n", ORA_IN, ORA_FIN);
    nuovaPrenotazione = creaPrenotazione(nuovoUtente, nuovoVeicolo, ORA_IN, ORA_FIN);
    printf("Risultato nuovaPrenotazione: %p\n", (void*)nuovaPrenotazione);
    if (!nuovaPrenotazione) {
        errore = 1;
        printf("ERRORE: creaPrenotazione ha restituito NULL\n");
    }

write_output:
    // Scrittura output
    fprintf(f_output, "%s\n", NOME ? NOME : "NULL");
    fprintf(f_output, "%s\n", CF ? CF : "NULL");
    fprintf(f_output, "%s\n", TARGA ? TARGA : "NULL");
    fprintf(f_output, "%s\n", MODELLO ? MODELLO : "NULL");
    fprintf(f_output, "%s\n", POSIZIONE ? POSIZIONE : "NULL");
    fprintf(f_output, "%d\n", ORA_IN);
    fprintf(f_output, "%d\n", ORA_FIN);
    fprintf(f_output, "%s %s", errore ? "PASS" : "FAIL", ID);

    fflush(f_output);
    fclose(f_output);
    f_output = NULL;

    // Confronto con oracle
    f_output = fopen(percorsoOutput, "r");
    if (!f_output) {
        fprintf(testResult, "FAIL %s\n", ID);
        goto cleanup;
    }

    int confronto = confrontaFileRigaPerRiga(f_oracle, f_output);
    printf("Confronto risultato: %d, di ID %s\n", confronto, ID);

    if (confronto == 1) {
        fprintf(testResult, "FAIL %s\n", ID);
    } else {
        fprintf(testResult, "PASS %s\n", ID);
    }

cleanup:
    if (f_input) fclose(f_input);
    if (f_oracle) fclose(f_oracle);
    if (f_output) fclose(f_output);

    if (NOME) free(NOME);
    if (CF) free(CF);
    if (TARGA) free(TARGA);
    if (MODELLO) free(MODELLO);
    if (POSIZIONE) free(POSIZIONE);
    if (temp_ora_in) free(temp_ora_in);
    if (temp_ora_fin) free(temp_ora_fin);

    if (nuovoUtente) liberaUtente(nuovoUtente);
    if (nuovoVeicolo) liberaVeicolo(nuovoVeicolo);
    if (nuovaPrenotazione) liberaPrenotazione(nuovaPrenotazione);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Parametri inseriti errati.\n");
        return 1;  // meglio return 1 che exit(-1)
    }

    printf("argv1: %s, argv2: %s\n\n", argv[1], argv[2]);

    FILE* testSuite = fopen(argv[1], "r");
    FILE* testResult = fopen(argv[2], "w");

    if (!testSuite || !testResult) {
        printf("Errore apertura file testSuite: %s\n", argv[1]);
        fclose(testSuite);
        fclose(testResult);
        return 1;
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
