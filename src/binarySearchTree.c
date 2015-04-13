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

typedef struct bstNode* BstNode;

struct bsTree {
  BstNode root;
  int ( *comparator ) (void *, void *) ;
};


struct bstNode* newNodeBst ( void* data ) {
  BstNode result;
  result = malloc ( sizeof ( struct bstNode ) );
  result->data = data;
  result->left = NULL;
  result->right = NULL;
  return result;
}

struct bsTree* newBSTree ( int ( *newComparator ) (void *, void *) ){
  struct bsTree *newTree = NULL;
  if ( ( newTree = malloc ( sizeof ( struct bsTree ) ) ) == NULL ) {
    return NULL;
  }
  else{
    newTree->root = NULL;
    newTree->comparator = newComparator;
    return newTree;
  }
}

void* searchBstNode ( int ( *comparator ) (void *, void *) , BstNode node , void* data ){
  int comparedValue;
  BstNode actual;
  void* returningValue = NULL;
  actual = node;
  while ( actual != NULL ){
    comparedValue = comparator ( data, actual->data );
    if ( comparedValue == 0 ){
      returningValue = actual->data ;
    }
    else{
      if (comparedValue < 0 ){
        actual = actual->left;
      }
      if ( comparedValue > 0 ){
        actual = actual->right;
      }
    }
  }
  return returningValue;
}

void* searchBst ( BSTree tree , void* containsKey ) {
  void* returningValue;
  if( tree->root == NULL ){
    returningValue =  NULL;
  }
  if( tree != NULL ) {
    if( tree->root != NULL ){
      returningValue = searchBstNode ( tree->comparator , tree->root , containsKey );
    }
  }
  return returningValue;
}

void insertBst ( BSTree tree , void* data ) {
  int comparedValue;
  BstNode node = NULL;
  BstNode next = NULL;
  BstNode last = NULL;

  /* No root */
  if ( tree->root == NULL ){
    node = newNodeBst ( data );
    tree->root = node;
  }
  /* Already Have root*/
  else{
    next = tree->root;
    while ( next != NULL ){
      last = next;
      comparedValue = tree->comparator ( data, next->data );
      if ( comparedValue < 0 ) {
        next = next->left;
      }
      else if ( comparedValue > 0 ) {
        next = next->right;
      }
    }
    node = newNodeBst ( data );
    if ( comparedValue < 0 ) last->left = node;
    if ( comparedValue > 0 ) last->right = node;
  }
}

