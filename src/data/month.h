/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _MONTH_H_INCLUDED_
#define _MONTH_H_INCLUDED_

typedef struct month* Month;

void initMonth ( void );

int getNumberSales ( void );

int getNumberClients ( void );

void addSales ( int sales );

void addClients ( int clients );

#endif /* _MONTH_H_INCLUDED_ */

