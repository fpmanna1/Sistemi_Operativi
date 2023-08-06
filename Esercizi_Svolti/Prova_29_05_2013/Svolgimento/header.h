#ifndef HEADER_H
#define HEADER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

int coda_RICHIESTA;
int coda_RISPOSTA;

#define DIM_BUFFER 3

#define NUM_CLIENT 3

typedef struct{
	long type;
	pid_t PIDclient
	int val1;
	int val2;
}Messaggio;

typedef struct{
	long PIDclient;
	int val3;
}Risultato;

typedef struct{
	Messaggio buf[DIM_BUFFER];
	
	pthread_mutex_t mutex;
	pthread_cond_t CV_PROD;
	pthread_cond_t CV_CONS;
	int testa;
	int coda;
	int cont;


}Buffer;

#endif
