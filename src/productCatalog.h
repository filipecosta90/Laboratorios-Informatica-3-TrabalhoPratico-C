/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _PRODUCT_CATALOG_H_INCLUDED_
#define _PRODUCT_CATALOG_H_INCLUDED_

typedef struct productCatalog * ProductCatalog;

typedef char* ProductCode;

ProductCatalog newProductCatalog ( void );

void initProductCatalog ( ProductCatalog );

void addProductToCatalog ( ProductCatalog , ProductCode );

int containsProductCode ( ProductCatalog, ProductCode );

int getTotalProductsByLetter ( struct productCatalog* prCat, char productInitial );

void deleteProductCatalog ( ProductCatalog );

int getProductCatalogSize ( ProductCatalog );

/* QUERIE 2 */
struct list* getProductsByLetter__LL_strings ( struct productCatalog* prCat , char productInitial );

/* QUERIE 4 AUXILIAR METHOD */
struct list* getFullProducts__LL_strings ( struct productCatalog* prCat , struct list* returningLL );

#endif /* _PRODUCT_CATALOG_H_INCLUDED_ */

