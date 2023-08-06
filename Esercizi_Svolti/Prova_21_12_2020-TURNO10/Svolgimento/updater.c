#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header.h"
#include "store.h"

#define MAX_DECR 4;

int main(){
    
    //Creazione code richieste e risposte
    int ds_queue_request, ds_queue_response;

    //create queues
    //int key_queue_request = // TODO aggiungere codice per la generazione della chiave
    //int key_queue_response = // TODO aggiungere codice per la generazione della chiave
    int key_queue_request = ftok(".",'a');
    int key_queue_response = ftok(".", 'b');
    
    // TODO aggiungere codice di inizializzazione delle code
    //ds_queue_request = //...
    //ds_queue_response = //...
    ds_queue_request = msgget(key_queue_request, 0);
    ds_queue_response = msgget(key_queue_response, 0);
    
    printf("[updater] Coda ds_queue_request ID: %d\n", ds_queue_request);
    printf("[updater] Coda ds_queue_response ID: %d\n", ds_queue_response);
    
    
    Msg_Req m_req;
 
    int i;
	m_req.tipo_richiesta = WRITE_TYPE;
    m_req.mittente = getpid();
    srand(time(NULL)*getpid());
    
    
    for (i=0; i<2; i++){
        // TODO costruzione del messaggio di richiesta

        m_req.id_prodotto = rand()%2;
        m_req.value = 1 + rand()%MAX_DECR;
        // TODO aggiungere codice per l'invio della richiesta
        
        msgsnd(ds_queue_request, (void*)&m_req, sizeof(Msg_Req)-sizeof(long), 0);

        printf("[updater] Richiesto decremento di %d unità del prodotto %d\n",m_req.value,m_req.id_prodotto);
    }
    
    return 0;
}


