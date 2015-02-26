#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "parser.h"

int read_file(char* filename){
  FILE *fp;
  fp = fopen(filename,"r");
  int count=0;
  char linha[100];
  while( fgets (linha, sizeof linha, fp) != NULL){
    count++;
  }
  fclose(fp);
  return count;
}

int main(){
  printf("número de linhas %d\n",read_file("../files/compras.txt"));
  return 0;
}

