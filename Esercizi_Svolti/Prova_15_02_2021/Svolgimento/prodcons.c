#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

#include "prodcons.h"

/* Dichiarazione di metodo privato, che sarà
 * eseguito da un thread "timer" */
static void * thread_timer(void *);

void inizializza_monitor(MonitorProdCons * m) {

    printf("[MONITOR] Inizializzazione monitor\n");

    /* TBD: Inizializzazione il monitor, e avviare
     *      il thread timer
     */
     pthread_mutex_init(&m->mutex, NULL);
     pthread_cond_init(&m->CV_PROD, NULL);
     pthread_cond_init(&m->CV_CONS, NULL);
     
     m->testa = 0;
     m->coda = 0;
     m->cont = 0;
     m->uscita_timer = 0;
     
     pthread_attr_t attr;
     pthread_attr_init(&attr);
     pthread_t timer;
     pthread_create(&timer, &attr, thread_timer, (void*)m);
}  


void distruggi_monitor(MonitorProdCons * m) {

    printf("[MONITOR] Distruzione monitor\n");

    /* TBD: Disattivare il monitor, e far
     *      terminare il thread timer tramite
     *      la variabile "uscita_timer"
     */
     pthread_mutex_destroy(&m->mutex);
     pthread_cond_destroy(&m->CV_CONS);
     pthread_cond_destroy(&m->CV_PROD);
     pthread_mutex_lock(&m->mutex);
     
     m->uscita_timer = 1;
     
     pthread_mutex_unlock(&m->mutex);
}

int produci(MonitorProdCons * m, int val) {

    /* TBD: Introdurre la sincronizzazione */


    struct timeval t1;
	gettimeofday(&t1,NULL);
    long start_time = t1.tv_sec*1000000 + t1.tv_usec;


	pthread_mutex_lock(&m->mutex);
	
	while(m->cont == DIM){
	
		pthread_cond_wait(&m->CV_PROD, &m->mutex);
        struct timeval t2;
	    gettimeofday(&t2,NULL);
        long current_time = t2.tv_sec*1000000 + t2.tv_usec;

        if(current_time - start_time >= 3000000) {

            printf("[MONITOR] Produttore ha atteso oltre 3 secondi, esce\n");

            /* TBD: Il metodo esce dal monitor senza porsi nuovamente 
                    in attesa sulla condition variable, e ritorna in uscita
                    un valore negativo
             */
             pthread_mutex_unlock(&m->mutex);
             return(-1);
        }
     }
    //m->buffer[/*TBD*/] = val;
    m->buffer[m->testa] = val;
    m->testa = (m->testa + 1) % DIM;
    m->cont++;

    printf("[MONITOR] Produzione %d\n", val);
    
    pthread_cond_signal(&m->CV_CONS);

    pthread_mutex_unlock(&m->mutex);
    return 0;
}

int consuma(MonitorProdCons * m, int * val) {

    /* TBD: Introdurre la sincronizzazione */

    struct timeval t1;
	gettimeofday(&t1,NULL);
    long start_time = t1.tv_sec*1000000 + t1.tv_usec;

	pthread_mutex_lock(&m->mutex);
	
	while(m->cont == 0) {
	
		pthread_cond_wait(&m->CV_CONS, &m->mutex);
        struct timeval t2;
	    gettimeofday(&t2,NULL);
        long current_time = t2.tv_sec*1000000 + t2.tv_usec;

        if(current_time - start_time >= 3000000) {

            printf("[MONITOR] Consumatore ha atteso oltre 3 secondi, esce\n");

            /* TBD: Il metodo esce dal monitor senza porsi nuovamente 
                    in attesa sulla condition variable, e ritorna in uscita
                    un valore negativo
             */
             pthread_mutex_unlock(&m->mutex);
             return(-1);
        }
     }



    //*val = m->buffer[/*TBD*/];
    *val = m->buffer[m->coda];
    m->coda = (m->coda + 1) % DIM;
    m->cont++;
   
    printf("[MONITOR] Consumazione %d\n", *val);
    
    pthread_cond_signal(&m->CV_PROD);
    
    pthread_mutex_unlock(&m->mutex);


    return 0;
}

void * thread_timer(void * p) {

    printf("[MONITOR] Avvio thread timer\n");
	MonitorProdCons* m = (MonitorProdCons*)p;

    while(1) {

        int uscita = 0;

        sleep(1);
        
        uscita = m->uscita_timer;

        /* TBD: Il thread timer periodicamente attiva tutti i thread sospesi */
        pthread_cond_broadcast(&m->CV_PROD);
        pthread_cond_broadcast(&m->CV_CONS);

        if(uscita != 0) {
            break;
        }
    }

    printf("[MONITOR] Uscita thread timer\n");

    pthread_exit(NULL);
}
