#ifndef LIST_H
#define LIST_H

#include "prenotazione.h"

#define NULLITEM 0

typedef struct node* list;

//prototipi
list newList(void);
int isEmptyList(list );
list tailList(list );
list consList(Prenotazione , list );
Prenotazione getFirst(list );

void stampaLista(list l);
bool stampaListaSecondoUtente(list , char*);
bool eliminaPrenot(list* , int);
list freeList(list l);

#endif // LIST_H
