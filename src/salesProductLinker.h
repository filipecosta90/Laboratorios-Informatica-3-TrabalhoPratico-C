/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _SALES_PRODUCT_LINKER_H_INCLUDED_
#define _SALES_PRODUCT_LINKER_H_INCLUDED_

typedef char* productCode;

typedef struct salesProductLinker*  SalesProductLinker;

SalesProductLinker newSalesProductLinker ( );

struct list* getClientsWhoBoughtProduct__LL  ( SalesProductLinker , productCode );

void addSalesLineToSPL ( struct salesProductLinker* salesPrLinker , char* productCode, char* clientCode , char salesMode , int unitsSold , float sellingPrice );

struct list* getTopNMostSoldProducts__LL ( SalesProductLinker , int nMost ,  int* totalClients , int* numberUnitsSold );

int getNumberOfIdleProducts ( SalesProductLinker );

#endif /* _SALES_PRODUCT_LINKER_H_INCLUDED_ */

