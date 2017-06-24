#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"
#include"DEncode.h"
int main(int argc, char* argv[])
{
	int i;
	//bmp test

	/*
	Bmp image;


	bmpReader(&image,"wolf.bmp");
	bmpWritter(&image,"wolf2.bmp");
	*/

	//bitwise test
	
	
	/*Pnm image;
	Pnm image2;
	FileData data;
	pnmReader(&image,"lena.ppm");
	pnmReader(&image2,"lena.ppm");
	fileReader(&data ,"teste.txt");
	for(i=0;i<data.size;i++)
	{
		printf("%x ", data.data[i] );
	}
	printf("\n\n");
	pnmEncoder(&image, &data);
	for(i=0;i<100;i++)
	{
		printf("%d: %x\t", i+1, image2.pixel[0][i].r);
		printf("%x\t", image.pixel[0][i].r);
		printf("| %x\t", image2.pixel[0][i].g);
		printf("%x\t", image.pixel[0][i].g);
		printf("| %x\t", image2.pixel[0][i].b);
		printf("%x\n", image.pixel[0][i].b);
	}
	pnmWritter(&image,"lena2.ppm");*/
	
	
	Pnm image10;
	FileData data10;
	pnmReader(&image10,"lena2.ppm");
	pnmDecoder(&image10, &data10, 10);
	printf("\n");printf("\n");
	for(i=0;i<10;i++)
	{
		printf("%x ", data10.data[i]);
	}
	printf("\n");

	return 0;
}
