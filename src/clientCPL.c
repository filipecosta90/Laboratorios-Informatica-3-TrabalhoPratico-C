/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "genLinkedList.h"
#include "binarySearchTree.h"
#include "clientCPL.h"
#include "productSales.h"
#include <assert.h>

struct clientCPL {
  char* clientCode;
  struct bsTree* productBST;
};

ClientCPL newClientCPL ( char* clientCode ){
  int stringSize;

  /* allocate memory for struct */
  ClientCPL clientCPLNew = ( ClientCPL ) malloc ( sizeof ( struct clientCPL ));
  memset ( ( clientCPLNew ), '\0', ( sizeof ( struct clientCPL ) ) );

  /* string */
  stringSize = strlen ( clientCode );
  clientCPLNew->clientCode = ( char* ) malloc ( ( stringSize +1 ) * sizeof ( char ) );
  strcpy ( clientCPLNew->clientCode , clientCode );

  /* BSTrees */
  clientCPLNew->productBST = newBSTree ( &equalsProductSales );

  return clientCPLNew;
}

ClientCPL addProductCPL ( ClientCPL cplClient , char* productCode , int UnitType ){
  ProductSales product1;
  ProductSales searchResult;
  assert ( cplClient != NULL );
  product1 = newProductSales ( productCode );
  searchResult = NULL;

  searchResult = (ProductSales) searchBst ( cplClient->productBST , product1 );

  if ( searchResult == NULL ){
    product1 = addUnitProductSales ( product1 , UnitType );
    insertBst ( cplClient->productBST , product1 );
  }
  else{
    searchResult = addUnitProductSales ( searchResult , UnitType );
  }
  return cplClient;
}

int clientCPLEquals ( void *isEqual1, void* isEqual2 ){
  ClientCPL c1, c2;
  int returningValue;
  if ( isEqual1 == NULL || isEqual2 == NULL ){
    returningValue = 0;
  }
  else{
    c1 = ( ClientCPL ) isEqual1;
    c2 = ( ClientCPL ) isEqual2;
    returningValue = strcmp ( c1->clientCode , c2->clientCode );
  }
  return returningValue;
}

void myFreeCharCPL ( void* myfree ){
  char* stringF;
  stringF = NULL;
  assert ( myfree != NULL );
  stringF = ( char* ) myfree;
  free ( stringF );
}

List clientCPLGetProduct__LL_STRINGS ( ClientCPL cplClient ){
  List productLL;
  List returningList;
  productLL = initLL ( );
  returningList = initLL ( ) ;
  assert ( cplClient != NULL );
  newLL ( productLL , sizeof ( ProductSales ) , &deleteProductSales );
  newLL ( returningList , sizeof ( char* ) , &myFreeCharCPL );
  productLL = BSTreeToOrderedLL ( cplClient->productBST , productLL , &productSalesUnitComparator  );
  returningList = convertLLtoStringer ( productLL , &toStringProductSales );
  return returningList;
}



/* QUERIE 5 */
int clientCPLGetTotalProduct ( ClientCPL cplClient ){
  if (cplClient == NULL){
    return ( 0 );
  }
  else {
    return  BSTreeMapReduceInt ( cplClient->productBST , &getProductSalesUnitsSold );
  }
}

struct bsTree* getClientCPLBST ( ClientCPL cplClient  ){
  return cplClient->productBST;
}

char* clientCPLToString ( void* toString ){
  ClientCPL cp1;
  int length;
  char* newString;
  assert( toString != NULL );
  cp1 = ( ClientCPL ) toString;
  length = strlen ( cp1->clientCode );
  newString = ( char* ) malloc ( ( length +1+1 ) * sizeof ( char ));
  strcpy ( newString , cp1->clientCode );
  strcat ( newString , "\n" );
  return newString;
}

void destroyClientCPL ( void* myfree ){
  ClientCPL mF;
  mF = NULL;
  assert ( myfree != NULL );
  mF = ( ClientCPL ) myfree;
  free ( mF );
}

