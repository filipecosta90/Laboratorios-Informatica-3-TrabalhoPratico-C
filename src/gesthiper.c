/*
 *  *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  *  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "productCatalog.h"
#include "clientCatalog.h"
#include "accounting.h"
#include "salesProductLinker.h"
#include "clientProductLinker.h"
#include "parser.h"
#include "genLinkedList.h"

void handleStrings ( List strings ){
  char* handler;
  handler = NULL;
  while ( sizeLL (strings) > 0 ){
    handler = headLL ( strings );
    printf( "%s" , handler );
  }
}

int main (int argc, char *argv[] ){
  time_t start, end;
  Accounting acBook;
  ClientCatalog clCat;
  ProductCatalog prCat;
  SalesProductLinker splProd;
  ClientProductLinker cplClient;
  List listStrings;
  int flagReadingSales, flagReadingClients, flagReadingProducts, errorReadingProducts, errorReadingClients, idleProd, totalProdCatalogNumber, totalSPLProdNumber;
  listStrings = NULL;
  idleProd = 0; 
  totalProdCatalogNumber = 0; 
  totalSPLProdNumber = 0;
  errorReadingClients = 0;
  errorReadingProducts = 0;
  start = time(NULL);
  acBook = newAccounting();
  clCat = newClientCatalog();
  prCat = newProductCatalog();
  splProd = newSalesProductLinker ();
  cplClient = newClientProductLinker ();
  initAccounting (acBook);
  flagReadingProducts = readFileProducts ( "../files/FichProdutos.txt" , prCat , &errorReadingProducts );
  flagReadingClients = readFileClients ( "../files/FichClientes.txt" , clCat , &errorReadingClients );
  errorReadingClients = 0;
  errorReadingProducts = 0;

  flagReadingSales = readFileSales( "../files/Compras.txt" , acBook , clCat , prCat , splProd , cplClient , &errorReadingProducts , &errorReadingClients );

  printf("flag sales:%d\n", flagReadingSales);
  printf("get interval total sales result: %d\n", getIntervalTotalSales( acBook, 1, 12));
  printf("get interval total billed result: %f\n", getIntervalTotalBilled( acBook, 1, 12));
  printf("\"Mês\",\"#Compras\",\"#Clientes\"\n");
  printf("\"1\",\"%d\",\"%d\"\n", getMonthSales(acBook, 1) , getCPLinkerMonthSize ( cplClient , 1 ) );
  printf("\"2\",\"%d\",\"%d\"\n", getMonthSales(acBook, 2) , getCPLinkerMonthSize ( cplClient , 2 ) );
  printf("\"3\",\"%d\",\"%d\"\n", getMonthSales(acBook, 3) , getCPLinkerMonthSize ( cplClient , 3 ) );
  printf("\"4\",\"%d\",\"%d\"\n", getMonthSales(acBook, 4) , getCPLinkerMonthSize ( cplClient , 4 ) );
  printf("\"5\",\"%d\",\"%d\"\n", getMonthSales(acBook, 5) , getCPLinkerMonthSize ( cplClient , 5 ) );
  printf("\"6\",\"%d\",\"%d\"\n", getMonthSales(acBook, 6) , getCPLinkerMonthSize ( cplClient , 6 ) );
  printf("\"7\",\"%d\",\"%d\"\n", getMonthSales(acBook, 7) , getCPLinkerMonthSize ( cplClient , 7 ) );
  printf("\"8\",\"%d\",\"%d\"\n", getMonthSales(acBook, 8) , getCPLinkerMonthSize ( cplClient , 8 ) );
  printf("\"9\",\"%d\",\"%d\"\n", getMonthSales(acBook, 9) , getCPLinkerMonthSize ( cplClient , 9 ) );
  printf("\"10\",\"%d\",\"%d\"\n", getMonthSales(acBook, 10) , getCPLinkerMonthSize ( cplClient , 10 ) );
  printf("\"11\",\"%d\",\"%d\"\n", getMonthSales(acBook, 11) , getCPLinkerMonthSize ( cplClient , 11 ) );
  printf("\"12\",\"%d\",\"%d\"\n", getMonthSales(acBook, 12) , getCPLinkerMonthSize ( cplClient , 12 ) );

  printf("Total Read Clients:%d, Error Clients: %d, Inserted Clients: %d\n", flagReadingClients, errorReadingClients, flagReadingClients - errorReadingClients );
  printf("Total Read Products:%d, Error Products: %d, Inserted Products: %d\n", flagReadingProducts, errorReadingProducts, flagReadingProducts - errorReadingProducts );
  printf("Total Client of letter A: %d\n", getTotalClientsByLetter ( clCat, 'A' ));
  printf("Total Client of letter B: %d\n", getTotalClientsByLetter ( clCat, 'B' ));
  printf("Total Client of letter C: %d\n", getTotalClientsByLetter ( clCat, 'C' ));
  printf("Total Client of letter D: %d\n", getTotalClientsByLetter ( clCat, 'D' ));
  printf("Total Client of letter E: %d\n", getTotalClientsByLetter ( clCat, 'E' ));
  printf("Total Client of letter F: %d\n", getTotalClientsByLetter ( clCat, 'F' ));
  printf("Total Client of letter G: %d\n", getTotalClientsByLetter ( clCat, 'G' ));
  printf("Total Client of letter H: %d\n", getTotalClientsByLetter ( clCat, 'H' ));
  printf("Total Client of letter I: %d\n", getTotalClientsByLetter ( clCat, 'I' ));
  printf("Total Client of letter J: %d\n", getTotalClientsByLetter ( clCat, 'J' ));
  printf("Total Client of letter K: %d\n", getTotalClientsByLetter ( clCat, 'K' ));
  printf("Total Client of letter L: %d\n", getTotalClientsByLetter ( clCat, 'L' ));
  printf("Total Client of letter M: %d\n", getTotalClientsByLetter ( clCat, 'M' ));
  printf("Total Client of letter N: %d\n", getTotalClientsByLetter ( clCat, 'N' ));
  printf("Total Client of letter O: %d\n", getTotalClientsByLetter ( clCat, 'O' ));
  printf("Total Client of letter P: %d\n", getTotalClientsByLetter ( clCat, 'P' ));
  printf("Total Client of letter Q: %d\n", getTotalClientsByLetter ( clCat, 'Q' ));
  printf("Total Client of letter R: %d\n", getTotalClientsByLetter ( clCat, 'R' ));
  printf("Total Client of letter S: %d\n", getTotalClientsByLetter ( clCat, 'S' ));
  printf("Total Client of letter T: %d\n", getTotalClientsByLetter ( clCat, 'T' ));
  printf("Total Client of letter U: %d\n", getTotalClientsByLetter ( clCat, 'U' ));
  printf("Total Client of letter V: %d\n", getTotalClientsByLetter ( clCat, 'V' ));
  printf("Total Client of letter X: %d\n", getTotalClientsByLetter ( clCat, 'X' ));
  printf("Total Client of letter W: %d\n", getTotalClientsByLetter ( clCat, 'W' ));
  printf("Total Client of letter Y: %d\n", getTotalClientsByLetter ( clCat, 'Y' ));
  printf("Total Client of letter Z: %d\n", getTotalClientsByLetter ( clCat, 'Z' ));
  printf("Total Products of letter A: %d\n", getTotalProductsByLetter ( prCat, 'A' ));
  printf("Total Products of letter B: %d\n", getTotalProductsByLetter ( prCat, 'B' ));
  printf("Total Products of letter C: %d\n", getTotalProductsByLetter ( prCat, 'C' ));
  printf("Total Products of letter D: %d\n", getTotalProductsByLetter ( prCat, 'D' ));
  printf("Total Products of letter E: %d\n", getTotalProductsByLetter ( prCat, 'E' ));
  printf("Total Products of letter F: %d\n", getTotalProductsByLetter ( prCat, 'F' ));
  printf("Total Products of letter G: %d\n", getTotalProductsByLetter ( prCat, 'G' ));

  listStrings = getNormalClientsWhoBoughtProduct__LL_STRINGS  ( splProd , "UH9277" );
  printf("##\n##number of clients UH9277: %d\n", sizeLL ( listStrings ));
  handleStrings ( listStrings );
  listStrings = getPromotionClientsWhoBoughtProduct__LL_STRINGS  ( splProd , "UH9277" );
  printf("##\n##number of clients GV4379: %d\n", sizeLL ( listStrings ));
  handleStrings ( listStrings );
  totalSPLProdNumber = getGlobalNumberProducts ( splProd );
  totalProdCatalogNumber = getProductCatalogSize ( prCat );
  idleProd = totalProdCatalogNumber - totalSPLProdNumber;
  printf ( "Number of idle produts ( %d - %d ) = %d \n" , totalProdCatalogNumber , totalSPLProdNumber , idleProd );
  listStrings = getTopNMostSoldProducts__LL_STRINGS ( splProd , 50 );
  handleStrings ( listStrings );
  printf ( "total billed by XA1482 %f\n" , getTotalBilledByProductInMonth ( splProd , "XA1482" , 1 ) );
  printf ( "total billed by XA1482 %f\n" , getTotalBilledByProductInMonth ( splProd , "XA1482" , 2 ) );
  printf ( "total billed by XA1482 %f\n" , getTotalBilledByProductInMonth ( splProd , "XA1482" , 3 ) );
  printf("querie 9 month 12 of BL139\n");
  listStrings = getClientOrderedProductListOfMonth__LL_STRINGS ( cplClient , "BL139" , 12 );
  handleStrings ( listStrings );
  printf("querie 9 month 6 of BL139\n");
  listStrings = getClientOrderedProductListOfMonth__LL_STRINGS ( cplClient , "BL139" , 6 );
  handleStrings ( listStrings );
  listStrings = getClientProductTableByMonth__LL_STRINGS ( cplClient , "BL139" );
  handleStrings ( listStrings );
  listStrings = getClientProductTableByMonth__LL_STRINGS ( cplClient , "FP957" );
  handleStrings ( listStrings );
  listStrings = getClientsWhoBoughtEveryMonth__LL_STRINGS ( cplClient, clCat );
  printf("##\n##number of clients who bought every month: %d\n", sizeLL ( listStrings ));
  listStrings = getClientsByLetter__LL_strings ( clCat , 'A' );
  printf("##\n##number of clients of letter A: %d\n", sizeLL ( listStrings ));
  listStrings = getProductsByLetter__LL_strings ( prCat , 'B' );
  printf("##\n##number of products of letter B: %d\n", sizeLL ( listStrings ));
  listStrings = getProductsWhoWereNeverBought__LL_STRINGS ( splProd ,  prCat );
  printf("##\n##number of products who where never bought: %d\n", sizeLL ( listStrings ));

  end = time(NULL);
  printf("%.5f\n", (double)(end - start));
  return 0;
}
