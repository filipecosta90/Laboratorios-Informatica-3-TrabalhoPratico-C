#include <stdio.h>
#include "avl_tree.h"

int main (){
  AvlTree arvore;
  arvore = newAvlTree();
  printf("abc\n");
  insertInAvlTree(arvore, "teste");
  insertInAvlTree(arvore, "abc");
  printf("inseriu\n");
  return 0;
}
