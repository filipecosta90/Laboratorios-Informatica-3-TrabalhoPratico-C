/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include "genLinkedList.h"
#include "avlTree.h"
#include "clientCatalog.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

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
  else if ( position >= 97 && position <= 122 ) { position -= 97; clientCode[0] = 'A' + position; }
  else { position = -1; }
  return position;
}

static int getClientArrayInPosition ( char* clientCode ) {
  int position;
  position = (int) clientCode[1];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; clientCode[0] = 'A' + position; }
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

void myFreeCharclCat ( void* myfree ){
  char* stringF;
  stringF = NULL;
  assert ( myfree != NULL );
  stringF = ( char* ) myfree;
  free ( stringF );
}

int reorderStringclCat ( void* isEqual1, void* isEqual2 ){
  char* p1, *p2;
  assert ( isEqual1 != NULL );
  assert ( isEqual2 != NULL );
  p1 = ( char* ) isEqual1;
  p2 = ( char* ) isEqual2;
  return strcmp ( p2 , p1 );
}

/* QUERIE 6 */
struct list* getClientsByLetter__LL_strings ( struct clientCatalog* clCat , char clientInitial ){
  int outPosition, inPosition;
  struct list* returningLL;
  returningLL = initLL ();
  newLL ( returningLL , sizeof ( char* ) , &myFreeCharclCat );
  inPosition = 0;
  outPosition = getClientArrayOutPosition ( &clientInitial );
  for ( ; inPosition < 26 ; inPosition++){
    returningLL = avlToLL ( clCat->lettersArray[outPosition][inPosition] , returningLL  );
  }
  returningLL = reorderLL ( returningLL , &reorderStringclCat , sizeof ( char )  , &myFreeCharclCat );
  return returningLL;
}

/* QUERIE 10 AUXILIAR METHOD */
struct list* getFullClients__LL_strings ( struct clientCatalog* clCat , struct list* returningLL ){
  int out , in;
  out = 0;
  in = 0;
  for ( ; out < 26 ; out++ ){
    in = 0;
    for( ; in<26; in++ ){
      returningLL = avlToLL ( clCat->lettersArray[out][in] , returningLL  );
    }
  }
  return returningLL;
}
