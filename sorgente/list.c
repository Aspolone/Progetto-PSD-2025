#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

#include <string.h>

struct node {
  Prenotazione prenotazione; //Prenotazione é un puntatore per gestire meglio la memoria
  struct node *next;
};


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
list nuovaLista(void){
  return NULL;
}

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
int isEmptyList(list l){
  return l == NULL;
  }

/*
    Alloca la memoria per un nuovo nodo e ne inizializza i campi

    parametri:
        prenotazione: un puntatore non-nullo alla struttura
        lista: un puntatore valido a una lista collegata

    precondizioni:
         tutti i parametri devono essere validi e rispettare i tipi

    postcondioni:
        se ha successo la funzione la lista viene aggiornata
        se fallisce la lista resta invariata

  ritorna:
    il puntatore alla nuova lista
*/
list aggLista(Prenotazione prenot, list l) {

  struct node *nuova_prenotazione = malloc(sizeof(struct node));

  if (nuova_prenotazione != NULL) {
    nuova_prenotazione->prenotazione = prenot;
    nuova_prenotazione->next = l;
    l = nuova_prenotazione;
  }

  return l;
}

/*
    Fornisce il collegamento alla coda della lista

    parametri:
        lista: puntatore valido a una lista collegata

    precondizioni:
        la lista passata è valida.

    postcondizioni:
        se la lista è vuota allora la funzione restituisce NULL,
        se abbiamo una lista non vuota crea una sottolista contenente la coda

    ritorna:
        NULL se la lista è vuota
        il puntatore alla sottolista se la lista è popolata
*/
list codaLista(list l) {
  list temp;
  if (l != NULL)
    temp = l->next;
  else
    temp = NULL;
  return temp;
}

/*
    Funzione che restituisce il primo elemento della lista

    parametri:
        lista: puntatore valido a una lista collegata

    precondizioni:
        la lista è valida

    postcondizioni:
        la lista rimane invariata

    ritorna:
        se la lista non è vuota allora restituisce il puntatore al primo elemento della lista
        se la lista è vuota la funzione restituisce un NULLITEM che indica l'assenza di un elemento valido
*/
Prenotazione prendiPrimo(list l) {
  Prenotazione e;
  if (l != NULL)
    e = l->prenotazione;
  else
    e = NULLITEM;
  return e;
}

/*
    Funzione che stampa a schermo il contenuto di una lista

    paramentri:
        l: puntatore valido a una lista collegata

    precondizioni:
        nessuna

    postcondizioni:
        se la lista è vuota non stampa nulla
        se la lista contiene degli elmenti, questi vengono stampati a schermo

    ritorna:
        nulla
*/
void stampaLista(list l) {
  list temp = l;
  while (!isEmptyList(temp)) {
    Prenotazione p = prendiPrimo(temp);
    printf("\nUtente: %s, Veicolo: %s, Posizione: %s, Orario: %d-%d, Prezzo: %.2f\n",
           getNome(getUtente(p)),
           getTarga(getVeicolo(p)),
           getPosizione(getVeicolo(p)),
           getInizio(p),
           getFine(p),
           getCosto(p));

    temp = codaLista(temp);
  }
}

/*
    Funzione che stampa in output i dati di un utente dato il suo nome

    parametri:
        lista: puntatore valido a una lista collegata
        nome: puntatore valido ad una stringa

    precondizioni:
        tutti i parametri sono validi

    postcondizioni:
        se viene trovata una prenotazione col nome indicato stampa su schermo tutte le prenotazioni con quel nome
        e restituisce TRUE
        se non trova il nome indicato restituisce FALSE

    ritorna:
        TRUE se trova il nome nella lista
        FALSE se il nome non è presente
*/
bool stampaListaSecondoUtente(list l, char* CF) {
  list temp = l;
  bool trovato = false;
  int i = 1;

  while (temp != NULL) {
    Prenotazione p = prendiPrimo(temp);

    if (strcmp(getCF(getUtente(p)), CF) == 0) {
      trovato = true;
      printf("\n%d) ID: %d, Veicolo: %s, Posizione: %s, Orario: %d-%d, Prezzo: %.2f\n",
             i,
             getID(p),
             getTarga(getVeicolo(p)),
             getPosizione(getVeicolo(p)),
             getInizio(p),
             getFine(p),
             getCosto(p));
      i++;
    }

    temp = codaLista(temp);
  }

  return trovato;
}

/*
    Funzione che scorre la lista ed elimina una prenotazione se presente nella lista

    parametri:
        lista: puntatore valido a lista collegata
        int: identificatore valido

    precondizioni:
        i parametri sono tutti validi

    postcondizioni:
        se esiste l'identificatore nella lista la prenotazione con quell'identificatore viene rimossa,
        la memoria occupata dal nodo deallocata e la lista viene aggiornata
        se l'identificatore non è presente, la funzione restituisce FALSE e
        la lista resta invariata

    ritorna:
        TRUE se ha trovato l'ID
        FALSE se non lo ha trovato
*/
bool eliminaPrenot(list *l, int ID) {
  list temp = *l; //copia lista su una lista temp, temp è corrente adesso
  list nodoPrec = NULL; //creo il nodo precedente e lo imposto null

  while (temp != NULL) { // scorre tutta la lista
    if (getID(temp->prenotazione) == ID) {// controlla se l'ID e lo stesso di quello inserito
      //quello trovato sara quello che verra eliminato

      if (nodoPrec != NULL) {// se il nodo precedente NON e vuoto, non stiamo eliminando il primo elemento
        // quindi nodo deve saltare al next di temp, puntando al prossimo
        nodoPrec->next = temp->next;//
      } else {
        // se nodoPrec = NULL, allora stiamo eliminando il primo elemento, quindi l (la cima della lista) dovrá solamente saltare oltre temp
        *l = temp->next;
      }

      liberaPrenotazione(temp->prenotazione); // qui liberiamo la value di temp
      free(temp);// liberiamo il nodo vero e proprio
      return true;
    }

    nodoPrec = temp;// se non ha ancora trovato il nodo da eliminare, inizia a scorrere la lista
    temp = temp->next;// scorrendo nodoPrec e temp in avanti
  }

  return false; // Non trovato
}

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
list liberaLista(list l) {
  while (!isEmptyList(l)) {
    Prenotazione p = prendiPrimo(l);
    liberaPrenotazione(p);

    list temp = l;
    l = codaLista(l);
    free(temp);
  }
  return NULL;
}