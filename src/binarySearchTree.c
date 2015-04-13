/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include <stdlib.h>
#include "binarySearchTree.h"

struct bstNode {
  void* data;
  struct bstNode* left;
  struct bstNode* right;
};

struct bstNode* newNodeBst ( void* data ) {
  struct bstNode* result;
  result = malloc ( sizeof ( struct bstNode ) );
  result->data = data;
  result->left = NULL;
  result->right = NULL;
  return result;
}

void* getNodeBstData ( struct bstNode** node ){
  return (*node)->data;
}

void freeNodeBst ( struct bstNode* node ) {
  free ( node );
}

struct bstNode** searchBst ( struct bstNode** root , int ( *comparator ) (void *, void *) , void* data ) {
  struct bstNode** node = root;
  int compareResult;
  while ( *node != NULL ) {
    compareResult = comparator ( data, (*node)->data );
    if ( compareResult < 0 ){
      node = &( *node )->left;
    }
    else {
      if ( compareResult > 0 ){
        node = &( *node )->right;
      }
      else {
        break;
      }
    }
  }
  return node;
}

void insertBst ( struct bstNode** root , int ( *comparator ) (void *, void *) , void* data ) {
  struct bstNode** node = searchBst ( root , comparator , data );
  if ( *node == NULL ) {
    *node = newNodeBst ( data );
  }
}

void deleteBst ( struct bstNode** node ) {
  void *temp;
  struct bstNode* oldNode = *node;
  if ( (*node)->left == NULL ) {
    *node = (*node)->right;
    freeNodeBst ( oldNode );
  }
  else if ( (*node)->right == NULL ) {
    *node = (*node)->left;
    freeNodeBst ( oldNode );
  } 
  else {
    struct bstNode** pred;
    pred = &(*node)->left;
    while ( (*pred)->right != NULL ) {
      pred = &(*pred)->right;
    }

    /* Swap values */
    temp = (*pred)->data;
    (*pred)->data = (*node)->data;
    (*node)->data = temp;

    deleteBst ( pred );
  }
}

