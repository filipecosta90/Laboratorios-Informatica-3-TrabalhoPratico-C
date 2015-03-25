/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _PARSER_H_INCLUDED_
#define _PARSER_H_INCLUDED_

int readFileSales ( char* , Accounting , ClientCatalog , int* , ProductCatalog , int* );

int readFileClients ( char* , ClientCatalog , int* );

int readFileProducts ( char* , ProductCatalog , int* );

#endif /* _PARSER_H_INCLUDED_ */

