/*
 *  *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  *  */

#include "accounting.h"
#include "parser.h"

int main (int argc, char *argv[] ){
  Accounting acBook;
  acBook = newAccounting();
  initAccounting (acBook);
  readFileSales( "files/compras.txt" , acBook );
  return 0;
}
