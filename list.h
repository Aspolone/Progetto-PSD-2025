#include "item.h"

#define NULLITEM 0
typedef struct node* list;

//rimpiazza prenot con item, cosicche nel file item.h possiamo mettere funzioni di creaAuto creaPrenot per gestire anche i veicoli con le liste

struct node {
  Prenotazione* prenotazione; //Prenotazione é un puntatore per gestire meglio la memoria
  struct node *next;
};

list newList(void);
int isEmptyList(list );
list tailList(list );
list consList(Prenotazione* , list );
Prenotazione* getFirst(list );