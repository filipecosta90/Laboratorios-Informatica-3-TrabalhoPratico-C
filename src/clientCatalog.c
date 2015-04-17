#include "clientCatalog.h"
#include "avlTree.h"
#include <stdlib.h>
#include <stdio.h>

struct clientCatalog {
  AvlTree lettersArray[26][26];
};

struct clientCatalog* newClientCatalog ( void ){
  struct clientCatalog* newClCat = ( struct clientCatalog* ) malloc ( sizeof (struct clientCatalog) );
  int in , out;
  in = 0;
  out = 0;
  for( ; out<26; out++){
    in = 0;
    for ( ; in < 26; in++ ){
      newClCat->lettersArray[out][in] = createTree();
    }
  }
  return newClCat;
}

static int getClientArrayOutPosition ( char* clientCode ) {
  int position;
  position = (int) clientCode[0];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

static int getClientArrayInPosition ( char* clientCode ) {
  int position;
  position = (int) clientCode[1];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

void addClientToCatalog ( struct clientCatalog* clCat, char* clientCode ) {
  int outPosition, inPosition; 
  outPosition = getClientArrayOutPosition( clientCode );
  inPosition = getClientArrayInPosition ( clientCode );
  avlInsert ( clCat->lettersArray[outPosition][inPosition] , clientCode );
}

int getTotalClientsByLetter ( struct clientCatalog* clCat, char clientInitial ) {
  int outPosition, inPosition, totalClients;
  outPosition = getClientArrayOutPosition( &clientInitial );
  inPosition = 0;
  totalClients = 0;
  for ( ; inPosition < 26 ; inPosition++){
    totalClients += avlSize ( clCat->lettersArray[outPosition][inPosition] );
  }
  return totalClients;
}

int containsClientCode ( struct clientCatalog* clCat, char* clientCode ){
  int outPosition, inPosition;
  outPosition = getClientArrayOutPosition ( clientCode );
  inPosition = getClientArrayInPosition ( clientCode );
  return avlContains ( clCat->lettersArray[outPosition][inPosition] , clientCode );
}


void deleteClientCatalog ( struct clientCatalog* clCat ) {
  int out , in;
  out = 0;
  in = 0;
  for ( ; out < 26 ; out++ ){
    in = 0;
    for( ; in<26; in++ ){
      avlFree ( clCat->lettersArray[out][in]);
    }
  }
  free (clCat);
}

