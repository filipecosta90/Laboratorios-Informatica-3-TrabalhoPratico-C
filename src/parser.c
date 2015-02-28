#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int productOk(char* line){
  int result = 1;
  if(isalpha(line[0])){
    if(isalpha(line[1])){
      if( isdigit(line[2]) && isdigit(line[3]) && isdigit(line[4]) && isdigit(line[5]) ){
        result = 0;
      }
    }
  }
  return result;
}

int priceOk(char* buf){
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

int unitOk (char* buf){
	int errorFlag=0,i=0;
	int totalSize=strlen(buf);
	while(i<totalSize && errorFlag!=1){
		if(!isdigit(buf[i])){
			errorFlag=1;
		}
		i++;
	}
  return errorFlag;
}

int salesTypeOk(char* buf){
  return ( buf[0] == 'P' || buf[0] == 'p' || buf[0] == 'n'|| buf[0] == 'N' ) ? 0 : 1;
}

int clientOk(char* buf){
	int result = 1;
	if(isalpha(buf[0])){
    	if(isalpha(buf[1])){
      		if( isdigit(buf[2]) && isdigit(buf[3]) && isdigit(buf[4])){
        		result = 0;
      		}
   		 }
  	}
  return result;
}

int monthOk(char* buf){
  return 0;
}

int read_file(char* filename){
  FILE *fp;
  fp = fopen(filename,"r");
  volatile int totalCount=0;
  volatile int correctCount=0;
  volatile int errorCount=0;
  volatile int error = 0;
  volatile int tokenPosition = 0;
  char buf[32];
  char* tk;
  while( fgets (buf, sizeof buf, fp) != NULL){
    totalCount++;
    tk = strtok(buf, " ");
    productOk(tk) == 0  ? tokenPosition++ : error++;
    if(!error){
      tk = strtok(NULL, " ");
      priceOk(tk) == 0? tokenPosition++ : error++;
      if(!error){
        tk = strtok(NULL, " ");
        unitOk(tk) == 0 ? tokenPosition++ : error++;
        if(!error){
          tk = strtok(NULL, " ");
          salesTypeOk(tk) == 0? tokenPosition ++ : error++;
          if(!error){
            tk = strtok(NULL, " ");
            clientOk(tk) == 0? tokenPosition ++ : error++;
            if(!error){
              tk = strtok(NULL, " ");
              monthOk(tk) == 0 ? tokenPosition ++ : error++;
              if(error==0){
                correctCount++;
              }
              else{
                errorCount++;
              }
            }
          }
        }
      }
    }
    error=0;
    tokenPosition=0;
  }
  fclose(fp);
  printf("total %d, correct %d, error %d\n", totalCount, correctCount, errorCount);
  return totalCount;
}

int main(void){

  printf("número de linhas %d\n",read_file("../files/compras.txt"));
  return 0;
}

