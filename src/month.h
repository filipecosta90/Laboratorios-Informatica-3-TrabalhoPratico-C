/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _MONTH_H_INCLUDED_
#define _MONTH_H_INCLUDED_

typedef struct month * Month;

Month newMonth( void );

void initMonth ( Month );

int getNumberSales ( Month );

float getTotalBilled ( Month );

void addSales ( Month , int );

void addBills ( Month , float );

void deleteMonth ( Month );

#endif /* _MONTH_H_INCLUDED_ */
