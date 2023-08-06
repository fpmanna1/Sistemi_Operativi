#include "header.h"
#include <stdio.h>


void fornitore(struct magazzino* mag) // aka produttore
{
	for(int i=0; i<NUM_ACCESSI; i++)
	{
		int indice = 0;
		enter_monitor(&(mag->m));
		
		if(mag->livello_scorte == MAX_DIM)
			wait_condition(&(mag->m), CV_FORNITORE);
		while(indice <= MAX_DIM && mag->s[indice].stato != LIBERO)
			indice++;
		mag->s[indice].stato = IN_USO;
	
		leave_monitor(&(mag->m));
		
		// fornitura di un elemento
		sleep(2);
		printf("\n[FORNITORE %d] Fornitura fornita dal fornitore %d\n",i, getpid());
		mag->s[indice].id = getpid();
	
		enter_monitor(&(mag->m));
		
		mag->s[indice].stato = OCCUPATO;
		mag->livello_scorte++;
		signal_condition(&(mag->m), CV_CLIENTE);
		
		leave_monitor(&(mag->m));
	}
}

void cliente(struct magazzino* mag) // aka consumatore
{
	for(int i=0; i<NUM_ACCESSI; i++)
	{
		int indice = 0;
		enter_monitor(&(mag->m));
		
		if(mag->livello_scorte == 0)
			wait_condition(&(mag->m), CV_CLIENTE);
		while(indice <= MAX_DIM && mag->s[indice].stato != OCCUPATO)
			indice++;
		mag->s[indice].stato = IN_USO;
		
		leave_monitor(&(mag->m));
		
		// prelievo
		
		sleep(2);
		printf("\n[CLIENTE %d] Acquisto della fornitura del fornitore %d\n",i, mag->s[indice].id);
		printf("\nmag->s[%d].stato = %d\n", i, mag->s[i].stato);
		mag->s[indice].id = 0;
		
		enter_monitor(&(mag->m));
		
		mag->s[indice].stato = LIBERO;
		mag->livello_scorte--;
		signal_condition(&(mag->m), CV_FORNITORE);
		
		leave_monitor(&(mag->m));
	}


}

