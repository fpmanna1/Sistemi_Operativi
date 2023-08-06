#include "header.h"

int main()
{
	key_t key_ric = ftok(".",'a');
	key_t key_ris = ftok(".", 'b');
	coda_RICHIESTA = msgget(key_ric, 0);
	coda_RISPOSTA = msgget(key_ris, 0);
	Messaggio* m;
	Risultato* r;
	m->PIDclient = getpid();
	
	srand(time(NULL));
	
	for(int i=0; i<5; i++)
	{
		m->val1 = (rand() % 10);
		m->val2 = (rand() % 10);
		msgsnd(coda_RICHIESTA, m, sizeof(Messaggio)-sizeof(long), 0);
		printf("Messaggio con %d e %d inviato!, PID = %d\n", m->val1, m->val2, m->PIDclient);
		msgrcv(coda_RISPOSTA, r, sizeof(Risultato)-sizeof(long), getpid(), 0);
		printf("Stampa del messaggio di risposta: PID : %d, Risultato : %d\n", r->PIDclient, r->val3);
	}
	
	return 0;
}
