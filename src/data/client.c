#include <stdlib.h>
#include <string.h>
#include "client.h"

struct client {

  char firstLetter;
  char secondLetter;
  char numbers[3];

};

Client newClient ( void ){
  Client clientNew = ( Client ) malloc ( sizeof ( struct client ));
  memset ( (clientNew), '\0', ( sizeof ( struct client)) );
  return clientNew;
}

void setClient ( Client clientToSet, char fstLetter, char sndLetter, char setNumbers[3] ){
  clientToSet->firstLetter=fstLetter;
  clientToSet->secondLetter=sndLetter;
  strcpy ( clientToSet->numbers , setNumbers );
}

char getFirstLetter ( Client  getClient ) { 
  return getClient->firstLetter;
}

char getSecondLetter ( Client getClient ) {
  return getClient->secondLetter;
}

char* getNumbers ( Client getClient ) {
  return getClient->numbers;
}

int equals (Client isEqual1, Client isEqual2 ){
  return ( isEqual1->firstLetter==isEqual2->firstLetter) & (isEqual1->secondLetter==isEqual2->secondLetter) & ( strcmp (isEqual1->numbers , isEqual2->numbers));
}

