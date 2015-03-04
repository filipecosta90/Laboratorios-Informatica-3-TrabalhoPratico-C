#include "binary_tree.h"

struct internal_binary_tree_node {
  char* key_value;
  struct internal_binary_tree_node *left;
  struct internal_binary_tree_node *right; 
};

struct binaryTree {
  struct internal_binary_tree_node *root;
};

BinaryTree newBinaryTree ( void ){

}

void initBinaryTree ( BinaryTree initTree ){

}

int getSizeOfTree ( BinaryTree getTree ){

}

void insertInTree ( BinaryTree insertTree, char* key){

}

void deleteBinaryTree ( BinaryTree deleteTree ){
  if ( deleteTree->root != null){
    deleteBinaryTree ( *(deleteTree->root).left );
    deleteBinaryTree ( *(deleteTree->root).right );
    free ( root );
  }
}
