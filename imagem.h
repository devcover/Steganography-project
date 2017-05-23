#ifndef IMAGEM_H
#define IMAGEM_H
typedef struct pixel{

		int r, g, b;

}Pixel;
/*informacoes da imagem (tipo do arquivo, quantidade maxima de pixels, dimensao da imagem)*/
typedef struct img{
	
	char ext[3];
	int maxpix;
	int tamj, tami;
	Pixel **pixel;
}Img;
#endif
/*recebe um endereço de struct img e uma string;
**Preenche a struct com o arquivo de mesmo nome
**da string recebida. o arquivo deve ser .ppm;
**retorna 1, caso o programa tenha sucedido e
**0 para caso não tenha.*/
int lerImagem(Img*, char*);
int escreverImagem(Img *, char *);
