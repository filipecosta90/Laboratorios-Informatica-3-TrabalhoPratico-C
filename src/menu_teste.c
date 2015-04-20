#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME 64
#define STANDARD_PRODUCT_FILENAME "../files/FichProdutos.txt"
#define STANDARD_CLIENT_FILENAME "../files/FichClientes.txt"
#define STANDARD_SALES_FILENAME "../files/Compras.txt"

static char letra;
static char cod_prod[6];
static char cod_cli[5];
static int mes,mes_ini,mes_fin,N;
static int flagReadedClients, flagReadedProducts, flagReadedSales, flagBlockedContent;

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

void readProductsFile(){
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
          flagReadedProducts = 1;
          break;
        case 2 :
          printf("Insira o nome do ficheiro a ser lido:\n");
          scanf("%s",fileName);
          printf("%s\n",fileName);
          flagReadedProducts = 1;
          break;
          /* Back one level */
        default :
          break;
      }
    }
  }
}

void readClientsFile(){
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
          flagReadedClients = 1;
          break;
        case 2 :
          printf("Insira o nome do ficheiro a ser lido:\n");
          scanf("%s",fileName);
          printf("%s\n",fileName);
          flagReadedClients = 1;
          break;
          /* Back one level */
        default :
          break;
      }
    }
  }
}

void readSalesFile () {
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
          flagReadedSales = 1;
          break;
        case 2 :
          printf("Insira o nome do ficheiro a ser lido:\n");
          scanf("%s",fileName);
          printf("%s\n",fileName);
          flagReadedSales = 1;
          break;
          /* Back one level */
        default :
          break;
      }
    }
  }
}

void querie1(){
  int opInternal;
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
    printf("\n4-Voltar ao menu anterior.\n");
    printf("\nEscolha uma opção:\n");
    scanf("%d",&opInternal);
    system("clear");
    if(opInternal>0){
      switch(opInternal) {
        case 1 : readProductsFile();
                 break;
        case 2 : readClientsFile();
                 break;
        case 3 :
                 if ( flagReadedProducts && flagReadedClients ){
                   readSalesFile();
                 }
                 else {
                   flagBlockedContent = 1;
                 }
                 break;
                 /* Back to top */
        default :
                 break;
      }
    }
  }
}

void querie2(){
  system("clear");
  head();
  printf("Listar produtos começados por uma determinada letra.\n\n");
  printf("Insira uma letra: ");
  scanf("%c",&letra);
  printf("%c",letra);
}

void querie3(){
  system("clear");
  head();
  printf("Listar as vendas (Normais e Promoções) de um determinado produto num dado mês\n\n");
  printf("Insira um codigo de um produto valido e um mes:\n");
  scanf("%s %d",cod_prod,&mes);
  printf("%s %d\n",cod_prod,mes);
}

void querie4(){
  system("clear");
  head();
  printf("Lista códigos de produtos (e o seu número total), que ninguém comprou.\n\n");
}

void querie5(){
  system("clear");
  head();
  printf("Tabela de produtos comprados (mês a mês) de um dado cliente.\n\n");
  printf("Insira um codigo de um cliente valido:\n");
  scanf("%s",cod_cli);
  printf("%s\n",cod_cli);
}

void querie6(){
  system("clear");
  head();
  printf("Listar clientes cujo código começa por uma determinada letra.\n\n");
  printf("Insira uma letra: ");
  scanf("%c",&letra);
  printf("%c",letra );
}

void querie7(){
  system("clear");
  head();
  printf("Lista compras registadas e total faturado num dado intervalo de tempo.\n\n");
  printf("Insira um intervalo de mêses (Ex: 2 4):\n");
  scanf("%d %d",&mes_ini,&mes_fin);
  printf("[%d-%d]",mes_ini,mes_fin);
}

void querie8(){
  system("clear");
  head();
  printf("Lista de clientes (e numero total) que compraram um determinado produto (Normais e Promoções).\n\n");
  printf("Insira um codigo de um produto valido:\n");
  scanf("%s",cod_prod);
  printf("%s\n",cod_prod);
}

void querie9(){
  system("clear");
  head();
  printf("Lista por ordem descendente de produtos que um determinado cliente comprou num dado mês\n\n");
  printf("Insira um codigo de um cliente valido e um mês:\n");
  scanf("%s %d",cod_cli,&mes);
  printf("%s %d\n",cod_cli,mes);
}

void querie10(){
  system("clear");
  head();
  printf("Listar clientes que realizaram compras em todos os meses do ano.\n\n");
}

void querie11(){
  system("clear");
  head();
  printf("Criar ficheiro CSV com o número de compras realizadas e número total de clientes que realizaram compras para cada mês.\n\n");
}

void querie12(){
  system("clear");
  head();
  printf("Lista de N produtos mais vendidos em todo o ano bem como o total de clientes que o comprou e número de unidades vendidas.\n\n");
  printf("Insira o numero de consultas que quer ver:\n");
  scanf("%d",&N);
  printf("%d\n",N);
}

void querie13(){
  system("clear");
  head();
  printf("Lista os 3 produtos mais comprados por um determinado cliente durante o ano.\n\n");
  printf("Insira um codigo de um cliente valido:\n");
  scanf("%s",cod_cli);
  printf("%s\n",cod_cli);
}

void querie14(){
  system("clear");
  head();
  printf("Lista de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou.\n\n");
}

void navegar(){
  int op;
  while(op!=15){
    head();
    menu();
    if( flagBlockedContent == 1 ){
      printf ( "\nA opção que escolheu encontra-se bloqueada. Atente na nota localizada abaixo da opção.\n");
      flagBlockedContent = 0;
    }
    printf("\nEscolha uma opção:\n");
    scanf("%d",&op);
    printf("%d\n", op);
    system("clear");
    if(op>0){
      switch(op) {
        case 1 :
          querie1();
          break;
        case 2 :
          if ( flagReadedProducts ){
            querie2();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 3 :
          if ( flagReadedSales ){
            querie3();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 4 :
          if ( flagReadedSales ){
            querie4();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
          break;
        case 5 :
          if ( flagReadedSales ){
            querie5();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 6 :
          if ( flagReadedClients ){
            querie6();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 7 :
          if ( flagReadedSales ){
            querie7();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 8 :
          if ( flagReadedSales ){
            querie8();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 9 :
          if ( flagReadedSales ){
            querie9();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 10 :
          if ( flagReadedSales ){
            querie10();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 11 :
          if ( flagReadedSales ){
            querie11();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 12 :
          if ( flagReadedSales ){
            querie12();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 13 :
          if ( flagReadedSales ){
            querie13();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        case 14 :
          if ( flagReadedSales ){
            querie14();
          }
          else {
            flagBlockedContent = 1;
          }
          break;
        default : //navegar();
          break;
      }
    }
  }
}

int main(){
  navegar();
  return 0;
}
