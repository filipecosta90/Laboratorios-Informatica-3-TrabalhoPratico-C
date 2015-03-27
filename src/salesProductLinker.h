/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _SALES_PRODUCT_LINKER_H_INCLUDED_
#define _SALES_PRODUCT_LINKER_H_INCLUDED_

typedef struct salesProductLinker*  SalesProductLinker;

SalesProductLinker newSalesProductLinker ( int ( *cmp) ( void* , void* ) );

int getClientsWhoBoughtProduct__LL  ( struct salesProductLinker* salesPrLinker , char* prCode , struct list* returnLL );

int getTopNMostSoldProducts__LL ( SalesProductLinker , int , struct list* , int* , int* );

int getNumberOfIdleProducts ( SalesProductLinker );

#endif /* _CLIENT_H_INCLUDED_ */

