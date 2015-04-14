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

ProductSPL addSaleSPL ( ProductSPL , ClientCode , SaleType , UnitType , PriceType );

struct list* getNClientCodes__LL ( ProductSPL );

struct list* getPClientCodes__LL ( ProductSPL );

int getTotalClientsSPL ( ProductSPL );

UnitType getTotalUnitsSoldSPL ( ProductSPL );

int productSPLEquals ( void* , void* );

char* productSPLToString ( ProductSPL );

List productSPLGetNormalClients__LL ( ProductSPL );

List productSPLGetPromotionClients__LL ( ProductSPL );

void destroyProductSPL ( ProductSPL );

#endif /* _PRODUCT_SPL_H_INCLUDED_ */

