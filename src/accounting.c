#include "data/month.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static Month monthsArray[12];

void initAccounting ( void ) {
  for(int i = 0; i<12; i++){
    monthsArray[i] = newMonth();
  }
}

void addSale ( int month ) {
  int position = month-1;
  addSales( monthsArray[position] , 1 );
}

void addClient ( int month ) {
  int position = month-1;
  addClients( monthsArray[position], 1);
}

void addBill ( int month , float billedValue) {
  int position = month -1;
  addBills ( monthsArray[position], billedValue );
}

char*  getCsvMonth ( int month ) {
  char* lineToReturn;
  char buffer[64];
  int position = month -1;
  sprintf( buffer, "\"%d\",\"%d\",\"%d\"", month , getNumberSales ( monthsArray[position] ) , getNumberClients ( monthsArray[position] ) );
  int sizeToReturn = strlen ( buffer ) + 1;
  lineToReturn = (char*) malloc ( sizeToReturn * sizeof (char) );
  strcpy( lineToReturn , buffer );
  lineToReturn[sizeToReturn-1] = '\0';
  return lineToReturn;
}

int getIntervalTotalSales ( int initialMonth , int finalMonth ){
  int totalSales = 0;
  for ( int i = initialMonth -1 ; i< finalMonth; i++){
    totalSales += getNumberSales ( monthsArray[ i ]);
  }
  return totalSales;
}

float getIntervalTotalBilled ( int initialMonth, int finalMonth ){
  float totalBilled = 0.0;
  for ( int i = initialMonth -1; i< finalMonth; i++ ){
    totalBilled += getTotalBilled ( monthsArray [ i ]);
  }
  return totalBilled;
}

void deleteAccounting ( void ) {
  for( int i = 0; i<12; i++){
    deleteMonth ( monthsArray[i]);
  }
  free (monthsArray);
}
