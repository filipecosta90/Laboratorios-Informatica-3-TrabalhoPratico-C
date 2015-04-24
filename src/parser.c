/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "productCatalog.h"
#include "clientCatalog.h"
#include "salesProductLinker.h"
#include "clientProductLinker.h"
#include "accounting.h"
#include "parser.h"

static int productOk(char* line){

  volatile int result = 1;
  volatile int size = strlen(line);
  if (size == 6){
    if(isalpha(line[0])){
      if(isalpha(line[1])){
        if( isdigit(line[2]) && isdigit(line[3]) && isdigit(line[4]) && isdigit(line[5]) ){
          result = 0;
        }
      }
    }
  }
  return result;
}

static int priceOk(char* buf){
  volatile int totalSize = strlen(buf);
  volatile int untilPoint = strcspn(buf,".");
  volatile int position = 0;
  volatile int errorFlag = 0;
  while (position < totalSize && errorFlag != 1){
    if(position != untilPoint){
      if(!isdigit(buf[position])){
        errorFlag = 1;
      }
    }
    position++;
  }
  return errorFlag;
}

static int unitOk (char* buf){
  volatile int errorFlag=0;
  volatile int position=0;
  volatile int totalSize=strlen(buf);
  while(position < totalSize && errorFlag==0){
    if(!isdigit(buf[position])){
      errorFlag=1;
    }
    position++;
  }
  return errorFlag;
}

static int salesTypeOk(char* buf){
  volatile int size = strlen (buf);
  volatile int result = 1;
  if (size == 1){
    if( buf[0] == 'P' || buf[0] == 'p' || buf[0] == 'n'|| buf[0] == 'N' ) 
    {
      result = 0;
    }
  }
  return result;
}

static int clientOk(char* buf){
  volatile int result = 1;
  volatile int size = strlen (buf);
  if (size == 5){
    if(isalpha(buf[0])){
      if(isalpha(buf[1])){
        if( isdigit(buf[2]) && isdigit(buf[3]) && isdigit(buf[4])){
          result = 0;
        }
      }
    }
  }
  return result;
}

static int monthOk(char* buf){
  volatile int result = 0;
  volatile int size = strlen (buf) - 2;
  volatile int position = 0;
  if(size >= 1 && size <=2 ){
    while (position < size && result == 0){
      if(!isdigit(buf[position])){
        result = 1;
      }
      position++;
    }
  }
  return result;
}

int readFileSales(char* filename, Accounting acBook , ClientCatalog clCat, ProductCatalog prCat, struct salesProductLinker* splProd , struct clientProductLinker* cplClient , int* clientErrorCount , int* productErrorCount ){
  FILE *fp;
  volatile int totalCount=0;
  volatile int correctCount=0;
  volatile int errorCount=0;
  volatile int error = 0;
  volatile int tokenPosition = 0;
  volatile int clientError=0;
  volatile int productError=0;
  char buf[32];
  volatile int maxSize=0;
  char* tk;
  float priceToken = 0.0;
  char productToken[7];
  char modeToken;
  int unitToken=0;
  char clientToken[6];
  int monthToken=0;
  fp = fopen(filename,"r");
  while( fgets (buf, sizeof buf, fp) != NULL){
    totalCount++;
    if(strlen(buf)>maxSize){maxSize=strlen(buf);}
    tk = strtok(buf, " ");
    productOk(tk) == 0  ? tokenPosition++ : error++;
    if(!error){
      strcpy ( productToken , tk );
      if ( containsProductCode ( prCat , productToken ) == 0 ){ error++; productError++;}
      if(!error){
        tk = strtok(NULL, " ");
        priceOk(tk) == 0? tokenPosition++ : error++;
        if(!error){
          priceToken = atof( tk );
          tk = strtok(NULL, " ");
          unitOk(tk) == 0 ? tokenPosition++ : error++;
          if(!error){
            unitToken=atoi( tk );
            tk = strtok(NULL, " ");
            salesTypeOk(tk) == 0? tokenPosition ++ : error++;
            if(!error){
              modeToken = tk[0];
              tk = strtok(NULL, " ");
              clientOk(tk) == 0? tokenPosition ++ : error++;
              if(!error){
                strcpy ( clientToken, tk );
                if ( containsClientCode( clCat, clientToken ) == 0 ){ error++; clientError++;}

                if(!error){
                  tk = strtok(NULL, " ");
                  monthOk(tk) == 0 ? tokenPosition ++ : error++;
                  if(error==0){
                    monthToken = atoi ( tk );
                    correctCount++;
                    addSale( acBook, monthToken  );
                    addClient( acBook, monthToken );
                    addBill( acBook, monthToken, priceToken * unitToken );
                    addSalesLineToSPL ( splProd , productToken , clientToken , modeToken , unitToken , priceToken*unitToken , monthToken );
                    addSalesLineToCPL ( cplClient , productToken , clientToken , unitToken , monthToken );
                  }
                  else{
                    errorCount++;
                  }
                }
              }
            }
          }
        }
      }
    }
    error=0;
    tokenPosition=0;
  }
  *clientErrorCount = clientError;
  *productErrorCount = productError;
  fclose(fp);
  return correctCount;
}

int readFileProducts(char* filename, ProductCatalog prCat , int* errorFlagCount ){
  FILE *fp;
  volatile int totalCount=0;
  volatile int correctCount=0;
  volatile int errorCount=0;
  volatile int error = 0;
  volatile int tokenPosition = 0;
  char buf[32];
  volatile int maxSize=0;
  char* tk;
  char productToken[7];
  fp = fopen(filename,"r");
  while( fgets (buf, sizeof buf, fp) != NULL){
    totalCount++;
    if(strlen(buf)>maxSize){maxSize=strlen(buf);}
    tk = strtok(buf, "\r");
    productOk(tk) == 0  ? tokenPosition++ : error++;
    if(error==0){
      strcpy ( productToken, tk );
      addProductToCatalog ( prCat , productToken );
      correctCount++;
    }
    else{
      errorCount++;
    }
  }
  *errorFlagCount = errorCount;
  fclose(fp);
  return correctCount;
}

int readFileClients( char* filename, ClientCatalog clCat, int* errorFlagCount ){
  FILE *fp;
  volatile int totalCount=0;
  volatile int correctCount=0;
  volatile int errorCount=0;
  volatile int error = 0;
  volatile int tokenPosition = 0;
  volatile int maxSize=0;
  char clientToken[6];
  char buf[32];
  char* tk;
  fp = fopen(filename,"r");
  while( fgets (buf, sizeof buf, fp) != NULL){
    totalCount++;
    if(strlen(buf)>maxSize){maxSize=strlen(buf);}
    tk = strtok(buf, "\r");
    clientOk(tk) == 0  ? tokenPosition++ : error++;
    if(error==0){
      strcpy ( clientToken, tk );
      addClientToCatalog ( clCat , clientToken );
      correctCount++;
    }
    else{
      errorCount++;
    }
  }
  *errorFlagCount = errorCount;
  fclose(fp);
  return correctCount;
}

