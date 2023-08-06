#ifndef HEADER_H
#define HEADER_H

#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define OCCUPATO 0
#define LIBERO 1
#define IN_USO 2

#define DIM_BUFFER 5

typedef struct{
	int operandi[4]; // il buffer contiene un array operando (da 2 a 4)
	int totale_operandi; // il numero di operandi presenti nell'array
}buffer;

typedef struct{
	buffer elaborazioni[DIM_BUFFER];
	int stato[DIM_BUFFER];
	// .. inserire qui le variabili per la sincronizzazione
	pthread_mutex_t mutex;
	pthread_cond_t CV_PROD;
	pthread_cond_t CV_CONS;

}MonitorElaborazioni;

#endif
