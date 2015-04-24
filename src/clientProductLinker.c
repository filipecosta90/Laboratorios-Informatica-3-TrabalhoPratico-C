/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include "genLinkedList.h"
#include "avlTree.h"
#include "binarySearchTree.h"
#include "clientCatalog.h"
#include "clientCPL.h"
#include "clientSales.h"
#include "productSales.h"
#include "clientProductLinker.h"

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

struct clientProductLinker* resetClientProductLinker ( struct clientProductLinker* resetCPL ) {
  int out , in, month;
  in = 0;
  out = 0;
  month = 0;
  for ( ; month < 12 ; month ++ ){
    out = 0;
    for( ; out<26; out++){
      in = 0;
      for ( ; in<26; in++ ){
        resetCPL->lettersArray[month][out][in] = newBSTree ( &clientCPLEquals );
      }
    }
  }
  return resetCPL;
}

static int getClientCPLArrayOutPosition ( char* clientCode ) {
  int position;
  position = (int) clientCode[0];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; clientCode[0] = 'A' + position; }
  else { position = -1; }
  return position;
}

static int getClientCPLArrayInPosition ( char* clientCode ) {
  int position;
  position = (int) clientCode[1];
  if ( position >= 65 && position <= 90 ) { position -= 65; } 
  else if ( position >= 97 && position <= 122 ) { position -= 97; clientCode[1] = 'A' + position; }
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

/* QUERIE 10 AUXILIAR METHOD */
static int thisClientBoughtEveryMonth ( ClientProductLinker clientPrLinker , char* clientCode ){
  int inPosition, outPosition, month, flagJumpOf;
  char* pos;
  ClientCPL searchResult;
  ClientCPL cplClient;
  searchResult = NULL;
  /* limpar \n indesejados */
  if ((pos=strchr(clientCode, '\n')) != NULL){
    *pos = '\0';
  }
  cplClient = newClientCPL ( clientCode );
  month = 0;
  flagJumpOf = 0;
  outPosition = getClientCPLArrayOutPosition( clientCode );
  inPosition = getClientCPLArrayInPosition ( clientCode );
  for ( ; month < 12 ; month ++ ){
    searchResult = (ClientCPL) searchBst ( clientPrLinker->lettersArray[month][outPosition][inPosition], cplClient );
    if ( searchResult == NULL ){
      /* jump of cycle */
      month = 12;
      flagJumpOf = 1;
    }
  }
  if ( flagJumpOf == 1 ) return 0;
  else return 1;
}

/* QUERIE 10 */
struct list* getClientsWhoBoughtEveryMonth__LL_STRINGS ( ClientProductLinker clientPrLinker , ClientCatalog clCat ){
  int out , in, month, sizeString;
  struct list* clientLL;
  struct list* returnLL;
  char* clientCode;
  char* toReturnString;
  clientCode = NULL;
  in = 0;
  out = 0;
  month = 0;
  sizeString = 0;
  clientLL = initLL ( );
  newLL ( clientLL , sizeof ( char* ) , &myFreeCharCPL1 );
  clientLL = getFullClients__LL_strings ( clCat , clientLL );
  returnLL = initLL ();
  newLL ( returnLL , sizeof ( char* ) , &myFreeCharCPL1 );
  for ( ; sizeLL ( clientLL ) > 0 ;  ){
    clientCode = (char*) headLL (clientLL);
    if ( thisClientBoughtEveryMonth ( clientPrLinker , clientCode ) ){
      sizeString = strlen ( clientCode );
      toReturnString = ( char* ) malloc ( ( sizeString +1 ) * sizeof ( char ) );
      strcat ( toReturnString , clientCode);
      strcat ( toReturnString , "\n");
      appendLL ( returnLL , toReturnString );
    }
  }
  return returnLL;
}

/* QUERIE 11 */
int getCPLinkerMonthSize ( ClientProductLinker clientPrLinker , int month ) {
  int out , in, returningValue ;
  in = 0;
  out = 0;
  returningValue = 0;
  for( ; out<26; out++){
    in = 0;
    for ( ; in<26; in++ ){
      returningValue += BSTreeSize ( clientPrLinker->lettersArray[month-1][out][in] ) ;
    }
  }
  return returningValue;
}

/* QUERIE 13 */
struct list* getClientTopNMostBoughtProducts__LL_STRINGS ( ClientProductLinker clientPrLinker , char* clientCode, int nMost ){
  List cplLL;
  List stringsLL;
  int inPosition , outPosition , month;

  ClientCPL searchResult;
  ClientCPL cplClient;
  searchResult = NULL;
  cplClient = newClientCPL ( clientCode );

  outPosition = getClientCPLArrayOutPosition( clientCode );
  inPosition = getClientCPLArrayInPosition ( clientCode );
  cplLL = initLL();
  month = 0;
  newLL ( cplLL , sizeof ( ProductSales ) , &deleteProductSales );
  for ( ; month < 12; month++ ){
    searchResult = (ClientCPL) searchBst ( clientPrLinker->lettersArray[month][outPosition][inPosition], cplClient );
    if ( searchResult != NULL ){
      cplLL = BSTreeToLLWithMergeRepeated ( getClientCPLBST ( searchResult ) , cplLL , &equalsProductSales , &mergeProductSales );
    }
  }

  cplLL = reorderLL ( cplLL , &productSalesUnitComparator , sizeof ( ProductSales ) , &deleteProductSales );
  cplLL = limitLL ( cplLL , nMost );

  stringsLL = convertLLtoStringer ( cplLL , &toStringProductSales );
  return stringsLL;
}

/* QUERIE 14 AUXILIAR METHOD */
static int thisClientHasNeverBought ( ClientProductLinker clientPrLinker , char* clientCode ){
  int inPosition, outPosition, month, flagJumpOf;
  ClientCPL searchResult;
  ClientCPL cplClient;
  searchResult = NULL;
  cplClient = newClientCPL ( clientCode );
  month = 0;
  flagJumpOf = 0;
  outPosition = getClientCPLArrayOutPosition( clientCode );
  inPosition = getClientCPLArrayInPosition ( clientCode );
  for ( ; month < 12 ; month ++ ){
    searchResult = (ClientCPL) searchBst ( clientPrLinker->lettersArray[month][outPosition][inPosition], cplClient );
    if ( searchResult != NULL ){
      /* jump of cycle */
      month = 12;
      flagJumpOf = 1;
    }
  }
  if ( flagJumpOf == 1 ) return 0;
  else return 1;
}

/* QUERIE 14.1 */
struct list* getClientsWhoNeverBoughtProducts__LL_STRINGS ( ClientProductLinker clientPrLinker , ClientCatalog clCat ){
  int out , in, month, sizeString;
  struct list* clientLL;
  struct list* returnLL;
  char* clientCode;
  char* toReturnString;
  char* pos;
  clientCode = NULL;
  in = 0;
  out = 0;
  month = 0;
  sizeString = 0;
  clientLL = initLL ( );
  newLL ( clientLL , sizeof ( char* ) , &myFreeCharCPL1 );
  clientLL = getFullClients__LL_strings ( clCat , clientLL );
  returnLL = initLL ();
  newLL ( returnLL , sizeof ( char* ) , &myFreeCharCPL1 );
  for ( ; sizeLL ( clientLL ) > 0 ;  ){
    clientCode = (char*) headLL (clientLL);
    /* limpar \n indesejados */
    if ((pos=strchr(clientCode, '\n')) != NULL){
      *pos = '\0';
    }
    if ( thisClientHasNeverBought ( clientPrLinker , clientCode ) ){
      sizeString = strlen ( clientCode );
      toReturnString = ( char* ) malloc ( ( sizeString +1 ) * sizeof ( char ) );
      strcat ( toReturnString , clientCode);
      strcat ( toReturnString , "\n\0");
      appendLL ( returnLL , toReturnString );
    }
  }
  return returnLL;
}

int getTotalClientsNumberWhoNeverBoughtProducts ( ClientProductLinker clientPrLinker , ClientCatalog clCat ){
  struct list* returnLL;
  returnLL = getClientsWhoNeverBoughtProducts__LL_STRINGS ( clientPrLinker , clCat );
  return sizeLL ( returnLL );
}
