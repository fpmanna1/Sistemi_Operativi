#ifndef HEADER_H
#define HEADER_H

#include "monitor.h"
#include <sys/types.h>
#include <unistd.h>

#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2

#define N_CV 2

#define CV_FORNITORE 0
#define CV_CLIENTE 1

#define MAX_DIM 100
#define NUM_FORNITORI 10
#define NUM_CLIENTI 10

#define NUM_PROCESSI NUM_FORNITORI + NUM_CLIENTI

#define NUM_ACCESSI 15


typedef struct{
	unsigned id;
	unsigned stato;
}scaffale;


struct magazzino{
	scaffale s[MAX_DIM]; 
	int livello_scorte; // numero elementi (prodotto) nel magazzino
	Monitor m;
};


void fornitore(struct magazzino *);
void cliente(struct magazzino *);

#endif
