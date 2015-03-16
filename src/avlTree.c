#include <stdlib.h>
#include <string.h>
#include "avlTree.h"
#include <stdio.h>

struct avlTree {
  char* key_value;
  struct avlTree *left;
  struct avlTree *right;
  int height;
};

static struct avlTree*  newNode ( char * key ){
  struct avlTree* newNode = ( struct avlTree* ) malloc ( sizeof (  struct avlTree ) );
  int sizeToAllocate = strlen (key) +1;
  newNode->key_value = (char*) malloc ( sizeToAllocate * sizeof ( char ) );
  strcpy( newNode->key_value , key );
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->height = 0;
  return (newNode);
}

static struct avlTree* allocateMemory (){
  struct avlTree* newNode = ( struct avlTree* ) malloc ( sizeof (  struct avlTree ) );
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->height = 0;
  newNode = NULL;
  return ( newNode );
}

static int height(struct avlTree* node){
  int leftHeight, rightHeight, returningHeight;
  leftHeight = 0;
  rightHeight = 0;
  if (node == NULL){
    returningHeight = 0;
  }
  else{
    if ( node->left == NULL )
      leftHeight=0;
    else
      leftHeight = 1 + node->left->height;
    if ( node->right == NULL )
      rightHeight=0;
    else
      rightHeight = 1 + node->right->height;
  }
  if ( leftHeight > rightHeight )
    returningHeight = leftHeight;
  else
    returningHeight = rightHeight;
  return returningHeight;
}

static struct avlTree* rightRotate ( struct avlTree *root ) {

  struct avlTree *rightPointer;
  rightPointer = root->left;

  if(rightPointer->right == NULL )
    rightPointer->right = allocateMemory();

  /* Perform rotation */
  root->left =rightPointer->right;
  rightPointer->right = root;

  /* Update heights */
  root->height = height ( root );
  rightPointer->height = height ( rightPointer );

  /* Return new root */
  return rightPointer;
}

static struct avlTree* leftRotate ( struct avlTree *root ) {

  struct avlTree *leftPointer;
  leftPointer = root->right;

  if (leftPointer->left == NULL)
    leftPointer->left = allocateMemory();
  /* Perform rotation */
  root->right = leftPointer->left;
  leftPointer->left = root;

  /* Update heights */
  root->height = height( root);
  leftPointer->height = height( leftPointer);

  /* Return new root */
  return leftPointer;
}

static struct avlTree* RightRight ( struct avlTree* root ){
  root = leftRotate ( root );
  return ( root );
}

static struct avlTree* LeftLeft  ( struct avlTree* root ){
  root = rightRotate ( root );
  return ( root );
}

static struct avlTree* LeftRight ( struct avlTree* root ){
  root->left = leftRotate ( root->left );
  root = rightRotate ( root );
  return ( root );
}

static struct avlTree* RightLeft ( struct avlTree* root ){
  root->right = rightRotate ( root->right );
  root = leftRotate ( root );
  return ( root );
}

static int getAvlBalance ( struct avlTree *node ){
  int leftBalance, rightBalance, returningBalance;
  leftBalance = 0;
  rightBalance = 0;
  if( node == NULL ){
    returningBalance = 0;
  }
  else{
    if ( node->left == NULL){
      leftBalance = 0;
    }
    else {
      leftBalance = 1 + node->left->height;
    }
    if ( node->right == NULL) {
      rightBalance = 0;
    }
    else {
      rightBalance = 1 + node->right->height;
    }
    returningBalance = leftBalance - rightBalance;
  }
  return returningBalance;
}

struct avlTree* insertInAvlTree ( struct avlTree* insertTree, char* key){
  int compareValue;
  if (insertTree == NULL){
    return ( newNode( key ) );
  }
  compareValue = strcmp ( key , insertTree->key_value );
  if( compareValue < 0 ){
    insertTree->left = insertInAvlTree ( insertTree->left, key );
    if ( getAvlBalance ( insertTree ) == -2 ){
      if ( strcmp ( key , insertTree->right->key_value )  == 1 ){
        insertTree = RightRight ( insertTree );
      }
      else{
        insertTree = RightLeft ( insertTree );
      }
    }
  }
  if( compareValue > 0 ){
    insertTree->right = insertInAvlTree ( insertTree->right , key);
    if ( getAvlBalance ( insertTree ) == 2 ){
      if ( strcmp ( key , insertTree->left->key_value ) == -1 ){
        insertTree = LeftLeft ( insertTree );
      }
      else{
        insertTree = LeftRight ( insertTree );
      }
    }
  }
  /* 2. Update Height of this ancestor node */
  insertTree->height = height ( insertTree );

  return insertTree;
}

int getSizeOfAvlTree ( AvlTree tree ) {
  if ( tree == NULL) {
    return 0;
  }
  else{
    return 1 + getSizeOfAvlTree (tree->left) + getSizeOfAvlTree (tree->right);
  }
}

