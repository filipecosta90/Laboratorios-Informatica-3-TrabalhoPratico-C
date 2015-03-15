#include "accounting.h"
#include "month.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct accounting {
  Month monthsArray[12];
};

void initAccounting ( struct accounting* acBook ) {
  int i = 0;
  for( ; i<12; i++){
    acBook->monthsArray[i] = newMonth();
  }
}

struct accounting* newAccounting ( void ){
  struct accounting* newAcBook = ( struct accounting* ) malloc ( sizeof (struct accounting) );
  return newAcBook;
}

void addSale ( struct accounting* acBook, int month ) {
  int position; 
  position = month-1;
  addSales( acBook->monthsArray[position] , 1 );
}

void addClient ( struct accounting* acBook, int month ) {
  int position;
  position = month-1;
  addClients( acBook->monthsArray[position], 1);
}

void addBill ( struct accounting* acBook, int month , float billedValue) {
  int position = month -1;
  addBills ( acBook->monthsArray[position], billedValue );
}

char*  getCsvMonth ( struct accounting* acBook, int month ) {
  char* lineToReturn;
  char buffer[64];
  int position, sizeToReturn;
  position = month -1;
  sprintf( buffer, "\"%d\",\"%d\",\"%d\"", month , getNumberSales ( acBook->monthsArray[position] ) , getNumberClients ( acBook->monthsArray[position] ) );
  sizeToReturn = strlen ( buffer ) + 1;
  lineToReturn = (char*) malloc ( sizeToReturn * sizeof (char) );
  strcpy( lineToReturn , buffer );
  lineToReturn[sizeToReturn-1] = '\0';
  return lineToReturn;
}

int getIntervalTotalSales ( struct accounting* acBook, int initialMonth , int finalMonth ){
  int totalSales, i;
  totalSales = 0;
  i = initialMonth -1 ;
  for ( ; i< finalMonth; i++){
    totalSales += getNumberSales ( acBook->monthsArray[ i ]);
  }
  return totalSales;
}

float getIntervalTotalBilled ( struct accounting* acBook, int initialMonth, int finalMonth ){
  float totalBilled;
  int i;
  totalBilled = 0.0;
  i = initialMonth -1;
  for ( ; i< finalMonth; i++ ){
    totalBilled += getTotalBilled ( acBook->monthsArray [ i ]);
  }
  return totalBilled;
}

void deleteAccounting ( struct accounting* acBook ) {
  int i;
  i = 0;
  for( ; i<12; i++){
    deleteMonth ( acBook->monthsArray[i]);
  }
  free (acBook);
}
