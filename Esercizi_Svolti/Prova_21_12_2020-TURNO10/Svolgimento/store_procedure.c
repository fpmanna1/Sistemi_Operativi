#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>

#include "store.h"

extern int ds_queue_request, ds_queue_response;

void Wait_Sem(int ds_sem, int id_sem) {
    struct sembuf buf;
    buf.sem_flg = 0;
    buf.sem_num = id_sem;
    buf.sem_op = -1;
    semop(ds_sem,&buf,1);
}

void Signal_Sem(int ds_sem, int id_sem) {
    struct sembuf buf;
    buf.sem_flg = 0;
    buf.sem_num = id_sem;
    buf.sem_op = 1;
    semop(ds_sem,&buf,1);
}

void init_magazzino(Magazzino *magazzino){
    // TODO inizializzazione dei semafori , delle variabili necessarie alla sincronizzazione
    // e delle scorte di magazzino iniziali
    
    magazzino->MUTEX = semget(IPC_PRIVATE, MAX_PRODOTTI, IPC_CREAT | 0664);
    magazzino->SYNCH = semget(IPC_PRIVATE, MAX_PRODOTTI, IPC_CREAT | 0664);
    
    for(int i=0; i<MAX_PRODOTTI; i++){
    	magazzino->num_lettori[i] = 0;
    	magazzino->scorta[i] = 0;
    	semctl(magazzino->MUTEX, i, SETVAL, 1);
    	semctl(magazzino->SYNCH, i, SETVAL, 1);
    }
    magazzino->num_scrittori = 0;
}
void destroy_magazzino(Magazzino *magazzino){
    // TODO rimozione dei semafori
    semctl(magazzino->MUTEX, 0, IPC_RMID);
    semctl(magazzino->SYNCH, 0, IPC_RMID);
}

void lettore(Magazzino *magazzino) {
    int ret;
    Msg_Req m_req;
    Msg_Resp m_resp;
    int k;

    for (k=0; k<4; k++) {
        // TODO aggiungere codice per la ricezione comando
        msgrcv(ds_queue_request, (void*)&m_req, sizeof(Msg_Req)-sizeof(long), READ_TYPE, 0);

        int id_prodotto = m_req.id_prodotto;

        // TODO Aggiungere codice per la lettura:
        // InizioLettura
        // Lettura del livello di scorta del prodotto il cui id è indicato nella richiesta
        // FineLettura
        InizioLettura(magazzino, id_prodotto);

        // TODO Costruire il messaggio di risposta m_resp

        printf("[lettore] Ricevuta richiesta di lettura per prodotto %d con livello scorte %d\n",m_resp.id_prodotto,m_resp.scorta);

        // TODO aggiungere codice per l'invio del messaggio di risposta
        m_resp.scorta = magazzino->scorta[id_prodotto];
        m_resp.pid = m_req.mittente;
        m_resp.id_prodotto = m_req.id_prodotto;
        
        msgsnd(ds_queue_response, (void*)&m_resp, sizeof(Msg_Resp)-sizeof(long), 0);
        
        printf("[lettore] Messaggio di risposta inviato...\n");
        
        FineLettura(magazzino, id_prodotto);
    }
}

void scrittore(Magazzino *magazzino){
    int ret;
    Msg_Req m_req;
    int k;

    for (k = 0; k < 2; k++) {
        // TODO aggiungere codice per la ricezione del comando
        msgrcv(ds_queue_request, (void*)&m_req, sizeof(Msg_Req)-sizeof(long), WRITE_TYPE, 0);
        
		int id_prodotto = m_req.id_prodotto;
		
        // TODO aggiungere codice per la scrittura
        // InizioScrittura
        // Decremento del livello di scorta del prodotto indicato nella richiesta della quantità indicata nella richiesta
        // FineScrittura
        InizioScrittura(magazzino, id_prodotto);

        printf("[scrittore] Ricevuta richiesta di decremento di %d per prodotto %d\n",m_req.value, m_req.id_prodotto);
        magazzino->scorta[id_prodotto] -= m_req.value;
        
        FineScrittura(magazzino, id_prodotto);
    }
}


void InizioLettura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di inizio lettura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
    Wait_Sem(magazzino->MUTEX, id_prodotto);
    magazzino->num_lettori[id_prodotto]++;
    if(magazzino->num_lettori[id_prodotto] == 1)
    	Wait_Sem(magazzino->SYNCH, id_prodotto);
    Signal_Sem(magazzino->MUTEX, id_prodotto); 
}

void FineLettura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di fine lettura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
    Wait_Sem(magazzino->MUTEX, id_prodotto);
    magazzino->num_lettori[id_prodotto]--;
    if(magazzino->num_lettori[id_prodotto] == 0)
    	Signal_Sem(magazzino->SYNCH, id_prodotto); // risveglio uno scrittore
    Signal_Sem(magazzino->MUTEX, id_prodotto); 
}

void InizioScrittura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di inizio scrittura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
    Wait_Sem(magazzino->SYNCH, id_prodotto);
}
void FineScrittura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di fine scrittura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
    Signal_Sem(magazzino->SYNCH, id_prodotto);
}
