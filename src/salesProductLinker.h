/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _SALES_PRODUCT_LINKER_H_INCLUDED_
#define _SALES_PRODUCT_LINKER_H_INCLUDED_

typedef char* productCode;

typedef struct salesProductLinker*  SalesProductLinker;

SalesProductLinker newSalesProductLinker ( );

struct list* getNormalClientsWhoBoughtProduct__LL_STRINGS  ( SalesProductLinker , productCode );

struct list* getPromotionClientsWhoBoughtProduct__LL_STRINGS ( SalesProductLinker , productCode );

void addSalesLineToSPL ( struct salesProductLinker* salesPrLinker , char* productCode, char* clientCode , char salesMode , int unitsSold , float sellingPrice , int month );

struct list* getTopNMostSoldProducts__LL_STRINGS ( SalesProductLinker , int nMost );

int getGlobalNumberProducts ( struct salesProductLinker* salesPrLinker );

int getPromotionClientsNumberWhoBoughtProductInMonth ( struct salesProductLinker* salesPrLinker , char* productCode , int month );

int getNormalClientsNumberWhoBoughtProductInMonth ( struct salesProductLinker* salesPrLinker , char* productCode , int month );

float getTotalBilledByProductInMonth ( struct salesProductLinker* salesPrLinker , char* productCode , int month );

#endif /* _SALES_PRODUCT_LINKER_H_INCLUDED_ */

