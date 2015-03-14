/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */


#ifndef _PRODUCT_CATALOG_H_INCLUDED_
#define _PRODUCT_CATALOG_H_INCLUDED_

typedef struct accounting * Accounting;

void initAccounting ( Accounting );

Accounting newAccounting ( void );

void addSale ( Accounting , int );

void addClient ( Accounting , int );

void addBill ( Accounting, int , float );

char* getCsvMonth ( Accounting, int );

int getIntervalTotalSales ( Accounting, int, int );

float getIntervalTotalBilled ( Accounting, int, int );

void deleteAccounting ( Accounting );

#endif /* _PRODUCT_CATALOG_H_INCLUDED_ */

