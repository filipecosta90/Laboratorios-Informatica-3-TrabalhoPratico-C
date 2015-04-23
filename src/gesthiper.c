/*
 *  *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  *  */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "productCatalog.h"
#include "clientCatalog.h"
#include "accounting.h"
#include "salesProductLinker.h"
#include "clientProductLinker.h"
#include "parser.h"
#include "genLinkedList.h"

#define MAX_FILENAME 64
#define MAX_LINE_OPTION 64
#define PRODUCT_STRING_SIZE 8
#define CLIENT_STRING_SIZE 7
#define STANDARD_PRODUCT_FILENAME "../files/FichProdutos.txt"
#define STANDARD_CLIENT_FILENAME "../files/FichClientes.txt"
#define STANDARD_SALES_FILENAME "../files/Compras.txt"
#define HORIZONTAL_LINES 20



static int flagReadedClients, flagReadedProducts, flagReadedSales, flagBlockedContent;

char* ensureUpper ( char *s ) {
  int i;
  for (i = 0; i < strlen(s); i++)
    s[i] = toupper(s[i]);
  return s;
}

void handleStrings ( List strings , char* title ){
  int actual, actualTopLimit, horizontalLines, actualLowLimit, readedSize, flagEXIT;
  char* pos;
  char internalOption[MAX_LINE_OPTION];
  char* handler;
  handler = NULL;
  actualLowLimit = 1;
  horizontalLines = (int) HORIZONTAL_LINES;
  readedSize = sizeLL (strings);
  flagEXIT=0;
  while ( flagEXIT == 0 ){
    system("clear");
    actual = actualLowLimit;
    actualTopLimit = actualLowLimit + horizontalLines -1;
    if(actualTopLimit > readedSize ){ actualTopLimit = readedSize; }
    printf("/****************************************\n");
    printf("/*\t%s\n" , title);
    printf("/*\tTotal de elementos lidos: %d\n" , readedSize);
    printf("/*\tMostrando elementos %d a %d\n" , actualLowLimit , actualTopLimit);
    printf("/****************************************\n");

    while ( actual <=  actualTopLimit ){
      handler = (char*) getDataInPositionLL ( strings , actual );
      printf( "%d|\t%s" , actual , handler );
      actual++;
    }
    printf("/****************************************\n");
    printf("/*\tPara terminar prima 'q'\n" );
    printf("/*\tPara avançar 1 elemento prima 'd'\n" );
    printf("/*\tPara avançar 20 elementos prima 'f'\n" );
    printf("/*\tPara recuar 1 elemento prima 's'\n" );
    printf("/*\tPara recuar 20 elementos prima 'a'\n" );
    printf("/****************************************\n");
    printf("opção:\n");
    fgets(internalOption, MAX_LINE_OPTION, stdin);
    if ((pos=strchr(internalOption, '\n')) != NULL){
      *pos = '\0';
    }
    if ( strcmp ( internalOption , "s" ) == 0 ){ actualLowLimit--; if( actualLowLimit < 1 ){ actualLowLimit = 1; } }
    if ( strcmp ( internalOption , "d" ) == 0 ){ actualLowLimit++; if( actualTopLimit > readedSize ){ actualTopLimit = readedSize; actualLowLimit = actualTopLimit - horizontalLines; } }
    if ( strcmp ( internalOption , "f" ) == 0 ){ actualLowLimit+=20; if( actualTopLimit > readedSize ){ actualTopLimit = readedSize; actualLowLimit = actualTopLimit - horizontalLines;  } }
    if ( strcmp ( internalOption , "a" ) == 0){ actualLowLimit-=20; if( actualLowLimit < 1 ){ actualLowLimit = 1; } }
    if ( strcmp ( internalOption , "q" ) == 0 ){ flagEXIT = 1; }
  }
}

void handleStringsToFile ( List strings , char* fileName ){
  char* handler;
  FILE * fp;
  handler = NULL;
  fp = fopen (fileName, "w");
  while ( sizeLL (strings) > 0 ){
    handler = headLL ( strings );
    fprintf( fp , "%s" , handler );
  }
  fclose(fp);
}

void logStats ( char* fileName , char* querie_number ,  clock_t tstart , clock_t tend ){
  FILE * fp;
  double duration;
  fp = fopen (fileName, "a");
  duration = (((double)tend - (double)tstart) / CLOCKS_PER_SEC ) * 1000;
  fprintf( fp , "\"%s\",\"%.5f\"\n", querie_number , duration );
  fclose(fp);
}

void head (){
  system("clear");
  printf("/***\n");
  printf("*                               888    888\n");
  printf("*                               888    888\n");
  printf("*                               888    888\n");
  printf("*     .d88b.   .d88b.  .d8888b  888888 88888b.  888  888 88888b.   .d88b.  888d888\n");
  printf("*    d88P\"88b d8P  Y8b 88K      888    888 \"88b 888  888 888 \"88b d8P  Y8b 888P\"\n");
  printf("*    888  888 88888888 \"Y8888b. 888    888  888 888  888 888  888 88888888 888\n");
  printf("*    Y88b 888 Y8b.          X88 Y88b.  888  888 Y88b 888 888 d88P Y8b.     888\n");
  printf("*     \"Y88888  \"Y8888   88888P'  \"Y888 888  888  \"Y88888 88888P\"   \"Y8888  888\n");
  printf("*         888                                        888 888\n");
  printf("*    Y8b d88P                                   Y8b d88P 888\n");
  printf("*     \"Y88P\"                                     \"Y88P\"  888\n");
  printf("*/\n");
}

void menu(){
  printf("1-Ler os ficheiros de Produtos, Clientes e Compras.\n");
  if ( flagReadedProducts == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("2-Listar produtos começados por uma determinada letra e o seu total.\n");
  if ( flagReadedSales == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("3-Listar as vendas (Normais e Promoções) de um determinado produto num dado mês e o total faturado\n");
  if ( flagReadedSales == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("4-Listar códigos de produtos (e o seu número total), que ninguém comprou.\n");
  if ( flagReadedSales == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("5-Tabela de produtos comprados (mês a mês) de um dado cliente.\n");
  if ( flagReadedClients == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("6-Listar clientes cujo código começa por uma determinada letra.\n");
  if ( flagReadedSales == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("7-Listar compras registadas e total faturado num dado intervalo de tempo.\n");
  if ( flagReadedSales == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("8-Listar clientes (e numero total) que compraram um determinado produto (Normais e Promoções).\n");
  if ( flagReadedSales == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("9-Listar por ordem descendente os produtos que um determinado cliente comprou num dado mês\n");
  if ( flagReadedSales == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("10-Listar clientes que realizaram compras em todos os meses do ano.\n");
  if ( flagReadedSales == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("11-Criar ficheiro CSV com o número de compras realizadas e número total de clientes que realizaram compras para cada mês.\n");
  if ( flagReadedSales == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("12-Listar N produtos mais vendidos em todo o ano bem como o total de clientes que o comprou e número de unidades vendidas.\n");
  if ( flagReadedSales == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("13-Listar os 3 produtos mais comprados por um determinado cliente durante o ano.\n");
  if ( flagReadedSales == 0 ){
    printf ( "\t **bloqueado** ");
  }
  printf("14-Número de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou.\n");
  printf("15-Sair\n");
}

void menuReadProductsFile( ProductCatalog prCat ){
  char internalOption[MAX_LINE_OPTION];
  char fileName[MAX_FILENAME];
  char * pos;
  int errorReadingProducts;
  int correctInsertedProducts;
  int flagEXIT, firstTime;
  clock_t start , end;
  flagEXIT = 0;
  firstTime = 1;

  do {
    if( firstTime == 0 ){
      printf("Pressione qualquer tecla para continuar.\n");
      getchar();
    }
    firstTime = 0;
    system("clear");
    head();
    if( flagReadedProducts == 1 ){
      printf("1-Ler o ficheiro de Produtos Standard (%s).\n\tNota: A leitura atual será eliminada!\n" , STANDARD_PRODUCT_FILENAME);
      printf("2-Especificar o nome do ficheiro de Produtos.\n\tNota: A leitura atual será eliminada!\n");
    }
    else {
      printf("1-Ler o ficheiro de Produtos Standard (%s).\n" , STANDARD_PRODUCT_FILENAME);
      printf("2-Especificar o nome do ficheiro de Produtos.\n");
    }

    printf("3-Voltar ao menu anterior.\n");
    printf("\nEscolha uma opção:\n");
    fgets(internalOption, MAX_LINE_OPTION, stdin);
    if ((pos=strchr(internalOption, '\n')) != NULL){
      *pos = '\0';
    }

    if ( strcmp ( internalOption , "1" ) == 0 ){
      start = clock();
      if ( flagReadedProducts == 1 ) {
        prCat = newProductCatalog();
        correctInsertedProducts = readFileProducts ( STANDARD_PRODUCT_FILENAME , prCat , &errorReadingProducts );
      }
      else{
        correctInsertedProducts = readFileProducts ( STANDARD_PRODUCT_FILENAME , prCat , &errorReadingProducts );
      }
      end = clock();
      logStats ( "statistics.csv" , "QUERIE QUERIE 1-Products" , start, end );
      printf("Resultado leitura de %s\n\t%d linhas lidas.\n\t%d linhas validadas.\n\t%d linhas rejeitadas.\n", STANDARD_PRODUCT_FILENAME , correctInsertedProducts+errorReadingProducts, correctInsertedProducts , errorReadingProducts );
      flagReadedProducts = 1;
    }
    if ( strcmp ( internalOption , "2" ) == 0 ){
      printf("Insira o nome do ficheiro a ser lido:\n");
      fgets(fileName, MAX_FILENAME, stdin);
      if ((pos=strchr(fileName, '\n')) != NULL){
        *pos = '\0';
      }
      start = clock();
      if ( flagReadedProducts == 1 ) {
        prCat = newProductCatalog();
        correctInsertedProducts = readFileProducts ( fileName , prCat , &errorReadingProducts );
      }
      else{
        correctInsertedProducts = readFileProducts ( fileName , prCat , &errorReadingProducts );
      }
      end = clock();
      logStats ( "statistics.csv" , "QUERIE 1-Products" , start, end );
      printf("Resultado leitura de %s\n\t%d linhas lidas.\n\t%d linhas validadas.\n\t%d linhas rejeitadas.\n", fileName , correctInsertedProducts+errorReadingProducts, correctInsertedProducts , errorReadingProducts );

      flagReadedProducts = 1;
    }
    if ( strcmp ( internalOption , "3" ) == 0 ){
      flagEXIT = 1;
    }
  } while ( flagEXIT == 0 );
}

void menuReadClientsFile( ClientCatalog clCat ){
  char internalOption[MAX_LINE_OPTION];
  char * pos;
  char fileName[MAX_FILENAME];
  int errorReadingClients;
  int correctInsertedClients;
  int flagEXIT, firstTime;
  clock_t start , end;
  flagEXIT = 0;
  firstTime = 1;

  do {
    if( firstTime == 0 ){
      printf("Pressione qualquer tecla para continuar.\n");
      getchar();
    }
    firstTime = 0;
    system("clear");
    head();
    if( flagReadedClients == 1 ){
      printf("1-Ler o ficheiro de Clientes Standard (%s).\n\tNota: A leitura atual será eliminada!\n" , STANDARD_CLIENT_FILENAME);
      printf("2-Especificar o nome do ficheiro de Clientes.\n\tNota: A leitura atual será eliminada!\n");
    }
    else {
      printf("1-Ler o ficheiro de Clientes Standard (%s).\n" , STANDARD_CLIENT_FILENAME);
      printf("2-Especificar o nome do ficheiro de Clientes.\n");
    }
    printf("3-Voltar ao menu anterior.\n");
    printf("\nEscolha uma opção:\n");
    fgets(internalOption, MAX_LINE_OPTION , stdin);
    if ((pos=strchr(internalOption, '\n')) != NULL){
      *pos = '\0';
    }
    start= clock();
    if ( strcmp ( internalOption , "1" ) == 0 ){
      if ( flagReadedClients == 1 ) {
        clCat = newClientCatalog();
        correctInsertedClients = readFileClients ( STANDARD_CLIENT_FILENAME , clCat , &errorReadingClients );
      }
      else{
        correctInsertedClients = readFileClients ( STANDARD_CLIENT_FILENAME , clCat , &errorReadingClients );
      }
      end = clock();
      logStats ( "statistics.csv" , "QUERIE 1-Clients" , start, end );
      printf("Resultado leitura de %s\n\t%d linhas lidas.\n\t%d linhas validadas.\n\t%d linhas rejeitadas.\n", STANDARD_CLIENT_FILENAME , correctInsertedClients+errorReadingClients, correctInsertedClients , errorReadingClients );
      flagReadedClients = 1;
    }
    if ( strcmp ( internalOption , "2" ) == 0 ){
      printf("Insira o nome do ficheiro a ser lido:\n");
      fgets(fileName, MAX_FILENAME, stdin);
      if ((pos=strchr(fileName, '\n')) != NULL){
        *pos = '\0';
      }
      start = clock();
      if ( flagReadedClients == 1 ) {
        clCat = newClientCatalog();
        correctInsertedClients = readFileClients ( fileName , clCat , &errorReadingClients );
      }
      else{
        correctInsertedClients = readFileClients ( fileName , clCat , &errorReadingClients );
      }
      end = clock();
      logStats ( "statistics.csv" , "QUERIE 1-Clients" , start, end );
      printf("Resultado leitura de %s\n\t%d linhas lidas.\n\t%d linhas validadas.\n\t%d linhas rejeitadas.\n", fileName , correctInsertedClients+errorReadingClients, correctInsertedClients , errorReadingClients );
      flagReadedClients = 1;
    }
    if ( strcmp ( internalOption , "3" ) == 0 ){
      flagEXIT = 1;
    }
  } while ( flagEXIT == 0 );
}

void menuReadSalesFile ( Accounting acBook , ClientCatalog clCat , ProductCatalog prCat , SalesProductLinker splProd , ClientProductLinker cplClient  ) {
  char internalOption[MAX_LINE_OPTION];
  char * pos;
  char fileName[MAX_FILENAME];
  int errorReadingClientsInSales , errorReadingProductsInSales ;
  int correctInsertedSales;
  int flagEXIT, firstTime;
  clock_t start , end;
  flagEXIT = 0;
  firstTime = 1;

  do {
    if( firstTime == 0 ){
      printf("Pressione qualquer tecla para continuar.\n");
      getchar();
    }
    firstTime = 0;
    system("clear");
    head();
    if( flagReadedSales == 1 ){
      printf("1-Ler o ficheiro de Compras Standard (%s).\n\tNota: A leitura atual será eliminada!\n" , STANDARD_SALES_FILENAME);
      printf("2-Especificar o nome do ficheiro de Compras.\n\tNota: A leitura atual será eliminada!\n");
    }
    else {
      printf("1-Ler o ficheiro de Compras Standard (%s).\n" , STANDARD_SALES_FILENAME);
      printf("2-Especificar o nome do ficheiro de Compras.\n");
    }
    printf("3-Voltar ao menu anterior.\n");
    printf("\nEscolha uma opção:\n");
    fgets(internalOption, MAX_LINE_OPTION , stdin);
    if ((pos=strchr(internalOption, '\n')) != NULL){
      *pos = '\0';
    }
    if ( strcmp ( internalOption , "1" ) == 0 ){
      start = clock();
      if ( flagReadedSales == 1 ) {
        acBook = newAccounting();
        splProd = newSalesProductLinker();
        cplClient = newClientProductLinker();
        initAccounting (acBook);
        correctInsertedSales = readFileSales( STANDARD_SALES_FILENAME , acBook , clCat , prCat , splProd , cplClient , &errorReadingProductsInSales , &errorReadingClientsInSales );
      }
      else{
        correctInsertedSales = readFileSales( STANDARD_SALES_FILENAME , acBook , clCat , prCat , splProd , cplClient , &errorReadingProductsInSales , &errorReadingClientsInSales );
      }
      end = clock();
      logStats ( "statistics.csv" , "QUERIE 1-Sales" , start, end );
      printf("Resultado leitura de %s\n\t%d linhas lidas.\n\t%d linhas validadas.\n\t%d linhas rejeitadas.\n", STANDARD_SALES_FILENAME , correctInsertedSales+errorReadingProductsInSales+errorReadingClientsInSales, correctInsertedSales , errorReadingProductsInSales+errorReadingClientsInSales );
      flagReadedSales = 1;
    }
    if ( strcmp ( internalOption , "2" ) == 0 ){
      printf("Insira o nome do ficheiro a ser lido:\n");
      fgets(fileName, MAX_FILENAME, stdin);
      if ((pos=strchr(fileName, '\n')) != NULL){
        *pos = '\0';
      }
      start= clock();
      if ( flagReadedSales == 1 ) {
        acBook = newAccounting();
        splProd = newSalesProductLinker();
        cplClient = newClientProductLinker();
        initAccounting (acBook);
        correctInsertedSales = readFileSales( fileName , acBook , clCat , prCat , splProd , cplClient , &errorReadingProductsInSales , &errorReadingClientsInSales );
      }
      else{
        correctInsertedSales = readFileSales( fileName , acBook , clCat , prCat , splProd , cplClient , &errorReadingProductsInSales , &errorReadingClientsInSales );
      }
      end = clock();
      logStats ( "statistics.csv" , "QUERIE 1-Sales" , start, end );
      printf("Resultado leitura de %s\n\t%d linhas lidas.\n\t%d linhas validadas.\n\t%d linhas rejeitadas.\n", fileName , correctInsertedSales+errorReadingProductsInSales+errorReadingClientsInSales, correctInsertedSales , errorReadingProductsInSales+errorReadingClientsInSales );
      flagReadedSales = 1;
    }
    if ( strcmp ( internalOption , "3" ) == 0 ){
      flagEXIT = 1;
    }
  } while ( flagEXIT == 0 );
}

/* *
 * QUERIE 1
 * Ler os 3 ficheiros (Produtos, Clientes e Compras), cujos nomes poderão ser introduzidos pelo utilizador ou, opcionalmente, assumidos por omissão.
 * O resultado desta leitura deverá ser a apresentação imediata ao utilizador do nome do ficheiro lido e o número total de linhas lidas e validadas.
 * Uma nova leitura destes ficheiros deverá de imediato reiniciar e refazer as estruturas de dados em memória;
 * */
void querie1( ProductCatalog prCat , ClientCatalog clCat, Accounting acBook , SalesProductLinker splProd , ClientProductLinker cplClient ){
  char internalOption[MAX_LINE_OPTION];
  char* pos;
  int errorReadingClients , errorReadingProducts , errorReadingClientsInSales , errorReadingProductsInSales ;
  int correctInsertedClients, correctInsertedProducts, correctInsertedSales;
  int firstTime , flagEXIT;
  clock_t start , end;
  firstTime = 1;
  flagEXIT = 0;

  do{
    if ( firstTime == 0 ){
      printf("Pressione qualquer tecla para continuar\n");
      getchar();
    }
    firstTime = 0;
    system("clear");
    head();
    if( flagReadedProducts == 0 ){
      printf("1-Ler o ficheiro de Produtos.\n");
    }
    else {
      printf("1-Ler o ficheiro de Produtos.\n\tNota: A leitura atual será eliminada!\n");
    }
    if( flagReadedClients == 0 ){
      printf("2-Ler o ficheiro de Clientes.\n");
    }
    else {
      printf("2-Ler o ficheiro de Clientes.\n\tNota: A leitura atual será eliminada!\n");
    }
    if( flagReadedClients == 1 && flagReadedProducts == 1 ){
      if ( flagReadedSales == 0 ){
        printf("3-Ler o ficheiro de Compras.\n");
      }
      else {
        printf("3-Ler o ficheiro de Compras.\n\tNota: A leitura atual será eliminada!\n");
      }
    }
    else {
      printf("3- ** bloqueado **  Ler o ficheiro de Compras. ** bloqueado **\n\tNota: para ler o ficheiro de compras tem que possuir uma leitura de produtos e clientes válida!\n");
    }
    if( flagBlockedContent == 1 ){
      printf ( "\nA opção que escolheu encontra-se bloqueada. Atente na nota localizada abaixo da opção.\n");
      flagBlockedContent = 0;
    }
    if ( flagReadedSales == 0 && flagReadedClients == 0 & flagReadedProducts == 0  ){
      printf("4-Ler o ficheiros de Produtos (%s), Compras (%s) e Vendas (%s) Standard.\n", STANDARD_PRODUCT_FILENAME, STANDARD_CLIENT_FILENAME, STANDARD_SALES_FILENAME);
    }
    else {
      printf("4-Ler o ficheiros de Produtos (%s), Compras (%s) e Vendas (%s) Standard.\n\tNota: A leitura atual será eliminada!\n", STANDARD_PRODUCT_FILENAME, STANDARD_CLIENT_FILENAME, STANDARD_SALES_FILENAME);
    }
    printf("\n5-Voltar ao menu anterior.\n");
    printf("\nEscolha uma opção:\n");
    fgets(internalOption, MAX_LINE_OPTION , stdin);
    if ((pos=strchr(internalOption, '\n')) != NULL){
      *pos = '\0';
    }
    if ( strcmp ( internalOption , "1" ) == 0 ){
      menuReadProductsFile( prCat );
    }
    if ( strcmp ( internalOption , "2" ) == 0 ){

      menuReadClientsFile( clCat );
    }
    if ( strcmp ( internalOption , "3" ) == 0 ){
      if ( flagReadedProducts && flagReadedClients ){
        menuReadSalesFile( acBook , clCat , prCat , splProd , cplClient );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( internalOption , "4" ) == 0 ){
      start = clock();
      if ( flagReadedProducts == 1 ) {
        prCat = newProductCatalog();
        correctInsertedProducts = readFileProducts ( STANDARD_PRODUCT_FILENAME , prCat , &errorReadingProducts );
      }
      else{
        correctInsertedProducts = readFileProducts ( STANDARD_PRODUCT_FILENAME , prCat , &errorReadingProducts );
      }
      printf("Resultado leitura de %s\n\t%d linhas lidas.\n\t%d linhas validadas.\n\t%d linhas rejeitadas.\n", STANDARD_PRODUCT_FILENAME , correctInsertedProducts+errorReadingProducts, correctInsertedProducts , errorReadingProducts );
      flagReadedProducts = 1;
      end = clock();
      logStats ( "statistics.csv" , "QUERIE 1-Products" , start, end );
      start = clock();
      if ( flagReadedClients == 1 ) {
        clCat = newClientCatalog();
        correctInsertedClients = readFileClients ( STANDARD_CLIENT_FILENAME , clCat , &errorReadingClients );
      }
      else{
        correctInsertedClients = readFileClients ( STANDARD_CLIENT_FILENAME , clCat , &errorReadingClients );
      }
      end = clock();
      logStats ( "statistics.csv" , "QUERIE 1-Clients" , start, end );
      printf("Resultado leitura de %s\n\t%d linhas lidas.\n\t%d linhas validadas.\n\t%d linhas rejeitadas.\n", STANDARD_CLIENT_FILENAME , correctInsertedClients+errorReadingClients, correctInsertedClients , errorReadingClients );
      flagReadedClients = 1;
      start = clock();
      if ( flagReadedSales == 1 ) {
        acBook = newAccounting();
        splProd = newSalesProductLinker();
        cplClient = newClientProductLinker();
        initAccounting (acBook);
        correctInsertedSales = readFileSales( STANDARD_SALES_FILENAME , acBook , clCat , prCat , splProd , cplClient , &errorReadingProductsInSales , &errorReadingClientsInSales );
      }
      else{
        correctInsertedSales = readFileSales( STANDARD_SALES_FILENAME , acBook , clCat , prCat , splProd , cplClient , &errorReadingProductsInSales , &errorReadingClientsInSales );
      }
      end = clock();
      logStats ( "statistics.csv" , "QUERIE 1-Sales" , start, end );
      printf("Resultado leitura de %s\n\t%d linhas lidas.\n\t%d linhas validadas.\n\t%d linhas rejeitadas.\n", STANDARD_SALES_FILENAME , correctInsertedSales+errorReadingProductsInSales+errorReadingClientsInSales, correctInsertedSales , errorReadingProductsInSales+errorReadingClientsInSales );
      flagReadedSales = 1;
    }
    if ( strcmp ( internalOption , "5" ) == 0 ){
      flagEXIT = 1;
    }
  } while ( flagEXIT == 0 );
}

/* *
 * QUERIE 2
 * Determinar a lista e o total de produtos cujo código se inicia por uma dada letra (maiúscula);
 * Apresentar tal lista ao utilizador e permitir que o mesmo navegue na mesma, sendo tal lista apresentada por ordem alfabética;
 * */
void querie2( ProductCatalog prCat , List listStrings ){
  char line[MAX_LINE_OPTION];
  char* pos;
  clock_t start , end;
  system("clear");
  head();
  printf("Listar produtos começados por uma determinada letra.\n\n");
  printf("Insira uma letra: ");
  fgets( line , MAX_LINE_OPTION , stdin);
  if ((pos=strchr( line , '\n')) != NULL){
    *pos = '\0';
  }
  start = clock();
  listStrings = getProductsByLetter__LL_strings ( prCat , line[0] );
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 2" , start, end );
  handleStrings ( listStrings , "total de produtos cujo código se inicia por uma dada letra" );
}

/* *
 * QUERIE 3
 * Dado um mês e um código de produto válidos, determinar e apresentar o número total de vendas em modo N e em modo P, e o total facturado com esse produto em tal mês ;
 * */
void querie3( SalesProductLinker splProd ){
  char codProduto[PRODUCT_STRING_SIZE];
  char* pos;
  char mesString[MAX_LINE_OPTION];
  float totalBilled;
  int normalSales, promotionSales;
  int mes;
  time_t start, end;
  normalSales = 0;
  promotionSales = 0;
  totalBilled = 0.0;
  system("clear");
  head();
  printf("Apresentar o número total de vendas em modo N e em modo P, e o total facturado de um produto num dado mês\n\n");
  printf("Insira um código de um produto valido:\n");
  fgets( codProduto , PRODUCT_STRING_SIZE , stdin);
  if ((pos=strchr( codProduto , '\n')) != NULL){
    *pos = '\0';
  }
  printf("Insira um mês válido:\n");
  fgets( mesString , MAX_LINE_OPTION , stdin);
  if ((pos=strchr( mesString , '\n')) != NULL){
    *pos = '\0';
  }
  mes = atoi ( mesString );
  start = clock();
  promotionSales =  getPromotionClientsNumberWhoBoughtProductInMonth ( splProd , ensureUpper( codProduto ) , mes );
  normalSales = getNormalClientsNumberWhoBoughtProductInMonth ( splProd , ensureUpper( codProduto ) , mes );
  totalBilled = getTotalBilledByProductInMonth ( splProd , ensureUpper( codProduto ) , mes );
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 3" , start, end );
  printf ( " Detalhes de vendas de código de produto %s para o mês %d\n\tNúmero de vendas N: %d\tvendas P: %d\n\tTotal faturado:%f\n", codProduto , mes, normalSales , promotionSales , totalBilled );
}

/**
 *QUERIE 4
 *Determinar a lista de códigos de produtos (e o seu número total), que ninguém comprou;
 **/
void querie4( SalesProductLinker splProd , ProductCatalog prCat , List listStrings ){
  time_t start, end;
  system("clear");
  head();
  printf("Lista códigos de produtos (e o seu número total), que ninguém comprou.\n\n");
  start = clock();
  listStrings = getProductsWhoWereNeverBought__LL_STRINGS ( splProd ,  prCat );
  end = clock();
  printf( "Número total de produtos que ninguém comprou: %d\n", sizeLL ( listStrings ));
  handleStrings ( listStrings , "lista de códigos de produtos que ninguém comprou" );
  logStats ( "statistics.csv" , "QUERIE 4" , start, end );
}

/**
 *QUERIE 5
 *Dado um código de cliente, criar uma tabela com o número total de produtos comprados, mês a mês (para meses em que não comprou a entrada deverá ficar a 0). 
 *A tabela deverá ser apresentada em ecrã. O utilizador deverá ter a opção de guardar tal tabela num ficheiro de texto;
 **/
void querie5( ClientProductLinker cplClient , List listStrings ){
  char internalOption[MAX_LINE_OPTION];
  char fileName[MAX_FILENAME];
  char codCliente[CLIENT_STRING_SIZE];
  char* pos;
  time_t start, end;
  system("clear");
  head();
  printf("Tabela de produtos comprados (mês a mês) de um dado cliente.\n\n");
  printf("Insira um codigo de um cliente valido:\n");
  fgets(codCliente, MAX_LINE_OPTION, stdin);
  if ((pos=strchr(codCliente, '\n')) != NULL){
    *pos = '\0';
  }
  start = clock();
  listStrings = getClientProductTableByMonth__LL_STRINGS ( cplClient , ensureUpper( codCliente ) );
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 5" , start, end );
  handleStrings ( listStrings , "tabela com o número total de produtos comprados, mês a mês" );
  printf("Pretende guardar a tabela num ficheiro de texto? (s/n)\n");
  fgets(internalOption, MAX_LINE_OPTION, stdin);
  if ((pos=strchr(internalOption, '\n')) != NULL){
    *pos = '\0';
  }
  if ( strcmp ( internalOption , "s" ) == 0 || strcmp ( internalOption , "S" ) == 0 ){
    printf("Indique o nome do ficheiro:\n");
    fgets(fileName, MAX_FILENAME, stdin);
    if ((pos=strchr(fileName, '\n')) != NULL){
      *pos = '\0';
    }
    handleStringsToFile( listStrings , fileName);
  }
}

/**
 *QUERIE 6
 *Determinar a lista de todos os códigos de clientes iniciados pela letra dada como parâmetro (maiúscula ou minúscula deverá ser indiferente);
 **/
void querie6( ClientCatalog clCat , List listStrings ){
  char internalOption[MAX_LINE_OPTION];
  char* pos;
  time_t start, end;
  system("clear");
  head();
  printf("Listar clientes cujo código começa por uma determinada letra.\n\n");
  printf("Insira uma letra: ");
  fgets(internalOption, MAX_LINE_OPTION, stdin);
  if ((pos=strchr(internalOption, '\n')) != NULL){
    *pos = '\0';
  }
  start = clock();
  listStrings = getClientsByLetter__LL_strings ( clCat , internalOption[0] );
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 6" , start, end );
  handleStrings ( listStrings , "lista de todos os códigos de clientes iniciados pela letra dada como parâmetro" );
}

/**
 *QUERIE 7
 *Dado um intervalo fechado de meses, por exemplo [2..6], determinar o total de compras registadas nesse intervalo e o total facturado;
 **/
void querie7( Accounting acBook ){
  int mesInicial, mesFinal;
  char internalOption[MAX_LINE_OPTION];
  char *pos;
  clock_t start , end;
  system("clear");
  head();
  printf("Lista compras registadas e total faturado num dado intervalo de tempo.\n\n");
  printf("Insira mês inicial:\n");
  fgets(internalOption, MAX_LINE_OPTION, stdin);
  if ((pos=strchr(internalOption, '\n')) != NULL){
    *pos = '\0';
  }
  mesInicial = atoi ( internalOption );
  printf("Insira mês final:\n");
  fgets(internalOption, MAX_LINE_OPTION, stdin);
  if ((pos=strchr(internalOption, '\n')) != NULL){
    *pos = '\0';
  }
  mesFinal = atoi ( internalOption );
  start = clock();
  printf("Número total de vendas no invervalo[%d-%d]: %d\n", mesInicial , mesFinal , getIntervalTotalSales( acBook, mesInicial , mesFinal ));
  printf("Total facturado no invervalo[%d-%d]: %f\n", mesInicial , mesFinal , getIntervalTotalBilled( acBook , mesInicial , mesFinal ));
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 7" , start, end );
}

/**
 *QUERIE 8
 *Dado um código de produto, determinar os códigos (e número total) dos clientes que o compraram, distinguido entre compra N e compra P;
 **/
void querie8( SalesProductLinker splProd , List listStrings ){
  char codProduto[PRODUCT_STRING_SIZE];
  char* pos;
  clock_t start , end;
  system("clear");
  head();
  printf("Lista de clientes (e numero total) que compraram um determinado produto (Normais e Promoções).\n\n");
  printf("Insira um codigo de um produto valido:\n");
  fgets( codProduto , PRODUCT_STRING_SIZE , stdin);
  if ((pos=strchr( codProduto , '\n')) != NULL){
    *pos = '\0';
  }
  start = clock();
  listStrings = getNormalClientsWhoBoughtProduct__LL_STRINGS  ( splProd , ensureUpper( codProduto ) );
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 8" , start, end );
  printf("Número total de clientes que compraram %s em modo normal: %d\n", codProduto , sizeLL ( listStrings ));
  handleStrings ( listStrings , "Códigos de clientes que compraram o produto em modo normal");
  listStrings = getPromotionClientsWhoBoughtProduct__LL_STRINGS  ( splProd , ensureUpper( codProduto ) );
  printf("Número total de clientes que compraram %s em modo promocional: %d\n", codProduto , sizeLL ( listStrings ));
  handleStrings ( listStrings , "Códigos de clientes que compraram o produto em modo promocional");
}

/**
 *QUERIE 9
 *Dado um código de cliente e um mês, determinar a lista de códigos de produtos que mais comprou, por ordem descendente;
 **/
void querie9( ClientProductLinker cplClient , List listStrings ){
  int mes;
  char codCliente[CLIENT_STRING_SIZE];
  char internalOption[MAX_LINE_OPTION];
  char* pos;
  clock_t start , end;
  system("clear");
  head();
  printf("Lista por ordem descendente de produtos que um determinado cliente comprou num dado mês\n\n");
  printf("Insira um codigo de um cliente valido:\n");
  fgets(codCliente, CLIENT_STRING_SIZE, stdin);
  if ((pos=strchr(codCliente, '\n')) != NULL){
    *pos = '\0';
  }
  printf("Insira um mês válido:\n");
  fgets(internalOption, MAX_LINE_OPTION, stdin);
  if ((pos=strchr(internalOption, '\n')) != NULL){
    *pos = '\0';
  }
  mes = atoi ( internalOption );
  start = clock();
  listStrings = getClientOrderedProductListOfMonth__LL_STRINGS ( cplClient , ensureUpper( codCliente ) , mes );
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 9" , start, end );
  handleStrings ( listStrings , "lista de códigos de produto que mais comprou" );
}

/**
 *QUERIE 10
 *Determinar a lista de códigos de clientes que realizaram compras em todos os meses do ano;
 **/
void querie10( ClientProductLinker cplClient , ClientCatalog clCat , List listStrings ){
  clock_t start , end;
  system("clear");
  head();
  printf("Listar clientes que realizaram compras em todos os meses do ano.\n\n");
  start = clock();
  listStrings = getClientsWhoBoughtEveryMonth__LL_STRINGS ( cplClient , clCat );
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 10" , start, end );
  printf("Número de clientes que realizaram compras em todos os meses do ano: %d\n", sizeLL ( listStrings ));
  handleStrings ( listStrings , "lista de códigos de clientes que realizaram compras em todos os meses do ano" );
}

/**
 *QUERIE 11
 *Criar um ficheiro em formato CSV (compatível com Excel), contendo para cada mês em que há compras registadas, o número de compras realizadas e o número total de clientes que realizaram tais compras, satisfazendo assim o formato final exemplo (com linha de cabeçalho):
 "Mês","#Compras","#Clientes"
 "1","35080","12010"
 "2","22670","10190"
 ....
 "12","56769","17310"
 **/
void querie11( Accounting acBook , ClientProductLinker cplClient ){
  int monthQ;
  char fileName[MAX_FILENAME];
  char* pos;
  FILE * fp;
  clock_t start , end;
  monthQ = 1;
  system("clear");
  head();
  printf("Criar ficheiro CSV com o número de compras realizadas e número total de clientes que realizaram compras para cada mês.\n\n");
  printf("Insira o nome do ficheiro a ser escrito:\n");
  fgets(fileName, MAX_FILENAME, stdin);
  if ((pos=strchr(fileName, '\n')) != NULL){
    *pos = '\0';
  }
  start = clock();
  fp = fopen (fileName, "w");
  fprintf( fp, "\"Mes\",\"#Compras\",\"#Clientes\"\n");
  printf( "\"Mes\",\"#Compras\",\"#Clientes\"\n");
  for( ; monthQ <=  12; monthQ++ ){
    fprintf( fp , "\"%d\",\"%d\",\"%d\"\n", monthQ, getMonthSales(acBook, monthQ ) , getCPLinkerMonthSize ( cplClient , monthQ ) );
    printf("\"%d\",\"%d\",\"%d\"\n", monthQ, getMonthSales(acBook, monthQ ) , getCPLinkerMonthSize ( cplClient , monthQ ) );
  }
  fclose(fp);
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 11" , start, end );
}

/**
 *QUERIE 12
 *Criar uma lista dos N produtos mais vendidos em todo o ano, indicando o número total de clientes e o número de unidades vendidas;
 **/
void querie12( SalesProductLinker splProd , List listStrings ){
  int nProd;
  char internalOption[MAX_LINE_OPTION];
  char *pos;
  clock_t start , end;
  system("clear");
  head();
  printf("Lista de N produtos mais vendidos em todo o ano bem como o total de clientes que o comprou e número de unidades vendidas.\n\n");
  printf("Insira o numero de consultas que quer ver:\n");
  fgets(internalOption, MAX_LINE_OPTION, stdin);
  if ((pos=strchr(internalOption, '\n')) != NULL){
    *pos = '\0';
  }
  nProd = atoi ( internalOption );
  start = clock();
  listStrings = getTopNMostSoldProducts__LL_STRINGS ( splProd , nProd );
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 12" , start, end );
  handleStrings ( listStrings , "lista dos N produtos mais vendidos em todo o ano" );
}

/**
 *QUERIE 13
 *Dado um código de cliente determinar quais os 3 produtos que mais comprou durante o ano;
 **/
void querie13( ClientProductLinker cplClient , List listStrings ){
  char codCliente[CLIENT_STRING_SIZE];
  char* pos;
  clock_t start , end;
  system("clear");
  head();
  printf("Lista os 3 produtos mais comprados por um determinado cliente durante o ano.\n\n");
  printf("Insira um codigo de um cliente valido:\n");
  fgets(codCliente, CLIENT_STRING_SIZE, stdin);
  if ((pos=strchr(codCliente, '\n')) != NULL){
    *pos = '\0';
  }
  start = clock();
  listStrings = getClientTopNMostBoughtProducts__LL_STRINGS ( cplClient , ensureUpper( codCliente ) , 3 );
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 13" , start, end );
  handleStrings ( listStrings , "3 produtos mais comprados do cliente durante o ano" );
}

/**
 *QUERIE 14
 *Determinar o número de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou;
 **/
void querie14( SalesProductLinker splProd , ClientProductLinker cplClient , ProductCatalog prCat , ClientCatalog clCat , List listStrings ){
  clock_t start , end;
  system("clear");
  head();
  start = clock();
  printf("Número de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou.\n\n");
  listStrings = getProductsWhoWereNeverBought__LL_STRINGS ( splProd ,  prCat );
  printf("Número de produtos que ninguém comprou: %d\n", sizeLL ( listStrings ));
  printf( "Número de clientes registados que não realizaram compras: %d\n" ,   getTotalClientsNumberWhoNeverBoughtProducts ( cplClient, clCat ) );
  end = clock();
  logStats ( "statistics.csv" , "QUERIE 14" , start, end );
}

void navegar( ProductCatalog prCat , ClientCatalog clCat, Accounting acBook , SalesProductLinker splProd , ClientProductLinker cplClient , List listStrings ){
  int firstTime , flagEXIT;
  char readedLine[MAX_LINE_OPTION];
  char *pos;
  flagEXIT = 0;
  firstTime = 1;

  do{
    if ( firstTime == 0 ){
      printf("Pressione qualquer tecla para continuar!\n");
      getchar();
    }
    firstTime = 0;
    head();
    menu();
    if( flagBlockedContent == 1 ){
      printf ( "\nA opção que escolheu encontra-se bloqueada. Atente na nota localizada abaixo da opção.\n");
      flagBlockedContent = 0;
    }
    printf("\nEscolha uma opção:\n");
    fgets(readedLine, 256, stdin);
    if ((pos=strchr(readedLine, '\n')) != NULL){
      *pos = '\0';
    }
    if ( strcmp ( readedLine , "1" ) == 0 ){
      querie1( prCat , clCat, acBook , splProd , cplClient );

    }
    if ( strcmp ( readedLine , "2" ) == 0 ){
      if ( flagReadedProducts ){
        querie2( prCat , listStrings );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "3" ) == 0 ){
      if ( flagReadedSales ){
        querie3( splProd );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "4" ) == 0 ){
      if ( flagReadedSales ){
        querie4( splProd , prCat , listStrings );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "5" ) == 0 ){
      if ( flagReadedSales ){
        querie5( cplClient , listStrings );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "6" ) == 0 ){
      if ( flagReadedClients ){
        querie6( clCat , listStrings );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "7" ) == 0 ){
      if ( flagReadedSales ){
        querie7( acBook );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "8" ) == 0 ){

      if ( flagReadedSales ){
        querie8( splProd , listStrings );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "9" ) == 0 ){

      if ( flagReadedSales ){
        querie9( cplClient , listStrings );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "10" ) == 0 ){
      if ( flagReadedSales ){
        querie10( cplClient , clCat , listStrings );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "11" ) == 0 ){
      if ( flagReadedSales ){
        querie11( acBook , cplClient  );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "12" ) == 0 ){
      if ( flagReadedSales ){
        querie12( splProd , listStrings );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "13" ) == 0 ){
      if ( flagReadedSales ){
        querie13( cplClient , listStrings );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "14" ) == 0 ){
      if ( flagReadedSales ){
        querie14( splProd , cplClient , prCat , clCat , listStrings );
      }
      else {
        flagBlockedContent = 1;
      }
    }
    if ( strcmp ( readedLine , "15" ) == 0 ){
      flagEXIT = 1;
    }
  }while ( flagEXIT == 0 );
}

int main (int argc, char *argv[] ){
  Accounting acBook;
  ClientCatalog clCat;
  ProductCatalog prCat;
  SalesProductLinker splProd;
  ClientProductLinker cplClient;
  List listStrings;
  listStrings = NULL;
  acBook = newAccounting();
  clCat = newClientCatalog();
  prCat = newProductCatalog();
  splProd = newSalesProductLinker ();
  cplClient = newClientProductLinker ();
  initAccounting (acBook);
  navegar( prCat , clCat, acBook , splProd , cplClient , listStrings );
  return 0;
}

