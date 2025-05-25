#ifndef VEICOLO_H
#define VEICOLO_H

typedef struct veicolo* Veicolo;

Veicolo creaVeicolo(char*, char*);


Veicolo leggiVeicoloDaRiga(char* riga);
Veicolo* caricaVeicoliDaFile(const char* nomeFile, int* numVeicoli);


void stampaVeicoli(int , Veicolo* );
void stampaValidita(Veicolo );

bool getData(Veicolo , int);
void setData(Veicolo , int, bool);
char* getTarga(Veicolo );
char* getModello(Veicolo );

void liberaVeicolo(Veicolo );


#endif // VEICOLO_H
