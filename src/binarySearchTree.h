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

struct list* BSTreeToLL ( BSTree tree , int sizeStruct,  void ( *destroyer ) (void *) );

#endif /* _BINARY_SEARCH_TREE_H_INCLUDED_ */

