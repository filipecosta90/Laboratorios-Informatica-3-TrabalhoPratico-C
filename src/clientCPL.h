/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _CLIENT_CPL_H_INCLUDED_
#define _CLIENT_CPL_H_INCLUDED_

typedef struct clientCPL* ClientCPL;

typedef int UnitType;

typedef char* ClientCode;

typedef char* ProductCode;

ClientCPL newClientCPL ( ClientCode );

ClientCPL addProductCPL ( ClientCPL , ProductCode , UnitType );

struct list* clientCPLGetProduct__LL_STRINGS ( ClientCPL cplClient );

/* QUERIE 5 */
int clientCPLGetTotalProduct ( ClientCPL cplClient );

int clientCPLEquals ( void* , void* );

char* clientCPLToString ( void* );

void destroyClientSPL ( void* );

struct bsTree* getClientCPLBST ( ClientCPL cplClient  );

#endif /* _CLIENT_CPL_H_INCLUDED_ */

