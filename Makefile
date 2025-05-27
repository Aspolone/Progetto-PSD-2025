car_sharing.exe: Prenotazione.o Utente.o list.o Veicolo.o car_sharing.o
	gcc Prenotazione.o Utente.o list.o Veicolo.o car_sharing.o -o car_sharing.exe

Prenotazione.o: Prenotazione.c Prenotazione.h macro_utili.h
	gcc -c Prenotazione.c

Utente.o: Utente.c Utente.h macro_utili.h
	gcc -c Utente.c

list.o: list.c list.h macro_utili.h
	gcc -c list.c

Veicolo.o: Veicolo.c Veicolo.h macro_utili.h
	gcc -c Veicolo.c

car_sharing.o: car_sharing.c Prenotazione.h Utente.h list.h Veicolo.h macro_utili.h
	gcc -c car_sharing.c

clean:
	rm -f *.o car_sharing.exe
