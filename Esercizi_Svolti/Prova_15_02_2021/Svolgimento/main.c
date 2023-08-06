#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "prodcons.h"

void * produttore(void *);
void * consumatore(void *);

int main() {


    printf("[MAIN] inizializza_monitor\n");

	MonitorProdCons* m = (MonitorProdCons*)malloc(sizeof(MonitorProdCons));
    /* TBD: Creare e inizializzare il monitor */
    
    inizializza_monitor(m);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_t threads[NUM_PROD + NUM_CONS];


    printf("[MAIN] pthread_create\n");

    /* TBD: Avviare i thread */
	/*
	Simulare l'esecuzione di 5 thread produttori e 1 thread consumatore. Ogni produttore produce 4 valori
(scelti casualmente) in un ciclo, senza porsi in attesa tra le iterazioni. Il consumatore effettua 20
consumazioni in un ciclo, attendendo 2 secondi tra le iterazioni. Il produttore dovrà verificare il valore
di ritorno del metodo di produzione, e se tale valore è negativo, si limiterà a ritentare la produzione
dopo 1 secondo di ulteriore attesa.
	*/
	
	for(int i=0; i<NUM_PROD + NUM_CONS; i++)
	{
		if(i == 0)
			pthread_create(&threads[i], &attr, consumatore, (void*)m);
		else
			pthread_create(&threads[i], &attr, produttore, (void*)m);
	}


    printf("[MAIN] pthread_join\n");

    /* TBD: Attendere la terminazione dei thread */
    for(int i=0; i<NUM_PROD + NUM_CONS; i++)
    	pthread_join(threads[i], NULL);



    printf("[MAIN] distruzione_monitor\n");

    /* TBD: Disattivazione e deallocazione del monitor */
    pthread_attr_destroy(&attr);
    distruggi_monitor(m);
    
    free(m);
    
    pthread_exit(NULL);

}


void * produttore(void * p) {
	MonitorProdCons* m = (MonitorProdCons*)p;

    printf("[MAIN] Avvio thread produttore\n");


    for(int i=0; i<4; i++) {

        int val = rand() % 10;

        printf("[MAIN] Produttore ha generato %d\n", val);

        //int ret = /* TBD: Chiamare il metodo di produzione */
        int ret = produci(m, val);

        while(ret < 0) {

            sleep(1);

            printf("[MAIN] Produttore ritenta inserimento di %d\n", val);

            //ret = /* TBD: Chiamare il metodo di produzione */
            ret = produci(m, val);
        }

    }


    pthread_exit(NULL);
}

void * consumatore(void * p) {

    printf("[MAIN] Avvio thread consumatore\n");
    
    MonitorProdCons* m = (MonitorProdCons*)p;


    for(int i=0; i<20; i++) {

        int val;

        //int ret = /* TBD: Chiamare il metodo di consumazione */
        int ret = consuma(m, &val);

        printf("[MAIN] Consumatore ha prelevato %d\n", val);

        sleep(2);
    }


    pthread_exit(NULL);
}
