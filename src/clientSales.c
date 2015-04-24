#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include <stdio.h>
#include "clientSales.h"

struct clientSales {
  char* clientCode;
  int unitsSold;
};

ClientSales newClientSales ( char* ClientCode ){
  int stringSize = 0;

  ClientSales clientSalesNew = ( ClientSales ) malloc ( sizeof ( struct clientSales ));
  memset ( (clientSalesNew), '\0', ( sizeof ( struct clientSales ) ) );

  stringSize = strlen ( ClientCode );
  clientSalesNew->clientCode  = ( char* ) malloc ( ( stringSize +1 ) * sizeof ( char ) );
  strcpy ( clientSalesNew->clientCode , ClientCode );

  clientSalesNew->unitsSold = 0;
  return clientSalesNew;
}

int getClientSalesUnitsSold ( ClientSales c1 ){
  assert ( c1 != NULL );
  return c1->unitsSold;
}

ClientSales addUnitClientSales ( ClientSales c1 , int addUnit ){
  assert ( c1 != NULL );
  c1->unitsSold += addUnit;
  return c1;
}

int equalsClientSales ( void* isEqual1, void* isEqual2 ){
  ClientSales c1, c2;
  int returningValue = -1;
  assert ( isEqual1 != NULL );
  assert ( isEqual2 != NULL );
  c1 = ( ClientSales ) isEqual1;
  c2 = ( ClientSales ) isEqual2;
  returningValue = strcmp ( c1->clientCode , c2->clientCode );
  return returningValue;
}

void deleteClientSales ( void* delete1 ){
  ClientSales d1;
  assert ( delete1 !=  NULL );
  d1 = ( ClientSales ) delete1;
  free ( d1 );
}

void* toStringClientSales ( void* toString ){
  ClientSales c1;
  int length, lengthUnitsSold;
  char buffer1[20];
  char* newString;
  assert( toString != NULL );
  c1 = ( ClientSales ) toString;
  length = strlen ( c1->clientCode );
  sprintf(buffer1, "%d", c1->unitsSold);
  lengthUnitsSold = strlen ( buffer1 );
  length += lengthUnitsSold;
  newString = ( char* ) malloc ( ( length +1+16+1 ) * sizeof ( char ));
  strcpy ( newString , c1->clientCode );
  strcat ( newString , "\tUNITS SOLD: ");
  strcat ( newString , buffer1 );
  strcat ( newString , "\n" );
  return newString;
}
