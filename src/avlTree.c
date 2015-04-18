#include <stdlib.h>
#include <string.h>
#include "avlTree.h"
#include "genLinkedList.h"

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

static int avlNodeContains ( struct avlNode * node , char* containsKey ){
  int comparedValue;
  int returningValue = 0;
  if ( node != NULL ){
    comparedValue = strcmp ( node->key , containsKey );
    if ( comparedValue == 0 ){
      returningValue = 1;
    }
    else{
      returningValue = avlNodeContains ( node->left , containsKey ) + avlNodeContains ( node->right , containsKey );
    }
  }
  return returningValue;
}

int avlContains ( struct avlTree *tree , char* containsKey ) {
  int returningValue = 0;
  if( tree != NULL ) {
    if( tree->root != NULL ){
      returningValue = avlNodeContains ( tree->root , containsKey );  
    }
  }
  return returningValue; 
}

void avlFreeNode ( struct avlNode *node ) {
  if ( node->left != NULL ) {
    avlFreeNode ( node->left );
  }
  if ( node->right != NULL ) {
    avlFreeNode ( node->right );
  }
  free ( node );
}

void avlFree ( AvlTree freeTree ) {
  if ( freeTree->root != NULL ) {
    avlFreeNode ( freeTree->root );
  }
}

void* toStringer ( struct avlNode * node ){
  char* nKey;
  int sizeToAllocate;
  nKey = NULL;
  sizeToAllocate = 0;
  if( node != NULL ){
  sizeToAllocate = strlen ( node->key );
  nKey = (char*) malloc ( (sizeToAllocate+1) * sizeof ( char ) );
  strcpy( nKey , node->key );
  }
  return nKey;
}

struct list* avlNodeToLL ( struct avlNode * node , struct list* listLL ){
  if ( node != NULL ){
    appendLL ( listLL , toStringer(node) );
    if ( node->left != NULL ) {
      avlNodeToLL( node->left , listLL );
    }
    if ( node->right != NULL ) {
      avlNodeToLL( node->right , listLL );
    }
  }
  return listLL;
}

struct list* avlToLL( struct avlTree *tree, struct list* returningLL ){
  if( tree != NULL ) {
    if( tree->root != NULL ){
      returningLL = avlNodeToLL ( tree->root , returningLL );
    }
  }
  return returningLL;
}

