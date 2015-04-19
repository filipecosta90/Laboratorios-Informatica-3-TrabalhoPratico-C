CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -O2

gesthiper: gesthiper.o accounting.o clientCatalog.o productCatalog.o productSPL.o clientCPL.o clientProductLinker.o salesProductLinker.o parser.o binarySearchTree.o genLinkedList.o avlTree.o month.o clientSales.o productSales.o
	gcc -o $@ $^ $(CFLAGS)

genLinkedList.o: genLinkedList.c
	$(CC) -c -o $@ $< $(CFLAGS)

avlTree.o: avlTree.c genLinkedList.c
	$(CC) -c -o $@ $< $(CFLAGS)

binarySearchTree.o: binarySearchTree.c
	$(CC) -c -o $@ $< $(CFLAGS)

month.o: month.c 
	$(CC) -c -o $@ $< $(CFLAGS)

clientSales.o: clientSales.c
	$(CC) -c -o $@ $< $(CFLAGS)

productSales.o: productSales.c
	$(CC) -c -o $@ $< $(CFLAGS)

clientProductLinker.o: clientProductLinker.c clientCatalog.c clientCPL.c clientProductLinker.c productSales.c avlTree.c genLinkedList.c binarySearchTree.c
	$(CC) -c -o $@ $< $(CFLAGS)

clientCatalog.o: clientCatalog.c avlTree.c genLinkedList.c
	$(CC) -c -o $@ $< $(CFLAGS)

clientCPL.o: clientCPL.c clientCatalog.c genLinkedList.c productSales.c binarySearchTree.c
	$(CC) -c -o $@ $< $(CFLAGS)

productSPL.o: productSPL.c genLinkedList.c clientSales.c binarySearchTree.c
	$(CC) -c -o $@ $< $(CFLAGS)

accounting.o: accounting.c month.c
	$(CC) -c -o $@ $< $(CFLAGS)

productCatalog.o: productCatalog.c avlTree.c
	$(CC) -c -o $@ $< $(CFLAGS)

salesProductLinker.o: salesProductLinker.c productSPL.c clientSales.c avlTree.c genLinkedList.c binarySearchTree.c 
	$(CC) -c -o $@ $< $(CFLAGS)

parser.o: parser.c accounting.c productCatalog.c clientCatalog.c salesProductLinker.c month.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o gesthiper 
