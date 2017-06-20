steg: main.c image.o DEncode.o
	gcc -W main.c image.o DEncode.o -o steg
image.o: image.c
	gcc -c image.c -W
DEncode.o: DEncode.c
	gcc -c DEncode.c -W
