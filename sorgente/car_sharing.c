#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Prenotazione.h"
#include "../include/list.h"
#include "../include/Utente.h"
#include "../include/Veicolo.h"
#include "../include/macro_utili.h"

int main() {
    int numVeicoli;

    printf("Apro il file: veicoli.txt\n"); //apre il file veicoli
    FILE* f = fopen("sorgente/veicoli.txt", "r"); //crea puntatore a file veicoli
    if (f == NULL) { //controllo di corretta apertura del FILE
        perror("Errore apertura file veicoli.txt");
        exit(1);
    }

    Veicolo* listaVeicoli = caricaVeicoliDaFile(f ,&numVeicoli); //associa ad un vettore i veicoli letti all'interno del file
    if (listaVeicoli == NULL) {
        printf("Errore: nessun veicolo caricato!\n");
        exit(1);
    }

    Utente utente = NULL;
    list listaPrenotazioni = nuovaLista();

    FILE* fileStorico = fopen("sorgente/storico.txt", "a");
    if(!fileStorico) {
        printf("Errore apertura file storico.\n");
        return 1;
    }

    int scelta;
    do { // ciclo while per poter far ripetere la selezione

        printf("\n--- MENU ---\n");
        printf("1) Crea utente\n");
        printf("2) Prenota veicolo\n");
        printf("3) Visualizza veicoli\n");
        printf("4) Visualizza prenotazioni\n");
        printf("5) Elimina prenotazione\n");
        printf("6) Stampa storico\n");
        printf("0) Esci\n");
        printf("Scelta: ");

        int inputCheck = 0;//metodo per fare in modo di accettare solo numeri come input.
        do{
            inputCheck = scanf("%d", &scelta); //perche la scanf ritorna il numero di valori assegnati ad una variabile
            getchar(); //pulisce l'input
        }while(!inputCheck); // se si inserisce una stringa, non trova l'intero, essendo lo specificatore %d. Quindi la scanf(); restituisce 0, facendo ripetere l'input.

        switch(scelta) {
            case 1: {
                if(utente) liberaUtente(utente); // se utente gia esiste (il while ha effettuato piu di un giro di ciclo, lo pulisce e va avanti)
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
                printf("\n[=== TARIFFA FISSA DI: %.2f$/h ===]\n", TARIFFA);
                printf("Veicoli disponibili:\n");
                for(int i=0; i<numVeicoli; i++) {
                    printf("%d) %s - %s - %s\n", i+1, getTarga(listaVeicoli[i]), getModello(listaVeicoli[i]), getPosizione(listaVeicoli[i]));
                }
                int sceltaVeicolo;
                printf("Scegli veicolo (numero): "); //scelta in base ai veicoli dentro il file
                scanf("%d", &sceltaVeicolo);
                if(sceltaVeicolo < 1 || sceltaVeicolo > numVeicoli) { //se il numero é negativo o maggiore non effettua la scelta
                    printf("Scelta non valida.\n");
                    break;
                }
                int inizio, fine;
                printf("\n[=== Prezzo ridotto del 10%% tra le 22 e le 06 ===]\n");
                printf("Inserisci ora inizio: ");
                scanf("%d", &inizio);
                printf("Inserisci ora fine: ");
                scanf("%d", &fine);
                if (inizio < 0 || inizio > 23 || fine < 0 || fine > 23 || inizio == fine) {
                    printf("Orari non validi. Per selezionare una sola ora [h_inizio] - [h_inizio + 1] .\n");
                    break;
                }

                Prenotazione p = creaPrenotazione(utente, listaVeicoli[sceltaVeicolo - 1], inizio, fine); //scelta veicolo -1 perché ci sta un offset da vettore
                if (p == NULL) {
                    printf("Prenotazione fallita, riprova con orari diversi.\n");
                    break;
                } else {
                listaPrenotazioni = aggLista(p, listaPrenotazioni);
                aggiungiStorico(fileStorico, p);
                printf("Prenotazione effettuata.\n");
                controllaSconto(p);
                break;
                }
            }
            case 3: {
                if(isEmptyList(listaPrenotazioni)) {
                    printf("Tutti i veicoli sono liberi.\n");
                } else
                    stampaVeicoli(numVeicoli, listaVeicoli);
                break;
            }
            case 4: {
                if(isEmptyList(listaPrenotazioni)) {
                    printf("Nessuna prenotazione.\n");
                } else {
                    printf("Prenotazioni:\n");
                    stampaLista(listaPrenotazioni);//stampa tutte le prenotazioni
                }
                break;
            }
            case 5: {
                if (isEmptyList(listaPrenotazioni)) {
                    printf("Nessuna prenotazione.\n");
                } else {
                    if (!stampaListaSecondoUtente(listaPrenotazioni, getCF(utente))) {
                        printf("Nessuna prenotazione per questo utente.\n");
                        break;
                    }
                    printf("\nInserisci ID prenotazione da voler eliminare (-1 per uscire): ");
                    int IdDaEliminare = 0;
                    scanf("%d", &IdDaEliminare);
                    if (IdDaEliminare == -1) break;

                    if (eliminaPrenot(&listaPrenotazioni, IdDaEliminare)) {
                        printf("Elemento eliminato con successo!\n");
                    } else {
                        printf("ID non trovato!\n");
                    }
                }
                break;
                case 6: {

                    if (stampaStorico("sorgente/storico.txt") == 1) {
                        printf("\nStampa effettuata con successo!.");
                    } else
                        printf("\nNon e' stato possibile stampare.");
                break;
                }
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
    if (utente) liberaUtente(utente);

    listaPrenotazioni = liberaLista(listaPrenotazioni);

    if (listaVeicoli != NULL) {//controlla se listaveicoli non é giá vuota per evitare crash e dump
        for(int i = 0; i < numVeicoli; i++) {
            if (listaVeicoli[i] != NULL) liberaVeicolo(listaVeicoli[i]);
        }
        free(listaVeicoli);
    }

    return 0;
}