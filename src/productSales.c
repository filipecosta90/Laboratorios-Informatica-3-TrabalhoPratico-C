#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include <stdio.h>
#include "productSales.h"


struct productSales {
  char* productCode;
  int unitsSold;
};

ProductSales newProductSales ( char* ProductCode ){
  int stringSize = 0;

  ProductSales productSalesNew = ( ProductSales ) malloc ( sizeof ( struct productSales ));
  memset ( (productSalesNew), '\0', ( sizeof ( struct productSales ) ) );

  stringSize = strlen ( ProductCode );
  productSalesNew->productCode  = ( char* ) malloc ( ( stringSize +1 ) * sizeof ( char ) );
  strcpy ( productSalesNew->productCode , ProductCode );

  productSalesNew->unitsSold = 0;
  return productSalesNew;
}

int getProductSalesUnitsSold ( ProductSales p1 ){
  assert ( p1 != NULL );
  return p1->unitsSold;
}

ProductSales addUnitProductSales ( ProductSales p1 , int addUnit ){
  assert ( p1 != NULL );
  p1->unitsSold += addUnit;
  return p1;
}

int equalsProductSales ( void* isEqual1, void* isEqual2 ){
  ProductSales p1, p2;
  int returningValue = -1;
  assert ( isEqual1 != NULL );
  assert ( isEqual2 != NULL );
  p1 = ( ProductSales ) isEqual1;
  p2 = ( ProductSales ) isEqual2;
  returningValue = strcmp ( p1->productCode , p2->productCode );
  return returningValue;
}

void deleteProductSales ( void* delete1 ){
  ProductSales d1;
  assert ( delete1 !=  NULL );
  d1 = ( ProductSales ) delete1;
  free ( d1 );
}

void* toStringProductSales ( void* toString ){
  ProductSales p1;
  int length, lengthUnitsSold;
  char buffer1[20];
  char* newString;
  assert( toString != NULL );
  p1 = ( ProductSales ) toString;
  length = strlen ( p1->productCode );
  sprintf(buffer1, "%d", p1->unitsSold);
  lengthUnitsSold = strlen ( buffer1 );
  length += lengthUnitsSold;
  newString = ( char* ) malloc ( ( length +1+16+1 ) * sizeof ( char ));
  strcpy ( newString , p1->productCode );
  strcat ( newString , "\tUNITS SOLD: ");
  strcat ( newString , buffer1 );
  strcat ( newString , "\n" );
  return newString;
}
