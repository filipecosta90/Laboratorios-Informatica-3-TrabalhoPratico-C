/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */


#ifndef _PRODUCT_SALES_H_INCLUDED_
#define _PRODUCT_SALES_H_INCLUDED_

typedef struct productSales* ProductSales;

/* retorna um novo productSales */
ProductSales newProductSales ( char* ProductCode );

/* retorna o numero de unidades vendidas do productSales */
int getProductSalesUnitsSold ( void* );

/* adiciona unidades ao productSales */
ProductSales addUnitProductSales (  ProductSales , int );

/* compara dois productSales */
int equalsProductSales ( void* , void* );

/* elimina dois productSales */
void deleteProductSales ( void* );

/* faz merge das unidades dos dois productSales para o passado em 1º parâmetro */
void* mergeProductSales ( void* , void* );

/* compara os dois productSales */
int productSalesUnitComparator ( void* comp1 , void* comp2 );

/* retorna um toString do productSales */
void* toStringProductSales ( void* );

#endif /* _PRODUCT_SALES_H_INCLUDED_ */

