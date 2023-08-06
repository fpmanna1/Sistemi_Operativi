#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header.h"
#include "store.h"

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
    ds_queue_request = msgget(key_queue_request, 0);
    //ds_queue_response = //...
    ds_queue_response = msgget(key_queue_response, 0);
    
    printf("[viewer] Coda ds_queue_request ID: %d\n", ds_queue_request);
    printf("[viwwer] Coda ds_queue_response ID: %d\n", ds_queue_response);
    
    Msg_Req m_req;
    Msg_Resp m_res;

    int i;
	m_req.mittente = getpid();
    m_req.tipo_richiesta = READ_TYPE;
        
    srand(time(NULL)*getpid());
    
    for (i=0; i<4; i++){
        
        // TODO costruzione del messaggio di richiesta
     
        m_req.id_prodotto = rand() % 3;

        // TODO aggiungere codice per inviare la richiesta
        msgsnd(ds_queue_request, (void*)&m_req, sizeof(Msg_Req)-sizeof(long), 0);
        // TODO aggiungere codice per ricevere la risposta
        
        msgrcv(ds_queue_response,(void*)&m_res, sizeof(Msg_Resp)-sizeof(long), getpid(), 0);
        printf("[viewer] Sono disponibili %d unità del prodotto %d\n",m_res.scorta,m_res.id_prodotto);
    }
    
    return 0;
}


