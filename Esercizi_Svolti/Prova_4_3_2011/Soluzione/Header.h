#include <sys/types.h>

#define RICHIESTE 5
#define CLIENT 3

typedef struct{
	long pid;
	int v1;
	int v2;
}Buffer_C;

typedef struct{
	long pid;
	int v3; // valore finale prodotto, calcolato dai thread
}Buffer_S;

void client();
void server();
void* Prodotto(void*);
