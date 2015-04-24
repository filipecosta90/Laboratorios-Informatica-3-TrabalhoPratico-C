/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _CLIENT_PRODUCT_LINKER_H_INCLUDED_
#define _CLIENT_PRODUCT_LINKER_H_INCLUDED_

typedef struct clientProductLinker*  ClientProductLinker;

struct clientProductLinker* newClientProductLinker ( );

struct clientProductLinker* resetClientProductLinker ( struct clientProductLinker* resetCPL );

void addSalesLineToCPL ( struct clientProductLinker* clientPrLinker , char* productCode, char* clientCode , int unitsSold , int month );

/* QUERIE 5 */
struct list* getClientProductTableByMonth__LL_STRINGS ( ClientProductLinker clientPrLinker , char* clientCode );

/* QUERIE 9 */
struct list* getClientOrderedProductListOfMonth__LL_STRINGS ( ClientProductLinker clientPrLinker , char* clientCode , int month );

/* QUERIE 10 */
struct list* getClientsWhoBoughtEveryMonth__LL_STRINGS ( ClientProductLinker clientPrLinker , struct clientCatalog* );

/* QUERIE 11 */
int  getCPLinkerMonthSize ( ClientProductLinker clientPrLinker , int month );

/* QUERIE 13 */
struct list* getClientTopNMostBoughtProducts__LL_STRINGS ( ClientProductLinker clientPrLinker , char* clientCode, int nMost );

/* QUERIE 14.1 */
struct list* getClientsWhoNeverBoughtProducts__LL_STRINGS ( ClientProductLinker clientPrLinker , ClientCatalog clCat );

/* QUERIE 14 */
int getTotalClientsNumberWhoNeverBoughtProducts ( ClientProductLinker clientPrLinker , ClientCatalog clCat );

#endif /* _CLIENT_PRODUCT_LINKER_H_INCLUDED_ */

