#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "header.h"


int main(int argc, char *argv[]){
	int coda;
	pid_t pid;
	long id_sensore;
        
	if (argc < 2 ) {
		printf("ERRORE: il client deve ricevere il proprio ID\n");
		return -1;
	}
	/*
	Ogni client invia 10 misure in maniera asincrona su
	un’unica coda. Ogni messaggio inviato dovrà contenere un identificativo intero del Client (tra 1 e 3) e
	il valore della misura (intero), selezionato casualmente tra 0 e 100 con la funzione rand(). Una volta
	inviate le 10 misure, i processi Client terminano
	*/
        
	id_sensore = atol(argv[1]);
       
	key_t key;
	//key = //TODO:inserire la chiave
	key = ftok(".",'a');
    
	//coda = //TODO:inizializzare la coda
	coda = msgget(key, 0);

	printf("[DEBUG] - sensore id coda %d\n",coda);	
	printf("[Client %d] - invio richieste...\n",getpid());


	int i = 0;
	Misura misura;	

	srand(time(NULL));
	
	// TODO: inviare in ciclo NUM_REQ misure da inviare al server tramite coda
	for(int i=0; i<NUM_REQ; i++)
	{
		misura.id = id_sensore;
		misura.valore = (rand() % 100);
		msgsnd(coda, (void*)&misura, sizeof(Misura)-sizeof(long), 0);
	}

	printf("[Client %d] - Fine processo\n",getpid());

	return 0;
}
