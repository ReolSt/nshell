all:
		make nshell

nshell: main.o interpret.o file.o parsing.o system.o
		gcc -o nshell main.o file.o parsing.o system.o interpret.o -Wall
		rm main.o interpret.o file.o parsing.o system.o

main.o: main.c
		gcc -c main.c -Wall

file.o: file.c
		gcc -c file.c -Wall

parsing.o: parsing.c
		gcc -c parsing.c -Wall

system.o: system.c
		gcc -c system.c -Wall

interpret.o: interpret.c
		gcc -c interpret.c -Wall

clean:
		rm nshell main.o interpret.o file.o parsing.o system.o
