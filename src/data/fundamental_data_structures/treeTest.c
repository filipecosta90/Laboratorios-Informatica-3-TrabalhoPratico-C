#include <stdio.h>
#include "avl_tree.h"

int main (){
  AvlTree arvore;
  newAvlTree ( arvore );
  printf("abc\n");
  insertInAvlTree(arvore, "teste");
  insertInAvlTree(arvore, "b");
  insertInAvlTree(arvore, "a");
  insertInAvlTree(arvore, "d");
  preOrder(arvore);
  printf("inseriu\n, %d\n", getSizeOfAvlTree ( arvore ));
  return 0;
}
