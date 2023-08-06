#ifndef _AUTH_H_
#define _AUTH_H_

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define NUM_CLIENT 2
#define NUM_SERVER 1
#define NUM_AUTH 1

typedef struct { // inviati da client e server

    long type;
    pid_t PIDclient;
    pid_t PIDserver;
    int token;

} RichiestaAuth;

typedef struct { // da inviare al server mettendo il pid del server nel campo tipo

    long type;
    int token;
    int esito;

} RispostaAuth;

typedef struct {

    long type;
    pid_t PID;
    int valore;
    int token;

} RichiestaElab; // richiesta scrittura della risorsa

typedef struct {

    long type;
    int esito;

} RispostaElab; // risposta del server alla richiesta di scrittura della risorsa del client



#define TOKEN_AUTH_REQ_TYPE 1
#define CONFERMA_AUTH_REQ_TYPE 2
#define ELAB_REQ_TYPE 3



void Auth(int id_coda_auth_req, int id_coda_auth_resp);
void Server(int id_coda_elab_req, int id_coda_elab_resp, int id_coda_auth_req, int id_coda_auth_resp);
void ClientAuth(int id_coda_auth_req, int id_coda_auth_resp, int id_coda_elab_req, int id_coda_elab_resp);
void ClientNonAuth(int id_coda_elab_req, int id_coda_elab_resp);



#endif /* _AUTH_H_ */
