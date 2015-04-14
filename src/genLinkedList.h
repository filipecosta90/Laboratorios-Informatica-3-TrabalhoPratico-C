/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _GENERIC_LINKED_LIST_H_INCLUDED_
#define _GENERIC_LINKED_LIST_H_INCLUDED_

typedef struct listNode*  ListNode;

typedef struct list* List;

/* http://stackoverflow.com/questions/1921539/using-boolean-values-in-c */
typedef enum { FALSE , TRUE } bool;

typedef bool ( *listIterator ) ( void * );

typedef void ( *freeFunction ) ( void* );

struct list* initLL ();

void newLL ( List , int , freeFunction );

void destroyLL ( List );

void prependLL ( List , void* );

void appendLL ( List , void* );

int sizeLL ( List );

void forEachLL ( List , listIterator );

void headLL ( List , void* , bool );

void tailLL ( List , void * );

#endif /* _GENERIC_LINKED_LIST_H_INCLUDED_ */

