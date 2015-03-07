#include <stdlib.h>
#include <string.h>
#include "avl_tree.h"

struct internalAvlTreeNode {
  char* key_value;
  struct internalAvlTreeNode *left;
  struct internalAvlTreeNode *right;
  int height;
};

struct avlTree {
  struct internalAvlTreeNode *root;
};

AvlTree newAvlTree ( void ){
  struct avlTree* newTree = ( struct avlTree* ) malloc ( sizeof (struct avlTree ));
  newTree->root = NULL;
  return newTree;
}

static struct internalAvlTreeNode* newInternalNode ( char * key ){
  struct internalAvlTreeNode* newNode = ( struct internalAvlTreeNode* ) malloc ( sizeof ( struct internalAvlTreeNode ) );
  strcpy( newNode->key_value , key );
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->height = 1;
  return newNode;
}

int height(struct internalAvlTreeNode* node){
  if (node == NULL)
    return 0;
  else
    return node->height;
}

// A utility function to get maximum of two integers
int max( int a, int b ){
  return (a > b)? a : b;
}

static struct internalAvlTreeNode* rightRotate ( struct internalAvlTreeNode *y ) {
  struct internalAvlTreeNode *x = y->left;
  struct internalAvlTreeNode *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = max( height( y->left ), height( y->right ) ) +1;
  x->height = max( height( x->left ), height( x->right ) ) +1;

  //Return new root
  return x;
}

static struct internalAvlTreeNode* leftRotate ( struct internalAvlTreeNode *y ) {
  struct internalAvlTreeNode *x = y->left;
  struct internalAvlTreeNode *T2 = x->right;

  // Perform rotation
  x->left = y;
  y->right = T2;

  // Update heights
  x->height = max( height( x->left ), height( x->right ) ) +1;
  y->height = max( height( y->left ), height( y->right ) ) +1;

  //Return new root
  return y;
}

int getHeightOfAvlTree ( struct internalAvlTreeNode *getAvl ){
  if( getAvl == NULL ){
    return 0;
  }
  else{
    return getAvl->height;
  }
}

static int getAvlBalance ( struct internalAvlTreeNode *node ){
  if( node == NULL){
    return 0;
  }
  else {
    return getHeightOfAvlTree ( node->left ) - getHeightOfAvlTree ( node->right );
  }
}


int getSizeOfAvlTree ( AvlTree getTree ){

}

static char* getRootKey ( AvlTree getTree ){
  return getTree->root->key_value;
}

void insertInAvlTree ( AvlTree tree, char* key){

  // 1. Perform the normal Avl rotation
  if( tree->root == NULL )
    tree->root = newInternalNode ( key );

  struct internalAvlTreeNode * insertTree = tree->root;
  int compareValue = strcmp ( key , insertTree->key_value ); 
  if( compareValue < 0 )
    insertInAvlTree ( insertTree->left, key );
  if( compareValue > 0 )
    insertInAvlTree ( insertTree->right , key);

  // 2. Update Height of this ancestor node 
  insertTree->height = max ( getHeightOfAvlTree ( insertTree->left ), getHeightOfAvlTree ( insertTree->right ) ) + 1;

  // 3. Get the balance factor of this ancestor node to check whetherthis node became unbalanced
  int balance = getAvlBalance ( insertTree );

  // If this node becomes unbalanced, then there are 4 cases
  // Left Left Case
  if (balance > 1 && ( strcmp ( key , insertTree->left->key_value) == -1 ))
    insertTree = rightRotate( insertTree );

  // Right Right Case
  if (balance < -1 && ( strcmp ( key , insertTree->right->key_value) == 1 ))
    insertTree = leftRotate( insertTree );

  // Left Right Case
  if (balance > 1 && ( strcmp ( key , insertTree->left->key_value) == 1 ))
  {
    insertTree->left =  leftRotate( insertTree->left );
    rightRotate( insertTree );
  }

  // Right Left Case
  if (balance < -1 && ( strcmp ( key , insertTree->right->key_value) == -1 ))
  {
    insertTree->right = rightRotate( insertTree->right );
    leftRotate( insertTree );
  }
}
