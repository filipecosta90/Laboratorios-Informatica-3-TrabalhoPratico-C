/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include "genLinkedList.h"
#include "avlTree.h"
#include "binarySearchTree.h"
#include "clientProductLinker.h"
#include "clientCPL.h"
#include "clientSales.h"

#include <stdio.h>
#include <stdlib.h>

struct clientProductLinker {
  struct bsTree* lettersArray[12][26][26];
};

struct clientProductLinker* newClientProductLinker ( ) {
  struct clientProductLinker* newCPL = ( struct clientProductLinker* ) malloc ( sizeof (struct clientProductLinker ) );
  int out , in, month;
  in = 0;
  out = 0;
  month = 0;
  for ( ; month < 12 ; month ++ ){
    out = 0;
  for( ; out<26; out++){
    in = 0;
    for ( ; in<26; in++ ){
      newCPL->lettersArray[month][out][in] = newBSTree ( &clientCPLEquals );
    }
  }
  }
  return newCPL;
}

static int getClientCPLArrayOutPosition ( char* clientCode ) {
  int position;
  position = (int) clientCode[0];
  if ( position >= 65 && position <= 90 ) { position -= 65; }
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

static int getClientCPLArrayInPosition ( char* clientCode ) {
  int position;
  position = (int) clientCode[1];
  if ( position >= 65 && position <= 90 ) { position -= 65; } 
  else if ( position >= 97 && position <= 122 ) { position -= 97; }
  else { position = -1; }
  return position;
}

void addSalesLineToCPL ( struct clientProductLinker* clientPrLinker , char* productCode, char* clientCode , int unitsSold , int month ) {
  int outPosition, inPosition;
  ClientCPL searchResult = NULL;
  ClientCPL cplClient;
  outPosition = getClientCPLArrayOutPosition( clientCode );
  inPosition = getClientCPLArrayInPosition ( clientCode );
  cplClient = newClientCPL ( clientCode );
  searchResult = (ClientCPL) searchBst ( clientPrLinker->lettersArray[month-1][outPosition][inPosition], cplClient );
  if ( searchResult == NULL ){
    cplClient = addProductCPL ( cplClient , productCode , unitsSold );
    insertBst ( clientPrLinker->lettersArray[month-1][outPosition][inPosition] , cplClient );
  }
  else {
    searchResult = addProductCPL ( searchResult , productCode , unitsSold );
  }
}
