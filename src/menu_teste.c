#include <stdio.h>
#include <stdlib.h>

char letra;
char cod_prod[6];
char cod_cli[5];
int mes,mes_ini,mes_fin,N;

void head (){
	system("clear");
	printf(" _______  _______  _______ _________        _________ _______  _______  _______");
	printf("\n(  ____ \\(  ____ \\(  ____ \\\\__   __/|\\     /|\\__   __/(  ____ )(  ____ \\(  ____ )");
	printf("\n| (    \\/| (    \\/| (    \\/   ) (   | )   ( |   ) (   | (    )|| (    \\/| (    )|");
	printf("\n| |      | (__    | (_____    | |   | (___) |   | |   | (____)|| (__    | (____)|");
	printf("\n| | ____ |  __)   (_____  )   | |   |  ___  |   | |   |  _____)|  __)   |     __)");
	printf("\n| | \\_  )| (            ) |   | |   | (   ) |   | |   | (      | (      | (\\ (   ");
	printf("\n| (___) || (____/\\/\\____) |   | |   | )   ( |___) (___| )      | (____/\\| ) \\ \\__");
	printf("\n(_______)(_______/\\_______)   )_(   |/     \\|\\_______/|/       (_______/|/   \\__/\n\n\n");
}

void menu(){
    printf("1-Listar produtos começados por uma determinada letra e o seu total.\n");
    printf("2-Listar as vendas (Normais e Promoções) de um determinado produto num dado mês e o total faturado\n");
    printf("3-Listar códigos de produtos (e o seu número total), que ninguém comprou.\n");
    printf("4-Tabela de produtos comprados (mês a mês) de um dado cliente.\n");
    printf("5-Listar clientes cujo código começa por uma determinada letra.\n");
    printf("6-Listar compras registadas e total faturado num dado intervalo de tempo.\n");
    printf("7-Listar clientes (e numero total) que compraram um determinado produto (Normais e Promoções).\n");
    printf("8-Listar por ordem descendente os produtos que um determinado cliente comprou num dado mês\n");
    printf("9-Listar clientes que realizaram compras em todos os meses do ano.\n");
    printf("10-Criar ficheiro CSV com o número de compras realizadas e número total de clientes que realizaram compras para cada mês.\n");
    printf("11-Listar N produtos mais vendidos em todo o ano bem como o total de clientes que o comprou e número de unidades vendidas.\n");
    printf("12-Listar os 3 produtos mais comprados por um determinado cliente durante o ano.\n");
    printf("13-Listar clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou.\n");
    printf("\n14-Sair\n");
}

void querie1(){
	system("clear");
	head();
	printf("Listar produtos começados por uma determinada letra.\n\n");
	printf("Insira uma letra: ");
	scanf("%c",&letra);
	printf("%c",letra);
}

void querie2(){
	system("clear");
	head();
	printf("Listar as vendas (Normais e Promoções) de um determinado produto num dado mês\n\n");
	printf("Insira um codigo de um produto valido e um mes:\n");
	scanf("%s %d",cod_prod,&mes);
	printf("%s %d\n",cod_prod,mes);
}

void querie3(){
	system("clear");
	head();
	printf("Lista códigos de produtos (e o seu número total), que ninguém comprou.\n\n");
}

void querie4(){
	system("clear");
	head();
	printf("Tabela de produtos comprados (mês a mês) de um dado cliente.\n\n");
	printf("Insira um codigo de um cliente valido:\n");
	scanf("%s",cod_cli);
	printf("%s\n",cod_cli);
}

void querie5(){
	system("clear");
	head();
	printf("Listar clientes cujo código começa por uma determinada letra.\n\n");
	printf("Insira uma letra: ");
    scanf("%c",&letra);
    printf("%c",letra );
}


void querie6(){
	system("clear");
	head();
	printf("Lista compras registadas e total faturado num dado intervalo de tempo.\n\n");
	printf("Insira um intervalo de mêses (Ex: 2 4):\n");
	scanf("%d %d",&mes_ini,&mes_fin);
	printf("[%d-%d]",mes_ini,mes_fin);
}

void querie7(){
	system("clear");
	head();
    printf("Lista de clientes (e numero total) que compraram um determinado produto (Normais e Promoções).\n\n");
	printf("Insira um codigo de um produto valido:\n");
	scanf("%s",cod_prod);
	printf("%s\n",cod_prod);
}

void querie8(){
	system("clear");
	head();
    printf("Lista por ordem descendente de produtos que um determinado cliente comprou num dado mês\n\n");
	printf("Insira um codigo de um cliente valido e um mês:\n");
	scanf("%s %d",cod_cli,&mes);
	printf("%s %d\n",cod_cli,mes);
}

void querie9(){
	system("clear");
	head();
    printf("Listar clientes que realizaram compras em todos os meses do ano.\n\n");
}

void querie10(){
	system("clear");
	head();
    printf("Criar ficheiro CSV com o número de compras realizadas e número total de clientes que realizaram compras para cada mês.\n\n");
}

void querie11(){
	system("clear");
	head();
    printf("Lista de N produtos mais vendidos em todo o ano bem como o total de clientes que o comprou e número de unidades vendidas.\n\n");
    printf("Insira o numero de consultas que quer ver:\n");
    scanf("%d",&N);
	printf("%d\n",N);
}

void querie12(){
	system("clear");
	head();
    printf("Lista os 3 produtos mais comprados por um determinado cliente durante o ano.\n\n");
	printf("Insira um codigo de um cliente valido:\n");
	scanf("%s",cod_cli);
	printf("%s\n",cod_cli);
}

void querie13(){
	system("clear");
	head();
    printf("Lista de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou.\n\n");
}

void navegar(){
	int op;
	head();
	menu();
	printf("\nEscolha uma opção:\n");  
	while(op!=14){
		scanf("%d",&op);
		printf("%d\n", op);
		system("clear");
		if(op>0){
			switch(op) {
				case 1 : querie1(); 
					break;
				case 2 : querie2();
					break;
				case 3 : querie3();
					break;
				case 4 : querie4();
					break;
				case 5 : querie5();
					break;
				case 6 : querie6();
					break;
				case 7 : querie7();
					break;
				case 8 : querie8();
					break;
				case 9 : querie9();
					break;
				case 10 : querie10();
					break;
				case 11 : querie11();
					break;
				case 12 : querie12();
					break;
				case 13 : querie13();
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