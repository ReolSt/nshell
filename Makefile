all:
		make nshell

nshell: main.o file.o parsing.o system.o
		gcc -o nshell main.o file.o parsing.o system.o

main.o: main.c
		gcc -c main.c

file.o: file.c
		gcc -c file.c

parsing.o: parsing.c
		gcc -c parsing.c

system.o: system.c
		gcc -c system.c

clean:
	  rm nshell main.o file.o parsing.o system.o
