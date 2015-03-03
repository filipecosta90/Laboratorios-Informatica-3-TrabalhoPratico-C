#include <stdlib.h>
#include <string.h>
#include "product.h"

struct product {

  char firstLetter;
  char secondLetter;
  char numbers[4];

};

Product newProduct ( void ){
  Product newProduct = (Product) malloc ( sizeof ( struct product ));
  memset ( (newProduct), '\0', ( sizeof ( struct product)) );
  return newProduct;
}

void setProduct ( Product productToSet, char fstLetter, char sndLetter, char setNumbers[4] ){
  productToSet->firstLetter=fstLetter;
  productToSet->secondLetter=sndLetter;
  strcpy ( productToSet->numbers , setNumbers );
}

char getFirstLetter ( Product getProduct ) { 
  return getProduct->firstLetter;
}

char getSecondLetter ( Product getProduct ) {
  return getProduct->secondLetter;
}

char* getNumbers ( Product getProduct ) {
  return getProduct->numbers;
}

int equals (Product isEqual1, Product isEqual2 ){
  return ( isEqual1->firstLetter==isEqual2->firstLetter) & (isEqual1->secondLetter==isEqual2->secondLetter) & ( strcmp (isEqual1->numbers , isEqual2->numbers));
}
