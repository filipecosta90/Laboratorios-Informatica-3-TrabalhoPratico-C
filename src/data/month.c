#include "month.h"

typedef struct month {

  static int numberSales;
  static int numberClients;

}Month;

void initMonth( void ){
  numberSales = 0;
  numberClients = 0;
}

int getNumberSales( void ){
  return numberSales;
}

int getNumberClients(void ){
  return numberClients;
}

void addSales ( int sales ) {
  numberSales += sales;
}

void addClients ( int clients) {
  numberClients += clients;
}

