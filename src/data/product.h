/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */


#ifndef _PRODUCT_H_INCLUDED_
#define _PRODUCT_H_INCLUDED_

typedef struct product * Product;

Product newProduct ( void );

void initProduct ( Product );

void setProduct ( char, char, char[4] );

char getFirstLetter ( Product );

char getSecondLetter ( Product );

char* getNumbers ( Product );

int equals ( Product , Product );

void destroyProduct ( Product );

char* toString ( Product );

#endif /* _PRODUCT_H_INCLUDED_ */

