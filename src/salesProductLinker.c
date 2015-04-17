/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include "genLinkedList.h"
#include "avlTree.h"
#include "binarySearchTree.h"
#include "salesProductLinker.h"
#include "productSPL.h"
#include "clientSales.h"

#include <stdio.h>
#include <stdlib.h>

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

void addSalesLineToSPL ( struct salesProductLinker* salesPrLinker , char* productCode, char* clientCode , char salesMode , int unitsSold , float sellingPrice ) {
  int outPosition, inPosition;
  ProductSPL searchResult = NULL;
  ProductSPL splProd;
  outPosition = getProductSPLArrayOutPosition( productCode );
  inPosition = getProductSPLArrayInPosition ( productCode );
  splProd = newProductSPL ( productCode );
  searchResult = (ProductSPL) searchBst ( salesPrLinker->lettersArray[outPosition][inPosition], splProd );
  if ( searchResult == NULL ){
    splProd = addSaleSPL ( splProd , clientCode , salesMode , unitsSold , sellingPrice );
    insertBst ( salesPrLinker->lettersArray[outPosition][inPosition] , splProd );
  }
  else {
    searchResult = addSaleSPL ( searchResult , clientCode , salesMode , unitsSold , sellingPrice );
  }
}

List getNormalClientsWhoBoughtProduct__LL_STRINGS ( struct salesProductLinker* salesPrLinker , char* productCode ){
  List returnLL;
  int inPosition, outPosition;
  ProductSPL searchResult;
  ProductSPL splProd;
  returnLL = ( List ) malloc ( sizeof ( List ) );
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
  returnLL = ( List ) malloc ( sizeof ( List ) );
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

