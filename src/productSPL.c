/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "genLinkedList.h"
#include "binarySearchTree.h"
#include "productSPL.h"
#include "clientSales.h"
#include <assert.h>

struct productSPL {
  char* productCode;
  int unitsSold;
  int distinctClients;
  struct bsTree* normalBST;
  struct bsTree* promotionBST;
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

  productSPLNew->normalBST = newBSTree ( &equalsClientSales );
  productSPLNew->promotionBST = newBSTree ( equalsClientSales );

  return productSPLNew;
}

ProductSPL addSaleSPL ( ProductSPL splProd , char* ClientCode , char SaleType , int UnitType , float PriceType ){
  ClientSales client1;
  ClientSales searchResultNormal, searchResultPromotion;
  assert ( splProd != NULL );
  client1 = newClientSales ( ClientCode );
  searchResultNormal = NULL;
  searchResultPromotion = NULL;
  splProd->unitsSold += UnitType;
  searchResultNormal = (ClientSales) searchBst ( splProd->normalBST , client1 );
  searchResultPromotion = (ClientSales) searchBst ( splProd->promotionBST , client1 );

  if( searchResultNormal == NULL && searchResultPromotion == NULL ){
    splProd->distinctClients++;
  }

  if ( SaleType == 'N'){
    if ( searchResultNormal == NULL ){
      client1 = addUnitClientSales ( client1 , UnitType );
      insertBst ( splProd->normalBST , client1 );
    }
    else{
      searchResultNormal = addUnitClientSales ( searchResultNormal , UnitType );
    }
  }
  if ( SaleType == 'P' ){
    if( searchResultPromotion == NULL ){
      client1 = addUnitClientSales ( client1 , UnitType );
      insertBst ( splProd->promotionBST , client1 );
    }
    else{
      searchResultPromotion = addUnitClientSales ( searchResultPromotion , UnitType );
    }
  }
  return splProd;
}

int productSPLEquals ( void *isEqual1, void* isEqual2 ){
  ProductSPL p1, p2;
  int returningValue;
  if ( isEqual1 == NULL || isEqual2 == NULL ){
    returningValue = 0;
  }
  else{
    p1 = ( ProductSPL ) isEqual1;
    p2 = ( ProductSPL ) isEqual2;
    returningValue = strcmp ( p1->productCode , p2->productCode );
  }
  return returningValue;
}

void myFreeChar ( void* myfree ){
  char* stringF;
  stringF = NULL;
  assert ( myfree != NULL );
  stringF = ( char* ) myfree;
  free ( stringF );
}

List productSPLGetNormalClients__LL_STRINGS ( ProductSPL splProd ){
  List returningList;
  returningList = initLL ( ) ;
  assert ( splProd != NULL );
  newLL ( returningList , sizeof ( char* ) , &myFreeChar );
  returningList = BSTreeToLL_ToString ( splProd->normalBST , sizeof ( char* ) , &myFreeChar, &toStringClientSales  );
  return returningList;
}

List productSPLGetPromotionClients__LL_STRINGS ( ProductSPL splProd ){
  List returningList;
  returningList = initLL ( ) ;
  assert ( splProd != NULL );
  newLL ( returningList , sizeof ( char* ) , &myFreeChar );
  returningList = BSTreeToLL_ToString ( splProd->promotionBST , sizeof ( char* ) , &myFreeChar , &toStringClientSales );
  return returningList;
}

char* productSPLToString ( ProductSPL sp1 ){
  int length, lengthUnitsSold, lengthDistinctClients;
  char buffer1[20], buffer2[20];
  char* newString;
  assert ( sp1 != NULL );
  length = strlen ( sp1->productCode );
  sprintf(buffer1, "%d", sp1->unitsSold);
  lengthUnitsSold = strlen ( buffer1 );
  length += lengthUnitsSold;
  sprintf(buffer2, "%d", sp1->distinctClients);
  lengthDistinctClients = strlen ( buffer2 );
  length += lengthDistinctClients;
  newString = ( char* ) malloc ( ( length +1+13+19+1 ) * sizeof ( char ));
  strcpy ( newString , sp1->productCode );
  strcat ( newString , "\tUNITS SOLD: ");
  strcat ( newString , buffer1 );
  strcat ( newString , "\tDISTINCT CLIENTS: " );
  strcat ( newString , buffer2 );
  strcat ( newString , "\n" );
  return newString;
}

