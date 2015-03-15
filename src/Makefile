CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -O2

gesthiper: gesthiper.o accounting.o clientCatalog.o parser.o month.o avlTree.o
	gcc -o $@ $^ $(CFLAGS)

avlTree.o: avlTree.c
	$(CC) -c -o $@ $< $(CFLAGS)

month.o: month.c 
	$(CC) -c -o $@ $< $(CFLAGS)

accounting.o: accounting.c month.c
	$(CC) -c -o $@ $< $(CFLAGS)

clientCatalog.o: clientCatalog.c avlTree.c
	$(CC) -c -o $@ $< $(CFLAGS)

parser.o: parser.c accounting.c month.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o 
