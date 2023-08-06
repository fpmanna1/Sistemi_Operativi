#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "monitor.h"
#include "header.h"

int main()
{
	Monitor m;
	pid_t pid;
	key_t key_shm;
	int id_mag;
	struct magazzino* magazzino;
	
	// creazione shared memory
	id_mag = shmget(IPC_PRIVATE, sizeof(struct magazzino), IPC_CREAT | 0664);
	
	// attach della memoria condvisa
	magazzino = (struct magazzino*) shmat(id_mag, 0, 0);
	
	//inizializzazione del magazzino
	init_monitor(&m, N_CV);
	for(int i=0; i<MAX_DIM; i++)
		magazzino->s[i].stato = LIBERO;
		
	magazzino->livello_scorte = 0;
	magazzino->m = m;
	// creazionedi 10 fornitori e di 10 clienti
	
	for(int i=0; i<NUM_FORNITORI; i++)
	{
		pid=fork();
		if(pid == 0)
		{
			fornitore(magazzino);
			printf("\nCreazione del fornitore %d\n", i);
			exit(0);
		}
	}
	
	for(int i=0; i<NUM_CLIENTI; i++)
	{
		pid=fork();
		if(pid == 0)
		{
			cliente(magazzino);
			printf("\nCreazione del cliente %d\n", i);
			exit(0);
		}
	}
	
	for(int i=0; i<NUM_PROCESSI; i++)
	{
		wait(NULL);
		printf("Processo %d correttamente terminato\n", i);
	}
	
	remove_monitor(&m);
	
	shmctl(id_mag, IPC_RMID, 0);
	
	return 0;
}
