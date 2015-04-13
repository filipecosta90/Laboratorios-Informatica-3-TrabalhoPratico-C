/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include <stdlib.h>
#include <string.h>
#include "productSPL.h"
#include "clientSales.h"
#include "binarySearchTree.h"
#include <assert.h>

struct productSPL {
  char* productCode;
  int unitsSold;
  int distinctClients;
  struct bstNode* normalBST;
  struct bstNode* promotionBST;
  int ( *clientComparator ) ( void* , void* );
};

ProductSPL newProductSPL ( char* ProductCode ){
  int stringSize;

  ProductSPL productSPLNew = ( ProductSPL ) malloc ( sizeof ( struct productSPL ));
  memset ( ( productSPLNew ), '\0', ( sizeof ( struct productSPL ) ) );

  stringSize = strlen ( ProductCode );
  productSPLNew->productCode = ( char* ) malloc ( ( stringSize +1 ) * sizeof ( char ) );
  strcpy ( productSPLNew->productCode , ProductCode );

  productSPLNew->unitsSold = 0;
  productSPLNew->distinctClients = 0;

  productSPLNew->normalBST = newNodeBst ( NULL );
  productSPLNew->promotionBST = newNodeBst ( NULL );
  productSPLNew->clientComparator = &equalsClientSales; 

  return productSPLNew;
}

ProductSPL addSaleSPL ( ProductSPL splProd , char* ClientCode , char SaleType , int UnitType , float PriceType ){
  ClientSales client1;
  struct bstNode** searchResultNormal;
  struct bstNode** searchResultPromotion;
  assert ( splProd != NULL );
  client1 = newClientSales ( ClientCode );
  searchResultNormal = NULL;
  searchResultPromotion = NULL;
  searchResultNormal = searchBst ( &splProd->normalBST , splProd->clientComparator , client1 );
  searchResultPromotion = searchBst ( &splProd->promotionBST , splProd->clientComparator , client1 );
  if( *searchResultNormal == NULL && *searchResultPromotion == NULL ){
    splProd->distinctClients++;
  }
  if ( SaleType == 'N'){
    if ( *searchResultNormal == NULL ){
      client1 = addUnitClientSales ( client1 , UnitType );
      insertBst ( &splProd->normalBST , splProd->clientComparator , client1 );
    }
    else{
      client1 = ( ClientSales ) getNodeBstData ( searchResultNormal );
      client1 = addUnitClientSales ( client1 , UnitType );
    }
  }
  if ( SaleType == 'P' ){
    if( *searchResultPromotion == NULL ){
      client1 = addUnitClientSales ( client1 , UnitType );
      insertBst ( &splProd->promotionBST , splProd->clientComparator , client1 );
    }
    else{
      client1 = ( ClientSales ) getNodeBstData ( searchResultPromotion );
      client1 = addUnitClientSales ( client1 , UnitType );
    }
  }
  return splProd; 
}

int productSPLEquals ( void *isEqual1, void* isEqual2 ){
  ProductSPL p1, p2;
  int returningValue = -1;
  assert ( isEqual1 != NULL && isEqual2 != NULL );
  p1 = ( ProductSPL ) isEqual1;
  p2 = ( ProductSPL ) isEqual2;
  returningValue = strcmp ( p1->productCode , p2->productCode );
  return returningValue;
}

