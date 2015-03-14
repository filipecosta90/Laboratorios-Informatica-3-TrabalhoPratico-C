#include <stdlib.h>
#include <string.h>
#include "avl_tree.h"
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
  newNode->height = 1;
  return (newNode);
}

static int height(struct avlTree* node){
  if (node == NULL)
    return 0;
  else
    return node->height;
}

// A utility function to get maximum of two integers
static int max( int a, int b ){
  return (a > b)? a : b;
}

static struct avlTree* rightRotate ( struct avlTree *y ) {
  struct avlTree *x = y->left;
  struct avlTree *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = max( height( y->left ), height( y->right ) ) +1;
  x->height = max( height( x->left ), height( x->right ) ) +1;

  //Return new root
  return x;
}

static struct avlTree* leftRotate ( struct avlTree *x ) {
  struct avlTree *y = x->right;
  struct avlTree *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  x->height = max( height( x->left ), height( x->right ) ) +1;
  y->height = max( height( y->left ), height( y->right ) ) +1;

  //Return new root
  return y;
}

int getHeightOfAvlTree ( struct avlTree *getAvl ){
  if( getAvl == NULL ){
    return 0;
  }
  else{
    return getAvl->height;
  }
}

static int getAvlBalance ( struct avlTree *node ){
  if( node == NULL){
    return 0;
  }
  else {
    return getHeightOfAvlTree ( node->left ) - getHeightOfAvlTree ( node->right );
  }
}

struct avlTree* insertInAvlTree ( struct avlTree* insertTree, char* key){
  if (insertTree == NULL){
    return ( newNode( key ) );
  }
  int compareValue = strcmp ( key , insertTree->key_value ); 
  if( compareValue < 0 ){
    insertTree->left = insertInAvlTree ( insertTree->left, key );
  }
  if( compareValue > 0 ){
    insertTree->right = insertInAvlTree ( insertTree->right , key);
  }
  // 2. Update Height of this ancestor node 
  insertTree->height = max ( getHeightOfAvlTree ( insertTree->left ), getHeightOfAvlTree ( insertTree->right ) ) + 1;

  // 3. Get the balance factor of this ancestor node to check whetherthis node became unbalanced
  int balance;
  balance = getAvlBalance ( insertTree );

  // If this node becomes unbalanced, then there are 4 cases
  // Left Left Case
  if (balance > 1 && ( strcmp ( key , insertTree->left->key_value) == -1 ))
    return rightRotate( insertTree );

  // Right Right Case
  if (balance < -1 && ( strcmp ( key , insertTree->right->key_value) == 1 ))
    return leftRotate( insertTree );

  // Left Right Case
  if (balance > 1 && ( strcmp ( key , insertTree->left->key_value) == 1 ))
  {
    insertTree->left =  leftRotate( insertTree->left );
    return rightRotate( insertTree );
  }

  // Right Left Case
  if (balance < -1 && ( strcmp ( key , insertTree->right->key_value) == -1 ))
  {
    insertTree->right = rightRotate( insertTree->right );
    return leftRotate( insertTree );
  }
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

