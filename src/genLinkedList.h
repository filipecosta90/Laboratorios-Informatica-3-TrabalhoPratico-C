/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _GENERIC_LINKED_LIST_H_INCLUDED_
#define _GENERIC_LINKED_LIST_H_INCLUDED_

typedef struct listNode*  ListNode;

typedef struct list* List;

typedef void ( *freeFunction ) ( void* );

struct list* initLL ();

void newLL ( List , int , freeFunction );

void destroyLL ( List );

void prependLL ( List , void* );

void appendLL ( List , void* );

int sizeLL ( List );

void*  headLL ( List );

void tailLL ( List , void * );

#endif /* _GENERIC_LINKED_LIST_H_INCLUDED_ */

