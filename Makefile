CFLAGS = -Wall -g -O2 -std=c99 -Wno-unused-result

all: main

main: main.o leitura.o lista.o dados.o cont.o imprimir.o
	gcc $(CFLAGS) main.o leitura.o lista.o dados.o cont.o imprimir.o -o lattes

lista.o: lista.c lista.h
	gcc $(CFLAGS) -c lista.c

leitura.o: leitura.c leitura.h
	gcc $(CFLAGS) -c leitura.c

dados.o: dados.c dados.h
	gcc $(CFLAGS) -c dados.c

cont.o: cont.c cont.h
	gcc $(CFLAGS) -c cont.c

imprimir.o: imprimir.c imprimir.h
	gcc $(CFLAGS) -c imprimir.c

main.o : main.c 
	gcc $(CFLAGS) -c main.c

clean:
	rm -rf ./*.o
	 
purge: clean
	rm -rf lattes