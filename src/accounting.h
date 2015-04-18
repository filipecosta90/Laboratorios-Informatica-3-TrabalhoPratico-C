/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _ACCOUNTING_H_INCLUDED_
#define _ACCOUNTING_H_INCLUDED_

typedef int type_of_month;

typedef struct accounting * Accounting;

Accounting newAccounting ( void );

void initAccounting ( Accounting );

void addSale ( Accounting , type_of_month );

void addClient ( Accounting , type_of_month );

void addBill ( Accounting, type_of_month , float );

int getMonthSales ( Accounting, type_of_month );

int getIntervalTotalSales ( Accounting, type_of_month , type_of_month );

float getIntervalTotalBilled ( Accounting, type_of_month , type_of_month );

void deleteAccounting ( Accounting );

#endif /* _ACCOUNTING_H_INCLUDED_ */

