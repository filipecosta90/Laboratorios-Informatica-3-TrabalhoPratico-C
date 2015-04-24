/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _BINARY_SEARCH_TREE_H_INCLUDED_
#define _BINARY_SEARCH_TREE_H_INCLUDED_

typedef struct bsTree* BSTree;

struct bsTree* newBSTree( int ( *comparator ) (void *, void *) );

void* searchBst ( BSTree , void* );

void insertBst ( BSTree , void* );

struct list* BSTreeToLL ( BSTree tree , struct list* returningLL );

struct list* BSTreeToLL_ToString ( BSTree tree, int sizeStruct , void ( *destroyer ) ( void* ) , void* ( *toStringer ) ( void* ) );

struct list* BSTreeToOrderedLLWithLimit ( BSTree tree , struct list* returningLL, int ( *orderer ) ( void* , void* ) , int limit );

struct list* BSTreeToOrderedLL ( BSTree tree , struct list* returningLL, int ( *orderer ) ( void* , void* ) );

struct list* BSTreeToLLWithMergeRepeated ( BSTree tree , struct list* returningLL, int ( *isEqual ) ( void* , void* ) , void* ( *merger) ( void* , void* ) );

int BSTreeMapReduceInt ( BSTree tree  , int ( *mapper ) ( void* ) );

int BSTreeSize ( BSTree tree );

#endif /* _BINARY_SEARCH_TREE_H_INCLUDED_ */

