#ifndef UTENTE_H
#define UTENTE_H

#include <stdbool.h>
#include <stdio.h>

typedef struct prenotazione* Prenotazione;
typedef struct utente* Utente;

#define UTENTE_MAX_NOME 50
#define CF_MAX 17
#define MAX_PRENOTAZIONI 10


//Prototipi
Utente creaUtente(char* , char*);

void aggPrenot(Utente, Prenotazione);
char* getNome(Utente);
char* getCF(Utente);
int getNPrenot(Utente);
void setNPrenot(Utente, int);
Prenotazione getPrenot(Utente, int);
void setPrenot(Utente, int, Prenotazione);


void liberaUtente(Utente);

#endif // UTENTE_H
