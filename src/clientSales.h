/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */


#ifndef _CLIENT_SALES_H_INCLUDED_
#define _CLIENT_SALES_H_INCLUDED_

typedef char* ClientCode;

typedef struct clientSales*  ClientSales;

ClientSales newClientSales ( ClientCode );

int getClientSalesUnitsSold ( ClientSales );

ClientSales addUnitClientSales ( ClientSales , int );

int equalsClientSales ( void* , void* );

#endif /* _CLIENT_SALES_H_INCLUDED_ */
