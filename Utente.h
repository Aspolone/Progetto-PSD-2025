#ifndef UTENTE_H
#define UTENTE_H

typedef struct prenotazione* Prenotazione;
typedef struct utente* Utente;


//Prototipi
Utente creaUtente(char* , char*);

int aggPrenot(Utente, Prenotazione);
char* getNome(Utente);
char* getCF(Utente);
int getNPrenot(Utente);
void setNPrenot(Utente, int);
Prenotazione getPrenot(Utente, int);
void setPrenot(Utente, int, Prenotazione);


void liberaUtente(Utente);

#endif // UTENTE_H
