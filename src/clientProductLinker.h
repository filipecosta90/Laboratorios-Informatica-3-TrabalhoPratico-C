/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _CLIENT_PRODUCT_LINKER_H_INCLUDED_
#define _CLIENT_PRODUCT_LINKER_H_INCLUDED_

typedef struct clientProductLinker*  ClientProductLinker;

/* retorna um novo clientProductLinker */
struct clientProductLinker* newClientProductLinker ( );

/* reinicia o  clientProductLinker */
struct clientProductLinker* resetClientProductLinker ( struct clientProductLinker* resetCPL );

/* elimina o  clientProductLinker */
void deleteClientProductLinker ( struct clientProductLinker* deleteCPL );

/* adiciona vendas ao clientProductLinker */
void addSalesLineToCPL ( struct clientProductLinker* clientPrLinker , char* productCode, char* clientCode , int unitsSold , int month );

/* QUERIE 5 */
/* retorna uma lista de strings onde em cada linha está um mês com as vendas do cliente */
struct list* getClientProductTableByMonth__LL_STRINGS ( ClientProductLinker clientPrLinker , char* clientCode );

/* QUERIE 9 */
/* retorna uma lista de strings ordenada dos productos comprados do cliente num determinado mês */
struct list* getClientOrderedProductListOfMonth__LL_STRINGS ( ClientProductLinker clientPrLinker , char* clientCode , int month );

/* QUERIE 10 */
/* retorna uma lista de strings de clientes que compraram todos os meses do ano */
struct list* getClientsWhoBoughtEveryMonth__LL_STRINGS ( ClientProductLinker clientPrLinker , struct clientCatalog* );

/* QUERIE 11 */
/* retorna o número de clientes para um determinado mês */
int  getCPLinkerMonthSize ( ClientProductLinker clientPrLinker , int month );

/* QUERIE 13 */
/* retorna um top de produtos comprados pelo cliente durante o ano*/
struct list* getClientTopNMostBoughtProducts__LL_STRINGS ( ClientProductLinker clientPrLinker , char* clientCode, int nMost );

/* QUERIE 14.1 */
/* retorna uma lista strings de clientes que nunca compraram produtos */
struct list* getClientsWhoNeverBoughtProducts__LL_STRINGS ( ClientProductLinker clientPrLinker , ClientCatalog clCat );

/* QUERIE 14 */
/* retorna um inteiro contado o numero de clientes que nunca compraram produtos */
int getTotalClientsNumberWhoNeverBoughtProducts ( ClientProductLinker clientPrLinker , ClientCatalog clCat );

#endif /* _CLIENT_PRODUCT_LINKER_H_INCLUDED_ */

