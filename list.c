#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list newList(void){
  return NULL;
}

int isEmptyList(list l){
  return l == NULL;
  }


list consList(Prenotazione* prenot, list l) {

  struct node *nuova_prenotazione = malloc(sizeof(struct node));

  if (nuova_prenotazione != NULL) {
    nuova_prenotazione->prenotazione = prenot;
    nuova_prenotazione->next = l;
    l = nuova_prenotazione;
  }

  return l;
}

list tailList(list l) {
  list temp;
  if (l != NULL)
    temp = l->next;
  else
    temp = NULL;
  return temp;
}

//non avendo messo in dichiarazione di struct *, adesso andra' messo un po' ovunque
Prenotazione* getFirst(list l) {
  Prenotazione* e;
  if (l != NULL)
    e = l->prenotazione;
  else
    e = NULLITEM;
  return e;
}

void stampaLista(list l) {
  list temp = l;
  while (!isEmptyList(temp)) {
    Prenotazione* p = getFirst(temp);
    printf("Prenotazione: Utente %s, Veicolo %s, Inizio %d, Fine %d\n",
           p->utente->nome,
           p->veicolo->targa,
           p->inizio_data,
           p->fine_data);
    temp = tailList(temp);
  }
}

list freeList(list l) {
  while (!isEmptyList(l)) {
    Prenotazione* p = getFirst(l);
    liberaPrenotazione(p);

    list temp = l;
    l = tailList(l);
    free(temp);
  }
  return NULL;
}