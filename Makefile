all:
		make nshell

nshell: main.o file.o parsing.o system.o interpret.o vector.o string.o
		gcc -o nshell main.o file.o parsing.o system.o interpret.o vector.o string.o -Wall
		rm main.o file.o parsing.o system.o interpret.o vector.o string.o

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

vector.o: core/Vector/Vector.c
		gcc -c core/Vector/Vector.c -Wall

string.o: core/String/String.c
		gcc -c core/String/String.c -Wall

clean:
		rm nshell
