#ifndef IMAGEM_H
#define IMAGEM_H
typedef struct pixel{

		int r, g, b;

}Pixel;
/*ppm image struct, to store on ram*/
typedef struct ppm{
	
	char ext[3];
	int max_pixel;
	int sizej, sizei;
	Pixel **pixel;
}Ppm;
#endif
/*recebe um endereço de struct img e uma string;
**Preenche a struct com o arquivo de mesmo nome
**da string recebida. o arquivo deve ser .ppm;
**retorna 1, caso o programa tenha sucedido e
**0 para caso não tenha.*/
int lerImagem(Img*, char*);
int escreverImagem(Img *, char *);
