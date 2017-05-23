#include "imagem.h"
#include <stdio.h>
#include <stdlib.h>
int lerImagem(Img *imagem, char *nomeArq)
{
	FILE *canal;
	int i, j;
	canal = fopen(nomeArq, "r");
	if(canal != NULL)
	{
		//verificar se funciona somente com "imagem.ext" ou "imagem.tamj" etc
		fscanf(canal, "%s", imagem->ext);
		fscanf(canal, "%d %d", &imagem->tamj, &imagem->tami);
		fscanf(canal, "%d", &imagem->maxpix);

		
		//efetuar alocação dinamica para a struct pixel contida em imagem.
		imagem->pixel = (Pixel**) malloc( sizeof(Pixel*) * imagem->tami);

		for(i=0;i<imagem->tami;i++)
		{
			imagem->pixel[i] = (Pixel*) malloc( sizeof(Pixel) * imagem->tamj);	
			for(j=0;j<imagem->tami;j++)
			{
				fscanf(canal, "%d %d %d", 
					&imagem->pixel[i][j].r,
					&imagem->pixel[i][j].g, &imagem->pixel[i][j].b);
			}
		}
		fclose(canal);
		return 1;
	}
	else
	{
		printf("erro na criação de streamming de leitura\n");
		return 0;
	}
}
int escreverImagem(Img *img, char *nomeArq)
{
	int i,j;

	//criação de uma stream para escrita
	FILE *canal;
	canal = fopen(nomeArq,"w");
	
	//verifica se a criação da stream funciona
	if(canal != NULL)
	{
		fprintf(canal, "%s\n", &img->ext[0]);//escreve o tipo ex: "P3", "P4"
		fprintf(canal, "%d %d\n", img->tamj, img->tami);//escreve a dimenção tamj, tami
		fprintf(canal, "%d\n", img->maxpix);//escreve maximo de pixels
		//escreve os pixels
		for(i=0;i<512;i++)
		{
				for(j=0;j<512;j++)
				{
					fprintf(canal, "%d %d %d\n", img->pixel[i][j].r, img->pixel[i][j].g, img->pixel[i][j].b);
				}
		}
		fclose(canal);
		return 1;
	}
	else
	{
		printf("erro na criação de streamming de escrita\n");
		return 0;
	}
}
