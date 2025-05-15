#include <stdio.h>
#include <stdlib.h>
//#inlcude "item.h" forsce non abbiamo bisogno di includerla essendo gia inclusa in list.h
#include "list.h"

list newList(void){
  return NULL;
}

int emptyList(list l){
  return l == NULL;
  }

//aggiungere alla funzione check validitá e solo se é true procede con l'aggiunta del nodo, sennó annulla
//questa funzione verrá chiamata nel main da uno switch case (vorrei cercare un modo per rendere l'interfaccia scorrevole
//fatto sta che prima di essa vi sará chiamata aggPrenot();
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