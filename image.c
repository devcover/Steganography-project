#include "image.h"
#include <stdio.h>
#include <stdlib.h>
//reads .ppm image and store information on and Img struct type
int lerImagemppm(Img *imagem, char *nomeArq)
{
	FILE *canal;
	int i, j;
	canal = fopen(nomeArq, "r");
	if(canal != NULL)
	{

		fscanf(canal, "%s", imagem->ext);
		fscanf(canal, "%d %d", &imagem->tamj, &imagem->tami);
		fscanf(canal, "%d", &imagem->maxpix);

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
		printf("error in creating a read stream\n");
		return 0;
	}
}
int escreverImagemppm(Img *img, char *nomeArq)
{
	int i,j;

	FILE *canal;
	canal = fopen(nomeArq,"w");
	
	if(canal != NULL)
	{
		fprintf(canal, "%s\n", &img->ext[0]);
		fprintf(canal, "%d %d\n", img->tamj, img->tami);
		fprintf(canal, "%d\n", img->maxpix);

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
		printf("error in criating a write stream\n");
		return 0;
	}
}
