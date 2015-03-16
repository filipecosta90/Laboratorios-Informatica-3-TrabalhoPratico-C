#include <stdlib.h>
#include <string.h>
#include "avlTree.h"
#include <stdio.h>

struct avlNode {
  struct avlNode *left;
  struct avlNode *right;
  char *key;
};

struct avlTree {
  struct avlNode *root;
};

static struct avlNode*  createNode ( char * key ){
  struct avlNode* newNode = ( struct avlNode* ) malloc ( sizeof (  struct avlNode ) );
  int sizeToAllocate = strlen (key) +1;
  newNode->key = (char*) malloc ( sizeToAllocate * sizeof ( char ) );
  strcpy( newNode->key , key );
  newNode->left = NULL;
  newNode->right = NULL;
  return (newNode);
}

struct avlTree *createTree (){
  struct avlTree *newTree = NULL;
  if ( ( newTree = malloc ( sizeof ( struct avlTree ) ) ) == NULL ) {
    return NULL;
  }
  else{
    newTree->root = NULL;
    return newTree;
  }
}

/* Find the height of an AVL node recursively */
static int avlNodeHeight( struct avlNode *node ) {
  int heightLeft = 0;
  int heightRight = 0;

  if( node->left ){
    heightLeft = avlNodeHeight( node->left );
  }
  if( node->right ){
    heightRight = avlNodeHeight( node->right );
  }
  return heightRight > heightLeft ? ++heightRight : ++heightLeft;
}

/* Find the balance of an AVL node */
static int avlBalanceFactor( struct avlNode *node ) {
  int balanceFactor = 0;

  if( node->left  ){
    balanceFactor += avlNodeHeight( node->left );
  }
  if( node->right ){ 
    balanceFactor -= avlNodeHeight( node->right );
  }
  return balanceFactor ;
}

/* Left Left Rotate */
struct avlNode* avlRotateLeftLeft( struct avlNode *node ) {
  struct avlNode *a = node;
  struct avlNode *b = a->left;

  a->left = b->right;
  b->right = a;

  return( b );
}

/* Left Right Rotate */
struct avlNode* avlRotateLeftRight( struct avlNode *node ) {
  struct avlNode *a = node;
  struct avlNode *b = a->left;
  struct avlNode *c = b->right;

  a->left = c->right;
  b->right = c->left; 
  c->left = b;
  c->right = a;

  return( c );
}

/* Right Left Rotate */
struct avlNode* avlRotateRightLeft( struct avlNode *node ) {
  struct avlNode *a = node;
  struct avlNode *b = a->right;
  struct avlNode *c = b->left;

  a->right = c->left;
  b->left = c->right; 
  c->right = b;
  c->left = a;

  return( c );
}

/* Right Right Rotate */
struct avlNode *avlRotateRightRight( struct avlNode *node ) {
  struct avlNode *a = node;
  struct avlNode *b = a->right;

  a->right = b->left;
  b->left = a; 

  return( b );
}


/* Balance a Node */
struct avlNode* avlBalanceNode ( struct avlNode* node ){
  struct avlNode *newRoot = NULL;
  int balanceFactor;

  /* Balance the children, if they exist. */
  if( node->left ){
    node->left  = avlBalanceNode ( node->left  );
  }
  if( node->right ) {
    node->right = avlBalanceNode ( node->right );
  }
  balanceFactor = avlBalanceFactor ( node );
  /* Left Heavy */
  if( balanceFactor >= 2 ) { 
    if( avlBalanceFactor( node->left ) <= -1 ){
      newRoot = avlRotateLeftRight( node );
    }
    else {
      newRoot = avlRotateLeftLeft( node );
    } 
  }
  /* Right Heavy */
  else if( balanceFactor <= -2 ) {
    if( avlBalanceFactor( node->right ) >= 1 ){
      newRoot = avlRotateRightLeft( node );
    }
    else {
      newRoot = avlRotateRightRight( node );
    }
  } else {
    /* This node is balanced. There are no changes to be made. */
    newRoot = node;
  }
  return( newRoot );
}

/* Balance a Tree */
void avlBalanceTree ( struct avlTree *tree ){
  struct avlNode *newRoot;
  newRoot = NULL;
  newRoot = avlBalanceNode ( tree->root );
  if ( newRoot != tree->root ) {
    tree->root = newRoot;
  }
}

void avlInsert ( struct avlTree *tree, char * newKey ) {
  int comparedValue;
  struct avlNode *node = NULL;
  struct avlNode *next = NULL;
  struct avlNode *last = NULL;

  /* No root */
  if ( tree->root == NULL ){
    node = createNode ( newKey );
    tree->root = node;
  }
  /* Already Have root*/
  else{
    next = tree->root;
    while ( next != NULL ){
      last = next;
      comparedValue = strcmp ( newKey , next->key);
      if ( comparedValue < 0 ) {
        next = next->left;
      }
      else if ( comparedValue > 0 ) {
        next = next->right;
      }
    }
    node = createNode ( newKey );
    comparedValue = strcmp ( newKey , last->key );
    if ( comparedValue < 0 ) last->left = node;
    if ( comparedValue > 0 ) last->right = node;
  }
  avlBalanceTree ( tree );
}

int avlNodeSize ( struct avlNode* node ){
  if ( node == NULL ){
    return ( 0 );
  }
  else {
    return 1 + avlNodeSize ( node->left ) + avlNodeSize ( node->right );
  }
}

int avlSize ( struct avlTree *tree ) {
  if( tree != NULL) {
    if ( tree->root != NULL ){
      return avlNodeSize ( tree->root );
    }
  }
  return ( 0 );
}

