#ifndef __HEADER
#define __HEADER

//Funzioni che ci servono
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#define NUM_REQ 10

// TODO: completare il messaggio misura dai sensori
typedef struct{
	//...
	long id; // id del client, tra 1 e 3
	int valore;
}Misura;

typedef struct{
	int somma;
	// TODO completare con le variabili per la sincronizzazione tra i thread
	pthread_mutex_t mutex;
	pthread_cond_t CV_CONS;
	int num_somme;
}Buffer;

#endif
