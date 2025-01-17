/*
 *  *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  *  */

#ifndef _AVL_TREE_H_INCLUDED_
#define _AVL_TREE_H_INCLUDED_

typedef struct avlTree * AvlTree;

AvlTree createTree ();

void avlInsert ( AvlTree, char* );

int avlSize ( AvlTree );

int avlContains ( AvlTree , char* );

void avlFree ( AvlTree );

/* QUERIE 10 AUXILIAR METHOD */
struct list* avlToLL ( struct avlTree* , struct list* returningLL );

#endif /* _AVL_TREE_H_INCLUDED_ */
