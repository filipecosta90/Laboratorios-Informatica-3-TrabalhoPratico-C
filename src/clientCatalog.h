/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */


#ifndef _CLIENT_CATALOG_H_INCLUDED_
#define _CLIENT_CATALOG_H_INCLUDED_

typedef struct clientCatalog* ClientCatalog;

ClientCatalog newClientCatalog ( void );

void addClientToCatalog ( ClientCatalog , char* clientCode );

int containsClientCode ( ClientCatalog, char* clientCode );

int getTotalClientsByLetter ( ClientCatalog, char );

void deleteClientCatalog ( ClientCatalog );

/* QUERIE 6 */
struct list* getClientsByLetter__LL_strings ( struct clientCatalog* clCat , char letter );

/* QUERIE 10 AUXILIAR METHOD */
struct list* getFullClients__LL_strings ( struct clientCatalog* clCat , struct list* returningLL );

#endif /* _CLIENT_CATALOG_H_INCLUDED_ */

