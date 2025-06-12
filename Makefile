car_sharing.o: sorgente/car_sharing.c include/Prenotazione.h include/Utente.h include/list.h include/Veicolo.h include/macro_utili.h
	gcc -c sorgente/car_sharing.c -Iinclude -Wall -o car_sharing.o

test.exe: Prenotazione.o Utente.o list.o Veicolo.o test.o
	gcc Prenotazione.o Utente.o list.o Veicolo.o test.o -o test.exe

Prenotazione.o: sorgente/Prenotazione.c include/Prenotazione.h include/macro_utili.h
	gcc -c sorgente/Prenotazione.c -Iinclude -Wall

Utente.o: sorgente/Utente.c include/Utente.h include/macro_utili.h
	gcc -c sorgente/Utente.c -Iinclude -Wall

list.o: sorgente/list.c include/list.h include/macro_utili.h
	gcc -c sorgente/list.c -Iinclude -Wall

Veicolo.o: sorgente/Veicolo.c include/Veicolo.h include/macro_utili.h
	gcc -c sorgente/Veicolo.c -Iinclude -Wall

test.o: test/test.c include/Prenotazione.h include/Utente.h include/list.h include/Veicolo.h include/macro_utili.h
	gcc -c test/test.c -Iinclude -Wall

clean:
	rm -f *.o car_sharing.exe test.exe