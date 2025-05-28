#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#include <string.h>

struct node {
  Prenotazione prenotazione; //Prenotazione é un puntatore per gestire meglio la memoria
  struct node *next;
};

list nuovaLista(void){
  return NULL;
}

int isEmptyList(list l){
  return l == NULL;
  }


list aggLista(Prenotazione prenot, list l) {

  struct node *nuova_prenotazione = malloc(sizeof(struct node));

  if (nuova_prenotazione != NULL) {
    nuova_prenotazione->prenotazione = prenot;
    nuova_prenotazione->next = l;
    l = nuova_prenotazione;
  }

  return l;
}

list codaLista(list l) {
  list temp;
  if (l != NULL)
    temp = l->next;
  else
    temp = NULL;
  return temp;
}

//non avendo messo in dichiarazione di struct *, adesso andra' messo un po' ovunque
Prenotazione prendiPrimo(list l) {
  Prenotazione e;
  if (l != NULL)
    e = l->prenotazione;
  else
    e = NULLITEM;
  return e;
}

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