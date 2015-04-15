/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include <stdlib.h>
#include "binarySearchTree.h"
#include "genLinkedList.h"

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
  int found;
  BstNode actual;
  void* returningValue = NULL;
  actual = node;
  found = 0;
  while ( actual != NULL && found != 1){
    comparedValue = comparator ( data, actual->data );
    if ( comparedValue == 0 ){
      returningValue = actual->data ;
      found = 1;
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

List BstNodeToLL ( List ll , BstNode b1 ){
  if( b1 != NULL){
    prependLL ( ll , b1->data );
    if( b1->left != NULL ){
      ll = BstNodeToLL ( ll , b1->left );
    }
    if ( b1->right != NULL ){
      ll = BstNodeToLL ( ll, b1->right );
    }
  }
  return ll;
}

List BstNodeToLL_ToString ( List ll , BstNode b1 , void* ( *toStringer ) ( void*) ){
  if( b1 != NULL){
    appendLL ( ll , toStringer ( b1->data ) );
    if( b1->left != NULL ){
      ll = BstNodeToLL_ToString ( ll , b1->left , toStringer );
    }
    if ( b1->right != NULL ){
      ll = BstNodeToLL_ToString ( ll, b1->right , toStringer );
    }
  }
  return ll;
}

List BSTreeToLL ( BSTree tree , int sizeStruct,  void ( *destroyer ) (void *) ){
  List returningLL;
  returningLL = initLL();
  newLL ( returningLL , sizeStruct , destroyer );
  /* No root */
  if ( tree->root == NULL ){
    return returningLL;
  }
  else{
    returningLL = BstNodeToLL ( returningLL , tree->root );
  }
  return returningLL;
}

struct list* BSTreeToLL_ToString ( BSTree tree, int sizeStruct , void ( *destroyer ) ( void* ) , void* ( *toStringer ) ( void* ) ){
  List returningLL;
  returningLL = initLL();
  newLL ( returningLL , sizeStruct , destroyer );
  /* No root */
  if ( tree->root == NULL ){
    return returningLL;
  }
  else{
    returningLL = BstNodeToLL_ToString ( returningLL , tree->root , toStringer );
  }
  return returningLL;
}

int BSTNodeSize ( BstNode node ){
  if ( node == NULL ){
    return ( 0 );
  }
  else {
    return 1 + BSTNodeSize ( node->left ) + BSTNodeSize ( node->right );
  }
}

int BSTreeSize ( BSTree tree ) {
  if( tree != NULL) {
    if ( tree->root != NULL ){
      return BSTNodeSize ( tree->root );
    }
  }
  return ( 0 );
}
