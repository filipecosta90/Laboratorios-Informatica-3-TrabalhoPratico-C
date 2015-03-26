/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _SALES_PRODUCT_LINKER_H_INCLUDED_
#define _SALES_PRODUCT_LINKER_H_INCLUDED_

typedef struct salesProductLinker*  SalesProductLinker;

SalesProductLinker newSalesProductLinker ( void );

int getClientsWhoBoughtProduct__LL  ( SalesProductLinker , char* , List );

int getTopNMostSoldProducts__LL ( SalesProductLinker , int , List , int* , int* );

int getNumberOfIdleProducts ( SalesProductLinker );

#endif /* _CLIENT_H_INCLUDED_ */

