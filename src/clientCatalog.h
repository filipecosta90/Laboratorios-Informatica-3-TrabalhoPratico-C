/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _CLIENT_CATALOG_H_INCLUDED_
#define _CLIENT_CATALOG_H_INCLUDED_

typedef struct clientCatalog* ClientCatalog;

/* retorna um novo ClientCatalog */
ClientCatalog newClientCatalog ( void );

/* reinicia os valores do ClientCatalog */
struct clientCatalog* resetClientCatalog ( struct clientCatalog* resetClCat );

/* adiciona cliente ao ClientCatalog */
void addClientToCatalog ( ClientCatalog , char* clientCode );

/* verifica se contém o codigo de cliente */
int containsClientCode ( ClientCatalog, char* clientCode );

/* retorna o número total de clientes presentes no ClientCatalog iniciados por uma letra */
int getTotalClientsByLetter ( ClientCatalog, char );

/* elimina o clientCatalog */
void deleteClientCatalog ( ClientCatalog );

/* QUERIE 6 */
/* retorna a lista de strings dos clientes presentes no ClientCatalog iniciados por uma letra */
struct list* getClientsByLetter__LL_strings ( struct clientCatalog* clCat , char letter );

/* QUERIE 10 AUXILIAR METHOD */
/* retorna uma lista de strings contendo a totalidade dos nome de cliente presentes no ClientCatalog*/
struct list* getFullClients__LL_strings ( struct clientCatalog* clCat , struct list* returningLL );

#endif /* _CLIENT_CATALOG_H_INCLUDED_ */

