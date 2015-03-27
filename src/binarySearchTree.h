/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#ifndef _BINARY_SEARCH_TREE_H_INCLUDED_
#define _BINARY_SEARCH_TREE_H_INCLUDED_

typedef struct bstNode *BstNode;

struct bstNode* newNodeBst ( void* );

void freeNode ( BstNode );

struct bstNode** searchBst ( struct bstNode** , int ( *comparator ) (void *, void *) , void* );

void insertBst ( struct bstNode** , int ( *comparator ) (void *, void *) , void* );

void deleteBst ( struct bstNode** );

void* getNodeBstData ( struct bstNode** );

#endif /* _BINARY_SEARCH_TREE_H_INCLUDED_ */

