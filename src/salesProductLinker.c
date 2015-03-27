/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include "salesProductLinker.h"
#include "genLinkedList.h"
#include "avlTree.h"
#include "binarySearchTree.h"
#include <stdlib.h>

struct salesProductLinker {
  struct bstNode* lettersArray[26];
  int ( *splComparator ) ( void* , void* );
};

struct salesProductLinker* newSalesProductLinker ( int ( *cmp) ( void* , void* ) ){
  struct salesProductLinker* newSPL = ( struct salesProductLinker* ) malloc ( sizeof (struct salesProductLinker ) );
  int i = 0;
  newSPL->splComparator = cmp;
  for( ; i<26; i++){
    newSPL->lettersArray[i] = newNodeBst( NULL );
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
  struct bstNode** searchResult = NULL;
  struct ProductSPL splProd;
  position = getProductSPLArrayPosition( productCode );
  splProd = newProductSPL ( productCode );
  searchResult = searchBst ( salesPrLinker->lettersArray[position] , salesPrLinker->splComparator , splProd );
  if ( *searchResult == NULL ){
    setProductSPL ( splProd , clientCode , salesMode , unitsSold , sellingPrice );
    insertBst ( salesPrLinker->lettersArray[position] , salesPrLinker->splComparator , splProd );
  }
  else {
    splProd = ( ProductSPL ) getNodeBstData ( searchResult );
    increaseProductSPL ( splProd , clientCode , salesMode , unitsSold , sellingPrice );
  }
}

int getClientsWhoBoughtProduct__LL ( struct salesProductLinker* salesPrLinker , char* prCode , struct list* returnLL ){

}

int getTopNMostSoldProducts__LL ( struct salesProductLinker* salesPrLinker , int nMost , struct List returnLL , int* totalClients , int* numberUnitsSold ){

}

int getNumberOfIdleProducts ( struct salesProductLinker* salesPrLiner ){

}
