#include <stdlib.h>
#include <string.h>
#include "accountingProduct.h"

struct accountingProduct {
  int NSales;
  float NBilled;
  int PSales;
  float PBilled;
};

Accounting newAccountingProduct ( void ){
  AccountingProduct accountingProductNew = ( AccountingProduct ) malloc ( sizeof ( struct accountingProduct ));
  memset ( (accountingProductNew), '\0', ( sizeof ( struct accountingProduct)) );
  return ( accountingProductNew );
}

void setAccountingProduct ( AccountingProduct acProdToSet, int n_Sales, float n_Billed, int p_Sales, float p_Billed ){
  clientToSet->firstLetter=fstLetter;
  clientToSet->secondLetter=sndLetter;
  strcpy ( clientToSet->numbers , setNumbers );
}

int getNSales ( AccountingProduct getAccountingProduct ) {
  return ( getAccountingProduct->Nsales );
}

int getPSales ( AccountingProduct getAccountingProduct ) {
  return ( getAccountingProduct->PSales );
}

float getNBilled ( AccountingProduct getAccountingProduct ) {
  return ( getAccountingProduct->NBilled );
}

float getPBilled ( AccountingProduct getAccountingProduct ) {
  return ( getAccountingProduct->PBilled );
}

float getTotalBilled ( AccountingProduct getAccountingProduct ) {
  return ( getAccountingProduct->NBilled + getAccountingProduct->PBilled );
}

