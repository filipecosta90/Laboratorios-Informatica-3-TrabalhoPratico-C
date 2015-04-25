/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _MONTH_H_INCLUDED_
#define _MONTH_H_INCLUDED_

typedef struct month * Month;

/*retorna um novo Month */
Month newMonth( void );

/* inicializa o month */
void initMonth ( Month );

/* retorna o numero de vendas do mês */
int getNumberSales ( Month );

/* retorna o valor total faturado no mês */
float getTotalBilled ( Month );

/* adiciona venda(s) ao mês */
void addSales ( Month , int );

/* adiciona facturação ao mês */
void addBills ( Month , float );

/* elimina o mês */
void deleteMonth ( Month );

#endif /* _MONTH_H_INCLUDED_ */
