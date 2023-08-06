#ifndef _HEADER_H_
#define _HEADER_H_

#include <pthread.h>

#define DIM 6

#define NUM_PROD 1
#define NUM_CONS 1

typedef int Frame[2][2];

typedef struct {

    Frame vettore[DIM]; // vettore in cui ogni cella è una matrice 2x2

    /* TBD: Completare la struttura dati monitor */
    pthread_mutex_t mutex;
    pthread_cond_t CV_PROD;
    pthread_cond_t CV_CONS;
    
    int testa;
    int coda;
    int cont;

} MonitorStreaming;

void inizializza(MonitorStreaming * m);
void produci(MonitorStreaming * m, Frame f);
void consuma(MonitorStreaming * m, Frame f);
void bufferizza(MonitorStreaming * m, int n);
void distruggi(MonitorStreaming * m);

#endif
