/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include "genLinkedList.h"
#include "avlTree.h"
#include "binarySearchTree.h"
#include "productCatalog.h"
#include "productSPL.h"
#include "clientSales.h"
#include "salesProductLinker.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct salesProductLinker {
  struct bsTree* lettersArray[26][26];
};

struct salesProductLinker* newSalesProductLinker ( ) {
  struct salesProductLinker* newSPL = ( struct salesProductLinker* ) malloc ( sizeof (struct salesProductLinker ) );
  int out , in;
  in = 0;
  out = 0;
  for( ; out<26; out++){
    in = 0;
    for ( ; in<26; in++ ){
      newSPL->lettersArray[out][in] = newBSTree ( &productSPLEquals );
    }
  }
  return newSPL;
}

static int getProductSPLArrayOutPosition ( char* productCode ) {
  int position;
  position = (int) productCode[0];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

static int getProductSPLArrayInPosition ( char* productCode ) {
  int position;
  position = (int) productCode[1];
  if ( position >= 65 && position <= 90 ) { position -= 65; } 
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

void addSalesLineToSPL ( struct salesProductLinker* salesPrLinker , char* productCode, char* clientCode , char salesMode , int unitsSold , float sellingPrice , int month ) {
  int outPosition, inPosition;
  ProductSPL searchResult = NULL;
  ProductSPL splProd;
  outPosition = getProductSPLArrayOutPosition( productCode );
  inPosition = getProductSPLArrayInPosition ( productCode );
  splProd = newProductSPL ( productCode );
  searchResult = (ProductSPL) searchBst ( salesPrLinker->lettersArray[outPosition][inPosition], splProd );
  if ( searchResult == NULL ){
    splProd = addSaleSPL ( splProd , clientCode , salesMode , unitsSold , sellingPrice , month );
    insertBst ( salesPrLinker->lettersArray[outPosition][inPosition] , splProd );
  }
  else {
    searchResult = addSaleSPL ( searchResult , clientCode , salesMode , unitsSold , sellingPrice, month );
  }
}

List getNormalClientsWhoBoughtProduct__LL_STRINGS ( struct salesProductLinker* salesPrLinker , char* productCode ){
  List returnLL;
  int inPosition, outPosition;
  ProductSPL searchResult;
  ProductSPL splProd;
  returnLL = initLL ();
  outPosition = getProductSPLArrayOutPosition( productCode );
  inPosition = getProductSPLArrayInPosition ( productCode );
  splProd = newProductSPL ( productCode );
  searchResult = (ProductSPL) searchBst ( salesPrLinker->lettersArray[outPosition][inPosition], splProd );
  returnLL = productSPLGetNormalClients__LL_STRINGS ( searchResult );
  return returnLL;
}

List getPromotionClientsWhoBoughtProduct__LL_STRINGS ( struct salesProductLinker* salesPrLinker , char* productCode ){
  List returnLL;
  int outPosition, inPosition;
  ProductSPL searchResult;
  ProductSPL splProd;
  returnLL = initLL ();
  outPosition = getProductSPLArrayOutPosition( productCode );
  inPosition = getProductSPLArrayInPosition( productCode );
  splProd = newProductSPL ( productCode );
  searchResult = (ProductSPL) searchBst ( salesPrLinker->lettersArray[outPosition][inPosition], splProd );
  returnLL = productSPLGetPromotionClients__LL_STRINGS ( searchResult );
  return returnLL;
}

List getTopNMostSoldProducts__LL_STRINGS ( struct salesProductLinker* salesPrLinker , int nMost ){
  List splLL;
  List stringsLL; 
  int in , out;
  in = 0;
  out = 0;
  splLL = initLL();
  newLL ( splLL , sizeof ( ProductSPL ) , &destroyProductSPL );
  for( ; out <26; out++){
    in = 0;
    for ( ; in < 26; in++ ){
      splLL = BSTreeToOrderedLLWithLimit( salesPrLinker->lettersArray[out][in] , splLL , &productSPLUnitComparator , nMost );
    }
  }
  stringsLL = convertLLtoStringer ( splLL , &productSPLToString );
  return stringsLL;
}

int getGlobalNumberProducts ( struct salesProductLinker* salesPrLinker ){
  int globalCount;
  int out , in;
  globalCount = 0;
  in = 0;
  out = 0;
  for( ; out<26; out++){
    in = 0;
    for ( ; in < 26; in++ ){
      globalCount += BSTreeSize ( salesPrLinker->lettersArray[out][in]);
    }
  }
  return globalCount;
}

int getPromotionClientsNumberWhoBoughtProductInMonth ( struct salesProductLinker* salesPrLinker , char* productCode , int month ){
  int outPosition, inPosition , promotionClientsNumber;
  ProductSPL searchResult;
  ProductSPL splProd;
  outPosition = getProductSPLArrayOutPosition( productCode );
  inPosition = getProductSPLArrayInPosition( productCode );
  splProd = newProductSPL ( productCode );
  searchResult = (ProductSPL) searchBst ( salesPrLinker->lettersArray[outPosition][inPosition], splProd );
  promotionClientsNumber = productSPLGetPromotionClientsNumberInMonth ( searchResult , month );
  return promotionClientsNumber;
}

int getNormalClientsNumberWhoBoughtProductInMonth ( struct salesProductLinker* salesPrLinker , char* productCode , int month ){
  int outPosition, inPosition , normalClientsNumber;
  ProductSPL searchResult;
  ProductSPL splProd;
  outPosition = getProductSPLArrayOutPosition( productCode );
  inPosition = getProductSPLArrayInPosition( productCode );
  splProd = newProductSPL ( productCode );
  searchResult = (ProductSPL) searchBst ( salesPrLinker->lettersArray[outPosition][inPosition], splProd );
  normalClientsNumber = productSPLGetNormalClientsNumberInMonth ( searchResult , month );
  return normalClientsNumber;
}

float getTotalBilledByProductInMonth ( struct salesProductLinker* salesPrLinker , char* productCode , int month ){
  int outPosition, inPosition;
  float billedValue;
  ProductSPL searchResult;
  ProductSPL splProd;
  outPosition = getProductSPLArrayOutPosition( productCode );
  inPosition = getProductSPLArrayInPosition( productCode );
  splProd = newProductSPL ( productCode );
  searchResult = (ProductSPL) searchBst ( salesPrLinker->lettersArray[outPosition][inPosition], splProd );
  billedValue = productSPLGetTotalBilledInMonth ( searchResult , month );
  return billedValue;
}

void myFreeCharSPL1 ( void* myfree ){
  char* stringF;
  stringF = NULL;
  assert ( myfree != NULL );
  stringF = ( char* ) myfree;
  free ( stringF );
}

/* QUERIE 4 AUXILIAR METHOD */
static int thisProductWasNeverBought ( SalesProductLinker salesPrLinker , char* productCode ){
  int inPosition, outPosition, month, flagJumpOf;
  ProductSPL searchResult;
  ProductSPL splProd;
  outPosition = getProductSPLArrayOutPosition( productCode );
  inPosition = getProductSPLArrayInPosition( productCode );
  splProd = newProductSPL ( productCode );
  month = 0;
  flagJumpOf = 0;
  searchResult = NULL;
  for ( ; month < 12 ; month ++ ){
    searchResult = (ProductSPL) searchBst ( salesPrLinker->lettersArray[outPosition][inPosition], splProd );
    if ( searchResult != NULL ){
      /* jump of cycle */
      month = 12;
      flagJumpOf = 1;
    }
  }
  if ( flagJumpOf == 1 ) return 0;
  else return 1;
}

/* QUERIE 4 */
struct list* getProductsWhoWereNeverBought__LL_STRINGS ( SalesProductLinker salesPrLinker , ProductCatalog prCat ){
  int out , in, month, sizeString;
  struct list* productLL;
  struct list* returnLL;
  char* productCode;
  char* toReturnString;
  productCode = NULL;
  in = 0;
  out = 0;
  month = 0;
  sizeString = 0;
  productLL = initLL ( );
  newLL ( productLL , sizeof ( char* ) , &myFreeCharSPL1 );
  productLL = getFullProducts__LL_strings ( prCat , productLL );
  returnLL = initLL ();
  newLL ( returnLL , sizeof ( char* ) , &myFreeCharSPL1 );
  for ( ; sizeLL ( productLL ) > 0 ;  ){
    productCode = (char*) headLL (productLL);
    if ( thisProductWasNeverBought ( salesPrLinker , productCode ) ){
      sizeString = strlen ( productCode );
      toReturnString = ( char* ) malloc ( ( sizeString +1 ) * sizeof ( char ) );
      strcat ( toReturnString , productCode);
      strcat ( toReturnString , "\n\0");
      appendLL ( returnLL , toReturnString );
    }
  }
  return returnLL;
}
