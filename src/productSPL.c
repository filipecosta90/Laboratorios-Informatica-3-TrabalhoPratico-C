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
  int normalSalesByMonth[12];
  int promotionSalesByMonth[12];
  float billedByMonth[12];
};

ProductSPL newProductSPL ( char* ProductCode ){
  int stringSize;

  /* allocate memory for struct */
  ProductSPL productSPLNew = ( ProductSPL ) malloc ( sizeof ( struct productSPL ));
  memset ( ( productSPLNew ), '\0', ( sizeof ( struct productSPL ) ) );

  /* string */
  stringSize = strlen ( ProductCode );
  productSPLNew->productCode = ( char* ) malloc ( ( stringSize +1 ) * sizeof ( char ) );
  strcpy ( productSPLNew->productCode , ProductCode );

  /* counters */
  productSPLNew->unitsSold = 0;
  productSPLNew->distinctClients = 0;

  /* BSTrees */
  productSPLNew->normalBST = newBSTree ( &equalsClientSales );
  productSPLNew->promotionBST = newBSTree ( equalsClientSales );

  /* arrays by month */
  memset( productSPLNew->normalSalesByMonth ,0,sizeof( productSPLNew->normalSalesByMonth ));
  memset( productSPLNew->promotionSalesByMonth ,0,sizeof( productSPLNew->promotionSalesByMonth ));
  memset( productSPLNew->billedByMonth ,0.0,sizeof( productSPLNew->billedByMonth ));

  return productSPLNew;
}

ProductSPL addSaleSPL ( ProductSPL splProd , char* ClientCode , char SaleType , int UnitType , float PriceType , int month ){
  ClientSales client1;
  ClientSales searchResultNormal, searchResultPromotion;
  assert ( splProd != NULL );
  client1 = newClientSales ( ClientCode );
  searchResultNormal = NULL;
  searchResultPromotion = NULL;
  /* SPL counters */
  splProd->unitsSold += UnitType;
  splProd->billedByMonth[month-1] += PriceType;

  searchResultNormal = (ClientSales) searchBst ( splProd->normalBST , client1 );
  searchResultPromotion = (ClientSales) searchBst ( splProd->promotionBST , client1 );

  if( searchResultNormal == NULL && searchResultPromotion == NULL ){
    splProd->distinctClients++;
  }

  if ( SaleType == 'N'){
    splProd->normalSalesByMonth[month-1] += UnitType;
    if ( searchResultNormal == NULL ){
      client1 = addUnitClientSales ( client1 , UnitType );
      insertBst ( splProd->normalBST , client1 );
    }
    else{
      searchResultNormal = addUnitClientSales ( searchResultNormal , UnitType );
    }
  }
  if ( SaleType == 'P' ){
    splProd->promotionSalesByMonth[month-1] += UnitType;
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

int productSPLUnitComparator ( void* comp1 , void* comp2 ){
  ProductSPL p1, p2;
  int returningValue;
  if ( comp1 == NULL || comp2 == NULL ){
    returningValue = 0;
  }
  else{
    p1 = ( ProductSPL ) comp1;
    p2 = ( ProductSPL ) comp2;
    returningValue = p1->unitsSold - p2->unitsSold;
    if ( returningValue == 0 ){
      returningValue = strcmp ( p2->productCode , p1->productCode );
    }
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

char* productSPLToString ( void* toString ){
  ProductSPL sp1;

  int length, lengthUnitsSold, lengthDistinctClients;
  char buffer1[20], buffer2[20];
  char* newString;
  assert( toString != NULL );
  sp1 = ( ProductSPL ) toString;
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

void destroyProductSPL ( void* myfree ){
  ProductSPL mF;
  mF = NULL;
  assert ( myfree != NULL );
  mF = ( ProductSPL ) myfree;
  free ( mF );
}

int productSPLGetNormalClientsNumberInMonth ( ProductSPL splProd  , int month ){
  return splProd->normalSalesByMonth[month-1];

}

int productSPLGetPromotionClientsNumberInMonth ( ProductSPL splProd , int month ){
  return splProd->promotionSalesByMonth[month-1];
}

float productSPLGetTotalBilledInMonth ( ProductSPL splProd , int month ){
  return splProd->billedByMonth[month-1];
}
