/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */


#ifndef _CLIENT_H_INCLUDED_
#define _CLIENT_H_INCLUDED_

typedef struct client*  Client;

Client newClient ( void );

void setClient ( Client , char, char, char[3] );

char getFirstLetter ( Client );

char getSecondLetter ( Client );

char* getNumbers ( Client );

int equals ( Client, Client );

#endif /* _CLIENT_H_INCLUDED_ */

