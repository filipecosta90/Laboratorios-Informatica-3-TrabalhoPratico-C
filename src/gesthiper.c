/*
 *  *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  *  */

#include <stdio.h>
#include <stdlib.h>

#include "accounting.h"
#include "parser.h"

int main (int argc, char *argv[] ){
  Accounting acBook;
  int flagReadingSales = 0;
  acBook = newAccounting();
  initAccounting (acBook);
  flagReadingSales = readFileSales( "../files/compras.txt" , acBook );
  printf("flag sales:%d\n", flagReadingSales);
  return 0;
}
