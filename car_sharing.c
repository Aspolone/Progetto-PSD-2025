#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h"
#include "list.h"
#include "Utente.h"
#include "Veicolo.h"

#define MAX_VEICOLI 100


int main() {
    int numVeicoli;

    printf("Apro il file: veicoli.txt\n");
    FILE* f = fopen("veicoli.txt", "r");
    if (f == NULL) {
        perror("Errore apertura file veicoli.txt");
        exit(1);
    }

    Veicolo** listaVeicoli = caricaVeicoliDaFile("veicoli.txt", &numVeicoli);

    if(numVeicoli == 0) {
        printf("Nessun veicolo caricato.\n");
        return 1;
    }

    Utente* utente = NULL;
    list listaPrenotazioni = newList();

    FILE* fileStorico = fopen("storico.txt", "a");
    if(!fileStorico) {
        printf("Errore apertura file storico.\n");
        return 1;
    }

    int scelta;
    do { // ciclo while per poter far ripetere le prenotazioni

        printf("\n--- MENU ---\n");
        printf("1) Crea utente\n");
        printf("2) Prenota veicolo\n");
        printf("3) Visualizza veicoli'\n");
        printf("4) Visualizza prenotazioni\n");
        printf("0) Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        getchar(); // pulisci \n

        switch(scelta) {
            case 1: {
                if(utente) liberaUtente(utente); // se utente gia esiste (il while ha effettuato piu di un giro di ciclo, lo pulisce e va avanti
                char nome[UTENTE_MAX_NOME];
                char cf[CF_MAX];
                printf("Inserisci nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Inserisci codice fiscale (16 caratteri): ");
                fgets(cf, sizeof(cf), stdin);
                cf[strcspn(cf, "\n")] = 0;
                utente = creaUtente(nome, cf);
                if (utente == NULL) {
                    break;
                } else{
                printf("Utente creato.\n");
                break;
                }
            }
            case 2: {
                if(!utente) {
                    printf("Prima crea un utente!\n"); //
                    break;
                }
                printf("Veicoli disponibili:\n");
                for(int i=0; i<numVeicoli; i++) {
                    printf("%d) %s - %s\n", i+1, listaVeicoli[i]->targa, listaVeicoli[i]->modello);
                }
                int sceltaVeicolo;
                printf("Scegli veicolo (numero): "); //scelta in base ai veicoli dentro il file
                scanf("%d", &sceltaVeicolo);
                if(sceltaVeicolo < 1 || sceltaVeicolo > numVeicoli) { //se il numero é negativo o maggiore non effettua la scelta
                    printf("Scelta non valida.\n");
                    break;
                }
                int inizio, fine;
                printf("Inserisci ora inizio e fine (0-23): ");
                scanf("%d %d", &inizio, &fine);
                if(inizio < 0 || fine > 24 || inizio >= fine) {
                    printf("Orari non validi.\n");
                    break;
                }

                Prenotazione* p = creaPrenotazione(utente, listaVeicoli[sceltaVeicolo - 1], inizio, fine);
                if (p == NULL) {
                    printf("Prenotazione fallita, riprova con orari diversi.\n");
                    break;
                } else {
                listaPrenotazioni = consList(p, listaPrenotazioni);
                aggiungiStorico(fileStorico, p);
                printf("Prenotazione effettuata.\n");
                break;
                }
            }
            case 3: {
                if(isEmptyList(listaPrenotazioni)) {
                    printf("Tutti i veicoli sono liberi.\n");
                } else {
                    stampaVeicoli(numVeicoli, listaVeicoli);
                }
                break;
            }
            case 4: {
                if(isEmptyList(listaPrenotazioni)) {
                    printf("Nessuna prenotazione.\n");
                } else {
                    printf("Prenotazioni:\n");
                    stampaLista(listaPrenotazioni);
                }
                break;
            }
            case 0:
                printf("Uscita...\n");
                break;
            default:
                printf("Scelta non valida.\n");
        }
    } while(scelta != 0);

    fclose(fileStorico);

    // Libera memoria
    if(utente) liberaUtente(utente);

    listaPrenotazioni = freeList(listaPrenotazioni);

    for(int i=0; i<numVeicoli; i++) liberaVeicolo(listaVeicoli[i]);
    free(listaVeicoli);

    return 0;
}