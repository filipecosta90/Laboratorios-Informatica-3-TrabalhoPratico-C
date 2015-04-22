/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include "genLinkedList.h"
#include "avlTree.h"
#include "productCatalog.h"

#include <assert.h>
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
  else if ( position >= 97 && position <= 122 ) { position -= 97; productCode[0] = 'A' + position; }
  else { position = -1; }
  return position;
}

static int getProductArrayInPosition ( char* productCode ) {
  int position;
  position = (int) productCode[1];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; productCode[1] = 'A' + position;}
  else { position = -1; }
  return position;
}

void addProductToCatalog ( struct productCatalog* prCat, char* productCode ) {
  int outPosition, inPosition;
  outPosition = getProductArrayOutPosition( productCode );
  inPosition = getProductArrayInPosition( productCode );
  avlInsert ( prCat->lettersArray[outPosition][inPosition] , productCode );
}

int getTotalProductsByLetter ( struct productCatalog* prCat, char productInitial ) {
  int outPosition, inPosition, totalProducts;
  outPosition = getProductArrayOutPosition( &productInitial );
  inPosition = 0;
  totalProducts = 0;
  for ( ; inPosition < 26 ; inPosition++){
    totalProducts += avlSize ( prCat->lettersArray[outPosition][inPosition] );
  }
  return totalProducts;
}

int getProductCatalogSize ( struct productCatalog* prCat ) {
  int outPosition, inPosition, totalProducts;
  outPosition = 0;
  inPosition = 0;
  totalProducts = 0;
  for( ; outPosition<26; outPosition++){
    inPosition = 0;
    for ( ; inPosition < 26; inPosition++ ){
      totalProducts += avlSize ( prCat->lettersArray[outPosition][inPosition] );
    }
  }
  return totalProducts;
}

int containsProductCode ( struct productCatalog* prCat, char* productCode ){
  int outPosition, inPosition;
  outPosition = getProductArrayOutPosition ( productCode );
  inPosition = getProductArrayInPosition ( productCode );
  return avlContains ( prCat->lettersArray[outPosition][inPosition] , productCode );
}

void myFreeCharprCat ( void* myfree ){
  char* stringF;
  stringF = NULL;
  assert ( myfree != NULL );
  stringF = ( char* ) myfree;
  free ( stringF );
}

/* QUERIE 2 */
struct list* getProductsByLetter__LL_strings ( struct productCatalog* prCat , char productInitial ){
  int outPosition, inPosition;
  struct list* returningLL;
  returningLL = initLL ();
  newLL ( returningLL , sizeof ( char* ) , &myFreeCharprCat );
  inPosition = 0;
  outPosition = getProductArrayOutPosition ( &productInitial );
  for ( ; inPosition < 26 ; inPosition++){
    returningLL = avlToLL ( prCat->lettersArray[outPosition][inPosition] , returningLL  );
  }
  return returningLL;
}

/* QUERIE 4 AUXILIAR METHOD */
struct list* getFullProducts__LL_strings ( struct productCatalog* prCat , struct list* returningLL ){
  int out , in;
  out = 0;
  in = 0;
  for ( ; out < 26 ; out++ ){
    in = 0;
    for( ; in<26; in++ ){
      returningLL = avlToLL ( prCat->lettersArray[out][in] , returningLL  );
    }
  }
  return returningLL;
}
