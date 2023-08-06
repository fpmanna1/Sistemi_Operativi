#include "header.h"

int main()
{
	key_t key_ric = ftok(".",'a');
	key_t key_ris = ftok(".", 'b');
	coda_RICHIESTA = msgget(key_ric, 0);
	coda_RISPOSTA = msgget(key_ris, 0);
	
	Messaggio* m;
	Risultato* r;
	
	/*
	Quando tutti i Client
terminano, il programma principale attende 3 secondi e poi invia un messaggio speciale al Server,
contenente la coppia di valori {-1, -1}, che causa la terminazione del Server come illustrato di seguito.
Il Server istanzia 2 tipi di thread, rispettivamente un Manager e 2 Worker. Il Manager verifica
periodicamente la disponibilità di un messaggio senza bloccarsi, attendendo con una sleep di un
secondo tra un controllo e l'altro. Quando riceve un messaggio, lo pone in un array di buffer condiviso
con i thread Worker. Il messaggio viene prelevato da un thread Worker, che calcola il prodotto della
coppia di valori, ed ha il compito di inviare al Client (identificato dal PID) un messaggio contenente il
prodotto risultante, tramite la coda di messaggi di risposta. Quando il Manager riceve il messaggio con
la coppia di valori {-1,-1}, forza la terminazione dei Worker con pthread_cancel e termina a sua
volta. Il processo Server attende la terminazione del thread Manager per poi terminare
	*/
	
	









}
