car_sharing.o: sorgente/car_sharing.c include/Prenotazione.h include/Utente.h include/list.h include/Veicolo.h include/macro_utili.h
	gcc -c sorgente/car_sharing.c -Iinclude -o car_sharing.o

test.exe: Prenotazione.o Utente.o list.o Veicolo.o test.o
	gcc Prenotazione.o Utente.o list.o Veicolo.o test.o -o test.exe

Prenotazione.o: sorgente/Prenotazione.c include/Prenotazione.h include/macro_utili.h
	gcc -c sorgente/Prenotazione.c -Iinclude

Utente.o: sorgente/Utente.c include/Utente.h include/macro_utili.h
	gcc -c sorgente/Utente.c -Iinclude

list.o: sorgente/list.c include/list.h include/macro_utili.h
	gcc -c sorgente/list.c -Iinclude

Veicolo.o: sorgente/Veicolo.c include/Veicolo.h include/macro_utili.h
	gcc -c sorgente/Veicolo.c -Iinclude

car_sharing.o: car_sharing.c include/Prenotazione.h include/Utente.h include/list.h include/Veicolo.h include/macro_utili.h
	gcc -c car_sharing.c -Iinclude

test.o: test/test.c include/Prenotazione.h include/Utente.h include/list.h include/Veicolo.h include/macro_utili.h
	gcc -c test/test.c -Iinclude

clean:
	rm -f *.o car_sharing.exe test.exe