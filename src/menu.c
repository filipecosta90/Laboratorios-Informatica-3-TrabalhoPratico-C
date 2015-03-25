#include <stdio.h>
#include <stdlib.h>

void menu(){
    printf("-----------GESTHIPER-----------\n\n");
    printf("1-Listar produtos começados por uma determinada letra.\n");
    printf("2-Listar as vendas (Normais e Promoções) de um determinado produto num dado mês\n");
    printf("3-Listar códigos de produtos (e o seu número total), que ninguém comprou.\n");
    printf("4-Tabela de produtos comprados (mês a mês) de um dado cliente.\n");
    printf("5-Listar clientes cujo código começa por uma determinada letra.\n");
    printf("6-Tabela de produtos comprados (mês a mês) de um dado cliente.\n");
    printf("7-Listar compras registadas e total faturado num dado intervalo de tempo.\n");
    printf("8-Listar clientes (e numero total) que compraram um determinado produto (Normais e Promoções).\n");
    printf("9-Listar por ordem descendente os produtos que um determinado cliente comprou num dado mês\n");
    printf("10-Listar clientes que realizaram compras em todos os meses do ano.\n");
    printf("11-Criar ficheiro CSV com o número de compras realizadas e número total de clientes que realizaram compras para cada mês.\n");
    printf("12-Listar N produtos mais vendidos em todo o ano bem como o total de clientes que o comprou e número de unidades vendidas.\n");
    printf("13-Listar os 3 produtos mais comprados por um determinado cliente durante o ano.\n");
    printf("14-Listar clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou.\n");
    printf("\n15-Sair\n");  
}

int main(){
  int op;
  char letra;
  char cod_prod[6],cod_cli[5];
  int mes, mes_ini, mes_fin,aux=0; 
  menu();
  printf("\nIntroduza uma opção válida:\n");
  while(op!=15){
    scanf("%d",&op);
    system("clear");
    if (aux==1)   printf("Introduza uma opção válida\n\n");
    if(op>0){
      switch(op) {
        case 1 : 
          system("clear");
          printf("Listar produtos começados por uma determinada letra.\n");
          printf("Insira uma letra: ");
          scanf("%c",&letra);
          printf("%c",letra );
          break;
        case 2 :
          system("clear");
          printf("Listar as vendas (Normais e Promoções) de um determinado produto num dado mês\n");
          printf("Insira um codigo de um poduto valido: ");
          scanf("%s",cod_prod);
          printf("%s\n",cod_prod);
          printf("\nInsira um mês: ");
          scanf("%d",&mes);
          printf("%d\n",mes);
          break;
        case 3 :
          system("clear");
          printf("Lista códigos de produtos (e o seu número total), que ninguém comprou.\n");
          break;
        case 4 :
          system("clear");
          printf("Tabela de produtos comprados (mês a mês) de um dado cliente.\n");
          printf("Insira um codigo de um cliente valido: ");
          scanf("%s",cod_cli);
          printf("%s\n",cod_cli);
          break;
        case 5 : 
          system("clear");
          printf("Listar clientes cujo código começa por uma determinada letra.\n");
          printf("Insira uma letra: ");
          scanf("%c",&letra);
          printf("%c",letra );
          break;
        case 6 :
          system("clear");
          printf("Tabela de produtos comprados (mês a mês) de um dado cliente.\n");
          printf("Insira um codigo de um cliente valido: ");
          scanf("%s",cod_cli);
          printf("%s\n",cod_cli);
          break;
        case 7 :
          system("clear");
          printf("Lista compras registadas e total faturado num dado intervalo de tempo.\n");
          printf("Insira um intervalo de mêses (Ex: 2 4): ");
          scanf("%d %d",&mes_ini,&mes_fin);
          printf("[%d-%d]",mes_ini,mes_fin);
          break;
        default : aux=1;
          break;
      }
    }
    else{
      aux=1;
    }
  }
}