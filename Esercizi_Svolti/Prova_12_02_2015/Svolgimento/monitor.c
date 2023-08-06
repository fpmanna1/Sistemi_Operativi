#include "header.h"

void init_monitor(MonitorElaborazioni* m)
{
	for(int i=0; i<DIM_BUFFER; i++)
		m->stato[i] = LIBERO;
		
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	pthread_mutex_init(&m->mutex, &attr);
	pthread_cond_init(&m->CV_PROD, &attr);
	pthread_cond_init(&m->CV_CONS, &attr);
}

void remove_monitor(MonitorElaborazioni* m)
{
	pthread_attr_destroy(&attr);
	pthread_mutex_destory(&m->mutex);
	pthread_cond_destroy(&m->CV_PROD);
	pthread_cond_destroy(&m->CV_CONS);
	free(m);
}

void Richiedente(void* mon, buffer)
{
	MonitorOperandi* m = (MonitorOperandi*)mon;
	srand(time(NULL));
	
	int quantita_operandi;
	m->
	
	quantita_operandi = 2 + (rand() % 3); // genero numero casuale tra 2 e 4
	




}

void produci_richiesta(MonitorElaborazioni * m, buffer * b)
{
	//inizio scrittura
	pthread_mutex_lock(&m->mutex);
	



	pthread_mutex_unlock(&m->mutex);
	// produzione



	// fine scrittura
	pthread_mutex_lock(&m->mutex);
	
	
	
	
	pthread_mutex_unlock(&m->mutex);

}

