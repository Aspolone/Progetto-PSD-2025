#ifndef LIST_H
#define LIST_H

#include "prenotazione.h"

#define NULLITEM 0
typedef struct node* list;

struct node {
  Prenotazione* prenotazione; //Prenotazione é un puntatore per gestire meglio la memoria
  struct node *next;
};

list newList(void);
int isEmptyList(list );
list tailList(list );
list consList(Prenotazione* , list );
Prenotazione* getFirst(list );
void stampaLista(list l);
list freeList(list l);

#endif // LIST_H
