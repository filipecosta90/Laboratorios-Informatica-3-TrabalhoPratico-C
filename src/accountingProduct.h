/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _ACCOUNTING_PRODUCT_H_INCLUDED_
#define _ACCOUNTING_PRODUCT_H_INCLUDED_

typedef struct accountingProduct*  AccountingProduct;

AccountingProduct newAccountingProduct ( void );

void setAccountingProduct ( AccountingProduct , int , float , int , float );

int getNSales ( AccountingProduct );

int getPSales ( AccountingProduct );

float getNBilled ( AccountingProduct );

float getPBilled ( AccountingProduct );

float getTotalBilled ( AccountingProduct );

#endif /* _CLIENT_H_INCLUDED_ */

