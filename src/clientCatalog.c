#include "clientCatalog.h"
#include "avlTree.h"
#include <stdlib.h>
#include <stdio.h>

struct clientCatalog {
  AvlTree lettersArray[26];
};

struct clientCatalog* newClientCatalog ( void ){
  struct clientCatalog* newClCat = ( struct clientCatalog* ) malloc ( sizeof (struct clientCatalog) );
  return newClCat;
}

static int getClientArrayPosition ( char* clientCode ) {
  int position;
  position = (int) clientCode[0];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

void addClientToCatalog ( struct clientCatalog* clCat, char* clientCode ) {
  int position; 
  position = getClientArrayPosition( clientCode );
  clCat->lettersArray[position] = insertInAvlTree ( clCat->lettersArray[position] , clientCode );
}

int getTotalClientsByLetter ( struct clientCatalog* clCat, char clientInitial ) {
  int position, totalClients;
  position = getClientArrayPosition( &clientInitial );
  totalClients = getSizeOfAvlTree ( clCat->lettersArray[position] );
  return totalClients;
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

