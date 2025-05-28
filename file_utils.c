#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"

void finput_array(char *file_name, int a[], int n){
    int i;

    FILE *fd;

    fd = fopen(file_name, "r");
    if (fd == NULL)

        printf("Errore in apertura del file %s \n", file_name);
    else
    {
        // Altrimenti, esegui il seguente blocco di codice:

        for (i = 0; i < n; i++)
            // Cicla attraverso gli elementi dell'array.
            fscanf(fd, "%d", &a[i]);
            // Legge un intero dal file e lo memorizza nell'array a.

        fclose(fd);
        // Chiude il file dopo aver letto tutti gli interi.
    }
}


void foutput_array(char *file_name, int a[], int n) {
    // La funzione scrive un array di interi in un file specificato.

    int i;
    // Dichiarazione di una variabile di loop.

    FILE *fd;
    // Dichiarazione di un puntatore a FILE per gestire l'apertura e la scrittura del file.

    fd = fopen(file_name, "w");
    // Apre il file specificato in modalità di scrittura ("w") e assegna il puntatore a fd.

    if (fd == NULL)
        // Controlla se l'apertura del file ha avuto successo.
        printf("Errore in apertura del file %s \n", file_name);
        // Se l'apertura del file fallisce, stampa un messaggio di errore.

    else {
        // Altrimenti, esegui il seguente blocco di codice:

        for (i = 0; i < n; i++)
            // Cicla attraverso gli elementi dell'array.
            fprintf(fd, "%d\n", a[i]);
            // Scrive un intero nel file, seguito da un newline.

        fclose(fd);
        // Chiude il file dopo aver scritto tutti gli interi.
    }
}

int confronta_array(int a[], int b[], int n) {
    // La funzione confronta due array di interi e restituisce 1 se sono uguali, altrimenti restituisce 0.

    int i = 0;
    // Inizializza una variabile di loop.

    int trovato_diff = 0;
    // Inizializza una variabile per indicare se è stata trovata una differenza tra gli array.

    while (i < n && !trovato_diff)
    {
        // Cicla finché non viene trovata una differenza o si esauriscono gli elementi da confrontare.

        if (a[i] != b[i])
            // Controlla se gli elementi corrispondenti negli array sono diversi.
            trovato_diff = 1;
            // Se è stata trovata una differenza, imposta la variabile trovato_diff a 1.
        else
            i++;
            // Altrimenti, passa all'elemento successivo.

    }

    return (trovato_diff) ? 0 : 1;
    // Restituisce 1 se non sono state trovate differenze (i due array sono uguali), altrimenti restituisce 0.
}
