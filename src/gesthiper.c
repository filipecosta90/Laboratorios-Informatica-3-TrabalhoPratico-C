/*
 *  *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  *  */

#include <stdio.h>
#include <stdlib.h>

#include "clientCatalog.h"
#include "accounting.h"
#include "parser.h"

int main (int argc, char *argv[] ){
  Accounting acBook;
  ClientCatalog clCat;
  int flagReadingSales, flagReadingClients;
  acBook = newAccounting();
  clCat = newClientCatalog();
  initAccounting (acBook);
  flagReadingClients = readFileClients ( "../files/FichClientes.txt" , clCat );
  flagReadingSales = readFileSales( "../files/Compras.txt" , acBook );
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
  printf("flag clients:%d\n", flagReadingClients);
  printf("Total Client of letter A: %d\n", getTotalClientsByLetter ( clCat, 'A' ));
printf("Total Client of letter B: %d\n", getTotalClientsByLetter ( clCat, 'B' ));
printf("Total Client of letter D: %d\n", getTotalClientsByLetter ( clCat, 'd' ));
return 0;
}

