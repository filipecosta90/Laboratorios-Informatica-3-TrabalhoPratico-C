#include <stdio.h>
#include "avl_tree.h"

int main (){
  AvlTree arvore= NULL;
  arvore = insertInAvlTree(arvore, "teste");
  arvore = insertInAvlTree(arvore, "b");
  arvore = insertInAvlTree(arvore, "a");
  arvore = insertInAvlTree(arvore, "d");
  printf("inseriu %d objectos.\n", getSizeOfAvlTree ( arvore ));
  return 0;
}
