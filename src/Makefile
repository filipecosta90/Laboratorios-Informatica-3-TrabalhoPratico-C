CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -O2

gesthiper: gesthiper.o accounting.o clientCatalog.o productCatalog.o parser.o month.o avlTree.o genLinkedList.o
	gcc -o $@ $^ $(CFLAGS)

genLinkedList.o: genLinkedList.c
	$(CC) -c -o $@ $< $(CFLAGS)

avlTree.o: avlTree.c
	$(CC) -c -o $@ $< $(CFLAGS)

month.o: month.c 
	$(CC) -c -o $@ $< $(CFLAGS)

accounting.o: accounting.c month.c
	$(CC) -c -o $@ $< $(CFLAGS)

clientCatalog.o: clientCatalog.c avlTree.c
	$(CC) -c -o $@ $< $(CFLAGS)

productCatalog.o: productCatalog.c avlTree.c
	$(CC) -c -o $@ $< $(CFLAGS)

parser.o: parser.c accounting.c productCatalog.c clientCatalog.c month.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o gesthiper 
