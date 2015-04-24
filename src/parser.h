/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _PARSER_H_INCLUDED_
#define _PARSER_H_INCLUDED_

/* QUERIE 1 - leitura ficheiro de compras */
int readFileClients ( char* , ClientCatalog , int* );

/* QUERIE 1 - leitura ficheiro de produtos */
int readFileProducts ( char* , ProductCatalog , int* );

/* QUERIE 1 - leitura ficheiro de vendas */
int readFileSales ( char* , Accounting , ClientCatalog , ProductCatalog, SalesProductLinker ,  ClientProductLinker , int*  , int* );

#endif /* _PARSER_H_INCLUDED_ */

