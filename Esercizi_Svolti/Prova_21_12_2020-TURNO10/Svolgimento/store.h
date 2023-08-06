#ifndef HEADERM_H
#define HEADERM_H

#include "header.h"

#define SCORTA_INIZIALE 20

#define READ_TYPE 1
#define WRITE_TYPE 2


typedef struct {
    // TODO aggiungere le variabili necessarie alla sincronizzazione

    int scorta[MAX_PRODOTTI];
    
    int num_lettori[MAX_PRODOTTI];
    int num_scrittori;
    
	int MUTEX; // accesso in mutua esclusione a num_lettori
	int SYNCH; // mutua esclusione tra lettori e scrittori
    
}Magazzino;


void init_magazzino(Magazzino *magazzino);
void destroy_magazzino(Magazzino *magazzino);

void lettore(Magazzino *magazzino);
void scrittore(Magazzino *magazzino);

void InizioLettura(Magazzino *magazzino, int id_prodotto);
void FineLettura(Magazzino *magazzino, int id_prodotto);
void InizioScrittura(Magazzino *magazzino, int id_prodotto);
void FineScrittura(Magazzino *magazzino, int id_prodotto);



#endif
