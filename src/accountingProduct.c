#include <stdlib.h>
#include <string.h>
#include "accountingProduct.h"

struct accountingProduct {
  int nSales;
  float nBilled;
  int pSales;
  float pBilled;
};

AccountingProduct newAccountingProduct ( void ){
  AccountingProduct accountingProductNew = ( AccountingProduct ) malloc ( sizeof ( struct accountingProduct ));
  memset ( (accountingProductNew), '\0', ( sizeof ( struct accountingProduct)) );
  return ( accountingProductNew );
}

void setAccountingProduct ( AccountingProduct acProdToSet, int n_Sales, float n_Billed, int p_Sales, float p_Billed ){
  acProdToSet->nSales = n_Sales;
  acProdToSet->nBilled = n_Billed;
  acProdToSet->pSales = p_Sales;
  acProdToSet->nBilled = p_Billed;
}

int getNSales ( AccountingProduct getAccountingProduct ) {
  return ( getAccountingProduct->nSales );
}

int getPSales ( AccountingProduct getAccountingProduct ) {
  return ( getAccountingProduct->pSales );
}

float getNBilled ( AccountingProduct getAccountingProduct ) {
  return ( getAccountingProduct->nBilled );
}

float getPBilled ( AccountingProduct getAccountingProduct ) {
  return ( getAccountingProduct->pBilled );
}

float getTotalBilled ( AccountingProduct getAccountingProduct ) {
  return ( getAccountingProduct->nBilled + getAccountingProduct->nBilled );
}

