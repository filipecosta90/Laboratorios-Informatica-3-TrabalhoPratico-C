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

#define MAX_FILENAME 64
#define STANDARD_PRODUCT_FILENAME "../files/FichProdutos.txt"
#define STANDARD_CLIENT_FILENAME "../files/FichClientes.txt"
#define STANDARD_SALES_FILENAME "../files/Compras.txt"

static char letra;
static char cod_prod[6];
static char cod_cli[5];
static int mes,mes_ini,mes_fin,N;
static int flagReadedClients, flagReadedProducts, flagReadedSales, flagBlockedContent;

void handleStrings ( List strings ){
  char* handler;
  handler = NULL;
  while ( sizeLL (strings) > 0 ){
    handler = headLL ( strings );
    printf( "%s" , handler );
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
  printf("14-Listar clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou.\n");
  printf("15-Sair\n");
}

void menuReadProductsFile( ProductCatalog prCat , int errorReadingProducts , int flagReadingProducts ){
  int opInternal;
  char fileName[MAX_FILENAME];
  opInternal = 0;
  while(opInternal!=3){
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
    scanf("%d",&opInternal);
    system("clear");
    if(opInternal>0){
      switch(opInternal) {
        case 1 :
          flagReadingProducts = readFileProducts ( STANDARD_PRODUCT_FILENAME , prCat , &errorReadingProducts );
          flagReadedProducts = 1;
          break;
        case 2 :
          printf("Insira o nome do ficheiro a ser lido:\n");
          scanf("%s",fileName);
          printf("%s\n",fileName);
          flagReadingProducts = readFileProducts ( fileName , prCat , &errorReadingProducts );
          flagReadedProducts = 1;
          break;
          /* Back one level */
        default :
          break;
      }
    }
  }
}

void menuReadClientsFile( ClientCatalog clCat , int errorReadingClients , int flagReadingClients ){
  int opInternal;
  char fileName[MAX_FILENAME];
  opInternal = 0;
  while(opInternal!=3){
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
    scanf("%d",&opInternal);
    system("clear");
    if(opInternal>0){
      switch(opInternal) {
        case 1 :
          flagReadingClients = readFileClients ( STANDARD_CLIENT_FILENAME , clCat , &errorReadingClients );
          flagReadedClients = 1;
          break;
        case 2 :
          printf("Insira o nome do ficheiro a ser lido:\n");
          scanf("%s",fileName);
          printf("%s\n",fileName);
          flagReadingClients = readFileClients ( fileName , clCat , &errorReadingClients );
          flagReadedClients = 1;
          break;
          /* Back one level */
        default :
          break;
      }
    }
  }
}

void menuReadSalesFile ( Accounting acBook , ClientCatalog clCat , ProductCatalog prCat , SalesProductLinker splProd , ClientProductLinker cplClient , int errorReadingClients, int errorReadingProducts, int flagReadingSales  ) {
  int opInternal;
  char fileName[MAX_FILENAME];
  opInternal = 0;
  while(opInternal!=3){
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
    scanf("%d",&opInternal);
    system("clear");
    if(opInternal>0){
      switch(opInternal) {
        case 1 :
          flagReadingSales = readFileSales( STANDARD_SALES_FILENAME , acBook , clCat , prCat , splProd , cplClient , &errorReadingProducts , &errorReadingClients );
          flagReadedSales = 1;
          break;
        case 2 :
          printf("Insira o nome do ficheiro a ser lido:\n");
          scanf("%s",fileName);
          flagReadingSales = readFileSales( fileName , acBook , clCat , prCat , splProd , cplClient , &errorReadingProducts , &errorReadingClients );
          flagReadedSales = 1;
          break;
          /* Back one level */
        default :
          break;
      }
    }
  }
}

/* *
 * QUERIE 1
 * Ler os 3 ficheiros (Produtos, Clientes e Compras), cujos nomes poderão ser introduzidos pelo utilizador ou, opcionalmente, assumidos por omissão.
 * O resultado desta leitura deverá ser a apresentação imediata ao utilizador do nome do ficheiro lido e o número total de linhas lidas e validadas.
 * Uma nova leitura destes ficheiros deverá de imediato reiniciar e refazer as estruturas de dados em memória;
 * */
void querie1( ProductCatalog prCat , ClientCatalog clCat, Accounting acBook , SalesProductLinker splProd , ClientProductLinker cplClient , int* errorReadingProducts , int* flagReadingProducts , int *errorReadingClients, int *flagReadingClients , int* flagReadingSales ){
  int opInternal;
  opInternal = 0;
  while(opInternal!=4){
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
    scanf("%d",&opInternal);
    system("clear");
    if(opInternal>0){
      switch(opInternal) {
        case 1 :
          menuReadProductsFile( prCat , *errorReadingProducts, *flagReadingProducts );
          break;
        case 2 :
          menuReadClientsFile( clCat , *errorReadingClients, *flagReadingClients );
          break;
        case 3 :
          if ( flagReadedProducts && flagReadedClients ){
            menuReadSalesFile( acBook , clCat , prCat , splProd , cplClient , *errorReadingClients , *errorReadingProducts , *flagReadingSales );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 4 :
          *flagReadingProducts = readFileProducts ( STANDARD_PRODUCT_FILENAME , prCat , errorReadingProducts );
          flagReadedProducts = 1;
          *flagReadingClients = readFileClients ( STANDARD_CLIENT_FILENAME , clCat , errorReadingClients );
          flagReadedClients = 1;
          *flagReadingSales = readFileSales( STANDARD_SALES_FILENAME , acBook , clCat , prCat , splProd , cplClient , errorReadingProducts , errorReadingClients );
          flagReadedSales = 1;
          break;
          /* Back to top */
        default :
          break;
      }
    }
  }
}

/* *
 * QUERIE 2
 * Determinar a lista e o total de produtos cujo código se inicia por uma dada letra (maiúscula);
 * Apresentar tal lista ao utilizador e permitir que o mesmo navegue na mesma, sendo tal lista apresentada por ordem alfabética;
 * */
void querie2( ProductCatalog prCat , List listStrings ){
  system("clear");
  head();
  printf("Listar produtos começados por uma determinada letra.\n\n");
  printf("Insira uma letra: ");
  scanf("%c",&letra);
  listStrings = getProductsByLetter__LL_strings ( prCat , letra );
  handleStrings ( listStrings );
}

/* *
 * QUERIE 3
 * Dado um mês e um código de produto válidos, determinar e apresentar o número total de vendas em modo N e em modo P, e o total facturado com esse produto em tal mês ;
 * */
void querie3( SalesProductLinker splProd ){
  float totalBilled;
  int normalSales, promotionSales;
  normalSales = 0;
  promotionSales = 0;
  totalBilled = 0.0;
  system("clear");
  head();
  printf("Apresentar o número total de vendas em modo N e em modo P, e o total facturado de um produto num dado mês\n\n");
  printf("Insira um código de um produto valido:\n");
  scanf( "%s" , cod_prod );
  printf("Insira um mês válido:\n");
  scanf( "%d" , &mes);
  promotionSales =  getPromotionClientsNumberWhoBoughtProductInMonth ( splProd , cod_prod , mes );
  normalSales = getNormalClientsNumberWhoBoughtProductInMonth ( splProd , cod_prod , mes );
  totalBilled = getTotalBilledByProductInMonth ( splProd , cod_prod , mes );
  printf ( " Detalhes de vendas de código de produto %s para o mês %d\n\t Número de vendas N: %d\tvendas T, %d\n\tTotal faturado:%f\n", cod_prod , mes, normalSales , promotionSales , totalBilled );
}

/**
 *QUERIE 4
 *Determinar a lista de códigos de produtos (e o seu número total), que ninguém comprou;
 **/
void querie4( SalesProductLinker splProd , ProductCatalog prCat , List listStrings ){
  system("clear");
  head();
  printf("Lista códigos de produtos (e o seu número total), que ninguém comprou.\n\n");
  listStrings = getProductsWhoWereNeverBought__LL_STRINGS ( splProd ,  prCat );
  printf( "Número total de produtos que ninguém comprou: %d\n", sizeLL ( listStrings ));
  handleStrings ( listStrings );
}

/**
 *QUERIE 5
 *Dado um código de cliente, criar uma tabela com o número total de produtos comprados, mês a mês (para meses em que não comprou a entrada deverá ficar a 0). 
 *A tabela deverá ser apresentada em ecrã. O utilizador deverá ter a opção de guardar tal tabela num ficheiro de texto;
 **/
void querie5( ClientProductLinker cplClient , List listStrings ){
  char guardar;
  char fileName[MAX_FILENAME];
  system("clear");
  head();
  printf("Tabela de produtos comprados (mês a mês) de um dado cliente.\n\n");
  printf("Insira um codigo de um cliente valido:\n");
  scanf("%s",cod_cli);
  listStrings = getClientProductTableByMonth__LL_STRINGS ( cplClient , cod_cli );
  handleStrings ( listStrings );
  printf("Pretende guardar a tabela num ficheiro de texto? (s/n)\n");
  scanf("%c",&guardar);
  if ( guardar == 'S' || guardar == 's' ){
    printf("Indique o nome do ficheiro:\n");
    scanf ("%s", fileName);
    handleStringsToFile( listStrings , fileName);
  }
}

/**
 *QUERIE 6
 *Determinar a lista de todos os códigos de clientes iniciados pela letra dada como parâmetro (maiúscula ou minúscula deverá ser indiferente);
 **/
void querie6( ClientCatalog clCat , List listStrings ){
  system("clear");
  head();
  printf("Listar clientes cujo código começa por uma determinada letra.\n\n");
  printf("Insira uma letra: ");
  scanf("%c",&letra);
  listStrings = getClientsByLetter__LL_strings ( clCat , letra );
  handleStrings ( listStrings );
}

/**
 *QUERIE 7
 *Dado um intervalo fechado de meses, por exemplo [2..6], determinar o total de compras registadas nesse intervalo e o total facturado;
 **/
void querie7( Accounting acBook ){
  system("clear");
  head();
  printf("Lista compras registadas e total faturado num dado intervalo de tempo.\n\n");
  printf("Insira um intervalo de mêses (Ex: 2 4):\n");
  scanf("%d %d",&mes_ini,&mes_fin);
  printf("Número total de vendas no invervalo[%d-%d]: %d\n", mes_ini , mes_fin , getIntervalTotalSales( acBook, mes_ini, mes_fin ));
  printf("Total facturado no invervalo[%d-%d]: %f\n", mes_ini , mes_fin , getIntervalTotalBilled( acBook, mes_ini, mes_fin));
}

/**
 *QUERIE 8
 *Dado um código de produto, determinar os códigos (e número total) dos clientes que o compraram, distinguido entre compra N e compra P;
 **/
void querie8( SalesProductLinker splProd , List listStrings ){
  system("clear");
  head();
  printf("Lista de clientes (e numero total) que compraram um determinado produto (Normais e Promoções).\n\n");
  printf("Insira um codigo de um produto valido:\n");
  scanf("%s",cod_prod);
  listStrings = getNormalClientsWhoBoughtProduct__LL_STRINGS  ( splProd , cod_prod );
  printf("Número total de clientes que compraram %s em modo normal: %d\n", cod_prod, sizeLL ( listStrings ));
  handleStrings ( listStrings );
  listStrings = getPromotionClientsWhoBoughtProduct__LL_STRINGS  ( splProd , cod_prod );
  printf("Número total de clientes que compraram %s em modo promocional: %d\n", cod_prod, sizeLL ( listStrings ));
  handleStrings ( listStrings );
}

/**
 *QUERIE 9
 *Dado um código de cliente e um mês, determinar a lista de códigos de produtos que mais comprou, por ordem descendente;
 **/
void querie9( ClientProductLinker cplClient , List listStrings ){
  system("clear");
  head();
  printf("Lista por ordem descendente de produtos que um determinado cliente comprou num dado mês\n\n");
  printf("Insira um codigo de um cliente valido:\n");
  scanf("%s",cod_cli);
  printf("Insira um mês valido:\n");
  scanf ( "%d",&mes );
  listStrings = getClientOrderedProductListOfMonth__LL_STRINGS ( cplClient , cod_cli , mes );
  handleStrings ( listStrings );
}

/**
 *QUERIE 10
 *Determinar a lista de códigos de clientes que realizaram compras em todos os meses do ano;
 **/
void querie10( ClientProductLinker cplClient , ClientCatalog clCat , List listStrings ){
  system("clear");
  head();
  printf("Listar clientes que realizaram compras em todos os meses do ano.\n\n");
  listStrings = getClientsWhoBoughtEveryMonth__LL_STRINGS ( cplClient, clCat );
  printf("Número de clientes que realizaram compras em todos os meses do ano: %d\n", sizeLL ( listStrings ));
  handleStrings ( listStrings );
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
  FILE * fp;
  monthQ = 1;
  system("clear");
  head();
  printf("Criar ficheiro CSV com o número de compras realizadas e número total de clientes que realizaram compras para cada mês.\n\n");
  printf("Insira o nome do ficheiro a ser escrito:\n");
  scanf("%s",fileName);
  fp = fopen (fileName, "w");
  fprintf( fp, "\"Mes\",\"#Compras\",\"#Clientes\"\n");
  printf( "\"Mes\",\"#Compras\",\"#Clientes\"\n");
  for( ; monthQ <=  12; monthQ++ ){
    fprintf( fp , "\"%d\",\"%d\",\"%d\"\n", monthQ, getMonthSales(acBook, monthQ ) , getCPLinkerMonthSize ( cplClient , monthQ ) );
    printf("\"%d\",\"%d\",\"%d\"\n", monthQ, getMonthSales(acBook, monthQ ) , getCPLinkerMonthSize ( cplClient , monthQ ) );
  }
  fclose(fp);
}

/**
 *QUERIE 12
 *Criar uma lista dos N produtos mais vendidos em todo o ano, indicando o número total de clientes e o número de unidades vendidas;
 **/
void querie12( SalesProductLinker splProd , List listStrings ){
  system("clear");
  head();
  printf("Lista de N produtos mais vendidos em todo o ano bem como o total de clientes que o comprou e número de unidades vendidas.\n\n");
  printf("Insira o numero de consultas que quer ver:\n");
  scanf("%d",&N);
  listStrings = getTopNMostSoldProducts__LL_STRINGS ( splProd , N );
  handleStrings ( listStrings );
}

/**
 *QUERIE 13
 *Dado um código de cliente determinar quais os 3 produtos que mais comprou durante o ano;
 **/
void querie13( ClientProductLinker cplClient , List listStrings ){
  system("clear");
  head();
  printf("Lista os 3 produtos mais comprados por um determinado cliente durante o ano.\n\n");
  printf("Insira um codigo de um cliente valido:\n");
  scanf("%s",cod_cli);
  listStrings = getClientTopNMostBoughtProducts__LL_STRINGS ( cplClient , cod_cli , 3 );
  handleStrings ( listStrings );
}

/**
 *QUERIE 14
 *Determinar o número de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou;
 **/
void querie14( SalesProductLinker splProd , ClientProductLinker cplClient , ProductCatalog prCat , ClientCatalog clCat , List listStrings ){
  system("clear");
  head();
  printf("Número de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou.\n\n");
  listStrings = getProductsWhoWereNeverBought__LL_STRINGS ( splProd ,  prCat );
  printf("Número de produtos que ninguém comprou: %d\n", sizeLL ( listStrings ));
  printf( "Número de clientes registados que não realizaram compras: %d\n" ,   getTotalClientsNumberWhoNeverBoughtProducts ( cplClient, clCat ) );
}

void navegar( ProductCatalog prCat , ClientCatalog clCat, Accounting acBook , SalesProductLinker splProd , ClientProductLinker cplClient , int* errorReadingProducts , int* flagReadingProducts , int *errorReadingClients, int *flagReadingClients , int* flagReadingSales , List listStrings ){
  int op;
  op = 0;
  while(op!=15){
    head();
    menu();
    if( flagBlockedContent == 1 ){
      printf ( "\nA opção que escolheu encontra-se bloqueada. Atente na nota localizada abaixo da opção.\n");
      flagBlockedContent = 0;
    }
    printf("\nEscolha uma opção:\n");
    scanf("%d",&op);
    if(op>0){
      switch(op) {
        case 1 :
          querie1( prCat , clCat, acBook , splProd , cplClient , errorReadingProducts , flagReadingProducts , errorReadingClients, flagReadingClients, flagReadingSales );
          break;
        case 2 :
          if ( flagReadedProducts ){
            querie2( prCat , listStrings );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 3 :
          if ( flagReadedSales ){
            querie3( splProd );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 4 :
          if ( flagReadedSales ){
            querie4( splProd , prCat , listStrings );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 5 :
          if ( flagReadedSales ){
            querie5( cplClient , listStrings );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 6 :
          if ( flagReadedClients ){
            querie6( clCat , listStrings );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 7 :
          if ( flagReadedSales ){
            querie7( acBook );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 8 :
          if ( flagReadedSales ){
            querie8( splProd , listStrings );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 9 :
          if ( flagReadedSales ){
            querie9( cplClient , listStrings );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 10 :
          if ( flagReadedSales ){
            querie10( cplClient , clCat , listStrings );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 11 :
          if ( flagReadedSales ){
            querie11( acBook , cplClient  );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 12 :
          if ( flagReadedSales ){
            querie12( splProd , listStrings );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 13 :
          if ( flagReadedSales ){
            querie13( cplClient , listStrings );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 14 :
          if ( flagReadedSales ){
            querie14( splProd , cplClient , prCat , clCat , listStrings );
          }
          else {
            flagBlockedContent = 1;
          }
          break;
          /* exit */
        default :
          break;
      }
    }
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
  navegar( prCat , clCat, acBook , splProd , cplClient , &errorReadingProducts , &flagReadingProducts , &errorReadingClients, &flagReadingClients , &flagReadingSales , listStrings );
  return 0;
}

