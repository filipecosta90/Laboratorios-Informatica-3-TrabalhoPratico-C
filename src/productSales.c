/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

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

int getProductSalesUnitsSold ( void* in  ){
  ProductSales p1;
  p1 = NULL;
  if ( in == NULL ){
    return ( 0 );
  }
  else {
    p1 = ( ProductSales ) in;
    return p1->unitsSold;
  }
}

ProductSales addUnitProductSales ( ProductSales p1 , int addUnit ){
  assert ( p1 != NULL );
  p1->unitsSold = p1->unitsSold + addUnit;
  return p1;
}

int equalsProductSales ( void* isEqual1, void* isEqual2 ){
  ProductSales p1, p2;
  assert ( isEqual1 != NULL );
  assert ( isEqual2 != NULL );
  p1 = ( ProductSales ) isEqual1;
  p2 = ( ProductSales ) isEqual2;
  return strcmp ( p1->productCode , p2->productCode );
}

int productSalesUnitComparator ( void* comp1 , void* comp2 ){
  ProductSales p1, p2;
  int returningValue;
  if ( comp1 == NULL || comp2 == NULL ){
    returningValue = 0;
  }
  else{
    p1 = ( ProductSales ) comp1;
    p2 = ( ProductSales ) comp2;
    returningValue = p1->unitsSold - p2->unitsSold;
    if ( returningValue == 0 ){
      returningValue = strcmp ( p2->productCode , p1->productCode );
    }
  }
  return returningValue;
}

void* mergeProductSales ( void* comp1 , void* comp2 ){
  ProductSales p1, p2;
  if ( comp1 == NULL || comp2 == NULL ){
    return NULL;
  }
  else{
    p1 = ( ProductSales ) comp1;
    p2 = ( ProductSales ) comp2;
    p1->unitsSold = p1->unitsSold + p2->unitsSold;
    return p1;
  }
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
