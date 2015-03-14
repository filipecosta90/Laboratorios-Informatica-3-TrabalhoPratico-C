CC = gcc
CFLAGS = -Wall -ansi -pedantic -O2

gesthiper: gesthiper.o accounting.o parser.o month.o
	gcc -o $@ $^ $(CFLAGS)

month.o: month.c 
	$(CC) -c -o $@ $< $(CFLAGS)

accounting.o: accounting.c month.c
	$(CC) -c -o $@ $< $(CFLAGS)

parser.o: parser.c accounting.c month.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o 
