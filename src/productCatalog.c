#include "productCatalog.h"
#include "avlTree.h"
#include <stdlib.h>

struct productCatalog {
  AvlTree lettersArray[26][26];
};

struct productCatalog* newProductCatalog ( void ){
  struct productCatalog* newPrCat = ( struct productCatalog* ) malloc ( sizeof (struct productCatalog) );
  int out , in;
  out = 0;
  in = 0;
  for ( ; out < 26; out++ ){
    in = 0;
    for( ; in<26; in++){
      newPrCat->lettersArray[out][in] = createTree();
    }
  }
  return newPrCat;
}

static int getProductArrayOutPosition ( char* productCode ) {
  int position;
  position = (int) productCode[0];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

static int getProductArrayInPosition ( char* productCode ) {
  int position;
  position = (int) productCode[1];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

void addProductToCatalog ( struct productCatalog* prCat, char* productCode ) {
  int outPosition, inPosition;
  outPosition = getProductArrayOutPosition( productCode );
  inPosition = getProductArrayInPosition( productCode );
  avlInsert ( prCat->lettersArray[outPosition][inPosition] , productCode );
}

int getTotalProductByLetter ( struct productCatalog* prCat, char productInitial ) {
  int outPosition, inPosition, totalProducts;
  outPosition = getProductArrayOutPosition( &productInitial );
  inPosition = 0;
  totalProducts = 0;
  for ( ; inPosition < 26 ; inPosition++){
  totalProducts += avlSize ( prCat->lettersArray[outPosition][inPosition] );
  }
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

int containsProductCode ( struct productCatalog* prCat, char* productCode ){
  int outPosition, inPosition;
  outPosition = getProductArrayOutPosition ( productCode );
  inPosition = getProductArrayInPosition ( productCode );
  return avlContains ( prCat->lettersArray[outPosition][inPosition] , productCode );
}

