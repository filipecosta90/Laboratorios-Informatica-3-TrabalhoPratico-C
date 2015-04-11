/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */


#ifndef _CLIENT_CATALOG_H_INCLUDED_
#define _CLIENT_CATALOG_H_INCLUDED_

typedef struct clientCatalog * ClientCatalog;

typedef char* ClientCode;

ClientCatalog newClientCatalog ( void );

void addClientToCatalog ( ClientCatalog , ClientCode );

int containsClientCode ( ClientCatalog, ClientCode );

int getTotalClientsByLetter ( ClientCatalog, char );

void deleteClientCatalog ( ClientCatalog );

#endif /* _CLIENT_CATALOG_H_INCLUDED_ */

