/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */


#ifndef _PARSER_H_INCLUDED_
#define _PARSER_H_INCLUDED_

int readFileSales ( char* , Accounting , ClientCatalog , ProductCatalog );

int readFileClients ( char* , ClientCatalog );

int readFileProducts ( char* , ProductCatalog );

#endif /* _PARSER_H_INCLUDED_ */

