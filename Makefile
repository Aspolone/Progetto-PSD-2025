car_sharing.exe: Prenotazione.o Utente.o list.o Veicolo.o car_sharing.o
	gcc Prenotazione.o Utente.o list.o Veicolo.o car_sharing.o -o car_sharing.exe

Prenotazione.o: sorgente/Prenotazione.c include/Prenotazione.h include/macro_utili.h
	gcc -c Prenotazione.c

Utente.o: sorgente/Utente.c include/Utente.h include/macro_utili.h
	gcc -c Utente.c

list.o: sorgente/list.c include/list.h include/macro_utili.h
	gcc -c list.c

Veicolo.o: sorgente/Veicolo.c include/Veicolo.h include/macro_utili.h
	gcc -c Veicolo.c

car_sharing.o: car_sharing.c include/Prenotazione.h include/Utente.h include/list.h include/Veicolo.h include/macro_utili.h
	gcc -c car_sharing.c

clean:
	rm -f *.o car_sharing.exe
