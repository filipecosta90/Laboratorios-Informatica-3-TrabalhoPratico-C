/*
 *  *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  *  */

#include <stdio.h>
#include <stdlib.h>

#include "accounting.h"
#include "parser.h"

int main (int argc, char *argv[] ){
  Accounting acBook;
  int flagReadingSales = 0;
  acBook = newAccounting();
  initAccounting (acBook);
  flagReadingSales = readFileSales( "../files/compras.txt" , acBook );
  printf("flag sales:%d\n", flagReadingSales);
  printf("get interval total sales result: %d\n", getIntervalTotalSales( acBook, 1, 12));
  printf("get interval total billed result: %f\n", getIntervalTotalBilled( acBook, 1, 12));
  printf("\"Mês\",\"#Compras\",\"#Clientes\"\n");
  printf("%s\n",getCsvMonth(acBook, 1));
  printf("%s\n",getCsvMonth(acBook, 2));
  printf("%s\n",getCsvMonth(acBook, 3));
  printf("%s\n",getCsvMonth(acBook, 4));
  printf("%s\n",getCsvMonth(acBook, 5));
  printf("%s\n",getCsvMonth(acBook, 6));
  printf("%s\n",getCsvMonth(acBook, 7));
  printf("%s\n",getCsvMonth(acBook, 8));
  printf("%s\n",getCsvMonth(acBook, 9));
  printf("%s\n",getCsvMonth(acBook, 10));
  printf("%s\n",getCsvMonth(acBook, 11));
  printf("%s\n",getCsvMonth(acBook, 12));
  return 0;
}
