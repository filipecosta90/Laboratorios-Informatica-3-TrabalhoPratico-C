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

int getNumberClients ( Month );

void addSales ( Month , int );

void addClients ( Month, int );

#endif /* _MONTH_H_INCLUDED_ */

