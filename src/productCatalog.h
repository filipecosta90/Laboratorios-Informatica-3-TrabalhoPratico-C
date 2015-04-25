/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _PRODUCT_CATALOG_H_INCLUDED_
#define _PRODUCT_CATALOG_H_INCLUDED_

typedef struct productCatalog * ProductCatalog;

typedef char* ProductCode;

/* retorna um novo ProductCatalog */
ProductCatalog newProductCatalog ( void );

/* reinicia os valores do ProductCatalog */
struct productCatalog* resetProductCatalog ( struct productCatalog* resetPrCat );

/* inicializa os valores do ProductCatalog */
void initProductCatalog ( ProductCatalog );

/* adiciona produto ao ProductCatalog */
void addProductToCatalog ( ProductCatalog , ProductCode );

/* verifica se contem o produto no ProductCatalog*/
int containsProductCode ( ProductCatalog, ProductCode );

/* retorna o número total de produtos presentes no ProductCatalog iniciados por uma letra */
int getTotalProductsByLetter ( struct productCatalog* prCat, char productInitial );

/* elimina o ProductCatalog */
void deleteProductCatalog ( ProductCatalog );

/* retorna o numero totoal de produtos presente no ProductCatalog */
int getProductCatalogSize ( ProductCatalog );

/* QUERIE 2 */
/* retorna uma lista de strings contendo os nomes de produto presentes no ProductCatalog iniciados por uma letra */
struct list* getProductsByLetter__LL_strings ( struct productCatalog* prCat , char productInitial );

/* QUERIE 4 AUXILIAR METHOD */
/* retorna uma lista de strings contendo a totalidade dos nome de produto presentes no ProductCatalog*/
struct list* getFullProducts__LL_strings ( struct productCatalog* prCat , struct list* returningLL );

#endif /* _PRODUCT_CATALOG_H_INCLUDED_ */

