/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _PRODUCT_SPL_H_INCLUDED_
#define _PRODUCT_SPL_H_INCLUDED_

typedef struct productSPL* ProductSPL;

typedef char SaleType;

typedef int UnitType;

typedef float PriceType;

/* retorna um novo productSPL */
ProductSPL newProductSPL ( char* productCode );

/* adiciona a linha de vendas ao productSPL */
ProductSPL addSaleSPL ( ProductSPL , char* clientCode , SaleType , UnitType , PriceType , int month );

/* retorna o numero de clientes do productSPL */
int getTotalClientsSPL ( ProductSPL );

/* retorna o numero de unidades vendidas do productSPL */
UnitType getTotalUnitsSoldSPL ( ProductSPL );

/* compara dois productSPL */
int productSPLEquals ( void* , void* );

/* compara apenas as unidades de dois productSPL */
int productSPLUnitComparator ( void* comp1 , void* comp2 );

/* converte o productSPL para string */
void* productSPLToString ( void* );

/* retorna a lista de strings de clientes que compraram o productSPL em modo normal */
struct list* productSPLGetNormalClients__LL_STRINGS ( ProductSPL );

/* retorna a lista de strings de clientes que compraram o productSPL em modo promocional */
struct list* productSPLGetPromotionClients__LL_STRINGS ( ProductSPL );

/* destrói o productSPL */
void destroyProductSPL ( void* );

/* retorna a o número de clientes que compraram o productSPL em modo normal no mês X */
int productSPLGetNormalClientsNumberInMonth ( ProductSPL , int month );

/* retorna a o número de clientes que compraram o productSPL em modo promocional no mês X */
int productSPLGetPromotionClientsNumberInMonth ( ProductSPL , int month );

/* retorna o valor da facturação do productSPL no mês X */
float productSPLGetTotalBilledInMonth ( ProductSPL , int month );

#endif /* _PRODUCT_SPL_H_INCLUDED_ */

