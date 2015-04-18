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

typedef char* ClientCode;

typedef char* ProductCode;

ProductSPL newProductSPL ( ProductCode );

ProductSPL addSaleSPL ( ProductSPL , ClientCode , SaleType , UnitType , PriceType , int month );

int getTotalClientsSPL ( ProductSPL );

UnitType getTotalUnitsSoldSPL ( ProductSPL );

int productSPLEquals ( void* , void* );

int productSPLUnitComparator ( void* comp1 , void* comp2 );

void* productSPLToString ( void* );

struct list* productSPLGetNormalClients__LL_STRINGS ( ProductSPL );

struct list* productSPLGetPromotionClients__LL_STRINGS ( ProductSPL );

void destroyProductSPL ( void* );

int productSPLGetNormalClientsNumberInMonth ( ProductSPL , int month );

int productSPLGetPromotionClientsNumberInMonth ( ProductSPL , int month );

float productSPLGetTotalBilledInMonth ( ProductSPL , int month );

#endif /* _PRODUCT_SPL_H_INCLUDED_ */

