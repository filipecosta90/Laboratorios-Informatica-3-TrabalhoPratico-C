#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "parser.h"

int read_file(FILE *f){
	fopen(f,"r");
	int count=0;
	char linha[100];
	while(fscanf(f,"%s\n",linha)!=EOF){
		count++;
	}
	return count;
}

int main(){
	read_file("../files/compras.txt");
	return 0;
}
