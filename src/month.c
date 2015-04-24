/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "month.h"

struct month {

  int numberSales;
  int numberClients;
  float totalBilled;
};

Month newMonth ( void ) {
  Month newMonth = (Month) malloc ( sizeof (struct month));
  memset (( newMonth ) , '\0', ( sizeof ( struct month)) );
  return newMonth;
}

void initMonth( Month initMonth ){
  initMonth->numberSales = 0;
  initMonth->numberClients = 0;
  initMonth->totalBilled = 0.0;
}

int getNumberSales( Month getMonth ){
  return getMonth->numberSales;
}

int getNumberClients( Month getMonth ){
  return getMonth->numberClients;
}

float getTotalBilled ( Month getMonth ){
  return getMonth->totalBilled;
} 

void addSales ( Month addMonth , int sales ) {
  addMonth->numberSales += sales;
}

void addClients ( Month addMonth , int clients) {
  addMonth->numberClients += clients;
}

void addBills ( Month addMonth, float bill) {
  addMonth->totalBilled += bill;
}

void deleteMonth ( Month monthToDelete ){
  free( monthToDelete );
}

