/*
 *  *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *   *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *    *  */

#ifndef _BINARY_TREE_H_INCLUDED_
#define _BINARY_TREE_H_INCLUDED_

typedef struct binaryTree * BinaryTree;

BinaryTree newBinaryTree( void );

void initBinaryTree ( BinaryTree );

int getSizeOfTree ( BinaryTree );

void insertInTree ( BinaryTree , char* );

void deleteBinaryTree ( BinaryTree );

#endif /* _BINARY_TREE_H_INCLUDED_ */
