#include "prodcons.h"

#include <stdio.h>


void inizializza(MonitorStreaming * m) {

    /* TBD: Inizializzare il monitor */
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->CV_PROD, NULL);
    pthread_cond_init(&m->CV_CONS, NULL);
}

void produci(MonitorStreaming * m, Frame f) {

    /* TBD: Completare il metodo, con la sincronizzazione */
    pthread_mutex_lock(&m->mutex);
	while(m->cont == DIM)
		pthread_cond_wait(&m->CV_PROD, &m->mutex);
    printf("Produzione frame: { %d, %d, %d, %d }\n", f[0][0], f[0][1], f[1][0], f[1][1]);

    /* TBD  = f[0][0];
     TBD *= f[0][1];
     TBD  = f[1][0];
     TBD  = f[1][1]; */
     m->vettore[m->testa][0][0] = f[0][0];
     m->vettore[m->testa][0][1] = f[0][1];
     m->vettore[m->testa][1][0] = f[1][0];
     m->vettore[m->testa][1][1] = f[1][1];
     m->testa = (m->testa + 1) % DIM;
     m->cont++;
     
    pthread_cond_signal(&m->CV_CONS);
    printf("Risveglio il consumatore...\n");
    pthread_mutex_unlock(&m->mutex);

}

void consuma(MonitorStreaming * m, Frame f) {

    /* TBD: Completare il metodo, con la sincronizzazione */
    pthread_mutex_lock(&m->mutex);
    /*f[0][0] =  TBD 
    f[0][1] = TBD 
    f[1][0] =  TBD 
    f[1][1] =  TBD */
    
    while(m->cont == 0)
    	pthread_cond_wait(&m->CV_CONS, &m->mutex);
    
    f[0][0] = m->vettore[m->coda][0][0];
    f[0][1] = m->vettore[m->coda][0][1];
    f[1][0] = m->vettore[m->coda][1][0];
    f[1][1] = m->vettore[m->coda][1][1];
    printf("Consumazione frame: { %d, %d, %d, %d }\n", f[0][0], f[0][1], f[1][0], f[1][1]);
    m->cont--;
    m->coda = (m->coda + 1) % DIM;
    pthread_cond_signal(&m->CV_PROD);
     printf("Risveglio il produttore..\n");
    pthread_mutex_unlock(&m->mutex);
}

void bufferizza(MonitorStreaming * m, int n) {

    /* TBD: Completare il metodo */
    pthread_mutex_lock(&m->mutex);
    while(m->cont < n)
    	pthread_cond_wait(&m->CV_CONS, &m->mutex);
    	
   	//if(m->cont == n)
   	printf("Ho accumulato %d frame\n", n);
   	pthread_cond_signal(&m->CV_CONS);
    pthread_mutex_unlock(&m->mutex);
}

void distruggi(MonitorStreaming * m) {

    /* TBD: Completare il metodo */
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->CV_PROD);
    pthread_cond_destroy(&m->CV_CONS);
}
