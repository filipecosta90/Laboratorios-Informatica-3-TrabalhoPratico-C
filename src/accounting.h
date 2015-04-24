/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _ACCOUNTING_H_INCLUDED_
#define _ACCOUNTING_H_INCLUDED_

typedef int type_of_month;

typedef struct accounting * Accounting;

/* retorna um novo modo de contabilidade */
Accounting newAccounting ( void );

/* (re)inicializa o módulo */
void initAccounting ( Accounting );

/* adiciona venda ao mês */
void addSale ( Accounting , type_of_month );

/* adiciona conta ao mês */
void addBill ( Accounting, type_of_month , float );

/* retorna o número de vendas registado no mês*/
int getMonthSales ( Accounting, type_of_month );

/* retorna o número de vendas registado no intervalo de meses */
int getIntervalTotalSales ( Accounting, type_of_month , type_of_month );

/* retorna o valor facturado registado no intervalo de meses */
float getIntervalTotalBilled ( Accounting, type_of_month , type_of_month );

void deleteAccounting ( Accounting );

#endif /* _ACCOUNTING_H_INCLUDED_ */

