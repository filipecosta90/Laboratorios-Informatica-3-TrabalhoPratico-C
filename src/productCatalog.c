#include "productCatalog.h"
#include "avlTree.h"
#include <stdlib.h>
#include <stdio.h>

struct productCatalog {
  AvlTree lettersArray[26];
};

struct productCatalog* newProductCatalog ( void ){
  struct productCatalog* newPrCat = ( struct productCatalog* ) malloc ( sizeof (struct productCatalog) );
  return newPrCat;
}

static int getProductArrayPosition ( char* productCode ) {
  int position;
  position = (int) productCode[0];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

void addProductToCatalog ( struct productCatalog* prCat, char* productCode ) {
  int position;
  position = getProductArrayPosition( productCode );
  prCat->lettersArray[position] = insertInAvlTree ( prCat->lettersArray[position] , productCode );
}

int getTotalProductByLetter ( struct productCatalog* prCat, char productInitial ) {
  int position, totalProducts;
  position = getProductArrayPosition( &productInitial );
  totalProducts = getSizeOfAvlTree ( prCat->lettersArray[position] );
  return totalProducts;
}

/* 
   void deleteClientCatalog ( struct clientCatalog* clCat ) {
   int i = 0;
   for( ; i<26; i++){
   freeAvlTree ( clCat->lettersArray[i]);
   }
   free (clCat);
   } 
   */
