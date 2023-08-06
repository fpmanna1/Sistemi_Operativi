#include "header.h"

void Wait_Sem(int sem, int num_sem){
	struct sembuf s;
	s->sem_flg = 0;
	s->sem_op = -1;
	s->sem_num = num_sem;
	semop(sem, &s, 1);
}

void Signal_Sem(int sem, int num_sem){
	struct sembuf s;
	s->sem_flg = 0;
	s->sem_op = 1;
	s->sem_num = num_sem;
	semop(sem, &s, 1);
}

void inizio_lettura(int sem,struttura* esame){
	Wait_Sem(sem, MUTEXL);
	esame->num_lettori++;
	if(esame->num_lettori == 1)
		Signal_Sem(sem, MUTEXA);
	Signal_Sem(sem, MUTEXL);
}

void fine_lettura(int sem,struttura* esame){
	Wait_Sem(sem, MUTEXL);
	esame->num_lettori--;
	if(esame->num_lettori == 0)
		Signal_Sem(sem, MUTEXA);
	Signal_Sem(sem, MUTEXL);
}

void inizio_scrittura(int sem){
	Wait_Sem(sem, MUTEXA);
}

void fine_scrittura(int sem){
	Signal_Sem(sem, MUTEXA);
}

void accedi_prenotati(int sem){
	Wait_Sem(sem, MUTEXP);
}

void lascia_prenotati(int sem){
	Signal_Sem(sem, MUTEXP);
}
