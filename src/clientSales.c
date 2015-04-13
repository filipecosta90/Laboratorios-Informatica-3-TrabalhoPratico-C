#include <stdlib.h>
#include <string.h>
#include "assert.h"

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
  assert ( isEqual1 != NULL && isEqual2 != NULL );
  c1 = ( ClientSales ) isEqual1;
  c2 = ( ClientSales ) isEqual2;
  returningValue = strcmp ( c1->clientCode , c2->clientCode );
  return returningValue;
}

