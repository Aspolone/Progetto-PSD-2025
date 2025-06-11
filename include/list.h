#ifndef LIST_H
#define LIST_H

#include "Prenotazione.h"

#define NULLITEM 0

typedef struct node* list;

//prototipi
list nuovaLista(void);
int isEmptyList(list );
list codaLista(list );
list aggLista(Prenotazione , list );
Prenotazione prendiPrimo(list );

void stampaLista(list l);
bool stampaListaSecondoUtente(list , char*);
bool eliminaPrenot(list* , int);
list liberaLista(list l);

#endif // LIST_H
