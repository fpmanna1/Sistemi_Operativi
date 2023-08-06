#ifndef _PRODCONS_H_
#define _PRODCONS_H_

#include <pthread.h>

#define DIM 4

#define NUM_PROD 5
#define NUM_CONS 1

typedef struct {

    int buffer[DIM];

    /* TBD: Definire variabili per la sincronizzazione,
     *      e una variabile "uscita_timer"
     */
     int testa;
     int coda;
     int cont;
     
     int uscita_timer;
     
     pthread_mutex_t mutex;
     pthread_cond_t CV_PROD;
     pthread_cond_t CV_CONS;

} MonitorProdCons;

void inizializza_monitor(MonitorProdCons * m);
void distruggi_monitor(MonitorProdCons * m);
int produci(MonitorProdCons * m, int val);
int consuma(MonitorProdCons * m, int * val);

#endif
