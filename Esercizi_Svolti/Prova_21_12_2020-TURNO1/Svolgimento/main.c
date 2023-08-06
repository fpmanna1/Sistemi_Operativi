#include "prodcons.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void * Produttore(void *);
void * Consumatore(void *);

int main() {

    /* TBD: Avviare i thread produttore e consumatore */
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t thread_prod;
	pthread_t thread_cons;
	
	MonitorStreaming* m = (MonitorStreaming*)malloc(sizeof(MonitorStreaming));
	m->testa = 0;
	m->coda = 0;
	m->cont = 0;
	
	inizializza(m);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	printf("Creazione threads...\n");
	
	pthread_create(&thread_prod, &attr, Consumatore, (void*)m);
	pthread_create(&thread_cons, &attr, Produttore, (void*)m);
	
	printf("Terminazione threads...\n");
	pthread_join(thread_prod, NULL);
	pthread_join(thread_cons, NULL);
	printf("Threads terminati\n");
	printf("Distruzione monitor in corso....\n");
	distruggi(m);
	free(m);
	pthread_attr_destroy(&attr);
	sleep(1);
	printf("Monitor distrutto\n");
	//pthread_exit(NULL);
	return 0;
}

void * Produttore(void * p) {

	MonitorStreaming* m = (MonitorStreaming*)p;
    for(int i=0; i<10; i++) {

        Frame f;
        f[0][0] = rand() % 11;
        f[0][1] = rand() % 11;
        f[1][0] = rand() % 11;
        f[1][1] = rand() % 11;

        /* TBD: Chiamare il metodo "produci()" del monitor */
		produci(m, f);
        sleep(1);
    }

    pthread_exit(NULL);
}

void * Consumatore(void * p) {

    /* TBD: Chiamare il metodo "bufferizza()" del monitor */
	MonitorStreaming* m = (MonitorStreaming*)p;
	bufferizza(m, 4);
    for(int i=0; i<10; i++) {

        Frame f;

        /* TBD: Chiamare il metodo "consuma()" del monitor */
		consuma(m, f);
        sleep(1);
    }

    pthread_exit(NULL);
}
