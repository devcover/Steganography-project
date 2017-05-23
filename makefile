steg: main.c imagem.o
	gcc -W main.c imagem.o -o steg
imagem.o: imagem.c
	gcc -c imagem.c -W
