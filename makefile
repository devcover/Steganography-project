steg: main.c image.o
	gcc -W main.c image.o -o steg
image.o: image.c
gcc -c image.c -W
