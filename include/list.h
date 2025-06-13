#ifndef LIST_H
#define LIST_H

#include "Prenotazione.h"

#define NULLITEM 0

typedef struct node* list;


/*
    Funzione per creare una nuova lista vuota

    parametri:
        Nessuno

    precondizioni:
        Nessuna

    postcondizioni:
        Viene creata e restituita una lista vuota

    ritorna:
        Un puntatore NULL alla lista vuota
*/
list nuovaLista(void);

/*
    Funzione per controllare se una lista è vuota

    parametri:
        list l: puntatore alla lista da verificare

    precondizioni:
        Il puntatore l può essere NULL o puntare a una lista valida

    postcondizioni:
        Nessuna

    ritorna:
        1 se la lista è vuota
        0 se è popolata
*/
int isEmptyList(list );

/*
    Funzione che restituisce un puntatore alla coda di una lista collegata

    parametri:
        lista: puntatore valido a una lista collegata

    precondizioni:
        la lista passata è valida

    postcondizioni:
        se la lista è vuota, la funzione restituisce NULL
        se la lista non è vuota, la funzione restituisce un puntatore alla sottolista che rappresenta la coda

    ritorna:
        NULL se la lista è vuota
        puntatore alla sottolista che rappresenta la coda se la lista è non vuota
*/
list codaLista(list );

/*
    Funzione che aggiunge una prenotazione a una lista collegata

    parametri:
        prenotazione: puntatore non NULL a una struttura Prenotazione valida
        lista: puntatore a una lista collegata

    precondizioni:
        prenotazione è non NULL e valida
        lista è un puntatore valido

    postcondizioni:
        se ha successo, la lista viene aggiornata con il nuovo nodo contenente la prenotazione
        in caso di fallimento la lista rimane invariata

    ritorna:
        il puntatore alla lista aggiornata
*/
list aggLista(Prenotazione , list );

/*
    Funzione che restituisce il primo elemento della lista collegata

    parametri:
        lista: puntatore valido a una lista collegata

    precondizioni:
        la lista è valida

    postcondizioni:
        la lista rimane invariata

    ritorna:
        il puntatore al primo elemento della lista se la lista non è vuota
        NULLITEM se la lista è vuota
*/
Prenotazione prendiPrimo(list );

/*
    Funzione che stampa a schermo il contenuto di una lista collegata

    parametri:
        l: puntatore valido a una lista collegata

    precondizioni:
        nessuna

    postcondizioni:
        se la lista è vuota, non viene stampato nulla
        se la lista contiene elementi, questi vengono stampati a schermo in ordine

    ritorna:
        nulla
*/
void stampaLista(list l);

/*
    Funzione che stampa in output i dati di un utente dato il suo nome

    parametri:
        lista: puntatore valido a una lista collegata di utenti
        nome: puntatore valido a una stringa contenente il nome da cercare

    precondizioni:
        tutti i parametri sono validi e non NULL

    postcondizioni:
        se viene trovato almeno un utente con il nome indicato,
        stampa su schermo tutte le prenotazioni associate a quell’utente e restituisce TRUE
        se nessun utente con il nome indicato è presente nella lista,
        non stampa nulla e restituisce FALSE

    ritorna:
        TRUE se trova uno o più utenti con il nome indicato
        FALSE altrimenti
*/
bool stampaListaSecondoUtente(list , char*);

/*
    Funzione che elimina una prenotazione dalla lista se presente

    parametri:
        lista: puntatore valido a una lista collegata
        id: identificatore valido della prenotazione da eliminare

    precondizioni:
        tutti i parametri sono validi
        la lista è correttamente formata

    postcondizioni:
        se esiste una prenotazione con l’identificatore specificato:
            quella prenotazione viene rimossa dalla lista
            la memoria occupata dal nodo associato viene deallocata
            la lista viene aggiornata correttamente
        se l’identificatore non è presente nella lista:
            la lista rimane invariata

    ritorna:
        TRUE se è stata trovata e rimossa la prenotazione con l’ID
        FALSE se non è stata trovata nessuna prenotazione con l’ID
*/
bool eliminaPrenot(list* , int);

/*
    Funzione che libera la memoria allocata dalla lista collegata

    parametri:
        lista: puntatore valido a una lista collegata

    precondizioni:
        la lista è valida

    postcondizioni:
        tutti i nodi della lista e le prenotazioni eventualmente contenute vengono deallocati
        la memoria occupata viene completamente liberata
        viene restituito un puntatore NULL che rappresenta la lista svuotata

    ritorna:
        un puntatore NULL alla lista vuota
*/
list liberaLista(list l);

#endif // LIST_H
