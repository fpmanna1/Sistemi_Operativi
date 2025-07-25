#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "auth.h"

int main() {

    printf("Creazione code di messaggi\n");

    int id_coda_auth_req = msgget(IPC_PRIVATE, IPC_CREAT | 0664);

    int id_coda_auth_resp = msgget(IPC_PRIVATE, IPC_CREAT | 0664);
    
    int id_coda_elab_req = msgget(IPC_PRIVATE, IPC_CREAT | 0664);
    
    int id_coda_elab_resp = msgget(IPC_PRIVATE, IPC_CREAT | 0664);


    pid_t pid;


    printf("Avvio processo autenticatore\n");

    /* TBD: Avvio processo (funzione Auth) */
    if(!fork)
    {
    	Auth(id_coda_auth_req, id_coda_auth_resp);
    	exit(0);
    }
   
    printf("Avvio processo server\n");

    /* TBD: Avvio processo (funzione Server) */
    if(!fork)
    {
    	Server(id_coda_elab_req, id_coda_elab_resp, id_coda_auth_req, id_coda_auth_resp);
    	exit(0);
    }

    printf("Avvio processo client autenticato\n");

    /* TBD: Avvio processo (funzione ClientAuth) */
    if(!fork)
    {
    	ClientAuth(id_coda_auth_req, id_coda_auth_resp, id_coda_elab_req, id_coda_elab_resp);
    	exit(0);
    }
    
    printf("Avvio processo client non-autenticato\n");

    /* TBD: Avvio processo (funzione ClientNonAuth) */
	if(!fork)
	{
		ClientNonAuth(id_coda_elab_req, id_coda_elab_resp);
		exit(0);
	}

    printf("Attesa terminazione processi\n");

    /* TBD: Attesa terminazione */
    for(int i=0; i<NUM_CLIENT + NUM_SERVER + NUM_AUTH; i++)
    {
    	wait(NULL);
    }


    printf("Rimozione code di messaggi\n");

    /* TBD: Rimozione code */ 
    msgctl(id_coda_elab_req, IPC_RMID, 0);
    msgctl(id_coda_elab_resp, IPC_RMID, 0);
    msgctl(id_coda_auth_req, IPC_RMID, 0);
    msgctl(id_coda_auth_resp, IPC_RMID, 0);
    
    return 0;
}
