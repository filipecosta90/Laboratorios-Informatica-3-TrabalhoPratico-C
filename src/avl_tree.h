/*
 *  *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  *  */

#ifndef _AVL_TREE_H_INCLUDED_
#define _AVL_TREE_H_INCLUDED_

typedef struct avlTree * AvlTree;

int getSizeOfAvlTree ( AvlTree );

AvlTree insertInAvlTree ( AvlTree , char* );

void freeAvlTree ( AvlTree );

#endif /* _AVL_TREE_H_INCLUDED_ */

