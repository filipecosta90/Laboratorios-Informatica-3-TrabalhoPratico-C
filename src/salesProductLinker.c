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
  struct bsTree* lettersArray[26];
};

struct salesProductLinker* newSalesProductLinker ( ) {
  struct salesProductLinker* newSPL = ( struct salesProductLinker* ) malloc ( sizeof (struct salesProductLinker ) );
  int i = 0;
  for( ; i<26; i++){
    newSPL->lettersArray[i] = newBSTree ( &productSPLEquals );
  }
  return newSPL;
}

static int getProductSPLArrayPosition ( char* productCode ) {
  int position;
  position = (int) productCode[0];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

void addSalesLineToSPL ( struct salesProductLinker* salesPrLinker , char* productCode, char* clientCode , char salesMode , int unitsSold , float sellingPrice ) {
  int position;
  ProductSPL searchResult = NULL;
  ProductSPL splProd;
  position = getProductSPLArrayPosition( productCode );
  splProd = newProductSPL ( productCode );
  searchResult = (ProductSPL) searchBst ( salesPrLinker->lettersArray[position], splProd );
  if ( searchResult == NULL ){
    splProd = addSaleSPL ( splProd , clientCode , salesMode , unitsSold , sellingPrice );
    insertBst ( salesPrLinker->lettersArray[position] , splProd );
  }
  else {
    searchResult = addSaleSPL ( searchResult , clientCode , salesMode , unitsSold , sellingPrice );
  }
}

List getClientsWhoBoughtProduct__LL ( struct salesProductLinker* salesPrLinker , char* productCode ){
  List returnLL;
  int position;
  ProductSPL searchResult;
  ProductSPL splProd;
  returnLL = ( List ) malloc ( sizeof ( List ) );
  position = getProductSPLArrayPosition( productCode );
  splProd = newProductSPL ( productCode );
  searchResult = (ProductSPL) searchBst ( salesPrLinker->lettersArray[position], splProd );
  returnLL = productSPLGetNormalClients__LL ( searchResult );
  return returnLL;
}

List getTopNMostSoldProducts__LL ( struct salesProductLinker* salesPrLinker , int nMost , int* totalClients , int* numberUnitsSold ){

}

int getNumberOfIdleProducts ( struct salesProductLinker* salesPrLiner ){
  int idleCount;
  idleCount = 0;

  return idleCount;
}
