/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */


#ifndef _PRODUCT_SALES_H_INCLUDED_
#define _PRODUCT_SALES_H_INCLUDED_

typedef struct productSales* ProductSales;

ProductSales newProductSales ( char* ProductCode );

int getClientSalesUnitsSold ( ProductSales );

ProductSales addUnitProductSales (  ProductSales , int );

int equalsProductSales ( void* , void* );

void deleteProductSales ( void* );

int productSalesUnitComparator ( void* comp1 , void* comp2 );

void* toStringProductSales ( void* );

#endif /* _PRODUCT_SALES_H_INCLUDED_ */

