/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _CLIENT_PRODUCT_LINKER_H_INCLUDED_
#define _CLIENT_PRODUCT_LINKER_H_INCLUDED_


typedef struct clientProductLinker*  ClientProductLinker;

struct clientProductLinker* newClientProductLinker ( );

void addSalesLineToCPL ( struct clientProductLinker* clientPrLinker , char* productCode, char* clientCode , int unitsSold , int month );

#endif /* _CLIENT_PRODUCT_LINKER_H_INCLUDED_ */

