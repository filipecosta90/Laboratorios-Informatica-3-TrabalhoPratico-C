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

/* retorna novo ClientCPL */
ClientCPL newClientCPL ( ClientCode );

/* adiciona Produto ao ClientCPL */
ClientCPL addProductCPL ( ClientCPL , ProductCode , UnitType );

/* retorna uma lista de strings de produtos do clientCPL */
struct list* clientCPLGetProduct__LL_STRINGS ( ClientCPL cplClient );

/* QUERIE 5 */
/* retorna o total de produtos do clientCPL */
int clientCPLGetTotalProduct ( ClientCPL cplClient );

/* compara dois clientPL */
int clientCPLEquals ( void* , void* );

/* retorna toString do clientCPL */
char* clientCPLToString ( void* );

/* elimina clientCPL */
void destroyClientSPL ( void* );

/* retorna uma arvore binaria de clientCPL */
struct bsTree* getClientCPLBST ( ClientCPL cplClient  );

#endif /* _CLIENT_CPL_H_INCLUDED_ */

