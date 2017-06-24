#include"image.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int pnmReader(Pnm *image, char *file_name)
{
	FILE *channel;
	int i, j;
	int pad;
	channel = fopen(file_name, "r");
	if(channel!=NULL)
	{
		/*Reads the header*/
		fscanf(channel, "%s", &image->pnm_type[0]);
		fscanf(channel, "%d %d", &image->sizej, &image->sizei);
		fscanf(channel, "%d", &image->max_pixel);
		fread(&pad,1,1,channel);
		/*Sees what's the value of pnm_type to do the specific treatment to it*/
		if(strcmp(image->pnm_type,"P6")==0)
		{
			if(image->max_pixel<256)
			{
				image->pixel = (Pixel**) malloc( sizeof(Pixel*) * image->sizei);
				
				for(i=0;i<image->sizei;i++)
				{
					image->pixel[i] = (Pixel*) malloc( sizeof(Pixel) * image->sizej);	
					for(j=0;j<image->sizej;j++)
					{
						fread(&image->pixel[i][j].r,1,1,channel);
						fread(&image->pixel[i][j].g,1,1,channel);
						fread(&image->pixel[i][j].b,1,1,channel);
					}
				}
			}
			else
			{
				image->pixel = (Pixel**) malloc( sizeof(Pixel*) * image->sizei);
				for(i=0;i<image->sizei;i++)
				{
					image->pixel[i] = (Pixel*) malloc( sizeof(Pixel) * image->sizej);	
					for(j=0;j<image->sizej;j++)
					{
						fread(&image->pixel[i][j].r,2,1,channel);
						fread(&image->pixel[i][j].g,2,1,channel);
						fread(&image->pixel[i][j].b,2,1,channel);
					}
				}
			}
		}
		if(strcmp(image->pnm_type,"P5")==0){}
		if(strcmp(image->pnm_type,"P4")==0){}
		if(strcmp(image->pnm_type,"P3")==0)
		{
			image->pixel = (Pixel**) malloc( sizeof(Pixel*) * image->sizei);
			for(i=0;i<image->sizei;i++)
			{
				image->pixel[i] = (Pixel*) malloc( sizeof(Pixel) * image->sizej);	
				for(j=0;j<image->sizej;j++)
				{
					fscanf(channel,
					"%d %d %d",
					&image->pixel[i][j].r,
					&image->pixel[i][j].g,
					&image->pixel[i][j].b);
				}
			}
		}
		if(strcmp(image->pnm_type,"P2")==0){}
		if(strcmp(image->pnm_type,"P1")==0){}
		fclose(channel);
	}
	else
	{
		printf("reading file \"%s\" error\n", file_name);
		return 0;
	}
}
int pnmWritter(Pnm *image, char *file_name)
{
	FILE *channel;
	int i, j;

	channel = fopen(file_name, "wb");
	if(channel!=NULL)
	{
		fprintf(channel,"%s\n",&image->pnm_type[0]);
		fprintf(channel,"%d %d\n", image->sizej, image->sizei);
		fprintf(channel,"%d\n", image->max_pixel);
		if(strcmp(image->pnm_type,"P6")==0)
		{
			for(i=0;i<image->sizei;i++)
			{
				for(j=0;j<image->sizej;j++)
				{
					fwrite(&image->pixel[i][j].r,1,1,channel);
					fwrite(&image->pixel[i][j].g,1,1,channel);
					fwrite(&image->pixel[i][j].b,1,1,channel);
				}
			}
		}
		if(strcmp(image->pnm_type,"P3")==0)
		{
			for(i=0;i<image->sizei;i++)
			{
				for(j=0;j<image->sizej;j++)
				{
					fprintf(channel,"%d %d %d\n", image->pixel[i][j].r,image->pixel[i][j].g,image->pixel[i][j].b);
				}
			}
		}
		fclose(channel);
	}
	else
	{
		printf("writting to file \"%s\" error\n", file_name);
	}
}

int bmpReader(Bmp *image, char *file_name)
{
	FILE *channel;
	char c;
	unsigned int i, j;
	unsigned int clrsUsed;
	channel = fopen(file_name, "rb");
	if(channel!=NULL)
	{
		
		fread(&image->bFile.bfhType, sizeof(BITMAPFILEHEADER)-sizeof(image->bFile.ignore), 1, channel);
		fread(&image->bInfo.biHeader, sizeof(BITMAPINFOHEADER), 1, channel);
		if((clrsUsed = image->bInfo.biHeader.bihClrUsed)==0)
		{
			clrsUsed = 1;
		}

		image->bInfo.biColors = (RGBQUAD *) malloc( sizeof( RGBQUAD ) * clrsUsed );
		for(i=0;i<clrsUsed;i++)
		{
			fread(&image->bInfo.biColors[i],sizeof(RGBQUAD),1,channel);
		}

		image->pixels = malloc(1*image->bInfo.biHeader.bihImageSize);
		fread(image->pixels,image->bInfo.biHeader.bihImageSize,1,channel);
		fclose(channel);
	}
	else
	{
		printf("reading file \"%s\" error\n", file_name);
		return 0;
	}
}

int bmpWritter(Bmp *image, char *file_name)
{
	FILE *channel;
	unsigned int i, j;
	unsigned int clrsUsed;
	channel = fopen(file_name, "wb");
	if(channel!=NULL)
	{
		fwrite(&image->bFile.bfhType, sizeof(BITMAPFILEHEADER)-sizeof(image->bFile.ignore), 1, channel);
		fwrite(&image->bInfo.biHeader, sizeof(BITMAPINFOHEADER), 1, channel);
		if((clrsUsed = image->bInfo.biHeader.bihClrUsed) == 0)
		{
			clrsUsed = 1;
		}
		for(i=0;i<clrsUsed;i++)
		{
			fwrite(&image->bInfo.biColors[i],sizeof(RGBQUAD),1,channel);
		}
		fwrite(image->pixels,image->bInfo.biHeader.bihImageSize,1,channel);
		fclose(channel);
	}
	else
	{
		printf("reading file \"%s\" error\n", file_name);
		return 0;
	}
}
