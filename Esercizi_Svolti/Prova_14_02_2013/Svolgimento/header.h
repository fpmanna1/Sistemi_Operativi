#ifndef HEADER_H
#define HEADER_H

#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sem.h>

#define MUTEXL 0 // accesso in mutua esclusione a num_lettori
#define MUTEXA 1 // accesso in mutua esclusione a prossimo_appello
#define MUTEXP 2 // 

#define STRING_MAX_DIM 11

// è un problema lettore-scrittore
typedef struct{
	char prossimo_appello[STRING_MAX_DIM];
	int prenotati;
	int num_lettori;
}struttura;

void inizio_lettura(int sem,struttura* esame);
void fine_lettura(int sem,struttura* esame);
void inizio_scrittura(int sem);
void fine_scrittura(int sem);
void accedi_prenotati(int sem);
void lascia_prenotati(int sem);

#endif
