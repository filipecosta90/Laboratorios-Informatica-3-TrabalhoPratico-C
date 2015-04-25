/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _SALES_PRODUCT_LINKER_H_INCLUDED_
#define _SALES_PRODUCT_LINKER_H_INCLUDED_

typedef char* productCode;

typedef struct salesProductLinker*  SalesProductLinker;

/* retorna um novo salesProductLinker */
SalesProductLinker newSalesProductLinker ( );

/* reinicia o salesProductLinker */
struct salesProductLinker* resetSalesProductLinker ( struct salesProductLinker* resetSPL );

/* elimina o salesProductLinker */
void deleteSalesProductLinker ( struct salesProductLinker* deleteSPL );

/* retorna a lista de strings de clientes que compraram o produto em modo normal*/
struct list* getNormalClientsWhoBoughtProduct__LL_STRINGS  ( SalesProductLinker , productCode );

/* retorna a lista de strings de clientes que compraram o produto em modo promocional*/
struct list* getPromotionClientsWhoBoughtProduct__LL_STRINGS ( SalesProductLinker , productCode );

/* adiciona a linha de vendas ao SPL */
void addSalesLineToSPL ( struct salesProductLinker* salesPrLinker , char* productCode, char* clientCode , char salesMode , int unitsSold , float sellingPrice , int month );

/* retorna a lista dos produtos mais vendidos no ano*/
struct list* getTopNMostSoldProducts__LL_STRINGS ( SalesProductLinker , int nMost );

/* retorna o número de produtos - neste caso o número de produtos que foram comprados*/
int getGlobalNumberProducts ( struct salesProductLinker* salesPrLinker );

/* retorna a o número de clientes que compraram o produto em modo promocional no mês X */
int getPromotionClientsNumberWhoBoughtProductInMonth ( struct salesProductLinker* salesPrLinker , char* productCode , int month );

/* retorna a o número de clientes que compraram o produto em modo normal no mês X */
int getNormalClientsNumberWhoBoughtProductInMonth ( struct salesProductLinker* salesPrLinker , char* productCode , int month );

/* retorna o valor da facturação do produto no mês X */
float getTotalBilledByProductInMonth ( struct salesProductLinker* salesPrLinker , char* productCode , int month );

/* retorna a lista de strings de produtos que nunca foram comprados , para tal confere a sua lista de produtos com a lista de produtos do catálogo */
struct list* getProductsWhoWereNeverBought__LL_STRINGS ( SalesProductLinker salesPrLinker , ProductCatalog prCat );

#endif /* _SALES_PRODUCT_LINKER_H_INCLUDED_ */

