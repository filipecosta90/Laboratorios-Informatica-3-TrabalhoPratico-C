/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include "genLinkedList.h"
#include "avlTree.h"
#include "binarySearchTree.h"
#include "clientProductLinker.h"
#include "clientCPL.h"
#include "clientSales.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct clientProductLinker {
  struct bsTree* lettersArray[12][26][26];
};

struct clientProductLinker* newClientProductLinker ( ) {
  struct clientProductLinker* newCPL = ( struct clientProductLinker* ) malloc ( sizeof (struct clientProductLinker ) );
  int out , in, month;
  in = 0;
  out = 0;
  month = 0;
  for ( ; month < 12 ; month ++ ){
    out = 0;
    for( ; out<26; out++){
      in = 0;
      for ( ; in<26; in++ ){
        newCPL->lettersArray[month][out][in] = newBSTree ( &clientCPLEquals );
      }
    }
  }
  return newCPL;
}

static int getClientCPLArrayOutPosition ( char* clientCode ) {
  int position;
  position = (int) clientCode[0];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

static int getClientCPLArrayInPosition ( char* clientCode ) {
  int position;
  position = (int) clientCode[1];
  if ( position >= 65 && position <= 90 ) { position -= 65; } 
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

void addSalesLineToCPL ( struct clientProductLinker* clientPrLinker , char* productCode, char* clientCode , int unitsSold , int month ) {
  int outPosition, inPosition;
  ClientCPL searchResult = NULL;
  ClientCPL cplClient;
  outPosition = getClientCPLArrayOutPosition( clientCode );
  inPosition = getClientCPLArrayInPosition ( clientCode );
  cplClient = newClientCPL ( clientCode );
  searchResult = (ClientCPL) searchBst ( clientPrLinker->lettersArray[month-1][outPosition][inPosition], cplClient );
  if ( searchResult == NULL ){
    cplClient = addProductCPL ( cplClient , productCode , unitsSold );
    insertBst ( clientPrLinker->lettersArray[month-1][outPosition][inPosition] , cplClient );
  }
  else {
    searchResult = addProductCPL ( searchResult , productCode , unitsSold );
  }
}

void myFreeCharCPL1 ( void* myfree ){
  char* stringF;
  stringF = NULL;
  assert ( myfree != NULL );
  stringF = ( char* ) myfree;
  free ( stringF );
}

/* QUERIE 5 */
struct list* getClientProductTableByMonth__LL_STRINGS ( ClientProductLinker clientPrLinker , char* clientCode ){
  List returnLL;
  int inPosition, outPosition, month, unitsSold;
  ClientCPL searchResult;
  ClientCPL cplClient;
  int length, lengthUnitsSold;
  char buffer1[20], buffer2[20];
  char* newString;
  returnLL = initLL ();
  outPosition = getClientCPLArrayOutPosition( clientCode );
  inPosition = getClientCPLArrayInPosition ( clientCode );
  cplClient = newClientCPL ( clientCode );
  month = 0;
  newLL ( returnLL , sizeof ( char* ) , &myFreeCharCPL1 );
  length = strlen ( clientCode );
  newString = ( char* ) malloc ( ( length +1+37+1 ) * sizeof ( char ));
  strcat ( newString , "TOTAL BOUGTH PRODUCTS (BY MONTH) OF: ");
  strcat ( newString , clientCode );
  strcat ( newString , "\n");
  appendLL ( returnLL , newString );
  for ( ; month < 12 ; month++ ){
    searchResult = (ClientCPL) searchBst ( clientPrLinker->lettersArray[month][outPosition][inPosition], cplClient );
    if ( searchResult == NULL ){
      unitsSold = 0;
    }
    else {
      unitsSold = clientCPLGetTotalProduct  ( searchResult );
    }
    sprintf(buffer1, "%d", month+1);
    sprintf(buffer2, "%d", unitsSold);
    lengthUnitsSold = strlen ( buffer2 );
    length += lengthUnitsSold;
    newString = ( char* ) malloc ( ( length +9+16+1+1 ) * sizeof ( char ));
    strcat ( newString , "\tMONTH: ");
    strcat ( newString , buffer1 );
    strcat ( newString , "\tUNITS BOUGHT: " );
    strcat ( newString , buffer2 );
    strcat ( newString , "\n" );
    appendLL ( returnLL , newString );
  }
  return returnLL;
}

/* QUERIE 9 */
struct list* getClientOrderedProductListOfMonth__LL_STRINGS ( ClientProductLinker clientPrLinker , char* clientCode , int month ){
  List returnLL;
  int inPosition, outPosition;
  ClientCPL searchResult;
  ClientCPL cplClient;
  returnLL = initLL ();
  outPosition = getClientCPLArrayOutPosition( clientCode );
  inPosition = getClientCPLArrayInPosition ( clientCode );
  cplClient = newClientCPL ( clientCode );
  searchResult = (ClientCPL) searchBst ( clientPrLinker->lettersArray[month-1][outPosition][inPosition], cplClient );
  returnLL = clientCPLGetProduct__LL_STRINGS ( searchResult );
  return returnLL;
}
