/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include <stdlib.h>
#include <string.h>
#include "productSPL.h"
#include "clientSales.h"
#include "binarySearchTree.h"
#include "assert.h"

struct productSPL {
  char* productCode;
  int unitsSold;
  struct bstNode* normalBST;
  struct bstNode* promotionBST;
  int ( *client_Comparator ) ( void* , void* );
};

ProductSPL newProductSPL ( char* ProductCode ){
  int stringSize;

  ProductSPL productSPLNew = ( ProductSPL ) malloc ( sizeof ( struct productSPL ));
  memset ( ( productSPLNew ), '\0', ( sizeof ( struct productSPL ) ) );

  stringSize = strlen ( ProductCode );
  productSPLNew->productCode = ( char* ) malloc ( ( stringSize +1 ) * sizeof ( char ) );
  strcpy ( productSPLNew->productCode , ProductCode );

  productSPLNew->normalBST = newNodeBst ( NULL );
  productSPLNew->promotionBST = newNodeBst ( NULL );
  productSPLNew->client_Comparator = &equalsClientSales; 

  return productSPLNew;
}

int equals (ProductSPL isEqual1, ProductSPL isEqual2 ){
  int returningValue = -1;
  assert ( isEqual1 != NULL && isEqual2 != NULL );
  returningValue = strcmp ( isEqual1->productCode , isEqual2->productCode );
  return returningValue;
}

