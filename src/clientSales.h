/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _CLIENT_SALES_H_INCLUDED_
#define _CLIENT_SALES_H_INCLUDED_

typedef struct clientSales* ClientSales;

/* retorna um novo ClientSales já com o nome de cliente associado */
ClientSales newClientSales ( char* ClientCode );

/* retorna o númeo de unidades vendidas do ClientSales */
int getClientSalesUnitsSold ( ClientSales );

/* adiciona unidades ao ClientSales */
ClientSales addUnitClientSales (  ClientSales , int );

/* compara dois ClientSales */
int equalsClientSales ( void* , void* );

/* elimina ClientSales */
void deleteClientSales ( void* );

/* retorna toString do ClientSales */
void* toStringClientSales ( void* );

#endif /* _CLIENT_SALES_H_INCLUDED_ */

